/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 15:23:10 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/02 01:22:24 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <unistd.h>
# include <libft.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

int				print_hash_usage(void);
int				print_base64_usage(void);
int				print_commands(char *name);
int				print_errno(char *str);
int				print_error(char *str);
char			*print_bits(void *bytes, size_t size);
uint64_t		reverse_bits(uint64_t in);
uint32_t		uint32_t_reverse_bits(uint32_t in);
uint32_t		left_rotate(uint32_t buff, unsigned int amount);
uint32_t		right_rotate(uint32_t buff, unsigned int amount);
void			xor_array(void *inout, void *b, size_t size);
int				hash_arg_parsing(int ac, char **av);
int				base64_arg_parsing(int ac, char **av);

#endif
