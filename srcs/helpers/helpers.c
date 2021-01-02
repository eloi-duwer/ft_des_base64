/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 17:52:03 by eduwer            #+#    #+#             */
/*   Updated: 2020/12/31 22:29:02 by eduwer           ###   ########.fr       */
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

void		xor_array(void *inout, void *b, size_t size)
{
	unsigned char	*ptr_a;
	unsigned char	*ptr_b;

	ptr_a = (unsigned char *)inout;
	ptr_b = (unsigned char *)b;
	while (size > 0)
	{
		*ptr_a ^= *ptr_b;
		ptr_a++;
		ptr_b++;
		size--;
	}
}
