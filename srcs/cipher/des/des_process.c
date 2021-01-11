/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 02:54:27 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/11 01:00:28 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft_ssl_des.h>

static bool		des_get_next_block(t_des_args *ctx, uint64_t *block)
{
	unsigned char	buff[8];
	ssize_t			ret;
	ssize_t			i;

	if (ctx->fd_in == -1)
		return (false);
	ret = read(ctx->fd_in, buff, 8);
	if (ret == -1)
		exit(print_errno("Can't read file: "));
	if (ret >= 0 && ret < 8)
	{
		close(ctx->fd_in);
		ctx->fd_in = -1;
	}
	if (ret == 0)
		return (false);
	*block = 0;
	i = 0;
	while (i < ret)
	{
		*block = (*block << 8) | buff[i];
		i++;
	}
	return (true);
}

/*
**	Initial Permutation for a 64-bit block
*/

static const uint8_t	g_ip[64] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

/*
**	Reverse Initial Permutation for a 64-bit block
*/

static const uint8_t	g_rip[64] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};

static const uint8_t	g_expand[48] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

static uint32_t	func(uint32_t half, uint64_t subkey)
{
	uint64_t	expanded_half;

	expanded_half = ((uint64_t)half) << 32;
	expanded_half = swap_bits_u64(expanded_half, g_expand, 48);
	expanded_half = subkey ^ expanded_half;
	return (s_boxes(expanded_half));
}

/*
** halves: Left then Right half of the block,
** For the current round and the precendent
*/

static int		des_loop_blocks(t_des_args *ctx)
{
	uint64_t	block;
	uint32_t	halves[2][2];
	int			i;

	des_write_salt_to_file(ctx);
	while (des_get_next_block(ctx, &block))
	{
		block = swap_bits_u64(block, g_ip, 64);
		halves[0][0] = block >> 32;
		halves[0][1] = block & 0xFFFFFFFF;
		i = -1;
		while (++i < 16)
		{
			halves[1][0] = halves[0][1];
			halves[1][1] = halves[0][0] ^ func(halves[0][1], ctx->subkeys[i]);
			halves[0][0] = halves[1][0];
			halves[0][1] = halves[1][1];
		}
		des_write_to_file(ctx, swap_bits_u64(\
			((uint64_t)halves[0][1] << 32) | halves[0][0], g_rip, 64));
	}
	des_empty_buffer(ctx);
	close(ctx->fd_out);
	return (0);
}

int				des_process(t_des_args *ctx)
{
	if (ctx->key_str != NULL && (ctx->has_key = true))
		ctx->key = ft_char_to_hex_u64(ctx->key_str);
	if (ctx->salt_str != NULL && (ctx->has_salt = true))
		ctx->salt = reverse_bits_u64(ft_char_to_hex_u64(ctx->salt_str));
	if (ctx->iv_str != NULL && (ctx->has_iv = true))
		ctx->iv = ft_char_to_hex_u64(ctx->iv_str);
	ctx->fd_in = 0;
	if (ctx->filename_in != NULL && \
		(ctx->fd_in = open(ctx->filename_in, O_RDONLY)) == -1)
		return (print_errno("Can't open input file: "));
	ctx->fd_out = 1;
	if (ctx->filename_out != NULL && \
		(ctx->fd_out = open(ctx->filename_out, O_WRONLY)) == -1)
		return (print_errno("Can't open output file: "));
	if (ctx->has_key == false && ctx->password == NULL)
		get_password(ctx);
	get_salt(ctx);
	if (ctx->has_key == false)
		get_key(ctx);
	gen_subkeys(ctx);
	return (des_loop_blocks(ctx));
}
