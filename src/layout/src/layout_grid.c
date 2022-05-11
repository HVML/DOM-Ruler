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


#include "layout.h"
#include "select.h"
#include "utils.h"
#include "hl_dom_element_node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

int hl_solve_grid_child_width_height(HLContext* ctx, HLDomElementNode *node, int grid_w, int grid_h)
{
    int width = 0;
    int max_width = 0;
    int min_width = 0;

    int height = 0;
    int max_height = 0;
    int min_height = 0;

    uint8_t type = 0;
    css_fixed value = 0;
    css_unit unit = CSS_UNIT_PX;

    // start width
    type = css_computed_width(node->layout.computed_style, &value, &unit);
    if (type == CSS_WIDTH_SET) {
        if (unit == CSS_UNIT_PCT) {
            width = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            width = FIXTOINT(hl_css_len2px(ctx, value, unit, node->layout.computed_style));
        }
    }
    else
    {
        width = grid_w;
    }

    value = 0;
    unit = CSS_UNIT_PX;
    type = css_computed_max_width(node->layout.computed_style, &value, &unit);
    if (type == CSS_MAX_WIDTH_SET) {
        if (unit == CSS_UNIT_PCT) {
            max_width = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            max_width = FIXTOINT(hl_css_len2px(ctx, value, unit, node->layout.computed_style));
        }
    } else {
        /* Inadmissible */
        max_width = -1;
    }


    value = 0;
    unit = CSS_UNIT_PX;
    type = hl_computed_min_width(node->layout.computed_style, &value, &unit);
    if (type == CSS_MIN_WIDTH_SET) {
        if (unit == CSS_UNIT_PCT) {
            min_width = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            min_width = FIXTOINT(hl_css_len2px(ctx, value, unit, node->layout.computed_style));
        }
    } else {
        /* Inadmissible */
        min_width = 0;
    }
    // end width

    // start height
    type = css_computed_height(node->layout.computed_style, &value, &unit);
    if (type == CSS_HEIGHT_SET) {
        if (unit == CSS_UNIT_PCT) {
            height = HL_FPCT_OF_INT_TOINT(value, grid_h);
        } else {
            height = FIXTOINT(hl_css_len2px(ctx, value, unit, node->layout.computed_style));
        }
    }
    else
    {
        height = grid_h;
    }

    value = 0;
    unit = CSS_UNIT_PX;
    type = css_computed_max_height(node->layout.computed_style, &value, &unit);
    if (type == CSS_MAX_HEIGHT_SET) {
        if (unit == CSS_UNIT_PCT) {
            max_height = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            max_height = FIXTOINT(hl_css_len2px(ctx, value, unit, node->layout.computed_style));
        }
    } else {
        /* Inadmissible */
        max_height = -1;
    }


    value = 0;
    unit = CSS_UNIT_PX;
    type = hl_computed_min_height(node->layout.computed_style, &value, &unit);
    if (type == CSS_MIN_HEIGHT_SET) {
        if (unit == CSS_UNIT_PCT) {
            min_height = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            min_height = FIXTOINT(hl_css_len2px(ctx, value, unit, node->layout.computed_style));
        }
    } else {
        /* Inadmissible */
        min_height = 0;
    }
    // end height

    if (max_width >= 0 && width > max_width) {
        width = max_width;
    }

    if (min_width > 0 && width < min_width) {
        width = min_width;
    }

    if (max_height >= 0 && height > max_height) {
        height = max_height;
    }

    if (min_height > 0 && height < min_height) {
        height = min_height;
    }

    node->layout.box_values.w = width;
    node->layout.box_values.h = height;

    return HILAYOUT_OK;
}

int hl_find_grid_child_position(HLContext* ctx, HLGridTemplate* grid_template, HLDomElementNode *node, HLGridItem* row_column)
{
    // no set
    bool found = false;
    int row = 0;
    int column = 0;
    int x = 0;
    int y = 0;
    for (int i = 0; i < grid_template->n_row; i++)
    {
        x = 0;
        for (int j = 0; j < grid_template->n_column; j++)
        {
            if (grid_template->mask[i][j] == 0)
            {
                row = i;
                column = j;
                found = true;
                break;
            }
            x = x + grid_template->columns[j];
        }
        if (found)
            break;
        y = y + grid_template->rows[i];
    }

    grid_template->mask[row][column] = 1;
    int h = grid_template->rows[row];
    int w = grid_template->columns[column];

    hl_solve_grid_child_width_height(ctx, node, w, h);

    // grid-row-start, grid-row-end, grid-column-start, grid-column-end

    // grid-row-start, grid-row-end

    // grid-column-start, grid-column-end
    return 0;
}

