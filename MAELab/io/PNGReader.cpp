/*
 Fragments Automatic Matching Laboratory (FAMLab)
 Copyright (C) 2017  Pham Xuan Thanh (xuan-thanh.pham@etu.u-bordeaux.fr)
 Version: 1.1
 Created on: December, 2017

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
//#include <png.h>
#include <setjmp.h>
#include <stdint.h>

using namespace std;

#include "../imageModel/Point.h"
#include "../imageModel/Matrix.h"

#include "PNGReader.h"

//ptrRGBAMatrix decompressPNG(const char *filename, int &rows, int &cols)
//{
//    cout << "Begin decompress PNG image." << endl;

//    ptrRGBAMatrix rgbaMatrix;

//    png_byte color_type;
//    png_byte bit_depth;
//    png_bytep *row_pointers;

//    FILE *fp = fopen(filename, "rb");

//    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//    if(!png) abort();

//    png_infop info = png_create_info_struct(png);
//    if(!info) abort();

//    if(setjmp(png_jmpbuf(png))) abort();

//    png_init_io(png, fp);

//    png_read_info(png, info);

//    cols      = png_get_image_width(png, info);
//    rows     = png_get_image_height(png, info);
//    color_type = png_get_color_type(png, info);
//    bit_depth  = png_get_bit_depth(png, info);

//    rgbaMatrix = new Matrix<RGBA>(rows, cols);

//    if(bit_depth == 16)
//        png_set_strip_16(png);

//    if(color_type == PNG_COLOR_TYPE_PALETTE)
//        png_set_palette_to_rgb(png);

//    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
//    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
//        png_set_expand_gray_1_2_4_to_8(png);

//    if(png_get_valid(png, info, PNG_INFO_tRNS))
//        png_set_tRNS_to_alpha(png);

//    // These color_type don't have an alpha channel then fill it with 0xff.
//    if(color_type == PNG_COLOR_TYPE_RGB ||
//            color_type == PNG_COLOR_TYPE_GRAY ||
//            color_type == PNG_COLOR_TYPE_PALETTE)
//        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

//    if(color_type == PNG_COLOR_TYPE_GRAY ||
//            color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
//        png_set_gray_to_rgb(png);

//    png_read_update_info(png, info);

//    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * rows);
//    for(int y = 0; y < rows; y++) {
//        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
//    }

//    png_read_image(png, row_pointers);

//    // get each value of each channel
//    for(int y = 0; y < rows; y++) {
//        png_bytep row = row_pointers[y];
//        for(int x = 0; x < cols; x++) {
//            png_bytep px = &(row[x * 4]);
//            // print each value
//            printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);

//            RGBA rgba;
//            rgba.R = (unsigned long int) px[0];
//            rgba.G = (unsigned long int) px[1];
//            rgba.B = (unsigned long int) px[2];
//            rgba.A = (unsigned long int) px[3];
//            rgbaMatrix->setAtPosition(y, x, rgba);
//        }
//    }

//    fclose(fp);

//    // To avoid memory leaks
//    png_destroy_read_struct(&png, &info, NULL);
//    png=NULL;
//    info=NULL;

//    cout << "Finished de-compress PNG." << endl;
//    return rgbaMatrix;
//}
