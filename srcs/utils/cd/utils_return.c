#include "minishell.h"

char	*ft_check_pwd(t_win *win)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (win->env[i])
	{
		if (ft_strnstr(win->env[i], "PWD=", 4))
		{
			tmp = ft_give_path(win, "PWD=", i);
			if (!tmp)
				return (free_errormalloc_return_null(tmp));
			break ;
		}
		i++;
	}
	return (tmp);
}

char	*ft_check_oldpwd(t_win *win)
{
	int		i;
	char	*tmp_old;

	i = 0;
	tmp_old = NULL;
	while (win->env[i])
	{
		if (ft_strnstr(win->env[i], "OLDPWD=", 7))
		{
			tmp_old = ft_give_path(win, "OLDPWD=", i);
			if (!tmp_old)
				return (free_errormalloc_return_null(tmp_old));
		}
		i++;
	}
	return (tmp_old);
}

int	ft_return(t_win *win)
{
	char	*tmp_old;
	char	*res;
	char 	*copy;

	tmp_old = NULL;
	res = NULL;
	copy = NULL;
	tmp_old = ft_check_oldpwd(win);
	if (!tmp_old)
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	if (chdir(tmp_old) != 0)
		return (ft_print_error_token(ERROR_FILE_DIRECTORY, "cd"));
	copy = ft_replace(win, tmp_old, "PWD=");
	if (copy == NULL)
	{
		free(tmp_old);
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	}
	free(tmp_old);
	res = ft_replace(win, copy, "OLDPWD=");
	if (res == NULL)
	{
		free(copy);
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	}
	ft_free_two_str(res, copy);
	return (SUCCESS);
}

/*int	ft_return(t_win *win)
{
	ft_init_val(win);
	win->tmp_old = ft_check_oldpwd(win);
	if (!win->tmp_old)
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	if (chdir(win->tmp_old) != 0)
		return (ft_print_error_token(ERROR_FILE_DIRECTORY, "cd"));
	win->copy = ft_replace(win, win->tmp_old, "PWD=");
	if (win->copy == NULL)
	{
		free(win->tmp_old);
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	}
	free(win->tmp_old);
	win->res = ft_replace(win, win->copy, "OLDPWD=");
	if (win->res == NULL)
	{
		free(win->copy);
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	}
	ft_free_two_str(win->res, win->copy);
	return (SUCCESS);
}*/
