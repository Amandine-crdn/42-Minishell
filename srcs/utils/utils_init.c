#include "minishell.h"

void	ft_init_val(t_win *win)
{
	win->i = 0;
	win->tmp = NULL;
	win->res = NULL;
	win->tmp_old = NULL;
	win->copy = NULL;
}

void	ft_init_val_cmd(t_cmd *cmd)
{
	cmd->i = 0;
	cmd->j = 0;
	cmd->res = 0;
	cmd->cmd_nb = 0;
}
