#include "FTMix_lib.h"

void			FTMix_free_music_len(void)
{
	if (ftmix.MUSIC_LEN)
	{
		free(ftmix.MUSIC_LEN);
		ftmix.MUSIC_LEN = NULL;
	}
}

void			FTMix_free_animation_channel(size_t channel)
{
	size_t		i = 0;
	while (i < ftmix.ANIMATION_NB[channel] && ftmix.ANIMATION[channel])
	{
		if (ftmix.ANIMATION[channel][i])
		{
			SDL_DestroyTexture(ftmix.ANIMATION[channel][i]);
			ftmix.ANIMATION[channel][i] = NULL;
		}
		i++;
	}
	if (ftmix.ANIMATION[channel])
	{
		free(ftmix.ANIMATION[channel]);
		ftmix.ANIMATION[channel] = NULL;
	}
}

void		FTMix_free_music_path(void)
{
	size_t		i;

	if (ftmix.MUSIC_PATH)
	{
		i = 0;
		while (i < ftmix.MUSIC_NB && ftmix.MUSIC_PATH[i])
		{
			free(ftmix.MUSIC_PATH[i]);
			ftmix.MUSIC_PATH[i] = NULL;
			i++;
		}
		free(ftmix.MUSIC_PATH);
		ftmix.MUSIC_PATH = NULL;
	}
}

void			FTMix_free_pic(void)
{
	size_t		i;

	if (ftmix.t_PAUSE)
		SDL_DestroyTexture(ftmix.t_PAUSE);
	if (ftmix.t_PLAY)
		SDL_DestroyTexture(ftmix.t_PLAY);
	if (ftmix.t_VOLUME_LOW)
		SDL_DestroyTexture(ftmix.t_VOLUME_LOW);
	if (ftmix.t_VOLUME_MID)
		SDL_DestroyTexture(ftmix.t_VOLUME_MID);
	if (ftmix.t_VOLUME_HIGH)
		SDL_DestroyTexture(ftmix.t_VOLUME_HIGH);
	if (ftmix.t_VOLUME_OFF)
		SDL_DestroyTexture(ftmix.t_VOLUME_OFF);
	if (ftmix.t_POINT)
		SDL_DestroyTexture(ftmix.t_POINT);
	if (ftmix.t_BASE)
		SDL_DestroyTexture(ftmix.t_BASE);
	if (ftmix.FONT)
	{
		i = 0;
		while (i < 19 && ftmix.FONT[i])
		{
			TTF_CloseFont(ftmix.FONT[i]);
			ftmix.FONT[i] = NULL;
			i++;
		}
	}
	ftmix.t_PAUSE = NULL;
	ftmix.t_PLAY = NULL;
	ftmix.t_VOLUME_LOW = NULL;
	ftmix.t_VOLUME_MID = NULL;
	ftmix.t_VOLUME_HIGH = NULL;
	ftmix.t_VOLUME_OFF = NULL;
	ftmix.t_POINT = NULL;
	ftmix.t_BASE = NULL;
}

void		FTMix_free_music_name(void)
{
	size_t		i;

	if (ftmix.MUSIC_NAME)
	{
		i = 0;
		if (!ftmix.MUSIC_NB)
			SDL_FreeSurface(ftmix.MUSIC_NAME[0]);
		while (i < ftmix.MUSIC_NB && ftmix.MUSIC_NAME[i])
		{
			SDL_FreeSurface(ftmix.MUSIC_NAME[i]);
			ftmix.MUSIC_NAME[i] = NULL;
			i++;
		}
		free(ftmix.MUSIC_NAME);
		ftmix.MUSIC_NAME = NULL;
	}
}

void			FTMix_free_animation_load()
{
	size_t		i = 0;

	while (i < FTMIX_ANIMATION_MAX)
	{
		FTMix_free_animation_channel(i);
		i++;
	}
	if (ftmix.LOADING[0])
		SDL_FreeSurface(ftmix.LOADING[0]);
	if (ftmix.LOADING[1])
		SDL_FreeSurface(ftmix.LOADING[1]);
	if (ftmix.LOADING[2])
		SDL_FreeSurface(ftmix.LOADING[2]);
}

void			FTMix_free_load(void)
{
	FTMix_free_pic();
	FTMix_free_music_path();
	FTMix_free_music_name();
	FTMix_free_music_len();
	if (ftmix.MUSIC)
	{
		Mix_FreeMusic(ftmix.MUSIC);
		ftmix.MUSIC = NULL;
	}
}
