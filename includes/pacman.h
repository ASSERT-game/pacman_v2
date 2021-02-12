/***************************************************************************
 * FILENAME:    pacman.h
 * DESCRIPTION: General header for pacman.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 01Feb2021
***************************************************************************/

#ifndef PACMAN_H
# define PACMAN_H

# include "SDLX.h"

# include "pacman_structs.h"
# include "pacman_assets.h"

# define ASSETS "assets/"

SDL_bool	input_entry(SDLX_GameInput *game_input);
void		init_input_mappers(void);

void		instance_ghost(t_ghost *dest, int ghost, int x, int y, void (*fn)(struct s_pmContext *));
void		update_ghost(t_pmContext *gContext, t_ghost *ghost);
void		realign_ghost(t_ghost *ghost);

void		target_clyde(t_pmContext *gContext);
void		target_inky(t_pmContext *gContext);
void		target_pinky(t_pmContext *gContext);
void		target_blinky(t_pmContext *gContext);
void		draw_target(int x, int y);

void		instance_player(t_pacman *player, int x, int y);
void		update_player(t_pmContext *gContext, t_pacman *player);
void		realign_player(t_pacman *player);

void		draw_pellets(t_map map);
void		fill_map(t_map *map_dest);
void		update_map(t_pmContext *gContext);

#endif
