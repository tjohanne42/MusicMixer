#include "ftmix_lib.h"

void			ftmix_load_name(void)
{
	size_t		i = 0;
	char		*tmp = NULL;
	size_t		z;
	size_t		len;

	if (ftmix.music.nb == 0)
		return;
	if (!(ftmix.music.name = malloc(sizeof(*ftmix.music.name) * ftmix.music.nb)))
		ftmix_exit_error("malloc");
	while (i < ftmix.music.nb)
	{
		len = ft_strlen(ftmix.music.path[i]);
		if (!(tmp = malloc(sizeof(*tmp) * (len + 1))))
			ftmix_exit_error("malloc");
		ft_strncpy(tmp, ftmix.music.path[i], len);
		while (tmp[len] != '.')
			len--;
		tmp[len] = '\0';
		while (tmp[len] != '/' && len > 0)
			len--;
		if (len > 0)
		{
			z = 0;
			while (tmp[z + len + 1])
			{
				tmp[z] = tmp[z + len + 1];
				z++;
			}
			tmp[z] = '\0';
		}
		ftmix.music.name[i] = NULL;
		len = ft_strlen(tmp);
		if (!(ftmix.music.name[i] = malloc(sizeof(*ftmix.music.name[i]) * (len + 1))))
			ftmix_exit_error("malloc");
		ft_strncpy(ftmix.music.name[i], tmp, len);
		free(tmp);
		tmp = NULL;
		i++;
	}
	if (!(ftmix.music.s_name = malloc(sizeof(*ftmix.music.s_name) * ftmix.music.nb)))
		ftmix_exit_error("malloc");
	i = 0;
	while (i < ftmix.music.nb)
	{
		ftmix.music.s_name[i] = NULL;
		z = 18;
		if (!(ftmix.music.s_name[i] = TTF_RenderText_Blended(ftmix.font[z], ftmix.music.name[i], ftmix.color1)))
			ftmix_exit_error("TTF_RenderText_Blended");
		z--;
		while ((ftmix.music.s_name[i]->w > 300 || ftmix.music.s_name[i]->h > 31) && z > 0)
		{
			SDL_FreeSurface(ftmix.music.s_name[i]);
			ftmix.music.s_name[i] = NULL;
			if (!(ftmix.music.s_name[i] = TTF_RenderText_Blended(ftmix.font[z], ftmix.music.name[i], ftmix.color1)))
				ftmix_exit_error("TTF_RenderText_Blended");
			z--;
		}
		i++;
	}
}
