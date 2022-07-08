#include "minishell.h"

int	ft_count_slash(t_win *win)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (win->env[i])
	{
		if (ft_strnstr(win->env[i], "PWD=", 4))
		{
			j = 0;
			while (win->env[i][j])
			{
				if (win->env[i][j] == '/')
					count++;
				j++;
			}
		}
		i++;
	}
	return (count);
}

int	count_tild(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '~')
			count++;
		i++;
	}
	return (count);
}
