/***************************************************************************
 * FILENAME:    SDLX_background.c
 * DESCRIPTION: Handles setting an automatic background.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 09Feb2021
***************************************************************************/

#include "SDLX.h"

SDLX_Sprite	**SDLX_internal_background(void)
{
	static SDLX_Sprite *background;
	return (&(background));
}

SDLX_Sprite	*SDLX_get_background(void) { return (*SDLX_internal_background()); }

void		SDLX_set_background(SDLX_Sprite *src) { *SDLX_internal_background() = src; }
