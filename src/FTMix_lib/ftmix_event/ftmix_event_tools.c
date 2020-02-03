#include "ftmix_lib.h"

void			ftmix_add_bubble(SDL_Event event)
{
	if (ftmix.bubble.nb + 1 >= FTMIX_BUBBLE_MAX)
		return;
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		ftmix.bubble.x[ftmix.bubble.nb] = event.button.x;
		ftmix.bubble.y[ftmix.bubble.nb] = event.button.y;
	}
	else if (event.type == SDL_MOUSEMOTION)
	{
		ftmix.bubble.x[ftmix.bubble.nb] = event.motion.x;
		ftmix.bubble.y[ftmix.bubble.nb] = event.motion.y;
	}
	else
	{
		ftmix.bubble.x[ftmix.bubble.nb] = 0;
		ftmix.bubble.y[ftmix.bubble.nb] = 0;
	}
	ftmix.bubble.color[ftmix.bubble.nb].r = rand() % 256;
	ftmix.bubble.color[ftmix.bubble.nb].g = rand() % 256;
	ftmix.bubble.color[ftmix.bubble.nb].b = rand() % 256;
	ftmix.bubble.color[ftmix.bubble.nb].a = 255;
	ftmix.bubble.start[ftmix.bubble.nb] = SDL_GetTicks();
	ftmix.bubble.nb += 1;
}

void			ftmix_event_bubble(void)
{
	if (ftmix.bubble.bubble)
		ftmix.bubble.bubble = SDL_FALSE;
	else
		ftmix.bubble.bubble = SDL_TRUE;
}

static _Bool	ftmix_event_rand_tool(size_t nb, size_t z)
{
	size_t		i = 0;

	while (i < z)
	{
		if (nb == ftmix.music.rand_tab[i])
			return (SDL_FALSE);
		i++;
	}
	return (SDL_TRUE);
}

void			ftmix_event_rand(void)
{
	size_t		i = 1;
	size_t		tmp;

	if (!ftmix.music.rand)
	{
		ftmix.music.rand_tab[0] = ftmix.music.actual;
		while (i < ftmix.music.nb)
		{
			tmp = rand() % ftmix.music.nb;
			while (!ftmix_event_rand_tool(tmp, i))
				tmp = rand() % ftmix.music.nb;
			ftmix.music.rand_tab[i] = tmp;
			i++;
		}
		ftmix.music.rand = SDL_TRUE;
	}
	else
		ftmix.music.rand = SDL_FALSE;
}

void			ftmix_volume_wheel(SDL_Event event)
{
	size_t		tmp = 0;

	if (event.wheel.direction != SDL_MOUSEWHEEL_NORMAL)
	{
		event.wheel.x *= -1;
		event.wheel.y *= -1;
	}
	if (event.wheel.y * -2 > (int)ftmix.music.volume && (tmp = 1))
		ftmix.music.volume = 0;
	else if ((int)ftmix.music.volume + event.wheel.y * 2 > MIX_MAX_VOLUME && (tmp = 1))
		ftmix.music.volume = MIX_MAX_VOLUME;
	else if ((tmp = 1))
		ftmix.music.volume = ftmix.music.volume + event.wheel.y * 2;
	if (tmp)
		Mix_VolumeMusic(ftmix.music.volume);
}

void			ftmix_change_timer(int ms)
{
	size_t		len;

	if (!ftmix.music.nb)
		return;
	len = ft_strlen(ftmix.music.path[ftmix.music.actual]);
	if (ftmix.music.path[ftmix.music.actual][len - 1] != '3' || ftmix.music.path[ftmix.music.actual][len - 2] != 'p' ||
		ftmix.music.path[ftmix.music.actual][len - 3] != 'm' || ftmix.music.path[ftmix.music.actual][len - 4] != '.')
		return;
	ftmix_set_timer((int)ftmix_get_timer() + ms);
}

void			ftmix_change_volume(int nb)
{
	if (nb < 0 && nb * -1 > (int)ftmix.music.volume)
		nb = ftmix.music.volume * -1;
	ftmix.music.volume += nb;
	if (ftmix.music.volume > MIX_MAX_VOLUME)
		ftmix.music.volume = MIX_MAX_VOLUME;
	Mix_VolumeMusic(ftmix.music.volume);
}

void			ftmix_auto_play_next(void)
{
	if (Mix_PlayingMusic() != 1 && ftmix.music.nb > 0)
	{
		if (ftmix.music.loop)
			ftmix_load_music(ftmix.music.path[ftmix.music.actual], 1);
		else
			ftmix_event_next();
	}
}

void			ftmix_event_reload(void)
{
	int			i;

	i = Mix_PausedMusic();
	if (Mix_PlayingMusic() == 1)
		Mix_HaltMusic();
	ftmix_load();
	if (i != Mix_PausedMusic())
		ftmix_event_pause();
}

void			ftmix_event_loop(void)
{
	if (ftmix.music.loop)
		ftmix.music.loop = SDL_FALSE;
	else
		ftmix.music.loop = SDL_TRUE;
}

void			ftmix_event_volume_pic(void)
{
	if (ftmix.music.volume != 0)
	{
		ftmix.music.volume_last = ftmix.music.volume;
		ftmix.music.volume = 0;
	}
	else if (ftmix.music.volume_last != MIX_MAX_VOLUME + 1)
		ftmix.music.volume = ftmix.music.volume_last;
	else
		ftmix.music.volume = MIX_MAX_VOLUME / 2;
	Mix_VolumeMusic(ftmix.music.volume);
}

