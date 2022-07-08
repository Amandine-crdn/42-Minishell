#include "minishell.h"

char	**ft_copy_env(char **new_env, char **old_env, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_env[i] = NULL;
		new_env[i] = ft_strdup(old_env[i]);
		if (!new_env[i])
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
