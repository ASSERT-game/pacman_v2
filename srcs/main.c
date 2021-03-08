/***************************************************************************
 * FILENAME:    main.c
 * DESCRIPTION: Entry point for Pacman
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 01Feb2021
***************************************************************************/

#include "pacman.h"

void	pacman_initalize(t_pmContext *gContext)
{
	fill_map(&(gContext->map));
	gContext->ticks = 0;

	init_BackgrundSprite(&(gContext->background));
	SDLX_set_background(&(gContext->background));

	SDLX_RenderQueue_init(&(gContext->rQueue));

	instance_ghost(&(gContext->blinky),	SD_BLINKY | SD_GHOST_RIGHT, 12, 11, target_blinky);
	instance_ghost(&(gContext->pinky),	SD_PINKY  | SD_GHOST_RIGHT, 12, 11, target_pinky);
	instance_ghost(&(gContext->inky),	SD_INKY   | SD_GHOST_RIGHT, 13, 11, target_inky);
	instance_ghost(&(gContext->clyde),	SD_CLYDE  | SD_GHOST_RIGHT, 15, 11, target_clyde);

	instance_player(&(gContext->player), 14, 23);

	init_input_mappers();

	srand(0x9AC533D);

	gContext->clone = SDL_FALSE;
	gContext->pause = SDL_FALSE;
}

int	main(SDL_UNUSED int ac, SDL_UNUSED char *args[])
{
	SDL_bool	exit;
	t_pmContext	gContext;

	SDLX_GetDisplay();
	pacman_initalize(&(gContext));

	exit = SDL_FALSE;
	while (exit != SDL_TRUE)
	{
		exit = input_entry(&(g_GameInput));
		if (exit == SDL_TRUE)
			break ;

		if (g_GameInput.GameInput.button_GUIDE)
		{
			SDL_Log("Pressed");
			if (gContext.pause == SDL_FALSE)
			{
				gContext.pause = SDL_TRUE;
				SDL_Delay(140);
			}
			else
			{
				gContext.pause = SDL_FALSE;
				SDL_Delay(140);
			}
		}

		if (g_GameInput.GameInput.button_START)
			pacman_initalize(&(gContext));

		if (gContext.pause == SDL_FALSE)
		{
			update_ghost(&(gContext), &(gContext.blinky));
			update_ghost(&(gContext), &(gContext.pinky));
			update_ghost(&(gContext), &(gContext.inky));
			update_ghost(&(gContext), &(gContext.clyde));

			update_player(&(gContext), &(gContext.player));

			update_map(&(gContext));
		}

		if (exit != SDL_TRUE && SDLX_discrete_frames(&(gContext.ticks)) != EXIT_FAILURE)
		{
			draw_pellets(gContext.map);
			SDLX_RenderQueue_flush(&(gContext.rQueue), SDLX_GetDisplay()->renderer);
			SDLX_screen_reset(SDLX_GetDisplay()->renderer, NULL);
		}
		gContext.rQueue.index = 0;
	}
	return (EXIT_SUCCESS);
}
