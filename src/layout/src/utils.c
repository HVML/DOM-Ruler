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

    Copyright (C) 2021 Beijing FMSoft Technologies Co., Ltd.

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

#include "hidomlayout.h"
#include "utils.h"
#include "node.h"
#include "hl_dom_element_node.h"
#include <string.h>

/** Media DPI in fixed point units: defaults to 96, same as nscss_baseline_pixel_density */
//css_fixed default_hl_css_media_dpi = F_96;
int hl_default_media_dpi = 96;

/** Medium screen density for device viewing distance. */
//css_fixed default_hl_css_baseline_pixel_density = F_96;
int hl_default_css_baseline_pixel_density = 96;

/**
 * Convert css pixels to physical pixels.
 *
 * \param[in] css_pixels  Length in css pixels.
 * \return length in physical pixels
 */
css_fixed hl_css_pixels_css_to_physical(const HLContext* ctx,
        css_fixed css_pixels)
{
    return FDIV(FMUL(css_pixels, ctx->hl_css_media_dpi),
            ctx->hl_css_baseline_pixel_density);
}

/**
 * Convert physical pixels to css pixels.
 *
 * \param[in] physical_pixels  Length in physical pixels.
 * \return length in css pixels
 */
css_fixed hl_css_pixels_physical_to_css(const HLContext* ctx,
        css_fixed physical_pixels)
{
    return FDIV(FMUL(physical_pixels, ctx->hl_css_baseline_pixel_density),
            ctx->hl_css_media_dpi);
}

int hl_set_media_dpi(HLContext *ctx, int dpi)
{
    if (dpi <= 0)
    {
        dpi = hl_default_media_dpi;
    }

    if (dpi < 72 || dpi > 250) {
        int bad = dpi;
        dpi = min(max(dpi, 72), 250);
    }
    ctx->hl_css_media_dpi = INTTOFIX(dpi);
    return HILAYOUT_OK;
}

int hl_set_baseline_pixel_density(HLContext* ctx, int density)
{
    if (density <= 0) {
        density = hl_default_css_baseline_pixel_density;
    }

    if (density < 72 || density > 250) {
        int bad = density;
        density = min(max(density, 72), 250);
    }
    ctx->hl_css_baseline_pixel_density = INTTOFIX(density);
    return HILAYOUT_OK;
}

css_unit hl_css_utils_fudge_viewport_units(const HLContext *ctx, css_unit unit)
{
    switch (unit) {
        case CSS_UNIT_VI:
            assert(ctx->root_style != NULL);
            if (css_computed_writing_mode(ctx->root_style) ==
                    CSS_WRITING_MODE_HORIZONTAL_TB) {
                unit = CSS_UNIT_VW;
            } else {
                unit = CSS_UNIT_VH;
            }
            break;
        case CSS_UNIT_VB:
            assert(ctx->root_style != NULL);
            if (css_computed_writing_mode(ctx->root_style) ==
                    CSS_WRITING_MODE_HORIZONTAL_TB) {
                unit = CSS_UNIT_VH;
            } else {
                unit = CSS_UNIT_VW;
            }
            break;
        case CSS_UNIT_VMIN:
            if (ctx->vh < ctx->vw) {
                unit = CSS_UNIT_VH;
            } else {
                unit = CSS_UNIT_VW;
            }
            break;
        case CSS_UNIT_VMAX:
            if (ctx->vh > ctx->vw) {
                unit = CSS_UNIT_VH;
            } else {
                unit = CSS_UNIT_VW;
            }
            break;
        default: break;
    }

    return unit;
}

