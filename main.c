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

    image->pix[0].r = 255;
    image->pix[0].g = 255;
    image->pix[0].b = 255;

    write_ppm("nossa_imagem.ppm", image);

    free_ppm(image);

    return 0;
}
