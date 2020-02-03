C_STANDART = \033[0m
C_GRAS = \033[1m
C_SOULIGN = \033[4m
C_CLIGN = \033[5m
C_SURLIGN = \033[7m
C_BLACK = \033[30m
C_RED = \033[31m
C_GREEN = \033[32m
C_YELLOW = \033[33m
C_BLUE = \033[34m
C_PINK = \033[35m
C_CYAN = \033[36m
C_GREY = \033[37m

NAME = MusicMixer

CC = gcc -Wall -Wextra -Werror

SRC = 	main.c \
		ftmix_lib/ftmix_init/ftmix_init.c ftmix_lib/ftmix_init/ftmix_WinMain.c \
		ftmix_lib/ftmix_load/ftmix_load.c ftmix_lib/ftmix_load/ftmix_load_len.c \
		ftmix_lib/ftmix_load/ftmix_load_name.c ftmix_lib/ftmix_load/ftmix_load_path.c \
		ftmix_lib/ftmix_load/ftmix_load_texture.c \
		ftmix_lib/ftmix_event/ftmix_event.c ftmix_lib/ftmix_event/ftmix_event_tools.c \
		ftmix_lib/ftmix_event/ftmix_big_event_tools.c \
		ftmix_lib/ftmix_print/ftmix_print.c ftmix_lib/ftmix_print/ftmix_print_tools.c \
		ftmix_lib/ftmix_animation/ftmix_animation.c \
		ftmix_lib/ftmix_mini_libft.c ftmix_lib/ftmix_utf8.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@ windres "src/ftmix_lib/icon.rc" icon.o
	@ $(CC) $(addprefix src/, $(SRC)) icon.o -I inc -I inc/lib_inc lib/mingw/lib/libmingw32.a -Llib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o bin/$(NAME)
	@ rm -f icon.o
	@ echo -e "$(C_STANDART)==\tCompilation $(NAME)\t\t$(C_GREEN)DONE$(C_STANDART)"
	
clean:
	@ rm -f bin/$(NAME)
	@ rm -f icon.o
	@ echo -e "$(C_STANDART)==\tClean $(NAME)\t\t\t$(C_GREEN)DONE$(C_STANDART)"

re: clean all

test: re
	./bin/$(NAME)