css_fixed hl_css_len2pt(const HLContext *ctx, css_fixed length, css_unit unit)
{
    /* Length must not be relative */
    assert(unit != CSS_UNIT_EM &&
            unit != CSS_UNIT_EX &&
            unit != CSS_UNIT_CAP &&
            unit != CSS_UNIT_CH &&
            unit != CSS_UNIT_IC &&
            unit != CSS_UNIT_REM &&
            unit != CSS_UNIT_RLH);

    unit = hl_css_utils_fudge_viewport_units(ctx, unit);

    switch (unit) {
        /* We assume the screen and any other output has the same dpi */
        /* 1in = DPIpx => 1px = (72/DPI)pt */
        case CSS_UNIT_PX: return FDIV(FMUL(length, F_72), F_96);
                          /* 1in = 72pt */
        case CSS_UNIT_IN: return FMUL(length, F_72);
                          /* 1in = 2.54cm => 1cm = (72/2.54)pt */
        case CSS_UNIT_CM: return FMUL(length,
                                  FDIV(F_72, FLTTOFIX(2.54)));
                          /* 1in = 25.4mm => 1mm = (72/25.4)pt */
        case CSS_UNIT_MM: return FMUL(length,
                                  FDIV(F_72, FLTTOFIX(25.4)));
                          /* 1in = 101.6q => 1mm = (72/101.6)pt */
        case CSS_UNIT_Q: return FMUL(length,
                                 FDIV(F_72, FLTTOFIX(101.6)));
        case CSS_UNIT_PT: return length;
                          /* 1pc = 12pt */
        case CSS_UNIT_PC: return FMUL(length, INTTOFIX(12));
        case CSS_UNIT_VH: return FDIV(FMUL(FDIV(FMUL(length, ctx->vh), F_100), F_72), F_96);
        case CSS_UNIT_VW: return FDIV(FMUL(FDIV(FMUL(length,ctx->vw), F_100), F_72), F_96);
        default: break;
    }

    return 0;
}

css_fixed hl_css_len2px(const HLContext *ctx,
        css_fixed length, css_unit unit, const css_computed_style *style)
{
    /* We assume the screen and any other output has the same dpi */
    css_fixed px_per_unit;

    unit = hl_css_utils_fudge_viewport_units(ctx, unit);

    switch (unit) {
        case CSS_UNIT_PX:
            px_per_unit = F_1;
            break;
            /* 1in = 96 CSS pixels */
        case CSS_UNIT_IN:
            px_per_unit = F_96;
            break;
            /* 1in = 2.54cm => 1cm = (DPI/2.54)px */
        case CSS_UNIT_CM:
            px_per_unit = FDIV(F_96, FLTTOFIX(2.54));
            break;
            /* 1in = 25.4mm => 1mm = (DPI/25.4)px */
        case CSS_UNIT_MM:
            px_per_unit = FDIV(F_96, FLTTOFIX(25.4));
            break;
            /* 1in = 101.6q => 1q = (DPI/101.6)px */
        case CSS_UNIT_Q:
            px_per_unit = FDIV(F_96, FLTTOFIX(101.6));
            break;
            /* 1in = 72pt => 1pt = (DPI/72)px */
        case CSS_UNIT_PT:
            px_per_unit = FDIV(F_96, F_72);
            break;
            /* 1pc = 12pt => 1in = 6pc => 1pc = (DPI/6)px */
        case CSS_UNIT_PC:
            px_per_unit = FDIV(F_96, INTTOFIX(6));
            break;
        case CSS_UNIT_VH:
            px_per_unit = FDIV(ctx->vh, F_100);
            break;
        case CSS_UNIT_VW:
            px_per_unit = FDIV(ctx->vw, F_100);
            break;
        default:
            px_per_unit = 0;
            break;
    }

    px_per_unit = hl_css_pixels_css_to_physical(ctx, px_per_unit);

    /* Ensure we round px_per_unit to the nearest whole number of pixels:
     * the use of FIXTOINT() below will truncate. */
    px_per_unit += F_0_5;

    /* Calculate total number of pixels */
    return FMUL(length, TRUNCATEFIX(px_per_unit));
}


uint8_t hl_computed_min_height(
        const css_computed_style *style,
        css_fixed *length, css_unit *unit)
{
    uint8_t value = css_computed_min_height(style, length, unit);

    if (value == CSS_MIN_HEIGHT_AUTO) {
        value = CSS_MIN_HEIGHT_SET;
        *length = 0;
        *unit = CSS_UNIT_PX;
    }

    return value;
}

