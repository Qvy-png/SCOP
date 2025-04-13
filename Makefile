NAME = scop

CC = gcc

CFLAGS = -Wall -Wextra -std=c11

LIBS = -lglfw -lGLEW -lGL -lm

SRC = srcs/main.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(LIBS)

clean:
	rm -f $(NAME)
