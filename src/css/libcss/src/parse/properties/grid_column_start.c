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

css_error css__parse_grid_column_start(css_language *c,
		const parserutils_vector *vector, int *ctx,
		css_style *result)
{
	int orig_ctx = *ctx;
	css_error error;
	const css_token *token;
	bool match;
    css_fixed length = 0;
    uint32_t unit = 0;

#if 0
    while ((token = parserutils_vector_iterate(vector, ctx)) != NULL) {
        if (token->idata != NULL) {
            fprintf(stderr, "..................................type=%d|idata=%s|grid_template_columns=%s\n", token->type, lwc_string_data(token->idata), lwc_string_data(c->strings[GRID_TEMPLATE_COLUMNS]));
        }
    }
#endif
#if 0

	token = parserutils_vector_iterate(vector, ctx);
	if (token == NULL) {
		*ctx = orig_ctx;
		return CSS_INVALID;
	}

    fprintf(stderr, "..................................%s:%d|type=%d|idata=%s|token=%p\n", __FILE__, __LINE__, token->type, lwc_string_data(token->idata), token);
    *ctx = orig_ctx;
    error = css__parse_unit_specifier(c, vector, ctx, UNIT_PX, &length, &unit);
    if (error != CSS_OK) {
        *ctx = orig_ctx;
        return error;
    }

    error = css__stylesheet_style_appendOPV(result, CSS_PROP_GRID_TEMPLATE_COLUMNS, 0, WIDTH_SET);
    if (error != CSS_OK)
        *ctx = orig_ctx;

    error = css__stylesheet_style_vappend(result, 2, length, unit);
    if (error != CSS_OK) {
        *ctx = orig_ctx;
        return error;
    }
	return error;
#else
    return CSS_INVALID;
#endif
}
