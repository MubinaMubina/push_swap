
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	if ((dst == NULL) && (src == NULL))
		return (dst);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d > s)
	{
		while (len--)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

// int	main(void)
// {
// 	char b[100] = "hello mubina ibrahim";
// 	char c[14] = "MUBINA";
// 	size_t len;

// 	len = 6;

// 	printf("%s\n", (char *)ft_memmove(b, c, len));
// 	printf("%s\n", (char *)memmove(b, c, len));
// 	return (0);
// }