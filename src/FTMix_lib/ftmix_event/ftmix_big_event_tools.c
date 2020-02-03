#include "ftmix_lib.h"

void			ftmix_event_timer_line(SDL_Event old_event, size_t fps, void (*ptr)(void))
{
	_Bool			EXIT_VALUE;
	SDL_Event		event;
	unsigned int	last_time;
	unsigned int	current_time;
	int				i;
	int				len;

	if (!ftmix.music.nb)
		return;
	len = ft_strlen(ftmix.music.path[ftmix.music.actual]);
	if (ftmix.music.path[ftmix.music.actual][len - 1] != '3' || ftmix.music.path[ftmix.music.actual][len - 2] != 'p' ||
		ftmix.music.path[ftmix.music.actual][len - 3] != 'm' || ftmix.music.path[ftmix.music.actual][len - 4] != '.')
		return;
	len = ftmix.music.len[ftmix.music.actual];
	i = Mix_PausedMusic();
	if (i != 1)
		ftmix_event_pause();
	if (old_event.button.x  - ftmix.pos_x < 15)
		ftmix_set_timer(0);
	else if (old_event.button.x - ftmix.pos_x > 305)
		ftmix_set_timer(len);
	else
		ftmix_set_timer((old_event.button.x - ftmix.pos_x - 15) * len / 290);
	EXIT_VALUE = SDL_FALSE;
	(*ptr)();
	SDL_RenderPresent(ftmix.renderer);
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
			if (event.motion.x  - ftmix.pos_x < 15)
				ftmix_set_timer(0);
			else if (event.motion.x - ftmix.pos_x > 305)
				ftmix_set_timer(len);
			else
				ftmix_set_timer((event.motion.x - ftmix.pos_x - 15) * len / 290);
		}
		current_time = SDL_GetTicks();
		if (current_time >= last_time + (1000 / fps))
		{
			(*ptr)();
			last_time = SDL_GetTicks();
		}
		SDL_RenderPresent(ftmix.renderer);
	}
	if (i != 1)
		ftmix_event_pause();
}

void			ftmix_event_volume_line(SDL_Event old_event, size_t fps, void (*ptr)(void))
{
	_Bool			EXIT_VALUE;
	SDL_Event		event;
	unsigned int	last_time;
	unsigned int	current_time;
	unsigned int	volume_tmp;

	volume_tmp = ftmix.music.volume;
	if (old_event.button.x - ftmix.pos_x < 145)
		ftmix.music.volume = 0;
	else if (old_event.button.x - ftmix.pos_x > 195)
		ftmix.music.volume = MIX_MAX_VOLUME;
	else
		ftmix.music.volume = (old_event.button.x - ftmix.pos_x - 145) * MIX_MAX_VOLUME / 50;
	Mix_VolumeMusic(ftmix.music.volume);
	EXIT_VALUE = SDL_FALSE;
	(*ptr)();
	SDL_RenderPresent(ftmix.renderer);
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
			if (event.motion.x - ftmix.pos_x < 145)
				ftmix.music.volume = 0;
			else if (event.motion.x - ftmix.pos_x > 195)
				ftmix.music.volume = MIX_MAX_VOLUME;
			else
				ftmix.music.volume = (event.motion.x - ftmix.pos_x - 145) * MIX_MAX_VOLUME / 50;
			Mix_VolumeMusic(ftmix.music.volume);
		}
		ftmix_auto_play_next();
		current_time = SDL_GetTicks();
		if (current_time >= last_time + (1000 / fps))
		{
			(*ptr)();
			last_time = SDL_GetTicks();
		}
		SDL_RenderPresent(ftmix.renderer);
	}
	if (ftmix.music.volume != 0)
		ftmix.music.volume_last = ftmix.music.volume;
	else
		ftmix.music.volume_last = volume_tmp;
}