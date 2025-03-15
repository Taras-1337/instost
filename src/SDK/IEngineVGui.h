#pragma once

#include <stdint.h>
#include <wchar.h>

typedef uint64_t hfont;

enum fontflags
{
    FONTFLAG_NONE         = 0,
    FONTFLAG_ITALIC       = 0x1,
    FONTFLAG_UNDERLINE    = 0x2,
    FONTFLAG_STRIKEOUT    = 0x4,
    FONTFLAG_SYMBOL       = 0x8,
    FONTFLAG_ANTIALIAS    = 0x10,
    FONTFLAG_GAUSSIANBLUR = 0x20,
    FONTFLAG_ROTARY       = 0x40,
    FONTFLAG_DROPSHADOW   = 0x80,
    FONTFLAG_ADDITIVE     = 0x100,
    FONTFLAG_OUTLINE      = 0x200,
    FONTFLAG_CUSTOM       = 0x400,
    FONTFLAG_BITMAP       = 0x800,
};

enum paintmode
{
    PAINT_UIPANELS =     (1 << 0),
    PAINT_INGAMEPANELS = (1 << 1),
    PAINT_CURSOR =       (1 << 2)
};

extern hfont font;

void
draw_set_color(void *self, int r, int g, int b, int a);

void
draw_outlined_rect(void *self, int x0, int y0, int x1, int y1);

void
draw_filled_rect(void *self, int x0, int y0, int x1, int y1);

void
draw_line(void *self, int x0, int y0, int x1, int y1);

void
draw_set_text_font(void *self, hfont f);

void
draw_set_text_color(void *self, int r, int g, int b, int a);

void
draw_set_text_pos(void *self, int x, int y);

void
draw_print_text(void *self, const wchar_t *text, int len);

hfont
create_font(void *self);

void
set_font_glyphset(void       *self,
                  hfont       f,
                  const char *font_name,
                  int         tall,
                  int         weight,
                  int         blur,
                  int         scanlines,
                  int         flags);

void
setup_font(const char *font_name, int size, int flags);
