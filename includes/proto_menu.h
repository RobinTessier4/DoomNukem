#ifndef PROTO_MENU_H
# define PROTO_MENU_H

# include "data.h"

/* menu_background.c */

int				init_background(t_data *d);
int				put_menu_bg(t_data *d);

/* menu_button.c */

int				render_bg_btn(t_data *d, SDL_Rect pos);
int				render_text_btn(t_data *d, SDL_Rect pos, SDL_Texture *texture, char *text);
int				render_btn(t_data *d);

/* menu_clean.c */

int				free_menu(t_data *d);
int				exit_menu(t_data *d);

/* menu_exec */

int				catch_btn_event(t_data *d, int ac, char **av);

#endif