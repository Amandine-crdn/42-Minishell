#include "minishell.h"

static int	ft_count_char_malloc(char *s, int compteur)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (count < compteur && s[i])
	{
		if (s[i] == '/')
		{
			count++;
			if (count == compteur)
				break ;
		}
		i++;
	}
	return (i);
}

static char	*ft_newpwd(int compteur, char *str)
{
	char	*new;
	int		j;
	int		i;
	int		len;

	i = 0;
	new = NULL;
	len = ft_count_char_malloc(str, compteur);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (free_errormalloc_return_null(new));
	j = 4;
	while (j < len)
	{
		new[i] = str[j];
		j++;
		i++;
	}
	new[i] = 0;
	return (new);
}

int	ft_previous(t_win *win, int compteur)
{
	int		i;
	char	*res;
	char	*new_pwd;

	i = 0;
	new_pwd = NULL;
	res = NULL;
	while (win->env[i])
	{
		if (ft_strnstr(win->env[i], "PWD=", 4))
		{
			res = ft_newpwd(compteur, win->env[i]);
			if (res == NULL)
				return (ERROR_MALLOC);
			new_pwd = ft_replace(win, res, "PWD=");
			if (new_pwd == NULL)
				return (ERROR_MALLOC);
			free(new_pwd);
		}
		i++;
	}
	free(res);
	return (SUCCESS);
}
