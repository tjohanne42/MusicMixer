#ifndef FTMIX_LIB_H
 #define FTMIX_LIB_H

#ifndef _UNICODE
 #define _UNICODE
#endif
#ifndef UNICODE
 #define UNICODE
#endif

#include "time.h"
#include "locale.h"
#include "stdio.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <windows.h>

#define FTMIX_POLICE_NAME "GeosansLight.ttf"
#define FTMIX_ANIMATION_MAX 2
#define FTMIX_BUBBLE_MAX 100

typedef	struct 		t_ftmix_bubble
{
	_Bool			bubble;
	size_t			nb;
	int				x[FTMIX_BUBBLE_MAX];
	int				y[FTMIX_BUBBLE_MAX];
	unsigned int	start[FTMIX_BUBBLE_MAX];
	SDL_Color		color[FTMIX_BUBBLE_MAX];
}					s_ftmix_bubble;

typedef	struct 		t_ftmix_music
{
	Mix_Music		*music;
	size_t			nb;
	size_t			actual;
	unsigned int	timer;
	unsigned int	*len;	
	size_t			volume;
	size_t			volume_last;
	char			**path;
	char			**name;
	SDL_Surface		**s_name;
	_Bool			loop;
	_Bool			rand;
	size_t			*rand_tab;
}					s_ftmix_music;

typedef struct 		t_ftmix_texture
{
	SDL_Texture		*pause;
	SDL_Texture		*play;
	SDL_Texture		*volume_low;
	SDL_Texture		*volume_mid;
	SDL_Texture		*volume_high;
	SDL_Texture		*volume_off;
	SDL_Texture		*point;
	SDL_Texture		*mixer;
}					s_ftmix_texture;

typedef struct 		t_ftmix_animation
{
	SDL_Texture		**animation[FTMIX_ANIMATION_MAX];
	unsigned int	nb[FTMIX_ANIMATION_MAX];
	unsigned int	w[FTMIX_ANIMATION_MAX];
	unsigned int	h[FTMIX_ANIMATION_MAX];
	unsigned int	actual[FTMIX_ANIMATION_MAX];
	unsigned int	len_ms[FTMIX_ANIMATION_MAX];
	int				start[FTMIX_ANIMATION_MAX];
	size_t			music[FTMIX_ANIMATION_MAX];
}					s_ftmix_animation;

typedef	struct 			t_ftmix
{
	SDL_Window			*window;	
	SDL_Renderer		*renderer;
	wchar_t				*music_folder;
	char				*pic_folder;
	int					pos_x;
	int					pos_y;
	TTF_Font			**font;
	SDL_Color			color1;
	SDL_Color			color2;
	SDL_Surface			*loading_text[3];
	s_ftmix_music		music;
	s_ftmix_texture		texture;
	s_ftmix_animation	animation;
	s_ftmix_bubble		bubble;
}						s_ftmix;

s_ftmix			ftmix;

void			ftmix_init(const wchar_t *name, unsigned int w, unsigned int h, const wchar_t *pic_folder, const wchar_t *music_folder);
_Bool			ftmix_event(SDL_Event event, size_t fps, void (*ptr)(void));
void			ftmix_print(int x, int y);
void			ftmix_auto_play_next(void);

// ftmix_animation
void			ftmix_init_animation(const wchar_t *path, size_t channel, size_t nb, unsigned int len_ms, const char *format, size_t music);
void			ftmix_print_animation(unsigned int x, unsigned int y, size_t channel);

// ftmix_load
void			ftmix_load(void);
void			ftmix_load_texture(void);
void			ftmix_load_path(void);
void			ftmix_load_name(void);
void			ftmix_load_len(void);
void			ftmix_print_while_loading(void);
SDL_Texture		*ftmix_texture_from_pic(char *s1, char *s2);
void			ftmix_exit_error(const char *str);

// ftmix_event_tools
_Bool			ftmix_point_in_rect(int px, int py, int rx, int ry, int rw, int rh);
void			ftmix_load_music(const char *path, int nb);
void			ftmix_event_pause(void);
void			ftmix_event_timer_line(SDL_Event old_event, size_t fps, void (*ptr)(void));
void			ftmix_event_volume_line(SDL_Event old_event, size_t fps, void (*ptr)(void));
void			ftmix_change_volume(int nb);
void			ftmix_change_timer(int ms);
void			ftmix_event_reload(void);
void			ftmix_event_loop(void);
void			ftmix_event_volume_pic(void);
unsigned int	ftmix_get_timer(void);
void			ftmix_set_timer(int ms);
void			ftmix_event_previous(void);
void			ftmix_event_next(void);
void			ftmix_volume_wheel(SDL_Event event);
void			ftmix_event_rand(void);
void			ftmix_add_bubble(SDL_Event event);
void			ftmix_event_bubble(void);

// ftmix_print_tools
void			ftmix_FillRect(int x, int y, size_t w, size_t h, size_t r, size_t g, size_t b, size_t a);
void			ftmix_PrintTexture(SDL_Texture *texture, int x, int y);
void			ftmix_PrintSurfaceCenterXY(SDL_Surface *surface, int x, int y);
void			ftmix_PrintTextCenterY(char *str, int x, int y, TTF_Font *font, size_t r, size_t g, size_t b, size_t a);
void			ftmix_PrintSurface(SDL_Surface *surface, int x, int y);
void			ftmix_PrintCercle(int x_center, int y_center, unsigned int rayon, SDL_Color color);

// ftmix_utf8
char			*ft_wstrtstr(const wchar_t *wstr);
char			*wchar_utf8(intmax_t i);
intmax_t		ft_binary_to_decimal(const size_t *tab);
int				ft_power(intmax_t x, intmax_t power);
char			*ft_strnew(size_t i);
size_t			ft_wstrlen(const wchar_t *wstr);
_Bool			ft_wstrfreejoin(wchar_t **s1, const wchar_t *s2, char statut);
wchar_t			*ft_wstrjoin(const wchar_t *s1, const wchar_t *s2);
void			ft_wstrncpy(wchar_t *dest, const wchar_t *src, size_t n);

// ftmix_mini_libft
_Bool			ft_strfreejoin(char **s1, const char *s2, char statut);
char			*ft_mststr(long int ms);
void			ft_strncpy(char *dest, const char *src, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strjoin(const char *s1, const char *s2);
int				ft_strcmp(const char *s1, const char *s2);


#endif