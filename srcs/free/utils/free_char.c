#include "minishell.h"

char	*free_strs(char **big, char	*small, char *ret)
{
	int	i;

	i = 0;
	if (big)
	{
		while (big[i])
		{
			free(big[i]);
			i++;
		}
		free(big);
	}
	if (small)
		free(small);
	return (ret);
}

char	*free_errormalloc_return_null(char *s)
{
	printf("cd: error malloc\n");
	if (s)
		free(s);
	return (NULL);
}

char	*ft_free_two_str_null(char *s, char *s2)
{
	free(s);
	free(s2);
	return (NULL);
}

char	**ft_free_str_null_tab(int *s, char *s2, char **s3)
{
	int	i;

	i = 0;
	if (s)
		free(s);
	if (s2)
		free(s2);
	if (s3)
	{
		while (s3[i])
		{
			free(s3[i]);
			i++;
		}
		free(s3);
	}
	return (NULL);
}

char	*ft_free_str_null(char *s)
{
	if (s)
		free(s);
	return (NULL);
}
