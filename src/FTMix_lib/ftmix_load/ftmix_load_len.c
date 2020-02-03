#include "ftmix_lib.h"

static int		ftmix_wav_len(size_t i)
{
	FILE 		*fichier = NULL;
	int			ret;

	if (!(fichier = fopen(ftmix.music.path[i], "r")))
		ftmix_exit_error("fopen");
	if (fseek(fichier, 0, SEEK_END) != 0)
		ftmix_exit_error("fseek");
	if ((ret = ftell(fichier)) == -1)
		ftmix_exit_error("ftell");
	fclose(fichier);
	return (ret * 10 / 2 / 2 / 441);
}

void			ftmix_load_len(void)
{
	size_t		i = 0;
	size_t		y = 32;
	size_t		z;
	size_t		len;

	if (!ftmix.music.nb)
		return;
	z = Mix_PausedMusic();
	if (z == 1)
		ftmix_event_pause();
	Mix_VolumeMusic(0);
	if (!(ftmix.music.len = malloc(sizeof(*ftmix.music.len) * ftmix.music.nb)))
		ftmix_exit_error("malloc");
	while (i < ftmix.music.nb)
	{
		ftmix_print_while_loading();
		len = ft_strlen(ftmix.music.path[i]);
		if (ftmix.music.path[i][len - 1] == '3' && ftmix.music.path[i][len - 2] == 'p' && ftmix.music.path[i][len - 3] == 'm' && ftmix.music.path[i][len - 4] == '.')
		{
			ftmix_load_music(ftmix.music.path[i], 1);
			ftmix.music.len[i] = 3 * 60 * 1000;
			Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
			SDL_Delay(y);
			while (Mix_PlayingMusic() == 1)
			{
				ftmix.music.len[i] += 3 * 60 * 1000;
				Mix_RewindMusic();
				Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
				SDL_Delay(y);
			}
			ftmix_load_music(ftmix.music.path[i], 1);
			ftmix.music.len[i] -= 3 * 60 * 1000;
			Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
			SDL_Delay(y);
			while (Mix_PlayingMusic() == 1)
			{
				ftmix.music.len[i] += 60 * 1000;
				Mix_RewindMusic();
				Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
				SDL_Delay(y);
			}
			ftmix_load_music(ftmix.music.path[i], 1);
			ftmix.music.len[i] -= 30 * 1000;
			Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
			SDL_Delay(y);
			ftmix_print_while_loading();
			if (Mix_PlayingMusic() != 1)
			{
				ftmix_load_music(ftmix.music.path[i], 1);
				ftmix.music.len[i] -= 15 * 1000;
				Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
				SDL_Delay(y);
				if (Mix_PlayingMusic() != 1)
				{
					ftmix_load_music(ftmix.music.path[i], 1);
					ftmix.music.len[i] -= 15 * 1000;
					Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
					SDL_Delay(y);
				}
				while (Mix_PlayingMusic() == 1)
				{
					ftmix.music.len[i] += 1000;
					Mix_RewindMusic();
					Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
					SDL_Delay(y);
				}
			}
			else
			{
				ftmix.music.len[i] += 15 * 1000;
				Mix_RewindMusic();
				Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
				SDL_Delay(y);
				if (Mix_PlayingMusic() != 1)
				{
					ftmix_load_music(ftmix.music.path[i], 1);
					ftmix.music.len[i] -= 15 * 1000;
					Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
					SDL_Delay(y);
				}
				while (Mix_PlayingMusic() == 1)
				{
					ftmix.music.len[i] += 1000;
					Mix_RewindMusic();
					Mix_SetMusicPosition((double)(ftmix.music.len[i] / 1000));
					SDL_Delay(y);
				}
			}
			ftmix.music.len[i] -= 1000;
		}
		else if (ftmix.music.path[i][len - 1] == 'v' && ftmix.music.path[i][len - 2] == 'a' && ftmix.music.path[i][len - 3] == 'w' && ftmix.music.path[i][len - 4] == '.')
			ftmix.music.len[i] = ftmix_wav_len(i);
		else
			ftmix.music.len[i] = 0;
		i++;
	}
	Mix_VolumeMusic(ftmix.music.volume);
	if (z == 1)
		ftmix_event_pause();
}
