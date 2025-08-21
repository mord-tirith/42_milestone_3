#######################
#        ▘  ▌ ▜       #
#  ▌▌▀▌▛▘▌▀▌▛▌▐ █▌▛▘  #
#  ▚▘█▌▌ ▌█▌▙▌▐▖▙▖▄▌  #
#######################

# Basic Variables:
NAME		= philosophers
PNAME		= Philosophers
INC_DIR	= inc/
SRC_DIR	= src/
OBJ_DIR	= .obj/

# File Variables:
SRC_FILES	= cleaner.c error.c looper.c philo.c routine.c sim.c utils.c
SRC				= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ				:= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# Compiler Variables:
CC			= cc
CFLAGS	= -Wall -Wextra -Werror -g

# Valgrind Variables:
VAL_OUT	= allgrind.log
VAL_RUN = ./philosophers 3 800 200 200 3

# Makefile Variables:
MAKEFLAGS += --no-print-directory
STAMP			=	$(OBJ_DIR).build-stamp

####################
#      ▜   ▗ ▗     #
#  ▛▌▀▌▐ █▌▜▘▜▘█▌  #
#  ▙▌█▌▐▖▙▖▐▖▐▖▙▖  #
#  ▌               #
####################

CYAN		:= $(shell tput setaf 87)
BLUE		:= $(shell tput setaf 111)
RED			:= $(shell tput setaf 160)
PINK		:= $(shell tput setaf 200)
YELLOW	:= $(shell tput setaf 220)
RESET		:= $(shell tput sgr0)

################
#      ▜       #
#  ▛▘▌▌▐ █▌▛▘  #
#  ▌ ▙▌▐▖▙▖▄▌  #
################

.PHONY: all clean fclean re clean_install banner q norm valgrind

all: $(NAME)
	@if test -e $(STAMP) && test $(STAMP) -nt $(NAME); then \
		echo "${BLUE}${PNAME} already up to date${RESET}"; \
	fi
	@touch $(STAMP)

$(NAME): $(OBJ)
	@make banner
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "${BLUE}${PNAME} installed${RESET}"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	@if test -e $(OBJ_DIR); then \
		rm -rf $(OBJ_DIR); \
		echo "${YELLOW}.o files removed${RESET}"; \
	else \
		echo "${RED}Error: no .o files to remove${RESET}"; \
	fi

fclean: clean
	@if test -e $(NAME); then \
		rm -f $(NAME) $(VAL_OUT); \
		echo "${YELLOW}${PNAME} uninstalled${RESET}"; \
	else \
		echo "${RED}Error: ${PNAME} isn't currently installed${RESET}"; \
	fi

re: fclean all

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

banner:
	@echo "${PINK}▓     ▓▓  ▓▓▓  ▓    ▓  ▓▓▓▓▓     ▓▓";
	@echo "▒  ▒▒  ▒  ▒▒▒  ▒▒  ▒▒  ▒▒▒▒  ▒▒▒  ▒";
	@echo "░     ░░       ░░  ░░  ░░░░  ░░░  ░";
	@echo "▒  ▒▒▒▒▒  ▒▒▒  ▒▒  ▒▒  ▒▒▒▒  ▒▒▒  ▒";
	@echo "▓  ▓▓▓▓▓  ▓▓▓  ▓    ▓     ▓▓     ▓▓";
	@echo "                        ${CYAN}by thenriqu${RESET}";
