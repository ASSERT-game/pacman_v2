/***************************************************************************
 * FILENAME:    SDLX_ticks.h
 * DESCRIPTION:
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 28Jan2021
***************************************************************************/

#ifndef SDLX_TICKS_H
# define SDLX_TICKS_H

# include "SDL2/SDL_timer.h"
# include "SDL2/SDL_log.h"

// 1 second = 1000 ms.
# define TICK_RATE (50)

int		SDLX_discrete_frames(int *ticks);

#endif
