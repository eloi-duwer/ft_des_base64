/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 01:50:32 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/08 03:48:14 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# include <libft.h>

typedef enum	e_des_alg
{
	ecb,
	cbc
}		t_des_alg;

typedef struct	s_des_args {
	int			ac;
	char		**av;
	int			av_i;
	t_des_alg	alg;
	bool		base64;
	bool		decode;
	char		*filename_in;
	char		*in;
	size_t		in_size;
	char		*filename_out;
	char		*password;
	char		*key_str;
	char		*salt_str;
	char		*iv_str;
	uint64_t	key;
	uint64_t	salt;
	uint64_t	iv;
	uint64_t	subkeys[16];
}				t_des_args;

uint8_t		*pbkdf2_hmac_sha256(char *password, uint8_t *salt, \
				size_t salt_len, size_t dk_len);
uint8_t		*hmac_sha256(char *password, uint8_t *msg, size_t msg_len);
void		gen_subkeys(t_des_args *ctx);
int			des_process(t_des_args *args);

#endif
