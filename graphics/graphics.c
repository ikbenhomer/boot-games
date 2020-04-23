#include "graphics.h"

void set_video_mode(u8 mode)
{
    __asm__(
        "int $0x10" : : "a" ((0x00 << 8) | mode)                        
    );
}

void clear_screen()
{
    set_video_mode(0);
}

void set_cursor_pos(u8 x, u8 y)
{
    __asm__(
        "int $0x10" : : "a" (0x02 << 8),
                        "d" ((y << 8) | x)
    );
}

void set_bg_color(u8 color)
{
    __asm__(
        "int $0x10" : : "a" (0x0b << 8),
                        "b" (color)
    );
}

void write_char(u8 character, u8 color)
{
    __asm__(
        "int $0x10" : : "a" ((0x0e << 8) | character),
                        "b" (color)
    );
}

void write_str(char* str, u8 color)
{
    // walk through string until we reach null character
    while(*str != '\0')
    {
        write_char(*str, color);
        str++;
    }
}

void draw_line_x(u8 x_pos, u8 y_pos, u8 end_x, u8 sym, u8 color)
{
    // since all will be on the same line, only need to set_cursor_pos once
    set_cursor_pos(x_pos, y_pos);
    for(; x_pos < end_x; x_pos++)
    {
        write_char(sym, color);
    }
}

void draw_line_y(u8 x_pos, u8 y_pos, u8 end_y, u8 sym, u8 color)
{
    // need to set_cursor_pos because we're walking vertically downward
    for(; y_pos < end_y; y_pos++)
    {
        set_cursor_pos(x_pos, y_pos);
        write_char(sym, color);
    }
}

void draw_box(u8 x_pos, u8 y_pos, u8 w, u8 h, u8 color, int border)
{
    u8 end_x = x_pos+w-1;
    u8 end_y = y_pos+h-1;
    
    u8 y;
    for(y = y_pos; y <= end_y; y++)
    {
        // starting a new line in the box
        set_cursor_pos(x_pos, y);
        u8 x;
        for(x = x_pos; x <= end_x; x++)
        {
            if(border)
            {
                if(x == end_x && y == end_y) // bottom right
                {
                    write_char(188, color);
                }
                else if(x == x_pos && y == end_y) // bottom left
                {
                    write_char(200, color);
                }
                else if(x == end_x && y == y_pos) // top right
                {
                    write_char(187, color);
                }
                else if(x == x_pos && y == y_pos) // top left
                {
                    write_char(201, color);
                }
                else if(x == x_pos || x == end_x) // vertical lines
                {
                    write_char(186, color);
                }
                else if(y == y_pos || y == end_y) // horizontal lines
                {
                    write_char(205, color);
                }
                else // fill
                {
                    write_char(178, color);
                }
            }
            else // fill all if no border
            {
                write_char(178, color);
            }
        }
    }
}

void test_render(u8 x_pos, u8 y_pos, u8 w, u8 h)
{
    u8 end_x = x_pos+w;
    u8 end_y = y_pos+h;

    u8 y;
    u8 color = 0;
    for(y = y_pos; y < end_y; y++)
    {
        set_cursor_pos(x_pos, y);
        u8 x;
        for(x = x_pos; x < end_x; x++)
        {
            write_char(233, color);
            color = (color+1)%16;
        }
    }
}