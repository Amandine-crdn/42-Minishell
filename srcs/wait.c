#include "minishell.h"

int	ft_wait(int count_pipe, t_cmd *cmd_tab)
{
	int	i;
	int	pid;
	int	status;

	i = 0;
	pid = 0;
	status = 0;
	while (i <= count_pipe)
	{
		pid = waitpid(0, &status, 0);
		if (pid == -1)
			return (ERROR);
		else if (pid == cmd_tab->pid)
			attribute_exit_status(status);
		if (cmd_tab[i].outfile >= 0)
			close(cmd_tab[i].outfile);
		if (cmd_tab[i].infile >= 0)
			close(cmd_tab[i].infile);
		i++;
	}
	return (SUCCESS);
}
