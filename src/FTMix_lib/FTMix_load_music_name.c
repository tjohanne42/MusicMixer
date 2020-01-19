#include "FTMix_lib.h"

void			FTMix_load_music_name(void)
{
	char		**music_name;
	size_t		len_path;
	size_t		i;
	size_t		z;
	size_t		x;

	FTMix_free_music_name();
	if (!ftmix.MUSIC_NB)
	{
		if (!(ftmix.MUSIC_NAME = malloc(sizeof(*ftmix.MUSIC_NAME) * 1)))
			FTMix_ExitWithError("malloc");
		z = 18;
		if (!(ftmix.MUSIC_NAME[0] = TTF_RenderText_Blended(ftmix.FONT[z], "... - ...", ftmix.COLOR1)))
			FTMix_ExitWithError("TTF_RenderText_Blended");
		z--;
		while ((ftmix.MUSIC_NAME[0]->w > 300 || ftmix.MUSIC_NAME[0]->h > 31) && z > 0)
		{
			if (!(ftmix.MUSIC_NAME[0] = TTF_RenderText_Blended(ftmix.FONT[z], "... - ...", ftmix.COLOR1)))
				FTMix_ExitWithError("TTF_RenderText_Blended");
			z--;
		}
		return;
	}
	music_name = NULL;
	if (!(music_name = malloc(sizeof(*music_name) * ftmix.MUSIC_NB)))
		FTMix_ExitWithError("malloc");
	i = 0;
	while (i < ftmix.MUSIC_NB)
	{
		music_name[i] = NULL;
		len_path = ft_strlen(ftmix.MUSIC_PATH[i]);
		x = 1;
		while (len_path >= x && ftmix.MUSIC_PATH[i][len_path - x] != L'/')
			x++;
		x--;
		if (!(music_name[i] = malloc(sizeof(*music_name[i]) * (x - 3))))
			FTMix_ExitWithError("malloc");
		z = 0;
		while (x - z > 4)
		{
			music_name[i][z] = ftmix.MUSIC_PATH[i][len_path - x + z];
			z++;
		}
		music_name[i][z] = L'\0';
		i++;
	}
	if (!(ftmix.MUSIC_NAME = malloc(sizeof(*ftmix.MUSIC_NAME) * ftmix.MUSIC_NB)))
		FTMix_ExitWithError("malloc");
	i = 0;
	while (i < ftmix.MUSIC_NB)
	{
		z = 18;
		if (!(ftmix.MUSIC_NAME[i] = TTF_RenderText_Blended(ftmix.FONT[z], music_name[i], ftmix.COLOR1)))
			FTMix_ExitWithError("TTF_RenderText_Blended");
		z--;
		while ((ftmix.MUSIC_NAME[i]->w > 300 || ftmix.MUSIC_NAME[i]->h > 31) && z > 0)
		{
			if (!(ftmix.MUSIC_NAME[i] = TTF_RenderText_Blended(ftmix.FONT[z], music_name[i], ftmix.COLOR1)))
				FTMix_ExitWithError("TTF_RenderText_Blended");
			z--;
		}
		i++;
	}
	i = 0;
	while (i < ftmix.MUSIC_NB)
	{
		free(music_name[i]);
		i++;
	}
	free(music_name);
}
