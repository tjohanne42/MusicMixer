#include "music_mixer.h"

static void		print_frame(void)
{
	if (SDL_SetRenderDrawColor(ftmix.RENDERER, 0, 0, 0, 255) != 0)
		FTMix_ExitWithError("SDL_SetRenderDrawColor");
	if (SDL_RenderClear(ftmix.RENDERER) != 0)
		FTMix_ExitWithError("SDL_RenderClear");
	FTMix_print(ftmix.WINDOW_W / 2 - 175, ftmix.WINDOW_H / 2 - 175);
	if (ftmix.MUSIC_NB > 0 && ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL] > 0)
		FTMix_print_animation_on_music(ftmix.WINDOW_W / 2 - ftmix.ANIMATION_W[1] / 2, ftmix.WINDOW_H / 2 - ftmix.ANIMATION_H[1] / 2 + 50, 1);
}

int				main(int argc, char **argv)
{
	if (argc < 1)
		SDL_Log("my main %d %s", argc, argv[0]);

	// init FTMix
	wchar_t		name[] = L"¤ MusicMixer ¤";
	wchar_t		pic_path[] = L"../src/FTMix_lib/¤pic";
	wchar_t		music_path[] = L"../¤music";

	FTMix_init(name, 600, 400, pic_path, music_path);
	FTMix_load();
	if (ftmix.MUSIC_NB > 0)
		FTMix_init_animation_on_music(L"turtle/", 10, 1010, 1);

	// start the program
	SDL_bool	EXIT_VALUE = SDL_FALSE;
	SDL_Event	event;
	unsigned int	last_count;
	unsigned int	current_count;
	size_t			fps = 60;
	void			(*ptr)(void) = &print_frame;

	print_frame();
	last_count = SDL_GetTicks();
	FTMix_event_pause();
	SDL_RenderPresent(ftmix.RENDERER);
	while (!EXIT_VALUE)
	{
		event.type = 0;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			EXIT_VALUE = SDL_TRUE;
		else
			FTMix_event(event, fps, (ptr));
		current_count = SDL_GetTicks();
		if (current_count - last_count >= 1000 / fps)
		{
			print_frame();
			last_count = current_count;
		}
		FTMix_change_music();
		SDL_RenderPresent(ftmix.RENDERER);
	}
	return (0);
}
