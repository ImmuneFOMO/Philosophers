NAME := philo

FILES := files/philosopher.c files/helpers.c files/output.c
OFILES := $(FILES:.c=.o)

CFLAGS := -Wall -Wextra -Werror -pthread
CC := cc

all: $(NAME)

$(NAME):$(OFILES)
	@$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re, fclean, clean, all
