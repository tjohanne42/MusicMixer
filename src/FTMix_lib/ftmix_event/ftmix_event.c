#include "ftmix_lib.h"

_Bool			ftmix_event(SDL_Event event, size_t fps, void (*ptr)(void))
{
	_Bool	tmp = SDL_FALSE;

	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		if (ftmix.bubble.bubble && !ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 320, ftmix.pos_y + 60, 30, 30))
			ftmix_add_bubble(event);
		if (ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x, ftmix.pos_y, 350, 90))
		{
			if ((tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 10, ftmix.pos_y + 25, 30, 30)))
				ftmix_event_previous();
			else if ((tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 40, ftmix.pos_y + 25, 30, 30)))
				ftmix_event_pause();
			else if ((tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 70, ftmix.pos_y + 25, 30, 30)))
				ftmix_event_next();
			else if ((tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 100, ftmix.pos_y + 25, 40, 30)))
				ftmix_event_volume_pic();
			else if ((tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 280, ftmix.pos_y + 25, 30, 30)))
				ftmix_event_loop();
			else if ((tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 140, ftmix.pos_y + 25, 60, 30)))
				ftmix_event_volume_line(event, fps, ptr);
			else if (ftmix.music.len[ftmix.music.actual] != 0 && (tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 10, ftmix.pos_y + 5, 300, 20)))
				ftmix_event_timer_line(event, fps, ptr);
			else if ((tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 320, ftmix.pos_y, 30, 30)))
				ftmix_event_reload();
			else if ((tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 320, ftmix.pos_y + 30, 30, 30)))
				ftmix_event_rand();
			else if ((tmp = ftmix_point_in_rect(event.button.x, event.button.y, ftmix.pos_x + 320, ftmix.pos_y + 60, 30, 30)))
				ftmix_event_bubble();
		}
	}
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_UP && (tmp = SDL_TRUE))
			ftmix_change_volume(2);
		else if (event.key.keysym.sym == SDLK_DOWN && (tmp = SDL_TRUE))
			ftmix_change_volume(-2);
		else if (event.key.keysym.sym == SDLK_SPACE && (tmp = SDL_TRUE))
			ftmix_event_pause();
		else if (ftmix.music.len[ftmix.music.actual] != 0 && event.key.keysym.sym == SDLK_LEFT && (tmp = SDL_TRUE))
			ftmix_change_timer(-5000);
		else if (ftmix.music.len[ftmix.music.actual] != 0 && event.key.keysym.sym == SDLK_RIGHT && (tmp = SDL_TRUE))
			ftmix_change_timer(5000);
	}
	else if (event.type == SDL_MOUSEWHEEL && (tmp = SDL_TRUE))
		ftmix_volume_wheel(event);
	return (tmp);
}