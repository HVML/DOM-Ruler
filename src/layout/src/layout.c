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

typedef uint8_t (*css_len_func)(const css_computed_style *style, css_fixed *length, css_unit *unit);
typedef uint8_t (*css_border_style_func)(const css_computed_style *style);
typedef uint8_t (*css_border_color_func)(const css_computed_style *style, css_color *color);

/** Array of per-side access functions for computed style margins. */
static const css_len_func margin_funcs[4] = {
	css_computed_margin_top,
	css_computed_margin_right,
	css_computed_margin_bottom,
	css_computed_margin_left,
};

/** Array of per-side access functions for computed style paddings. */
static const css_len_func padding_funcs[4] = {
	css_computed_padding_top,
	css_computed_padding_right,
	css_computed_padding_bottom,
	css_computed_padding_left,
};

/** Array of per-side access functions for computed style border_widths. */
static const css_len_func border_width_funcs[4] = {
	css_computed_border_top_width,
	css_computed_border_right_width,
	css_computed_border_bottom_width,
	css_computed_border_left_width,
};

/** Array of per-side access functions for computed style border styles. */
static const css_border_style_func border_style_funcs[4] = {
	css_computed_border_top_style,
	css_computed_border_right_style,
	css_computed_border_bottom_style,
	css_computed_border_left_style,
};

/** Array of per-side access functions for computed style border colors. */
static const css_border_color_func border_color_funcs[4] = {
	css_computed_border_top_color,
	css_computed_border_right_color,
	css_computed_border_bottom_color,
	css_computed_border_left_color,
};


int _hilayout_select_child_style(const css_media* media, css_select_ctx* select_ctx, HLDomElementNode* node)
{
    int ret = _hilayout_select_node_style(media, select_ctx, node);
    if (ret != HILAYOUT_OK)
    {
        return ret;
    }
    HLDomElementNode* child = node->first_child;
    while(child)
    {
        ret = _hilayout_select_child_style(media, select_ctx, child);
        if (ret != HILAYOUT_OK)
        {
            return ret;
        }
        child = child->next;
    }
    return HILAYOUT_OK;
}


void _hl_calculate_mbp_width(const HLContext *len_ctx,
		    const css_computed_style *style,
		    unsigned int side,
		    bool margin,
		    bool border,
		    bool padding,
		    int *fixed,
		    float *frac
            )
{
	css_fixed value = 0;
	css_unit unit = CSS_UNIT_PX;

	assert(style);

	/* margin */
	if (margin) {
		enum css_margin_e type;

		type = margin_funcs[side](style, &value, &unit);
		if (type == CSS_MARGIN_SET) {
			if (unit == CSS_UNIT_PCT) {
				*frac += FIXTOINT(FDIV(value, F_100));
			} else {
				*fixed += FIXTOINT(_hl_css_len2px(len_ctx,
						value, unit, style));
			}
		}
	}

	/* border */
	if (border) {
		if (border_style_funcs[side](style) !=
				CSS_BORDER_STYLE_NONE) {
			border_width_funcs[side](style, &value, &unit);

			*fixed += FIXTOINT(_hl_css_len2px(len_ctx,
					value, unit, style));
		}
	}

	/* padding */
	if (padding) {
		padding_funcs[side](style, &value, &unit);
		if (unit == CSS_UNIT_PCT) {
			*frac += FIXTOINT(FDIV(value, F_100));
		} else {
			*fixed += FIXTOINT(_hl_css_len2px(len_ctx,
					value, unit, style));
		}
	}
}

void _hl_handle_box_sizing(
		const HLContext *len_ctx,
		HLDomElementNode *node,
		int available_width,
		bool setwidth,
		int *dimension)
{
	enum css_box_sizing_e bs;

	assert(node && node->computed_style);

	bs = css_computed_box_sizing(node->computed_style);

	if (bs == CSS_BOX_SIZING_BORDER_BOX) {
		int orig = *dimension;
		int fixed = 0;
		float frac = 0;

		_hl_calculate_mbp_width(len_ctx, node->computed_style,
				setwidth ? HL_LEFT : HL_TOP,
				false, true, true, &fixed, &frac);
		_hl_calculate_mbp_width(len_ctx, node->computed_style,
				setwidth ? HL_RIGHT : HL_BOTTOM,
				false, true, true, &fixed, &frac);
		orig -= frac * available_width + fixed;
		*dimension = orig > 0 ? orig : 0;
	}
}


