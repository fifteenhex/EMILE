/*
 *
 * (c) 2004-2007 Laurent Vivier <Laurent@Vivier.EU>
 *
 */

#ifndef __VGA_H__
#define __VGA_H__

#include <macos/types.h>
#include <macos/video.h>

#include <emile_second_head.h>

extern int vga_init(const char *mode);

extern void vga_put(char c);
extern void vga_print(char *s);
extern void vga_cursor_refresh(void);

extern unsigned long vga_get_videobase(void);
extern unsigned long vga_get_row_bytes(void);
extern unsigned long vga_get_depth(void);
extern unsigned long vga_get_width(void);
extern unsigned long vga_get_height(void);
extern unsigned long vga_get_video(void);
extern int vga_is_available(void);
extern void vga_set_palette(RGBColor *palette);

#endif
