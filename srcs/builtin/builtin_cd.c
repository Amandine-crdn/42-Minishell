#include "minishell.h"

static int	ft_end(t_win *win, int *value_cmd_path, char *tmp_pwd, char *curr_path)
{
	char	*res;
	
	res = NULL;
	res = ft_replace(win, tmp_pwd, "OLDPWD=");
	if (res == NULL)
	{
		ft_free_two_str(tmp_pwd, curr_path);
		free(value_cmd_path);
		// free(res); // a virer non ?
		return (ERROR_MALLOC);//return (0); // pour moi si res est null c'est qu'il y a eu un pepin de malloc, tu confirmes ?
	}
	ft_free_two_str(tmp_pwd, curr_path);
	free(value_cmd_path);
	//if (res == NULL) // on peut enlever non ?
	//	return (0);
	free(res);
	return (SUCCESS);
}

static int	ft_cd(t_win *win, char *cmd)
{
	if (ft_strncmp(cmd, "..\0", 3) == 0)
		return (ft_cd_pp(win, cmd));
	else
		return (ft_move(win, cmd));
}

static int	ft_suite(char *curr_path, char **cmd, t_win *win)
{
	int		i;
	char	**cmd_path;
	int		*value_cmd_path;
	char	*tmp_pwd;
	char	*res;

	i = 0;
	cmd_path = NULL;
	value_cmd_path = NULL;
	tmp_pwd = NULL;
	res = NULL;
	value_cmd_path = creation_malloc(curr_path);
	if (value_cmd_path == NULL)
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	cmd_path = creation_tab(curr_path, value_cmd_path);
	if (cmd_path == NULL)
	{
		free(value_cmd_path);
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	}
	tmp_pwd = ft_check_pwd(win);
	if (tmp_pwd == NULL)
	{
		free(value_cmd_path);
		ft_free_tab_int(cmd_path, ERROR_MALLOC);
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	}
	if (curr_path[0] == '/')
	{
		res = ft_replace(win, "/", "PWD=");
		if (!res)
		{
			free(value_cmd_path);
			free(value_cmd_path);
			ft_free_tab_int(cmd_path, ERROR_MALLOC);
			return (ft_print_error_token(ERROR_MALLOC, "cd"));
		}
	}
	while (cmd_path[i] && i < count_word(curr_path))
	{
		if (ft_cd(win, cmd_path[i]) == ERROR_MALLOC)
		{
			free(value_cmd_path);
			free(value_cmd_path);
			ft_free_tab_int(cmd_path, ERROR_MALLOC);
			return (ERROR_MALLOC);
		}
		i++;
	}
	ft_free_tab(cmd_path, count_word(cmd[1]));
	if (ft_end(win, value_cmd_path, tmp_pwd, curr_path) == ERROR_MALLOC)
	{
		free(value_cmd_path);
		free(value_cmd_path);
		ft_free_tab_int(cmd_path, ERROR_MALLOC);
		return (ERROR_MALLOC);
	}
	return (SUCCESS);
}

/*static int	ft_errors(t_win *win, char **cmd)
{

}*/


int	ft_check_cd(t_win *win, char **cmd)
{
	char	*current_path;

	g_exit_status = 127; // virer ?
	current_path = NULL;
	if (!cmd[1])
	{
		if (ft_home(win) == ERROR_MALLOC)
			return (ft_print_error_token(ERROR_MALLOC, "cd"));
		g_exit_status = 0;
		return (SUCCESS);
	}
	if (cmd[2])
		return (ft_print_error_token(ERROR_SYNTAX, "cd"));
	current_path = choice_current_path(cmd, win);
	/////// VERIF ICI ///// MALLOC
	if (!current_path)
		return (ft_print_error_token(ERROR_MALLOC, "cd"));
	if (ft_return_value(win, cmd) == ERROR_MALLOC)
		// return (free_print_returnint(current_path, ERROR_MALLOC));
	{
		free(current_path);
		return (ERROR_MALLOC);
	}
	else if (ft_return_value(win, cmd) == ERROR_FILE_DIRECTORY)
		// return (free_print_returnint(current_path, ERROR));
	{
		free(current_path);
		return (ERROR);
	}
	else if (ft_return_value(win, cmd) == SUCCESS)
	//	return (free_print_returnint(current_path, SUCCESS));
	{
		free(current_path);
		return (SUCCESS);
	}


	// if (ft_return_value(win, cmd) == 1)
	// {
	// 	free(current_path);
	// 	//g_exit_status = 0;
	// 	return (1); // on est bien sur un success ???
	// }
	if (access(current_path, X_OK) == -1 || chdir(current_path) != 0)
	{
		free(current_path);
		ft_print_error_token(ERROR_SYNTAX, "cd");
		return (0);
	}
	if (ft_suite(current_path, cmd, win) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	g_exit_status = 0;
	return (SUCCESS);
}
