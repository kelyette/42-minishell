.DEFAULT_GOAL := all

NAME = builtins

SOURCE = No_copy_main.c\
		No_copy_envp.c No_copy_envp_helper_1.c No_copy_envp_helper_2.c\
		No_copy_exit_code_handler.c\
		No_copy_libft.c\
		builtins_echo_pwd_env.c builtins_export.c\
		builtins_export_helper.c builtins_unset.c builtins_exit.c builtins_cd.c builtins_cd_helper.c\


OBJ_DIR = obj

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))

GCC = gcc
FLAGS = -Wextra -Wall -Werror
# FLAGS =
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