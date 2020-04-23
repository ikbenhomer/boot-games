#ifndef GRAPHICS_H
#define GRAPHICS_H

#define RED    0x04
#define BROWN  0x06
#define YELLOW 0x0E
#define GREEN  0x02
#define CYAN   0x03
#define BLUE   0x01
#define PURPLE 0x05
#define GRAY   0x08
#define WHITE  0x0F
#define BLACK  0x00

typedef unsigned char u8;

void set_video_mode(u8 mode);
void clear_screen();
void set_cursor_pos(u8 x, u8 y);
void set_bg_color(u8 color);
void write_char(u8 character, u8 color);
void write_str(char* str, u8 color);
void draw_line_x(u8 x_pos, u8 y_pos, u8 end_x, u8 sym, u8 color);
void draw_line_y(u8 x_pos, u8 y_pos, u8 end_y, u8 sym, u8 color);
void draw_box(u8 x_pos, u8 y_pos, u8 w, u8 h, u8 color, int border);
void test_render(u8 x_pos, u8 y_pos, u8 w, u8 h);

#endif
