
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	target;
	size_t			i;

	ptr = (unsigned char *)s;
	target = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == target)
			return ((void *)(ptr + i));
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char	*a;
// 	char		*result;
// 	size_t		c;

// 	a = "Mubina";
// 	c = 4;

// 	result = (char *)ft_memchr(a, 'b', c);
// 	if (result)
// 		printf("Found 'b' at: %s\n", result);
// 	else
// 		printf("Character 'b' not found in first %zu characters\n", c);

// 	return (0);
// }