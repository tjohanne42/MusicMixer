#include "FTMix_lib.h"

/*static void		FTMix_load_animation(size_t channel)
{
	SDL_Rect	rect;
	char		s2[10] = "00000.bmp";

	if (ftmix.ANIMATION_NB[channel] > 10000)
	{
		s2[0] = ftmix.ANIMATION_ACTUAL[channel] / 10000 + '0';
		s2[1] = ftmix.ANIMATION_ACTUAL[channel] / 1000 % 10 + '0';
		s2[2] = ftmix.ANIMATION_ACTUAL[channel] / 100 % 10 + '0';
		s2[3] = ftmix.ANIMATION_ACTUAL[channel] / 10 % 10 + '0';
		s2[4] = ftmix.ANIMATION_ACTUAL[channel] % 10 + '0';
	}
	else
	{
		size_t		i = 0;
		while (i < 10)
		{
			s2[i] = s2[i + 1];
			i++;
		}
		s2[0] = ftmix.ANIMATION_ACTUAL[channel] / 1000 + '0';
		s2[1] = ftmix.ANIMATION_ACTUAL[channel] / 100 % 10 + '0';
		s2[2] = ftmix.ANIMATION_ACTUAL[channel] / 10 % 10 + '0';
		s2[3] = ftmix.ANIMATION_ACTUAL[channel] % 10 + '0';
	}

	if (ftmix.ANIMATION[channel])
		SDL_DestroyTexture(ftmix.ANIMATION[channel]);
	ftmix.ANIMATION[channel] = NULL;
	if (!(ftmix.ANIMATION[channel] = FTMix_GetTextureFromPic(ftmix.ANIMATION_PATH[channel], s2, &rect)))
		FTMix_ExitWithError("FTMix_GetTextureFromPic");
	ftmix.ANIMATION_W[channel] = rect.w;
	ftmix.ANIMATION_H[channel] = rect.h;
}

void			FTMix_print_animation(int x, int y, size_t channel)
{
	unsigned int	timer;
	static unsigned int		test = 0;;

	if (channel >= FTMIX_ANIMATION_MAX)
		return;
	if (test == 0)
		test = SDL_GetTicks();
	if (ftmix.ANIMATION_LAST[channel] == 0)
		ftmix.ANIMATION_LAST[channel] = SDL_GetTicks();
	else
	{
		timer = (SDL_GetTicks() - ftmix.ANIMATION_LAST[channel]) * (1000 / (ftmix.ANIMATION_LEN[channel] / ftmix.ANIMATION_NB[channel])) / 1000 % ftmix.ANIMATION_NB[channel];
		if (timer != ftmix.ANIMATION_ACTUAL[channel])
		{
			ftmix.ANIMATION_ACTUAL[channel] = timer;
			FTMix_load_animation(channel);
		}
	}
	if (SDL_GetTicks() - test >= ftmix.ANIMATION_LEN[channel] / ftmix.ANIMATION_NB[channel])
		FTMix_PrintTexture(ftmix.ANIMATION[channel], x, y);
}

void		FTMix_init_animation(const wchar_t *str, size_t nb, unsigned int len, size_t channel)
{
	size_t		i = 0;
	char		*s1 = NULL;
	char		*s3 = NULL;

	if (channel >= FTMIX_ANIMATION_MAX)
		return;
	FTMix_free_animation_channel(channel);
	ftmix.ANIMATION_ACTUAL[channel] = 0;
	ftmix.ANIMATION_NB[channel] = nb;
	ftmix.ANIMATION_LEN[channel] = len;
	ftmix.ANIMATION_LAST[channel] = 0;
	if (!(s3 = ft_wstrtstr(str)))
		FTMix_ExitWithError("ft_wstrtstr");
	if (!(s1 = ft_strjoin(ftmix.DIR_PIC_PATH, s3)))
		FTMix_ExitWithError("ft_strjoin");
	i = ft_strlen(s1);
	if (!(ftmix.ANIMATION_PATH[channel] = malloc(sizeof(*ftmix.ANIMATION_PATH[channel]) * (i + 1))))
		FTMix_ExitWithError("malloc");
	ft_strncpy(ftmix.ANIMATION_PATH[channel], s1, i);
	FTMix_load_animation(channel);
	free(s1);
	free(s3);
}*/

void			FTMix_print_animation_on_music(int x, int y, size_t channel)
{
	unsigned int			actual;

	if (channel >= FTMIX_ANIMATION_MAX)
		return;
	actual = FTMix_get_timer() * ftmix.ANIMATION_NB[channel] / ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL] % ftmix.ANIMATION_NB[channel];
	FTMix_PrintTexture(ftmix.ANIMATION[channel][actual], x, y);
}

void		FTMix_init_animation_on_music(const wchar_t *str, size_t nb, unsigned int len, size_t channel)
{
	size_t		i = 0;
	char		*s1 = NULL;
	char		*s3 = NULL;

	if (channel >= FTMIX_ANIMATION_MAX)
		return;
	FTMix_free_animation_channel(channel);
	ftmix.ANIMATION_NB[channel] = nb;
	ftmix.ANIMATION_LEN[channel] = len;
	if (!(s3 = ft_wstrtstr(str)))
		FTMix_ExitWithError("ft_wstrtstr");
	if (!(s1 = ft_strjoin(ftmix.DIR_PIC_PATH, s3)))
		FTMix_ExitWithError("ft_strjoin");
	ftmix.ANIMATION[channel] = NULL;
	if (!(ftmix.ANIMATION[channel] = malloc(sizeof(*ftmix.ANIMATION[channel]) * nb)))
		FTMix_ExitWithError("malloc");
	SDL_Rect	rect;
	char		s2[10] = "00000.bmp";

	if (ftmix.ANIMATION_NB[channel] <= 10000)
	{
		i = 0;
		while (i < 10)
		{
			s2[i] = s2[i + 1];
			i++;
		}
	}
	i = 0;
	while (i < ftmix.ANIMATION_NB[channel])
	{
		if (ftmix.ANIMATION_NB[channel] > 10000)
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
		ftmix.ANIMATION[channel][i] = NULL;
		if (!(ftmix.ANIMATION[channel][i] = FTMix_GetTextureFromPic(s1, s2, &rect)))
			FTMix_ExitWithError("FTMix_GetTextureFromPic");
		ftmix.ANIMATION_W[channel] = rect.w;
		ftmix.ANIMATION_H[channel] = rect.h;
		FTMix_print_while_loading();
		i++;
	}
	free(s1);
	free(s3);
}
