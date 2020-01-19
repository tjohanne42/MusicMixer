#include "FTMix_lib.h"

void			FTMix_event_timer_line(SDL_Event old_event, size_t fps, void (*ptr)(void))
{
	_Bool			EXIT_VALUE;
	SDL_Event		event;
	unsigned int	last_time;
	unsigned int	current_time;
	int				i;
	int				len;

	if (!ftmix.MUSIC_NB)
		return;
	len = ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL];
	i = Mix_PausedMusic();
	if (i != 1)
		FTMix_event_pause();
	if (old_event.button.x  - (int)ftmix.POS_X < 15)
		FTMix_set_timer(0);
	else if (old_event.button.x - (int)ftmix.POS_X > 305)
		FTMix_set_timer(len);
	else
		FTMix_set_timer((old_event.button.x - (int)ftmix.POS_X - 15) * len / 290);
	EXIT_VALUE = SDL_FALSE;
	FTMix_print(-1, -1);
	SDL_RenderPresent(ftmix.RENDERER);
	last_time = SDL_GetTicks();
	while (!EXIT_VALUE)
	{
		event.type = 0;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
			EXIT_VALUE = SDL_TRUE;
		else if (event.type == SDL_MOUSEMOTION)
		{
			if (event.motion.x  - (int)ftmix.POS_X < 15)
				FTMix_set_timer(0);
			else if (event.motion.x - (int)ftmix.POS_X > 305)
				FTMix_set_timer(len);
			else
				FTMix_set_timer((event.motion.x - (int)ftmix.POS_X - 15) * len / 290);
		}
		current_time = SDL_GetTicks();
		if (current_time >= last_time + (1000 / fps))
		{
			(*ptr)();
			last_time = SDL_GetTicks();
		}
		SDL_RenderPresent(ftmix.RENDERER);
	}
	if (i != 1)
		FTMix_event_pause();
}

void			FTMix_event_volume_line(SDL_Event old_event, size_t fps, void (*ptr)(void))
{
	_Bool			EXIT_VALUE;
	SDL_Event		event;
	unsigned int	last_time;
	unsigned int	current_time;
	unsigned int	volume_tmp;

	volume_tmp = ftmix.VOLUME;
	if (old_event.button.x - (int)ftmix.POS_X < 145)
		ftmix.VOLUME = 0;
	else if (old_event.button.x - (int)ftmix.POS_X > 195)
		ftmix.VOLUME = MIX_MAX_VOLUME;
	else
		ftmix.VOLUME = (old_event.button.x - (int)ftmix.POS_X - 145) * MIX_MAX_VOLUME / 50;
	Mix_VolumeMusic(ftmix.VOLUME);
	EXIT_VALUE = SDL_FALSE;
	FTMix_print(-1, -1);
	SDL_RenderPresent(ftmix.RENDERER);
	last_time = SDL_GetTicks();
	while (!EXIT_VALUE)
	{
		event.type = 0;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			exit(EXIT_SUCCESS);
		else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
			EXIT_VALUE = SDL_TRUE;
		else if (event.type == SDL_MOUSEMOTION)
		{
			if (event.motion.x - (int)ftmix.POS_X < 145)
				ftmix.VOLUME = 0;
			else if (event.motion.x - (int)ftmix.POS_X > 195)
				ftmix.VOLUME = MIX_MAX_VOLUME;
			else
				ftmix.VOLUME = (event.motion.x - (int)ftmix.POS_X - 145) * MIX_MAX_VOLUME / 50;
			Mix_VolumeMusic(ftmix.VOLUME);
		}
		FTMix_change_music();
		current_time = SDL_GetTicks();
		if (current_time >= last_time + (1000 / fps))
		{
			(*ptr)();
			last_time = SDL_GetTicks();
		}
		SDL_RenderPresent(ftmix.RENDERER);
	}
	if (ftmix.VOLUME != 0)
		ftmix.VOLUME_LAST = ftmix.VOLUME;
	else
		ftmix.VOLUME_LAST = volume_tmp;
}
