#include "ftmix_lib.h"

/*static void		ftmix_new_load_animation_on_music(unsigned int want, size_t channel)
{
	size_t		i = 0;
	char		s2[10] = "00000.bmp";
	int			paused;

	if ((paused = Mix_PausedMusic()) != 1)
		ftmix_event_pause();
	if (ftmix.animation.nb[channel] <= 10000)
	{
		while (i < 10)
		{
			s2[i] = s2[i + 1];
			i++;
		}
		i = 0;
	}
	while (i < FTMIX_BUFF_ANIMATION_SIZE)
	{
		if (ftmix.animation.animation[channel][i])
		{
			SDL_DestroyTexture(ftmix.animation.animation[channel][i]);
			ftmix.animation.animation[channel][i] = NULL;
		}
		i++;
	}
	i = 0;
	while (i < FTMIX_BUFF_ANIMATION_SIZE / 2 && i + want < ftmix.animation.nb[channel])
	{
		if (ftmix.animation.nb[channel] > 10000)
		{
			s2[0] = (want + i) / 10000 + '0';
			s2[1] = (want + i) / 1000 % 10 + '0';
			s2[2] = (want + i) / 100 % 10 + '0';
			s2[3] = (want + i) / 10 % 10 + '0';
			s2[4] = (want + i) % 10 + '0';
		}
		else
		{
			s2[0] = (want + i) / 1000 + '0';
			s2[1] = (want + i) / 100 % 10 + '0';
			s2[2] = (want + i) / 10 % 10 + '0';
			s2[3] = (want + i) % 10 + '0';
		}
		if (!(ftmix.animation.animation[channel][i] = ftmix_texture_from_pic(ftmix.animation.path[channel], s2)))
			ftmix_exit_error("ftmix_texture_from_pic");
		i++;
	}
	ftmix.animation.start_pos[channel] = 0;
	ftmix.animation.start_nb[channel] = want;
	ftmix.animation.loaded[channel] = i - 1;
	ftmix.animation.actual[channel] = 0;
	if (paused != 1)
		ftmix_event_pause();
}

static void		ftmix_continue_load_animation_on_music(unsigned int want, size_t channel, unsigned int tmp, int timer)
{
	size_t			i = 0;
	unsigned int	nb;
	char			s2[10] = "00000.bmp";

	ftmix.animation.actual[channel] = (want - ftmix.animation.start_nb[channel] + ftmix.animation.start_pos[channel]) % FTMIX_BUFF_ANIMATION_SIZE;
	if (ftmix.animation.nb[channel] <= 10000)
	{
		while (i < 10)
		{
			s2[i] = s2[i + 1];
			i++;
		}
	}
	i = ftmix.animation.loaded[channel] + 1;
	if (i == FTMIX_BUFF_ANIMATION_SIZE)
		i = 0;
	if (i < ftmix.animation.start_pos[channel])
		nb = i + FTMIX_BUFF_ANIMATION_SIZE - ftmix.animation.start_pos[channel] + ftmix.animation.start_nb[channel];
	else if (i > ftmix.animation.start_pos[channel])
		nb = i - ftmix.animation.start_pos[channel] + ftmix.animation.start_nb[channel];
	else
		nb = ftmix.animation.start_nb[channel] + FTMIX_BUFF_ANIMATION_SIZE;
	size_t		count = 0;
	int			last = 40;
	while (i != ftmix.animation.actual[channel] && nb < ftmix.animation.nb[channel] && (int)SDL_GetTicks() - (int)tmp + last < timer)
	{
		last = SDL_GetTicks();
		ftmix.animation.loaded[channel] = i;
		if (nb == ftmix.animation.start_nb[channel] + FTMIX_BUFF_ANIMATION_SIZE)
		{
			ftmix.animation.start_pos[channel]++;
			if (ftmix.animation.start_pos[channel] == FTMIX_BUFF_ANIMATION_SIZE)
				ftmix.animation.start_pos[channel] = 0;
			ftmix.animation.start_nb[channel]++;
		}
		if (ftmix.animation.nb[channel] > 10000)
		{
			s2[0] = nb / 10000 + '0';
			s2[1] = nb / 1000 % 10 + '0';
			s2[2] = nb / 100 % 10 + '0';
			s2[3] = nb / 10 % 10 + '0';
			s2[4] = nb % 10 + '0';
		}
		else
		{
			s2[0] = nb / 1000 + '0';
			s2[1] = nb / 100 % 10 + '0';
			s2[2] = nb / 10 % 10 + '0';
			s2[3] = nb % 10 + '0';
		}
		if (ftmix.animation.animation[channel][i])
		{
			SDL_DestroyTexture(ftmix.animation.animation[channel][i]);
			ftmix.animation.animation[channel][i] = NULL;
		}
		if (!(ftmix.animation.animation[channel][i] = ftmix_texture_from_pic(ftmix.animation.path[channel], s2)))
			ftmix_exit_error("ftmix_texture_from_pic");
		i++;
		if (i == FTMIX_BUFF_ANIMATION_SIZE)
			i = 0;
		if (i < ftmix.animation.start_pos[channel])
			nb = i + FTMIX_BUFF_ANIMATION_SIZE - ftmix.animation.start_pos[channel] + ftmix.animation.start_nb[channel];
		else if (i > ftmix.animation.start_pos[channel])
			nb = i - ftmix.animation.start_pos[channel] + ftmix.animation.start_nb[channel];
		else
			nb = ftmix.animation.start_nb[channel] + FTMIX_BUFF_ANIMATION_SIZE;
		last = SDL_GetTicks() - last;
		count++;
	}
	if (timer > 0 && (int)SDL_GetTicks() - (int)tmp > timer)
		SDL_Log("too long : %d ms want : %d count = %d", SDL_GetTicks() - tmp, timer, count);
}

void			ftmix_load_animation_on_music(size_t channel, int timer)
{
	unsigned int	tmp = SDL_GetTicks();
	unsigned int	want;
	size_t			max_loaded;

	if (channel >= FTMIX_ANIMATION_MAX || !ftmix.music.nb || !ftmix.animation.nb[channel] ||
		ft_strcmp(ftmix.music.name[ftmix.music.actual], ftmix.animation.music[channel]) != 0)
		return;
	max_loaded = ftmix.animation.start_nb[channel] + ftmix.animation.loaded[channel];
	if (ftmix.animation.loaded[channel] < ftmix.animation.start_pos[channel])
		max_loaded += FTMIX_BUFF_ANIMATION_SIZE - ftmix.animation.start_pos[channel];
	want = ftmix_get_timer() * ftmix.animation.nb[channel] / ftmix.music.len[ftmix.music.actual] % ftmix.animation.nb[channel];
	if (ftmix.animation.stream[channel] == -1)
	{
		ftmix.animation.actual[channel] = want;
		return;
	}
	if (want < ftmix.animation.start_nb[channel] || want > max_loaded)
		ftmix_new_load_animation_on_music(want, channel);
	else if (timer > 40)
		ftmix_continue_load_animation_on_music(want, channel, tmp, timer);
}

_Bool			ftmix_print_animation_on_music(int x, int y, size_t channel)
{
	if (channel >= FTMIX_ANIMATION_MAX || !ftmix.music.nb || !ftmix.animation.nb[channel] ||
		ft_strcmp(ftmix.music.name[ftmix.music.actual], ftmix.animation.music[channel]) != 0)
		return (SDL_FALSE);
	ftmix_PrintTexture(ftmix.animation.animation[channel][ftmix.animation.actual[channel]], x, y);
	return (SDL_TRUE);
}

void		ftmix_init_animation_on_music(const wchar_t *path, const wchar_t *music, size_t nb, size_t channel)
{
	static _Bool	done = SDL_FALSE;
	char		*s1 = NULL;
	SDL_Rect	rect;
	size_t		i = 0;
	char		s2[10] = "00000.bmp";

	if (channel >= FTMIX_ANIMATION_MAX || !ftmix.music.nb)
		return;
	if (!done)
	{
		ftmix_init_animation();
		atexit(ftmix_free_animation);
		done = SDL_TRUE;
	}
	ftmix_free_animation_channel(channel);
	if (!(ftmix.animation.music[channel] = ft_wstrtstr(music)))
		ftmix_exit_error("ft_wstrtstr");
	if (!(s1 = ft_wstrtstr(path)))
		ftmix_exit_error("ft_wstrtstr");
	if (!(ftmix.animation.path[channel] = ft_strjoin(ftmix.pic_folder, s1)))
		ftmix_exit_error("ft_strjoin");
	free(s1);
	ftmix.animation.nb[channel] = nb;
	if (nb <= 10000)
	{
		while (i < 10)
		{
			s2[i] = s2[i + 1];
			i++;
		}
		i = 0;
	}
	if (nb <= FTMIX_BUFF_ANIMATION_SIZE)
	{
		ftmix.animation.stream[channel] = -1;
		if (!(ftmix.animation.animation[channel] = malloc(sizeof(*ftmix.animation.animation[channel]) * (nb + 1))))
			ftmix_exit_error("malloc");
		while (i < nb)
		{
			s2[0] = i / 1000 + '0';
			s2[1] = i / 100 % 10 + '0';
			s2[2] = i / 10 % 10 + '0';
			s2[3] = i % 10 + '0';
			ftmix.animation.animation[channel][i] = NULL;
			if (!(ftmix.animation.animation[channel][i] = ftmix_texture_from_pic(ftmix.animation.path[channel], s2)))
				ftmix_exit_error("ftmix_texture_from_pic");
			i++;
		}
		ftmix.animation.animation[channel][i] = NULL;
	}
	else
	{
		ftmix.animation.stream[channel] = 0;
		if (!(ftmix.animation.animation[channel] = malloc(sizeof(*ftmix.animation.animation[channel]) * FTMIX_BUFF_ANIMATION_SIZE)))
			ftmix_exit_error("malloc");
		while (i < FTMIX_BUFF_ANIMATION_SIZE)
		{
			ftmix.animation.animation[channel][i] = NULL;
			i++;
		}
		i = 0;
		while (i < FTMIX_BUFF_ANIMATION_SIZE / 2)
		{
			if (nb > 10000)
			{
				s2[0] = i / 10000 + '0';
				s2[1] = i / 1000 % 10 + '0';
				s2[2] = i / 100 % 10 + '0';
				s2[3] = i / 10 % 10 + '0';
				s2[4] = i % 10 + '0';
			}
			else
			{
				s2[0] = i / 1000 + '0';
				s2[1] = i / 100 % 10 + '0';
				s2[2] = i / 10 % 10 + '0';
				s2[3] = i % 10 + '0';
			}
			ftmix.animation.animation[channel][i] = NULL;
			if (!(ftmix.animation.animation[channel][i] = ftmix_texture_from_pic(ftmix.animation.path[channel], s2)))
				ftmix_exit_error("ftmix_texture_from_pic");
			i++;
		}
		ftmix.animation.actual[channel] = 0;
		ftmix.animation.loaded[channel] = i - 1;
		ftmix.animation.start_pos[channel] = 0;
		ftmix.animation.start_nb[channel] = 0;
	}
	if (SDL_QueryTexture(ftmix.animation.animation[channel][0], NULL, NULL, &rect.w, &rect.h) != 0)
		ftmix_exit_error("SDL_QueryTexture");
	ftmix.animation.w[channel] = rect.w;
	ftmix.animation.h[channel] = rect.h;
}*/

