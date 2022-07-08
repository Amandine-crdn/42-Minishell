#include "minishell.h"

int	ft_print_error_token(int err, char *token)
{
	if (err == ERROR_SYNTAX)
		printf("%s : syntax error\n", token);
	else if (err == ERROR_COMMAND)
		printf("%s: command not found\n", token);
	else if (err == PB_OPEN)
		printf("Error open\n");
	else if (err == ERROR_FILE_DIRECTORY)
		printf("%s: no such file or directory\n", token);
	else if (err == ERROR_MALLOC)
		printf("Malloc error\n");
	else if (err == ERROR_MALLOC_MAIN)
	{
		printf("Malloc error\n");
		g_exit_status = 127;
	}
	else if (err == ERROR_PIPE)
		printf("Pipe error\n");
	else if (err == ERROR_FORK)
		printf("Fork error\n");
	else if (err == ERROR)
		printf("Error\n");
	else if (err == END_MINISHELL)
		printf("Error : error nb arguments\n");
	return (err);
}
