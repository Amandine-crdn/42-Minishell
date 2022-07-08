#include "minishell.h"

static char	*check_pwd(t_win *win)
{
	int		i;
	char	*tmp = NULL;

	i = 0;
	while (win->env[i])
	{
		if (ft_strnstr(win->env[i], "PWD=", 4))
		{
			tmp = ft_give_path(win, "PWD=", i);
			if (!tmp)
				return (free_errormalloc_return_null(tmp));
		}
		i++;
	}
	return (tmp);
}

char		*ft_check_home(t_win *win)
{
	int		i;
	char	*tmp_home = NULL;

	i = 0;
	while (win->env[i])
	{
		if (ft_strnstr(win->env[i], "HOME=", 5))
		{
			tmp_home = ft_give_path(win, "HOME=", i);
			if (!tmp_home)
				return (NULL);
		}
		i++;
	}
	return (tmp_home);
}

int			ft_home(t_win *win)
{
	char	*tmp;
	char	*tmp_home;
	char 	*res;

	tmp = NULL;
	tmp_home = NULL;
	res = NULL;
	tmp_home = ft_check_home(win);
	if (!tmp_home)
		return (ERROR_MALLOC);
	if (chdir(tmp_home) != 0)
	{
		free(tmp_home);
		return (ERROR);
	}	
	tmp = check_pwd(win);
	if (!tmp)
	{
		ft_free_two_str(tmp, tmp_home);
		return (ERROR_MALLOC);
	}
	res = ft_replace(win, tmp, "OLDPWD=");
	if (res == NULL)
	{
		ft_free_two_str(tmp, tmp_home);
		free(res);
		return (ERROR_MALLOC);
	}
	free(res);
	res = ft_replace(win, tmp_home, "PWD=");
	if (res == NULL)
	{
		ft_free_two_str(tmp, tmp_home);
		free(res);
		return (ERROR_MALLOC);
	}
	ft_free_two_str(tmp, tmp_home);
	free(res);
	return (SUCCESS);
}
