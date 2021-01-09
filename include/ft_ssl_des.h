/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 01:50:32 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/09 01:18:32 by eduwer           ###   ########.fr       */
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
}				t_des_alg;

typedef struct	s_des_args {
	int			ac;
	char		**av;
	int			av_i;
	t_des_alg	alg;
	bool		base64;
	bool		decode;
	char		*filename_in;
	int			fd_in;
	char		*filename_out;
	int			fd_out;
	bool		password_malloced;
	char		*password;
	char		*key_str;
	char		*salt_str;
	char		*iv_str;
	bool		has_key;
	uint64_t	key;
	bool		has_salt;
	uint64_t	salt;
	bool		has_iv;
	uint64_t	iv;
	uint64_t	subkeys[16];
}				t_des_args;

uint8_t			*pbkdf2_hmac_sha256(char *password, uint8_t *salt, \
					size_t salt_len, size_t dk_len);
uint8_t			*hmac_sha256(char *password, uint8_t *msg, size_t msg_len);
void			gen_subkeys(t_des_args *ctx);
uint32_t		s_boxes(uint64_t n);
void			get_salt(t_des_args *ctx);
void			get_key(t_des_args *ctx);
int				des_process(t_des_args *args);

#endif
