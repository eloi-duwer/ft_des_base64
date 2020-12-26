#include <ft_ssl_base64.h>
#include <ft_ssl.h>

static int	process_base64(t_base64_args *args)
{
	char	*ret;
	size_t	ret_size;
	int		fd;

	if (args->decode == true)
		ret = dec_base64(args->data, args->data_size, &ret_size);
	else
		ret = enc_base64(args->data, args->data_size, &ret_size);
	if (ret == NULL)
	{
		print_errno("ft_ssl: Error during base64 process: ");
		return (1);
	}
	fd = 1;
	if (args->output_file != NULL && (fd = open(args->output_file, \
		O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU)) == -1)
	{
		print_errno("ft_ssl: can't open output file: ");
		return (1);
	}
	if (write(fd, ret, ret_size) == -1 || (args->decode == false && write(fd, "\n", 1) == -1))
	{
		print_errno("ft_ssl: error while writing to file: ");
		return (1);
	}
	if (fd != 1)
		close(fd);
	free(args->data);
	free(ret);
	return (0);
}

static int	read_file_and_process(t_base64_args *args)
{
	if (args->input_file != NULL)
	{
		if ((args->fd = open(args->input_file, O_RDONLY)) == -1)
		{
			print_errno("ft_ssl: Can't open input file: ");
			return (1);
		}
		if (read_whole_file(args->fd, (void **)&args->data, &args->data_size) != 0)
		{
			print_errno("ft_ssl: Error while reading input file: ");
			return (1);
		}
		close(args->fd);
	}
	else if (read_whole_stdin((void **)&args->data, &args->data_size) != 0)
	{
		print_errno("ft_ssl: Error while reading stdin: ");
		return (1);
	}
	return (process_base64(args));
}

static int	base64_parse_subargs(t_base64_args *args, int ac, char **av)
{
	if (ft_strcmp(av[args->av_i], "-e") == 0)
		args->decode = false;
	else if (ft_strcmp(av[args->av_i], "-d") == 0)
		args->decode = true;
	else if (ft_strcmp(av[args->av_i], "-i") == 0)
	{
		args->av_i++;
		if (args->av_i >= ac)
		{
			ft_printf("argument -i needs an input file after it\n");
			return (1);

		}
		args->input_file = av[args->av_i];
	}
	else if (ft_strcmp(av[args->av_i], "-o") == 0)
	{
		args->av_i++;
		if (args->av_i >= ac)
		{
			ft_printf("argment -o needs an output file after it\n");
			return (1);
		}
		args->output_file = av[args->av_i];
	}
	else
		return (print_base64_usage());
	return (0);
}

int			base64_arg_parsing(int ac, char **av)
{
	t_base64_args args;

	ft_bzero(&args, sizeof(args));
	args.av_i = 2;
	while (args.av_i < ac)
	{
		if (av[args.av_i][0] == '-')
		{
			if (base64_parse_subargs(&args, ac, av) != 0)
				return (1);
		}
		else
		{
			ft_printf("Extra operand: '%s'\n", av[args.av_i]);
			return (1);
		}
		args.av_i++;
	}
	return (read_file_and_process(&args));
}