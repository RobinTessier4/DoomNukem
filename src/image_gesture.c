#include "global_header.h"
#include "img_file.h"

unsigned int *alloc_image(int width, int height)
{
    unsigned int *image;

    if (!(image = (unsigned int *)malloc(sizeof(unsigned int) * width * height)))
       exit_with_msg("Failed To malloc");
    ft_bzero(image, width * height * sizeof(unsigned int));
    return (image);
}

t_img create_img(unsigned int *pixels, SDL_Rect pos_size)
{
    t_img img;

    img.pixels = pixels;
    img.pos_size = pos_size;
    return (img);
}

void put_pixel(unsigned int *pixels, SDL_Point p_pos, t_size img_size, int color)
{
    pixels[p_pos.x + p_pos.y * img_size.w] = color;
}

void put_pixel_attempt(unsigned int *pixels, SDL_Point p_pos, t_size img_size, int color)
{
    int pixel_pos;

    pixel_pos = p_pos.x + p_pos.y * img_size.w;
    if (!pixels[pixel_pos])
        pixels[pixel_pos] = color;
}