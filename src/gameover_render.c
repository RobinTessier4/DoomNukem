#include "proto_global.h"

int	render_gameover(t_data *d)
{
	//RESET INFO CAR LA JE SUIS MORTE ET AU MEME ENDROIT DE MA MORT
	SDL_PumpEvents();
	handle_key_event(d);
	handle_poll_event(d);
	put_gameover_bg(d);
	render_gameover_button(d);
	catch_over_btn_event(d);
	SDL_RenderPresent(d->rend);
	return (0);
}