int hl_layout_grid_child(HLContext* ctx, HLGridTemplate* grid_template,
        HLDomElementNode *node, int level, hidomlayout_layout_handler *handler)
{
    HL_LOGW("layout grid item|level=%d|tag=%s|id=%s\n", level, node->tag,
            hilayout_element_node_get_id(node));

    HLGridItem* node_row_column = hl_grid_item_create(node, handler);
    hl_find_grid_child_position(ctx, grid_template, node, node_row_column);
    hl_grid_item_destroy(node_row_column);
}

HLGridItem* hl_get_grid_item(HLContext* ctx, HLDomElementNode* node,
        hidomlayout_layout_handler *handler)
{
    HLGridItem* item = (HLGridItem*)hl_element_node_get_inner_data(node, HL_INNER_LAYOUT_ATTACH);
    if (item)
    {
        return item;
    }
    hl_computed_z_index(node, handler);
    hl_find_background(node, handler);
    hl_find_font(ctx, node, handler);
    return hl_grid_item_create(node, handler);
}

HLGridItem* hl_destroy_grid_item(HLDomElementNode* node)
{
    HLGridItem* item = (HLGridItem*)hl_element_node_get_inner_data(node, HL_INNER_LAYOUT_ATTACH);
    if (item)
    {
        free(item);
    }
    hl_element_node_set_inner_data(node, HL_INNER_LAYOUT_ATTACH, NULL, NULL);
}

void hl_layout_child_with_grid_rc_row_column(HLContext *ctx,
        void *n, hidomlayout_layout_handler *handler,
        void* user_data)
{
    HLDomElementNode *node = (HLDomElementNode *)n;
    HLGridTemplate* grid_template = (HLGridTemplate*)user_data;
    HLGridItem* item = hl_get_grid_item(ctx, node, handler);
    int set_row = (item->rc_set & HL_GRID_ITEM_RC_ROW_START) | (item->rc_set & HL_GRID_ITEM_RC_ROW_END);
    int set_column = (item->rc_set & HL_GRID_ITEM_RC_COLUMN_START) | (item->rc_set & HL_GRID_ITEM_RC_COLUMN_END);

    if (!(set_row && set_column))
    {
        return;
    }

    int n_row = grid_template->n_row;
    int n_column = grid_template->n_column;

    int r_count = 0;
    int r_start = 0;
    int r_end = 0;

    int c_count = 0;
    int c_start = 0;
    int c_end = 0;

    switch(set_row)
    {
        case HL_GRID_ITEM_RC_ROW_START | HL_GRID_ITEM_RC_ROW_END:
            r_start = item->row_start - 1;
            r_count = max(abs(item->row_end - item->row_start), 1);
            break;

        case HL_GRID_ITEM_RC_ROW_START:
            r_start = item->row_start - 1;
            r_count = 1;
            break;

        case HL_GRID_ITEM_RC_ROW_END:
            r_start = item->row_end - 2;
            r_count = 1;
            break;
    }
    r_start = r_start >= 0 ? r_start : 0;
    r_end = r_start + r_count;

    // TODO: row_start, row_end > row count
    // now as auto
    if (r_start > n_row - 1)
    {
        item->rc_set = item->rc_set & (~set_row);
        return;
    }

    switch(set_column)
    {
        case HL_GRID_ITEM_RC_COLUMN_START | HL_GRID_ITEM_RC_COLUMN_END:
            c_start = item->column_start - 1;
            c_count = max(abs(item->column_end - item->column_start), 1);
            break;

        case HL_GRID_ITEM_RC_COLUMN_START:
            c_start = item->column_start - 1;
            c_count = 1;
            break;

        case HL_GRID_ITEM_RC_COLUMN_END:
            c_start = item->column_end - 2;
            c_count = 1;
            break;
    }
    c_start = c_start >= 0 ? c_start : 0;
    c_end = c_start + c_count;

    // TODO: column_start, column_end > column count
    // now as auto
    if (c_start > n_column - 1)
    {
        item->rc_set = item->rc_set & (~set_column);
        return;
    }

    int grid_x = 0;
    int grid_y = 0;
    int grid_w = 0;
    int grid_h = 0;

    for (int i = 0; i < r_start; i++)
    {
        grid_y += grid_template->rows[i];
    }

    for (int j = 0; j < c_start; j++)
    {
        grid_x += grid_template->columns[j];
    }

    for (int i = r_start; i < r_end && i < n_row; i++)
    {
        grid_h += grid_template->rows[i];
    }

    for (int i = c_start; i < c_end && i < n_column; i++)
    {
        grid_w += grid_template->columns[i];
    }

    node->layout.box_values.x = node->parent->layout.box_values.x + grid_x;
    node->layout.box_values.y = node->parent->layout.box_values.y + grid_y;
    item->layout_done = 1;
    hl_solve_grid_child_width_height(ctx, node, grid_w, grid_h);


    // mask
    for (int i = r_start; i < r_end && i < n_row; i++)
    {
        for (int j = c_start; j < c_end && j < n_column; j++)
        {
            grid_template->mask[i][j] = 1;
        }
    }

    HL_LOGW("layout grid rc row column|row_start=%d|row_count=%d|column_start=%d|column_count=%d"
            "|tag=%s|id=%s|(x,y,w,h)=(%f, %f, %f, %f)|layout_done=%d\n",
            item->row_start, r_count,
            item->column_start, c_count,
            node->tag, hilayout_element_node_get_id(node),
            node->layout.box_values.x, node->layout.box_values.y, node->layout.box_values.w, node->layout.box_values.h,
            item->layout_done);

}