void _hl_find_dimensions(const HLContext *len_ctx,
		       int available_width,
		       int viewport_height,
		       HLDomElementNode *box,
		       const css_computed_style *style,
		       int *width,
		       int *height,
		       int *max_width,
		       int *min_width,
		       int *max_height,
		       int *min_height
		       )
{
	HLDomElementNode* containing_block = NULL;
	unsigned int i;

	if (width) {
		enum css_width_e wtype;
		css_fixed value = 0;
		css_unit unit = CSS_UNIT_PX;

		wtype = css_computed_width(style, &value, &unit);

		if (wtype == CSS_WIDTH_SET) {
			if (unit == CSS_UNIT_PCT) {
				*width = HL_FPCT_OF_INT_TOINT(
						value, available_width);
			} else {
				*width = FIXTOINT(_hl_css_len2px(len_ctx,
						value, unit, style));
			}
		} else {
			*width = HL_AUTO;
		}

		if (*width != HL_AUTO) {
			_hl_handle_box_sizing(len_ctx, box, available_width,
					true, width);
		}
	}

	if (height) {
		enum css_height_e htype;
		css_fixed value = 0;
		css_unit unit = CSS_UNIT_PX;

		htype = css_computed_height(style, &value, &unit);

		if (htype == CSS_HEIGHT_SET) {
			if (unit == CSS_UNIT_PCT) {
				enum css_height_e cbhtype;

				if (box->parent && box->parent->layout_type !=
						LAYOUT_INLINE_CONTAINER) {
					/* Box is a block level element */
					containing_block = box->parent;
				} else if (box->parent && box->parent->layout_type ==
						LAYOUT_INLINE_CONTAINER) {
					/* Box is an inline block */
					assert(box->parent->parent);
					containing_block = box->parent->parent;
				}

				if (containing_block) {
					css_fixed f = 0;
					css_unit u = CSS_UNIT_PX;

					cbhtype = css_computed_height(
							containing_block->computed_style,
							&f, &u);
				}

				if (containing_block &&
					containing_block->box_values.h != HL_AUTO &&
					(css_computed_position(box->computed_style) ==
							CSS_POSITION_ABSOLUTE ||
						cbhtype == CSS_HEIGHT_SET)) {
					/* Box is absolutely positioned or its
					 * containing block has a valid
					 * specified height.
					 * (CSS 2.1 Section 10.5) */
					*height = HL_FPCT_OF_INT_TOINT(value,
						containing_block->box_values.h);
				} else if ((!box->parent ||
						!box->parent->parent) &&
						viewport_height >= 0) {
					/* If root element or it's child
					 * (HTML or BODY) */
					*height = HL_FPCT_OF_INT_TOINT(value,
							viewport_height);
				} else {
					/* precentage height not permissible
					 * treat height as auto */
					*height = HL_AUTO;
				}
			} else {
				*height = FIXTOINT(_hl_css_len2px(len_ctx,
						value, unit, style));
			}
		} else {
			*height = HL_AUTO;
		}

		if (*height != HL_AUTO) {
			_hl_handle_box_sizing(len_ctx, box, available_width,
					false, height);
		}
	}

	if (max_width) {
		enum css_max_width_e type;
		css_fixed value = 0;
		css_unit unit = CSS_UNIT_PX;

		type = css_computed_max_width(style, &value, &unit);

		if (type == CSS_MAX_WIDTH_SET) {
			if (unit == CSS_UNIT_PCT) {
				*max_width = HL_FPCT_OF_INT_TOINT(value,
						available_width);
			} else {
				*max_width = FIXTOINT(_hl_css_len2px(len_ctx,
						value, unit, style));
			}
		} else {
			/* Inadmissible */
			*max_width = -1;
		}

		if (*max_width != -1) {
			_hl_handle_box_sizing(len_ctx, box, available_width,
					true, max_width);
		}
	}

	if (min_width) {
		enum css_min_width_e type;
		css_fixed value = 0;
		css_unit unit = CSS_UNIT_PX;

		type = _hl_computed_min_width(style, &value, &unit);

		if (type == CSS_MIN_WIDTH_SET) {
			if (unit == CSS_UNIT_PCT) {
				*min_width = HL_FPCT_OF_INT_TOINT(value,
						available_width);
			} else {
				*min_width = FIXTOINT(_hl_css_len2px(len_ctx,
						value, unit, style));
			}
		} else {
			/* Inadmissible */
			*min_width = 0;
		}

		if (*min_width != 0) {
			_hl_handle_box_sizing(len_ctx, box, available_width,
					true, min_width);
		}
	}

	if (max_height) {
		enum css_max_height_e type;
		css_fixed value = 0;
		css_unit unit = CSS_UNIT_PX;

		type = css_computed_max_height(style, &value, &unit);

		if (type == CSS_MAX_HEIGHT_SET) {
			if (unit == CSS_UNIT_PCT) {
				/* TODO: handle percentage */
				*max_height = -1;
			} else {
				*max_height = FIXTOINT(_hl_css_len2px(len_ctx,
						value, unit, style));
			}
		} else {
			/* Inadmissible */
			*max_height = -1;
		}
	}

	if (min_height) {
		enum css_min_height_e type;
		css_fixed value = 0;
		css_unit unit = CSS_UNIT_PX;

		type = _hl_computed_min_height(style, &value, &unit);

		if (type == CSS_MIN_HEIGHT_SET) {
			if (unit == CSS_UNIT_PCT) {
				/* TODO: handle percentage */
				*min_height = 0;
			} else {
				*min_height = FIXTOINT(_hl_css_len2px(len_ctx,
						value, unit, style));
			}
		} else {
			/* Inadmissible */
			*min_height = 0;
		}
	}
}

