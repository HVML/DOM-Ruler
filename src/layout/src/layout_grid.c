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

int _hl_layout_grid_child(HLContext* ctx, HLGridTemplate* gridTemplate, HLDomElementNode *node, int level)
{
    HLGridRowColumn* gridRC = _hl_computed_grid_row_column(node);
    HL_LOGW("layout grid item|level=%d|tag=%s|id=%s|name=%s\n", level, node->tag, node->attr[HL_ATTR_NAME_ID], node->attr[HL_ATTR_NAME_NAME] );

    _hl_grid_row_column_destroy(gridRC);
}

int _hl_layout_child_node_grid(HLContext* ctx, HLDomElementNode *node, int level)
{
    HLGridTemplate* gridTemplate = _hl_computed_grid_template(ctx, node);

    int cl = level + 1;
    HLDomElementNode* child = node->first_child;
    while(child)
    {
        _hl_layout_grid_child(ctx, gridTemplate, node, cl);
        child = child->next;
    }
    _hl_grid_template_destroy(gridTemplate);

    return HILAYOUT_OK;
}
