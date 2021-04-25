/*
 * 
 * Copyright (C) 2021 Beijing FMSoft Technologies Co., Ltd.
 */

#include <assert.h>
#include <string.h>

#include "bytecode/bytecode.h"
#include "bytecode/opcodes.h"
#include "parse/properties/properties.h"
#include "parse/properties/utils.h"

css_error css__parse_text_shadow_impl(css_language *c,
		const parserutils_vector *vector, int *ctx,
		css_style *result, int np)
{
    int orig_ctx = *ctx;
	css_error error = CSS_INVALID;
	const css_token *token;
	bool match;

    int last_ctx = *ctx;

    css_fixed text_shadow_h;
    uint32_t  text_shadow_h_unit;

    css_fixed text_shadow_v;
    uint32_t  text_shadow_v_unit;

    css_fixed text_shadow_blur;
    uint32_t  text_shadow_blur_unit;

	uint32_t text_shadow_color = 0;
	uint16_t text_shadow_color_value= 0;

    uint8_t text_shadow_type = CSS_TEXT_SHADOW_INHERIT;
    uint8_t try_parse_color = true;

	token = parserutils_vector_iterate(vector, ctx);
	if ((token == NULL) || (token->type != CSS_TOKEN_IDENT) ) {
		*ctx = orig_ctx;
		return CSS_INVALID;
	}

	if (lwc_string_caseless_isequal(token->idata, c->strings[INHERIT], &match) == lwc_error_ok && match) {
		error = css_stylesheet_style_inherit(result, CSS_PROP_TEXT_SHADOW);
	} else if (lwc_string_caseless_isequal(token->idata, c->strings[NONE], &match) == lwc_error_ok && match) {
		error = css__stylesheet_style_appendOPV(result, CSS_PROP_TEXT_SHADOW, 0, TEXT_SHADOW_NONE);
	} else {
        // text_shadow_h
        error = css__parse_unit_specifier(c, vector, ctx, UNIT_PX, &text_shadow_h, &text_shadow_h_unit);
        if (error != CSS_OK) 
        {
            *ctx = orig_ctx;
            return error;
        }

        if (text_shadow_h_unit != UNIT_PX)
        {
            *ctx = orig_ctx;
            return CSS_INVALID;
        }
        text_shadow_type |= TEXT_SHADOW_H;
    }

    // text_shadow_v
	token = parserutils_vector_iterate(vector, ctx);
	if ((token == NULL) || (token->type != CSS_TOKEN_IDENT) ) {
		*ctx = orig_ctx;
		return CSS_INVALID;
	}

    error = css__parse_unit_specifier(c, vector, ctx, UNIT_PX, &text_shadow_v, &text_shadow_v_unit);
    if (error != CSS_OK) 
    {
        *ctx = orig_ctx;
        return error;
    }

    if (text_shadow_v_unit != UNIT_PX)
    {
        *ctx = orig_ctx;
        return CSS_INVALID;
    }
    text_shadow_type |= TEXT_SHADOW_V;

    // text_shadow_blur
    // text_shadow_color
	token = parserutils_vector_iterate(vector, ctx);
    if (token != NULL && token->type == CSS_TOKEN_IDENT)
    {
        error = css__parse_unit_specifier(c, vector, ctx, UNIT_PX, &text_shadow_blur, &text_shadow_blur_unit);
        if (error == CSS_OK) 
        {
            if (text_shadow_blur_unit != UNIT_PX)
            {
                *ctx = orig_ctx;
                return CSS_INVALID;
            }
            text_shadow_type |= TEXT_SHADOW_BLUR;
            
            // for text shadow color
            token = parserutils_vector_iterate(vector, ctx);
            if ((token == NULL) || (token->type != CSS_TOKEN_IDENT) ) {
                *ctx = orig_ctx;
                try_parse_color = false;
            }
        }

        if (try_parse_color)
        {
            error = css__parse_colour_specifier(c, vector, ctx, &text_shadow_color_value, &text_shadow_color);
            if (error != CSS_OK) {
                *ctx = orig_ctx;
                return error;
            }
            if (text_shadow_color_value == COLOR_SET)
            {
                text_shadow_type |= TEXT_SHADOW_COLOR;
            }
        }
    }


    error = css__stylesheet_style_appendOPV(result, CSS_PROP_TEXT_SHADOW, 0, text_shadow_type);
    if (error != CSS_OK)
    {
        *ctx = orig_ctx;
        return error;
    }

    error = css__stylesheet_style_vappend(result, 2, text_shadow_h, text_shadow_h_unit);
    if (error != CSS_OK) {
        *ctx = orig_ctx;
        return error;
    }

    error = css__stylesheet_style_vappend(result, 2, text_shadow_v, text_shadow_v_unit);
    if (error != CSS_OK) {
        *ctx = orig_ctx;
        return error;
    }

    if (text_shadow_type & TEXT_SHADOW_BLUR)
    {
        error = css__stylesheet_style_vappend(result, 2, text_shadow_blur, text_shadow_blur_unit);
        if (error != CSS_OK) {
            *ctx = orig_ctx;
            return error;
        }
    }

    if (text_shadow_type & TEXT_SHADOW_COLOR)
    {
        error = css__stylesheet_style_append(result, text_shadow_color);
        if (error != CSS_OK) {
            *ctx = orig_ctx;
            return error;
        }
    }

	if (error != CSS_OK)
		*ctx = orig_ctx;

	return error;
}

