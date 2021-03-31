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

#include <assert.h>
#include <string.h>

#include "bytecode/bytecode.h"
#include "bytecode/opcodes.h"
#include "parse/properties/properties.h"
#include "parse/properties/utils.h"

css_error css__parse_grid_template_columns(css_language *c,
        const parserutils_vector *vector, int *ctx,
        css_style *result)
{
    int orig_ctx = *ctx;
    int last_ctx = *ctx;
    css_error error;
    const css_token *token;
    css_fixed length = 0;
    uint32_t unit = 0;

    while ((token = parserutils_vector_iterate(vector, ctx)) != NULL) {
        if (token->idata != NULL) {
            error = css__parse_unit_specifier(c, vector, &last_ctx, UNIT_PX, &length, &unit);
            if (error != CSS_OK) 
            {
                *ctx = orig_ctx;
                return error;
            }
            error = css__stylesheet_style_appendOPV(result, CSS_PROP_GRID_TEMPLATE_COLUMNS, 0, GRID_TEMPLATE_COLUMNS_SET);
            if (error != CSS_OK)
            {
                *ctx = orig_ctx;
                return error;
            }

            error = css__stylesheet_style_vappend(result, 2, length, unit);
            if (error != CSS_OK) {
                *ctx = orig_ctx;
                return error;
            }
            fprintf(stderr, "..................................type=%d|idata=%s|grid_template_columns=%s|ctx=%d|last_ctx=%d|length=%d|unit=%d\n", 
                    token->type, lwc_string_data(token->idata), lwc_string_data(c->strings[GRID_TEMPLATE_COLUMNS]), *ctx, last_ctx, length, unit);
            last_ctx = *ctx;
        }
    }
    error = css__stylesheet_style_append(result, GRID_TEMPLATE_COLUMNS_END);
    return error;
}
