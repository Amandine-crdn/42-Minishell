#include "minishell.h"

void	set_child_process(t_cmd *cmd_tab, int nbr_cmd, int nb_pipe, int *fd)
{
	close(fd[0]);
	if (cmd_tab[nbr_cmd].infile >= 0)
	{
		dup2(cmd_tab[nbr_cmd].infile, 0);
		close(cmd_tab[nbr_cmd].infile);
	}
	if (cmd_tab[nbr_cmd].outfile >= 0)
	{
		dup2(cmd_tab[nbr_cmd].outfile, 1);
		close(cmd_tab[nbr_cmd].outfile);
	}
	else if (nbr_cmd != nb_pipe)
		dup2(fd[1], 1);
	close(fd[1]);
}

void	set_parent_process(t_cmd *cmd_tab, int nbr_cmd, int nb_pipe, int *fd)
{
	close(fd[1]);
	if (cmd_tab[nbr_cmd].infile >= 0)
		close(cmd_tab[nbr_cmd].infile);
	if (cmd_tab[nbr_cmd].infile == -2)
		cmd_tab[nbr_cmd].infile = fd[0];
	if (nbr_cmd != nb_pipe && cmd_tab[nbr_cmd + 1].infile == -2)
		cmd_tab[nbr_cmd + 1].infile = fd[0];
	else
		close(fd[0]);
}
