#include "minishell.h"

static int	ft_modif_pwd(t_win *win, int i)
{
	free(win->env[i]);
	win->env[i] = NULL;
	win->env[i] = ft_strjoin("PWD=", "/");
	if (!win->env[i])
		return (ERROR_MALLOC);
	free(win->env[i]);
	return (SUCCESS);
}

int	ft_racine(t_win *win)
{
	int	i;

	i = 0;
	ft_init_val(win);
	while (win->env[i])
	{
		if (ft_strnstr(win->env[i], "PWD=", 4))
		{
			win->tmp = ft_give_path(win, "PWD=", i);
			if (!win->tmp)
				return (free_print_returnint(win->tmp, ERROR_MALLOC));
			if (ft_modif_pwd(win, i) == ERROR_MALLOC)
				return (free_print_returnint(win->tmp, ERROR_MALLOC));
		}
		i++;
	}
	win->res = ft_replace(win, "OLDPWD=", win->tmp);
	if (win->res == NULL)
		return (free_print_returnint(win->tmp, ERROR_MALLOC));
	free(win->res);
	if (chdir("/") != 0)
		ft_print_error_token(ERROR, "cd");
	return (ft_free_str_int(win->tmp, SUCCESS));
}
