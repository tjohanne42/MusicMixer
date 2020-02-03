#include "ftmix_lib.h"

SDL_Texture		*ftmix_texture_from_pic(char *s1, char *s2)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	char		*str;

	surface = NULL;
	texture = NULL;
	if (s2 && s2[0] != '\0')
	{
		str = NULL;
		if (!(str = ft_strjoin(s1, s2)))
			ftmix_exit_error("ft_strjoin");
		if (!(surface = IMG_Load(str)))
			ftmix_exit_error("IMG_Load");
		free(str);
	}
	else
	{
		if (!(surface = IMG_Load(s1)))
			ftmix_exit_error("IMG_Load");
	}
	texture = SDL_CreateTextureFromSurface(ftmix.renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		ftmix_exit_error("SDL_CreateTextureFromSurface");
	return (texture);
}

void			ftmix_load_texture(void)
{
	size_t		i = 1;
	char		*str = NULL;
	size_t		y = 54;

	ftmix.loading_text[0] = NULL;
	ftmix.loading_text[1] = NULL;
	ftmix.loading_text[2] = NULL;
	if (!(str = ft_strjoin(ftmix.pic_folder, FTMIX_POLICE_NAME)))
		ftmix_exit_error("ft_strjoin");
	if (!(ftmix.font = malloc(sizeof(*ftmix.font) * 100)))
		ftmix_exit_error("malloc");
	ftmix.font[y] = NULL;
	if (!(ftmix.font[y] = TTF_OpenFont(str, y + 1)))
		ftmix_exit_error("TTF_OpenFont");
	if (!(ftmix.loading_text[0] = TTF_RenderText_Blended(ftmix.font[y], "Loading .", ftmix.color1)))
		ftmix_exit_error("TTF_RenderText_Blended");
	if (!(ftmix.loading_text[1] = TTF_RenderText_Blended(ftmix.font[y], "Loading . .", ftmix.color1)))
		ftmix_exit_error("TTF_RenderText_Blended");
	if (!(ftmix.loading_text[2] = TTF_RenderText_Blended(ftmix.font[y], "Loading . . .", ftmix.color1)))
		ftmix_exit_error("TTF_RenderText_Blended");
	ftmix_print_while_loading();
	while (i <= 100)
	{
		if (i == y)
			i++;
		ftmix.font[i - 1] = NULL;
		if (!(ftmix.font[i - 1] = TTF_OpenFont(str, i)))
			ftmix_exit_error("TTF_OpenFont");
		i++;
	}
	free(str);
	ftmix.texture.play = ftmix_texture_from_pic(ftmix.pic_folder, "ftmix_play.png");
	ftmix.texture.pause = ftmix_texture_from_pic(ftmix.pic_folder, "ftmix_pause.png");
	ftmix.texture.volume_low = ftmix_texture_from_pic(ftmix.pic_folder, "ftmix_volume_low.png");
	ftmix.texture.volume_mid = ftmix_texture_from_pic(ftmix.pic_folder, "ftmix_volume_mid.png");
	ftmix.texture.volume_high = ftmix_texture_from_pic(ftmix.pic_folder, "ftmix_volume_high.png");
	ftmix.texture.volume_off = ftmix_texture_from_pic(ftmix.pic_folder, "ftmix_volume_off.png");
	ftmix.texture.point = ftmix_texture_from_pic(ftmix.pic_folder, "ftmix_point.png");
	ftmix.texture.mixer = ftmix_texture_from_pic(ftmix.pic_folder, "ftmix_mixer.png");
}
