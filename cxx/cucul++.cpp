/*
 *  libcucul++    C++ bindings for libcucul
 *  Copyright (c) 2006 Jean-Yves Lamoureux <jylam@lnxscene.org>
 *                All Rights Reserved
 *
 *  $Id$
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the Do What The Fuck You Want To
 *  Public License, Version 2, as published by Sam Hocevar. See
 *  http://sam.zoy.org/wtfpl/COPYING for more details.
 */

/*
 *  This file contains the main functions used by \e libcucul++ applications
 *  to initialise a drawing context.
 */

#include "config.h"

#include <stdio.h> // BUFSIZ
#include <stdarg.h> // va_*

#include "cucul++.h"

Cucul::Cucul()
{
    cv = cucul_create_canvas(0, 0);
    if(!cv)
        throw -1;
}

Cucul::Cucul(int width, int height)
{
    cv = cucul_create_canvas(width, height);
    if(!cv) throw -1;
}

Cucul::Cucul(Buffer *b, char const *format)
{
    cv = cucul_import_canvas(b->get_buffer(), format);
    if(!cv) throw -1;
}

Cucul::~Cucul()
{
    if(cv)
        cucul_free_canvas(cv);
}

cucul_canvas_t *Cucul::get_cucul_canvas_t()
{
    return cv;
}

void Cucul::setSize(unsigned int width, unsigned int height)
{
    cucul_set_canvas_size(cv, width, height);
}

unsigned int Cucul::getWidth(void)
{
    return cucul_get_canvas_width(cv);
}

unsigned int Cucul::getHeight(void)
{
    return cucul_get_canvas_height(cv);
}

void Cucul::setColor(unsigned int f, unsigned int b)
{
    cucul_set_color(cv, f, b);
}

char const * Cucul::getColorName(unsigned int color)
{
    return cucul_get_color_name(color);
}

void Cucul::putChar(int x, int y, char ch)
{
    cucul_putchar(cv, x, y, ch);
}

void Cucul::putStr(int x, int y, char *str)
{
    cucul_putstr(cv, x, y, str);
}

void Cucul::Printf(int x, int y, char const * format,...)
{
    char tmp[BUFSIZ];
    char *buf = tmp;
    va_list args;

    va_start(args, format);
#if defined(HAVE_VSNPRINTF)
    vsnprintf(buf, getWidth() - x + 1, format, args);
#else
    vsprintf(buf, format, args);
#endif
    buf[getWidth() - x] = '\0';
    va_end(args);

    putStr(x, y, buf);
}

void Cucul::Clear(void)
{
    cucul_clear_canvas(cv);
}

void Cucul::Blit(int x, int y, Cucul* c1, Cucul* c2)
{
    cucul_blit(cv, x, y, c1->get_cucul_canvas_t(), c2->get_cucul_canvas_t());
}

void Cucul::Invert()
{
    cucul_invert(cv);
}

void Cucul::Flip()
{
    cucul_flip(cv);
}

void Cucul::Flop()
{
    cucul_flop(cv);
}

void Cucul::Rotate()
{
    cucul_rotate(cv);
}

void Cucul::drawLine(int x1, int y1, int x2, int y2, char const *ch)
{
    cucul_draw_line(cv, x1, y1, x2, y2, ch);
}

void Cucul::drawPolyline(int const x[], int const y[], int f, char const *ch)
{
    cucul_draw_polyline(cv, x, y, f, ch);
}

void Cucul::drawThinLine(int x1, int y1, int x2, int y2)
{
    cucul_draw_thin_line(cv, x1, y1, x2, y2);
}

void Cucul::drawThinPolyline(int const x[], int const y[], int f)
{
    cucul_draw_thin_polyline(cv, x, y, f);
}

void Cucul::drawCircle(int x, int y, int d, char const *ch)
{
    cucul_draw_circle(cv, x, y, d, ch);
}

void Cucul::drawEllipse(int x, int y, int d1, int d2, char const *ch)
{
    cucul_draw_ellipse(cv, x, y, d1, d2, ch);
}

