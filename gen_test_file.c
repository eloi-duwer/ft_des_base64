#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <libft.h>

//Used to generate a file with 0123456789ABCDEF (hex representation) in it.
int main()
{
	int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC);
	uint64_t data = ft_char_to_hex_u64("0123456789ABCDEF");
	int i = 0;
	unsigned char *pt = (unsigned char *)(&data);
	while (i < 8)
	{
		write(fd, &(pt[7 - i]), 1);
		i++;
	}
	close(fd);
	return (0);
}