uint8_t hl_computed_min_width(
        const css_computed_style *style,
        css_fixed *length, css_unit *unit)
{
    uint8_t value = css_computed_min_width(style, length, unit);

    if (value == CSS_MIN_WIDTH_AUTO) {
        value = CSS_MIN_WIDTH_SET;
        *length = 0;
        *unit = CSS_UNIT_PX;
    }

    return value;
}


uint8_t hl_computed_display(const css_computed_style *style, bool root)
{
    uint8_t value = css_computed_display(style, root);

    switch (value) {
    case CSS_DISPLAY_BLOCK:
        return LAYOUT_BLOCK;

    case CSS_DISPLAY_INLINE_BLOCK:
        return LAYOUT_INLINE_BLOCK;
#if 1
    case CSS_DISPLAY_GRID:
        return LAYOUT_GRID;

    case CSS_DISPLAY_INLINE_GRID:
        return LAYOUT_INLINE_GRID;
#else
    case CSS_DISPLAY_GRID:
        return LAYOUT_BLOCK;

    case CSS_DISPLAY_INLINE_GRID:
        return LAYOUT_INLINE_BLOCK;
#endif

    default:
        return LAYOUT_BLOCK;
    }
}

HLGridItem *hl_grid_item_create(void *node,
        hidomlayout_node_op *op)
{
    if (node == NULL) {
        return NULL;
    }

    css_fixed value = 0;
    css_unit unit = CSS_UNIT_PX;

    HiLayoutNode *layout = (HiLayoutNode *)op->get_attach(node, NULL);
    HLGridItem *item = calloc(1, sizeof(HLGridItem));

    int8_t type = css_computed_grid_column_start(layout->computed_style,
            &value, &unit);
    if (type == CSS_GRID_COLUMN_START_SET)
    {
        item->rc_set = item->rc_set | HL_GRID_ITEM_RC_COLUMN_START;
        item->column_start = FIXTOINT(value);
    }

    type = css_computed_grid_column_end(layout->computed_style, &value, &unit);
    if (type == CSS_GRID_COLUMN_END_SET)
    {
        item->rc_set = item->rc_set | HL_GRID_ITEM_RC_COLUMN_END;
        item->column_end = FIXTOINT(value);
    }

    type = css_computed_grid_row_start(layout->computed_style, &value, &unit);
    if (type == CSS_GRID_ROW_START_SET)
    {
        item->rc_set = item->rc_set | HL_GRID_ITEM_RC_ROW_START;
        item->row_start = FIXTOINT(value);
    }

    type = css_computed_grid_row_end(layout->computed_style, &value, &unit);
    if (type == CSS_GRID_ROW_END_SET)
    {
        item->rc_set = item->rc_set | HL_GRID_ITEM_RC_ROW_END;
        item->row_end = FIXTOINT(value);
    }

    hl_element_node_set_inner_data(node, HL_INNER_LAYOUT_ATTACH, item, NULL);
    return item;
}

