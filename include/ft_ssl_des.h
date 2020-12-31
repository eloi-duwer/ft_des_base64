/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 01:50:32 by eduwer            #+#    #+#             */
/*   Updated: 2020/12/31 17:58:16 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

# include <stdint.h>

uint8_t		*hmac_sha256_from_string(char *key_str, char *msg);
uint8_t		*hmac_sha256(uint8_t *key, size_t key_size, char *msg);

# endif