int _hl_solve_width(HLDomElementNode* box,
		   int available_width,
		   int width,
		   int lm,
		   int rm,
		   int max_width,
		   int min_width)
{
	bool auto_width = false;

	/* Increase specified left/right margins */
	if (box->margin[HL_LEFT] != HL_AUTO && box->margin[HL_LEFT] < lm &&
			box->margin[HL_LEFT] >= 0)
		box->margin[HL_LEFT] = lm;
	if (box->margin[HL_RIGHT] != HL_AUTO && box->margin[HL_RIGHT] < rm &&
			box->margin[HL_RIGHT] >= 0)
		box->margin[HL_RIGHT] = rm;

	/* Find width */
	if (width == HL_AUTO) {
		int margin_left = box->margin[HL_LEFT];
		int margin_right = box->margin[HL_RIGHT];

		if (margin_left == HL_AUTO) {
			margin_left = lm;
		}
		if (margin_right == HL_AUTO) {
			margin_right = rm;
		}

		width = available_width -
				(margin_left + box->border[HL_LEFT] +
				box->padding[HL_LEFT] + box->padding[HL_RIGHT] +
				box->border[HL_RIGHT] + margin_right);
		width = width < 0 ? 0 : width;
		auto_width = true;
	}

	if (max_width >= 0 && width > max_width) {
		/* max-width is admissable and width exceeds max-width */
		width = max_width;
		auto_width = false;
	}

	if (min_width > 0 && width < min_width) {
		/* min-width is admissable and width is less than max-width */
		width = min_width;
		auto_width = false;
	}

	/* Width was auto, and unconstrained by min/max width, so we're done */
	if (auto_width) {
		/* any other 'auto' become 0 or the minimum required values */
		if (box->margin[HL_LEFT] == HL_AUTO) {
			box->margin[HL_LEFT] = lm;
		}
		if (box->margin[HL_RIGHT] == HL_AUTO) {
			box->margin[HL_RIGHT] = rm;
		}
		return width;
	}

	/* Width was not auto, or was constrained by min/max width
	 * Need to compute left/right margins */

	/* HTML alignment (only applies to over-constrained boxes) */
	if (box->margin[HL_LEFT] != HL_AUTO && box->margin[HL_RIGHT] != HL_AUTO &&
			box->parent != NULL && box->parent->computed_style != NULL) {
		switch (css_computed_text_align(box->parent->computed_style)) {
		case CSS_TEXT_ALIGN_LIBCSS_RIGHT:
			box->margin[HL_LEFT] = HL_AUTO;
			box->margin[HL_RIGHT] = 0;
			break;
		case CSS_TEXT_ALIGN_LIBCSS_CENTER:
			box->margin[HL_LEFT] = box->margin[HL_RIGHT] = HL_AUTO;
			break;
		case CSS_TEXT_ALIGN_LIBCSS_LEFT:
			box->margin[HL_LEFT] = 0;
			box->margin[HL_RIGHT] = HL_AUTO;
			break;
		default:
			/* Leave it alone; no HTML alignment */
			break;
		}
	}

	if (box->margin[HL_LEFT] == HL_AUTO && box->margin[HL_RIGHT] == HL_AUTO) {
		/* make the margins equal, centering the element */
		box->margin[HL_LEFT] = box->margin[HL_RIGHT] =
				(available_width - lm - rm -
				(box->border[HL_LEFT] + box->padding[HL_LEFT] +
				width + box->padding[HL_RIGHT] +
				box->border[HL_RIGHT])) / 2;

		if (box->margin[HL_LEFT] < 0) {
			box->margin[HL_RIGHT] += box->margin[HL_LEFT];
			box->margin[HL_LEFT] = 0;
		}

		box->margin[HL_LEFT] += lm;

	} else if (box->margin[HL_LEFT] == HL_AUTO) {
		box->margin[HL_LEFT] = available_width - lm -
				(box->border[HL_LEFT] + box->padding[HL_LEFT] +
				width + box->padding[HL_RIGHT] +
				box->border[HL_RIGHT] + box->margin[HL_RIGHT]);
		box->margin[HL_LEFT] = box->margin[HL_LEFT] < lm
				? lm : box->margin[HL_LEFT];
	} else {
		/* margin-right auto or "over-constrained" */
		box->margin[HL_RIGHT] = available_width - rm -
				(box->margin[HL_LEFT] + box->border[HL_LEFT] +
				 box->padding[HL_LEFT] + width +
				 box->padding[HL_RIGHT] +
				 box->border[HL_RIGHT]);
	}

	return width;
}

