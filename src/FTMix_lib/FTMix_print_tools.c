#include "FTMix_lib.h"

void			FTMix_PrintTexture(SDL_Texture *texture, int x, int y)
{
	SDL_Rect	rect;

	if (SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h) != 0)
		FTMix_ExitWithError("SDL_QueryTexture");
	rect.x = x;
	rect.y = y;
	if (SDL_RenderCopy(ftmix.RENDERER, texture, NULL, &rect) != 0)
		FTMix_ExitWithError("SDL_RenderCopy");
}

void			FTMix_PrintSurfaceCenterXY(SDL_Surface *surface, int x, int y)
{
	SDL_Texture		*texture;

	texture = NULL;
	if (!(texture = SDL_CreateTextureFromSurface(ftmix.RENDERER, surface)))
		FTMix_ExitWithError("SDL_CreateTextureFromSurface");
	FTMix_PrintTexture(texture, x - surface->w / 2, y - surface->h / 2);
	SDL_DestroyTexture(texture);
}

void			FTMix_PrintTextCenterY(char *str, int x, int y, TTF_Font *font, size_t r, size_t g, size_t b, size_t a)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;
	SDL_Color	color = {r, g, b, a};

	surface = NULL;
	texture = NULL;
	if (!(surface = TTF_RenderText_Blended(font, str, color)))
		FTMix_ExitWithError("TTF_RenderText_Blended");
	if (!(texture = SDL_CreateTextureFromSurface(ftmix.RENDERER, surface)))
		FTMix_ExitWithError("SDL_CreateTextureFromSurface");
	FTMix_PrintTexture(texture, x, y - surface->h / 2);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void			FTMix_FillRect(int x, int y, size_t w, size_t h, size_t r, size_t g, size_t b, size_t a)
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
		FTMix_ExitWithError("SDL_CreateRGBSurface");
	if (SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, r, g, b, a)) != 0)
		FTMix_ExitWithError("SDL_FillRect");
	texture = SDL_CreateTextureFromSurface(ftmix.RENDERER, surface);
	SDL_FreeSurface(surface);
	if (!texture)
		FTMix_ExitWithError("SDL_CreateTextureFromSurface");
	FTMix_PrintTexture(texture, x, y);
	SDL_DestroyTexture(texture);
}
