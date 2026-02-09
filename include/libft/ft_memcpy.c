
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	if (dst == NULL && src == NULL)
		return (dst);
	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	while (n > 0)
	{
		*(temp_dst++) = *(temp_src++);
		n--;
	}
	return (dst);
}

// int	main(void)
// {
// 	char b[10] = "hello";
// 	char c[14] = "MUBINA.MUBINA";
// 	size_t len;

// 	len = 6;

// 	printf("%s\n", (char *)ft_memcpy(b, c, len));
// 	return (0);
// }