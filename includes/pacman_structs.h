/***************************************************************************
 * FILENAME:    pacman_structs.h
 * DESCRIPTION: Structs to be used in the PacMan application.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 02Feb2021
***************************************************************************/

#include "SDLX.h"

struct s_pmContext;

enum	ghost_state
{
	GM_NONE,
	GM_EATEN,
	GM_FRIGHTEN,
	GM_CHASE,
};

typedef struct	s_ghost
{
	int			x;
	int			y;

	int			tar_x;
	int			tar_y;

	int				mode;
	SDLX_direction	from;

	int			ghost;
	SDLX_Sprite	sprite;

	void		(*ghost_target)(struct s_pmContext *);
}				t_ghost;

typedef struct	s_pacman
{
	int			x;
	int			y;

	int			prev_x;
	int			prev_y;

	SDLX_direction	facing;

	SDLX_Sprite		sprite;

	int			x_i;
	int			y_i;

	SDLX_direction	facing_i;

	SDLX_Sprite		sprite_i;

	SDL_bool		dead;
}				t_pacman;

#define GAME_COLS 29
#define GAME_ROWS 31

typedef char t_map[GAME_ROWS][GAME_COLS];

typedef struct	s_pmContext
{
	t_map		map;
	int			ticks;
	SDLX_Sprite	background;

	SDLX_RenderQueue	rQueue;

	int					fright_ticks;
	t_ghost				blinky;
	t_ghost				pinky;
	t_ghost				inky;
	t_ghost				clyde;

	t_pacman			player;

	SDLX_GameInput		game_in;

	SDL_bool			clone;
	SDL_bool			pause;

}				t_pmContext;
