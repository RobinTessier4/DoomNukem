/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 23:12:15 by robin             #+#    #+#             */
/*   Updated: 2020/07/05 23:12:15 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include "render.h"

# define GAMEOVER_PATH "asset/img/menu/jail_gameover.bmp"
# define MENU_BG_PATH "asset/img/menu/jail_bg1.bmp"

typedef struct		s_menu
{
	char			**argv_tab;
	char			**argv_over_tab;
	SDL_Texture		*menu_bg_t;
	SDL_Texture		*gameover_t;
	SDL_Texture		*btn;
	SDL_Texture		*play_t;
	SDL_Texture		*editor_t;
	SDL_Texture		*quit_t;
	SDL_Texture		*over_continue_t;
	SDL_Texture		*over_quit_t;
}					t_menu;

#endif