void hl_layout_child_with_grid_rc_row(HLContext* ctx,
        void *n, hidomlayout_layout_handler *handler,
        void* user_data)
{
    HLDomElementNode *node = (HLDomElementNode *)n;
    HLGridTemplate* grid_template = (HLGridTemplate*)user_data;
    HLGridItem* item = hl_get_grid_item(ctx, node, handler);
    int set_row = (item->rc_set & HL_GRID_ITEM_RC_ROW_START) | (item->rc_set & HL_GRID_ITEM_RC_ROW_END);

    if (item->layout_done || !set_row)
    {
        return;
    }

    int n_row = grid_template->n_row;
    int n_column = grid_template->n_column;

    int r_count = 0;
    int r_start = 0;
    int r_end = 0;

    switch(set_row)
    {
        case HL_GRID_ITEM_RC_ROW_START | HL_GRID_ITEM_RC_ROW_END:
            r_start = item->row_start - 1;
            r_count = max(abs(item->row_end - item->row_start), 1);
            break;

        case HL_GRID_ITEM_RC_ROW_START:
            r_start = item->row_start - 1;
            r_count = 1;
            break;

        case HL_GRID_ITEM_RC_ROW_END:
            r_start = item->row_end - 2;
            r_count = 1;
            break;
    }
    r_start = r_start >= 0? r_start : 0;
    r_end = r_start + r_count;

    // TODO: r_start > row count
    // now as auto
    if (r_start > n_row - 1)
    {
        item->rc_set = item->rc_set & (~set_row);
        return;
    }

    int c_start = -1;
    int c_end = -1;
    bool found = false;
    for (int i = 0; i < grid_template->n_column; i++)
    {
        found = true;
        for (int j = r_start; j < r_end; j++)
        {
            if (grid_template->mask[j][i] == 1)
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            c_start = i;
            break;
        }
    }

    if (!found)
    {
        item->rc_set = item->rc_set & (~set_row);
        return;
    }

    c_end = c_start + 1;

    int grid_x = 0;
    int grid_y = 0;
    int grid_w = 0;
    int grid_h = 0;

    for (int i = 0; i < r_start; i++)
    {
        grid_y += grid_template->rows[i];
    }

    for (int j = 0; j < c_start; j++)
    {
        grid_x += grid_template->columns[j];
    }

    for (int i = r_start; i < r_end && i < n_row; i++)
    {
        grid_h += grid_template->rows[i];
    }

    for (int i = c_start; i < c_end && i < n_column; i++)
    {
        grid_w += grid_template->columns[i];
    }

    node->layout.box_values.x = node->parent->layout.box_values.x + grid_x;
    node->layout.box_values.y = node->parent->layout.box_values.y + grid_y;
    item->layout_done = 1;
    hl_solve_grid_child_width_height(ctx, node, grid_w, grid_h);

    // mask
    for (int i = r_start; i < r_end && i < n_row; i++)
    {
        for (int j = c_start; j < c_end && j < n_column; j++)
        {
            grid_template->mask[i][j] = 1;
        }
    }


    HL_LOGW("layout grid rc row|r_start=%d|r_count=%d"
            "|tag=%s|id=%s|(x,y,w,h)=(%f, %f, %f, %f)|layout_done=%d\n",
            r_start, r_count,
            node->tag, hilayout_element_node_get_id(node),
            node->layout.box_values.x, node->layout.box_values.y, node->layout.box_values.w, node->layout.box_values.h,
            item->layout_done);
}

