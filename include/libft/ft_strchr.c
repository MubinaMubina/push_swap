
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	target;

	target = (char)c;
	while (*s)
	{
		if (*s == target)
			return ((char *)s);
		s++;
	}
	if (*s == target)
		return ((char *)s);
	return (NULL);
}
// int	main(void)
// {
// 	const char *s;

// 	s = "Mubinanananana";
// // can use %p for getting the first occurance memory location
// 	printf("%s\n", ft_strchr(s, 'n'));
// 	printf("%s\n", strchr(s, 'n'));
// }