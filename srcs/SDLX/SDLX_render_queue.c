/***************************************************************************
 * FILENAME:    SDLX_render_queue.c
 * DESCRIPTION: General Functions to render.
 *
 * ENVIRONMENT:
 *     macOS High Sierra 10.13.6
 *     Visual Studio Code 1.52.1
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 24Jan2021
***************************************************************************/

#include "SDLX_structs.h"

#define QUEUE_DEFAULT_SIZE (5)

int	SDLX_RenderQueue_init(SDLX_RenderQueue *dest)
{
	dest->index = 0;
	dest->capacity = QUEUE_DEFAULT_SIZE;
	dest->content = SDL_calloc(QUEUE_DEFAULT_SIZE, sizeof(*dest->content));

	return (EXIT_SUCCESS);
}

void	SDLX_draw_animation(SDL_Renderer *renderer, SDLX_Sprite *animation)
{
	size_t	no;

	// SDL_Log("ERROR %zu", animation->sprite_data->cycle);
	no = animation->current % animation->sprite_data->cycle;

	SDL_RenderCopyEx(renderer,
	animation->sprite_data[no].texture,
	animation->sprite_data[no].src,

	animation->dst,
	animation->angle,
	animation->center,
	animation->flip);
}

void	SDLX_RenderQueue_flush(SDLX_RenderQueue *queue, SDL_Renderer *renderer)
{
	size_t	i;

	i = 0;
	while (i < queue->index)
	{
		SDLX_draw_animation(renderer, queue->content[i]);
		i++;
	}
	queue->index = 0;
}

void	SDLX_RenderQueue_add(SDLX_RenderQueue *dst, SDLX_Sprite *src)
{
	if (dst->index + 1 >= dst->capacity)
	{
		dst->content = SDL_realloc(dst->content, sizeof(dst->content) * (dst->capacity * ALLOC_RATE));
		dst->capacity = dst->capacity * ALLOC_RATE;
	}

	dst->content[dst->index] = src;
	dst->index += 1;
}
