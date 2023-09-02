NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer -g
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
BUILDIN_OBJ_PATH	= obj_buildin
BUILDIN_OBJ 		= $(BUILDIN:%.c=%.o)
BUILDIN_OBJS		= $(addprefix $(BUILDIN_OBJ_PATH)/, $(BUILDIN_OBJ))

LEXER_PATH= srcs/lexer
LEXER		= expansion_utils.c \
				expansion.c \
				lexer_boolean.c \
				lexer_boolean2.c \
				lexer_node_init.c \
				lexer_node.c \
				lexer_partial.c \
				lexer_print.c \
				lexer.c

LEXERS	= $(addprefix $(LEXER_PATH)/, $(LEXER))

LEXER_OBJ_PATH	= obj_lexer
LEXER_OBJ 		= $(LEXER:%.c=%.o)
LEXER_OBJS		= $(addprefix $(LEXER_OBJ_PATH)/, $(LEXER_OBJ))

PARSER_PATH= srcs/parser
PARSER		= parser.c \
				free_parser.c \

PARSER_OBJ_PATH	= obj_parser
PARSER_OBJ 		= $(PARSER:%.c=%.o)
PARSER_OBJS		= $(addprefix $(PARSER_OBJ_PATH)/, $(PARSER_OBJ))

PARSERS	= $(addprefix $(PARSER_PATH)/, $(PARSER))

SRC_PATH	= srcs
SRC			= ft_get_list_size.c \
				ft_puterr_utils.c \
				ft_puterr_utils2.c \
				handle_quote.c \
				main.c \
				signal.c

SRCS		= $(addprefix $(SRC_PATH)/, $(SRC))

OBJ_PATH	= obj_srcs
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
BLUE		= \033[1;34m
RESET		= \033[0m

all : $(NAME)

$(NAME) : $(OBJS) $(BUILDIN_OBJS) $(LEXER_OBJS) $(PARSER_OBJS)
	@ make -C $(LIB_PATH)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(BUILDIN_OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(LIBS) -lreadline -L $(shell brew --prefix readline)/lib
	@ mkdir -p ./obj
	@ mv $(PARSER_OBJ_PATH) $(LEXER_OBJ_PATH) $(BUILDIN_OBJ_PATH) $(OBJ_PATH) ./obj
	@ echo "$(CHECK) $(BLUE)Compiling minishell... $(RESET)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	@ mkdir -p $(OBJ_PATH)
	@ $(CC) $(CFLAGS) -o $@ -c $< -I $(shell brew --prefix readline)/include

$(BUILDIN_OBJ_PATH)/%.o: $(BUILDIN_PATH)/%.c $(INCS)
	@ mkdir -p $(BUILDIN_OBJ_PATH)
	@ $(CC) $(CFLAGS) -o $@ -c $< -I $(shell brew --prefix readline)/include

$(LEXER_OBJ_PATH)/%.o: $(LEXER_PATH)/%.c $(INCS)
	@ mkdir -p $(LEXER_OBJ_PATH)
	@ $(CC) $(CFLAGS) -o $@ -c $< -I $(shell brew --prefix readline)/include

$(PARSER_OBJ_PATH)/%.o: $(PARSER_PATH)/%.c $(INCS)
	@ mkdir -p $(PARSER_OBJ_PATH)
	@ $(CC) $(CFLAGS) -o $@ -c $< -I $(shell brew --prefix readline)/include

clean:
	@ make clean -C $(LIB_PATH)
	@ $(RM) -r ./obj/
	@ echo "$(REMOVE) $(BLUE)Remove minishell objects... $(RESET)"

fclean: clean
	@ make fclean -C $(LIB_PATH)
	@ $(RM) $(NAME)
	@echo "$(REMOVE) $(BLUE)Remove minishell... $(RESET)"

re: fclean all

run: all
	@ clear
	@ ./$(NAME)

debug: run

.PHONY : all clean fclean re run debug
