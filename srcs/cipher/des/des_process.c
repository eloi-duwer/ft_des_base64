/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 02:54:27 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/08 03:29:50 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft_ssl_des.h>

int				des_process(t_des_args *ctx)
{
	if (ctx->key_str != NULL)
		ctx->key = ft_char_to_hex_u64(ctx->key_str);
	if (ctx->salt_str != NULL)
		ctx->salt = ft_char_to_hex_u64(ctx->salt_str);
	if (ctx->iv_str != NULL)
		ctx->iv = ft_char_to_hex_u64(ctx->iv_str);
	//FOR DEBUG PURPOSES ONLY, SEE http://page.math.tu-berlin.de/~kant/teachinghess/krypto-ws2006/des.htm
	ctx->key = 0x133457799BBCDFF1;
	gen_subkeys(ctx);
	return (0);
}
