/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 02:41:42 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/17 13:26:29 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft_ssl_des.h>

/*
** Why do we try multiple reads?
** In non-canonical mode, a read on tty 
** (if we read from stdin without a pipe afaik) will stop when an endl
** is reached, which means that we can have a ret from read < 8 but bytes are
** still disponible after (read can do this if you read from a socket too)
** So we loop until we have read enough bytes
*/
static ssize_t	des_get_64_bits(t_des_args *ctx, uint64_t *bl)
{
	ssize_t	tot;
	ssize_t	ret;

	if (ctx->fd_in == -1 || ctx->finished_reading == true)
		return (0);
	tot = 0;
	*bl = 0;
	while (tot < 8)
	{
		ret = read(ctx->fd_in, &((uint8_t *)bl)[tot], 8 - tot);
		if (ret == -1)
			exit(print_errno("Error while reading the file: "));
		if (ret == 0)
			return (tot);
		tot += ret;
	}
	return (tot);
}

static bool		set_finished_reading(t_des_args *ctx)
{
	close(ctx->fd_in);
	ctx->finished_reading = true;
	return (true);
}

/*
** Decoding mode is quite a hassle, because of the padding
** there is ALWAYS padding at the end, even if we don't need it 
** (so that the presence of padding is not ambiguous)
** Which means that we CAN have 8 bytes of padding,
** We can't know it in advance. The solution is to add a read Buffer
** So that we always try to read what is after what we return, and we
** can know if the current block contains the padding or not
** We could do it by reading the entire file, but it's quite gross and 
** ram-ineficient (yes it has been done everywhere else shhhhhhh)
** This trickery should not be needed elsewere, as there is no padding
** on the other algs
*/

bool			des_get_next_block(t_des_args *ctx, uint64_t *bl)
{
	ssize_t	ret;

	if (ctx->finished_reading == true)
		return (false);
	*bl = ctx->n_bl;
	if (ctx->next_block_is_last == true)
		return (set_finished_reading(ctx));
	ret = des_get_64_bits(ctx, &ctx->n_bl);
	ctx->n_bl = reverse_bits_u64(ctx->n_bl);
	if (ret < 8)
	{
		ctx->next_block_is_last = true;
		if (ctx->decode == false)
			ft_memset(&ctx->n_bl, 8 - ret, 8 - ret);
		else if (ret != 0)
			exit(print_error(\
				"Error: File size is expected to be a multiple of 8 bytes"));
		else
			return (set_finished_reading(ctx));
	}
	return (true);
}

void			des_init_next_block(t_des_args *ctx)
{
	ssize_t	ret;

	ret = des_get_64_bits(ctx, &ctx->n_bl);
	ctx->n_bl = reverse_bits_u64(ctx->n_bl);
	if (ret < 8)
	{
		ctx->next_block_is_last = true;
		if (ctx->decode == false)
			ft_memset(&ctx->n_bl, 8 - ret, 8 - ret);
		else if (ret != 0)
			exit(print_error(\
				"Error: File size is expected to be a multiple of 8 bytes"));
	}
}
