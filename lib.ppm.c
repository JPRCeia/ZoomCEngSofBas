/* file:          lib_ppm.c
 * description:   PPM library
 * date:          03/2023
 * author:        Sergio Johann Filho <sergio.johann@acad.pucrs.br>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib.ppm.h"


int read_ppm(char *file, struct image_s *image)
{
	FILE *fptr;
	char *t;
	char buf[128];
	int r, d, i, j;
	struct pixel_s *img_data;
	
	fptr = fopen(file, "rb");
	if (!fptr)
		return -1;
		
	t = fgets(buf, sizeof(buf), fptr);
	if (!t)
		goto failread;
	
	if (strncmp(buf, "P6\n", 3) != 0)
		goto failread;

        do {
		t = fgets(buf, sizeof(buf), fptr);
		if (!t)
			goto failread;
				
	} while (strncmp(buf, "#", 1) == 0);
	
        r = sscanf(buf, "%u %u", &image->width, &image->height);
        if (r < 2)
		goto failread;

        r = fscanf(fptr, "%u", &d);
        if ((r < 1) || (d != 255))
		goto failread;
		
        fseek(fptr, 1, SEEK_CUR);
        
        img_data = malloc(image->width * image->height * sizeof(struct pixel_s));
        if (!img_data)
		goto failread;
        
        image->pix = img_data;
        
		fread(image->pix, 3, image->height * image->width, fptr);

	
	fclose(fptr);

	return 0;
	
failread:
	fclose(fptr);
	
	return -1;
}


int write_ppm(char *file, struct image_s *image)
{
	FILE *fptr;
	int i, j;
	
	fptr = fopen(file, "wb");
	if (!fptr)
		return -1;
		
	fprintf(fptr, "P6\n%d %d\n255\n", image->width, image->height);
    
	fwrite(image->pix, 3, image->height * image->width, fptr);

	fclose(fptr);
	
	return 0;
}


int new_ppm(struct image_s *image, int width, int height)
{
	struct pixel_s *img_data;

	image->width = width;
	image->height = height;
	
        img_data = malloc(image->width * image->height * sizeof(struct pixel_s));
        if (!img_data)
		return -1;
        
        image->pix = img_data;
        memset(image->pix, 0, image->width * image->height * sizeof(struct pixel_s));
	
	return 0;
}


int free_ppm(struct image_s *image)
{
	if (image->pix) {
		free(image->pix);
		
		return 0;
	}
	
	return -1;
}
