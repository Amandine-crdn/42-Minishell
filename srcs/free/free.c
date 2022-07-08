#include "minishell.h"

int	ft_free_str_int(char *s, int err)
{
	free(s);
	return (err);
}

int	free_print_returnint(char *s, int err)
{
	free(s);
	if (err == ERROR_MALLOC)
		printf("Malloc error\n");
	else
		printf("Error\n");
	return (err);
}

int	ft_free_null_int(char *s, char *s2, int err)
{
	if (s)
		free(s);
	if (s2)
		free(s2);
	if (err == ERROR_MALLOC)
		return (ERROR_MALLOC);
	else
		return (SUCCESS);
}

int	*ft_free_int_null(int *s)
{
	if (s)
		free(s);
	return (NULL);
}

int	ft_free_tab_int(char **big, int err)
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
	return (err);
}
