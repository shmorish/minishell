NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g

SRC_PATH	= srcs
SRC			= main.c select_commands.c ft_exit.c ft_echo.c ft_pwd.c ft_cd.c ft_env.c ft_export.c ft_unset.c \
		ft_env_node_utils.c ft_env_init.c ft_print_utils.c ft_is_number_str.c ft_free.c \
		ft_strcmp.c ft_get_list_size.c
SRCS		= $(addprefix $(SRC_PATH)/, $(SRC))

OBJ_PATH	= obj
OBJ 		= $(SRC:.c=.o)
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

$(NAME) : $(OBJS)
	@ make -C $(LIB_PATH)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) -lreadline
	@echo "$(CHECK) $(BLUE)Compiling minishell... $(RESET)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCS)
	@ mkdir -p $(OBJ_PATH)
	@ $(CC) $(CFLAGS) -o $@ -c $< -I ./includes/

clean:
	@ make clean -C $(LIB_PATH)
	@ $(RM) $(OBJS)
	@ $(RM) -r $(OBJ_PATH)
	@echo "$(REMOVE) $(BLUE)Remove minishell objects... $(RESET)"

fclean: clean
	@ make fclean -C $(LIB_PATH)
	@ $(RM) $(NAME)
	@echo "$(REMOVE) $(BLUE)Remove minishell... $(RESET)"

re: fclean all

.PHONY : all clean fclean re