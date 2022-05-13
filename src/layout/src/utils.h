/////////////////////////////////////////////////////////////////////////////// //
//                          IMPORTANT NOTICE
//
// The following open source license statement does not apply to any
// entity in the Exception List published by FMSoft.
//
// For more information, please visit:
//
// https://www.fmsoft.cn/exception-list
//
//////////////////////////////////////////////////////////////////////////////
/**
 \verbatim

    This file is part of HiDOMLayout. hiDOMLayout is a library to
    maintain a DOM tree, lay out and stylize the DOM nodes by
    using CSS (Cascaded Style Sheets).

    Copyright (C) 2021~2022 Beijing FMSoft Technologies Co., Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General License for more details.

    You should have received a copy of the GNU Lesser General License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU Lesser General License version 3 (LGPLv3). If you cannot accept
    LGPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
 */

#ifndef _HL_UTILS_H_
#define _HL_UTILS_H_

#include "hidomlayout.h"
#include <libcss/libcss.h>

// top, right, bottom, left
#define HL_TOP          0
#define HL_RIGHT        1
#define HL_BOTTOM       2
#define HL_LEFT         3

#define HL_AUTO         INT_MIN
#define UNKNOWN_WIDTH   INT_MAX

/* Fixed point percentage (a) of an integer (b), to an integer */
#define HL_FPCT_OF_INT_TOINT(a, b) (FIXTOINT(FDIV((a * b), F_100)))

/** 22:10 fixed point */
#define HL_PLOT_STYLE_RADIX (10)

/** Scaling factor for plot styles */
#define HL_PLOT_STYLE_SCALE (1 << HL_PLOT_STYLE_RADIX)

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

struct HiLayoutNode;

typedef struct HLContext_ {
    HLMedia *media;
    HLCSS *css;
    css_fixed hl_css_media_dpi;
    css_fixed hl_css_baseline_pixel_density;

    int vw;
    int vh;
    const css_computed_style *root_style;

    struct HiLayoutNode *root;
} HLContext;

#ifdef __cplusplus
extern "C" {
#endif

css_fixed hl_css_pixels_css_to_physical(const HLContext *ctx,
        css_fixed css_pixels);
css_fixed hl_css_pixels_physical_to_css(const HLContext *ctx,
        css_fixed physical_pixels);
int hl_set_media_dpi(HLContext *ctx, int dpi);
int hl_set_baseline_pixel_density(HLContext *ctx, int density);

css_unit hl_css_utils_fudge_viewport_units(const HLContext *ctx, css_unit unit);
css_fixed hl_css_len2pt(const HLContext *ctx, css_fixed length, css_unit unit);
css_fixed hl_css_len2px(const HLContext *ctx,
        css_fixed length, css_unit unit, const css_computed_style *style);

uint8_t hl_computed_min_height(
        const css_computed_style *style,
        css_fixed *length, css_unit *unit);
uint8_t hl_computed_min_width(
        const css_computed_style *style,
        css_fixed *length, css_unit *unit);

uint8_t hl_computed_display(const css_computed_style *style, bool root);


void hl_destroy_svg_values(HLUsedSvgValues *svg);
lwc_string *hl_lwc_string_dup(const char *str);
void hl_lwc_string_destroy(lwc_string *str);

#ifdef __cplusplus
}
#endif

#endif // _HL_UTILS_H_

