.DEFAULT_GOAL := all

NAME = shell

SOURCE = main.c signal.c lexer.c lexer_case_single.c lexer_case_double.c lexer_case_string.c lexer_helper_1.c lexer_helper_2.c\
		envp.c envp_helper_1.c envp_helper_2.c\
		dollar_handler.c dollar_handler_helper.c

OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))

GCC = gcc
# FLAGS = -Wextra -Wall -Werror
FLAGS =
RM = rm -f

all : $(NAME)

$(OBJ_DIR)/%.o:%.c
	@mkdir -p $(OBJ_DIR)
	@$(GCC) $(FLAGS) -I include/ -c $< -o $@

$(NAME):	$(OBJECTS)
	@$(GCC) $(FLAGS) $(OBJECTS) -lreadline -o $(NAME)
	@echo "Built $(NAME)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "Deleted object files"

fclean:		clean
	@$(RM) $(NAME)
	@echo "Deleted $(NAME)"

re: fclean all

.PHONY: all clean fclean re