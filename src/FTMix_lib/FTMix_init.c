#include "FTMix_lib.h"

static void		FTMix_exit(void)
{
	if (ftmix.RENDERER)
		SDL_DestroyRenderer(ftmix.RENDERER);
	if (ftmix.WINDOW)
		SDL_DestroyWindow(ftmix.WINDOW);
	TTF_Quit();
	IMG_Quit();
	Mix_CloseAudio();
	Mix_CloseAudio();
	SDL_Quit();
}

void			FTMix_ExitWithError(const char *str)
{
	SDL_Log("ERROR %s : %s\n", str, SDL_GetError());
	SDL_Log("ERROR %s : %s\n", str, IMG_GetError());
	SDL_Log("ERROR %s : %s\n", str, TTF_GetError());
	exit(EXIT_FAILURE);
}


static void		FTMix_OpenWindow(const char *name, const unsigned int w, const unsigned int h, const char *icon_path)
{
	SDL_Surface	*ico = NULL;
	char		*str = NULL;

	// Create window
	if (!(ftmix.WINDOW = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN)))
		FTMix_ExitWithError("SDL_CreateWindow");
	// Create W_renderer
	if (!(ftmix.RENDERER = SDL_CreateRenderer(ftmix.WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		FTMix_ExitWithError("SDL_CreateW_Renderer");
	// Set blend mode (superposition des couleurs en fonction de a dans rgba)
	if (SDL_SetRenderDrawBlendMode(ftmix.RENDERER, SDL_BLENDMODE_MOD) != 0)
		FTMix_ExitWithError("SDL_SetRenderDrawBlendMode");
	if (icon_path)
	{
		if (!(str = ft_strjoin(icon_path, "icon.png")))
			FTMix_ExitWithError("ft_strjoin");
		if (!(ico = IMG_Load(str)))
			FTMix_ExitWithError("IMG_Load");
		free(str);
		SDL_SetWindowIcon(ftmix.WINDOW, ico);
		SDL_FreeSurface(ico);
	}
}

void			FTMix_init(const wchar_t *name, unsigned int w, unsigned int h, const wchar_t *dir_pic_wpath, const wchar_t *dir_music_wpath)
{
	static _Bool	DONE = SDL_FALSE;
	char			*name_tmp = NULL;
	int				initted;
	int 			flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

	if (DONE)
		return;
	DONE = SDL_TRUE;
	if (!setlocale(LC_ALL, ""))
		FTMix_ExitWithError("setlocale");
	srand(time(NULL));
	ftmix.WINDOW = NULL;
	ftmix.RENDERER = NULL;
	ftmix.WINDOW_W = w;
	ftmix.WINDOW_H = h;
	atexit(FTMix_exit);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		FTMix_ExitWithError("SDL_Init");
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
		FTMix_ExitWithError("Mix_OpenAudio");
	initted = IMG_Init(flags);
	if ((initted&flags) != flags)
		FTMix_ExitWithError("IMG_Init");
	if (TTF_Init() != 0)
		FTMix_ExitWithError("TTF_Init");
	FTMix_init_dir_path(dir_pic_wpath, dir_music_wpath);
	if (!(name_tmp = ft_wstrtstr(name)))
		FTMix_ExitWithError("ft_wstrtstr");
	FTMix_OpenWindow(name_tmp, w, h, ftmix.DIR_PIC_PATH);
	free(name_tmp);
}
