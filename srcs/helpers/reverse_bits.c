/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 21:39:02 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/02 01:13:41 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint64_t	reverse_bits(uint64_t in)
{
	int			i;
	uint64_t	ret;

	i = 0;
	ret = 0;
	while (i < 64 / 8)
	{
		ret = ret << 8;
		ret |= (in >> (i * 8)) & 0xFF;
		i++;
	}
	return (ret);
}

uint32_t	uint32_t_reverse_bits(uint32_t in)
{
	size_t		i;
	uint32_t	ret;

	i = 0;
	ret = 0;
	while (i < 32 / 8)
	{
		ret = ret << 8;
		ret |= (in >> (i * 8)) & 0xFF;
		i++;
	}
	return (ret);
}
