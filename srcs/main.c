/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:03:45 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/02 01:00:02 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

int			print_commands(char *name)
{
	if (name != NULL)
		ft_fdprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\n", name);
	else
		ft_fdprintf(2, "Usage: ./ft_ssl <command>\n\n");
	ft_fdprintf(2, "Standart commands:\n\n");
	ft_fdprintf(2, "Message Digest commands:\nmd5\nsha256\nsha384\nsha512\n\n");
	ft_fdprintf(2, "Cipher commands:\nbase64\n");
	return (1);
}

int			print_hash_usage(void)
{
	ft_fdprintf(2, "Usage: ./ft_ssl <hash command> [-pqr] [-s string] \
[files ...]\n");
	return (1);
}

int			print_base64_usage(void)
{
	ft_fdprintf(2, "Usage: ./ft_ssl base64 [-ed] [-i input_file] \
[-o output_file]\n");
	return (1);
}

#include <ft_ssl_des.h>
#include <ft_ssl_base64.h>

int			main(int argc, char **argv)
{
	size_t	salt_size;
	uint8_t	*salt = ft_char_to_hex(argv[2], &salt_size);
	if (salt == NULL)
	{
		ft_printf("salt is invalid, expected hex format\n");
		return (1);
	}
	uint8_t	*ret = pbkdf2_hmac_sha256(argv[1], salt, salt_size, 32);
	ft_printf("hex: ");
	for (int i = 0; i < 32; i++) {
		ft_printf("%x", ret[i]);
	}
	ft_printf("\n");
	size_t size;
	char *base64 = enc_base64((char *)ret, 32, &size);
	ft_printf("base64: %s\n", base64);
	free(salt);
	free(ret);
	free(base64);

	/*if (argc == 1)
		return (print_commands(NULL));
	if (ft_strcmp(argv[1], "md5") == 0
		|| ft_strcmp(argv[1], "sha256") == 0
		|| ft_strcmp(argv[1], "sha512") == 0
		|| ft_strcmp(argv[1], "sha384") == 0)
		return (hash_arg_parsing(argc, argv));
	else if (ft_strcmp(argv[1], "base64") == 0)
		return (base64_arg_parsing(argc, argv));
	else
		return (print_commands(argv[1]));*/
}
