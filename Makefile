##
## EPITECH PROJECT, 2020
## CPP_plazza_2019
## File description:
## Makefile
##

CC = g++ -std=c++17

CFLAGS = -pthread -I./headers

LIB = -lpthread

NAME = plazza

SRC = $(wildcard sources/*.cpp sources/IPC/*.cpp sources/Ordering/*.cpp sources/Exceptions/*.cpp)

OBJ = $(SRC:.cpp=.o)

RM = rm -rf

all: $(NAME)

$(OBJ): %.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIB)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re $(NAME)