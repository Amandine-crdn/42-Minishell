#include "minishell.h"


static int	ft_isn(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-')
		{
			i++;
			while (s[i])
			{
				if (s[i] == 'n')
					i++;
				else
					return (i);
			}
		}
		else
			return (i);
	}
	return (i);
}

static void	ft_print_multiple_param(char **cmd, int i)
{
	int	space;

	space = 0;
	while (cmd[i])
	{
		if (i == 1)
		{
			if (ft_isn(cmd[i]) == ft_strlen(cmd[i]))
			{
				space = 1;
				i++;
			}
			else
			{
				i = 1;
			}
		}
		if (i > 1 && space == 0)
			printf(" ");
		printf("%s", cmd[i]);
		i++;
	}
	if (space == 0)
		printf("\n");
}


/*static void	ft_print_multiple_param(char **cmd, int i)
{
	while (cmd[i])
	{
		printf("i : %d\n", i);
		if (i > 1)
			printf(" ");
		printf("%s", cmd[i]);
		i++;
	}
	printf("\n");
}*/

int	ft_echo(char **cmd, int i, int y)
{
	if (cmd[1] && ft_strncmp(cmd[1], "-n\0", 3) == 0 && cmd[2])
	{
		while (cmd[i] && ft_strncmp(cmd[i], "-n\0", 3) == 0 && cmd[i + 1])
			i++;
		while (cmd[i])
		{
			if (y > 0)
				printf(" ");
			printf("%s", cmd[i]);
			y++;
			i++;
		}
	}
	else if (cmd[1] && ft_strncmp(cmd[1], "-n\0", 3) == 0)
	{
		g_exit_status = 0;
		return (SUCCESS);
	}
	else if (cmd[1])
		ft_print_multiple_param(cmd, i);
	else
		printf("\n");
	g_exit_status = 0;
	return (SUCCESS);
}
