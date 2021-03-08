#ifndef SDLX_H
#define SDLX_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"

# include "SDLX_const.h"
# include "SDLX_config.h"
# include "SDLX_ticks.h"

# include "SDLX_structs.h"

void			SDLX_start(SDLX_Display *dest);

SDLX_Display	*SDLX_GetDisplay(void);

void			SDLX_screen_reset(SDL_Renderer *renderer, SDL_Color *bg_color);

void			SDLX_close(void);

void			SDLX_draw_animation(SDL_Renderer *renderer, SDLX_Sprite *animation);

int				SDLX_RenderQueue_init(SDLX_RenderQueue *dest);
void			SDLX_RenderQueue_add(SDLX_RenderQueue *dst, SDLX_Sprite *src);
void			SDLX_RenderQueue_flush(SDLX_RenderQueue *queue, SDL_Renderer *renderer);

int				SDLX_AxisConvert(SDL_Point *axis);
void			SDLX_FillXbox_Axis(SDLX_GameInput *game_input, SDL_GameController *controller);
void			SDLX_toDPAD(SDLX_GameInput *game_input, int set);

SDL_GameController	*SDLX_XboxController_link(int player_no);

void	SDLX_KeyMap(SDLX_input_mapper *key_map, const Uint8 *keystate);
void	SDLX_ControllerMap(SDLX_input_mapper *key_map, SDL_GameController *controller);

SDLX_direction	SDLX_reverse_dir(SDLX_direction direction);
SDLX_Sprite		*SDLX_new_Sprite(SDLX_Sprite *dst);

SDLX_Sprite		*SDLX_get_background(void);
void			SDLX_set_background(SDLX_Sprite *src);

SDL_bool		SDLX_poll(void);

#endif
