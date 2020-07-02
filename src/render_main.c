#include "proto_global.h"
#include <errno.h>

int					main(int ac, char **av)
{
    t_data			d;
    
    init_data(&d, ac, av);
    // ft_putstr("Main worked\n");
	// printf("map: %s\n", av[1]);
	// printf("d.run_game: %d\n", d.run_game);
	d.run_game = MENU;
    init_sound(&d);
    play_sound(&d, MUS1);
	while (d.run_game > 0)
	{
		if (d.run_game == GAME)
			render_game(&d, ac, av);
		else if (d.run_game == MENU)
			render_menu(&d, ac, av);
		else if (d.run_game == GAMEOVER)
			render_gameover(&d, ac, av);
		else if (d.run_game == EDITOR)
		{
			if (access("./editor", X_OK))
			{
				printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
				d.run_game = 0;
			}
			else
				execv("./editor", av);
		}
	}
	exit_env(&d);
}

