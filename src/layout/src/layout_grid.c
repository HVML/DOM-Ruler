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

    This file is part of HybridOS, a developing operating system based on
    MiniGUI. HybridOs will support embedded systems and smart IoT devices.

    Copyright (C) 2020 Beijing FMSoft Technologies Co., Ltd.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/blog/minigui-licensing-policy/>.

 \endverbatim
 */


#include "layout.h"
#include "select.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int _hl_solve_grid_child_width_height(HLContext* ctx, HLDomElementNode *node, int grid_w, int grid_h)
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
    type = css_computed_width(node->computed_style, &value, &unit);
    if (type == CSS_WIDTH_SET) {
        if (unit == CSS_UNIT_PCT) {
            width = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            width = FIXTOINT(_hl_css_len2px(ctx, value, unit, node->computed_style));
        }
    }
    else
    {
        width = grid_w;
    }

    value = 0;
    unit = CSS_UNIT_PX;
    type = css_computed_max_width(node->computed_style, &value, &unit);
    if (type == CSS_MAX_WIDTH_SET) {
        if (unit == CSS_UNIT_PCT) {
            max_width = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            max_width = FIXTOINT(_hl_css_len2px(ctx, value, unit, node->computed_style));
        }
    } else {
        /* Inadmissible */
        max_width = -1;
    }


    value = 0;
    unit = CSS_UNIT_PX;
    type = _hl_computed_min_width(node->computed_style, &value, &unit);
    if (type == CSS_MIN_WIDTH_SET) {
        if (unit == CSS_UNIT_PCT) {
            min_width = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            min_width = FIXTOINT(_hl_css_len2px(ctx, value, unit, node->computed_style));
        }
    } else {
        /* Inadmissible */
        min_width = 0;
    }
    // end width
    
    // start height
    type = css_computed_height(node->computed_style, &value, &unit);
    if (type == CSS_HEIGHT_SET) {
        if (unit == CSS_UNIT_PCT) {
            height = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            height = FIXTOINT(_hl_css_len2px(ctx, value, unit, node->computed_style));
        }
    }
    else
    {
        height = grid_h;
    }

    value = 0;
    unit = CSS_UNIT_PX;
    type = css_computed_max_height(node->computed_style, &value, &unit);
    if (type == CSS_MAX_HEIGHT_SET) {
        if (unit == CSS_UNIT_PCT) {
            max_height = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            max_height = FIXTOINT(_hl_css_len2px(ctx, value, unit, node->computed_style));
        }
    } else {
        /* Inadmissible */
        max_height = -1;
    }


    value = 0;
    unit = CSS_UNIT_PX;
    type = _hl_computed_min_height(node->computed_style, &value, &unit);
    if (type == CSS_MIN_HEIGHT_SET) {
        if (unit == CSS_UNIT_PCT) {
            min_height = HL_FPCT_OF_INT_TOINT(value, grid_w);
        } else {
            min_height = FIXTOINT(_hl_css_len2px(ctx, value, unit, node->computed_style));
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

    node->box_values.w = width;
    node->box_values.h = height;

    return HILAYOUT_OK;
}

int _hl_find_grid_child_position(HLContext* ctx, HLGridTemplate* grid_template, HLDomElementNode *node, HLGridRowColumn* row_column)
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

    _hl_solve_grid_child_width_height(ctx, node, w, h);
    fprintf(stderr, "...................................row=%d|column=%d|x=%d|y=%d|gw=%d|gh=%d|w=%f|h=%f\n", 
            row, column, x, y, w, h, node->box_values.w, node->box_values.h);

    // grid-row-start, grid-row-end, grid-column-start, grid-column-end

    // grid-row-start, grid-row-end

    // grid-column-start, grid-column-end
    return 0;
}

int _hl_layout_grid_child(HLContext* ctx, HLGridTemplate* grid_template, HLDomElementNode *node, int level)
{
    HL_LOGW("layout grid item|level=%d|tag=%s|id=%s|name=%s\n", level, node->tag, node->attr[HL_ATTR_NAME_ID], node->attr[HL_ATTR_NAME_NAME] );

    HLGridRowColumn* node_row_column = _hl_computed_grid_row_column(node);
    _hl_find_grid_child_position(ctx, grid_template, node, node_row_column);
    _hl_grid_row_column_destroy(node_row_column);
}

int _hl_layout_child_node_grid(HLContext* ctx, HLDomElementNode *node, int level)
{
    HLGridTemplate* grid_template = _hl_computed_grid_template(ctx, node);

    int cl = level + 1;
    HLDomElementNode* child = node->first_child;
    while(child)
    {
        _hl_layout_grid_child(ctx, grid_template, child, cl);
        child = child->next;
    }
    _hl_grid_template_destroy(grid_template);

    return HILAYOUT_OK;
}
