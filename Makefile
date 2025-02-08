RED			= \033[0;31m
CYAN		= \033[0;36m
GREEN		= \033[0;32m
YELLOW	= \033[0;33m
WHITE		= \033[0;37m


NAME		= minishell
CC			= cc
CFLAGS	= -Wall -Wextra -Werror
INC			= -I inc/ -I lib/libft
LIBFT		= -L lib/libft -lft
READL		= -lreadline
RM			= rm -rf

SRCPATH	= src/
SRC = main.c \
	parsing/lexer/manipulate_input.c parsing/lexer/init_src_token.c parsing/lexer/manipulate_token.c parsing/lexer/manipulate_token2.c parsing/lexer/manipulate_token3.c parsing/lexer/manipulate_token4.c parsing/lexer/manipulate_token5.c \
	parsing/parser/parser.c parsing/parser/ft_pipe.c parsing/parser/quotes.c parsing/parser/quotes_2.c parsing/parser/in_out.c parsing/parser/in_out2.c parsing/parser/in_out3.c parsing/parser/manip_env.c parsing/parser/manip_env2.c \
	parsing/parser/manip_env3.c parsing/parser/manip_env4.c parsing/parser/manip_env5.c parsing/parser/manip_env6.c parsing/parser/manip_env7.c parsing/parser/manip_env8.c parsing/parser/manip_env9.c parsing/parser/manip_env10.c \
	parsing/parser/manip_env11.c parsing/parser/decoupe_ast_no_quotes.c parsing/parser/decoupe_ast_no_quotes2.c parsing/parser/final_ast.c parsing/parser/manip_node_commannd.c parsing/parser/manip_node_redir.c parsing/parser/manip_node_redir2.c \
	parsing/parser/manip_node_redir3.c parsing/parser/exception.c parsing/parser/supp_quotes.c \
	signals/signal.c builtin/export_with_option.c builtin/ft_unset.c builtin/ft_unset2.c builtin/update_cmd.c ft_free/ft_free.c ft_free/ft_free_2.c ft_free/ft_free_3.c error_pars.c error_pars2.c exe/print_exec.c exe/print_exec_utils.c\
	exe/redir.c exe/redir_utils.c exe/heredoc.c exe/heredoc_expand.c exe/heredoc_utils.c exe/heredoc_utils_2.c exe/pipex.c exe/pipex_init.c exe/pipex_lonely.c exe/pipex_errors.c exe/exec.c exe/childs.c exe/cmd_access.c exe/free_exe.c exe/print_status.c \
	exe/builtin.c exe/builtin_cd.c exe/builtin_cd_utils.c exe/builtin_echo.c exe/builtin_env.c exe/builtin_exit.c exe/builtin_export.c exe/builtin_export=.c exe/builtin_pwd.c exe/utils.c exe/utils_2.c exe/utils_3.c prompt_name.c prompt_name_utils.c print_errors.c

all: $(NAME)

OBJDIR	= .config/obj/
OBJ			= $(addprefix $(OBJDIR), $(SRC:.c=.o))

DEPDIR	= .config/dep/
DEP			= $(addprefix $(DEPDIR), $(SRC:.c=.d))

$(NAME): $(OBJ)
		@echo "$(CYAN)Linking $(NAME)...$(WHITE)"
		@$(MAKE) --no-print-directory -C lib/libft
		@$(CC) $(CFLAGS) $(OBJ) $(READL) $(LIBFT) -o $(NAME)
		@echo "$(GREEN)Done$(WHITE)"

$(OBJDIR)%.o: $(SRCPATH)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DEPDIR)%.d: $(SRCPATH)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(INC) -MM $< -MT $(@:.d=.o) -MF $@ -MP

-include $(DEP)

clean:
		@echo "$(RED)Cleaning $(NAME)...$(WHITE)"
		@$(MAKE) --no-print-directory fclean -C lib/libft
		@$(RM) .config
		@echo "$(GREEN)Done$(WHITE)"

fclean: clean
		@$(RM) $(NAME)

re: fclean all

norm:
	@echo "$(YELLOW)Executing norminette...$(WHITE)"
	@norminette

.PHONY : all clean fclean re norm