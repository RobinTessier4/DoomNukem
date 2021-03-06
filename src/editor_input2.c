/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_input2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alebui <alebui@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 22:44:41 by ahippoly          #+#    #+#             */
/*   Updated: 2020/07/09 16:37:16 by alebui           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proto_global.h"

static int	handle_realeased_scancode(SDL_Scancode key_released)
{
	int added_num;

	added_num = -1;
	if (key_released == SDL_SCANCODE_0)
		added_num = 0;
	if (key_released == SDL_SCANCODE_1)
		added_num = 1;
	if (key_released == SDL_SCANCODE_2)
		added_num = 2;
	if (key_released == SDL_SCANCODE_3)
		added_num = 3;
	if (key_released == SDL_SCANCODE_4)
		added_num = 4;
	if (key_released == SDL_SCANCODE_5)
		added_num = 5;
	if (key_released == SDL_SCANCODE_6)
		added_num = 6;
	if (key_released == SDL_SCANCODE_7)
		added_num = 7;
	if (key_released == SDL_SCANCODE_8)
		added_num = 8;
	if (key_released == SDL_SCANCODE_9)
		added_num = 9;
	return (added_num);
}

void		handle_input_mode(t_env *env, SDL_Scancode key_released)
{
	t_input	*input;
	int		added_num;

	if (env->selected_input != -1 && env->selected_mouse_mode
			!= MOUSE_MODE_CREATE_ROOM)
	{
		added_num = handle_realeased_scancode(key_released);
		if (added_num != -1)
		{
			input = &env->input_lst[env->selected_input];
			input->value = ft_min(input->value * 10 + added_num, input->max);
			update_wall_param(env);
		}
	}
}

void		check_hovered_input(t_env *env)
{
	int i;

	i = 0;
	env->hovered_input_id = -1;
	while (i < NB_INPUT)
	{
		if (is_cursor_in_hitbox(env, env->input_lst[i].pos_size))
			env->hovered_input_id = i;
		i++;
	}
}

static void	process_input_color(t_env *env, char *str, t_input input,
	unsigned int color)
{
	if ((input_text_to_img(str, 2, color, create_img(env->p_screen,
			set_sdl_rect(input.pos_size.x, input.pos_size.y, WIN_SIZE_X,
			WIN_SIZE_Y)))) < 0)
		exit_editor(env, "error : failed to transform input text to image");
}

void		print_inputs(t_env *env)
{
	int		i;
	t_input	input;
	char	*str;

	i = 0;
	while (i < NB_INPUT)
	{
		input = env->input_lst[i];
		str = ft_itoa(input.value);
		if (env->selected_input == i)
			process_input_color(env, str, input, 0xFF88FF88);
		else if (env->hovered_input_id == i)
			process_input_color(env, str, input, 0xFF8888FF);
		else
			process_input_color(env, str, input, 0xFFDDDDDD);
		i++;
		free(str);
	}
}
