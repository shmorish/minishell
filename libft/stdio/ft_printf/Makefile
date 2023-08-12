NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

INCLUDE = './ft_printf.h'

SRCS = ft_printf.c \
		ft_format.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putptr.c \
		ft_putnbr.c \
		ft_putunbr.c \
		ft_puthex.c \
		ft_putbinary.c

OBJS = $(SRCS:.c=.o)

CHECK = \033[32m[✔]\033[0m
REMOVE = \033[31m[✘]\033[0m
BLUE = \033[1;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@ ar rc $(NAME) $(OBJS)
	@echo "$(CHECK) $(BLUE)Compiling ft_printf...$(RESET)"


# for Mac
.c.o: $(OBJS)
	@ $(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

# for Ubuntu
# %.o: %.c $(INCLUDE)
# 	@ $(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@

clean:
	@ $(RM) $(OBJS)
	@echo "$(REMOVE) $(BLUE)Remove ft_printf object files... $(RESET)"

fclean: clean
	@ $(RM) $(NAME)
	@echo "$(REMOVE) $(BLUE)Remove $(NAME)$(RESET)"

re: fclean all

.PHONY: clean fclean re all
