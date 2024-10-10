#include <stdio.h>
#include "lib.ppm.h"

void paintRedPixels(struct image_s *image_copy, int original_x, int original_y, int color_value);
void paintGreenPixels(struct image_s *image_copy, int original_x, int original_y, int color_value);
void paintBluePixels(struct image_s *image_copy, int original_x, int original_y, int color_value);

void processPixels(struct image_s *image_original, struct image_s *image_copy);
int createImageCopy(struct image_s *image_original, struct image_s *image_copy);
void cleanup(struct image_s *image_original, struct image_s *image_copy);

int main()
{
    struct image_s data_original;
    struct image_s *image_original = &data_original;

    struct image_s data_copy;
    struct image_s *image_copy = &data_copy;

    int r_original = read_ppm("lena.ppm", image_original);

    if (r_original != 0) {
        fprintf(stderr, "Erro\n");
        return 1;
    }

    int r_copy = createImageCopy(image_original, image_copy);
    if (r_copy != 0) {
        fprintf(stderr, "Erro\n");
        free_ppm(image_original);
        return 1;
    }

    processPixels(image_original, image_copy);

    if (write_ppm("lena.copy.ppm", image_copy) != 0) {
        fprintf(stderr, "Erro \n");
    }

    cleanup(image_original, image_copy);

    return 0;
}

void processPixels(struct image_s *image_original, struct image_s *image_copy) {
    for (int i = 0; i < image_original->height; i++) {
        for (int j = 0; j < image_original->width; j++) {
            struct pixel_s original_pixel = image_original->pix[j + i * image_original->width];
            paintRedPixels(image_copy, j, i, original_pixel.r);
            paintGreenPixels(image_copy, j, i, original_pixel.g);
            paintBluePixels(image_copy, j, i, original_pixel.b);
        }
    }
}

int createImageCopy(struct image_s *image_original, struct image_s *image_copy) {
    return new_ppm(image_copy, image_original->width * 3, image_original->height * 3);
}

void cleanup(struct image_s *image_original, struct image_s *image_copy) {
    free_ppm(image_original);
    free_ppm(image_copy);
}


void paintRedPixels(struct image_s *image_copy, int original_x, int original_y, int color_value)
{
	int pixelPosition = original_x * 3 + original_y * image_copy->width * 3; 

	struct pixel_s *pixelTop = &image_copy->pix[pixelPosition]; 
	struct pixel_s *pixelMid = pixelTop + image_copy->width; 
	struct pixel_s *pixelBot = pixelMid + image_copy->width; 

	if (color_value >= 180) { 
		pixelTop->r = 255;
		pixelMid->r = 255;
		pixelBot->r = 255;
	} else if (color_value >= 135) { 
		pixelTop->r = 255;
		pixelBot->r = 255;
	} else if (color_value >= 75) { 
		pixelMid->r = 255;
	}

}

void paintGreenPixels(struct image_s *image_copy, int original_x, int original_y, int color_value)
{
	int pixelPosition = (original_x * 3 + 1) + original_y * image_copy->width * 3; 

	struct pixel_s *pixelTop = &image_copy->pix[pixelPosition]; 
	struct pixel_s *pixelMid = pixelTop + image_copy->width; 
	struct pixel_s *pixelBot = pixelMid + image_copy->width; 

	if (color_value >= 180) { 
		pixelTop->g = 255;
		pixelMid->g = 255;
		pixelBot->g = 255;
	} else if (color_value >= 135) {
		pixelTop->g = 255;
		pixelBot->g = 255;
	} else if (color_value >= 75) {
		pixelMid->g = 255;
	}
}

void paintBluePixels(struct image_s *image_copy, int original_x, int original_y, int color_value)
{
	int pixelPosition = (original_x * 3 + 2) + original_y * image_copy->width * 3; 

	struct pixel_s *pixelTop = &image_copy->pix[pixelPosition];
	struct pixel_s *pixelMid = pixelTop + image_copy->width; 
	struct pixel_s *pixelBot = pixelMid + image_copy->width; 

	if (color_value >= 180) { 
		pixelTop->b = 255;
		pixelMid->b = 255;
		pixelBot->b = 255;
	} else if (color_value >= 135) { 
		pixelTop->b = 255;
		pixelBot->b = 255;
	} else if (color_value >= 75) { 
		pixelMid->b = 255;
	}
}
