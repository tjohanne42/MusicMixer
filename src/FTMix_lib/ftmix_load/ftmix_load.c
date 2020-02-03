#include "ftmix_lib.h"

static void		ftmix_free_texture(void)
{
	size_t		i = 0;

	if (ftmix.texture.pause)
	{
		SDL_DestroyTexture(ftmix.texture.pause);
		ftmix.texture.pause = NULL;
	}
	if (ftmix.texture.play)
	{
		SDL_DestroyTexture(ftmix.texture.play);
		ftmix.texture.play = NULL;
	}
	if (ftmix.texture.volume_low)
	{
		SDL_DestroyTexture(ftmix.texture.volume_low);
		ftmix.texture.volume_low = NULL;
	}
	if (ftmix.texture.volume_mid)
	{
		SDL_DestroyTexture(ftmix.texture.volume_mid);
		ftmix.texture.volume_mid = NULL;
	}
	if (ftmix.texture.volume_high)
	{
		SDL_DestroyTexture(ftmix.texture.volume_high);
		ftmix.texture.volume_high = NULL;
	}
	if (ftmix.texture.volume_off)
	{
		SDL_DestroyTexture(ftmix.texture.volume_off);
		ftmix.texture.volume_off = NULL;
	}
	if (ftmix.texture.point)
	{
		SDL_DestroyTexture(ftmix.texture.point);
		ftmix.texture.point = NULL;
	}
	if (ftmix.texture.mixer)
	{
		SDL_DestroyTexture(ftmix.texture.mixer);
		ftmix.texture.mixer = NULL;
	}
	if (ftmix.font)
	{
		while (i < 100 && ftmix.font[i])
			TTF_CloseFont(ftmix.font[i++]);
		free(ftmix.font);
		ftmix.font = NULL;
	}
	if (ftmix.loading_text[0])
	{
		SDL_FreeSurface(ftmix.loading_text[0]);
		ftmix.loading_text[0] = NULL;
	}
	if (ftmix.loading_text[1])
	{
		SDL_FreeSurface(ftmix.loading_text[1]);
		ftmix.loading_text[1] = NULL;
	}
	if (ftmix.loading_text[2])
	{
		SDL_FreeSurface(ftmix.loading_text[2]);
		ftmix.loading_text[2] = NULL;
	}
}

static void		ftmix_free_load(void)
{
	size_t		i = 0;

	if (ftmix.music.music)
	{
		Mix_FreeMusic(ftmix.music.music);
		ftmix.music.music = NULL;
	}
	if (ftmix.music.len)
	{
		free(ftmix.music.len);
		ftmix.music.len = NULL;
	}
	if (ftmix.music.path)
	{
		while (i < ftmix.music.nb && ftmix.music.path[i])
			free(ftmix.music.path[i++]);
		free(ftmix.music.path);
		ftmix.music.path = NULL;
		i = 0;
	}
	if (ftmix.music.name)
	{
		while (i < ftmix.music.nb && ftmix.music.name[i])
			free(ftmix.music.name[i++]);
		free(ftmix.music.name);
		ftmix.music.name = NULL;
		i = 0;
	}
	if (ftmix.music.s_name)
	{
		while (i < ftmix.music.nb && ftmix.music.s_name[i])
			SDL_FreeSurface(ftmix.music.s_name[i++]);
		free(ftmix.music.s_name);
		ftmix.music.s_name = NULL;
	}
	if (ftmix.music.rand_tab)
	{
		free(ftmix.music.rand_tab);
		ftmix.music.rand_tab = NULL;
	}
}

static void		ftmix_init_data(void)
{
	ftmix.music.nb = 0;
	ftmix.music.music = NULL;
	ftmix.music.len = NULL;
	ftmix.music.path = NULL;
	ftmix.music.name = NULL;
	ftmix.music.s_name = NULL;
	ftmix.music.rand_tab = NULL;
	ftmix.music.actual = 0;
	ftmix.music.timer = 0;
	ftmix.music.loop = SDL_FALSE;
	ftmix.music.rand = SDL_FALSE;
}

