# Binary Names
CLIENT_NAME = client
SERVER_NAME = server
CLIENT_BONUS_NAME = client_bonus
SERVER_BONUS_NAME = server_bonus
PRINTF_LIB = libftprintf.a

# Directories
SRC_DIR = src
PRINTF_DIR = printf

# Source Files
CLIENT_SRC_FILES = client.c
SERVER_SRC_FILES = server.c
CLIENT_BONUS_FILES = client_bonus.c
SERVER_BONUS_FILES = server_bonus.c

# Full Paths
CLIENT_SRC = $(addprefix $(SRC_DIR)/, $(CLIENT_SRC_FILES))
SERVER_SRC = $(addprefix $(SRC_DIR)/, $(SERVER_SRC_FILES))
CLIENT_BONUS_SRC = $(addprefix $(SRC_DIR)/, $(CLIENT_BONUS_FILES))
SERVER_BONUS_SRC = $(addprefix $(SRC_DIR)/, $(SERVER_BONUS_FILES))

# Object Files
CLIENT_OBJ = ${CLIENT_SRC:.c=.o}
SERVER_OBJ = ${SERVER_SRC:.c=.o}
CLIENT_BONUS_OBJ = ${CLIENT_BONUS_SRC:.c=.o}
SERVER_BONUS_OBJ = ${SERVER_BONUS_SRC:.c=.o}

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = -I include

# Commands
RM = rm -rf

# Targets
.PHONY: all bonus clean fclean re

all: $(CLIENT_NAME) $(SERVER_NAME)

bonus: $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME)

$(CLIENT_NAME): $(CLIENT_OBJ)
	@make -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(INCLUDE) $(PRINTF_DIR)/$(PRINTF_LIB) -o $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJ)
	@make -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(INCLUDE) $(PRINTF_DIR)/$(PRINTF_LIB) -o $(SERVER_NAME)

$(CLIENT_BONUS_NAME): $(CLIENT_BONUS_OBJ)
	@make -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJ) $(INCLUDE) $(PRINTF_DIR)/$(PRINTF_LIB) -o $(CLIENT_BONUS_NAME)

$(SERVER_BONUS_NAME): $(SERVER_BONUS_OBJ)
	@make -C $(PRINTF_DIR)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJ) $(INCLUDE) $(PRINTF_DIR)/$(PRINTF_LIB) -o $(SERVER_BONUS_NAME)

clean:
	@make clean -C $(PRINTF_DIR)
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ) $(CLIENT_BONUS_OBJ) $(SERVER_BONUS_OBJ)

fclean: clean
	@make fclean -C $(PRINTF_DIR)
	$(RM) $(CLIENT_NAME) $(SERVER_NAME) $(CLIENT_BONUS_NAME) $(SERVER_BONUS_NAME) $(PRINTF_DIR)/$(PRINTF_LIB)

re: fclean all

