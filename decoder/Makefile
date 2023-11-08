NAME = decoder

CC = cc
INCLUDE = -I ./include/
CFLAGS = -g $(INCLUDE) -Wall -Werror -Wextra 

RM = rm -rf

PATH_SRC = ./src/


PATH_OBJS = ./objs/

SRC =	$(PATH_SRC)main.c

OBJS = $(patsubst $(PATH_SRC)%.c, $(PATH_OBJS)%.o, $(SRC))

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)


$(PATH_OBJS)%.o:    $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)main/
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) ./objs

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all $(PATH_OBJS) clean fclean re