int _hl_block_find_dimensions(HLContext* ctx,
        HLDomElementNode *node,
        int container_width,
        int container_height,
        int lm,
        int rm
        )
{
    int width = 0;
    int max_width = 0;
    int min_width = 0;
    int height = 0;
    int max_height = 0;
    int min_height = 0;

    _hl_find_dimensions(ctx,
            container_width,
            container_height,
            node,
            node->computed_style,
            &width,
            &height,
            &max_width,
            &min_width,
            &max_height,
            &min_height);
    int sw = _hl_solve_width(node, container_width, width, 0, 0, max_width, min_width);
    int sh = height;
    HL_LOGD("block node dimension|tag=%s|id=%s|nw=%d|max_width=%d|min_width=%d|nh=%d|max_height=%d|min_height=%d|sw=%d|sh=%d\n",
            node->tag, node->id,
            width, max_width, min_width,
            height, max_height, min_height,
            sw, sh
           );

    node->box_values.w = sw;
    node->box_values.h = sh;
}

void _hl_computed_offsets(const HLContext* len_ctx,
		       HLDomElementNode* box,
		       HLDomElementNode* containing_block,
		       int* top,
		       int* right,
		       int* bottom,
		       int* left)
{
	uint32_t type;
	css_fixed value = 0;
	css_unit unit = CSS_UNIT_PX;

	assert(containing_block->box_values.w != UNKNOWN_WIDTH &&
			containing_block->box_values.w != HL_AUTO &&
			containing_block->box_values.h != HL_AUTO);

	/* left */
	type = css_computed_left(box->computed_style, &value, &unit);
	if (type == CSS_LEFT_SET) {
		if (unit == CSS_UNIT_PCT) {
			*left = HL_FPCT_OF_INT_TOINT(value,
					containing_block->box_values.w);
		} else {
			*left = FIXTOINT(_hl_css_len2px(len_ctx,
					value, unit, box->computed_style));
		}
	} else {
		*left = HL_AUTO;
	}

	/* right */
	type = css_computed_right(box->computed_style, &value, &unit);
	if (type == CSS_RIGHT_SET) {
		if (unit == CSS_UNIT_PCT) {
			*right = HL_FPCT_OF_INT_TOINT(value,
					containing_block->box_values.w);
		} else {
			*right = FIXTOINT(_hl_css_len2px(len_ctx,
					value, unit, box->computed_style));
		}
	} else {
		*right = HL_AUTO;
	}

	/* top */
	type = css_computed_top(box->computed_style, &value, &unit);
	if (type == CSS_TOP_SET) {
		if (unit == CSS_UNIT_PCT) {
			*top = HL_FPCT_OF_INT_TOINT(value,
					containing_block->box_values.h);
		} else {
			*top = FIXTOINT(_hl_css_len2px(len_ctx,
					value, unit, box->computed_style));
		}
	} else {
		*top = HL_AUTO;
	}

	/* bottom */
	type = css_computed_bottom(box->computed_style, &value, &unit);
	if (type == CSS_BOTTOM_SET) {
		if (unit == CSS_UNIT_PCT) {
			*bottom = HL_FPCT_OF_INT_TOINT(value,
					containing_block->box_values.h);
		} else {
			*bottom = FIXTOINT(_hl_css_len2px(len_ctx,
					value, unit, box->computed_style));
		}
	} else {
		*bottom = HL_AUTO;
	}
}

