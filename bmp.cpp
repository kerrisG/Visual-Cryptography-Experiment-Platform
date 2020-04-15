#include "stdafx.h"

#pragma pack(2)        //两字节对齐，否则bmp_fileheader会占16Byte
struct bmp_fileheader
{
	unsigned short    bfType;        //若不对齐，这个会占4Byte
	unsigned long    bfSize;
	unsigned short    bfReverved1;
	unsigned short    bfReverved2;
	unsigned long    bfOffBits;
};

struct bmp_infoheader
{
	unsigned long    biSize;
	unsigned long    biWidth;
	unsigned long    biHeight;
	unsigned short    biPlanes;
	unsigned short    biBitCount;
	unsigned long    biCompression;
	unsigned long    biSizeImage;
	unsigned long    biXPelsPerMeter;
	unsigned long    biYpelsPerMeter;
	unsigned long    biClrUsed;
	unsigned long    biClrImportant;
};

unsigned char *load_bmp(const char *filename, int *out_width, int *out_height, int *out_depth)
{
	struct bmp_fileheader bfh;
	struct bmp_infoheader bih;
	unsigned char *buffer = NULL;

	unsigned long width = 0;
	unsigned long height = 0;
	unsigned short depth = 0;
	unsigned long i = 0, j = 0;

	FILE *input_file = fopen(filename, "rb");
	if (!input_file)
		return NULL;

	fread(&bfh, sizeof(struct bmp_fileheader), 1, input_file);
	fread(&bih, sizeof(struct bmp_infoheader), 1, input_file);

	width = bih.biWidth;
	height = bih.biHeight;
	depth = bih.biBitCount;

	fseek(input_file, bfh.bfOffBits, SEEK_SET);
	buffer = (unsigned char*)malloc(bih.biWidth*bih.biHeight*bih.biBitCount / 8);
	fread(buffer, sizeof(unsigned char)*bih.biWidth*bih.biHeight*bih.biBitCount / 8, 1, input_file);

	fclose(input_file);

	*out_width = width;
	*out_height = height;
	*out_depth = depth;

	return buffer;
}

void save_bmp(const char *filename, unsigned char *buffer, int width, int height, int depth)
{
	struct bmp_fileheader bfh;
	struct bmp_infoheader bih;

	unsigned long headersize;
	unsigned long filesize;

	FILE *output_file = fopen(filename, "wb");
	if (depth == 8)
	{
		headersize = 14 + 40 + 256 * 4;
		filesize = headersize + width * height;
	}
	else if (depth == 24)
	{
		headersize = 14 + 40;
		filesize = headersize + width*height*depth / 8;
	}

	memset(&bfh, 0, sizeof(struct bmp_fileheader));
	memset(&bih, 0, sizeof(struct bmp_infoheader));

	//写入比较关键的几个bmp头参数
	bfh.bfType = 0x4D42;
	bfh.bfSize = filesize;
	bfh.bfOffBits = headersize;

	bih.biSize = 40;
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = (unsigned short)depth;
	bih.biSizeImage = width*height*depth / 8;

	fwrite(&bfh, sizeof(struct bmp_fileheader), 1, output_file);
	fwrite(&bih, sizeof(struct bmp_infoheader), 1, output_file);

	if (depth == 8)        //灰度图像要添加调色板
	{
		unsigned char *platte;
		unsigned char j = 0;
		int i = 0;
		platte = (unsigned char*)malloc(256 * 4);

		for (i = 0; i<1024; i += 4)
		{
			platte[i] = j;
			platte[i + 1] = j;
			platte[i + 2] = j;
			platte[i + 3] = 0;
			j++;
		}
		fwrite(platte, sizeof(unsigned char) * 1024, 1, output_file);
		free(platte);
	}

	fwrite(buffer, sizeof(unsigned char)*height*width*depth / 8, 1, output_file);    //一次写一行    
	fclose(output_file);
}
