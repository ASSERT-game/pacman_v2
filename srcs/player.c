/***************************************************************************
 * FILENAME:    player.c
 * DESCRIPTION: General File to manage the player
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

#define PACMAN_TILE_SIZE (16)

SDLX_Sprite_Data	*carve_pacman_sprite(void)
{
	size_t	i;
	size_t	j;
	SDL_Texture			*texture;
	SDLX_Sprite_Data	*result;

	result = SDL_calloc(4 * 4 + 4 * 4 + 11, sizeof(*result));
	texture = IMG_LoadTexture(SDLX_GetDisplay()->renderer, ASSETS"pacman_pacman.png");

	i = 0;
	/* PacMan's 4 stages */
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result[i * 4 + j].texture = texture;
			result[i * 4 + j]._src = (SDL_Rect){j * PACMAN_TILE_SIZE, i * PACMAN_TILE_SIZE, PACMAN_TILE_SIZE, PACMAN_TILE_SIZE};
			result[i * 4 + j].src = &(result[i * 4 + j]._src);
			result[i * 4 + j].cycle = 4;
			j++;
		}
		i++;
	}

	/* Clone's 4 stages */
	while (i < 8)
	{
		j = 0;
		while (j < 4)
		{
			result[i * 4 + j].texture = texture;
			result[i * 4 + j]._src = (SDL_Rect){j * PACMAN_TILE_SIZE, i * PACMAN_TILE_SIZE, PACMAN_TILE_SIZE, PACMAN_TILE_SIZE};
			result[i * 4 + j].src = &(result[i * 4 + j]._src);
			result[i * 4 + j].cycle = 4;
			j++;
		}
		i++;
	}

	j = 0;
	while (j < 11)
	{
		result[8 * 4 + j].texture = texture;
		result[8 * 4 + j]._src = (SDL_Rect){j * PACMAN_TILE_SIZE, i * PACMAN_TILE_SIZE, PACMAN_TILE_SIZE, PACMAN_TILE_SIZE};
		result[8 * 4 + j].src = &(result[i * 4 + j]._src);
		result[8 * 4 + j].cycle = 11;
		j++;
	}
	return (result);
}

int		fetch_PacManSpriteInfo(SDLX_Sprite_Data **dst, int no)
{
	static SDLX_Sprite_Data *sprite_arr;

	if (sprite_arr == NULL)
		sprite_arr = carve_pacman_sprite();

		 if (no == SD_PACMAN_LEFT)	{ (*dst) = &(sprite_arr[0 * 4]); return (EXIT_SUCCESS);}
	else if (no == SD_PACMAN_RIGHT)	{ (*dst) = &(sprite_arr[1 * 4]); return (EXIT_SUCCESS);}
	else if (no == SD_PACMAN_UP)	{ (*dst) = &(sprite_arr[2 * 4]); return (EXIT_SUCCESS);}
	else if (no == SD_PACMAN_DOWN)	{ (*dst) = &(sprite_arr[3 * 4]); return (EXIT_SUCCESS);}
	else if (no == SD_CLONE_LEFT)	{ (*dst) = &(sprite_arr[4 * 4]); SDL_Log("Clone Left"); return (EXIT_SUCCESS);}
	else if (no == SD_CLONE_RIGHT)	{ (*dst) = &(sprite_arr[5 * 4]); SDL_Log("Clone Right"); return (EXIT_SUCCESS);}
	else if (no == SD_CLONE_UP)		{ (*dst) = &(sprite_arr[6 * 4]); SDL_Log("Clone Up"); return (EXIT_SUCCESS);}
	else if (no == SD_CLONE_DOWN)	{ (*dst) = &(sprite_arr[7 * 4]); SDL_Log("Clone Down"); return (EXIT_SUCCESS);}
	else if (no == SD_PACMAN_DEATH)	{ (*dst) = &(sprite_arr[8 * 4]); return (EXIT_SUCCESS);}
	else { (*dst) = NULL; return (EXIT_FAILURE);}
}

void	instance_player(t_pacman *player, int x, int y)
{
	player->x = x;
	player->y = y;

	player->x_i = x;
	player->y_i = y;

	SDLX_new_Sprite(&(player->sprite));
	fetch_PacManSpriteInfo(&(player->sprite.sprite_data), SD_PACMAN_UP);
	player->sprite._dst = (SDL_Rect){0, 0, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};

	SDLX_new_Sprite(&(player->sprite_i));
	fetch_PacManSpriteInfo(&(player->sprite_i.sprite_data), SD_CLONE_UP);
	player->sprite_i._dst = (SDL_Rect){0, 0, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};

	realign_player(player);

	player->dead = SDL_FALSE;
}

void	realign_player(t_pacman *player)
{
	player->sprite.dst->x = (4 + ((player->x - 1) * 8)) * DISPLAY_SCALE;
	player->sprite.dst->y = (4 + ((player->y - 1) * 8)) * DISPLAY_SCALE;

	player->sprite_i.dst->x = (4 + ((player->x_i - 1) * 8)) * DISPLAY_SCALE;
	player->sprite_i.dst->y = (4 + ((player->y_i - 1) * 8)) * DISPLAY_SCALE;
}

