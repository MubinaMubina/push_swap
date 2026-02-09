
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*temp;
	size_t	i;
	size_t	total;

	i = 0;
	total = count * size;
	if (count > 0 && size > 0 && count > (size_t)-1 / size)
		return (NULL);
	temp = malloc(total);
	if (!temp)
		return (NULL);
	while (i < total)
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}

// int	main(void)
// {
// 	size_t i;
// 	int *zeros;
// 	int *zeros1;
// 	zeros = ft_calloc(3, 4);
// 	zeros1 = calloc(3, 4);
// 	i = 0;
// 	while (i < (3))
// 	{
// 		printf("%d\n", zeros[i]);
// 		printf("%d\n", zeros1[i]);
// 		printf("after iteration, %zu\n", i);
// 		i++;
// 	}
// }void	*ft_calloc(size_t count, size_t size)
