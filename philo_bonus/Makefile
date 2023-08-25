NAME := philo_bonus

FILES := files/philosopher_bonus.c files/helpers_bonus.c files/output_bonus.c
OFILES := $(FILES:.c=.o)

CFLAGS := -Wall -Wextra -Werror -pthread #-g -fsanitize=leak# -fsanitize=thread
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
