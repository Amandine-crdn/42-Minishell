#include "minishell.h"

static char	*check_path_exist_split_suite(char *word, char *tab, t_split *split)
{
	int i;
	i = 0;
	if (split->spe != 0)
	{
		while (tab[i] && tab[i] != split->fixe)
			i++;
		word = malloc(sizeof(char) * (i + 1));
		i = 0;
		while (tab[i] && tab[i] != split->fixe)
		{
			word[i] = tab[i];
			i++;
		}
		word[i] = 0;
	}
	else
		word = ft_strdup(tab);
	return (word);
}

char	*check_path_exist_split(char **env, char *tab, t_win *win, t_split *split)
{
	int		i;
	char	*word;
	char	*temp;

	i = 0;
	word = NULL;
	temp = NULL;
	word = check_path_exist_split_suite(word, tab, split);
	if (!word)
		return (ft_err_malloc(win, word));
	while (env[i] && ft_strnstr_check(env[i], word, ft_strlen(word)) == NULL)
		i++;
	if (env[i] != NULL)
	{
		temp = strdup(env[i]);
		if (!temp)
			return (ft_err_malloc(win, word));
	}	
	free(word);
	return (temp);
}
