/***************************************************************************
 * FILENAME:    ghost.c
 * DESCRIPTION: General File to manage the PacMan ghost.
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

void	instance_ghost(t_ghost *dest, int ghost, int x, int y, void (*fn)(struct s_pmContext *))
{
	dest->ghost = ghost;
	fetch_GhostSpriteInfo(&(dest->sprite.sprite_data), ghost);
	SDLX_new_Sprite(&(dest->sprite));

	dest->sprite._dst = (SDL_Rect){0, 0, 16 * DISPLAY_SCALE, 16 * DISPLAY_SCALE};

	dest->x = x;
	dest->y = y;

	dest->tar_x = 0;
	dest->tar_y = 0;

	dest->mode = GM_CHASE;
	dest->ghost_target = fn;
}

void	realign_ghost(t_ghost *ghost)
{
	ghost->sprite.dst->x = (4 + ((ghost->x - 1) * 8)) * DISPLAY_SCALE;
	ghost->sprite.dst->y = (4 + ((ghost->y - 1) * 8)) * DISPLAY_SCALE;
}

void	target_blinky(t_pmContext *gContext)
{
	gContext->blinky.tar_x = gContext->player.x;
	gContext->blinky.tar_y = gContext->player.y;
}

void	target_pinky(t_pmContext *gContext)
{
	gContext->pinky.tar_x = gContext->player.x;
	gContext->pinky.tar_y = gContext->player.y;

	if (gContext->player.facing.val == SDLX_UP)
	{
		gContext->pinky.tar_x = gContext->player.x - 4;
		gContext->pinky.tar_y = gContext->player.y - 4;
	}
	else if (gContext->player.facing.val == SDLX_DOWN)
		gContext->pinky.tar_y = gContext->player.y  + 4;
	else if (gContext->player.facing.val == SDLX_LEFT)
		gContext->pinky.tar_x = gContext->player.x - 4;
	else if (gContext->player.facing.val == SDLX_RIGHT)
		gContext->pinky.tar_x = gContext->player.x + 4;
}

void	target_inky(t_pmContext *gContext)
{
	int	m_x;
	int	m_y;

	int	d_x;
	int	d_y;

	m_x = gContext->player.x;
	m_y = gContext->player.y;

	if (gContext->player.facing.val == SDLX_UP)
	{
		m_x = gContext->player.x - 2;
		m_y = gContext->player.y - 2;
	}
	else if (gContext->player.facing.val == SDLX_DOWN)
		m_y = gContext->player.y  + 2;
	else if (gContext->player.facing.val == SDLX_LEFT)
		m_x = gContext->player.x - 2;
	else if (gContext->player.facing.val == SDLX_RIGHT)
		m_x = gContext->player.x + 2;

	d_x = gContext->blinky.x - m_x;
	d_y = gContext->blinky.y - m_y;

	gContext->inky.tar_x = m_x - d_x;
	gContext->inky.tar_y = m_y - d_y;
}

void	target_clyde(t_pmContext *gContext)
{
	int	dis_to_pacman;
	int	x;
	int	y;
	int	p_x;
	int	p_y;

	x = gContext->clyde.x;
	y = gContext->clyde.y;
	p_x = gContext->player.x;
	p_y = gContext->player.y;
	dis_to_pacman = (p_x - x) * (p_x - x) + (p_y - y) * (p_y - y);
	if (dis_to_pacman > 64)
	{
		gContext->clyde.tar_x = gContext->player.x;
		gContext->clyde.tar_y = gContext->player.y;
	}
	else
	{
		gContext->clyde.tar_x = 0;
		gContext->clyde.tar_y = 32;
	}
}

void	draw_target(int x, int y)
{
	SDL_Rect	dst;

	SDL_SetRenderDrawColor(SDLX_GetDisplay()->renderer, 255, 0, 0, 0);

	dst.x = (x * 8) * DISPLAY_SCALE - 8;
	dst.y = (y * 8) * DISPLAY_SCALE - 8;

	dst.w = 16 * DISPLAY_SCALE;
	dst.h = 16 * DISPLAY_SCALE;
	SDL_RenderDrawRect(SDLX_GetDisplay()->renderer, &dst);
}

void	move_ghost(t_ghost *ghost, t_map map)
{
	int				min;
	int				dis;
	SDLX_direction	dir;
	SDLX_direction	go;
	SDL_bool		up_block;
	int				x;
	int				y;

	min = SDL_MAX_SINT32;
	up_block = SDL_FALSE;
	x = (ghost->x);
	y = (ghost->y);
	if ((x == 12 && y == 11) ||
		(x == 12 && y == 23) ||
		(x == 15 && y == 11) ||
		(x == 15 && y == 23))
		up_block = SDL_TRUE;

	go.val = SDLX_DIR_NONE;
	dir.val = SDLX_UP;
	dis = (y + dir.c.y - ghost->tar_y) * (y + dir.c.y - ghost->tar_y) + (x + dir.c.x - ghost->tar_x) * (x + dir.c.x - ghost->tar_x);
	if (map[y - 1][x] != 'W' && min > dis && ghost->from.val != SDLX_DOWN && up_block == SDL_FALSE)
	{
		go.val = SDLX_UP;
		min = dis;
	}
	dir.val = SDLX_LEFT;
	dis = (y + dir.c.y - ghost->tar_y) * (y + dir.c.y - ghost->tar_y) + (x + dir.c.x - ghost->tar_x) * (x + dir.c.x - ghost->tar_x);
	if (map[y + dir.c.y][x - 1] != 'W' && min > dis && ghost->from.val != SDLX_RIGHT)
	{
		go.val = SDLX_LEFT;
		min = dis;
	}
	dir.val = SDLX_DOWN;
	dis = (y + dir.c.y - ghost->tar_y) * (y + dir.c.y - ghost->tar_y) + (x + dir.c.x - ghost->tar_x) * (x + dir.c.x - ghost->tar_x);
	if (map[y + dir.c.y][x + dir.c.x] != 'W' && min > dis && ghost->from.val != SDLX_UP)
	{
		go.val = SDLX_DOWN;
		min = dis;
	}
	dir.val = SDLX_RIGHT;
	dis = (y + dir.c.y - ghost->tar_y) * (y + dir.c.y - ghost->tar_y) + (x + dir.c.x - ghost->tar_x) * (x + dir.c.x - ghost->tar_x);
	if (map[y][x + dir.c.x] != 'W' && min > dis && ghost->from.val != SDLX_LEFT)
	{
		go.val = SDLX_RIGHT;
		min = dis;
	}

	ghost->from = go;
	ghost->x += go.c.x;
	ghost->y += go.c.y;
}

SDL_bool	ghost_player_collision(t_ghost *ghost, t_pacman *player)
{
	SDL_bool	result;

	result = SDL_FALSE;
	if (ghost->x == player->x && ghost->y == player->y)	result = SDL_TRUE;
	if (ghost->x == player->prev_x && ghost->y == player->prev_y)	result = SDL_TRUE;

	return (result);
}

void	move_random_dir(t_ghost *ghost, t_map map)
{
	int	gen;
	SDLX_direction try;

	gen = rand() % 4;
	if (gen == 0) try.val = SDLX_UP;
	if (gen == 1) try.val = SDLX_LEFT;
	if (gen == 2) try.val = SDLX_RIGHT;
	if (gen == 3) try.val = SDLX_DOWN;

	if (map[ghost->y + try.c.y][ghost->x + try.c.x] != 'W' && try.val != SDLX_reverse_dir(ghost->from).val)
	{
		ghost->x += try.c.x;
		ghost->y += try.c.y;
		ghost->from = try;
	}
	else if (map[ghost->y + ghost->from.c.y][ghost->x + ghost->from.c.x] != 'W')
	{
		ghost->x += ghost->from.c.x;
		ghost->y += ghost->from.c.y;
	}
}

void	update_ghost(t_pmContext *gContext, t_ghost *ghost)
{
	t_pacman	*player;

	player = &(gContext->player);
	if (ghost->mode == GM_FRIGHTEN)
	{
		if (ghost_player_collision(ghost, &(gContext->player)))
		{
			fetch_GhostSpriteInfo(&(ghost->sprite.sprite_data), SD_GHOST_EYES);
			ghost->mode = GM_EATEN;
		}
		if (gContext->fright_ticks == 0)
		{
			fetch_GhostSpriteInfo(&(ghost->sprite.sprite_data), ghost->ghost);
			ghost->mode = GM_CHASE;
		}
		move_random_dir(ghost, gContext->map);
	}
	else if (ghost->mode == GM_CHASE)
	{
		ghost->ghost_target(gContext);
		if (gContext->ticks % 4 != 1)
			move_ghost(ghost, gContext->map);
		if (ghost_player_collision(ghost, &(gContext->player)) && gContext->player.dead != SDL_TRUE)
		{
			gContext->player.dead = SDL_TRUE;
			gContext->player.facing.val = SDLX_DIR_NONE;
			gContext->player.facing_i.val = SDLX_DIR_NONE;
			fetch_PacManSpriteInfo(&(gContext->player.sprite.sprite_data), SD_PACMAN_DEATH);
			gContext->player.sprite.current = 0;
		}
	}
	else if (ghost->mode == GM_EATEN)
	{
		ghost->tar_x = 11;
		ghost->tar_y = 11;
		move_ghost(ghost, gContext->map);
		if (ghost->x == 11 && ghost->y == 11)
		{
			fetch_GhostSpriteInfo(&(ghost->sprite.sprite_data), ghost->ghost);
			ghost->mode = GM_CHASE;
		}
	}

	ghost->x += (GAME_COLS - 1);
	ghost->x %= (GAME_COLS - 1);

	realign_ghost(ghost);
	ghost->sprite.current++;
	SDLX_RenderQueue_add(&(gContext->rQueue), &(ghost->sprite));
}
