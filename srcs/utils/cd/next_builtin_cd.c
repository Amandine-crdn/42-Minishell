#include "minishell.h"

char	*ft_replace(t_win *win, char *current_path, char *var_path)
{
	int		i;
	int		y;
	int		p;
	char	*copy;

	i = 0;
	y = 0;
	p = 0;
	copy = NULL;
	while (win->env[i])
	{
		// puts("iciiiiiii");
		if (ft_strnstr(win->env[i], var_path, ft_strlen(var_path)))
		{
			while (win->env[i][y] != '=')
				y++;
			y++;
			copy = malloc(sizeof(char) * (ft_strlen(win->env[i]) - y + 1));
			if (!copy)
				return (NULL);
			// puts("on a malloc");
			while (win->env[i][y])
				copy[p++] = win->env[i][y++];
			// puts("on a copié");
			copy[p] = 0;
			free(win->env[i]);
			win->env[i] = NULL;
			win->env[i] = ft_strjoin(var_path, current_path);
			// printf("win->env[i] : %s\n", win->env[i]);
			if (!win->env[i])
			{
				free(copy);
				return (NULL);
			}
		}
		i++;
	}
	// printf("copy : %s\n", copy);
	// printf("var_path : %s\n", var_path);
	// printf("win->env[i] : %s\n", win->env[i]);
	return (copy);
}

char	*ft_give_path(t_win *win, char *str, int i)
{
	int		p;
	int		y;
	char	*temp = NULL;

	p = 0;
	y = 0;
	temp = malloc(sizeof(char) * (ft_strlen(win->env[i]) - ft_strlen(str) + 1));
	if (!temp)
		return (NULL);
	while (y != ft_strlen(str) && y < ft_strlen(win->env[i]))
		y++;
	while (y < ft_strlen(win->env[i]))
		temp[p++] = win->env[i][y++];
	temp[p] = 0;
	return (temp);
}

int	ft_move(t_win *win, char *current_path)
{
	int		i;
	char	*res;
	char	*tmp;
	
	i = 0;
	res = NULL;
	tmp = NULL;
	while (win->env[i])
	{
		if (ft_strnstr(win->env[i], "PWD=", 4))
		{
			tmp = ft_give_path(win, "PWD=", i);
			if (!tmp)
				return (ft_print_error_token(ERROR_MALLOC, "cd"));
		}
		i++;
	} 
	if (tmp[0] == '/' && tmp[1] != 0)
	{
		res = ft_strjoin(tmp, "/");
		if (!res)
		{
			free(tmp);
			return (ft_print_error_token(ERROR_MALLOC, "cd"));
		}
	}
	else
	{
		res = ft_strdup(tmp);
		if (!res)
		{
			free(tmp);
			return (ft_print_error_token(ERROR_MALLOC, "cd"));
		}
	}
	free(tmp);
	tmp = ft_strjoin(res, current_path);
	if (!tmp)
	{
		free(res);
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	}
	free(res);
	res = ft_replace(win, tmp, "PWD=");
	if (!res)
	{
		free(tmp);
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	}
	free(res);
	free(tmp);
	return (SUCCESS);
}
