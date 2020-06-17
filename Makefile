SRC_NAME =	$(sort editor_main.c error_gesture.c image_gesture.c \
			bresenham.c tool_sdlpoint_arithmetic.c editor_wall_add_del.c \
			editor_wall_edit.c text_img.c editor_buttons.c bmp_reader.c \
			editor_map_move.c editor_sector_creation.c line_intersect.c \
			editor_mouse_event.c editor_map_output.c utils.c \
			editor_input.c editor_map_reader.c editor_debug_utils.c \
			editor_icon.c editor_init_data.c editor_init_data2.c image_gesture2.c \
			editor_display_data.c editor_grid.c editor_button_fct.c editor_button_fct2.c)

RENDER_SRC_NAME = $(sort render_main.c editor_map_reader.c editor_sector_creation.c \
						error_gesture.c image_gesture.c line_intersect.c \
						tool_sdlpoint_arithmetic.c utils.c render_minimap.c \
						bresenham.c render_init_data.c render_event_gesture.c \
						render_wall_processing.c render_draw_walls.c render_texture_loading.c \
						text_img.c render_movement.c image_gesture2.c render_raycast.c \
						render_world_edit.c render_collide_z.c render_wall_proj.c \
						render_draw_floor.c)

DLC_SRC_NAME = $(sort  editor_map_reader.c editor_sector_creation.c \
						error_gesture.c image_gesture.c line_intersect.c \
						tool_sdlpoint_arithmetic.c utils.c render_minimap.c \
						bresenham.c render_data_init.c render_event_gesture.c \
						render_wall_processing.c render_draw_walls.c render_texture_loading.c \
						hud_text.c hud_clean.c hud_weapon.c hud_init_weapons.c hud_perso.c \
						hud_health.c hud_ammo.c hud_inv.c hud_inv1.c hud_utils.c hud_main.c) ##

SRC_PATH = ./src/
OBJ_PATH = ./obj/
SDL_PATH = ./SDL2/
LIBFT_PATH = ./libft/
INC_PATH = ./includes/ $(LIBFT_PATH)includes/ ./includes/SDL2/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_REND_NAME = $(RENDER_SRC_NAME:.c=.o)
OBJ_DLC_NAME = $(DLC_SRC_NAME:.c=.o) ##

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
OBJ_REND = $(addprefix $(OBJ_PATH),$(OBJ_REND_NAME))
OBJ_DLC = $(addprefix $(OBJ_PATH),$(OBJ_DLC_NAME)) ##
INC = $(addprefix -I,$(INC_PATH))

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = editor
RENDER_NAME = doom-nukem
OPTI =  -g3
PTHREAD = -lpthread
DLC = hud ##

LIBFT = libft/libft.a

LDFLAGS = $(addprefix -L,$(LIBFT_PATH))

SDLM = `sdl2-config --cflags --libs`

LIBS = -lft -lm -lSDL2 -lSDL2_ttf

LDLIBS = -lft -lm

.PHONY: all clean fclean re libft

all: $(NAME) $(RENDER_NAME)

libft:
	@printf "/--------------- creating library \e[1;36m$@\e[0m... ----------/\n"
	@make -C $(LIBFT_PATH)
	@printf "/---------------- library $@ created... ----------/\n"

$(NAME): libft $(OBJ)
	@printf "%-50s" "create executable "$(notdir $@)...
	@$(CC) $(CFLAGS) $(OPTI) $(INC) $(OBJ) -o $(NAME) $(SDLM) $(LDFLAGS) $(LIBS)
	@printf "\e[1;32m[OK]\e[0m\n"

$(RENDER_NAME): libft $(OBJ_REND)
	@printf "%-50s" "create executable "$(notdir $@)...
	@$(CC) $(OPTI) $(CFLAGS) $(INC) $(OBJ_REND) -o $(RENDER_NAME) $(SDLM) $(LDFLAGS) $(LIBS) $(PTHREAD)
	@printf "\e[1;32m[OK]\e[0m\n"

$(DLC): libft $(OBJ_DLC) ##
	@printf "%-50s" "create executable "$(notdir $@)... 
	@$(CC) $(CFLAGS) $(INC) $(OBJ_DLC) -o $(DLC) -g $(SDLM) $(LDFLAGS) $(LIBS) 
	@printf "\e[1;32m[OK]\e[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@printf "%-50s" "compiling "$(notdir $<)...
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(OPTI) $(INC) -o $@ -c $<
	@printf "\e[1;32m[OK]\e[0m\n"

clean:
	@printf "%-50s" "deleting objects..." 
	@$(RM) $(OBJ) $(OBJ_REND)
	@$(RM) -r $(OBJ_PATH)
	@printf "\e[1;32m[OK]\e[0m\n"

fclean: clean
	@printf "%-50s" "deleting executable..." 
	@$(RM) $(NAME) $(RENDER_NAME) $(DLC)
	@printf "\e[1;32m[OK]\e[0m\n"

re: fclean all