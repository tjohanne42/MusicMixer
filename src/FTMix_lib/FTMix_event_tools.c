#include "FTMix_lib.h"

void			FTMix_event_pause(void)
{
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
	ftmix.MUSIC_TIMER = SDL_GetTicks() - ftmix.MUSIC_TIMER;
}

void			FTMix_event_volume_pic(void)
{
	if (ftmix.VOLUME != 0)
	{
		ftmix.VOLUME_LAST = ftmix.VOLUME;
		ftmix.VOLUME = 0;
	}
	else if (ftmix.VOLUME_LAST != MIX_MAX_VOLUME + 1)
		ftmix.VOLUME = ftmix.VOLUME_LAST;
	else
		ftmix.VOLUME = MIX_MAX_VOLUME / 2;
	Mix_VolumeMusic(ftmix.VOLUME);
}

int				FTMix_get_timer(void)
{
	if (Mix_PausedMusic() == 1)
		return (ftmix.MUSIC_TIMER);
	return (SDL_GetTicks() - ftmix.MUSIC_TIMER);
}

_Bool			FTMix_PointInRect(size_t px, size_t py, size_t rx, size_t ry, size_t rw, size_t rh)
{
	SDL_Point	point;
	SDL_Rect	rect;

	point.x = px;
	point.y = py;
	rect.x = rx;
	rect.y = ry;
	rect.w = rw;
	rect.h = rh;
	return (SDL_PointInRect(&point, &rect));
}

void			FTMix_change_timer(int ms)
{
	FTMix_set_timer(FTMix_get_timer() + ms);
}

void			FTMix_event_loop(void)
{
	if (!ftmix.LOOP)
		ftmix.LOOP = SDL_TRUE;
	else
		ftmix.LOOP = SDL_FALSE;
}

void			FTMix_increase_volume(size_t v)
{
	if (ftmix.VOLUME + v <= MIX_MAX_VOLUME)
	{
		ftmix.VOLUME += v;
		Mix_VolumeMusic(ftmix.VOLUME);
	}
	else
	{
		ftmix.VOLUME = MIX_MAX_VOLUME;
		Mix_VolumeMusic(ftmix.VOLUME);
	}
}

void			FTMix_decrease_volume(size_t v)
{
	if (ftmix.VOLUME >= v)
	{
		ftmix.VOLUME -= v;
		Mix_VolumeMusic(ftmix.VOLUME);
	}
	else
	{
		ftmix.VOLUME = 0;
		Mix_VolumeMusic(ftmix.VOLUME);
	}
}

void			FTMix_event_previous(void)
{
	if (FTMix_get_timer() >= 5000)
	{
		FTMix_set_timer(0);
		return;
	}
	if (ftmix.LOOP)
		ftmix.LOOP = SDL_FALSE;
	FTMix_play_previous();
}

void			FTMix_event_next(void)
{
	if (ftmix.LOOP)
		ftmix.LOOP = SDL_FALSE;
	FTMix_play_next();
}

void			FTMix_play_previous(void)
{
	if (!ftmix.MUSIC_NB)
		return;
	if (ftmix.MUSIC_NB == 1)
		FTMix_load_music(ftmix.MUSIC_PATH[ftmix.MUSIC_ACTUAL]);
	else
	{
		if (ftmix.MUSIC_ACTUAL == 0)
			ftmix.MUSIC_ACTUAL = ftmix.MUSIC_NB - 1;
		else
			ftmix.MUSIC_ACTUAL--;
		FTMix_load_music(ftmix.MUSIC_PATH[ftmix.MUSIC_ACTUAL]);
	}
}

void			FTMix_play_next(void)
{
	if (!ftmix.MUSIC_NB)
		return;
	if (ftmix.MUSIC_NB == 1)
		FTMix_load_music(ftmix.MUSIC_PATH[ftmix.MUSIC_ACTUAL]);
	else
	{
		ftmix.MUSIC_ACTUAL++;
		if (ftmix.MUSIC_ACTUAL >= ftmix.MUSIC_NB)
			ftmix.MUSIC_ACTUAL = 0;
		FTMix_load_music(ftmix.MUSIC_PATH[ftmix.MUSIC_ACTUAL]);
	}
}

void			FTMix_set_timer(int ms)
{
	if (!ftmix.MUSIC_NB)
		return;
	if (ms < 0)
		FTMix_set_timer(0);
	else if (ms > ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL])
	{
		if (ftmix.LOOP)
			FTMix_load_music(ftmix.MUSIC_PATH[ftmix.MUSIC_ACTUAL]);
		else
			FTMix_play_next();
	}
	else
	{
		if (Mix_PausedMusic() == 1)
			ftmix.MUSIC_TIMER = ms;
		else
			ftmix.MUSIC_TIMER = SDL_GetTicks() - ms;
		Mix_RewindMusic();
		Mix_SetMusicPosition((double)ms / 1000);
	}
}

void			FTMix_change_music(void)
{
	if (Mix_PlayingMusic() != 1 && ftmix.MUSIC_NB > 0)
	{
		if (ftmix.LOOP)
			FTMix_load_music(ftmix.MUSIC_PATH[ftmix.MUSIC_ACTUAL]);
		else
			FTMix_play_next();
	}
}

void			FTMix_load_music(const char *path)
{
	int			i;

	i = Mix_PausedMusic();
	
	if (ftmix.MUSIC)
	{
		if (Mix_PlayingMusic() == 1)
			Mix_HaltMusic();
		Mix_FreeMusic(ftmix.MUSIC);
		ftmix.MUSIC = NULL;
	}
	ftmix.MUSIC = Mix_LoadMUS(path);
	Mix_PlayMusic(ftmix.MUSIC, 1);
	ftmix.MUSIC_TIMER = SDL_GetTicks();
	if (i == 1)
		FTMix_event_pause();
}

void			FTMix_event_reload(void)
{
	if (Mix_PlayingMusic() == 1)
		Mix_HaltMusic();
	FTMix_load();
	FTMix_event_pause();
}

void			FTMix_event_bubble(void)
{
	if (ftmix.BUBBLE)
		ftmix.BUBBLE = SDL_FALSE;
	else
		ftmix.BUBBLE = SDL_TRUE;
}
