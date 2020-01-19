#include "FTMix_lib.h"

static char		**FTMix_swap_dynamic_str(char **s, size_t first, size_t sec)
{
	char		*str;
	size_t		len1;
	size_t		len2;

	str = NULL;
	len1 = ft_strlen(s[first]);
	if (!(str = malloc(sizeof(*str) * (len1 + 1))))
		return (NULL);
	ft_strncpy(str, s[first], len1);
	free(s[first]);
	s[first] = NULL;
	len2 = ft_strlen(s[sec]);
	if (!(s[first] = malloc(sizeof(*s[first]) * (len2 + 1))))
		return (NULL);
	ft_strncpy(s[first], s[sec], len2);
	free(s[sec]);
	s[sec] = NULL;
	if (!(s[sec] = malloc(sizeof(*s[sec]) * (len1 + 1))))
		return (NULL);
	ft_strncpy(s[sec], str, len1);
	free(str);
	return (s);
}

static void		FTMix_rand_music_path(void)
{
	size_t		i;
	size_t		x;

	i = 0;
	while (i < ftmix.MUSIC_NB)
	{
		x = rand() % ftmix.MUSIC_NB;
		if (x != i)
		{
			if (!FTMix_swap_dynamic_str(ftmix.MUSIC_PATH, x, i))
				FTMix_ExitWithError("malloc");
		}
		i++;
	}
}

void			FTMix_print_while_loading(void)
{
	static unsigned int		last = 0;
	static size_t			count = 0;
	unsigned int			timer;

	timer = SDL_GetTicks();
	if (last == 0 || timer >= last + 1000 / 60)
	{
		if (SDL_SetRenderDrawColor(ftmix.RENDERER, 255, 255, 255, 255) != 0)
			FTMix_ExitWithError("SDL_SetRenderDrawColor");
		if (SDL_RenderClear(ftmix.RENDERER) != 0)
			FTMix_ExitWithError("SDL_RenderClear");
	//	FTMix_print_animation(200, 300, 0);
		FTMix_PrintSurfaceCenterXY(ftmix.LOADING[count % 3], ftmix.WINDOW_W / 2, ftmix.WINDOW_H / 2);
		last = timer;
		count++;
	}
	SDL_RenderPresent(ftmix.RENDERER);
	
}

static void		FTMix_init_variable(void)
{
	ftmix.MUSIC = NULL;
	ftmix.MUSIC_NB = 0;
	ftmix.MUSIC_PATH = NULL;
	ftmix.MUSIC_NAME = NULL;
	ftmix.MUSIC_ACTUAL = 0;
	ftmix.MUSIC_TIMER = 0;
	ftmix.COLOR1.r = 255;
	ftmix.COLOR1.g = 255;
	ftmix.COLOR1.b = 255;
	ftmix.COLOR1.a = 255;
	ftmix.COLOR2.r = 105;
	ftmix.COLOR2.g = 105;
	ftmix.COLOR2.b = 105;
	ftmix.COLOR2.a = 255;
	ftmix.FONT[0] = NULL;
	ftmix.MUSIC_LEN = NULL;
	ftmix.LOOP = SDL_FALSE;
	ftmix.VOLUME = 15;
	ftmix.VOLUME_LAST = 15;
	ftmix.BUBBLE = SDL_FALSE;
	Mix_VolumeMusic(ftmix.VOLUME);
}

void			FTMix_first_load(void)
{
	TTF_Font		*font = NULL;
	char			*str = NULL;
	SDL_Color		color = {0, 0, 0, 255};
//	size_t			i = 0;
	
/*	while (i < FTMIX_ANIMATION_MAX)
	{
		ftmix.ANIMATION[i] = NULL;
		ftmix.ANIMATION_PATH[i] = NULL;
		ftmix.ANIMATION_ACTUAL[i] = 0;
		ftmix.ANIMATION_NB[i] = 0;
		ftmix.ANIMATION_FPS[i] = 0;
		ftmix.ANIMATION_LAST[i] = 0;
		i++;
	}*/
	ftmix.t_PAUSE = NULL;
	ftmix.t_PLAY = NULL;
	ftmix.t_VOLUME_LOW = NULL;
	ftmix.t_VOLUME_MID = NULL;
	ftmix.t_VOLUME_HIGH = NULL;
	ftmix.t_VOLUME_OFF = NULL;
	ftmix.t_POINT = NULL;
	ftmix.t_BASE = NULL;
	ftmix.POS_X = 0;
	ftmix.POS_Y = 0;
	atexit(FTMix_free_load);
	atexit(FTMix_free_animation_load);
//	FTMix_init_animation(L"turtle/", 10, 150, 0);
	if (!(str = ft_strjoin(ftmix.DIR_PIC_PATH, FTMIX_POLICE_NAME)))
		FTMix_ExitWithError("ft_strjoin");
	if (!(font = TTF_OpenFont(str, 40)))
		FTMix_ExitWithError("TTF_OpenFont");
	ftmix.LOADING[0] = NULL;
	ftmix.LOADING[1] = NULL;
	ftmix.LOADING[2] = NULL;
	if (!(ftmix.LOADING[0] = TTF_RenderText_Blended(font, "Loading .", color)))
		FTMix_ExitWithError("SDL_TTF_RenderText_Blended");
	if (!(ftmix.LOADING[1] = TTF_RenderText_Blended(font, "Loading ..", color)))
		FTMix_ExitWithError("SDL_TTF_RenderText_Blended");
	if (!(ftmix.LOADING[2] = TTF_RenderText_Blended(font, "Loading ...", color)))
		FTMix_ExitWithError("SDL_TTF_RenderText_Blended");
	TTF_CloseFont(font);
	free(str);
	FTMix_print_while_loading();
}

void			FTMix_load(void)
{
	static _Bool	DONE = SDL_FALSE;
	
	if (!DONE)
	{
		FTMix_first_load();
		DONE = SDL_TRUE;
	}
	else
		FTMix_free_load();
	FTMix_init_variable();
	FTMix_print_while_loading();
	FTMix_load_pic();
	FTMix_print_while_loading();
	FTMix_load_music_path();
	FTMix_print_while_loading();
	FTMix_rand_music_path();
	FTMix_print_while_loading();
	FTMix_load_music_name();
	FTMix_print_while_loading();
	FTMix_load_music_len();
	if (ftmix.MUSIC_NB)
	{
		FTMix_load_music(ftmix.MUSIC_PATH[ftmix.MUSIC_ACTUAL]);
		FTMix_event_pause();
	} 
}
