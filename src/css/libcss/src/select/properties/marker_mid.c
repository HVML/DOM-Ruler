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

css_error css__cascade_marker_mid(uint32_t opv, css_style *style,
		css_select_state *state)
{
	return CSS_OK;
}

css_error css__set_marker_mid_from_hint(const css_hint *hint,
		css_computed_style *style)
{
	return CSS_OK;
}

css_error css__initial_marker_mid(css_select_state *state)
{
	return CSS_OK;
}

css_error css__compose_marker_mid(const css_computed_style *parent,
		const css_computed_style *child,
		css_computed_style *result)
{
	return CSS_OK;
}
