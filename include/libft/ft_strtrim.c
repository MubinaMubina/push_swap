
#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*result;
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	len = end - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1 + start, len);
	result[len] = '\0';
	return (result);
}
