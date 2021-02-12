/***************************************************************************
 * FILENAME:    extra_texture.c
 * DESCRIPTION: Handles the animation texture for the misc items.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 04Feb2021
***************************************************************************/

#include "pacman.h"

SDLX_Sprite_Data	*carve_extra_sprite(void)
{
	size_t	i;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(3, sizeof(*result));
	texture = IMG_LoadTexture(SDLX_GetDisplay()->renderer, ASSETS"pacman_extra.png");

	i = 0;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 0, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;

	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 16, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;

	i++;
	result[i].texture = texture;
	result[i]._src = (SDL_Rect){0, 32, 16, 16};
	result[i].src = &(result[i]._src);
	result[i].cycle = 1;

	return (result);
}

int	fetch_ExtraSpriteInfo(SDLX_Sprite_Data **dst, SDL_UNUSED int no)
{
	static SDLX_Sprite_Data *sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_extra_sprite();

	(*dst) = &(sprite_arr[no]);
	return (EXIT_SUCCESS);
}