HLGridTemplate *hl_grid_template_create(const HLContext *ctx,
        void *node, hidomlayout_node_op *op)
{
    if (node == NULL) {
        return NULL;
    }

    int row_size = 0;
    css_fixed *row_values = NULL;
    css_unit *row_units = NULL;

    int column_size = 0;
    css_fixed *column_values = NULL;
    css_unit *column_units = NULL;

    uint8_t ret = 0;
    HiLayoutNode *layout = (HiLayoutNode *)op->get_attach(node, NULL);

    ret = css_computed_grid_template_rows(layout->computed_style,
            &row_size, &row_values, &row_units);
    if (ret != CSS_GRID_TEMPLATE_ROWS_SET) {
        return NULL;
    }

    ret = css_computed_grid_template_columns(layout->computed_style,
            &column_size, &column_values, &column_units);
    if (ret != CSS_GRID_TEMPLATE_COLUMNS_SET) {
        return NULL;
    }

    HLGridTemplate *gt = (HLGridTemplate*)calloc(1, sizeof(HLGridTemplate));
    gt->x = layout->box_values.x;
    gt->y = layout->box_values.y;
    gt->w = layout->box_values.w;
    gt->h = layout->box_values.h;

    gt->n_row = row_size;
    gt->n_column = column_size;
    gt->mask = (uint8_t**)calloc(gt->n_row, sizeof(uint8_t*));
    for (int i = 0; i < gt->n_row; i++) {
        gt->mask[i] = (uint8_t*)calloc(gt->n_column, sizeof(uint8_t));
    }

    gt->rows = (int32_t*)malloc(gt->n_row * sizeof(int32_t));
    gt->columns = (int32_t*)malloc(gt->n_column * sizeof(int32_t));

    for (int i = 0; i < row_size; i++) {
        if (row_units[i] == CSS_UNIT_PCT) {
            gt->rows[i] = HL_FPCT_OF_INT_TOINT(row_values[i], gt->h);
        } else {
            gt->rows[i] = FIXTOINT(hl_css_len2px(ctx, row_values[i],
                        row_units[i], layout->computed_style));
        }
    }

    for (int i = 0; i < column_size; i++)
    {
        if (column_units[i] == CSS_UNIT_PCT) {
            gt->columns[i] = HL_FPCT_OF_INT_TOINT(column_values[i], gt->w);
        } else {
            gt->columns[i] = FIXTOINT(hl_css_len2px(ctx, column_values[i],
                        column_units[i], layout->computed_style));
        }
    }

    free(row_values);
    free(row_units);
    free(column_values);
    free(column_units);

    return gt;
}

void hl_grid_item_destroy(HLGridItem *p)
{
    if (p) {
        free(p);
    }
}

void hl_grid_template_destroy(HLGridTemplate *p)
{
    if (p == NULL) {
        return;
    }

    if (p->rows != NULL) {
        free(p->rows);
    }

    if (p->columns != NULL) {
        free(p->columns);
    }

    if (p->mask != NULL) {
        for (int i = 0; i < p->n_row; i++) {
            free(p->mask[i]);
        }
    }

    free(p->mask);
    free(p);
}

void hl_for_each_child(HLContext *ctx, void *node,
        hidomlayout_node_op *op,
        each_child_callback callback, void *user_data)
{
    if (ctx == NULL || node == NULL || callback == NULL) {
        return;
    }

    void *child = op->first_child(node);
    while(child) {
        callback(ctx, child, op, user_data);
        child = op->next(child);
    }
}

