/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_salt_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 03:59:35 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/16 03:47:00 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/random.h>
#include <ft_ssl_des.h>
#include <ft_ssl.h>
#include <termios.h>

/*
**	If decoding, salt is necessarily in arg or in the file.
**	(we do not handle -nosalt)
**	If encoding, we can generate salt if none provided
*/

void	get_salt(t_des_args *ctx)
{
	char	str[16];

	if (ctx->decode == true)
	{
		if (read(ctx->fd_in, str, 16) != 16 \
			|| ft_strncmp(str, "Salted__", 8) != 0)
			exit(print_error("Error while reading: bad file format"));
		ft_memcpy(&ctx->salt, &str[8], 8);
		ctx->salt = reverse_bits_u64(ctx->salt);
		
	}
	else if (ctx->has_salt == false)
		getrandom(&ctx->salt, 8, 0);
	ctx->has_salt = true;
}

/*
** As getpass is considered obsolete, this is the
** recommended minimal implementation taken from
** https://www.gnu.org/software/libc/manual/html_node/getpass.html
*/

void		get_password(t_des_args *ctx)
{
	struct termios old;
	struct termios new;

	if (tcgetattr(0, &old) != 0)
		exit(print_errno("Can't get password: "));
	ft_memcpy(&new, &old, sizeof(struct termios));
	new.c_lflag &= ~ECHO;
	if (tcsetattr(0, TCSAFLUSH, &new) != 0)
		exit(print_errno("Can't get password: "));
	ft_printf("Please enter des password: ");
	if (get_next_line(0, &ctx->password) == -1)
		exit(print_errno("Can't get password: "));
	ctx->password_malloced = true;
	ft_printf("\n");
	tcsetattr(0, TCSAFLUSH, &old);
}

void		get_key(t_des_args *ctx)
{
	uint8_t		*key;
	uint64_t	salt;
	int			i;

	salt = reverse_bits_u64(ctx->salt);
	if ((key = pbkdf2_hmac_sha256(ctx->password, \
		(uint8_t *)&salt, 8, 8)) == NULL)
		exit(print_errno("Can't generate key: "));
	ft_memset(ctx->password, 0, ft_strlen(ctx->password));
	if (ctx->password_malloced == true)
		free(ctx->password);
	i = -1;
	while (++i < 8)
		((uint8_t *)&ctx->key)[7 - i] = key[i];
	free(key);
}
