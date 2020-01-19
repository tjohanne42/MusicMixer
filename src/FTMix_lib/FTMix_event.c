#include "FTMix_lib.h"

_Bool			FTMix_event(SDL_Event event, size_t fps, void (*ptr)(void))
{
	_Bool	tmp = SDL_FALSE;

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		if (FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X, ftmix.POS_Y, 350, 90))
		{
			if ((tmp = FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X + 10, ftmix.POS_Y + 25, 30, 30)))
				FTMix_event_previous();
			else if ((tmp = FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X + 40, ftmix.POS_Y + 25, 30, 30)))
				FTMix_event_pause();
			else if ((tmp = FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X + 70, ftmix.POS_Y + 25, 30, 30)))
				FTMix_event_next();
			else if ((tmp = FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X + 100, ftmix.POS_Y + 25, 40, 30)))
				FTMix_event_volume_pic();
			else if ((tmp = FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X + 280, ftmix.POS_Y + 25, 30, 30)))
				FTMix_event_loop();
			else if ((tmp = FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X + 140, ftmix.POS_Y + 25, 60, 30)))
				FTMix_event_volume_line(event, fps, (ptr));
			else if (ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL] != 0 && (tmp = FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X + 10, ftmix.POS_Y + 5, 300, 20)))
				FTMix_event_timer_line(event, fps, (ptr));
			else if ((tmp = FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X + 320, ftmix.POS_Y, 30, 30)))
				FTMix_event_reload();
			else if ((tmp = FTMix_PointInRect(event.button.x, event.button.y, ftmix.POS_X + 320, ftmix.POS_Y + 30, 30, 30)))
				FTMix_event_bubble();
			
		}
	}
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP && (tmp = SDL_TRUE))
			FTMix_increase_volume(2);
		else if (event.key.keysym.sym == SDLK_DOWN && (tmp = SDL_TRUE))
			FTMix_decrease_volume(2);
		else if (event.key.keysym.sym == SDLK_SPACE && (tmp = SDL_TRUE))
			FTMix_event_pause();
		else if (ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL] != 0 && event.key.keysym.sym == SDLK_LEFT && (tmp = SDL_TRUE))
			FTMix_change_timer(-5000);
		else if (ftmix.MUSIC_LEN[ftmix.MUSIC_ACTUAL] != 0 && event.key.keysym.sym == SDLK_RIGHT && (tmp = SDL_TRUE))
			FTMix_change_timer(5000);
	}
	if (tmp)
		return (SDL_TRUE);
	return (SDL_FALSE);
}