int _hilayout_find_background(HLDomElementNode* node)
{
    css_color color;
    css_computed_background_color(node->computed_style, &color);
    node->background_values.color = color;
    return HILAYOUT_OK;
}

int _hilayout_find_font(HLContext* ctx, HLDomElementNode* node)
{
    lwc_string **families;
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;

    uint8_t val = css_computed_font_family(node->computed_style, &families);
    if (val == CSS_FONT_FAMILY_INHERIT)
    {
        HL_LOGD("layout node|tag=%s|id=%s|font inherit\n", node->tag, node->id);
        if (node->parent && node->parent->text_values.family)
        {
            node->text_values.family = strdup(node->parent->text_values.family);
        }
    }
    else
    {
        char* buf[1024] = {0};
        int index = 0;
        int len = 0;
        if (families != NULL) {
            while (*families != NULL) {
                buf[index] = strdup(lwc_string_data(*families));
                len += strlen(buf[index]);
                index++;
                families++;
            }
        }

        switch (val) {
            case CSS_FONT_FAMILY_SERIF:
                buf[index] = strdup("serif");
                len += strlen(buf[index]);
                index++;
                break;
            case CSS_FONT_FAMILY_SANS_SERIF:
                buf[index] = strdup("sans-serif");
                len += strlen(buf[index]);
                index++;
                break;
            case CSS_FONT_FAMILY_CURSIVE:
                buf[index] = strdup("cursive");
                len += strlen(buf[index]);
                index++;
                break;
            case CSS_FONT_FAMILY_FANTASY:
                buf[index] = strdup("fantasy");
                len += strlen(buf[index]);
                index++;
                break;
            case CSS_FONT_FAMILY_MONOSPACE:
                buf[index] = strdup("monospace");
                len += strlen(buf[index]);
                index++;
                break;
        }

        char* result = (char*)malloc(len + 1);
        memset(result, 0, len+1);
        for (int i=0; i<index; i++)
        {
            strcat(result, buf[i]);
            strcat(result, ",");
            free(buf[i]);
        }
        result[strlen(result) - 1 ] = 0;
        node->text_values.family = result;
    }

    css_computed_font_size(node->computed_style, &length, &unit);
    int text_height = _hl_css_len2px(ctx, length, unit, node->computed_style);
    node->text_values.size = FIXTOINT(text_height * 3 / 4);

    css_color color;
    val = css_computed_color(node->computed_style, &color);
    if (val == CSS_COLOR_INHERIT) {
        if (node->parent)
        {
            node->text_values.color = node->parent->text_values.color;
        }
    } else if (val == CSS_COLOR_COLOR) {
        node->text_values.color = color;
    }

    val = css_computed_font_weight(node->computed_style);
	switch (val) {
	case CSS_FONT_WEIGHT_100:
        node->text_values.weight = HLFONT_WEIGHT_THIN;
		break;
	case CSS_FONT_WEIGHT_200:
        node->text_values.weight = HLFONT_WEIGHT_EXTRA_LIGHT;
		break;
	case CSS_FONT_WEIGHT_300:
        node->text_values.weight = HLFONT_WEIGHT_LIGHT;
		break;
	case CSS_FONT_WEIGHT_400:
	case CSS_FONT_WEIGHT_NORMAL:
	default:
        node->text_values.weight = HLFONT_WEIGHT_NORMAL;
		break;
	case CSS_FONT_WEIGHT_500:
        node->text_values.weight = HLFONT_WEIGHT_MEDIUM;
		break;
	case CSS_FONT_WEIGHT_600:
        node->text_values.weight = HLFONT_WEIGHT_DEMIBOLD;
		break;
	case CSS_FONT_WEIGHT_700:
	case CSS_FONT_WEIGHT_BOLD:
        node->text_values.weight = HLFONT_WEIGHT_BOLD;
		break;
	case CSS_FONT_WEIGHT_800:
        node->text_values.weight = HLFONT_WEIGHT_EXTRA_BOLD;
		break;
	case CSS_FONT_WEIGHT_900:
        node->text_values.weight = HLFONT_WEIGHT_BLACK;
		break;
	}
}

