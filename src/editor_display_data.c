#include "proto_global.h"

// OKK

static void		process_input(t_env *env)
{
  char *wcount;
  char *rcount;
  char *wid;

  wcount = ft_itoa(env->wall_count);
  rcount = ft_itoa(env->room_count);
  wid = ft_itoa(env->selected_wall_id);
	input_text_to_img(wcount, 2, 0xFFFFFFFF, create_img(env->p_screen, set_sdl_rect(0.530 * WIN_SIZE_X, 0.800 * WIN_SIZE_Y, WIN_SIZE_X, WIN_SIZE_Y)));
  input_text_to_img(rcount, 2, 0xFFFFFFFF, create_img(env->p_screen, set_sdl_rect(0.530 * WIN_SIZE_X, 0.700 * WIN_SIZE_Y, WIN_SIZE_X, WIN_SIZE_Y)));
  input_text_to_img(wid, 2, 0xFFFFFFFF, create_img(env->p_screen, set_sdl_rect(0.700 * WIN_SIZE_X, 0.700 * WIN_SIZE_Y, WIN_SIZE_X, WIN_SIZE_Y)));
  free(wcount);
  free(rcount);
  free(wid);
}

void			print_env2screen(t_env *env)
{
    SDL_Rect	tmp;

    print_inputs(env);
	process_input(env);
	if ((SDL_UpdateTexture(env->screen, NULL, env->p_screen, WIN_SIZE_X * 4)) == -1)
		exit_editor(env, "error : failed to update texture");
    if ((SDL_UpdateTexture(env->editor_grid, NULL, env->p_grid, GRID_SIZE_X * 4)) == -1)
    	exit_editor(env, "error : failed to update texture");
    display_txt_img(env);
    display_buttons(env);
	if ((SDL_RenderCopy(env->rend, env->screen, NULL, NULL)) < 0)
		exit_editor(env, "error : failed to render copy");
    print_icon_list(env);
    print_player_spawn(env);
    print_mouse_icon(env);
    if ((SDL_RenderCopy(env->rend, env->editor_grid, NULL, &env->grid_pos)) < 0)
		exit_editor(env, "error : failed to render copy");
    tmp = set_sdl_rect(TEXT_POS_X, TEXT_POS_Y, TEXT_SIZE_X, TEXT_SIZE_Y);
	if ((SDL_RenderCopy(env->rend, env->text_list[env->selected_texture], NULL, &tmp)) < 0)
		exit_editor(env, "error : failed to render copy");
	update_sprite_texture(env);
    tmp = set_sdl_rect(ICON_MOB_POS_X, ICON_MOB_POS_Y, ICON_MOB_SIZE_X, ICON_MOB_SIZE_Y);
    if ((SDL_RenderCopy(env->rend, env->img_list[env->selected_mob], NULL, &tmp)) < 0)
		exit_editor(env, "error : failed to render copy");
	SDL_RenderPresent(env->rend);
}