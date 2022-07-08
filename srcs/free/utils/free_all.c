#include "minishell.h"

void	ft_free_tab(char **tab, int size)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (i < size)
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
	}
}

void	ft_free_cmd_tab(t_cmd *cmd_tab)
{
	int	i;
	int	j;

	i = 0;
	if (cmd_tab)
	{
		while (cmd_tab[i].cmd_param)
		{
			j = 0;
			while (cmd_tab[i].cmd_param[j])
			{
				free(cmd_tab[i].cmd_param[j]);
				j++;
			}
			free(cmd_tab[i].cmd_param);
			i++;
		}
		free(cmd_tab);
	}
}

void	ft_free_double_tab(t_cmd *cmd_tab, char **tab, int size, int status)
{
	ft_free_cmd_tab(cmd_tab);
	ft_free_tab(tab, size);
	if (status == 1)
		g_exit_status = 127;
}

void	ft_free_two_str(char *s, char *s2)
{
	free(s);
	free(s2);
}
