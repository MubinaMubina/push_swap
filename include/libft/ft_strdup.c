
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (str == NULL)
		return (NULL);
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

// int	main(void)
// {
// 	printf("%s\n", ft_strdup("MUBINA"));
// 	printf("%s\n", strdup("MUBINA"));
// }