#ifndef NETPBM_H
#define NETPBM_H

typedef struct{
  unsigned char chns;
  unsigned int rows;
  unsigned int cols;
  unsigned char max;
  unsigned char ***data;
  char filename[256];
}Image;

int load_img(Image *img);
int save_img(Image img);
int allocate_img(Image *img, unsigned int channels, unsigned int rows, unsigned int cols, unsigned char max);

#endif
