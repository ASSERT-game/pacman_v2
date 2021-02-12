/***************************************************************************
 * FILENAME:	SDLX_structs.h
 * DESCRIPTION: Structures to be used by SDLX and external files.
 *
 * ENVIRONMENT:
 *	 macOS High Sierra 10.13.6
 *	 Visual Studio Code 1.52.1
 * AUTHORS:
 *	 Kevin Colour
 * DATES:
 *	 Created: 24Jan2021
***************************************************************************/

#ifndef SDLX_structs_H
#define SDLX_structs_H

# include "SDL2/SDL.h"

# include "SDLX_const.h"

typedef struct SDLX_Display
{
	SDL_Renderer	*renderer;
	SDL_Window		*window;
}	SDLX_Display;

typedef struct SDLX_Sprite_Data
{
	SDL_Texture		*texture;
	SDL_Rect		_src;
	SDL_Rect		*src;
	size_t			cycle;
}	SDLX_Sprite_Data;

typedef struct SDLX_Sprite
{
	SDLX_Sprite_Data	*sprite_data;

	size_t				current;
	SDL_Rect			_dst;
	SDL_Rect			*dst;

	double				angle;
	SDL_Point			_center;
	SDL_Point			*center;
	SDL_RendererFlip	flip;
}	SDLX_Sprite;

typedef struct SDLX_RenderQueue
{
	size_t			index;
	size_t			capacity;

	SDLX_Sprite		**content;
}	SDLX_RenderQueue;

typedef struct	SDLX_iMap
{
	int			*dest;
	int			values;
	int			param;
}				SDLX_iMap;

typedef struct	SDLX_input_mapper
{
	size_t		amount;

	SDLX_iMap	*map_arr;
}				SDLX_input_mapper;

typedef struct	SDLX_GameInput
{
	SDLX_input_mapper	key_mapper;
	SDLX_input_mapper	pad_mapper;

	struct
	{
		int	button_A;
		int	button_B;
		int	button_X;
		int	button_Y;
		int	button_BACK;
		int	button_GUIDE;
		int	button_START;
		int	button_LEFTSTICK;
		int	button_RIGHTSTICK;
		int	button_LEFTSHOULDER;
		int	button_RIGHTSHOULDER;
		int	button_DPAD_UP;
		int	button_DPAD_DOWN;
		int	button_DPAD_LEFT;
		int	button_DPAD_RIGHT;

		int	num0;
		int	num1;
		int	num2;
		int	num3;
		int	num4;
		int	num5;
		int	num6;
		int	num7;
		int	num8;
		int	num9;

		SDL_Point primary;

		int	primleft;
		int	primright;

		SDL_Point second;

		int	secleft;
		int	secright;

		SDL_Point leftaxis;
		SDL_Point rightaxis;

	}	GameInput;
}				SDLX_GameInput;

SDLX_GameInput	g_GameInput;

#define BMAP(button) (g_GameInput.GameInput.button)

enum	SDLX_DIR
{
	SDLX_DIR_NONE	= 0x0000,

	/* These have the properties of Euclidian direction. */
	SDLX_ELEFT		= 0x00FF,
	SDLX_ERIGHT		= 0x0001,
	SDLX_EUP		= 0x0100,
	SDLX_EDOWN		= 0xFF00,

	/* These are made with the caution that arrays reverse up and down. */
	SDLX_ALEFT		= SDLX_ELEFT,
	SDLX_ARIGHT		= SDLX_ERIGHT,
	SDLX_AUP		= SDLX_EDOWN,
	SDLX_ADOWN		= SDLX_EUP,

	SDLX_LEFT		= SDLX_ALEFT,
	SDLX_RIGHT		= SDLX_ARIGHT,
	SDLX_UP			= SDLX_AUP,
	SDLX_DOWN		= SDLX_ADOWN,
};

typedef union SDLX_direction
{
	int			val;
	struct
	{
		int8_t	x;
		int8_t	y;
	}			c;
}	SDLX_direction;

#endif
