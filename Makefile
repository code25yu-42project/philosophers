# Project name
NAME_PROC       = philo_proc
NAME_THREAD     = philo_thread

# Compiler
CC              = cc
CFLAGS          = -Wall -Wextra -Werror -Iincludes

# Directories
SRCS_PROC_DIR   = srcs/philo_proc
SRCS_THREAD_DIR = srcs/philo_thread

# Source file names (파일명만)
SRCS_PROC_FILES       = exit.c init.c libft.c main.c monitor.c proc.c routine.c utils.c
SRCS_THREAD_FILES     = exit.c init.c libft.c main.c monitor.c routine.c thread.c utils.c

# Full source file paths
SRCS_PROC       = $(addprefix $(SRCS_PROC_DIR)/, $(SRCS_PROC_FILES))
SRCS_THREAD     = $(addprefix $(SRCS_THREAD_DIR)/, $(SRCS_THREAD_FILES))

# Object files
OBJS_PROC       = $(SRCS_PROC:.c=.o)
OBJS_THREAD     = $(SRCS_THREAD:.c=.o)

# Rules
all: $(NAME_PROC) $(NAME_THREAD)

$(NAME_PROC): $(OBJS_PROC)
	$(CC) $(CFLAGS) $^ -o $@

$(NAME_THREAD): $(OBJS_THREAD)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_PROC) $(OBJS_THREAD)

fclean: clean
	rm -rf $(NAME_PROC) $(NAME_THREAD)

re: fclean all

.PHONY: all clean fclean re
