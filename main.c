#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "lib_ppm.h"

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

    struct image_s data_zoom;
    struct image_s *zoom = &data_zoom;

    r = new_ppm(zoom, image->width * 3, image->height * 3);

    write_ppm("pucrs.ppm", zoom);

    free_ppm(zoom);
    free_ppm(image);

    return 0;
}
