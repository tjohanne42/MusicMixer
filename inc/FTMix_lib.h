#ifndef FTMIX_LIB_H
 #define FTMIX_LIB_H

#ifndef _UNICODE
 #define _UNICODE
#endif
#ifndef UNICODE
 #define UNICODE
#endif

#include "stdlib.h"
#include "time.h"
#include "locale.h"
#include <windows.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "tchar.h"

#define FTMIX_ANIMATION_MAX 10
#define FTMIX_POLICE_NAME "symbola.ttf"

/* USAGE FUNCTION */
// FTMix_init open a window and is pretty fast
void			FTMix_init(const wchar_t *name, unsigned int w, unsigned int h, const wchar_t *dir_pic_wpath, const wchar_t *dir_music_wpath);
// FTMix_load may take several time
void			FTMix_load(void);
// now you're good to start
// FTMix_Print write on ftmix.RENDERER to print ftmix.RENDERER use SDL_RenderPresent(ftmix.RENDERER)
void			FTMix_print(int x, int y);
_Bool			FTMix_event(SDL_Event event, size_t fps, void (*ptr)(void));
// this function automatically load next music if current music is end
// BUT you have to launch this at EVERY TIME in your main loop (rude, I know)
void			FTMix_change_music(void);

void			FTMix_init_animation(const wchar_t *str, size_t nb, size_t	fps, size_t channel);
void			FTMix_print_animation(int x, int y, size_t channel);
void			FTMix_init_animation_on_music(const wchar_t *str, size_t nb, unsigned int len, size_t channel);
void			FTMix_print_animation_on_music(int x, int y, size_t channel);

/* EVENT TOOLS FUNCTION */
_Bool			FTMix_PointInRect(size_t px, size_t py, size_t rx, size_t ry, size_t rw, size_t rh);
void			FTMix_event_pause(void);
// set timer (3000) = set music at 0:03
void			FTMix_set_timer(int ms);
// change timer (+3000) = +3sec ; change timer (-3000) = -3sec
void			FTMix_change_timer(int ms);
int				FTMix_get_timer(void);
void			FTMix_increase_volume(size_t v);
void			FTMix_decrease_volume(size_t v);
void			FTMix_play_next(void);
void			FTMix_play_previous(void);
void			FTMix_event_next(void);
void			FTMix_event_previous(void);
void			FTMix_event_loop(void);
void			FTMix_event_volume_pic(void);
void			FTMix_load_music(const char *path);
void			FTMix_event_reload(void);
void			FTMix_event_bubble(void);

/* PRINT TOOLS FUNCTION */
void			FTMix_PrintTexture(SDL_Texture *texture, int x, int y);
void			FTMix_FillRect(int x, int y, size_t w, size_t h, size_t r, size_t g, size_t b, size_t a);
void			FTMix_PrintTextCenterY(char *str, int x, int y, TTF_Font *font, size_t r, size_t g, size_t b, size_t a);
void			FTMix_PrintSurfaceCenterXY(SDL_Surface *surface, int x, int y);

/* MINI LIBFT */
char			*ft_mststr(long int ms);
void			ft_strncpy(char *dest, const char *src, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strjoin(const char *s1, const char *s2);
_Bool			ft_strfreejoin(char **s1, const char *s2, char statut);

/* WCHAR UTF8 */
char			*ft_wstrtstr(const wchar_t *wstr);
char			*wchar_utf8(intmax_t i);
intmax_t		ft_binary_to_decimal(const size_t *tab);
int				ft_power(intmax_t x, intmax_t power);
char			*ft_strnew(size_t i);
size_t			ft_wstrlen(const wchar_t *wstr);
_Bool			ft_wstrfreejoin(wchar_t **s1, const wchar_t *s2, char statut);
wchar_t			*ft_wstrjoin(const wchar_t *s1, const wchar_t *s2);
void			ft_wstrncpy(wchar_t *dest, const wchar_t *src, size_t n);


/* NON USAGE FUNCTION */
void			FTMix_init_dir_path(const wchar_t *dir_pic_wpath, const wchar_t *dir_music_wpath);
void			FTMix_load_pic(void);
void			FTMix_load_music_path(void);
void			FTMix_load_music_name(void);
void			FTMix_load_music_len(void);
SDL_Texture		*FTMix_GetTextureFromPic(char *path1, char *path2, SDL_Rect *rect);
void			FTMix_ExitWithError(const char *str);
void			FTMix_event_timer_line(SDL_Event old_event, size_t fps, void (*ptr)(void));
void			FTMix_event_volume_line(SDL_Event old_event, size_t fps, void (*ptr)(void));
void			FTMix_print_while_loading(void);
void			FTMix_free_music_name(void);
void			FTMix_free_pic(void);
void			FTMix_free_music_path(void);
void			FTMix_free_animation_channel(size_t channel);
void			FTMix_free_music_len(void);
void			FTMix_free_load(void);
void			FTMix_free_animation_load();

typedef	struct 		t_FTMix
{
	wchar_t			*DIR_MUSIC_WPATH;
	char			*DIR_PIC_PATH;
	char			*EXEC_STR;
	SDL_Window		*WINDOW;
	SDL_Renderer	*RENDERER;
	unsigned int	WINDOW_W;
	unsigned int	WINDOW_H;
	SDL_Texture		*t_PAUSE;
	SDL_Texture		*t_PLAY;
	SDL_Texture		*t_VOLUME_LOW;
	SDL_Texture		*t_VOLUME_MID;
	SDL_Texture		*t_VOLUME_HIGH;
	SDL_Texture		*t_VOLUME_OFF;
	SDL_Texture		*t_POINT;
	SDL_Texture		*t_BASE;
	SDL_Texture		**ANIMATION[FTMIX_ANIMATION_MAX];
	size_t			ANIMATION_ACTUAL[FTMIX_ANIMATION_MAX];
	size_t			ANIMATION_NB[FTMIX_ANIMATION_MAX];
	size_t			ANIMATION_LEN[FTMIX_ANIMATION_MAX];
//	unsigned int	ANIMATION_LAST[FTMIX_ANIMATION_MAX];
	size_t			ANIMATION_W[FTMIX_ANIMATION_MAX];
	size_t			ANIMATION_H[FTMIX_ANIMATION_MAX];
	char			*ANIMATION_PATH[FTMIX_ANIMATION_MAX];
	SDL_Surface		*LOADING[3];
	unsigned int	MUSIC_NB;
	unsigned int	POS_X;
	unsigned int	POS_Y;
	Mix_Music		*MUSIC;
	char			**MUSIC_PATH;
	SDL_Surface		**MUSIC_NAME;
	int				*MUSIC_LEN;
	size_t			MUSIC_ACTUAL;
	int				MUSIC_TIMER;
	size_t			VOLUME;
	size_t			VOLUME_LAST;
	SDL_Color		COLOR1;
	SDL_Color		COLOR2;
	TTF_Font		*FONT[19];
	_Bool			LOOP;
	_Bool			BUBBLE;
}					s_FTMix;

s_FTMix			ftmix;

#endif