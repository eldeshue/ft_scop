# result file name
NAME = libftmath.a

# compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = -src

SRCS = ftmf4_init.c ftmf4_init2.c ftmf4_qoperate.c ftmf4_qoperate2.c \
		ftmf4_voperate.c ftmf4_voperate2.c ftmf44_init.c ftmf44_init2.c\
		ftmf44_operate.c ftmf44_transform.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
