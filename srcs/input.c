/***************************************************************************
 * FILENAME:    input.c
 * DESCRIPTION: Input manager and control file.
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

SDLX_iMap	*pacman_key_map(size_t *size)
{
	static SDLX_iMap	key_map[] =
	{
		(SDLX_iMap){&BMAP(button_A), 1, SDL_SCANCODE_A},

		(SDLX_iMap){&BMAP(button_DPAD_LEFT),	1, SDL_SCANCODE_LEFT},
		(SDLX_iMap){&BMAP(button_DPAD_RIGHT),	1, SDL_SCANCODE_RIGHT},
		(SDLX_iMap){&BMAP(button_DPAD_UP),		1, SDL_SCANCODE_UP},
		(SDLX_iMap){&BMAP(button_DPAD_DOWN),	1, SDL_SCANCODE_DOWN},

		(SDLX_iMap){&BMAP(button_DPAD_LEFT),	1, SDL_SCANCODE_A},
		(SDLX_iMap){&BMAP(button_DPAD_RIGHT),	1, SDL_SCANCODE_D},
		(SDLX_iMap){&BMAP(button_DPAD_UP),		1, SDL_SCANCODE_W},
		(SDLX_iMap){&BMAP(button_DPAD_DOWN),	1, SDL_SCANCODE_S},

		(SDLX_iMap){&BMAP(button_START),	1, SDL_SCANCODE_R},
	};

	*size = sizeof(key_map) / sizeof(*key_map);
	return (&key_map[0]);
}

SDLX_iMap	*pacman_pad_map(size_t *size)
{
	static SDLX_iMap	key_map[] =
	{
		(SDLX_iMap){&BMAP(button_DPAD_LEFT),	1, SDL_CONTROLLER_BUTTON_DPAD_LEFT},
		(SDLX_iMap){&BMAP(button_DPAD_RIGHT),	1, SDL_CONTROLLER_BUTTON_DPAD_RIGHT},
		(SDLX_iMap){&BMAP(button_DPAD_UP),		1, SDL_CONTROLLER_BUTTON_DPAD_UP},
		(SDLX_iMap){&BMAP(button_DPAD_DOWN),	1, SDL_CONTROLLER_BUTTON_DPAD_DOWN},

		(SDLX_iMap){&BMAP(button_START),	1, SDL_CONTROLLER_BUTTON_START},
		(SDLX_iMap){&BMAP(button_GUIDE),	1, SDL_CONTROLLER_BUTTON_BACK},

		(SDLX_iMap){&BMAP(button_B),	1, SDL_CONTROLLER_BUTTON_B},
	};

	*size = sizeof(key_map) / sizeof(*key_map);
	return (&key_map[0]);
}

void	init_input_mappers(void)
{
	g_GameInput.key_mapper.map_arr = pacman_key_map(&(g_GameInput.key_mapper.amount));
	g_GameInput.pad_mapper.map_arr = pacman_pad_map(&(g_GameInput.pad_mapper.amount));
}

SDL_bool	input_entry(SDLX_GameInput *game_input)
{
	SDL_GameController	*controller;
	const Uint8			*keystate;
	SDL_Event	event;
	SDL_bool	exit;
	int			pad;

	exit = SDL_FALSE;
	/* Or do a memcpy of a previous saved input state here */
	SDL_memset(&(game_input->GameInput), 0, sizeof(game_input->GameInput));
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			exit = SDL_TRUE;
			SDL_Log("Exit");
			return (exit);
		}
	}

	keystate = SDL_GetKeyboardState(NULL);
	SDLX_KeyMap(&(game_input->key_mapper), keystate);

	controller = SDLX_XboxController_link(0);
	if (controller != NULL)
	{
		SDLX_ControllerMap(&(game_input->pad_mapper), controller);
		SDLX_FillXbox_Axis(game_input, controller);

		pad = SDLX_AxisConvert(&(game_input->GameInput.leftaxis));
		SDLX_toDPAD(game_input, pad);
		pad = SDLX_AxisConvert(&(game_input->GameInput.rightaxis));
		SDLX_toDPAD(game_input, pad);
	}

	return (exit);
}
