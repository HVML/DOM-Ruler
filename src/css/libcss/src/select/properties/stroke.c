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
	return CSS_OK;
}

css_error css__set_stroke_from_hint(const css_hint *hint,
		css_computed_style *style)
{
	return set_stroke(style, hint->status, hint->data.color);
}

css_error css__initial_stroke(css_select_state *state)
{
	css_hint hint;
	css_error error;

	error = state->handler->ua_default_for_property(state->pw,
			CSS_PROP_COLOR, &hint);
	if (error != CSS_OK)
		return error;

	return css__set_stroke_from_hint(&hint, state->computed);
}

css_error css__compose_stroke(const css_computed_style *parent,
		const css_computed_style *child,
		css_computed_style *result)
{
	css_color color;
	uint8_t type = get_stroke(child, &color);

	if (type == CSS_STROKE_INHERIT) {
		type = get_stroke(parent, &color);
	}

	return set_stroke(result, type, color);
}

