NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -MMD -MP -g
CFLAGS		+= -I $(shell brew --prefix readline)/include

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer
endif

BUILDIN_PATH= srcs/buildin
BUILDIN		= env_init.c \
				env_list_to_array.c \
				env_node_operate.c \
				env_node_new.c \
				ft_cd.c \
				ft_echo.c \
				ft_env.c \
				ft_exit.c \
				ft_export_utils.c \
				ft_export.c \
				ft_free.c \
				ft_is_number_str.c \
				ft_pwd.c \
				ft_split_once.c \
				ft_strccpy.c \
				ft_unset.c \
				is_long_overflow.c \
				other_commands_utils.c \
				other_commands.c \
				select_commands.c
BUILDINS	= $(addprefix $(BUILDIN_PATH)/, $(BUILDIN))
BUILDIN_OBJ_PATH	= obj/obj_buildin
BUILDIN_OBJ 		= $(BUILDIN:%.c=%.o)
BUILDIN_OBJS		= $(addprefix $(BUILDIN_OBJ_PATH)/, $(BUILDIN_OBJ))

LEXER_PATH= srcs/lexer
LEXER		= expansion_utils.c \
				expansion.c \
				ft_split_charset.c \
				lexer_boolean.c \
				lexer_boolean2.c \
				lexer_node_init.c \
				lexer_node.c \
				lexer_partial.c \
				lexer_print.c \
				lexer.c
LEXERS	= $(addprefix $(LEXER_PATH)/, $(LEXER))
LEXER_OBJ_PATH	= obj/obj_lexer
LEXER_OBJ 		= $(LEXER:%.c=%.o)
LEXER_OBJS		= $(addprefix $(LEXER_OBJ_PATH)/, $(LEXER_OBJ))

PARSER_PATH= srcs/parser
PARSER		= parser.c \
				free_parser.c \
				parser_bool.c \
				parser_cmd_free.c \
				parser_cmd.c \
				parser_node.c \
				parser_pipe.c \
				parser_redirect.c \
				print_parser.c \
				token_evolver.c
PARSERS	= $(addprefix $(PARSER_PATH)/, $(PARSER))
PARSER_OBJ_PATH	= obj/obj_parser
PARSER_OBJ 		= $(PARSER:%.c=%.o)
PARSER_OBJS		= $(addprefix $(PARSER_OBJ_PATH)/, $(PARSER_OBJ))

PIPE_PATH= srcs/pipe
PIPE		= make_pipefd.c \
				close_pipefd.c \
				redirect_input.c \
				redirect_output.c \
				free_pipe.c \
				heredoc_expansion.c \
				heredoc_utils.c \
				heredoc.c \
				pipe_error_exit.c \
				count_process.c
PIPES	= $(addprefix $(PIPE_PATH)/, $(PIPE))
PIPE_OBJ_PATH	= obj/obj_pipe
PIPE_OBJ 		= $(PIPE:%.c=%.o)
PIPE_OBJS		= $(addprefix $(PIPE_OBJ_PATH)/, $(PIPE_OBJ))

SRC_PATH	= srcs
SRC			= ft_puterr_utils.c \
				ft_puterr_utils2.c \
				main.c \
				signal_handler.c \
				signal.c \
				no_pipe_main.c \
				have_pipe_main.c \
				have_pipe_utils.c \

SRCS		= $(addprefix $(SRC_PATH)/, $(SRC))

OBJ_PATH	= obj
OBJ 		= $(SRC:%.c=%.o)
OBJS		= $(addprefix $(OBJ_PATH)/, $(OBJ))

INC_PATH	= includes
INC			= minishell.h
INCS		= $(addprefix $(INC_PATH)/, $(INC))

LIB_PATH	= libft
LIB			= libft.a
LIBS		= $(addprefix $(LIB_PATH)/, $(LIB))

RM			= rm -f

CHECK		= \033[32m[✔]\033[0m
REMOVE		= \033[31m[✘]\033[0m
GENERATE	= \033[33m[➤]\033[0m
BLUE		= \033[1;34m
YELLOW		= \033[1;33m
RESET		= \033[0m

all : $(NAME)

$(NAME) : $(OBJS) $(BUILDIN_OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(PIPE_OBJS)
	@ echo "\n"
	@ make -C $(LIB_PATH)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(BUILDIN_OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(PIPE_OBJS) $(LIBS) -lreadline -L $(shell brew --prefix readline)/lib
	@ mkdir -p ./obj
	@ echo "$(CHECK) $(BLUE)Compiling minishell... $(RESET)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) -o $@ -c $<
	@ printf "$(GENERATE) $(YELLOW)Generating $@... %-50.50s\r$(RESET)"

$(BUILDIN_OBJ_PATH)/%.o: $(BUILDIN_PATH)/%.c $(INCS)
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) -o $@ -c $<
	@ printf "$(GENERATE) $(YELLOW)Generating $@... %-50.50s\r$(RESET)"

$(LEXER_OBJ_PATH)/%.o: $(LEXER_PATH)/%.c $(INCS)
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) -o $@ -c $<
	@ printf "$(GENERATE) $(YELLOW)Generating $@... %-50.50s\r$(RESET)"

$(PARSER_OBJ_PATH)/%.o: $(PARSER_PATH)/%.c $(INCS)
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) -o $@ -c $<
	@ printf "$(GENERATE) $(YELLOW)Generating $@... %-50.50s\r$(RESET)"

$(PIPE_OBJ_PATH)/%.o: $(PIPE_PATH)/%.c $(INCS)
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) -o $@ -c $<
	@ printf "$(GENERATE) $(YELLOW)Generating $@... %-50.50s\r$(RESET)"

clean:
	@ make clean -C $(LIB_PATH)
	@ $(RM) -r ./obj/
	@ printf "$(GENERATE) $(YELLOW)Generating $@... %-50.50s\r$(RESET)"

fclean:
	@ make fclean -C $(LIB_PATH)
	@ $(RM) $(NAME)
	@ $(RM) -r ./obj/
	@ printf "$(GENERATE) $(YELLOW)Generating $@... %-50.50s\r$(RESET)"

re: fclean all

run: all
	@ clear
	@ ./$(NAME)

debug: re run

leak:
	while [ 1 ]; do leaks -q minishell; sleep 2; done

.PHONY : all clean fclean re run debug leak