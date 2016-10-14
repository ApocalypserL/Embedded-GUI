#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include "draw.h"

int main(int argc, char *argv[])
{
	struct fb_var_screeninfo vinfo;
	int screensize = 0;
	int color = 0;
	int offset = 0;
	unsigned char *fbp = NULL;
	fb_open(vinfo);
	dot(100,100);
}

void fb_open(struct fb_var_screeninfo vinfo)	//get variable info of frame buffer & send addr to mem
{
	fd = open("/dev/fb", O_RDWR);
	if (fd < 0)
	{
		printf("cannot open Frame Buffer\n");
		exit(1);
	}
	
	ioctl(fd, FBIOGET_VSCREENINFO, vinfo);
	ioctl(fd, FBIOGET_FSCREENINFO, finfo);
	printf("bits_per_pixel=%d\n", vinfo.bits_per_pixel);
	printf("x_res=%d\n", vinfo.xres);
	printf("y_res=%d\n", vinfo.yres);
	printf("screen memory length=%d\n", finfo.smem_len);
	
	
	screensize = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel/8;
	fbp = (unsigned char *)mmap(0,screensize,\PROT_READ | PROT_WRITE, MAP_SHARE, fd, 0);
	memset((*fbp),0,screensize);	//clear screen
}
                    
void dot(int x, int y)	//draw a dot on screen location (x, y)
{
	offset = (y * vinfo.xres + x) * vinfo.bits_per_pixel/8;	//offset bytes
	color = (red << 16) | (green << 8) | (blue);	//color
	*(unsigned char *)(fbp + offset) = color;
}

void draw_h_line(int x1, int x2, int y)	//draw a horizontal line
{
	for (int i = x1, i <= x2, ++i)
	{
		dot(i, y);
	}
}

void draw_v_line(int x, int y1, int y2)	//draw a vertical line
{
	for (int i = y1, i <= y2, ++i)
		dot(x, i);
}

void 
