#include "minishell.h"

int	ft_check_own_builtin(char *cmd)
{
	if (cmd == NULL)
		return (NO_BUILTIN);
	if (ft_strncmp(cmd, "exit\0", 5) == 0 || ft_strncmp(cmd, "export\0", 7) == 0 \
		|| ft_strncmp(cmd, "env\0", 4) == 0 || ft_strncmp(cmd, "unset\0", 6) == 0 \
			|| ft_strncmp(cmd, "pwd\0", 4) == 0 || ft_strncmp(cmd, "cd\0", 3) \
				== 0 || ft_strncmp(cmd, "echo\0", 5) == 0)
		return (SUCCESS);
	return (NO_BUILTIN);
}

int	ft_parse_cmd(t_win *win, char **cmd)
{
	if (ft_strncmp(cmd[0], "exit\0", 5) == 0)
		return (ft_exit(cmd));
	else if (ft_strncmp(cmd[0], "export\0", 7) == 0)
		return (ft_export_env(win, cmd));
	else if (ft_strncmp(cmd[0], "env\0", 4) == 0)
		ft_print_env(win, cmd);
	else if (ft_strncmp(cmd[0], "unset\0", 6) == 0)
		return (ft_unset(win, cmd));
	else if (ft_strncmp(cmd[0], "pwd\0", 4) == 0)
		return (ft_pwd(win, cmd));
	else if (ft_strncmp(cmd[0], "cd\0", 2) == 0)
		return (ft_check_cd(win, cmd));
	else if (ft_strncmp(cmd[0], "echo\0", 4) == 0)
		ft_echo(cmd, 1, 0);
	return (0);
}
