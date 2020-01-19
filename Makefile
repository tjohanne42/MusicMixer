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
		FTMix_lib/FTMix_big_event_tools.c FTMix_lib/FTMix_event.c \
		FTMix_lib/FTMix_event_tools.c FTMix_lib/FTMix_init.c \
		FTMix_lib/FTMix_init_dir_path.c FTMix_lib/FTMix_animation.c \
		FTMix_lib/FTMix_load.c FTMix_lib/FTMix_free.c \
		FTMix_lib/FTMix_load_music_len.c FTMix_lib/FTMix_load_music_name.c \
		FTMix_lib/FTMix_load_music_path.c FTMix_lib/FTMix_load_pic.c \
		FTMix_lib/FTMix_print.c FTMix_lib/FTMix_print_tools.c \
		FTMix_lib/mini_libft.c FTMix_lib/wchar_utf8.c FTMix_lib/WinMain.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@ windres "src/FTMix_lib/icon.rc" icon.o
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