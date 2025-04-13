NAME = scop

CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -g3

LIBS = -lglfw -lGLEW -lGL -lm

SRC = srcs/main.c \
		srcs/shaders.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(LIBS)

clean:
	rm -f $(NAME)

