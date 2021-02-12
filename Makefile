NAME = pacman

MEM_CHECK = -fsanitize=address
FLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes/ -I includes/includes_SDL2/

LIB_DIR = libs/
LIBRARIES = $(LIB_DIR)libSDL2.dylib $(LIB_DIR)libSDL2_ttf.dylib $(LIB_DIR)libSDL2_image.dylib

SDLX_DIR = SDLX/
SRCS_DIR = srcs/

BIN_DIR = bin/

SRCS_NAMES =		\
	$(addprefix $(SDLX_DIR), $(SDLX_NAMES))		\
	background		\
	extra_texture	\
	ghost_sprite	\
	ghost			\
	main 			\
	input			\
	map				\
	player			\
	update			\

SDLX_NAMES = 			\
	SDLX_background		\
	SDLX_init			\
	SDLX_input			\
	SDLX_ticks			\
	SDLX_render_queue	\
	SDLX_render			\
	SDLX_utils			\
	SDLX_xbox			\

C_FILES =				\
	$(SRCS_NAMES) 		\

SRCS = $(addsuffix .c, $(addprefix $(SRCS_DIR), $(C_FILES)))
OBJS = $(addprefix $(BIN_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(BIN_DIR) $(OBJS)
	gcc $(FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBRARIES)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)%.o: %.c
	mkdir -p $(BIN_DIR)$(dir $<)
	gcc $(FLAGS) $(INCLUDES) -c $< -o $@

run: all
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
