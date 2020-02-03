#include "ftmix_lib.h"

static void		ftmix_print_timer(int x, int y, int timer_ms)
{
	char		timer[18];
	char		*str;
	size_t		len;
	size_t		i;
	size_t		z;

	if (!ftmix.music.nb)
	{
		ftmix_PrintTextCenterY("-/-", x + 210, y + 40, ftmix.font[14], ftmix.color1.r, ftmix.color1.g, ftmix.color1.b, ftmix.color1.a);
		return;
	}
	if (!(str = ft_mststr(timer_ms)))
		ftmix_exit_error("ft_mststr");
	if (ftmix.music.len[ftmix.music.actual] == 0)
	{
		ftmix_PrintTextCenterY(str, x + 210, y + 40, ftmix.font[14], ftmix.color1.r, ftmix.color1.g, ftmix.color1.b, ftmix.color1.a);
		free(str);
		return;
	}
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		timer[i] = str[i];
		i++;
	}
	timer[i++] = '/';
	free(str);
	str = NULL;
	if (!(str = ft_mststr(ftmix.music.len[ftmix.music.actual])))
		ftmix_exit_error("ft_mststr");
	len += ft_strlen(str);
	z = 0;
	while (i + z < len + 1)
	{
		timer[i + z] = str[z];
		z++;
	}
	timer[i + z] = '\0';
	free(str);
	ftmix_PrintTextCenterY(timer, x + 210, y + 40, ftmix.font[14], ftmix.color1.r, ftmix.color1.g, ftmix.color1.b, ftmix.color1.a);
}

static void		ftmix_free_bubble(void)
{
	size_t		i = 0;

	while (i < ftmix.bubble.nb - 1)
	{
		ftmix.bubble.x[i] = ftmix.bubble.x[i + 1];
		ftmix.bubble.y[i] = ftmix.bubble.y[i + 1];
		ftmix.bubble.start[i] = ftmix.bubble.start[i + 1];
		ftmix.bubble.color[i].r = ftmix.bubble.color[i + 1].r;
		ftmix.bubble.color[i].g = ftmix.bubble.color[i + 1].g;
		ftmix.bubble.color[i].b = ftmix.bubble.color[i + 1].b;
		ftmix.bubble.color[i].a = ftmix.bubble.color[i + 1].a;
		i++;
	}
	ftmix.bubble.nb--;
}

static void		ftmix_print_bubble(unsigned int timer)
{
	size_t		i = 0;
	size_t		time_max = 700;
	int			r_max = 50;
	int			r;

	while (ftmix.bubble.nb > 0 && timer - ftmix.bubble.start[0] > time_max)
		ftmix_free_bubble();
	while (i < ftmix.bubble.nb)
	{
		r = (timer - ftmix.bubble.start[i]) * r_max / time_max;
		ftmix_PrintCercle(ftmix.bubble.x[i], ftmix.bubble.y[i], r, ftmix.bubble.color[i]);
		ftmix_PrintCercle(ftmix.bubble.x[i], ftmix.bubble.y[i], r + 1, ftmix.bubble.color[i]);
		ftmix_PrintCercle(ftmix.bubble.x[i], ftmix.bubble.y[i], r + 2, ftmix.bubble.color[i]);
		i++;
	}
}

void			ftmix_print(int x, int y)
{
	int			timer;

	ftmix.pos_x = x;
	ftmix.pos_y = y;
	timer = ftmix_get_timer();
	ftmix_FillRect(x, y, 350, 90, ftmix.color1.r, ftmix.color1.g, ftmix.color1.b, ftmix.color1.a);
	if (!ftmix.music.nb || ftmix.music.len[ftmix.music.actual] == 0)
		ftmix_FillRect(x + 20, y + 5, 290, 20, ftmix.color2.r, ftmix.color2.g, ftmix.color2.b, ftmix.color2.a);
	else if (timer * 290 / ftmix.music.len[ftmix.music.actual] < 290)
	{
		ftmix_FillRect(x + 20 + timer * 290 / ftmix.music.len[ftmix.music.actual], y + 5, 290 - timer * 290 / ftmix.music.len[ftmix.music.actual], 20,
		 ftmix.color2.r, ftmix.color2.g, ftmix.color2.b, ftmix.color2.a);
	}
	ftmix_FillRect(x + 140 + ftmix.music.volume * 50 / MIX_MAX_VOLUME, y + 25, 60 - ftmix.music.volume * 50 / MIX_MAX_VOLUME, 30,
		 ftmix.color2.r, ftmix.color2.g, ftmix.color2.b, ftmix.color2.a);
	if (!ftmix.music.loop)
		ftmix_FillRect(x + 280, y + 25, 30, 30, ftmix.color2.r, ftmix.color2.g, ftmix.color2.b, ftmix.color2.a);
	ftmix_FillRect(x + 320, y, 30, 30, ftmix.color2.r, ftmix.color2.g, ftmix.color2.b, ftmix.color2.a);
	if (!ftmix.music.rand)
		ftmix_FillRect(x + 320, y + 30, 30, 30, ftmix.color2.r, ftmix.color2.g, ftmix.color2.b, ftmix.color2.a);
	if (!ftmix.bubble.bubble)
		ftmix_FillRect(x + 320, y + 60, 30, 30, ftmix.color2.r, ftmix.color2.g, ftmix.color2.b, ftmix.color2.a);
	// AFFICHAGE DU MIXEUR
	ftmix_PrintTexture(ftmix.texture.mixer, x, y);
	// point SUR TIMER_LINE
	if (!ftmix.music.nb || ftmix.music.len[ftmix.music.actual] == 0)
		ftmix_PrintTexture(ftmix.texture.point, x + 10, y + 10);
	else
		ftmix_PrintTexture(ftmix.texture.point, x + 10 + timer * 290 / ftmix.music.len[ftmix.music.actual], y + 10);

	// PLAY
	if (Mix_PausedMusic() == 1)
		ftmix_PrintTexture(ftmix.texture.play, x + 40, y + 25);
	else
		ftmix_PrintTexture(ftmix.texture.pause, x + 40, y + 25);
	// VOLUME
	if (!ftmix.music.volume)
		ftmix_PrintTexture(ftmix.texture.volume_off, x + 100, y + 25);
	else if (ftmix.music.volume < MIX_MAX_VOLUME / 3)
		ftmix_PrintTexture(ftmix.texture.volume_low, x + 100, y + 25);
	else if (ftmix.music.volume < MIX_MAX_VOLUME * 2 / 3)
		ftmix_PrintTexture(ftmix.texture.volume_mid, x + 100, y + 25);
	else
		ftmix_PrintTexture(ftmix.texture.volume_high, x + 100, y + 25);
	// point SUR VOLUME_LINE
	ftmix_PrintTexture(ftmix.texture.point, x + 140 + ftmix.music.volume * 50 / MIX_MAX_VOLUME, y + 35);
	// AFFICHAGE DU TIMER
	ftmix_print_timer(x, y, timer);
	// AFFICHAGE DU MUSIC_NAME
	if (ftmix.music.nb)
		ftmix_PrintSurfaceCenterXY(ftmix.music.s_name[ftmix.music.actual], x + 160, y + 68);
	else
		ftmix_PrintSurfaceCenterXY(ftmix.music.s_name[0], x + 160, y + 68);
	// AFFICHAGE BUBBLE
	if (ftmix.bubble.bubble)
		ftmix_print_bubble(SDL_GetTicks());
}
