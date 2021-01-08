/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_salt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 03:59:35 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/08 04:28:09 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/random.h>
#include <ft_ssl_des.h>

void	get_salt(t_des_args *ctx)
{
	getrandom(&ctx->salt, 8, 0);
	ctx->has_salt = true;
}
