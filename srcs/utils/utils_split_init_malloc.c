#include "minishell.h"

int		count_malloc(t_split *split)
{
	int i;
	int diff2;

	diff2 = 0;
	i = split->temp + 1;
	while (split->s && split->s[i] != 0 && split->s[i] != ' ')
	{
		diff2++;
		i++;
		if (split->s[i] == '$')
			break;
	}
	return (diff2);
}

int	check_return(t_split *split)
{
	if (split->spe % 2 == 0)
	{
		if (split->s[split->temp] == '<' && split->s[split->temp + 1] == '<')
			return (HEREDOC);
		if (split->s[split->temp] == '>' && split->s[split->temp + 1] == '>')
			return (APPEND);
		if (split->s[split->temp] == '|' || split->s[split->temp + 1] == '|')
			return (SUCCESS);
		if (split->s[split->temp] == '>' || split->s[split->temp + 1] == '>')
			return (SUCCESS);
		if (split->s[split->temp] == '<' || split->s[split->temp + 1] == '<')
			return (SUCCESS);
		if (split->s[split->temp + 1] == '<' && split->s[split->temp + 2] == '<')
			return (SUCCESS);
		if (split->s[split->temp + 1] == '>' && split->s[split->temp + 2] == '>')
			return (SUCCESS);
	}
	return (ERROR);
}

static int	ft_suite(t_split *split, t_win *win)
{
	while (split->s && split->s[split->temp] != 0)
	{
		if (check_symbol(split, win, 0) != SUCCESS)
			return (ERROR_MALLOC);
		if ((split->s[split->temp] == 0) || ((split->spe % 2 == 0) && (split->s[split->temp] == ' ' || split->s[split->temp] == '\t')))
			break ;
		if (check_return(split) == SUCCESS)
		{
			split->i++;
			split->temp++;
			break ;
		}
		if (check_return(split) == APPEND || check_return(split) == HEREDOC)
		{
			split->i += 2;
			split->temp += 2;
			break ;
		}
		split->i++;
		split->temp++;
	}
	return (SUCCESS);
}

int	ft_count_sentence(t_split *split, t_win *win)
{	
	while (split->s && split->s[split->temp] != 0)
	{
		while (split->s && split->s[split->temp] != 0 && (split->s[split->temp] == ' ' || split->s[split->temp] == '\t'))
			split->temp++;
		split->i = 0;
		split->fixe = 0;
		if (ft_suite(split, win) != SUCCESS)
			return (ERROR_MALLOC);
		if (split->i != 0)
			split->j++;
		while (split->s && split->s[split->temp] != 0 && (split->s[split->temp] == ' ' || split->s[split->temp] == '\t'))
			split->temp++;
	}
	return (split->j);
}

int	*ft_hav_tab_len(t_split *split, t_win *win)
{
	int	*temp;

	temp = NULL;
	temp = malloc(sizeof(int) * split->len_sentence);
	if (!temp)
		return (NULL);
	while (split->s[split->temp])
	{
		while (split->s[split->temp] == ' ' || split->s[split->temp] == '\t')
			split->temp++;
		split->i = 0;
		split->fixe = 0;
		if (ft_suite(split, win) != SUCCESS)
			return (ft_free_int_null(temp));
		if (split->i != 0)
			temp[split->j++] = split->i;
		while (split->s && split->s[split->temp] != 0 && (split->s[split->temp] == ' ' || split->s[split->temp] == '\t'))
			split->temp++;
	}	
	return (temp);
}
