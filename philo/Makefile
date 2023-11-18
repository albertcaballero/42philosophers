NAME = philo
LIBRARY = philosophers.h
# CFLAGS= -Wall -Wextra -Werror
CC = cc

RED     =   \033[38;5;161m
GREEN   =   \033[38;5;154m
YELLOW  =   \033[38;5;227m
BLUE	=   \033[38;5;81m
PURPLE  =   \033[38;5;93m
PINK	=	\033[38;5;219m
NC      =   \033[0m

SRC = philo.c initargs.c utils.c checks.c actions.c parseargs.c
HEADERS = includes
DIR_O = temp

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: temp $(NAME)

$(NAME): $(LIBRARY) Makefile $(SRC) $(OBJS)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) #-fsanitize="thread" -g
	@printf "${PURPLE}== PHILO COMPILED SUCCESSFULLY ==\n${NC}"
	
temp:
	@mkdir -p temp

$(DIR_O)/%.o: %.c $(LIBRARY)
	$(CC) -I $(LIBRARY) -c -o $@ $<

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@printf "${RED}....EXTERMINATING....\n${NC}"
	@rm -f $(NAME)
	@sleep 0.5
	@printf "${PINK}PHILO X/ \n${NC}"
	@sleep 0.5
	@printf "${RED}.......DONE.......\n${NC}"

re: fclean all

.PHONY: all clean fclean re