
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)b;
	while (len > 0)
	{
		*(temp++) = (unsigned char)c;
		len--;
	}
	return (b);
}

// int	main(void)
// {
// 	int c;
// 	char b[10]= "hello";
// 	size_t len;

// 	c = 'X';
// 	len = 5;

// 	printf("%s\n", (char *)ft_memset(b, c, len));
// 	return (0);
// }
