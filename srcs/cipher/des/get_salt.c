/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_salt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 03:59:35 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/11 01:07:15 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/random.h>
#include <ft_ssl_des.h>
#include <ft_ssl.h>

/*
**	If decoding, salt is necessarily in arg or in the file.
**	(we do not handle -nosalt)
**	If encoding, we can generate salt if none provided
*/

void	get_salt(t_des_args *ctx)
{
	char	str[16];

	if (ctx->decode == true)
	{
		if (ctx->has_salt == false && (read(ctx->fd_in, str, 16) != 16 \
			|| ft_strncmp(str, "Salted__", 8) != 0))
			exit(print_error("Error while reading: bad file format"));
		ft_memcpy(&ctx->salt, &str[8], 8);
		ctx->salt = reverse_bits_u64(ctx->salt);
	}
	else if (ctx->has_salt == false)
		getrandom(&ctx->salt, 8, 0);
	ctx->has_salt = true;
}
