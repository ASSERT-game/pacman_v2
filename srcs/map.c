/***************************************************************************
 * FILENAME:    map.c
 * DESCRIPTION: The Game Map
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

void	fill_map(t_map *map_dest)
{
	memcpy((*map_dest)[ 0], "WWWWWWWWWWWWWWWWWWWWWWWWWWWW", GAME_COLS);
	memcpy((*map_dest)[ 1], "W............WW............W", GAME_COLS);
	memcpy((*map_dest)[ 2], "W.WWWW.WWWWW.WW.WWWWW.WWWW.W", GAME_COLS);
	memcpy((*map_dest)[ 3], "WPWWWW.WWWWW.WW.WWWWW.WWWWPW", GAME_COLS);
	memcpy((*map_dest)[ 4], "W.WWWW.WWWWW.WW.WWWWW.WWWW.W", GAME_COLS);
	memcpy((*map_dest)[ 5], "W..........................W", GAME_COLS);
	memcpy((*map_dest)[ 6], "W.WWWW.WW.WWWWWWWW.WW.WWWW.W", GAME_COLS);
	memcpy((*map_dest)[ 7], "W.WWWW.WW.WWWWWWWW.WW.WWWW.W", GAME_COLS);
	memcpy((*map_dest)[ 8], "W......WW....WW....WW......W", GAME_COLS);
	memcpy((*map_dest)[ 9], "WWWWWW.WWWWW.WW.WWWWW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[10], "WWWWWW.WWWWW.WW.WWWWW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[11], "WWWWWW.WW          WW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[12], "WWWWWW.WW WWWWWWWW WW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[13], "WWWWWW.WW W      W WW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[14], "      .   W      W   .      ", GAME_COLS);
	memcpy((*map_dest)[15], "WWWWWW.WW W      W WW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[16], "WWWWWW.WW WWWWWWWW WW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[17], "WWWWWW.WW          WW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[18], "WWWWWW.WW.WWWWWWWW.WW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[19], "WWWWWW.WW.WWWWWWWW.WW.WWWWWW", GAME_COLS);
	memcpy((*map_dest)[20], "W............WW............W", GAME_COLS);
	memcpy((*map_dest)[21], "W.WWWW.WWWWW.WW.WWWWW.WWWW.W", GAME_COLS);
	memcpy((*map_dest)[22], "W.WWWW.WWWWW.WW.WWWWW.WWWW.W", GAME_COLS);
	memcpy((*map_dest)[23], "WP..WW.......  .......WW..PW", GAME_COLS);
	memcpy((*map_dest)[24], "WWW.WW.WW.WWWWWWWW.WW.WW.WWW", GAME_COLS);
	memcpy((*map_dest)[25], "WWW.WW.WW.WWWWWWWW.WW.WW.WWW", GAME_COLS);
	memcpy((*map_dest)[26], "W......WW....WW....WW......W", GAME_COLS);
	memcpy((*map_dest)[27], "W.WWWWWWWWWW.WW.WWWWWWWWWW.W", GAME_COLS);
	memcpy((*map_dest)[28], "W.WWWWWWWWWW.WW.WWWWWWWWWW.W", GAME_COLS);
	memcpy((*map_dest)[29], "W..........................W", GAME_COLS);
	memcpy((*map_dest)[30], "WWWWWWWWWWWWWWWWWWWWWWWWWWWW", GAME_COLS);
}

void	draw_pellets(t_map map)
{
	size_t	i;
	size_t	j;

	SDLX_Sprite pellet;

	SDLX_new_Sprite(&pellet);
	fetch_ExtraSpriteInfo(&(pellet.sprite_data), 0);
	pellet._dst = (SDL_Rect){0, 0, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};

	i = 0;
	while (i < GAME_ROWS)
	{
		j = 0;
		while (j < GAME_COLS)
		{
			if (map[i][j] == '.')
			{
				pellet._dst.y = (i * 8 - 3) * DISPLAY_SCALE;
				pellet._dst.x = (j * 8 - 3) * DISPLAY_SCALE;
				SDLX_draw_animation(SDLX_GetDisplay()->renderer, &(pellet));
			}
			j++;
		}
		i++;
	}

	fetch_ExtraSpriteInfo(&(pellet.sprite_data), 2);
	pellet._dst = (SDL_Rect){1 * 8 * DISPLAY_SCALE - 8, 3 * 8 * DISPLAY_SCALE - 8, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};
	if (map[3][1] == 'P')	{ SDLX_draw_animation(SDLX_GetDisplay()->renderer, &(pellet)); }
	pellet._dst = (SDL_Rect){26 * 8 * DISPLAY_SCALE - 8, 3 * 8 * DISPLAY_SCALE - 8, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};
	if (map[3][26] == 'P')	{ SDLX_draw_animation(SDLX_GetDisplay()->renderer, &(pellet)); }
	pellet._dst = (SDL_Rect){1 * 8 * DISPLAY_SCALE - 8, 23 * 8 * DISPLAY_SCALE - 8, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};
	if (map[23][1] == 'P')	{ SDLX_draw_animation(SDLX_GetDisplay()->renderer, &(pellet)); }
	pellet._dst = (SDL_Rect){26 * 8 * DISPLAY_SCALE - 8, 23 * 8 * DISPLAY_SCALE - 8, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};
	if (map[23][26] == 'P')	{ SDLX_draw_animation(SDLX_GetDisplay()->renderer, &(pellet)); }
}
