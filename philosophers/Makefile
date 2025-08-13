#######################
#        ▘  ▌ ▜       #
#  ▌▌▀▌▛▘▌▀▌▛▌▐ █▌▛▘  #
#  ▚▘█▌▌ ▌█▌▙▌▐▖▙▖▄▌  #
#######################

#	Basic Variables:
NAME		= philosophers
PNAME		= Philosophers
SRC_DIR	= philo/
OBJ_DIR	= .philo_obj/

# File Variables:
SRC_FILES	= cleaner.c error.c looper.c main.c routine.c setting.c utils.c
SRC				= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				:= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
VAL_OUT		= allgrind_log

# Compiler Variables:
CC			= cc
CFLAGS	= -Wall -Wextra -Werror -g

# Makefile Variables:
MAKEFLAGS	+= --no-print-directory

# Misc Variables:
VAL_RUN	= ./philosophers 5 800 100 100 7

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
YELLOW	:= $(shell tput setaf 220)
RESET		:= $(shell tput sgr0)

################
#      ▜       #
#  ▛▘▌▌▐ █▌▛▘  #
#  ▌ ▙▌▐▖▙▖▄▌  #
################

.PHONY: all true_all clean fclean re clean_install banner q norm valgrind

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
		rm -f $(VAL_OUT); \
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

valgrind:
	@if [ ! -f "$(NAME)" ]; then \
		$(MAKE) q; \
	fi
	@if [ -f "$(VAL_OUT)" ]; then \
		rm -f $(VAL_OUT); \
	fi
	@echo "${YELLOW}Running Valgrind tools with input $(VAL_RUN)${RESET}"
	@echo	"=============================================" >> $(VAL_OUT)
	@echo	" Running Basic Valgrind:" >> $(VAL_OUT)
	@echo	"=============================================" >> $(VAL_OUT)
	@valgrind --leak-check=full --show-leak-kinds=all $(VAL_RUN) 1>> /dev/null 2>> $(VAL_OUT)
	@echo	"${YELLOW}Finished basic Valgrind${RESET}"
	@echo	"=============================================" >> $(VAL_OUT)
	@echo	" Running Helgrind Tool of Valgrind:" >> $(VAL_OUT)
	@echo	"=============================================" >> $(VAL_OUT)
	@valgrind --tool=helgrind $(VAL_RUN) 1>> /dev/null 2>> $(VAL_OUT)
	@echo "${YELLOW}Finished Helgrind${RESET}"
	@echo	"=============================================" >> $(VAL_OUT)
	@echo	" Running DRD Tool of Valgrind:" >> $(VAL_OUT)
	@echo	"=============================================" >> $(VAL_OUT)
	@valgrind --tool=drd $(VAL_RUN) 1>> /dev/null 2>> $(VAL_OUT)
	@echo	"${YELLOW}Finished DRD${RESET}"
	@echo "${BLUE}Valgrind ran on project, output saved to $(VAL_OUT)${RESET}"

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
