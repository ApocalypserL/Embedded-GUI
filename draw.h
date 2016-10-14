#ifndef _DRAW_H
#define _DRAW_H

void fb_open(struct fb_var_screeninfo vinfo);
void dot(int x, int y);
void draw_h_line(int x1, int x2, int y);
void draw_v_line(int y1, int y2, int x);
#endif
