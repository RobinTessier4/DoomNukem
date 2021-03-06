/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_display_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebui <alebui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:58:34 by ahippoly          #+#    #+#             */
/*   Updated: 2020/07/09 15:30:18 by alebui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto_global.h"

static void		process_input(t_env *env)
{
	char *wcount;
	char *rcount;
	char *wid;

	wcount = ft_itoa(env->wall_count);
	rcount = ft_itoa(env->room_count);
	wid = ft_itoa(env->selected_wall_id);
	if ((input_text_to_img(wcount, 2, 0xFFFFFFFF, create_img(env->p_screen,
		set_sdl_rect(0.530 * WIN_SIZE_X, 0.800 * WIN_SIZE_Y, WIN_SIZE_X,
		WIN_SIZE_Y)))) < 0)
		exit_editor(env, "error : failed to transform input text to image");
	if ((input_text_to_img(rcount, 2, 0xFFFFFFFF, create_img(env->p_screen,
		set_sdl_rect(0.530 * WIN_SIZE_X, 0.700 * WIN_SIZE_Y, WIN_SIZE_X,
		WIN_SIZE_Y)))) < 0)
		exit_editor(env, "error : failed to transform input text to image");
	if ((input_text_to_img(wid, 2, 0xFFFFFFFF, create_img(env->p_screen,
		set_sdl_rect(0.700 * WIN_SIZE_X, 0.700 * WIN_SIZE_Y, WIN_SIZE_X,
		WIN_SIZE_Y)))) < 0)
		exit_editor(env, "error : failed to transform input text to image");
	free(wcount);
	free(rcount);
	free(wid);
}

static void		before_print(t_env *env)
{
	print_inputs(env);
	process_input(env);
	SDL_UpdateTexture(env->screen, NULL, env->p_screen, WIN_SIZE_X * 4);
	SDL_UpdateTexture(env->editor_grid, NULL, env->p_grid, GRIDSIZEX * 4);
	display_txt_img(env);
	display_buttons(env);
	SDL_RenderCopy(env->rend, env->screen, NULL, NULL);
	print_icon_list(env);
	print_player_spawn(env);
	print_mouse_icon(env);
}

void			print_env2screen(t_env *env)
{
	SDL_Rect	tmp;

	before_print(env);
	if ((SDL_RenderCopy(env->rend, env->editor_grid, NULL, &env->grid_pos)) < 0)
		exit_editor(env, "error : failed to render copy");
	tmp = set_sdl_rect(TEXT_POS_X, TEXT_POS_Y, TEXT_SIZE_X, TEXT_SIZE_Y);
	if ((SDL_RenderCopy(env->rend, env->text_list[env->selected_texture],
		NULL, &tmp)) < 0)
		exit_editor(env, "error : failed to render copy");
	update_sprite_texture(env);
	tmp = set_sdl_rect(ICON_MOB_POS_X, ICON_MOB_POS_Y, ICON_MOB_SIZE_X,
		ICON_MOB_SIZE_Y);
	if ((SDL_RenderCopy(env->rend, env->img_list[env->selected_mob], NULL,
		&tmp)) < 0)
		exit_editor(env, "error : failed to render copy");
	SDL_RenderPresent(env->rend);
}
