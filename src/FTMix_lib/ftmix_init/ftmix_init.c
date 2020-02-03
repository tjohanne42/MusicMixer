#include "ftmix_lib.h"

static void		ftmix_exit(void)
{
	if (ftmix.renderer)
	{
		SDL_DestroyRenderer(ftmix.renderer);
		ftmix.renderer = NULL;
	}
	if (ftmix.window)
	{
		SDL_DestroyWindow(ftmix.window);
		ftmix.window = NULL;
	}
	TTF_Quit();
	IMG_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}

void			ftmix_exit_error(const char *str)
{
	SDL_Log("FAILURE %s : %s\n", str, SDL_GetError());
	SDL_Log("FAILURE %s : %s\n", str, IMG_GetError());
	SDL_Log("FAILURE %s : %s\n", str, TTF_GetError());
	exit(EXIT_FAILURE);
}

static void		ftmix_init_folder(const wchar_t *music_folder, const wchar_t *pic_folder)
{
	size_t		i = 0;
	size_t		len;
	wchar_t		*tmp = NULL;
	char		*str = NULL;

	if (music_folder)
	{
		len = ft_wstrlen(music_folder);
		if (!(tmp = malloc(sizeof(*tmp) * (len  + 1))))
			ftmix_exit_error("malloc");
		ft_wstrncpy(tmp, music_folder, len);
		if (tmp[0] == L'/' || tmp[0] == L'\\')
		{
			while (i < len)
			{
				tmp[i] = tmp[i + 1];
				i++;
			}
			len -= 1;
			i = 0;
		}
		if (tmp[len - 1] != '/')
		{
			if (!ft_wstrfreejoin(&tmp, L"/", 'e'))
				ftmix_exit_error("ft_wstrfreejoin");
		}
		if (!ft_wstrfreejoin(&ftmix.music_folder, tmp, 'e'))
			ftmix_exit_error("ft_wstrfreejoin");
		free(tmp);
		tmp = NULL;
	}
	if (pic_folder)
	{
		len = ft_wstrlen(pic_folder);
		if (!(tmp = malloc(sizeof(*tmp) * (len  + 1))))
			ftmix_exit_error("malloc");
		ft_wstrncpy(tmp, pic_folder, len);
		if (tmp[0] == L'/' || tmp[0] == L'\\')
		{
			while (i < len)
			{
				tmp[i] = tmp[i + 1];
				i++;
			}
			len -= 1;
			i = 0;
		}
		if (tmp[len - 1] != '/')
		{
			if (!ft_wstrfreejoin(&tmp, L"/", 'e'))
				ftmix_exit_error("ft_wstrfreejoin");
		}
		if (!(str = ft_wstrtstr(tmp)))
			ftmix_exit_error("ft_wstrtstr");
		free(tmp);
		if (!ft_strfreejoin(&ftmix.pic_folder, str, 'e'))
			ftmix_exit_error("ft_wstrfreejoin");
		free(str);
	}
}

static void		ftmix_open_window(const char *name, unsigned int w, unsigned int h, const char *pic_folder)
{
	SDL_Surface	*ico = NULL;
	char		*str = NULL;

	// Create window
	if (!(ftmix.window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_RESIZABLE)))
		ftmix_exit_error("SDL_CreateWindow");
	// Create W_renderer
	if (!(ftmix.renderer = SDL_CreateRenderer(ftmix.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		ftmix_exit_error("SDL_CreateW_Renderer");
	// Set blend mode (superposition des couleurs en fonction de a dans rgba)
	if (SDL_SetRenderDrawBlendMode(ftmix.renderer, SDL_BLENDMODE_NONE) != 0)
		ftmix_exit_error("SDL_SetRenderDrawBlendMode");
	if (pic_folder)
	{
		if (!(str = ft_strjoin(pic_folder, "icon.png")))
			ftmix_exit_error("ft_strjoin");
		if (!(ico = IMG_Load(str)))
			ftmix_exit_error("IMG_Load");
		free(str);
		SDL_SetWindowIcon(ftmix.window, ico);
		SDL_FreeSurface(ico);
	}
}

void			ftmix_init(const wchar_t *name, unsigned int w, unsigned int h, const wchar_t *music_folder, const wchar_t *pic_folder)
{
	static _Bool	done = SDL_FALSE;
	int				initted;
	int 			flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	char			*name_tmp = NULL;
//	SDL_Rect		rect = {0, 0, w, h};

	if (!name)
		return;
	if (!done)
	{
		if (!setlocale(LC_ALL, ""))
			ftmix_exit_error("setlocale");
		srand(time(NULL));
		ftmix.window = NULL;
		ftmix.renderer = NULL;
		atexit(ftmix_exit);
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			ftmix_exit_error("SDL_Init");
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
			ftmix_exit_error("Mix_OpenAudio");
		initted = IMG_Init(flags);
		if ((initted&flags) != flags)
			ftmix_exit_error("IMG_Init");
		if (TTF_Init() != 0)
			ftmix_exit_error("TTF_Init");
		ftmix_init_folder(music_folder, pic_folder);
		if (!(name_tmp = ft_wstrtstr(name)))
			ftmix_exit_error("ft_wstrtstr");
		ftmix_open_window(name_tmp, w, h, ftmix.pic_folder);
		free(name_tmp);
		done = SDL_TRUE;
	}
}
