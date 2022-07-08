#include "minishell.h"

char	*ft_check_variable_path(t_split *split)
{
	int		y;
	int		i;
	char	*temp;
	int 	diff2;

	temp = NULL;
	diff2 = count_malloc(split);
	temp = malloc(sizeof(char) * (diff2 + 1));
	if (!temp)
		return (NULL);
	y = 0;
	i = split->temp + 1;
	while (split->s && split->s[i] != 0 && split->s[i] != ' ')
	{
		temp[y++] = split->s[i++];
		if (split->s[i] == '$')
			break;
	}
	temp[y] = 0;
	return (temp);
}

static int check_dollar_next(t_split *split, int i, char *check_str)
{
	int		len;
	int		c;

	split->new_str = NULL;
	split->new_str = ft_transform_path(check_str);
	if (!split->new_str)
		return (ERROR_MALLOC);
	c = 0;
	len = ft_strlen(split->new_str);
	while (c < len)
	{
		if (i == 0)
		{
			split->i++;
			c++;
		}
		else
			split->new[split->j][split->i++] = split->new_str[c++];
	}
	free(split->new_str);
	return (SUCCESS);
}

static int	check_dollar_2(t_split *split)
{
	int		c;
	
	c = 0;
	if (split->fixe != 0 && (split->s[split->temp + 1] == '\'' || split->s[split->temp + 1] == '"'))
		return (SUCCESS);
	split->path = NULL;
	split->path = ft_check_variable_path(split);
	if (split->path == NULL)
		return (ERROR_MALLOC);
	if (ft_strlen(split->path) == 1 && split->path[0] == '?')
		return (SUCCESS);
	while (c <= ft_strlen(split->path))
	{
		split->temp++;
		c++;
	}
	return (SUCCESS);
}

static int	check_dollar(t_split *split, t_win *win, int i)
{
	int		check;
	char	*check_str;

	check = SUCCESS;
	check_str = NULL;
	if (check_dollar_2(split) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	check_str = check_path_exist_split(win->env, split->path, win, split);
	if (check_str != NULL)
	{
		check = check_dollar_next(split, i, check_str);	
		if (check == ERROR_MALLOC)
			return (ft_free_null_int(check_str, split->path, ERROR_MALLOC));
	}
	/*else // je ne comprends pas du tout cette ligne, comment se fait-il qu'avec echo "$" ca rentre dedans alors que winerr n'est pas egale a error malloc ?? 
	{
		if (win->err_malloc == ERROR_MALLOC)
		{
			puts("ici");
			return (ft_free_null_int(check_str, split->path, ERROR_MALLOC));
		}
	}*/
	return (ft_free_null_int(check_str, split->path, SUCCESS));
}

int	check_symbol(t_split *split, t_win *win, int i)
{
	if (split->s[split->temp] == '"' && split->fixe == 0)
		split->fixe = '"';
	else if (split->s[split->temp] == '\'' && split->fixe == 0)
		split->fixe = '\'';
	while (split->s[split->temp] == split->fixe)
	{
		split->temp++;
		split->spe++;
	}
	// echo "$" ou echo $
	if (split->s[split->temp] == '$' && ((split->s[split->temp + 1] == 0) || (split->fixe != 0 && split->s[split->temp + 1] == split->fixe)))
			return (SUCCESS);
	// echo "$?" ou echo $?
	if (split->s[split->temp] == '$' && split->s[split->temp + 1] == '?' && ((split->s[split->temp + 2] == 0) || (split->fixe != 0 && split->s[split->temp + 2] == split->fixe)       ))
			return (SUCCESS);

	if (split->s[split->temp] == '$' && split->s[split->temp + 1] == '=')
			return (SUCCESS);
	while (split->s[split->temp] == '$')
	{
		if (check_dollar(split, win, i) != SUCCESS)
			return (ERROR_MALLOC);
	}
	return (SUCCESS);
}
