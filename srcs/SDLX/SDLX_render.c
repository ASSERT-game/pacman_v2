/***************************************************************************
 * FILENAME:    SDLX_render.c
 * DESCRIPTION: Utility functions for rendering the screen.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 24Jan2021
***************************************************************************/

#include "SDLX.h"

// The function below will be called at the end of each draw stage
// and display the renderer onto the window, and prep it for a new
// draw stage.

void	SDLX_screen_reset(SDL_Renderer *renderer, SDL_Color *bg_color)
{
	// SDL_Log("NEW FRAME DRAWN");

	SDL_RenderPresent(renderer);
	if (bg_color != NULL)
		SDL_SetRenderDrawColor(renderer, bg_color->r, bg_color->g, bg_color->b, bg_color->a);
	// else
	// 	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_RenderClear(renderer);

	SDLX_Sprite	*background;

	background = SDLX_get_background();
	if (background != NULL)
		SDLX_draw_animation(renderer, background);

	// Line below might be unecessary.
	// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}