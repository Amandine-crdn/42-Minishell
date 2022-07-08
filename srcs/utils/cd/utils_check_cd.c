#include "minishell.h"

int	count_word(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (cmd[0] == '/' && cmd[i + 1] == 0)
		return (1);
	while (cmd && cmd[i])
	{
		if (cmd && i == 0 && cmd[i] == '/')
			i++;
		else if ((cmd[i] == '/') || ((i == ft_strlen(cmd) - 1) && cmd[ft_strlen(cmd) - 1] != '/'))
			count++;
		if (cmd[i] == 0)
			break ;
		i++;
	}
	return (count);
}

int	*creation_malloc(char *cmd)
{
	int	j;
	int	len;
	int	i;
	int	a;
	int	memory;
	int	*value_cmd_path;
	
	a = 0;
	i = 0;
	j = 0;
	memory = 0;
	value_cmd_path = NULL;
	len = ft_strlen(cmd);
	value_cmd_path = malloc(sizeof(int *) * (count_word(cmd)));
	if (!value_cmd_path)
		return (NULL);
	while (cmd && cmd[i])
	{
		if (i == 0 && cmd[0] == '/' && cmd[1] != 0)
		{
			i++;
			len -= 1;
			a = 1;
		}
		if (cmd[i] != '/')
		{
			i++;
			j++;
		}
		if ((cmd[i] == '/') || ((i == len) && cmd[len] != '/'))
		{
			if (i == len && cmd[len] != '/' && a == 1)
				j++;
			value_cmd_path[memory] = j;
	 		memory++;
	 		j = 0;
			if (cmd[i] == 0)
				break ;
			i++;
		}
	}
	return (value_cmd_path);
}

char	**creation_tab(char *cmd, int *value_cmd_path)
{
	char	**cmd_path = NULL;
	int		i = 0;
	int		size = 0;
	int		j;

	cmd_path = malloc(sizeof(char *) * (count_word(cmd) + 1));
	if (!cmd_path)
		return (NULL);
	while (cmd && cmd[i])
	{
		if (i == 0 && cmd[i] == '/' && cmd[1] != 0)
			i++;
		j = 0;
		cmd_path[size] = malloc(sizeof(char) * value_cmd_path[size] + 1);
		if (!cmd_path[size])
		{
			free(cmd_path);
			return (NULL);
		}
		while (cmd[i] && cmd[i] != '/' && j < value_cmd_path[size])
		{
			cmd_path[size][j] = cmd[i];
			j++;
			i++;
		}
		cmd_path[size][j] = 0;
		size++;
		if (cmd[i] == 0)
			break ;
		i++;
	}
	cmd_path[size] = NULL;
	return (cmd_path);
}