void Cucul::drawThinEllipse(int x, int y, int d1, int d2)
{
    cucul_draw_thin_ellipse(cv, x, y, d1, d2);
}

void Cucul::fillEllipse(int x, int y, int d1, int d2, char const *ch)
{
    cucul_fill_ellipse(cv, x, y, d1, d2, ch);
}

void Cucul::drawBox(int x, int y, int w, int h, char const *ch)
{
    cucul_draw_box(cv, x, y, w, h, ch);
}

void Cucul::drawThinBox(int x, int y, int w, int h)
{
    cucul_draw_thin_box(cv, x, y, w, h);
}

void Cucul::fillBox(int x, int y, int w, int h, char const *ch)
{
    cucul_fill_box(cv, x, y, w, h, ch);
}

void Cucul::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, char const *ch)
{
    cucul_draw_triangle(cv, x1, y1, x2, y2, x3, y3, ch);
}

void Cucul::drawThinTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    cucul_draw_thin_triangle(cv, x1, y1, x2, y2, x3, y3);
}

void Cucul::fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const char *ch)
{
    cucul_fill_triangle(cv, x1, y1, x2, y2, x3, y3, ch);
}

int Cucul::Rand(int min, int max)
{
    return cucul_rand(min, max);
}

Dither::Dither(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4, unsigned int v5, unsigned int v6, unsigned int v7, unsigned int v8)
{
    dither = cucul_create_dither(v1, v2, v3, v4, v5, v6, v7, v8);
}
Dither::~Dither()
{
    cucul_free_dither(dither);
}

void Dither::setPalette(unsigned int r[], unsigned int g[], unsigned int b[], unsigned int a[])
{
    cucul_set_dither_palette(dither, r, g, b, a);
}

void Dither::setBrightness(float f)
{
    cucul_set_dither_brightness(dither, f);
}

void Dither::setGamma(float f)
{
    cucul_set_dither_gamma(dither, f);
}

void Dither::setContrast(float f)
{
    cucul_set_dither_contrast(dither, f);
}

void Dither::setInvert(int i)
{
    cucul_set_dither_invert(dither, i);
}

void Dither::setAntialias(char const *cv)
{
    cucul_set_dither_antialias(dither, cv);
}

char const *const * Dither::getAntialiasList()
{
    return cucul_get_dither_antialias_list(dither);
}

void Dither::setColor(char const *cv)
{
    cucul_set_dither_color(dither, cv);
}

char const *const * Dither::getColorList()
{
    return cucul_get_dither_color_list(dither);
}

void Dither::setCharset(char const *cv)
{
    cucul_set_dither_charset(dither, cv);
}

char const *const * Dither::getCharsetList()
{
    return cucul_get_dither_charset_list(dither);
}

void Dither::setMode(char const *cv)
{
    cucul_set_dither_mode(dither, cv);
}

char const *const * Dither::getModeList(void)
{
    return cucul_get_dither_mode_list(dither);
}

void Dither::Bitmap(Cucul *cv, int x, int y, int w, int h, void *v)
{
    cucul_dither_bitmap(cv->get_cucul_canvas_t(), x, y, w, h, dither, v);
}

Font::Font(void const *s, unsigned int v)
{
    font = cucul_load_font(s, v);
    if(!font) throw -1;
}

char const *const * Font::getList(void)
{
    return cucul_get_font_list();
}

unsigned int Font::getWidth()
{
    return cucul_get_font_width(font);
}

unsigned int Font::getHeight()
{
    return cucul_get_font_height(font);
}

void Font::renderCanvas(Cucul *cv, unsigned char *buf, unsigned int x, unsigned int y, unsigned int w)
{
    cucul_render_canvas(cv->get_cucul_canvas_t(), font, buf, x, y, w);
}

Font::~Font()
{
    cucul_free_font(font);
}

Buffer::Buffer(Cucul *cv, char const *buf)
{
    buffer = cucul_export_canvas(cv->get_cucul_canvas_t(), buf);
    if(!buffer) throw -1;
}

char const *const * Buffer::getExportList(void)
{
    return cucul_get_export_list();
}

cucul_buffer *Buffer::get_buffer(void)
{
    return buffer;
}