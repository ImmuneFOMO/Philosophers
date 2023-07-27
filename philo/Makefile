NAME := philo

FILES := files/philosopher.c
OFILES := $(FILES:.c=.o)

CFLAGS := -Wall -Wextra -Werror
CC := cc

all: $(NAME)

$(NAME):$(OFILES)
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.phony: re, fclean, clean, all
