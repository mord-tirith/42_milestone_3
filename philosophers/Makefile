#######################
#        ▘  ▌ ▜       #
#  ▌▌▀▌▛▘▌▀▌▛▌▐ █▌▛▘  #
#  ▚▘█▌▌ ▌█▌▙▌▐▖▙▖▄▌  #
#######################

#	Basic Variables:
NAME				= philosophers
PNAME				= Philosophers
SRC_DIR				= philo/
OBJ_DIR				= .philo_obj/

# File Variables:
SRC_FILES	= cleanup.c clock.c day_in_life.c errors.c fill_cave.c minilib.c philosophers.c printer.c
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			:= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# Compiler Variables:
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

# Makefile Variables:
MAKEFLAGS	+= --no-print-directory

####################
#      ▜   ▗ ▗     #
#  ▛▌▀▌▐ █▌▜▘▜▘█▌  #
#  ▙▌█▌▐▖▙▖▐▖▐▖▙▖  #
#  ▌               #
####################

BLUE		:= $(shell tput setaf 111)
RED			:= $(shell tput setaf 160)
PINK		:= $(shell tput setaf 200)
CYAN		:= $(shell tput setaf 87)
YELLOW		:= $(shell tput setaf 220)
RESET		:= $(shell tput sgr0)

################
#      ▜       #
#  ▛▘▌▌▐ █▌▛▘  #
#  ▌ ▙▌▐▖▙▖▄▌  #
################

.PHONY: all true_all clean fclean re clean_install banner q norm

all:
	@if make -q true_all; then \
		echo "${BLUE}${PNAME} already up to date${RESET}"; \
	else \
		make true_all; \
	fi

true_all: $(NAME)

$(NAME): $(OBJ)
	@make banner
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "${BLUE}${PNAME} installed${RESET}"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rfd $(OBJ_DIR); \
		echo "${YELLOW}.o files removed${RESET}"; \
	else \
		echo "${RED}Error: no .o files to remove at this moment${RESET}"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "${YELLOW}Uninstalled ${PNAME}${RESET}"; \
	else \
		echo "${RED}Error: ${PNAME} isn't installed${RESET}"; \
	fi

re: fclean all

clean_install:
	@make all
	@make clean

q: $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "${BLUE}${PNAME} installed${RESET}"

norm:
	norminette ./src
	norminette ./inc

banner:
	@echo "${PINK}░       ░░  ░░░░  ░        ░  ░░░░░░░░      ░░░      ░░░      ░░       ░░  ░░░░  ░        ░       ░░░      ░░";
	@echo "▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒▒▒▒  ▒▒▒▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒  ▒▒▒▒  ▒  ▒▒▒▒▒▒▒";
	@echo "▓       ▓▓        ▓▓▓▓  ▓▓▓▓  ▓▓▓▓▓▓▓  ▓▓▓▓  ▓▓      ▓▓  ▓▓▓▓  ▓       ▓▓        ▓      ▓▓▓       ▓▓▓      ▓▓";
	@echo "█  ███████  ████  ████  ████  ███████  ████  ███████  █  ████  █  ███████  ████  █  ███████  ███  ████████  █";
	@echo "█  ███████  ████  █        █        ██      ███      ███      ██  ███████  ████  █        █  ████  ██      ██";
	@echo "                                                                                                  ${CYAN}by thenriqu${RESET}"