void			ftmix_print_while_loading(void)
{
	static size_t	frame = 0;
	static int		start = -20000;
	SDL_Rect		rect = {0, 0, 0, 0};
	size_t			tmp = 0;

	if (SDL_GetTicks() - start >= 20000)
	{
		frame = 0;
		start = SDL_GetTicks();
	}
	ftmix.animation.start[0] = frame % ftmix.animation.nb[0] * ftmix.animation.len_ms[0] + 1;
	SDL_GetWindowSize(ftmix.window, &rect.w, &rect.h);
	if (rect.w < 350 && rect.h < 90)
	{
		rect.w = 350;
		rect.h = 90;
	}
	else if (rect.w < 350)
		rect.w = 350;
	else if (rect.h < 90)
		rect.h = 90;
	else
		tmp = 1;
	if (tmp == 0)
		SDL_SetWindowSize(ftmix.window, rect.w, rect.h);
	if (SDL_SetRenderDrawColor(ftmix.renderer, 0, 0, 0, 255) != 0)
		ftmix_exit_error("SDL_SetRenderDrawColor");
	if (SDL_RenderClear(ftmix.renderer) != 0)
		ftmix_exit_error("SDL_RenderClear");
	if (rect.w >= (int)ftmix.animation.w[0] && rect.h >= (int)ftmix.animation.h[0] + 90)
	{
		ftmix_print_animation(rect.w / 2 - ftmix.animation.w[0] / 2, (rect.h - 90) / 2 - ftmix.animation.h[0] / 2 + 90, 0);
		ftmix_PrintSurface(ftmix.loading_text[frame % 3],
			rect.w / 2 - ftmix.loading_text[2]->w / 2, ((rect.h - 90) / 2 - ftmix.animation.h[0] / 2 + 90) / 2 - ftmix.loading_text[2]->h / 2);
	}
	else if (rect.w >= (int)ftmix.animation.w[1] && rect.h >= (int)ftmix.animation.h[1])
	{
		ftmix_print_animation(rect.w / 2 - ftmix.animation.w[0] / 2, rect.h / 2 - ftmix.animation.h[0] / 2, 0);
		ftmix_PrintSurface(ftmix.loading_text[frame % 3], rect.w / 2 - ftmix.loading_text[2]->w / 2, rect.h - 45 - ftmix.loading_text[2]->h / 2);
	}
	else
		ftmix_PrintSurface(ftmix.loading_text[frame % 3], rect.w / 2 - ftmix.loading_text[2]->w / 2, rect.h / 2 - ftmix.loading_text[2]->h / 2);
	frame++;
	SDL_RenderPresent(ftmix.renderer);
}

void			ftmix_load(void)
{
	static _Bool	done = SDL_FALSE;

	if (!done)
	{
		ftmix.pos_x = 0;
		ftmix.pos_y = 0;
		ftmix.color1.r = 255;
		ftmix.color1.g = 255;
		ftmix.color1.b = 255;
		ftmix.color1.a = 255;
		ftmix.color2.r = 105;
		ftmix.color2.g = 105;
		ftmix.color2.b = 105;
		ftmix.color2.a = 255;
		ftmix.music.volume = 30;
		ftmix.music.volume_last = 30;
		ftmix.bubble.bubble = SDL_FALSE;
		ftmix.bubble.nb = 0;
		Mix_VolumeMusic(30);
		ftmix_init_animation(L"anim/turtle/", 0, 10, 75, NULL, 0);
		ftmix_load_texture();
		atexit(ftmix_free_texture);
		atexit(ftmix_free_load);
		done = SDL_TRUE;
	}
	else
		ftmix_free_load();
	ftmix_init_data();
	ftmix_load_path();
	ftmix_print_while_loading();
	ftmix_load_name();
	ftmix_load_len();
	if (!(ftmix.music.rand_tab = malloc(sizeof(*ftmix.music.rand_tab) * ftmix.music.nb)))
		ftmix_exit_error("malloc");
	size_t		i = 0;
	while (i < ftmix.music.nb)
	{
		ftmix.music.rand_tab[i] = 0;
		i++;
	}
	if (ftmix.music.nb)
		ftmix_load_music(ftmix.music.path[0], 1);
	ftmix_event_pause();
}