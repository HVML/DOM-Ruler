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

#include "bytecode/bytecode.h"
#include "bytecode/opcodes.h"
#include "select/propset.h"
#include "select/propget.h"
#include "utils/utils.h"

#include "select/properties/properties.h"
#include "select/properties/helpers.h"

css_error css__cascade_grid_row_end(uint32_t opv, css_style *style,
		css_select_state *state)
{
	uint16_t value = CSS_GRID_ROW_END_INHERIT;
	css_fixed index = 0;

	if (isInherit(opv) == false) {
		switch (getValue(opv)) {
		case GRID_ROW_END_SET:
			value = CSS_GRID_ROW_END_SET;

			index = *((css_fixed *) style->bytecode);
			advance_bytecode(style, sizeof(index));
			break;
		case GRID_ROW_END_AUTO:
			value = CSS_GRID_ROW_END_AUTO;
			break;
		}
	}

	if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
			isInherit(opv))) {
		return set_grid_row_end(state->computed, value, index);
	}

	return CSS_OK;
}

css_error css__set_grid_row_end_from_hint(const css_hint *hint,
		css_computed_style *style)
{
	return set_grid_row_end(style, hint->status, hint->data.integer);
}

css_error css__initial_grid_row_end(css_select_state *state)
{
	return set_grid_row_end(state->computed, CSS_GRID_ROW_END_AUTO, 0);
}

css_error css__compose_grid_row_end(const css_computed_style *parent,
		const css_computed_style *child,
		css_computed_style *result)
{
	int32_t index = 0;
	uint8_t type = get_grid_row_end(child, &index);

	if (type == CSS_GRID_ROW_END_INHERIT) {
		type = get_grid_row_end(parent, &index);
	}

	return set_grid_row_end(result, type, index);
}

