
#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	*get_word(const char *s, char c)
{
	int		len;
	char	*word;
	int		i;

	len = word_len(s, c);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	fill_result(char **result, const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			result[i] = get_word(s, c);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	result[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	fill_result(result, s, c);
	return (result);
}

// int	main(void)
// {
// 	char *test = "hello,world,this,is,a,test";
// 	char **result = ft_split(test, ',');
// 	int i = 0;

// 	printf("Original string: %s\n", test);
// 	while (result[i])
// 	{
// 		printf("Word %d: %s\n", i, result[i]);
// 		i++;
// 	}
// }