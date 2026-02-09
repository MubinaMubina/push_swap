
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	i = 0;
	while (src[i] && (dstlen + i < dstsize - 1))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}

// int	main(void)
// {
// 	char dst[100] = "Mubina";
// 	char src[10] = "nothing90";
// 	size_t dstsize;

// 	dstsize = 20;
// 	printf("Result: %zu\n", ft_strlcat(dst, src, dstsize));
// 	printf("Final dst: %s\n", dst);
// 	return (0);
// }