#pragma once

unsigned char *load_bmp(const char *filename, int *out_width, int *out_height, int *out_depth);
void save_bmp(const char *filename, unsigned char *buffer, int width, int height, int depth);