void	move_player(SDLX_GameInput *input, t_pacman *player, t_map map)
{
	int	x;
	int	y;
	SDLX_direction	new_dir;

	new_dir.val = SDLX_DIR_NONE;
	if (input->GameInput.button_DPAD_RIGHT)	new_dir.val = SDLX_RIGHT;
	if (input->GameInput.button_DPAD_LEFT)	new_dir.val = SDLX_LEFT;
	if (input->GameInput.button_DPAD_DOWN)	new_dir.val = SDLX_DOWN;
	if (input->GameInput.button_DPAD_UP)	new_dir.val = SDLX_UP;

	x = player->x;
	y = player->y;
	if (map[y + new_dir.c.y][x + new_dir.c.x] != 'W' && new_dir.val != SDLX_DIR_NONE)
	{
		player->x += new_dir.c.x;
		player->y += new_dir.c.y;
		if (input->GameInput.button_DPAD_RIGHT) {fetch_PacManSpriteInfo(&(player->sprite.sprite_data), SD_PACMAN_RIGHT); player->facing.val = SDLX_RIGHT;}
		if (input->GameInput.button_DPAD_LEFT)	{fetch_PacManSpriteInfo(&(player->sprite.sprite_data), SD_PACMAN_LEFT);	 player->facing.val = SDLX_LEFT;}
		if (input->GameInput.button_DPAD_DOWN)	{fetch_PacManSpriteInfo(&(player->sprite.sprite_data), SD_PACMAN_DOWN);	 player->facing.val = SDLX_DOWN;}
		if (input->GameInput.button_DPAD_UP)	{fetch_PacManSpriteInfo(&(player->sprite.sprite_data), SD_PACMAN_UP);	 player->facing.val = SDLX_UP;}
	}
	else if (map[player->y + player->facing.c.y][player->x + player->facing.c.x] != 'W')
	{
		player->x += player->facing.c.x;
		player->y += player->facing.c.y;
	}

	// x = player->x_i;
	// y = player->y_i;
	// if (new_dir.val == SDLX_LEFT || new_dir.val == SDLX_RIGHT)
	// 	new_dir = SDLX_reverse_dir(new_dir);
	// if (map[y + new_dir.c.y][x + new_dir.c.x] != 'W' && new_dir.val != SDLX_DIR_NONE)
	// {
	// 	player->x_i += new_dir.c.x;
	// 	player->y_i += new_dir.c.y;
	// 	if (input->GameInput.button_DPAD_LEFT)	{fetch_PacManSpriteInfo(&(player->sprite_i.sprite_data), SD_CLONE_RIGHT);	player->facing_i.val = SDLX_RIGHT;}
	// 	if (input->GameInput.button_DPAD_RIGHT)	{fetch_PacManSpriteInfo(&(player->sprite_i.sprite_data), SD_CLONE_LEFT);	player->facing_i.val = SDLX_LEFT;}
	// 	if (input->GameInput.button_DPAD_UP)	{fetch_PacManSpriteInfo(&(player->sprite_i.sprite_data), SD_CLONE_UP);		player->facing_i.val = SDLX_UP;}
	// 	if (input->GameInput.button_DPAD_DOWN)	{fetch_PacManSpriteInfo(&(player->sprite_i.sprite_data), SD_CLONE_DOWN);	player->facing_i.val = SDLX_DOWN;}
	// }
	// else if (map[player->y_i + player->facing_i.c.y][player->x_i + player->facing_i.c.x] != 'W')
	// {
	// 	player->x_i += player->facing_i.c.x;
	// 	player->y_i += player->facing_i.c.y;
	// }
}

void	update_player(t_pmContext *gContext, t_pacman *player)
{
	player->sprite.current++;

	player->sprite_i.current++;

	player->prev_x = player->x;
	player->prev_y = player->y;

	if (player->dead == SDL_TRUE)
	{
		// SDLX_RenderQueue_add(&(gContext->rQueue), &(player->sprite_i));
		if (gContext->ticks % 2 == 0)
			player->sprite.current--;
		SDLX_RenderQueue_add(&(gContext->rQueue), &(player->sprite));
		if (player->sprite.current != player->sprite.sprite_data->cycle)
			return ;
		else
		{
			player->dead = SDL_FALSE;
			fetch_PacManSpriteInfo(&(gContext->player.sprite.sprite_data), SD_PACMAN_UP);
			player->x = 14;
			player->y = 23;
		}
	}

	move_player(&(g_GameInput), player, gContext->map);

	player->x += (GAME_COLS - 1);
	player->x %= (GAME_COLS - 1);

	player->x_i += (GAME_COLS - 1);
	player->x_i %= (GAME_COLS - 1);

	realign_player(player);
	SDLX_RenderQueue_add(&(gContext->rQueue), &(player->sprite));
	// SDLX_RenderQueue_add(&(gContext->rQueue), &(player->sprite_i));
}