void hl_layout_child_with_grid_rc_auto(HLContext* ctx,
        void *n, hidomlayout_layout_handler *handler,
        void* user_data)
{
    HLDomElementNode *node = (HLDomElementNode *)n;
    HLGridTemplate* grid_template = (HLGridTemplate*)user_data;
    HLGridItem* item = hl_get_grid_item(ctx, node, handler);

    if (item->layout_done)
    {
        return;
    }

    int n_row = grid_template->n_row;
    int n_column = grid_template->n_column;
    int set_column = (item->rc_set & HL_GRID_ITEM_RC_COLUMN_START) | (item->rc_set & HL_GRID_ITEM_RC_COLUMN_END);

    int c_count = 0;
    int c_start = 0;
    int c_end = 0;

    switch(set_column)
    {
        case HL_GRID_ITEM_RC_COLUMN_START | HL_GRID_ITEM_RC_COLUMN_END:
            c_start = item->column_start - 1;
            c_count = max(abs(item->column_end - item->column_start), 1);
            break;

        case HL_GRID_ITEM_RC_COLUMN_START:
            c_start = item->column_start - 1;
            c_count = 1;
            break;

        case HL_GRID_ITEM_RC_COLUMN_END:
            c_start = item->column_end - 2;
            c_count = 1;
            break;

        default:
            c_count = 0;
            break;
    }
    int r_start = -1;
    int r_end = -1;

    if (c_count == 0)
    {
        for (int i = 0; i < n_row; i++)
        {
            for (int j = 0; j < n_column; j++)
            {
                if (grid_template->mask[i][j] == 0)
                {
                    r_start = i;
                    r_end = r_start + 1;
                    c_start = j;
                    c_end = c_start + 1;
                    break;
                }
            }
            if (r_start > -1)
            {
                break;
            }
        }
    }
    else
    {
        c_start = c_start >= 0 ? c_start : 0;
        c_end = c_start + c_count;
        bool found = false;
        for (int i = 0; i < n_row; i++)
        {
            found = true;
            for (int j = c_start; j < c_end && j< n_column; j++)
            {
                if (grid_template->mask[i][j] == 1)
                {
                    found = false;
                    break;
                }
            }
            if (found)
            {
                r_start = i;
                r_end = r_start + 1;
                break;
            }
        }
    }

    int grid_x = 0;
    int grid_y = 0;
    int grid_w = 0;
    int grid_h = 0;

    for (int i = 0; i < r_start; i++)
    {
        grid_y += grid_template->rows[i];
    }

    for (int j = 0; j < c_start; j++)
    {
        grid_x += grid_template->columns[j];
    }

    for (int i = r_start; i < r_end && i < n_row; i++)
    {
        grid_h += grid_template->rows[i];
    }

    for (int i = c_start; i < c_end && i < n_column; i++)
    {
        grid_w += grid_template->columns[i];
    }

    node->layout.box_values.x = node->parent->layout.box_values.x + grid_x;
    node->layout.box_values.y = node->parent->layout.box_values.y + grid_y;
    item->layout_done = 1;
    hl_solve_grid_child_width_height(ctx, node, grid_w, grid_h);

    // mask
    for (int i = r_start; i < r_end && i < n_row; i++)
    {
        for (int j = c_start; j < c_end && j < n_column; j++)
        {
            grid_template->mask[i][j] = 1;
        }
    }

    HL_LOGW("layout grid rc auto|"
            "|tag=%s|id=%s|(x,y,w,h)=(%f, %f, %f, %f)|layout_done=%d\n",
            node->tag, hilayout_element_node_get_id(node),
            node->layout.box_values.x, node->layout.box_values.y, node->layout.box_values.w, node->layout.box_values.h,
            item->layout_done);
}

void hl_free_grid_item(HLContext* ctx,
        void *n, hidomlayout_layout_handler *handler,
        void* user_data)
{
    HLDomElementNode *node = (HLDomElementNode *)n;
    hl_destroy_grid_item(node);
}

int hl_layout_child_node_grid(HLContext* ctx, HLDomElementNode *node, int level, hidomlayout_layout_handler *handler)
{
    HLGridTemplate* grid_template = hl_grid_template_create(ctx, node, handler);

    int cl = level + 1;
    // layout with grid-row-start/end, grid-column-start/end
    hl_for_each_child(ctx, node, handler, hl_layout_child_with_grid_rc_row_column, grid_template);
    // layout with grid-row-start/end
    hl_for_each_child(ctx, node, handler, hl_layout_child_with_grid_rc_row, grid_template);
    // layout auto
    hl_for_each_child(ctx, node, handler, hl_layout_child_with_grid_rc_auto, grid_template);
    // free grid tree
    hl_for_each_child(ctx, node, handler, hl_free_grid_item, grid_template);
    // while for layout child call hl_layout_node
    //
    // clear
    hl_grid_template_destroy(grid_template);

    return HILAYOUT_OK;
}
