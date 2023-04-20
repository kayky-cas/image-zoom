#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "lib_ppm.h"

void draw_pixels(struct image_s *zoom, uint8_t color, int color_pos, int width, int pix_pos) {
    if (color >= 75 && color <= 134) {
        if (color_pos == 0) {
            zoom->pix[3 * width + (3 * pix_pos) + color_pos].r = color;
        } else if (color_pos == 1) {
            zoom->pix[3 * width + (3 * pix_pos) + color_pos].g = color;
        } else {
            zoom->pix[3 * width + (3 * pix_pos) + color_pos].b = color;
        }
    } else if (color >= 135 && color <= 179) {
        if (color_pos == 0) {
            zoom->pix[0 * 3 * width + (3 * pix_pos) + color_pos].r = color;
            zoom->pix[2 * 3 * width + (3 * pix_pos) + color_pos].r = color;
        } else if (color_pos == 1) {
            zoom->pix[0 * 3 * width + (3 * pix_pos) + color_pos].g = color;
            zoom->pix[2 * 3 * width + (3 * pix_pos) + color_pos].g = color;
        } else {
            zoom->pix[0 * 3 * width + (3 * pix_pos) + color_pos].b = color;
            zoom->pix[2 * 3 * width + (3 * pix_pos) + color_pos].b = color;
        }
    } else if (color >= 180) {
        if (color_pos == 0) {
            zoom->pix[0 * 3 * width + (3 * pix_pos) + color_pos].r = color;
            zoom->pix[1 * 3 * width + (3 * pix_pos) + color_pos].r = color;
            zoom->pix[2 * 3 * width + (3 * pix_pos) + color_pos].r = color;
        } else if (color_pos == 1) {
            zoom->pix[0 * 3 * width + (3 * pix_pos) + color_pos].g = color;
            zoom->pix[1 * 3 * width + (3 * pix_pos) + color_pos].g = color;
            zoom->pix[2 * 3 * width + (3 * pix_pos) + color_pos].g = color;
        } else {
            zoom->pix[0 * 3 * width + (3 * pix_pos) + color_pos].b = color;
            zoom->pix[1 * 3 * width + (3 * pix_pos) + color_pos].b = color;
            zoom->pix[2 * 3 * width + (3 * pix_pos) + color_pos].b = color;
        }
    }
}

void pucrs(struct image_s *image, struct image_s *zoom, int width, int pix_pos) {
    uint8_t r = image->pix[pix_pos].r;
    draw_pixels(zoom, r, 0, width, pix_pos);
    uint8_t g = image->pix[pix_pos].g;
    draw_pixels(zoom, g, 1, width, pix_pos);
    uint8_t b = image->pix[pix_pos].b;
    draw_pixels(zoom, b, 2, width, pix_pos);
}

int main(int argc, char** argv) {
    assert(argc > 1);

    char* image_name = argv[1];

    struct image_s data;
    struct image_s *image = &data;

    int r = read_ppm(image_name, image);

    if (r != 0) {
        fprintf(stderr, "Não foi possível ler a imagem %s!\n", image_name);
        exit(1);
    }

    free_ppm(image);

    struct image_s data_zoom;
    struct image_s *zoom = &data_zoom;

    r = new_ppm(zoom, image->width * 3, image->height * 3);

    for (int i = 0; i < image->width * image->height; i++) {
        pucrs(image, zoom, image->width, i);
    }

    write_ppm("pucrs.ppm", zoom);

    free_ppm(zoom);

    return 0;
}
