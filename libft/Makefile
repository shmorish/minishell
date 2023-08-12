NAME          = libft.a

CC            = cc
CFLAGS        = -Wall -Wextra -Werror

INCLUDE       = 'libft.h'

CTYPE_SRC     = ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_isdouble.c \
				ft_isint.c \
				ft_isstrspace.c \

LIST_SRC      = ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c

STDIO_SRC     = ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c
				  
STDLIB_SRC    = ft_abs.c \
				ft_atoi.c \
				ft_atol.c \
				ft_atoll.c \
				ft_calloc.c \
				ft_itoa.c \
				ft_atof.c \
				ft_strtol.c

STRING_SRC    = ft_bzero.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_split.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strdup.c \
				ft_striteri.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c

CTYPE_PATH    = ctype
CTYPE_SRCS	  = $(addprefix $(CTYPE_PATH)/, $(CTYPE_SRC))

LIST_PATH     = list
LIST_SRCS	  = $(addprefix $(LIST_PATH)/, $(LIST_SRC))

STDIO_PATH    = stdio
STDIO_SRCS	  = $(addprefix $(STDIO_PATH)/, $(STDIO_SRC))

STDLIB_PATH   = stdlib
STDLIB_SRCS	  = $(addprefix $(STDLIB_PATH)/, $(STDLIB_SRC))

STRING_PATH   = string
STRING_SRCS	  = $(addprefix $(STRING_PATH)/, $(STRING_SRC))

PRINTF_PATH   = stdio/ft_printf
PRINTF        = libftprintf.a

SRCS          = $(CTYPE_SRCS) \
				$(LIST_SRCS) \
				$(STDIO_SRCS) \
				$(STDLIB_SRCS) \
				$(STRING_SRCS)
OBJS          = $(SRCS:.c=.o)

CHECK         = \033[32m[✔]\033[0m
REMOVE        = \033[31m[✘]\033[0m
BLUE          = \033[1;34m
RESET         = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@ make -C $(PRINTF_PATH)
	@ mv $(PRINTF_PATH)/$(PRINTF) ./$(NAME)
	@ ar rc $(NAME) $(OBJS)
	@echo "$(CHECK) $(BLUE)Compiling libft...$(RESET)"

# for Mac
.c.o: $(OBJS)
	@ $(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

# for Ubuntu
#  %.o: %.c $(INCLUDE)
# 	@ $(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	@ make clean -C $(PRINTF_PATH)
	@ $(RM) $(OBJS)
	@echo "$(REMOVE) $(BLUE)Remove libft object files... $(RESET)"

fclean: clean
	@ $(RM) $(NAME)
	@ make fclean -C $(PRINTF_PATH)
	@echo "$(REMOVE) $(BLUE)Remove $(NAME)$(RESET)"

re: fclean all

.PHONY: bonus clean fclean re all