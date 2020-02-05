#include "music_mixer.h"

static SDL_Rect		print_frame(void)
{
	SDL_Rect	rect = {0, 0, 0, 0};
	size_t		tmp = 0;

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
	if (rect.w >= (int)ftmix.animation.w[1] && rect.h >= (int)ftmix.animation.h[1] + 90)
	{
		ftmix_print_animation(rect.w / 2 - ftmix.animation.w[1] / 2, (rect.h - 90) / 2 - ftmix.animation.h[1] / 2 + 90, 1);
		ftmix_print(rect.w / 2 - 175, ((rect.h - 90) / 2 - ftmix.animation.h[1] / 2 + 90) / 2 - 45);
	}
	else if (rect.w >= (int)ftmix.animation.w[1] && rect.h >= (int)ftmix.animation.h[1])
	{
		ftmix_print_animation(rect.w / 2 - ftmix.animation.w[1] / 2, rect.h / 2 - ftmix.animation.h[1] / 2, 1);
		ftmix_print(rect.w / 2 - 175, rect.h - 90);
	}
	else
		ftmix_print(rect.w / 2 - 175, rect.h / 2 - 45);
	return (rect);
}

static void		sync_for_ftmix(void)
{
	print_frame();
}

int				main(int argc, char **argv)
{
	if (argc < 1)
		SDL_Log("my main %d %s", argc, argv[0]);

	// init FTMix
	wchar_t			name[] = L"¤ MusicMixer ¤";
	wchar_t			pic_path[] = L"../src/ftmix_lib/¤pic";
	wchar_t			music_path[] = L"../music";

	ftmix_init(name, 600, 400, music_path, pic_path);
	ftmix_load();
	ftmix_init_animation(L"anim/dark vader/", 1, 86, 70, NULL, 0);

	// start the program
	SDL_bool		EXIT_VALUE = SDL_FALSE;
	SDL_Event		event;
	size_t			fps = 30;
	void			(*ptr)(void) = &sync_for_ftmix;
	unsigned int	last_count;
	unsigned int	current_count;

	ftmix_event_pause();
	print_frame();
	last_count = SDL_GetTicks();
	SDL_RenderPresent(ftmix.renderer);
	while (!EXIT_VALUE)
	{
		event.type = 0;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				EXIT_VALUE = SDL_TRUE;
			else
				ftmix_event(event, fps, ptr);
		}
		ftmix_auto_play_next();
		current_count = SDL_GetTicks();
		if (current_count - last_count >= 1000 / fps)
		{
			print_frame();
			last_count = current_count;
		}
		SDL_RenderPresent(ftmix.renderer);
	}
	return (0);
}
