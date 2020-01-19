#include "FTMix_lib.h"

static void		FTMix_print_timer(int x, int y, int timer_ms)
{
	char		timer[18];
	char		*str;
	size_t		len;
	size_t		i;
	size_t		z;

	if (!ftmix.MUSIC_NB)
	{
		FTMix_PrintTextCenterY("-/-", x + 210, y + 40, ftmix.FONT[13], ftmix.COLOR1.r, ftmix.COLOR1.g, ftmix.COLOR1.b, ftmix.COLOR1.a);
		return;
	}
	if (!(str = ft_mststr(timer_ms)))
		FTMix_ExitWithError("ft_mststr");
	if (ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL] == 0)
	{
		FTMix_PrintTextCenterY(str, x + 210, y + 40, ftmix.FONT[13], ftmix.COLOR1.r, ftmix.COLOR1.g, ftmix.COLOR1.b, ftmix.COLOR1.a);
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
	if (!(str = ft_mststr(ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL])))
		FTMix_ExitWithError("ft_mststr");
	len += ft_strlen(str);
	z = 0;
	while (i + z < len + 1)
	{
		timer[i + z] = str[z];
		z++;
	}
	timer[i + z] = '\0';
	free(str);
	FTMix_PrintTextCenterY(timer, x + 210, y + 40, ftmix.FONT[13], ftmix.COLOR1.r, ftmix.COLOR1.g, ftmix.COLOR1.b, ftmix.COLOR1.a);
}

void			FTMix_print(int x, int y)
{
	int			timer;

	if (x >= 0 && y >= 0)
	{
		ftmix.POS_X = x;
		ftmix.POS_Y = y;
	}
	else
	{
		x = ftmix.POS_X;
		y = ftmix.POS_Y;
	}
	timer = FTMix_get_timer();
	FTMix_FillRect(x, y, 350, 90, ftmix.COLOR1.r, ftmix.COLOR1.g, ftmix.COLOR1.b, ftmix.COLOR1.a);
	if (!ftmix.MUSIC_NB || ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL] == 0)
	{
		FTMix_FillRect(x + 20, y + 5, 290, 20, ftmix.COLOR2.r, ftmix.COLOR2.g, ftmix.COLOR2.b, ftmix.COLOR2.a);
	}
	else if (timer * 290 / ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL] < 290)
	{
		FTMix_FillRect(x + 20 + timer * 290 / ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL], y + 5, 290 - timer * 290 / ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL], 20,
		 ftmix.COLOR2.r, ftmix.COLOR2.g, ftmix.COLOR2.b, ftmix.COLOR2.a);
	}
	FTMix_FillRect(x + 140 + ftmix.VOLUME * 50 / MIX_MAX_VOLUME, y + 25, 60 - ftmix.VOLUME * 50 / MIX_MAX_VOLUME, 30,
		 ftmix.COLOR2.r, ftmix.COLOR2.g, ftmix.COLOR2.b, ftmix.COLOR2.a);
	if (!ftmix.LOOP)
		FTMix_FillRect(x + 280, y + 25, 30, 30, ftmix.COLOR2.r, ftmix.COLOR2.g, ftmix.COLOR2.b, ftmix.COLOR2.a);
	if (ftmix.BUBBLE == SDL_TRUE)
		FTMix_FillRect(x + 320, y + 30, 30, 30, ftmix.COLOR1.r, ftmix.COLOR1.g, ftmix.COLOR1.b, ftmix.COLOR1.a);
	else
		FTMix_FillRect(x + 320, y + 30, 30, 30, ftmix.COLOR2.r, ftmix.COLOR2.g, ftmix.COLOR2.b, ftmix.COLOR2.a);
	FTMix_FillRect(x + 320, y, 30, 30, ftmix.COLOR2.r, ftmix.COLOR2.g, ftmix.COLOR2.b, ftmix.COLOR2.a);
	// AFFICHAGE DU MIXEUR
	FTMix_PrintTexture(ftmix.t_BASE, x, y);
	// POINT SUR TIMER_LINE
	if (!ftmix.MUSIC_NB || ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL] == 0)
		FTMix_PrintTexture(ftmix.t_POINT, x + 10, y + 10);
	else
		FTMix_PrintTexture(ftmix.t_POINT, x + 10 + timer * 290 / ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL], y + 10);

	// PLAY
	if (Mix_PausedMusic() == 1)
		FTMix_PrintTexture(ftmix.t_PLAY, x + 40, y + 25);
	else
		FTMix_PrintTexture(ftmix.t_PAUSE, x + 40, y + 25);
	// VOLUME
	if (!ftmix.VOLUME)
		FTMix_PrintTexture(ftmix.t_VOLUME_OFF, x + 100, y + 25);
	else if (ftmix.VOLUME < MIX_MAX_VOLUME / 3)
		FTMix_PrintTexture(ftmix.t_VOLUME_LOW, x + 100, y + 25);
	else if (ftmix.VOLUME < MIX_MAX_VOLUME * 2 / 3)
		FTMix_PrintTexture(ftmix.t_VOLUME_MID, x + 100, y + 25);
	else
		FTMix_PrintTexture(ftmix.t_VOLUME_HIGH, x + 100, y + 25);
	// POINT SUR VOLUME_LINE
	FTMix_PrintTexture(ftmix.t_POINT, x + 140 + ftmix.VOLUME * 50 / MIX_MAX_VOLUME, y + 35);
	// AFFICHAGE DU TIMER
	FTMix_print_timer(x, y, timer);
	// AFFICHAGE DU MUSIC_NAME
	if (ftmix.MUSIC_NB)
		FTMix_PrintSurfaceCenterXY(ftmix.MUSIC_NAME[ftmix.MUSIC_ACTUAL], x + 160, y + 68);
	else
		FTMix_PrintSurfaceCenterXY(ftmix.MUSIC_NAME[0], x + 160, y + 68);
	
}
