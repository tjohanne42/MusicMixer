#include "ftmix_lib.h"

void			ftmix_PrintCercle(int x_center, int y_center, unsigned int rayon, SDL_Color color)
{
	int		x = 0;
	int		y = rayon;
	int		m = 5 - 4 * rayon;
	SDL_Point	points[8];

	if (SDL_SetRenderDrawColor(ftmix.renderer, color.r, color.g, color.b, color.a) != 0)
			ftmix_exit_error("SDL_SetRenderDrawColor");
	while (x <= y)
	{
		points[0].x = x + x_center;
		points[0].y = y + y_center;
		points[1].x = y + x_center;
		points[1].y = x + y_center;
		points[2].x = x * -1 + x_center;
		points[2].y = y + y_center;
		points[3].x = y * -1 + x_center;
		points[3].y = x + y_center;
		points[4].x = x + x_center;
		points[4].y = y * -1 + y_center;
		points[5].x = y + x_center;
		points[5].y = x * -1 + y_center;
		points[6].x = x * -1 + x_center;
		points[6].y = y * -1 + y_center;
		points[7].x = y * -1 + x_center;
		points[7].y = x * -1 + y_center;
		SDL_RenderDrawPoints(ftmix.renderer, points, 8);
		if (m > 0)
		{
			y -= 1;
			m -= 8 * y;
		}
		x += 1;
		m += 8 * x + 4;
	}
}

void			ftmix_PrintTexture(SDL_Texture *texture, int x, int y)
{
	SDL_Rect	rect;

	if (SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) != 0)
		ftmix_exit_error("SDL_QueryTexture");
	rect.x = x;
	rect.y = y;
	if (SDL_RenderCopy(ftmix.renderer, texture, NULL, &rect) != 0)
		ftmix_exit_error("SDL_RenderCopy");
}

void			ftmix_PrintSurfaceCenterXY(SDL_Surface *surface, int x, int y)
{
	SDL_Texture		*texture;

	texture = NULL;
	if (!(texture = SDL_CreateTextureFromSurface(ftmix.renderer, surface)))
		ftmix_exit_error("SDL_CreateTextureFromSurface");
	ftmix_PrintTexture(texture, x - surface->w / 2, y - surface->h / 2);
	SDL_DestroyTexture(texture);
}

void			ftmix_PrintSurface(SDL_Surface *surface, int x, int y)
{
	SDL_Texture		*texture;

	texture = NULL;
	if (!(texture = SDL_CreateTextureFromSurface(ftmix.renderer, surface)))
		ftmix_exit_error("SDL_CreateTextureFromSurface");
	ftmix_PrintTexture(texture, x, y);
	SDL_DestroyTexture(texture);
}

void			ftmix_PrintTextCenterY(char *str, int x, int y, TTF_Font *font, size_t r, size_t g, size_t b, size_t a)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	SDL_Color	color = {r, g, b, a};

	surface = NULL;
	texture = NULL;
	if (!(surface = TTF_RenderText_Blended(font, str, color)))
		ftmix_exit_error("TTF_RenderText_Blended");
	if (!(texture = SDL_CreateTextureFromSurface(ftmix.renderer, surface)))
		ftmix_exit_error("SDL_CreateTextureFromSurface");
	ftmix_PrintTexture(texture, x, y - surface->h / 2);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void			ftmix_FillRect(int x, int y, size_t w, size_t h, size_t r, size_t g, size_t b, size_t a)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	Uint32		rmask;
	Uint32		gmask;
	Uint32		bmask;
	Uint32		amask;

	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	}
	else
	{
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	}
	surface = NULL;
	texture = NULL;
	surface = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
	if (!surface)
		ftmix_exit_error("SDL_CreateRGBSurface");
	if (SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, r, g, b, a)) != 0)
		ftmix_exit_error("SDL_FillRect");
	texture = SDL_CreateTextureFromSurface(ftmix.renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		ftmix_exit_error("SDL_CreateTextureFromSurface");
	ftmix_PrintTexture(texture, x, y);
	SDL_DestroyTexture(texture);
}
