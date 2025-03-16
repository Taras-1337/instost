#include "IEngineVGui.h"

#include "common.h"
#include "../interfaces.h"
#include <stdio.h>

hfont font;

void
draw_set_color(void *self, int r, int g, int b, int a)
{
    typedef void (*vfn)(void *, int, int, int, int);
    vfn vfunc = (vfn) getvfunc(self, 14, 0);
    vfunc(self, r, g, b, a);
}

void
draw_outlined_rect(void *self, int x0, int y0, int x1, int y1)
{
    typedef void (*vfn)(void *, int, int, int, int);
    vfn vfunc = (vfn) getvfunc(self, 18, 0);
    vfunc(self, x0, y0, x1, y1);
}

void
draw_filled_rect(void *self, int x0, int y0, int x1, int y1)
{
    typedef void (*vfn)(void *, int, int, int, int);
    vfn vfunc = (vfn) getvfunc(self, 16, 0);
    vfunc(self, x0, y0, x1, y1);
}

void
draw_line(void *self, int x0, int y0, int x1, int y1)
{
    typedef void (*vfn)(void *, int, int, int, int);
    vfn vfunc = (vfn) getvfunc(self, 19, 0);
    vfunc(self, x0, y0, x1, y1);
}

void
draw_set_text_font(void *self, hfont f)
{
    typedef void (*vfn)(void *, hfont);
    vfn vfunc = (vfn) getvfunc(self, 23, 0);
    vfunc(self, f);
}

void
draw_set_text_color(void *self, int r, int g, int b, int a)
{
    typedef void (*vfn)(void *, int, int, int, int);
    vfn vfunc = (vfn) getvfunc(self, 24, 0);
    vfunc(self, r, g, b, a);
}

void
draw_set_text_pos(void *self, int x, int y)
{
    typedef void (*vfn)(void *, int, int);
    vfn vfunc = (vfn) getvfunc(self, 26, 0);
    vfunc(self, x, y);
}

void
draw_print_text(void *self, const wchar_t *text, int len)
{
    typedef void (*vfn)(void *, const wchar_t *, int);
    vfn vfunc = (vfn) getvfunc(self, 28, 0);
    vfunc(self, text, len);
}

hfont
create_font(void *self)
{
    typedef int (*vfn)(void *);
    /*
      80 - always 0
      78 - always 0
      76 - always 0
      75 - always 15
      74 - always 127
      71 - 449++
      69 - always 0
      68 - the same random num
      67 - the same random num
      66 - the same random num (same as 67)
      64 - the same random num
    */
    vfn vfunc = (vfn) getvfunc(self, 71, 0);
    return vfunc(self);
}

void
set_font_glyphset(void       *self,
                  hfont       f,
                  const char *font_name,
                  int         tall,
                  int         weight,
                  int         blur,
                  int         scanlines,
                  int         flags)
{
    typedef void (*vfn)(void *, hfont, const char *, int, int, int, int, int, int, int);
    vfn vfunc = (vfn) getvfunc(self, 73, 0); // 71 initial > 72 moved (crashes) / 74 calls every second, etc...
    vfunc(self, f, font_name, tall, weight, blur, scanlines, flags, 0, 0);
}

void
setup_font(const char *font_name, int size, int flags)
{
    font = create_font(surface);
    // set_font_glyphset(surface, font, font_name, size, 450, 0, 0, flags);
    se_msg("Font ID: %lld\n", font);
    printf("Font ID: %lld\n", font);
    fflush(stdout);
}