int hl_find_font(HLContext *ctx, void *node,
        hidomlayout_node_op *op)
{
    lwc_string **families;
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;

    HiLayoutNode *layout = (HiLayoutNode *)op->get_attach(node, NULL);
    void *parent = op->get_parent(node);
    HiLayoutNode* parent_layout = parent ?
        (HiLayoutNode *)op->get_attach(node, NULL) : NULL;

    uint8_t val = css_computed_font_family(layout->computed_style, &families);
    if (val == CSS_FONT_FAMILY_INHERIT) {
        HL_LOGD("layout node|tag=%s|id=%s|font inherit\n", node->tag, node->id);
        if (parent && parent_layout->text_values.font_family) {
            free (layout->text_values.font_family);
            layout->text_values.font_family = strdup(parent_layout->text_values.font_family);
        }
    }
    else {
        char* buf[1024] = {0};
        int index = 0;
        int len = 0;
        if (families != NULL) {
            while (*families != NULL) {
                buf[index] = strdup(lwc_string_data(*families));
                len += strlen(buf[index]) + 1;
                index++;
                families++;
            }
        }

        switch (val) {
            case CSS_FONT_FAMILY_SERIF:
                buf[index] = strdup("serif");
                len += strlen(buf[index]) + 1;
                index++;
                break;
            case CSS_FONT_FAMILY_SANS_SERIF:
                buf[index] = strdup("sans-serif");
                len += strlen(buf[index]) + 1;
                index++;
                break;
            case CSS_FONT_FAMILY_CURSIVE:
                buf[index] = strdup("cursive");
                len += strlen(buf[index]) + 1;
                index++;
                break;
            case CSS_FONT_FAMILY_FANTASY:
                buf[index] = strdup("fantasy");
                len += strlen(buf[index]) + 1;
                index++;
                break;
            case CSS_FONT_FAMILY_MONOSPACE:
                buf[index] = strdup("monospace");
                len += strlen(buf[index]) + 1;
                index++;
                break;
        }

        char* result = (char*)calloc(len + 1, 1);
        for (int i=0; i<index; i++) {
            strcat(result, buf[i]);
            strcat(result, ",");
            free(buf[i]);
        }
        result[strlen(result) - 1 ] = 0;
        free (layout->text_values.font_family);
        layout->text_values.font_family = result;
    }

    css_computed_font_size(layout->computed_style, &length, &unit);
    int text_height = hl_css_len2px(ctx, length, unit, layout->computed_style);
    layout->text_values.font_size = FIXTOINT(text_height * 3 / 4);

    css_color color;
    val = css_computed_color(layout->computed_style, &color);
    if (val == CSS_COLOR_INHERIT) {
        if (parent) {
            layout->text_values.color = parent_layout->text_values.color;
        }
    } else if (val == CSS_COLOR_COLOR) {
        layout->text_values.color = color;
    }

    val = css_computed_font_weight(layout->computed_style);
    switch (val) {
    case CSS_FONT_WEIGHT_100:
        layout->text_values.font_weight = HLFONT_WEIGHT_THIN;
        break;
    case CSS_FONT_WEIGHT_200:
        layout->text_values.font_weight = HLFONT_WEIGHT_EXTRA_LIGHT;
        break;
    case CSS_FONT_WEIGHT_300:
        layout->text_values.font_weight = HLFONT_WEIGHT_LIGHT;
        break;
    case CSS_FONT_WEIGHT_400:
    case CSS_FONT_WEIGHT_NORMAL:
    default:
        layout->text_values.font_weight = HLFONT_WEIGHT_NORMAL;
        break;
    case CSS_FONT_WEIGHT_500:
        layout->text_values.font_weight = HLFONT_WEIGHT_MEDIUM;
        break;
    case CSS_FONT_WEIGHT_600:
        layout->text_values.font_weight = HLFONT_WEIGHT_DEMIBOLD;
        break;
    case CSS_FONT_WEIGHT_700:
    case CSS_FONT_WEIGHT_BOLD:
        layout->text_values.font_weight = HLFONT_WEIGHT_BOLD;
        break;
    case CSS_FONT_WEIGHT_800:
        layout->text_values.font_weight = HLFONT_WEIGHT_EXTRA_BOLD;
        break;
    case CSS_FONT_WEIGHT_900:
        layout->text_values.font_weight = HLFONT_WEIGHT_BLACK;
        break;
    }
}

int hl_find_background(void *node, hidomlayout_node_op *op)
{
    css_color color;
    HiLayoutNode *layout = (HiLayoutNode *)op->get_attach(node, NULL);
    css_computed_background_color(layout->computed_style, &color);
    layout->background_values.color = color;
    return HILAYOUT_OK;
}

void hl_destroy_svg_values(HLUsedSvgValues* svg)
{
    if (svg == NULL)
    {
        return;
    }
    // baseline_shift
    // clip-path
    free(svg->clip_path);
    // clip-rule
    // color
    // direction
    // display
    // enable-background
    // comp-op
    // fill
    free(svg->fill_string);
    // fill-opacity
    // fill-rule
    // filter
    free(svg->filter);
    // flood-color
    // flood-opacity
    // font-family
    free(svg->font_family);
    // font-size
    // font-stretch
    // font-style
    // font-variant
    // font-weight
    // marker-end
    free(svg->marker_end);
    // mask
    free(svg->mask);
    // marker-mid
    free(svg->marker_mid);
    // marker-start
    free(svg->marker_start);
    // opacity
    // overflow
    // shape-rendering
    // text-rendering
    // stop-color
    // stop-opacity
    // stroke
    free(svg->stroke_string);
    // stroke-dasharray
    free(svg->stroke_dasharray);
    // stroke-dashoffset
    // stroke-linecap
    // stroke-linejoin
    // stroke-miterlimit
    // stroke-opacity
    // stroke-width
    // text-anchor
    // text-decoration
    // unicode-bidi
    // letter-spacing
    // visibility
    // writing-mode
    free(svg);
}
