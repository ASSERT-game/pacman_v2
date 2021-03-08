/***************************************************************************
 * FILENAME:    update.c
 * DESCRIPTION: Pacman common game update code.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 09Feb2021
***************************************************************************/

#include "pacman.h"

void	update_map(t_pmContext *gContext)
{
	int	p_x;
	int	p_y;

	p_x = gContext->player.x;
	p_y = gContext->player.y;

	if (gContext->map[p_y][p_x] == '.')
	{
		gContext->map[p_y][p_x] = ' ';
		if (SDLX_XboxController_link(0) != NULL)
			SDL_GameControllerRumble(SDLX_XboxController_link(0), 0x0100, 0xFF00, 30);
	}
	if (gContext->map[p_y][p_x] == 'P')
	{
		gContext->blinky.mode = GM_FRIGHTEN;
		fetch_GhostSpriteInfo(&(gContext->blinky.sprite.sprite_data), SD_GHOST_FRIGTHEN);
		gContext->pinky.mode = GM_FRIGHTEN;
		fetch_GhostSpriteInfo(&(gContext->pinky.sprite.sprite_data), SD_GHOST_FRIGTHEN);
		gContext->inky.mode = GM_FRIGHTEN;
		fetch_GhostSpriteInfo(&(gContext->inky.sprite.sprite_data), SD_GHOST_FRIGTHEN);
		gContext->clyde.mode = GM_FRIGHTEN;
		fetch_GhostSpriteInfo(&(gContext->clyde.sprite.sprite_data), SD_GHOST_FRIGTHEN);
		gContext->map[p_y][p_x] = ' ';
		gContext->fright_ticks = 70;
	}

	gContext->clone |= g_GameInput.GameInput.button_B;

	p_x = gContext->player.x_i;
	p_y = gContext->player.y_i;
	if (gContext->map[p_y][p_x] == '.' && gContext->clone)
	{
		gContext->map[p_y][p_x] = ' ';
		if (SDLX_XboxController_link(0) != NULL)
			SDL_GameControllerRumble(SDLX_XboxController_link(0), 0x0100, 0xFF00, 30);
	}

	if (gContext->fright_ticks > 0)
		gContext->fright_ticks--;
}