static void		ftmix_free_animation_channel(size_t channel)
{
	size_t		i = 0;

	if (channel >= FTMIX_ANIMATION_MAX)
		return;
	if (ftmix.animation.animation[channel])
	{
		while (ftmix.animation.animation[channel][i])
		{
			SDL_DestroyTexture(ftmix.animation.animation[channel][i]);
			ftmix.animation.animation[channel][i] = NULL;
			i++;
		}
		free(ftmix.animation.animation[channel]);
		ftmix.animation.animation[channel] = NULL;
	}
	ftmix.animation.nb[channel] = 0;
	ftmix.animation.w[channel] = 0;
	ftmix.animation.h[channel] = 0;
	ftmix.animation.actual[channel] = 0;
	ftmix.animation.len_ms[channel] = 0;
	ftmix.animation.start[channel] = -1;
	ftmix.animation.music[channel] = 0;
}

static void		ftmix_free_animation(void)
{
	size_t		i = 0;

	while (i < FTMIX_ANIMATION_MAX)
	{
		if (ftmix.animation.nb != 0)
			ftmix_free_animation_channel(i);
		i++;
	}
}

static void		ftmix_animation_first_init(void)
{
	size_t		i = 0;

	while (i < FTMIX_ANIMATION_MAX)
	{
		ftmix.animation.animation[i] = NULL;
		ftmix.animation.nb[i] = 0;
		ftmix.animation.len_ms[i] = 0;
		ftmix.animation.w[i] = 0;
		ftmix.animation.h[i] = 0;
		ftmix.animation.actual[i] = 0;
		ftmix.animation.start[i] = -1;
		ftmix.animation.music[i] = 0;
		i++;
	}
}

