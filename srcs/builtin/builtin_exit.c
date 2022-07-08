#include "minishell.h"

int	ft_exit(char **cmd)
{
	if (!cmd[1])
	{
		g_exit_status = 0;
		return (EXIT);
	}
	ft_print_error_token(ERROR, "exit");
	return (ERROR);
}
