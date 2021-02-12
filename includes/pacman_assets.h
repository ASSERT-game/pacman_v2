/***************************************************************************
 * FILENAME:    pacman_assets.h
 * DESCRIPTION: Header file for the fetch functions and enumns
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 02Feb2021
***************************************************************************/

#ifndef PACMAN_ASSETS_H
# define PACMAN_ASSETS_H

# include "SDLX.h"

enum	background_sprites
{
	SD_BACKGROUND,
};

int		init_BackgrundSprite(SDLX_Sprite *dest);
int		fetch_BackgroundSpriteInfo(SDLX_Sprite_Data **dst, int no);
int		fetch_ExtraSpriteInfo(SDLX_Sprite_Data **dst, int no);

enum	ghost_sprites
{
	SD_GHOST_NONE = 0b0,
	SD_BLINKY,
	SD_PINKY,
	SD_INKY,
	SD_CLYDE,

	SD_GHOST_DIR		= 0b0000011,
	SD_GHOST_UP			= 0b0000000,
	SD_GHOST_DOWN		= 0b0001000,
	SD_GHOST_LEFT		= 0b0010000,
	SD_GHOST_RIGHT		= 0b0011000,
	SD_GHOST_FRIGTHEN	= 0b0100000,
	SD_GHOST_EYES		= 0b1000000,
};

int		fetch_GhostSpriteInfo(SDLX_Sprite_Data **dst, int no);

enum	pacman_sprites
{
	SD_PACMAN = 0b0,

	SD_PACMAN_DIR		= 0b011,
	SD_PACMAN_UP		= 0b000,
	SD_PACMAN_DOWN		= 0b001,
	SD_PACMAN_LEFT		= 0b010,
	SD_PACMAN_RIGHT		= 0b011,

	SD_PACMAN_DEATH		= 0b100,
};

int		fetch_PacManSpriteInfo(SDLX_Sprite_Data **dst, int no);

#endif
