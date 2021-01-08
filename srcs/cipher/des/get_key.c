/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 04:04:28 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/08 16:39:07 by eduwer           ###   ########.fr       */
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

static void	get_password(t_des_args *ctx)
{
	struct termios old;
	struct termios new;

	if (tcgetattr(0, &old) != 0)
	{
		print_errno("Can't get password: ");
		exit(1);
	}
	ft_memcpy(&new, &old, sizeof(struct termios));
	new.c_lflag &= ~ECHO;
	if (tcsetattr(0, TCSAFLUSH, &new) != 0)
	{
		print_errno("Can't get password: ");
		exit(1);
	}
	ft_printf("Please enter des password: ");
	if (get_next_line(0, &ctx->password) == -1)
	{
		print_errno("Can't get password: ");
		exit(1);
	}
	ctx->password_malloced = true;
	ft_printf("\n");
	tcsetattr(0, TCSAFLUSH, &old);
}

void	get_key(t_des_args *ctx)
{
	uint8_t	*key;
	int		i;
	
	if (ctx->password == NULL)
		get_password(ctx);
	if ((key = pbkdf2_hmac_sha256(ctx->password, (uint8_t *)&ctx->salt, 8, 64)) == NULL)
	{
		print_errno("Can't generate key: ");
		exit(1);
	}
	ft_memset(ctx->password, 0, ft_strlen(ctx->password));
	if (ctx->password_malloced == true)
		free(ctx->password);
	i = -1;
	while (++i < 8)
		((uint8_t *)&ctx->key)[7 - i] = key[i];
	free(key);
}
