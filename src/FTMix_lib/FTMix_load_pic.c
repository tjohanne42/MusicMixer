#include "FTMix_lib.h"

SDL_Texture		*FTMix_GetTextureFromPic(char *path1, char *path2, SDL_Rect *rect)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	char		*str;

	surface = NULL;
	texture = NULL;
	str = NULL;
	if (!(str = ft_strjoin(path1, path2)))
		FTMix_ExitWithError("ft_strjoin");
	if (!(surface = IMG_Load(str)))
		FTMix_ExitWithError("IMG_Load");
	rect->x = 0;
	rect->y = 0;
	rect->w = surface->w;
	rect->h = surface->h;
	free(str);
	texture = SDL_CreateTextureFromSurface(ftmix.RENDERER, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		FTMix_ExitWithError("SDL_CreateTextureFromSurface");
	return (texture);
}

void			FTMix_load_pic(void)
{
	size_t		i;
	char		*str;
	SDL_Rect	rect;

	FTMix_free_pic();
	ftmix.t_PAUSE = FTMix_GetTextureFromPic(ftmix.DIR_PIC_PATH, "FTMix_pause.png", &rect);
	ftmix.t_PLAY = FTMix_GetTextureFromPic(ftmix.DIR_PIC_PATH, "FTMix_play.png", &rect);
	ftmix.t_VOLUME_LOW = FTMix_GetTextureFromPic(ftmix.DIR_PIC_PATH, "FTMix_volume_low.png", &rect);
	ftmix.t_VOLUME_MID = FTMix_GetTextureFromPic(ftmix.DIR_PIC_PATH, "FTMix_volume_mid.png", &rect);
	ftmix.t_VOLUME_HIGH = FTMix_GetTextureFromPic(ftmix.DIR_PIC_PATH, "FTMix_volume_high.png", &rect);
	ftmix.t_VOLUME_OFF = FTMix_GetTextureFromPic(ftmix.DIR_PIC_PATH, "FTMix_volume_off.png", &rect);
	ftmix.t_POINT = FTMix_GetTextureFromPic(ftmix.DIR_PIC_PATH, "FTMix_point.png", &rect);
	ftmix.t_BASE = FTMix_GetTextureFromPic(ftmix.DIR_PIC_PATH, "FTMix_base.png", &rect);
	if (!(str = ft_strjoin(ftmix.DIR_PIC_PATH, FTMIX_POLICE_NAME)))
		FTMix_ExitWithError("ft_strjoin");
	i = 1;
	while (i <= 19)
	{
		ftmix.FONT[i - 1] = NULL;
		if (!(ftmix.FONT[i - 1] = TTF_OpenFont(str, i)))
			FTMix_ExitWithError("ft_strfreejoin");
		i++;
	}
	free(str);
}
