/***************************************************************************
 * FILENAME:    ghost.c
 * DESCRIPTION: File to make and return the ghost textures.
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

#define GHOST_TILE_SIZE (16)

SDLX_Sprite_Data	*carve_ghost_sprite(void)
{
	size_t				i;
	size_t				j;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(8 * 5, sizeof(*result));
	texture = IMG_LoadTexture(SDLX_GetDisplay()->renderer, ASSETS"pacman_ghost.png");

	i = 0;
	/* Ghost frames */
	while (i < 4)
	{
		j = 0;
		while (j < 8)
		{
			result[i * 8 + j].texture = texture;
			result[i * 8 + j]._src = (SDL_Rect){j * GHOST_TILE_SIZE, i * GHOST_TILE_SIZE, GHOST_TILE_SIZE, GHOST_TILE_SIZE};
			result[i * 8 + j].src = &(result[i * 8 + j]._src);
			result[i * 8 + j].cycle = 2;
			j++;
		}
		i++;
	}

	/* Frigthen frames */
	j = 0;
	while (i + j < i + 4)
	{
		result[i * 8 + j].texture = texture;
		result[i * 8 + j]._src = (SDL_Rect){j * GHOST_TILE_SIZE, i * GHOST_TILE_SIZE, GHOST_TILE_SIZE, GHOST_TILE_SIZE};
		result[i * 8 + j].src = &(result[i * 8 + j]._src);
		result[i * 8 + j].cycle = 4;
		j++;
	}

	/* Eaten frames */
	while (i + j < i + 8)
	{
		result[i * 8 + j].texture = texture;
		result[i * 8 + j]._src = (SDL_Rect){j * GHOST_TILE_SIZE, i * GHOST_TILE_SIZE, GHOST_TILE_SIZE, GHOST_TILE_SIZE};
		result[i * 8 + j].src = &(result[i * 8 + j]._src);
		result[i * 8 + j].cycle = 1;
		j++;
	}
	return (result);
}

int		fetch_GhostSpriteInfo(SDLX_Sprite_Data **dst, int no)
{
	int	ghost;
	int	ghost_direction;
	static SDLX_Sprite_Data *sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_ghost_sprite();

	ghost = (no & 0b111);
	ghost_direction = (no >> 3) & SD_GHOST_DIR;

		 if (no == SD_GHOST_FRIGTHEN) { (*dst) = &(sprite_arr[4 * 8]); return (EXIT_SUCCESS); }
	else if (no == SD_GHOST_EYES)	{ (*dst) = &(sprite_arr[4 * 8 + 4 + ghost_direction]); return (EXIT_SUCCESS); }
	else if (ghost == SD_BLINKY)	{ (*dst) = &(sprite_arr[(ghost - 1) * 8 + ghost_direction * 2]); return (EXIT_SUCCESS); }
	else if (ghost == SD_PINKY)		{ (*dst) = &(sprite_arr[(ghost - 1) * 8 + ghost_direction * 2]); return (EXIT_SUCCESS); }
	else if (ghost == SD_INKY)		{ (*dst) = &(sprite_arr[(ghost - 1) * 8 + ghost_direction * 2]); return (EXIT_SUCCESS); }
	else if (ghost == SD_CLYDE)		{ (*dst) = &(sprite_arr[(ghost - 1) * 8 + ghost_direction * 2]); return (EXIT_SUCCESS); }
	else { *dst = NULL; return (EXIT_FAILURE);}
}
