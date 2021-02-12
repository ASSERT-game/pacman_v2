/***************************************************************************
 * FILENAME:    SDLX_utils.c
 * DESCRIPTION: Utility Functions that don't have a specific file.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 08Feb2021
***************************************************************************/

#include "SDLX.h"

SDLX_direction	SDLX_reverse_dir(SDLX_direction direction)
{
	direction.c.x *= -1;
	direction.c.y *= -1;

	return (direction);
}

SDLX_Sprite		*SDLX_new_Sprite(SDLX_Sprite *dst)
{
	if (dst == NULL)
		return (dst);

	dst->current = 0;

	dst->dst = &(dst->_dst);
	dst->angle = 0;
	dst->center = NULL;
	dst->flip = SDL_FLIP_NONE;

	return (dst);
}