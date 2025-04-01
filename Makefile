NAME = philo

SRC_DIR = ./src

OBJ_DIR = ./obj

SRC = $(SRC_DIR)/philo_main.c\
	$(SRC_DIR)/philo_parsing.c\
	$(SRC_DIR)/philo_init.c\
	$(SRC_DIR)/philo_safe_funct.c\
	$(SRC_DIR)/philo_sim.c\
	$(SRC_DIR)/philo_write.c\
	$(SRC_DIR)/philo_sync.c\
	$(SRC_DIR)/philo_utils.c\
	$(SRC_DIR)/philo_getter_setter.c\
	$(SRC_DIR)/philo_act.c\
	$(SRC_DIR)/philo_onephi.c\

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#DEP = $(OBJ:.o=.d)

WFLAGS = -Wall -Wextra -Werror

OPT =  -pthread -g -O3 #-fsanitize=thread

CC = cc
#-pthread => copile with POSIX threads library

.PHONY: all bonus clean fclean re valgrind
  
all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(WFLAGS) $(OPT) $^ -o $@ 
	@echo "Compilation finished! Executable '$(NAME)' is ready."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@ 

#-MMD includes all #include dependencies but excludes system headers.

# Include dependencies
#-include $(DEP)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@echo "*.o were cleaned."

fclean: clean
	@rm -f $(NAME)
	@echo "Executable '$(NAME)' was removed."

re: fclean all
	
valgrind:
	valgrind --track-fds=yes --show-leak-kinds=all --leak-check=full $(NAME)

re: fclean all