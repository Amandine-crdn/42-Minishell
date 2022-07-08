#include "minishell.h"

static char	**ft_copy_path(t_win *win)
{
	int		j;
	char	**global_path;

	j = 0;
	global_path = NULL;
	while (win->env[j])
	{
		if (ft_strnstr(win->env[j], "PATH=", 5))
		{
			global_path = ft_split_path(&win->env[j][5], ':');
			if (!global_path)
				return (NULL);
		}
		j++;
	}
	return (global_path);
}

static char	*ft_build_access(char *tab_line, char **global_path, int i)
{
	char	*tmp;
	char	*curr_path;

	tmp = ft_strjoin(global_path[i], "/");
	if (!tmp)
		return (NULL);
	curr_path = ft_strjoin(tmp, tab_line);
	if (!curr_path)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (curr_path);
}

char	*find_path_char(char *tab_line, t_win *win, int i)
{
	char	*curr_path;
	char	**global_path;

	global_path = NULL;
	curr_path = NULL;
	if (access(tab_line, X_OK) == 0)
		return (tab_line);
	global_path = ft_copy_path(win);
	if (!global_path)
		return (NULL);
	while (global_path && global_path[i])
	{
		curr_path = ft_build_access(tab_line, global_path, i);
		if (curr_path == NULL)
			break ;
		if (access(curr_path, X_OK) != -1)
			return (free_strs(global_path, NULL, curr_path));
		i++;
		free(curr_path);
	}
	return (free_strs(global_path, NULL, NULL));
}
