/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 02:54:27 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/08 16:54:53 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft_ssl_des.h>
#include <ft_ssl_base64.h>

int				des_process(t_des_args *ctx)
{
	if (ctx->key_str != NULL && (ctx->has_key = true))
		ctx->key = ft_char_to_hex_u64(ctx->key_str);
	if (ctx->salt_str != NULL && (ctx->has_salt = true))
		ctx->salt = ft_char_to_hex_u64(ctx->salt_str);
	if (ctx->iv_str != NULL && (ctx->has_iv = true))
		ctx->iv = ft_char_to_hex_u64(ctx->iv_str);
	//FOR DEBUG PURPOSES ONLY, SEE http://page.math.tu-berlin.de/~kant/teachinghess/krypto-ws2006/des.htm
	//ctx->has_key = true;
	//ctx->key = 0x133457799BBCDFF1;
	if (ctx->has_salt == false)
		get_salt(ctx);
	if (ctx->has_key == false)
		get_key(ctx);
	gen_subkeys(ctx);

	return (0);
}
