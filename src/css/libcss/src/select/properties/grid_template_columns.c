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

css_error css__cascade_grid_template_columns(uint32_t opv, css_style *style,
		css_select_state *state)
{
	uint16_t value = CSS_GRID_TEMPLATE_COLUMNS_INHERIT;
    css_fixed values[1024];
    css_unit units[1024];
    int32_t n_values = 0;

    fprintf(stderr, "##################################################%s:%d\n", __FILE__, __LINE__);
	if (isInherit(opv) == false) {
    fprintf(stderr, "##################################################%s:%d\n", __FILE__, __LINE__);
		uint32_t v = getValue(opv);

		while (v != GRID_TEMPLATE_COLUMNS_END) {
    fprintf(stderr, "##################################################%s:%d\n", __FILE__, __LINE__);
            css_fixed length;
            css_unit unit;

            switch (v) {
                case GRID_TEMPLATE_COLUMNS_SET:
                    value = CSS_GRID_TEMPLATE_COLUMNS_SET;
                    length = *((css_fixed *) style->bytecode);
                    advance_bytecode(style, sizeof(length));
                    unit = *((uint32_t *) style->bytecode);
                    advance_bytecode(style, sizeof(unit));
	                unit = css__to_css_unit(unit);
                    fprintf(stderr, ".........................................length=%d|unit=%d\n", length, unit);
                    break;

                default:
                    continue;
            }

            values[n_values] = length;
            units[n_values] = unit;
            n_values++;
		}
	}

	if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
			isInherit(opv))) {
        return set_grid_template_columns(state->computed, value, n_values, values, units);
    }

	return CSS_OK;
}

css_error css__set_grid_template_columns_from_hint(const css_hint *hint,
		css_computed_style *style)
{
    fprintf(stderr, "##################################################%s:%d\n", __FILE__, __LINE__);
    return set_grid_template_columns(style, CSS_GRID_TEMPLATE_COLUMNS_AUTO, 0, NULL, NULL);
}

css_error css__initial_grid_template_columns(css_select_state *state)
{
    fprintf(stderr, "##################################################%s:%d\n", __FILE__, __LINE__);
    return set_grid_template_columns(state->computed, CSS_GRID_TEMPLATE_COLUMNS_AUTO,  0, NULL, NULL);
}

css_error css__compose_grid_template_columns(const css_computed_style *parent,
		const css_computed_style *child,
		css_computed_style *result)
{
    fprintf(stderr, "##################################################%s:%d\n", __FILE__, __LINE__);
	int32_t index = 0;
    int32_t size = 0;
    css_error error;
    css_fixed* values = NULL;
    css_unit* units = NULL;

    uint8_t type = get_grid_template_columns(child, &size, &values, &units);
	if (type == CSS_GRID_TEMPLATE_COLUMNS_INHERIT) {
        if (values != NULL)
        {
            free(values);
        }
        if (units != NULL)
        {
            free(units);
        }
        type = get_grid_template_columns(parent, &size, &values, &units);
	}

	error = set_grid_template_columns(result, type, size, values, units);
    if (values != NULL)
    {
        free(values);
    }
    if (units != NULL)
    {
        free(units);
    }
    return error;
}