unsigned int	ftmix_get_timer(void)
{
	if (Mix_PausedMusic() == 1)
		return (ftmix.music.timer);
	return (SDL_GetTicks() - ftmix.music.timer);
}

void			ftmix_set_timer(int ms)
{
	size_t		len;

	if (!ftmix.music.nb)
		return;
	len = ft_strlen(ftmix.music.path[ftmix.music.actual]);
	if (ftmix.music.path[ftmix.music.actual][len - 1] != '3' || ftmix.music.path[ftmix.music.actual][len - 2] != 'p' ||
		ftmix.music.path[ftmix.music.actual][len - 3] != 'm' || ftmix.music.path[ftmix.music.actual][len - 4] != '.')
		return;
	if (ms < 0)
	{
		ftmix_set_timer(0);
		return;
	}
	int			i;

	i = Mix_PausedMusic();
	if (ftmix.music.len[ftmix.music.actual] == 0)
	{
		if (ms == 0)
			ftmix_load_music(ftmix.music.path[ftmix.music.actual], 1);
		if (i == 1)
			ftmix_event_pause();
   		return;
	}
	if (ms <= (int)ftmix.music.len[ftmix.music.actual])
	{
		if (Mix_PlayingMusic() == 1)
		{
			Mix_RewindMusic();
			if (i == 0)
				ftmix_event_pause();
			ftmix.music.timer = 0;
		}
		else
		{
			ftmix_load_music(ftmix.music.path[ftmix.music.actual], 1);
			ftmix_event_pause();
		}
		Mix_SetMusicPosition((double)(ms / 1000));
		ftmix.music.timer = ms;
		if (i != 1)
			ftmix_event_pause();
	}
	else
	{
		if (ftmix.music.loop)
		{
			ftmix_load_music(ftmix.music.path[ftmix.music.actual], 1);
			if (i == 1)
				ftmix_event_pause();
		}
		else
			ftmix_event_next();
	}
}

void			ftmix_event_previous(void)
{
	if (!ftmix.music.nb)
		return;
	int			i;
	size_t		len;
	size_t		z = 0;

	len = ft_strlen(ftmix.music.path[ftmix.music.actual]);
	if (ftmix.music.path[ftmix.music.actual][len - 1] == '3' && ftmix.music.path[ftmix.music.actual][len - 2] == 'p' &&
		ftmix.music.path[ftmix.music.actual][len - 3] == 'm' && ftmix.music.path[ftmix.music.actual][len - 4] == '.' && ftmix_get_timer() >= 5000)
		ftmix_set_timer(0);
	else
	{
		if (ftmix.music.loop)
			ftmix.music.loop = SDL_FALSE;
		i = Mix_PausedMusic();
		if (ftmix.music.rand)
		{
			while (z < ftmix.music.nb)
			{
				if (ftmix.music.rand_tab[z] == ftmix.music.actual)
					break;
				z++;
			}
			if (z == 0)
				z = ftmix.music.nb - 1;
			else
				z--;
			ftmix.music.actual = ftmix.music.rand_tab[z];
		}
		else
		{
			if (ftmix.music.actual != 0)
				ftmix.music.actual--;
			else
				ftmix.music.actual = ftmix.music.nb - 1;
		}
		ftmix_load_music(ftmix.music.path[ftmix.music.actual], 1);
		if (Mix_PausedMusic() != i)
			ftmix_event_pause();
	}
}

void			ftmix_event_next(void)
{
	if (!ftmix.music.nb)
		return;
	int			i;
	size_t		z = 0;

	i = Mix_PausedMusic();
	if (ftmix.music.rand)
	{
		while (z < ftmix.music.nb)
		{
			if (ftmix.music.rand_tab[z] == ftmix.music.actual)
				break;
			z++;
		}
		z++;
		if (z == ftmix.music.nb)
			z = 0;
		ftmix.music.actual = ftmix.music.rand_tab[z];
	}
	else
	{
		ftmix.music.actual++;
		if (ftmix.music.actual == ftmix.music.nb)
			ftmix.music.actual = 0;
	}
	ftmix_load_music(ftmix.music.path[ftmix.music.actual], 1);
	if (Mix_PausedMusic() != i)
		ftmix_event_pause();
	if (ftmix.music.loop)
		ftmix.music.loop = SDL_FALSE;
}

_Bool			ftmix_point_in_rect(int px, int py, int rx, int ry, int rw, int rh)
{
	if (px >= rx && px <= rx + rw && py >= ry && py <= ry + rh)
		return (SDL_TRUE);
	return (SDL_FALSE);
}

void			ftmix_event_pause(void)
{
	if (!ftmix.music.nb)
		return;
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
	ftmix.music.timer = SDL_GetTicks() - ftmix.music.timer;
}

void			ftmix_load_music(const char *path, int nb)
{
	if (!ftmix.music.nb)
		return;
	if (ftmix.music.music)
	{
		if (Mix_PlayingMusic() == 1)
			Mix_HaltMusic();
		Mix_FreeMusic(ftmix.music.music);
		ftmix.music.music = NULL;
	}
	ftmix.music.music = Mix_LoadMUS(path);
	Mix_PlayMusic(ftmix.music.music, nb);
	ftmix.music.timer = SDL_GetTicks();
}
