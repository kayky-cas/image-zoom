#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "lib_ppm.h"

void draw_pix(struct image_s *zoom, int color, uint8_t brightness, size_t i, size_t j, int line) {
    assert(line >= 0 && line < 3);
    *((&zoom->pix[(j + line) * zoom->width + i + color].r) + color) = brightness;
}

void draw_pix_line(struct image_s *zoom, int color, uint8_t brightness, size_t i, size_t j) {
    assert(color >= 0 && color < 3);

    if (brightness > 74 && brightness < 135) {
        draw_pix(zoom, color, brightness, i, j, 1);
    } else if (brightness > 134 && brightness < 180) {
        draw_pix(zoom, color, brightness, i, j, 0);
        draw_pix(zoom, color, brightness, i, j, 2);
    } else if (brightness > 179) {
        draw_pix(zoom, color, brightness, i, j, 0);
        draw_pix(zoom, color, brightness, i, j, 1);
        draw_pix(zoom, color, brightness, i, j, 2);
    }
}

struct image_s *zoom_image_3x(struct image_s *image) {
    struct image_s *zoom = malloc(sizeof(struct image_s));

    int r = new_ppm(zoom, image->width * 3, image->height * 3);

    if (r != 0) {
        fprintf(stderr, "Não foi possível criar a imagem!\n");
        exit(1);
    }

    for (size_t j = 0; j < image->height; j++) {
        for (size_t i = 0; i < image->width; i++) {
            draw_pix_line(zoom, 0, image->pix[j * image->width + i].r, i * 3, j * 3);
            draw_pix_line(zoom, 1, image->pix[j * image->width + i].g, i * 3, j * 3);
            draw_pix_line(zoom, 2, image->pix[j * image->width + i].b, i * 3, j * 3);
        }
    }

    return zoom;
}

int main(int argc, char** argv) {
    assert(argc > 2);

    char* image_name = argv[1];

    struct image_s data;
    struct image_s *image = &data;

    int r = read_ppm(image_name, image);

    if (r != 0) {
        fprintf(stderr, "Não foi possível ler a imagem %s!\n", image_name);
        exit(1);
    }

    struct image_s *zoom = zoom_image_3x(image);

    char* zoom_name = argv[2];

    write_ppm(zoom_name, zoom);

    free_ppm(zoom);
    free_ppm(image);

    return 0;
}