int _hilayout_layout_node(HLContext* ctx, HLDomElementNode *node, int x, int y, int container_width, int container_height, int level)
{
    if (node == NULL)
    {
        HL_LOGW("layout node|level=%d|node=%p\n", level, node);
        return HILAYOUT_OK;
    }

    HL_LOGD("layout node|level=%d|tag=%s|id=%s|in x=%d|y=%d|container_width=%d|container_height=%d\n",
            level, node->tag, node->id, x, y, container_width, container_height);
    node->box_values.x = x;
    node->box_values.y = y;

    _hi_computed_z_index(node);
    _hilayout_find_background(node);
    _hilayout_find_font(ctx, node);
    if (_hl_node_is_root(node))
    {
        node->box_values.w = container_width;
        node->box_values.h = container_height;
    }
    else if (css_computed_position(node->computed_style) == CSS_POSITION_FIXED)
    {
        HLDomElementNode* op = node->parent;
        node->parent = ctx->root;
        _hl_block_find_dimensions(ctx, node, ctx->root->box_values.w, ctx->root->box_values.h, 0, 0);
        node->parent = op;
    }
    else {
        switch (node->layout_type)
        {
            case LAYOUT_BLOCK:
                _hl_block_find_dimensions(ctx, node, container_width, container_height, 0, 0);
                break;

            case LAYOUT_INLINE_BLOCK:
                _hl_block_find_dimensions(ctx, node, container_width, container_height, 0, 0);
                break;

            case LAYOUT_GRID:
                _hl_block_find_dimensions(ctx, node, container_width, container_height, 0, 0);
                break;

            case LAYOUT_INLINE_GRID:
                _hl_block_find_dimensions(ctx, node, container_width, container_height, 0, 0);
                break;

            default:
                _hl_block_find_dimensions(ctx, node, container_width, container_height, 0, 0);
                break;
        }
    }

    HLDomElementNode* child = node->first_child;
    if (child == NULL)
    {
        HL_LOGW("layout node|level=%d|tag=%s|id=%s|(%f, %f, %f, %f)"
                "|background=0x%08X|text.family=%s|text.color=0x%08X|text.weight=%d|text.size=%d\n",
                level, node->tag, node->id,
                node->box_values.x, node->box_values.y, node->box_values.w, node->box_values.h,
                node->background_values.color,
                node->text_values.family, node->text_values.color, node->text_values.weight,
                node->text_values.size
               );
        return HILAYOUT_OK;
    }

    switch(node->layout_type)
    {
        case LAYOUT_GRID:
        case LAYOUT_INLINE_GRID:
            {
                HL_LOGW("layout node|level=%d|tag=%s|id=%s|(%f, %f, %f, %f)|background=0x%08X|text.family=%s|text.color=0x%08X|text.weight=%d|text.size=%d\n",
                        level, node->tag, node->id,
                        node->box_values.x, node->box_values.y, node->box_values.w, node->box_values.h,
                        node->background_values.color,
                        node->text_values.family, node->text_values.color, node->text_values.weight,
                        node->text_values.size
                       );
                return _hl_layout_child_node_grid(ctx, node, level);
            }
    }

    int cx = x;
    int cy = y;
    int cw = node->box_values.w;
    int ch = node->box_values.h;
    int cl = level + 1;

    int top = 0;
    int right = 0;
    int bottom = 0;
    int left = 0;
    int line_height = 0;
    int prev_width = 0;
    while(child)
    {
        if (css_computed_position(child->computed_style) == CSS_POSITION_FIXED)
        {
            int x = ctx->root->box_values.x;
            int y = ctx->root->box_values.y;
            int w = ctx->root->box_values.w;
            int h = ctx->root->box_values.h;

            _hl_computed_offsets(ctx, child, ctx->root, &top, &right, &bottom, &left);
            if (left == HL_AUTO)
                left = 0;

            if (top == HL_AUTO)
                top = 0;
            _hilayout_layout_node(ctx, child, x + left, y + top, w, h, cl);
            line_height = 0;
            child = child->next;
            continue;
        }

        switch (child->layout_type)
        {
            case LAYOUT_BLOCK:
            case LAYOUT_GRID:
                cx = x;
                if (css_computed_position(child->computed_style) == CSS_POSITION_RELATIVE)
                {
                    _hl_computed_offsets(ctx, child, node, &top, &right, &bottom, &left);
                }
                cy = cy + line_height;
                _hilayout_layout_node(ctx, child, cx + left, cy + top, cw, ch, cl);
                line_height = 0;
                break;

            case LAYOUT_INLINE_BLOCK:
            case LAYOUT_INLINE_GRID:
                if (css_computed_position(child->computed_style) == CSS_POSITION_RELATIVE)
                {
                    _hl_computed_offsets(ctx, child, node, &top, &right, &bottom, &left);
                }
                _hl_block_find_dimensions(ctx, child, cw, ch, 0, 0);
                if (cx + prev_width + child->box_values.w + left > cw)
                {
                    cx = x;
                    cy = cy + line_height;
                }
                else
                {
                    cx = cx + prev_width;
                }
                _hilayout_layout_node(ctx, child, cx + left, cy + top, cw, ch, cl);
                prev_width = child->box_values.w;
                break;

            default:
                cx = x;
                if (css_computed_position(child->computed_style) == CSS_POSITION_RELATIVE)
                {
                    _hl_computed_offsets(ctx, child, node, &top, &right, &bottom, &left);
                }
                cy = cy + line_height;
                _hilayout_layout_node(ctx, child, cx + left, cy + top, cw, ch, cl);
                line_height = 0;
                break;
        }
        line_height = line_height < child->box_values.h ? child->box_values.h : line_height;
        child = child->next;
    }

    HL_LOGW("layout node|level=%d|tag=%s|id=%s|"
            "(%f, %f, %f, %f)|background=0x%08X|text.family=%s|text.color=0x%08X|text.weight=%d|text.size=%d\n",
            level, node->tag, node->id,
            node->box_values.x, node->box_values.y, node->box_values.w, node->box_values.h,
            node->background_values.color,
            node->text_values.family, node->text_values.color, node->text_values.weight,
            node->text_values.size
            );
    return HILAYOUT_OK;
}

