/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:52:03 by eduwer            #+#    #+#             */
/*   Updated: 2020/03/02 22:09:48 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint32_t	left_rotate(uint32_t buff, unsigned int amount)
{
	return (buff << amount | buff >> (32 - amount));
}

uint32_t	right_rotate(uint32_t buff, unsigned int amount)
{
	return (buff >> amount | buff << (32 - amount));
}

char		*print_bits(void *bytes, size_t size)
{
	int				i;
	size_t			j;
	char			*ret;
	unsigned char	*ptr;

	ptr = (unsigned char *)bytes;
	ret = (char *)ft_memalloc(sizeof(char) * (size * 9));
	j = 0;
	while (j < size)
	{
		i = 7;
		while (i >= 0)
		{
			ret[(j * 9) + (7 - i)] = (ptr[j] & (0x1 << i & 0xFF)) ? '1' : '0';
			--i;
		}
		if (j < size - 1)
			ret[j * 9 + 8] = ' ';
		++j;
	}
	return (ret);
}

void		print_errno(char *buf)
{
	char	*errstr;

	errstr = strerror(errno);
	ft_fdprintf(2, "%s %s\n", buf, errstr);
}

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
		++i;
	}
	return (ret);
}
