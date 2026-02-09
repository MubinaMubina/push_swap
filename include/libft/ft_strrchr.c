
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	target;
	char	*last_found;

	target = (char)c;
	last_found = (NULL);
	while (*s)
	{
		if (*s == target)
			last_found = (char *)s;
		s++;
	}
	if (*s == target)
		last_found = (char *)s;
	return (last_found);
}
