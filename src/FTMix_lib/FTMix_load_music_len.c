#include "FTMix_lib.h"

static void		FTMix_pause(size_t y)
{
	SDL_Delay(y);
}

void			FTMix_load_music_len(void)
{
	size_t		i;
	size_t		z = 0;

	if (!ftmix.MUSIC_NB)
		return;
	FTMix_free_music_len();
	if (!(ftmix.MUSIC_LEN = malloc(sizeof(*ftmix.MUSIC_LEN) * ftmix.MUSIC_NB)))
		FTMix_ExitWithError("malloc");
	Mix_VolumeMusic(0);
	i = 0;
	size_t		y = 32;
	if ((z = Mix_PausedMusic()) == 1)
		FTMix_event_pause();
	size_t		len;
	while (i < ftmix.MUSIC_NB)
	{
		len = ft_strlen(ftmix.MUSIC_PATH[i]);
		if (ftmix.MUSIC_PATH[i][len - 1] == '3' && ftmix.MUSIC_PATH[i][len - 2] == 'p' && ftmix.MUSIC_PATH[i][len - 3] == 'm' && ftmix.MUSIC_PATH[i][len - 4] == '.')
		{
			FTMix_print_while_loading();
			FTMix_load_music(ftmix.MUSIC_PATH[i]);
			SDL_Delay(1);
			ftmix.MUSIC_LEN[i] = 3 * 60 * 1000;
			Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
			FTMix_pause(y);
			while (Mix_PlayingMusic() == 1)
			{
				ftmix.MUSIC_LEN[i] += 3 * 60 * 1000;
				Mix_RewindMusic();
				SDL_Delay(1);
				Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
				FTMix_pause(y);
			}
			FTMix_print_while_loading();
			Mix_PlayMusic(ftmix.MUSIC, 1);
			SDL_Delay(1);
			ftmix.MUSIC_LEN[i] -= 3 * 60 * 1000;
			while (Mix_PlayingMusic() == 1)
			{
				ftmix.MUSIC_LEN[i] += 60 * 1000;
				Mix_RewindMusic();
				SDL_Delay(1);
				Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
				FTMix_pause(y);
			}
			FTMix_print_while_loading();
			Mix_PlayMusic(ftmix.MUSIC, 1);
			SDL_Delay(1);
			ftmix.MUSIC_LEN[i] -= 30 * 1000;
			Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
			FTMix_pause(y);
			if (Mix_PlayingMusic() != 1)
			{
				Mix_PlayMusic(ftmix.MUSIC, 1);
				SDL_Delay(1);
				ftmix.MUSIC_LEN[i] -= 15 * 1000;
				Mix_RewindMusic();
				SDL_Delay(1);
				Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
				FTMix_pause(y);
				if (Mix_PlayingMusic() != 1)
				{
					Mix_PlayMusic(ftmix.MUSIC, 1);
					SDL_Delay(1);
					ftmix.MUSIC_LEN[i] -= 15 * 1000;
					Mix_RewindMusic();
					SDL_Delay(1);
					Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
					FTMix_pause(y);
				}
				while (Mix_PlayingMusic() == 1)
				{
					ftmix.MUSIC_LEN[i] += 1000;
					Mix_RewindMusic();
					SDL_Delay(1);
					Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
					FTMix_pause(y);
				}
			}
			else
			{
				ftmix.MUSIC_LEN[i] += 15 * 1000;
				Mix_RewindMusic();
				SDL_Delay(1);
				Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
				FTMix_pause(y);
				if (Mix_PlayingMusic() != 1)
				{
					Mix_PlayMusic(ftmix.MUSIC, 1);
					SDL_Delay(1);
					ftmix.MUSIC_LEN[i] -= 15 * 1000;
					Mix_RewindMusic();
					SDL_Delay(1);
					Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
					FTMix_pause(y);
				}
				while (Mix_PlayingMusic() == 1)
				{
					ftmix.MUSIC_LEN[i] += 1000;
					Mix_RewindMusic();
					SDL_Delay(1);
					Mix_SetMusicPosition((double)(ftmix.MUSIC_LEN[i] / 1000));
					FTMix_pause(y);
				}
			}
			ftmix.MUSIC_LEN[i] -= 1000;
		}
		else
			ftmix.MUSIC_LEN[i] = 0;
		i++;
	}
	Mix_VolumeMusic(ftmix.VOLUME);
	if (z == 1)
		FTMix_event_pause();
}
