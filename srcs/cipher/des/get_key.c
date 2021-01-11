/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 04:04:28 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/11 01:07:05 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft_ssl_des.h>
#include <termios.h>

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
	uint8_t	*key;
	int		i;

	if ((key = pbkdf2_hmac_sha256(ctx->password, \
		(uint8_t *)&ctx->salt, 8, 8)) == NULL)
		exit(print_errno("Can't generate key: "));
	ft_memset(ctx->password, 0, ft_strlen(ctx->password));
	if (ctx->password_malloced == true)
		free(ctx->password);
	i = -1;
	while (++i < 8)
		((uint8_t *)&ctx->key)[7 - i] = key[i];
	free(key);
}
