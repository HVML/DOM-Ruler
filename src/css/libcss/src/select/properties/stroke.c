/*
 * Copyright (C) 2021 Beijing FMSoft Technologies Co., Ltd.
 */

#include "bytecode/bytecode.h"
#include "bytecode/opcodes.h"
#include "select/propset.h"
#include "select/propget.h"
#include "utils/utils.h"

#include "select/properties/properties.h"
#include "select/properties/helpers.h"

css_error css__cascade_stroke(uint32_t opv, css_style *style,
		css_select_state *state)
{
    uint16_t value = CSS_STROKE_INHERIT;
    lwc_string *uri = NULL;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case STROKE_NONE:
            value = CSS_STROKE_NONE;
            break;
        case STROKE_CURRENT_COLOR:
            value = CSS_STROKE_CURRENT_COLOR;
            break;
        case STROKE_URI:
            value = CSS_STROKE_URI;
            css__stylesheet_string_get(style->sheet, *((css_code_t *) style->bytecode), &uri);
            advance_bytecode(style, sizeof(css_code_t));
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv),
            isImportant(opv), state, isInherit(opv))) {
        return set_stroke(state->computed, value, uri);
    }

    return CSS_OK;
}

css_error css__set_stroke_from_hint(const css_hint *hint,
		css_computed_style *style)
{
	css_error error;

	error = set_stroke(style, hint->status, hint->data.string);

	if (hint->data.string != NULL)
		lwc_string_unref(hint->data.string);

	return error;
}

css_error css__initial_stroke(css_select_state *state)
{
	return set_stroke(state->computed, CSS_STROKE_NONE, NULL);
}

css_error css__compose_stroke(const css_computed_style *parent,
		const css_computed_style *child,
		css_computed_style *result)
{
	lwc_string *url;
	uint8_t type = get_stroke(child, &url);

	if (type == CSS_STROKE_INHERIT) {
		type = get_stroke(parent, &url);
	}

	return set_stroke(result, type, url);
}

