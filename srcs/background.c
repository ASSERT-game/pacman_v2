/***************************************************************************
 * FILENAME:    background.c
 * DESCRIPTION: Makes and returns the texture for the background.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 02Feb2021
***************************************************************************/

#include "pacman.h"

int		fetch_BackgroundSpriteInfo(SDLX_Sprite_Data **dst, SDL_UNUSED int no)
{
	static SDLX_Sprite_Data	*sprite_arr;

	if (sprite_arr == NULL)
	{
		sprite_arr = SDL_calloc(1, sizeof(*sprite_arr));
		sprite_arr[0].texture = IMG_LoadTexture(SDLX_GetDisplay()->renderer, ASSETS"pacman_background.png");
		sprite_arr[0].src = NULL;
		sprite_arr[0].cycle = 1;
	}

	*dst = &(sprite_arr[0]);
	return (EXIT_SUCCESS);
}

int		init_BackgrundSprite(SDLX_Sprite *dst)
{
	int	result;

	result = fetch_BackgroundSpriteInfo(&(dst->sprite_data), SD_BACKGROUND);
	SDLX_new_Sprite(dst);
	dst->dst = NULL;

	return (result);
}
