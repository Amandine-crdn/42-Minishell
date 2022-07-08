#include "minishell.h"

void	handle_signal(int sig)
{
	g_exit_status = 130;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
