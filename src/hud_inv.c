#include <hud.h>

int					init_health_pack(t_data *d, t_hud *hud)
{
	if (!(hud->inv.healthpack_icon_s = SDL_LoadBMP(HEALTHPACK_PATH)))
	{
		printf("Erreur de chargement de l'image : %s", SDL_GetError());
		return (error(hud));
	}
	if (!(hud->inv.healthpack_icon_t = SDL_CreateTextureFromSurface(d->rend, hud->inv.healthpack_icon_s)))
	{
		printf("Erreur de conversion de la surface : %s", SDL_GetError());
		return (error(hud));
	}
	SDL_FreeSurface(hud->inv.healthpack_icon_s);
	return (0);
}

int					put_healthpack_icon(t_data *d, t_hud *hud, SDL_Rect pos)
{
	if (SDL_RenderCopy(d->rend, hud->inv.healthpack_icon_t, NULL, &pos))
	{
		printf("Erreur Render Copy : %s", SDL_GetError());
		return (error(hud));
	}
	return (0);
}

int					set_healthpack_info(t_data *d, t_hud *hud, int nb)
{
	SDL_Texture		*t_cpy;
	SDL_Surface		*s_cpy;	
	char			*text;

	if (!(text = ft_itoa(nb)))
		return (error(hud));
	if(!(s_cpy = TTF_RenderText_Blended(hud->font_nb, text, hud->color)))
	{
		printf("Erreur d'affichage du texte TTF : %s\n", TTF_GetError());
		return (error(hud));
	}
	if (!(hud->inv.healthpack_info_s = copy_surface(d, s_cpy, hud)))
		return (error(hud));
	SDL_FreeSurface(s_cpy);
	return (0);
}

int				render_healthpack_info(t_data *d, t_hud *hud, SDL_Rect pos)
{
	if (!(hud->inv.healthpack_info_t = SDL_CreateTextureFromSurface(d->rend, hud->inv.healthpack_info_s)))
		printf("Erreur de conversion de la surface : %s", SDL_GetError());
	if (SDL_RenderCopy(d->rend, hud->inv.healthpack_info_t, NULL, &pos))
	{
		printf("Erreur Render Copy : %s", SDL_GetError());
		return (error(hud));
	}
	return (0);
}