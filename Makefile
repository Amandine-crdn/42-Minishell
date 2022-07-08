
NAME	=	minishell

CC		=	gcc #clang

FLAG	=	-Wall -Wextra -Werror -g3 -g

SRC	=	main.c \
		parsing.c \
		utils_str_with_malloc.c \
		utils_str_without_malloc.c \
		builtin_env.c \
		builtin_pwd.c \
		builtin_cd.c \
		builtin_exit.c \
		builtin_echo.c \
		quit.c \
		free.c \
		utils/free_all.c \
		utils/free_char.c \
		check_path.c \
		ft_split_path.c \
		init.c	\
		split_init.c \
		signal.c \
		utils_split_init_malloc.c \
		utils_split_init.c \
		utils_split_path.c \
		utils_export.c \
		builtin_export.c \
		builtin_unset.c \
		exec_pipe.c \
		wait.c \
		save.c \
		utils_status.c \
		utils_exec.c \
		utils_heredoc.c \
		utils_copy_env.c \
		utils_init.c \
		setup_exec.c \
		cd/utils_cd.c \
		cd/utils_home.c \
		cd/utils_return.c \
		cd/utils_previous.c \
		cd/initialization_cd.c \
		cd/utils_racine.c \
		cd/utils_check_cd.c \
		cd/utils_cpp.c \
		cd/next_builtin_cd.c

OBJ		= $(SRC:%.c= obj/%.o)
DIR_OBJ	= cd utils
DIR_OBJ := $(addprefix ./obj/, $(DIR_OBJ:%=%)) ./obj

.PHONY:all
all:	$(NAME)

$(DIR_OBJ):
	@mkdir -p $@

./obj/%.o:./srcs/%.c
	@$(CC) $(FLAG) -Iincludes -o $@ -c $<

./obj/%.o:./srcs/builtin/%.c
	@$(CC) $(FLAG) -Iincludes -o $@ -c $<

./obj/%.o:./srcs/utils/%.c
	@$(CC) $(FLAG) -Iincludes -o $@ -c $<

./obj/%.o:./srcs/free/%.c
	@$(CC) $(FLAG) -Iincludes -o $@ -c $<

$(NAME): $(DIR_OBJ) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) -lreadline 

.PHONY: clean
clean:
	@rm -rf ./obj/
	@echo "OBJS deleted"

.PHONY: fclean
fclean:	clean
	@rm -rf $(NAME)
	@echo "$(NAME) deleted"

.PHONY: re
re:	fclean all

.PHONY: leak
leak:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignorereadline ./${NAME}
# si on veut rajouter les leaks de fd    --track-fds=yes
