#include "minishell.h"

static char	*ft_clean_cmd(char *cmd)
{
	int		i;
	char	*clean_cmd;

	i = 0;
	clean_cmd = NULL;
	if (cmd && cmd[ft_strlen(cmd) - 1] == '/')
	{	
		clean_cmd = malloc(sizeof(char) * ft_strlen(cmd));
		if (!clean_cmd)
			return (NULL);
		while (cmd && i < ft_strlen(cmd) - 1)
		{
			clean_cmd[i] = cmd[i];
			i++;
		}
		clean_cmd[i] = 0;
	}
	return (clean_cmd);
}

static char	*transform_tild(t_win *win, char *cmd, int i, int j)
{
	int		z;
	char	*tmp_home;
	char	*current_path;

	z = 0;
	tmp_home = NULL;
	current_path = NULL;
	tmp_home = ft_check_home(win);
	if (!tmp_home)
		return (NULL);
	current_path = malloc(sizeof(char) * ((ft_strlen(tmp_home) * count_tild(cmd)) + ft_strlen(cmd) - count_tild(cmd) + 1));
	if (!current_path)
	{
		free(tmp_home);
		return (NULL);
	}
	while (cmd[i])
	{
		if (cmd[i] == '~')
		{
			while (tmp_home[z])
			{
				current_path[j] = tmp_home[z];
				j++;
				z++;
			}
			i++;
			if (cmd[i] == 0)
				break ;
		}
		current_path[j] = cmd[i];
		i++;
		j++;
	}
	current_path[j] = 0;
	free(tmp_home);
	return (current_path);
}

char	*choice_current_path(char **cmd, t_win *win)
{
	char	*copy;
	char	*current_path;

	current_path = NULL;
	if (cmd[1] && cmd[1][ft_strlen(cmd[1]) - 1] == '/')
	{
		current_path = ft_clean_cmd(cmd[1]);
		if (!current_path)
			return (NULL);
		if (ft_strncmp(current_path, "~", 1) == 0)
		{
			copy = NULL;
			copy = ft_strdup(current_path);
			if (!copy)
				return (ft_free_str_null(current_path));
			free(current_path);
			current_path = transform_tild(win, copy, 0, 0);
			if (!current_path)
				return (ft_free_str_null(copy));
			free(copy);
		}
	}
	else
	{
		current_path = ft_strdup(cmd[1]);
		if (!current_path)
			return (NULL);
	}
	return (current_path);
}

int	ft_return_value(t_win *win, char **cmd)
{
	if (ft_strncmp(cmd[1], "-\0", 2) == 0)
		return (ft_return(win));
	else if (ft_strncmp(cmd[1], "/\0", 2) == 0)
		return (ft_racine(win));
	else if (ft_strncmp(cmd[1], "~\0", 2) == 0 || ft_strncmp(cmd[1], "~/\0", 3) == 0 || ft_strncmp(cmd[1], "--\0", 3) == 0)
		return (ft_home(win));
	return (0);
}
