NAME = philo
LIBRARY = philosophers.h
CFLAGS= -Wall -Wextra -Werror
CC = cc

RED     =   \033[38;5;161m
GREEN   =   \033[38;5;154m
YELLOW  =   \033[38;5;227m
BLUE	=   \033[38;5;81m
PURPLE  =   \033[38;5;93m
PINK	=	\033[38;5;219m
NC      =   \033[0m

SRC = philo.c parseargs.c utils.c

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))
DIR_O = temp

all: temp $(NAME)

$(NAME): $(OBJS) $(LIBRARY) Makefile $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) #-fsanitize="thread" -g
	@printf "${PURPLE}== PHILO COMPILED SUCCESSFULLY ==\n${NC}"
	
# temp:
# 	@mkdir -p temp

# $(DIR_O)/%.o: %.c $(NAME).h $(LIBRARY)
# 	$(C) -I $(HEADERS) -c -o $@ $<

clean:
	@rm -f $(OBJS)
	# @rm -rf $(DIR_O)

fclean: clean
	@printf "${RED}....EXTERMINATING....\n${NC}"
	@rm -f $(NAME)
	@sleep 0.5
	@printf "${PINK}\PHILO🔫\n${NC}"
	@sleep 0.5
	@printf "${RED}.......DONE.......\n${NC}"

re: fclean all

.PHONY: all clean fclean re