void			ftmix_print_animation(unsigned int x, unsigned int y, size_t channel)
{
	if (channel >= FTMIX_ANIMATION_MAX || !ftmix.animation.nb[channel])
		return;
	if (ftmix.animation.music[channel])
		ftmix.animation.actual[channel] = ftmix_get_timer() / ftmix.animation.len_ms[channel] % ftmix.animation.nb[channel];
	else
		ftmix.animation.actual[channel] = (SDL_GetTicks() - ftmix.animation.start[channel]) / ftmix.animation.len_ms[channel] % ftmix.animation.nb[channel];
	ftmix_PrintTexture(ftmix.animation.animation[channel][ftmix.animation.actual[channel]], x, y);
}

void			ftmix_init_animation(const wchar_t *path, size_t channel, size_t nb, unsigned int len_ms, const char *format, size_t music)
{
	static _Bool	done = SDL_FALSE;
	char			*s1 = NULL;
	SDL_Rect		rect;
	size_t			i = 0;
	char			s2[9] = "0000.bmp";

	if (channel >= FTMIX_ANIMATION_MAX || !nb || nb > 10000)
		return;
	if (!done)
	{
		ftmix_animation_first_init();
		atexit(ftmix_free_animation);
		done = SDL_TRUE;
	}
	ftmix_free_animation_channel(channel);
	ftmix.animation.nb[channel] = nb;
	if (!(s1 = ft_wstrtstr(path)))
		ftmix_exit_error("ft_wstrtstr");
	if (!ft_strfreejoin(&s1, ftmix.pic_folder, 's'))
		ftmix_exit_error("ft_strfreejoin");
	if (!(ftmix.animation.animation[channel] = malloc(sizeof(*ftmix.animation.animation) * (nb + 1))))
		ftmix_exit_error("malloc");
	if (format && !ft_strcmp("png", format))
	{
		s2[6] = 'p';
		s2[7] = 'n';
		s2[8] = 'g';
	}
	while (i < nb)
	{
		s2[0] = i / 1000 + '0';
		s2[1] = i / 100 % 10 + '0';
		s2[2] = i / 10 % 10 + '0';
		s2[3] = i % 10 + '0';
		ftmix.animation.animation[channel][i] = ftmix_texture_from_pic(s1, s2);
		i++;
	}
	free(s1);
	ftmix.animation.len_ms[channel] = len_ms;
	ftmix.animation.animation[channel][i] = NULL;
	ftmix.animation.actual[channel] = 0;
	ftmix.animation.start[channel] = -1;
	if (SDL_QueryTexture(ftmix.animation.animation[channel][0], NULL, NULL, &rect.w, &rect.h) != 0)
		ftmix_exit_error("SDL_QueryTexture");
	ftmix.animation.w[channel] = rect.w;
	ftmix.animation.h[channel] = rect.h;
	if (music)
		ftmix.animation.music[channel] = music;
}
