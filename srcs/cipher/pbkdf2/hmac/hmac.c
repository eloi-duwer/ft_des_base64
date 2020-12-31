/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hmac.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:50:39 by eduwer            #+#    #+#             */
/*   Updated: 2020/12/31 18:18:03 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl_hash.h>
#include <ft_ssl_des.h>

static uint8_t	*get_key(uint8_t *key, size_t size)
{
	uint8_t	*ret;

	if ((ret = (uint8_t *)malloc(64)) == NULL)
		return (NULL);
	if (size > 64)
	{
		if ((key = raw_sha256(key, size)) == NULL)
			return (NULL);
		size = 32;
	}
	if (size <= 64)
	{
		ft_memcpy(ret, key, size);
		ft_memset(&ret[size], 0, 64 - size);
	}
	return (ret);
}

uint8_t			*hmac_sha256(uint8_t *key, size_t key_size, char *msg)
{
	uint8_t	opad[64];
	uint8_t	ipad[64];
	int		i;
	uint8_t	*buff;

	if ((key = get_key(key, key_size)) == NULL)
		return (NULL);
	i = 0;
	while (i < 64)
	{
		opad[i] = key[i] ^ 0x5C;
		ipad[i] = key[i] ^ 0x36;
		i++;
	}
	free(key);
	buff = ft_memcat(ipad, 64, (uint8_t *)msg, ft_strlen(msg));
	key = raw_sha256(buff, 64 + ft_strlen(msg));
	free(buff);
	buff = ft_memcat(opad, 64, key, 32);
	free(key);
	key = raw_sha256(buff, 64 + 32);
	free(buff);
	return (key);
}

uint8_t			*hmac_sha256_from_string(char *key_str, char *msg)
{
	return (hmac_sha256((uint8_t *)key_str, ft_strlen(key_str), msg));
}
