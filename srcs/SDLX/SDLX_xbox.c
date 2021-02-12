/***************************************************************************
 * FILENAME:    SDLX_xbox.c
 * DESCRIPTION: SDLX file for handling xbox controller input
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 03Feb2021
***************************************************************************/

#include "SDLX.h"

SDL_GameController	*SDLX_XboxController_link(int player_no)
{
	SDL_GameController *controller;

	controller = SDL_GameControllerFromPlayerIndex(player_no);
	if (controller == NULL)
	{
		/* Some Function goes here to ensure other players
		controllers aren't being used */
		controller = SDL_GameControllerOpen(0);
	}
	// SDL_Log("Res: %p", controller);

	return (controller);
}

void	SDLX_FillXbox_Axis(SDLX_GameInput *game_input, SDL_GameController *controller)
{
	game_input->GameInput.leftaxis.x	= SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	game_input->GameInput.leftaxis.y	= SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
	game_input->GameInput.rightaxis.x	= SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
	game_input->GameInput.rightaxis.y	= SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
}