int hilayout_do_layout(HLMedia* media, HLCSS* css, HLDomElementNode *root)
{
    if (media == NULL || root == NULL || css == NULL || css->sheet == NULL)
    {
        HL_LOGW("%s|media=%p|root=%p|css=%p|style_sheet=%p|param error\n", __func__, media, root, css, css->sheet);
        return HILAYOUT_NOMEM;
    }

	HLContext context = {
		.media = media,
		.css = css,
        .root = root,
	};
    _hl_set_media_dpi(&context, media->dpi);
    _hl_set_baseline_pixel_density(&context, media->density);

	css_media m;
	m.type = CSS_MEDIA_SCREEN;
    m.width  = _hl_css_pixels_physical_to_css(&context, INTTOFIX(media->width));
    m.height = _hl_css_pixels_physical_to_css(&context, INTTOFIX(media->height));
    context.vw = m.width;
    context.vh = m.height;

    // create css select context
    css_select_ctx* select_ctx = _hilayout_css_select_ctx_create(css);

    int ret = _hilayout_select_child_style(&m, select_ctx, root);
    if (ret != HILAYOUT_OK)
    {
        HL_LOGW("%s|select child style failed.|code=%d\n", __func__, ret);
        _hilayout_css_select_ctx_destroy(select_ctx);
        return ret;
    }
    context.root_style = root->computed_style;

    _hilayout_layout_node(&context, root, 0, 0, media->width, media->height, 0);
    _hilayout_css_select_ctx_destroy(select_ctx);
    return ret;
}

