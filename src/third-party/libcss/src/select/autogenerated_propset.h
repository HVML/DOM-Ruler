/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 The NetSurf Project
 */

/** Default values are 'initial value', unless the property is inherited,
 *  in which case it is 'inherit'. */

#define ALIGN_CONTENT_INDEX 12
#define ALIGN_CONTENT_SHIFT 8
#define ALIGN_CONTENT_MASK 0x700

static inline css_error set_align_content(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[ALIGN_CONTENT_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~ALIGN_CONTENT_MASK) | (((uint32_t)type & 0x7) <<
			ALIGN_CONTENT_SHIFT);
	
	return CSS_OK;
}
#undef ALIGN_CONTENT_INDEX
#undef ALIGN_CONTENT_SHIFT
#undef ALIGN_CONTENT_MASK

#define ALIGN_ITEMS_INDEX 12
#define ALIGN_ITEMS_SHIFT 11
#define ALIGN_ITEMS_MASK 0x3800

static inline css_error set_align_items(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[ALIGN_ITEMS_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~ALIGN_ITEMS_MASK) | (((uint32_t)type & 0x7) <<
			ALIGN_ITEMS_SHIFT);
	
	return CSS_OK;
}
#undef ALIGN_ITEMS_INDEX
#undef ALIGN_ITEMS_SHIFT
#undef ALIGN_ITEMS_MASK

#define ALIGN_SELF_INDEX 13
#define ALIGN_SELF_SHIFT 29
#define ALIGN_SELF_MASK 0xe0000000

static inline css_error set_align_self(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[ALIGN_SELF_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~ALIGN_SELF_MASK) | (((uint32_t)type & 0x7) <<
			ALIGN_SELF_SHIFT);
	
	return CSS_OK;
}
#undef ALIGN_SELF_INDEX
#undef ALIGN_SELF_SHIFT
#undef ALIGN_SELF_MASK

#define BACKGROUND_ATTACHMENT_INDEX 18
#define BACKGROUND_ATTACHMENT_SHIFT 4
#define BACKGROUND_ATTACHMENT_MASK 0x30

static inline css_error set_background_attachment(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BACKGROUND_ATTACHMENT_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~BACKGROUND_ATTACHMENT_MASK) | (((uint32_t)type & 0x3)
			<< BACKGROUND_ATTACHMENT_SHIFT);
	
	return CSS_OK;
}
#undef BACKGROUND_ATTACHMENT_INDEX
#undef BACKGROUND_ATTACHMENT_SHIFT
#undef BACKGROUND_ATTACHMENT_MASK

#define BACKGROUND_COLOR_INDEX 14
#define BACKGROUND_COLOR_SHIFT 24
#define BACKGROUND_COLOR_MASK 0x3000000

static inline css_error set_background_color(css_computed_style *style, uint8_t
		type, css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BACKGROUND_COLOR_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~BACKGROUND_COLOR_MASK) | (((uint32_t)type & 0x3) <<
			BACKGROUND_COLOR_SHIFT);
	
	style->i.background_color = color;
	
	return CSS_OK;
}
#undef BACKGROUND_COLOR_INDEX
#undef BACKGROUND_COLOR_SHIFT
#undef BACKGROUND_COLOR_MASK

#define BACKGROUND_IMAGE_INDEX 19
#define BACKGROUND_IMAGE_SHIFT 30
#define BACKGROUND_IMAGE_MASK 0x40000000

static inline css_error set_background_image(css_computed_style *style, uint8_t
		type, lwc_string *string)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BACKGROUND_IMAGE_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~BACKGROUND_IMAGE_MASK) | (((uint32_t)type & 0x1) <<
			BACKGROUND_IMAGE_SHIFT);
	
	lwc_string *old_string = style->i.background_image;
	
	if (string != NULL) {
		style->i.background_image = lwc_string_ref(string);
	} else {
		style->i.background_image = NULL;
	}
	
	if (old_string != NULL)
		lwc_string_unref(old_string);
	
	return CSS_OK;
}
#undef BACKGROUND_IMAGE_INDEX
#undef BACKGROUND_IMAGE_SHIFT
#undef BACKGROUND_IMAGE_MASK

#define BACKGROUND_POSITION_INDEX 15
#define BACKGROUND_POSITION_SHIFT 21
#define BACKGROUND_POSITION_MASK 0xffe00000

static inline css_error set_background_position(css_computed_style *style,
		uint8_t type, css_fixed length_a, css_unit unit_a, css_fixed
		length_b, css_unit unit_b)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BACKGROUND_POSITION_INDEX];
	
	/* 11bits: aaaaabbbbbt : unit_a | unit_b | type */
	*bits = (*bits & ~BACKGROUND_POSITION_MASK) | ((((uint32_t)type & 0x1)
			| (unit_b << 1) | (unit_a << 6)) <<
			BACKGROUND_POSITION_SHIFT);
	
	style->i.background_position_a = length_a;
	
	style->i.background_position_b = length_b;
	
	return CSS_OK;
}
#undef BACKGROUND_POSITION_INDEX
#undef BACKGROUND_POSITION_SHIFT
#undef BACKGROUND_POSITION_MASK

#define BACKGROUND_REPEAT_INDEX 12
#define BACKGROUND_REPEAT_SHIFT 2
#define BACKGROUND_REPEAT_MASK 0x1c

static inline css_error set_background_repeat(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BACKGROUND_REPEAT_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~BACKGROUND_REPEAT_MASK) | (((uint32_t)type & 0x7) <<
			BACKGROUND_REPEAT_SHIFT);
	
	return CSS_OK;
}
#undef BACKGROUND_REPEAT_INDEX
#undef BACKGROUND_REPEAT_SHIFT
#undef BACKGROUND_REPEAT_MASK

#define BASELINE_SHIFT_INDEX 17
#define BASELINE_SHIFT_SHIFT 9
#define BASELINE_SHIFT_MASK 0x1e00

static inline css_error set_baseline_shift(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BASELINE_SHIFT_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~BASELINE_SHIFT_MASK) | (((uint32_t)type & 0xf) <<
			BASELINE_SHIFT_SHIFT);
	
	return CSS_OK;
}
#undef BASELINE_SHIFT_INDEX
#undef BASELINE_SHIFT_SHIFT
#undef BASELINE_SHIFT_MASK

#define BORDER_BOTTOM_COLOR_INDEX 18
#define BORDER_BOTTOM_COLOR_SHIFT 6
#define BORDER_BOTTOM_COLOR_MASK 0xc0

static inline css_error set_border_bottom_color(css_computed_style *style,
		uint8_t type, css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_BOTTOM_COLOR_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~BORDER_BOTTOM_COLOR_MASK) | (((uint32_t)type & 0x3)
			<< BORDER_BOTTOM_COLOR_SHIFT);
	
	style->i.border_bottom_color = color;
	
	return CSS_OK;
}
#undef BORDER_BOTTOM_COLOR_INDEX
#undef BORDER_BOTTOM_COLOR_SHIFT
#undef BORDER_BOTTOM_COLOR_MASK

#define BORDER_BOTTOM_LEFT_RADIUS_INDEX 5
#define BORDER_BOTTOM_LEFT_RADIUS_SHIFT 25
#define BORDER_BOTTOM_LEFT_RADIUS_MASK 0xfe000000

static inline css_error set_border_bottom_left_radius(css_computed_style
		*style, uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_BOTTOM_LEFT_RADIUS_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~BORDER_BOTTOM_LEFT_RADIUS_MASK) | ((((uint32_t)type &
			0x3) | (unit << 2)) << BORDER_BOTTOM_LEFT_RADIUS_SHIFT);
	
	style->i.border_bottom_left_radius = length;
	
	return CSS_OK;
}
#undef BORDER_BOTTOM_LEFT_RADIUS_INDEX
#undef BORDER_BOTTOM_LEFT_RADIUS_SHIFT
#undef BORDER_BOTTOM_LEFT_RADIUS_MASK

#define BORDER_BOTTOM_RIGHT_RADIUS_INDEX 6
#define BORDER_BOTTOM_RIGHT_RADIUS_SHIFT 11
#define BORDER_BOTTOM_RIGHT_RADIUS_MASK 0x3f800

static inline css_error set_border_bottom_right_radius(css_computed_style
		*style, uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_BOTTOM_RIGHT_RADIUS_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~BORDER_BOTTOM_RIGHT_RADIUS_MASK) | ((((uint32_t)type
			& 0x3) | (unit << 2)) <<
			BORDER_BOTTOM_RIGHT_RADIUS_SHIFT);
	
	style->i.border_bottom_right_radius = length;
	
	return CSS_OK;
}
#undef BORDER_BOTTOM_RIGHT_RADIUS_INDEX
#undef BORDER_BOTTOM_RIGHT_RADIUS_SHIFT
#undef BORDER_BOTTOM_RIGHT_RADIUS_MASK

#define BORDER_BOTTOM_STYLE_INDEX 17
#define BORDER_BOTTOM_STYLE_SHIFT 5
#define BORDER_BOTTOM_STYLE_MASK 0x1e0

static inline css_error set_border_bottom_style(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_BOTTOM_STYLE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~BORDER_BOTTOM_STYLE_MASK) | (((uint32_t)type & 0xf)
			<< BORDER_BOTTOM_STYLE_SHIFT);
	
	return CSS_OK;
}
#undef BORDER_BOTTOM_STYLE_INDEX
#undef BORDER_BOTTOM_STYLE_SHIFT
#undef BORDER_BOTTOM_STYLE_MASK

#define BORDER_BOTTOM_WIDTH_INDEX 0
#define BORDER_BOTTOM_WIDTH_SHIFT 16
#define BORDER_BOTTOM_WIDTH_MASK 0xff0000

static inline css_error set_border_bottom_width(css_computed_style *style,
		uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_BOTTOM_WIDTH_INDEX];
	
	/* 8bits: uuuuuttt : unit | type */
	*bits = (*bits & ~BORDER_BOTTOM_WIDTH_MASK) | ((((uint32_t)type & 0x7)
			| (unit << 3)) << BORDER_BOTTOM_WIDTH_SHIFT);
	
	style->i.border_bottom_width = length;
	
	return CSS_OK;
}
#undef BORDER_BOTTOM_WIDTH_INDEX
#undef BORDER_BOTTOM_WIDTH_SHIFT
#undef BORDER_BOTTOM_WIDTH_MASK

#define BORDER_COLLAPSE_INDEX 14
#define BORDER_COLLAPSE_SHIFT 20
#define BORDER_COLLAPSE_MASK 0x300000

static inline css_error set_border_collapse(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_COLLAPSE_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~BORDER_COLLAPSE_MASK) | (((uint32_t)type & 0x3) <<
			BORDER_COLLAPSE_SHIFT);
	
	return CSS_OK;
}
#undef BORDER_COLLAPSE_INDEX
#undef BORDER_COLLAPSE_SHIFT
#undef BORDER_COLLAPSE_MASK

#define BORDER_LEFT_COLOR_INDEX 14
#define BORDER_LEFT_COLOR_SHIFT 4
#define BORDER_LEFT_COLOR_MASK 0x30

static inline css_error set_border_left_color(css_computed_style *style,
		uint8_t type, css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_LEFT_COLOR_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~BORDER_LEFT_COLOR_MASK) | (((uint32_t)type & 0x3) <<
			BORDER_LEFT_COLOR_SHIFT);
	
	style->i.border_left_color = color;
	
	return CSS_OK;
}
#undef BORDER_LEFT_COLOR_INDEX
#undef BORDER_LEFT_COLOR_SHIFT
#undef BORDER_LEFT_COLOR_MASK

#define BORDER_LEFT_STYLE_INDEX 10
#define BORDER_LEFT_STYLE_SHIFT 8
#define BORDER_LEFT_STYLE_MASK 0xf00

static inline css_error set_border_left_style(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_LEFT_STYLE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~BORDER_LEFT_STYLE_MASK) | (((uint32_t)type & 0xf) <<
			BORDER_LEFT_STYLE_SHIFT);
	
	return CSS_OK;
}
#undef BORDER_LEFT_STYLE_INDEX
#undef BORDER_LEFT_STYLE_SHIFT
#undef BORDER_LEFT_STYLE_MASK

#define BORDER_LEFT_WIDTH_INDEX 0
#define BORDER_LEFT_WIDTH_SHIFT 0
#define BORDER_LEFT_WIDTH_MASK 0xff

static inline css_error set_border_left_width(css_computed_style *style,
		uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_LEFT_WIDTH_INDEX];
	
	/* 8bits: uuuuuttt : unit | type */
	*bits = (*bits & ~BORDER_LEFT_WIDTH_MASK) | ((((uint32_t)type & 0x7) | (
			unit << 3)) << BORDER_LEFT_WIDTH_SHIFT);
	
	style->i.border_left_width = length;
	
	return CSS_OK;
}
#undef BORDER_LEFT_WIDTH_INDEX
#undef BORDER_LEFT_WIDTH_SHIFT
#undef BORDER_LEFT_WIDTH_MASK

#define BORDER_RIGHT_COLOR_INDEX 11
#define BORDER_RIGHT_COLOR_SHIFT 0
#define BORDER_RIGHT_COLOR_MASK 0x3

static inline css_error set_border_right_color(css_computed_style *style,
		uint8_t type, css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_RIGHT_COLOR_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~BORDER_RIGHT_COLOR_MASK) | (((uint32_t)type & 0x3) <<
			BORDER_RIGHT_COLOR_SHIFT);
	
	style->i.border_right_color = color;
	
	return CSS_OK;
}
#undef BORDER_RIGHT_COLOR_INDEX
#undef BORDER_RIGHT_COLOR_SHIFT
#undef BORDER_RIGHT_COLOR_MASK

#define BORDER_RIGHT_STYLE_INDEX 10
#define BORDER_RIGHT_STYLE_SHIFT 12
#define BORDER_RIGHT_STYLE_MASK 0xf000

static inline css_error set_border_right_style(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_RIGHT_STYLE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~BORDER_RIGHT_STYLE_MASK) | (((uint32_t)type & 0xf) <<
			BORDER_RIGHT_STYLE_SHIFT);
	
	return CSS_OK;
}
#undef BORDER_RIGHT_STYLE_INDEX
#undef BORDER_RIGHT_STYLE_SHIFT
#undef BORDER_RIGHT_STYLE_MASK

#define BORDER_RIGHT_WIDTH_INDEX 0
#define BORDER_RIGHT_WIDTH_SHIFT 24
#define BORDER_RIGHT_WIDTH_MASK 0xff000000

static inline css_error set_border_right_width(css_computed_style *style,
		uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_RIGHT_WIDTH_INDEX];
	
	/* 8bits: uuuuuttt : unit | type */
	*bits = (*bits & ~BORDER_RIGHT_WIDTH_MASK) | ((((uint32_t)type & 0x7) |
			(unit << 3)) << BORDER_RIGHT_WIDTH_SHIFT);
	
	style->i.border_right_width = length;
	
	return CSS_OK;
}
#undef BORDER_RIGHT_WIDTH_INDEX
#undef BORDER_RIGHT_WIDTH_SHIFT
#undef BORDER_RIGHT_WIDTH_MASK

#define BORDER_SPACING_INDEX 15
#define BORDER_SPACING_SHIFT 10
#define BORDER_SPACING_MASK 0x1ffc00

static inline css_error set_border_spacing(css_computed_style *style, uint8_t
		type, css_fixed length_a, css_unit unit_a, css_fixed length_b,
		css_unit unit_b)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_SPACING_INDEX];
	
	/* 11bits: aaaaabbbbbt : unit_a | unit_b | type */
	*bits = (*bits & ~BORDER_SPACING_MASK) | ((((uint32_t)type & 0x1) | (
			unit_b << 1) | (unit_a << 6)) << BORDER_SPACING_SHIFT);
	
	style->i.border_spacing_a = length_a;
	
	style->i.border_spacing_b = length_b;
	
	return CSS_OK;
}
#undef BORDER_SPACING_INDEX
#undef BORDER_SPACING_SHIFT
#undef BORDER_SPACING_MASK

#define BORDER_TOP_COLOR_INDEX 14
#define BORDER_TOP_COLOR_SHIFT 12
#define BORDER_TOP_COLOR_MASK 0x3000

static inline css_error set_border_top_color(css_computed_style *style, uint8_t
		type, css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_TOP_COLOR_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~BORDER_TOP_COLOR_MASK) | (((uint32_t)type & 0x3) <<
			BORDER_TOP_COLOR_SHIFT);
	
	style->i.border_top_color = color;
	
	return CSS_OK;
}
#undef BORDER_TOP_COLOR_INDEX
#undef BORDER_TOP_COLOR_SHIFT
#undef BORDER_TOP_COLOR_MASK

#define BORDER_TOP_LEFT_RADIUS_INDEX 4
#define BORDER_TOP_LEFT_RADIUS_SHIFT 4
#define BORDER_TOP_LEFT_RADIUS_MASK 0x7f0

static inline css_error set_border_top_left_radius(css_computed_style *style,
		uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_TOP_LEFT_RADIUS_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~BORDER_TOP_LEFT_RADIUS_MASK) | ((((uint32_t)type &
			0x3) | (unit << 2)) << BORDER_TOP_LEFT_RADIUS_SHIFT);
	
	style->i.border_top_left_radius = length;
	
	return CSS_OK;
}
#undef BORDER_TOP_LEFT_RADIUS_INDEX
#undef BORDER_TOP_LEFT_RADIUS_SHIFT
#undef BORDER_TOP_LEFT_RADIUS_MASK

#define BORDER_TOP_RIGHT_RADIUS_INDEX 1
#define BORDER_TOP_RIGHT_RADIUS_SHIFT 0
#define BORDER_TOP_RIGHT_RADIUS_MASK 0x7f

static inline css_error set_border_top_right_radius(css_computed_style *style,
		uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_TOP_RIGHT_RADIUS_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~BORDER_TOP_RIGHT_RADIUS_MASK) | ((((uint32_t)type &
			0x3) | (unit << 2)) << BORDER_TOP_RIGHT_RADIUS_SHIFT);
	
	style->i.border_top_right_radius = length;
	
	return CSS_OK;
}
#undef BORDER_TOP_RIGHT_RADIUS_INDEX
#undef BORDER_TOP_RIGHT_RADIUS_SHIFT
#undef BORDER_TOP_RIGHT_RADIUS_MASK

#define BORDER_TOP_STYLE_INDEX 10
#define BORDER_TOP_STYLE_SHIFT 16
#define BORDER_TOP_STYLE_MASK 0xf0000

static inline css_error set_border_top_style(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_TOP_STYLE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~BORDER_TOP_STYLE_MASK) | (((uint32_t)type & 0xf) <<
			BORDER_TOP_STYLE_SHIFT);
	
	return CSS_OK;
}
#undef BORDER_TOP_STYLE_INDEX
#undef BORDER_TOP_STYLE_SHIFT
#undef BORDER_TOP_STYLE_MASK

#define BORDER_TOP_WIDTH_INDEX 1
#define BORDER_TOP_WIDTH_SHIFT 15
#define BORDER_TOP_WIDTH_MASK 0x7f8000

static inline css_error set_border_top_width(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BORDER_TOP_WIDTH_INDEX];
	
	/* 8bits: uuuuuttt : unit | type */
	*bits = (*bits & ~BORDER_TOP_WIDTH_MASK) | ((((uint32_t)type & 0x7) | (
			unit << 3)) << BORDER_TOP_WIDTH_SHIFT);
	
	style->i.border_top_width = length;
	
	return CSS_OK;
}
#undef BORDER_TOP_WIDTH_INDEX
#undef BORDER_TOP_WIDTH_SHIFT
#undef BORDER_TOP_WIDTH_MASK

#define BOTTOM_INDEX 4
#define BOTTOM_SHIFT 18
#define BOTTOM_MASK 0x1fc0000

static inline css_error set_bottom(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BOTTOM_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~BOTTOM_MASK) | ((((uint32_t)type & 0x3) | (unit <<
			2)) << BOTTOM_SHIFT);
	
	style->i.bottom = length;
	
	return CSS_OK;
}
#undef BOTTOM_INDEX
#undef BOTTOM_SHIFT
#undef BOTTOM_MASK

#define BOX_SIZING_INDEX 18
#define BOX_SIZING_SHIFT 20
#define BOX_SIZING_MASK 0x300000

static inline css_error set_box_sizing(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BOX_SIZING_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~BOX_SIZING_MASK) | (((uint32_t)type & 0x3) <<
			BOX_SIZING_SHIFT);
	
	return CSS_OK;
}
#undef BOX_SIZING_INDEX
#undef BOX_SIZING_SHIFT
#undef BOX_SIZING_MASK

#define BREAK_AFTER_INDEX 17
#define BREAK_AFTER_SHIFT 13
#define BREAK_AFTER_MASK 0x1e000

static inline css_error set_break_after(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BREAK_AFTER_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~BREAK_AFTER_MASK) | (((uint32_t)type & 0xf) <<
			BREAK_AFTER_SHIFT);
	
	return CSS_OK;
}
#undef BREAK_AFTER_INDEX
#undef BREAK_AFTER_SHIFT
#undef BREAK_AFTER_MASK

#define BREAK_BEFORE_INDEX 7
#define BREAK_BEFORE_SHIFT 0
#define BREAK_BEFORE_MASK 0xf

static inline css_error set_break_before(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BREAK_BEFORE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~BREAK_BEFORE_MASK) | (((uint32_t)type & 0xf) <<
			BREAK_BEFORE_SHIFT);
	
	return CSS_OK;
}
#undef BREAK_BEFORE_INDEX
#undef BREAK_BEFORE_SHIFT
#undef BREAK_BEFORE_MASK

#define BREAK_INSIDE_INDEX 12
#define BREAK_INSIDE_SHIFT 28
#define BREAK_INSIDE_MASK 0xf0000000

static inline css_error set_break_inside(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[BREAK_INSIDE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~BREAK_INSIDE_MASK) | (((uint32_t)type & 0xf) <<
			BREAK_INSIDE_SHIFT);
	
	return CSS_OK;
}
#undef BREAK_INSIDE_INDEX
#undef BREAK_INSIDE_SHIFT
#undef BREAK_INSIDE_MASK

#define CAPTION_SIDE_INDEX 14
#define CAPTION_SIDE_SHIFT 8
#define CAPTION_SIDE_MASK 0x300

static inline css_error set_caption_side(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[CAPTION_SIDE_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~CAPTION_SIDE_MASK) | (((uint32_t)type & 0x3) <<
			CAPTION_SIDE_SHIFT);
	
	return CSS_OK;
}
#undef CAPTION_SIDE_INDEX
#undef CAPTION_SIDE_SHIFT
#undef CAPTION_SIDE_MASK

#define CLEAR_INDEX 12
#define CLEAR_SHIFT 14
#define CLEAR_MASK 0x1c000

static inline css_error set_clear(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[CLEAR_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~CLEAR_MASK) | (((uint32_t)type & 0x7) << CLEAR_SHIFT);
	
	return CSS_OK;
}
#undef CLEAR_INDEX
#undef CLEAR_SHIFT
#undef CLEAR_MASK

#define CLIP_INDEX 2
#define CLIP_SHIFT 6
#define CLIP_MASK 0xffffffc0
static inline css_error set_clip(
		css_computed_style *style, uint8_t type,
		css_computed_clip_rect *rect)
{
	uint32_t *bits;

	bits = &style->i.bits[CLIP_INDEX];

	/*
	26bits: tt tttr rrrr bbbb blll llTR BLyy:
	units: top | right | bottom | left
	opcodes: top | right | bottom | left | type
	*/
	*bits = (*bits & ~CLIP_MASK) |
			((type & 0x3) << CLIP_SHIFT);

	if (type == CSS_CLIP_RECT) {
		*bits |= (((rect->top_auto ? 0x20 : 0) |
				(rect->right_auto ? 0x10 : 0) |
				(rect->bottom_auto ? 0x8 : 0) |
				(rect->left_auto ? 0x4 : 0)) << CLIP_SHIFT);

		*bits |= (((rect->tunit << 5) | rect->runit)
				<< (CLIP_SHIFT + 16));

		*bits |= (((rect->bunit << 5) | rect->lunit)
				<< (CLIP_SHIFT + 6));

		style->i.clip_a = rect->top;
		style->i.clip_b = rect->right;
		style->i.clip_c = rect->bottom;
		style->i.clip_d = rect->left;
	}

	return CSS_OK;
}
#undef CLIP_INDEX
#undef CLIP_SHIFT
#undef CLIP_MASK

#define CLIP_PATH_INDEX 16
#define CLIP_PATH_SHIFT 0
#define CLIP_PATH_MASK 0x1

static inline css_error set_clip_path(css_computed_style *style, uint8_t type,
		lwc_string *string)
{
	uint32_t *bits;
	
	bits = &style->i.bits[CLIP_PATH_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~CLIP_PATH_MASK) | (((uint32_t)type & 0x1) <<
			CLIP_PATH_SHIFT);
	
	lwc_string *old_string = style->i.clip_path;
	
	if (string != NULL) {
		style->i.clip_path = lwc_string_ref(string);
	} else {
		style->i.clip_path = NULL;
	}
	
	if (old_string != NULL)
		lwc_string_unref(old_string);
	
	return CSS_OK;
}
#undef CLIP_PATH_INDEX
#undef CLIP_PATH_SHIFT
#undef CLIP_PATH_MASK

#define CLIP_RULE_INDEX 10
#define CLIP_RULE_SHIFT 20
#define CLIP_RULE_MASK 0xf00000

static inline css_error set_clip_rule(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[CLIP_RULE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~CLIP_RULE_MASK) | (((uint32_t)type & 0xf) <<
			CLIP_RULE_SHIFT);
	
	return CSS_OK;
}
#undef CLIP_RULE_INDEX
#undef CLIP_RULE_SHIFT
#undef CLIP_RULE_MASK

#define COLOR_INDEX 19
#define COLOR_SHIFT 14
#define COLOR_MASK 0x4000

static inline css_error set_color(css_computed_style *style, uint8_t type,
		css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COLOR_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~COLOR_MASK) | (((uint32_t)type & 0x1) << COLOR_SHIFT);
	
	style->i.color = color;
	
	return CSS_OK;
}
#undef COLOR_INDEX
#undef COLOR_SHIFT
#undef COLOR_MASK

#define COLUMN_COUNT_INDEX 14
#define COLUMN_COUNT_SHIFT 0
#define COLUMN_COUNT_MASK 0x3

static inline css_error set_column_count(css_computed_style *style, uint8_t
		type, int32_t integer)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COLUMN_COUNT_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~COLUMN_COUNT_MASK) | (((uint32_t)type & 0x3) <<
			COLUMN_COUNT_SHIFT);
	
	style->i.column_count = integer;
	
	return CSS_OK;
}
#undef COLUMN_COUNT_INDEX
#undef COLUMN_COUNT_SHIFT
#undef COLUMN_COUNT_MASK

#define COLUMN_FILL_INDEX 18
#define COLUMN_FILL_SHIFT 10
#define COLUMN_FILL_MASK 0xc00

static inline css_error set_column_fill(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COLUMN_FILL_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~COLUMN_FILL_MASK) | (((uint32_t)type & 0x3) <<
			COLUMN_FILL_SHIFT);
	
	return CSS_OK;
}
#undef COLUMN_FILL_INDEX
#undef COLUMN_FILL_SHIFT
#undef COLUMN_FILL_MASK

#define COLUMN_GAP_INDEX 7
#define COLUMN_GAP_SHIFT 4
#define COLUMN_GAP_MASK 0x7f0

static inline css_error set_column_gap(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COLUMN_GAP_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~COLUMN_GAP_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << COLUMN_GAP_SHIFT);
	
	style->i.column_gap = length;
	
	return CSS_OK;
}
#undef COLUMN_GAP_INDEX
#undef COLUMN_GAP_SHIFT
#undef COLUMN_GAP_MASK

#define COLUMN_RULE_COLOR_INDEX 18
#define COLUMN_RULE_COLOR_SHIFT 22
#define COLUMN_RULE_COLOR_MASK 0xc00000

static inline css_error set_column_rule_color(css_computed_style *style,
		uint8_t type, css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COLUMN_RULE_COLOR_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~COLUMN_RULE_COLOR_MASK) | (((uint32_t)type & 0x3) <<
			COLUMN_RULE_COLOR_SHIFT);
	
	style->i.column_rule_color = color;
	
	return CSS_OK;
}
#undef COLUMN_RULE_COLOR_INDEX
#undef COLUMN_RULE_COLOR_SHIFT
#undef COLUMN_RULE_COLOR_MASK

#define COLUMN_RULE_STYLE_INDEX 3
#define COLUMN_RULE_STYLE_SHIFT 0
#define COLUMN_RULE_STYLE_MASK 0xf

static inline css_error set_column_rule_style(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COLUMN_RULE_STYLE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~COLUMN_RULE_STYLE_MASK) | (((uint32_t)type & 0xf) <<
			COLUMN_RULE_STYLE_SHIFT);
	
	return CSS_OK;
}
#undef COLUMN_RULE_STYLE_INDEX
#undef COLUMN_RULE_STYLE_SHIFT
#undef COLUMN_RULE_STYLE_MASK

#define COLUMN_RULE_WIDTH_INDEX 1
#define COLUMN_RULE_WIDTH_SHIFT 7
#define COLUMN_RULE_WIDTH_MASK 0x7f80

static inline css_error set_column_rule_width(css_computed_style *style,
		uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COLUMN_RULE_WIDTH_INDEX];
	
	/* 8bits: uuuuuttt : unit | type */
	*bits = (*bits & ~COLUMN_RULE_WIDTH_MASK) | ((((uint32_t)type & 0x7) | (
			unit << 3)) << COLUMN_RULE_WIDTH_SHIFT);
	
	style->i.column_rule_width = length;
	
	return CSS_OK;
}
#undef COLUMN_RULE_WIDTH_INDEX
#undef COLUMN_RULE_WIDTH_SHIFT
#undef COLUMN_RULE_WIDTH_MASK

#define COLUMN_SPAN_INDEX 18
#define COLUMN_SPAN_SHIFT 14
#define COLUMN_SPAN_MASK 0xc000

static inline css_error set_column_span(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COLUMN_SPAN_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~COLUMN_SPAN_MASK) | (((uint32_t)type & 0x3) <<
			COLUMN_SPAN_SHIFT);
	
	return CSS_OK;
}
#undef COLUMN_SPAN_INDEX
#undef COLUMN_SPAN_SHIFT
#undef COLUMN_SPAN_MASK

#define COLUMN_WIDTH_INDEX 5
#define COLUMN_WIDTH_SHIFT 11
#define COLUMN_WIDTH_MASK 0x3f800

static inline css_error set_column_width(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COLUMN_WIDTH_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~COLUMN_WIDTH_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << COLUMN_WIDTH_SHIFT);
	
	style->i.column_width = length;
	
	return CSS_OK;
}
#undef COLUMN_WIDTH_INDEX
#undef COLUMN_WIDTH_SHIFT
#undef COLUMN_WIDTH_MASK

#define COMP_OP_INDEX 11
#define COMP_OP_SHIFT 2
#define COMP_OP_MASK 0x7c

static inline css_error set_comp_op(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COMP_OP_INDEX];
	
	/* 5bits: ttttt : type */
	*bits = (*bits & ~COMP_OP_MASK) | (((uint32_t)type & 0x1f) <<
			COMP_OP_SHIFT);
	
	return CSS_OK;
}
#undef COMP_OP_INDEX
#undef COMP_OP_SHIFT
#undef COMP_OP_MASK

#define CONTENT_INDEX 18
#define CONTENT_SHIFT 28
#define CONTENT_MASK 0x30000000
static inline css_error set_content(
		css_computed_style *style, uint8_t type,
		css_computed_content_item *content)
{
	uint32_t *bits;
	css_computed_content_item *oldcontent;
	css_computed_content_item *c;

	/* 2bits: type */
	bits = &style->i.bits[CONTENT_INDEX];
	oldcontent = style->content;

	*bits = (*bits & ~CONTENT_MASK) |
			((type & 0x3) << CONTENT_SHIFT);

	for (c = content; c != NULL &&
			c->type != CSS_COMPUTED_CONTENT_NONE; c++) {
		switch (c->type) {
		case CSS_COMPUTED_CONTENT_STRING:
			c->data.string = lwc_string_ref(c->data.string);
			break;
		case CSS_COMPUTED_CONTENT_URI:
			c->data.uri = lwc_string_ref(c->data.uri);
			break;
		case CSS_COMPUTED_CONTENT_ATTR:
			c->data.attr = lwc_string_ref(c->data.attr);
			break;
		case CSS_COMPUTED_CONTENT_COUNTER:
			c->data.counter.name =
				lwc_string_ref(c->data.counter.name);
			break;
		case CSS_COMPUTED_CONTENT_COUNTERS:
			c->data.counters.name =
				lwc_string_ref(c->data.counters.name);
			c->data.counters.sep =
				lwc_string_ref(c->data.counters.sep);
			break;
		default:
			break;
		}
	}

	style->content = content;

	/* Free existing array */
	if (oldcontent != NULL) {
		for (c = oldcontent;
				c->type != CSS_COMPUTED_CONTENT_NONE; c++) {
			switch (c->type) {
			case CSS_COMPUTED_CONTENT_STRING:
				lwc_string_unref(c->data.string);
				break;
			case CSS_COMPUTED_CONTENT_URI:
				lwc_string_unref(c->data.uri);
				break;
			case CSS_COMPUTED_CONTENT_ATTR:
				lwc_string_unref(c->data.attr);
				break;
			case CSS_COMPUTED_CONTENT_COUNTER:
				lwc_string_unref(c->data.counter.name);
				break;
			case CSS_COMPUTED_CONTENT_COUNTERS:
				lwc_string_unref(c->data.counters.name);
				lwc_string_unref(c->data.counters.sep);
				break;
			default:
				break;
			}
		}

		if (oldcontent != content)
			free(oldcontent);
	}

	return CSS_OK;
}
#undef CONTENT_INDEX
#undef CONTENT_SHIFT
#undef CONTENT_MASK

#define COUNTER_INCREMENT_INDEX 19
#define COUNTER_INCREMENT_SHIFT 16
#define COUNTER_INCREMENT_MASK 0x10000

static inline css_error set_counter_increment(css_computed_style *style,
		uint8_t type, css_computed_counter *counter_arr)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COUNTER_INCREMENT_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~COUNTER_INCREMENT_MASK) | (((uint32_t)type & 0x1) <<
			COUNTER_INCREMENT_SHIFT);
	
	css_computed_counter *old_counter_arr = style->counter_increment;
	css_computed_counter *c;
	
	for (c = counter_arr; c != NULL && c->name != NULL; c++)
		c->name = lwc_string_ref(c->name);
	
	style->counter_increment = counter_arr;
	
	/* Free existing array */
	if (old_counter_arr != NULL) {
		for (c = old_counter_arr; c->name != NULL; c++)
			lwc_string_unref(c->name);
		
		if (old_counter_arr != counter_arr)
			free(old_counter_arr);
	}
	
	return CSS_OK;
}
#undef COUNTER_INCREMENT_INDEX
#undef COUNTER_INCREMENT_SHIFT
#undef COUNTER_INCREMENT_MASK

#define COUNTER_RESET_INDEX 18
#define COUNTER_RESET_SHIFT 0
#define COUNTER_RESET_MASK 0x1

static inline css_error set_counter_reset(css_computed_style *style, uint8_t
		type, css_computed_counter *counter_arr)
{
	uint32_t *bits;
	
	bits = &style->i.bits[COUNTER_RESET_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~COUNTER_RESET_MASK) | (((uint32_t)type & 0x1) <<
			COUNTER_RESET_SHIFT);
	
	css_computed_counter *old_counter_arr = style->counter_reset;
	css_computed_counter *c;
	
	for (c = counter_arr; c != NULL && c->name != NULL; c++)
		c->name = lwc_string_ref(c->name);
	
	style->counter_reset = counter_arr;
	
	/* Free existing array */
	if (old_counter_arr != NULL) {
		for (c = old_counter_arr; c->name != NULL; c++)
			lwc_string_unref(c->name);
		
		if (old_counter_arr != counter_arr)
			free(old_counter_arr);
	}
	
	return CSS_OK;
}
#undef COUNTER_RESET_INDEX
#undef COUNTER_RESET_SHIFT
#undef COUNTER_RESET_MASK

#define CURSOR_INDEX 17
#define CURSOR_SHIFT 22
#define CURSOR_MASK 0x7c00000

static inline css_error set_cursor(css_computed_style *style, uint8_t type,
		lwc_string **string_arr)
{
	uint32_t *bits;
	
	bits = &style->i.bits[CURSOR_INDEX];
	
	/* 5bits: ttttt : type */
	*bits = (*bits & ~CURSOR_MASK) | (((uint32_t)type & 0x1f) <<
			CURSOR_SHIFT);
	
	lwc_string **old_string_arr = style->cursor;
	lwc_string **s;
	
	for (s = string_arr; s != NULL && *s != NULL; s++)
		*s = lwc_string_ref(*s);
	
	style->cursor = string_arr;
	
	/* Free existing array */
	if (old_string_arr != NULL) {
		for (s = old_string_arr; *s != NULL; s++)
			lwc_string_unref(*s);
		
		if (old_string_arr != string_arr)
			free(old_string_arr);
	}
	
	return CSS_OK;
}
#undef CURSOR_INDEX
#undef CURSOR_SHIFT
#undef CURSOR_MASK

#define DIRECTION_INDEX 14
#define DIRECTION_SHIFT 10
#define DIRECTION_MASK 0xc00

static inline css_error set_direction(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[DIRECTION_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~DIRECTION_MASK) | (((uint32_t)type & 0x3) <<
			DIRECTION_SHIFT);
	
	return CSS_OK;
}
#undef DIRECTION_INDEX
#undef DIRECTION_SHIFT
#undef DIRECTION_MASK

#define DISPLAY_INDEX 17
#define DISPLAY_SHIFT 27
#define DISPLAY_MASK 0xf8000000

static inline css_error set_display(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[DISPLAY_INDEX];
	
	/* 5bits: ttttt : type */
	*bits = (*bits & ~DISPLAY_MASK) | (((uint32_t)type & 0x1f) <<
			DISPLAY_SHIFT);
	
	return CSS_OK;
}
#undef DISPLAY_INDEX
#undef DISPLAY_SHIFT
#undef DISPLAY_MASK

#define EMPTY_CELLS_INDEX 14
#define EMPTY_CELLS_SHIFT 6
#define EMPTY_CELLS_MASK 0xc0

static inline css_error set_empty_cells(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[EMPTY_CELLS_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~EMPTY_CELLS_MASK) | (((uint32_t)type & 0x3) <<
			EMPTY_CELLS_SHIFT);
	
	return CSS_OK;
}
#undef EMPTY_CELLS_INDEX
#undef EMPTY_CELLS_SHIFT
#undef EMPTY_CELLS_MASK

#define ENABLE_BACKGROUND_INDEX 17
#define ENABLE_BACKGROUND_SHIFT 17
#define ENABLE_BACKGROUND_MASK 0x3e0000

static inline css_error set_enable_background(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[ENABLE_BACKGROUND_INDEX];
	
	/* 5bits: ttttt : type */
	*bits = (*bits & ~ENABLE_BACKGROUND_MASK) | (((uint32_t)type & 0x1f) <<
			ENABLE_BACKGROUND_SHIFT);
	
	return CSS_OK;
}
#undef ENABLE_BACKGROUND_INDEX
#undef ENABLE_BACKGROUND_SHIFT
#undef ENABLE_BACKGROUND_MASK

#define FILL_INDEX 13
#define FILL_SHIFT 5
#define FILL_MASK 0xe0
static inline css_error set_fill(css_computed_style *style, uint8_t type,
        lwc_string *string, css_color color)
{
    uint32_t *bits;

    bits = &style->i.bits[FILL_INDEX];

    /* 3bits: ttt : type */
    *bits = (*bits & ~FILL_MASK) | (((uint32_t)type & 0x7) << FILL_SHIFT);

    lwc_string *old_string = style->i.fill;

    if (string != NULL) {
        style->i.fill = lwc_string_ref(string);
    } else {
        style->i.fill = NULL;
    }

    if (old_string != NULL)
        lwc_string_unref(old_string);

    style->i.fill_color = color;

    return CSS_OK;
}
#undef FILL_INDEX
#undef FILL_SHIFT
#undef FILL_MASK

#define FILL_OPACITY_INDEX 19
#define FILL_OPACITY_SHIFT 19
#define FILL_OPACITY_MASK 0x80000

static inline css_error set_fill_opacity(css_computed_style *style, uint8_t
		type, css_fixed fixed)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FILL_OPACITY_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~FILL_OPACITY_MASK) | (((uint32_t)type & 0x1) <<
			FILL_OPACITY_SHIFT);
	
	style->i.fill_opacity = fixed;
	
	return CSS_OK;
}
#undef FILL_OPACITY_INDEX
#undef FILL_OPACITY_SHIFT
#undef FILL_OPACITY_MASK

#define FILL_RULE_INDEX 13
#define FILL_RULE_SHIFT 8
#define FILL_RULE_MASK 0x700

static inline css_error set_fill_rule(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FILL_RULE_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~FILL_RULE_MASK) | (((uint32_t)type & 0x7) <<
			FILL_RULE_SHIFT);
	
	return CSS_OK;
}
#undef FILL_RULE_INDEX
#undef FILL_RULE_SHIFT
#undef FILL_RULE_MASK

#define FILTER_INDEX 19
#define FILTER_SHIFT 24
#define FILTER_MASK 0x1000000

static inline css_error set_filter(css_computed_style *style, uint8_t type,
		lwc_string *string)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FILTER_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~FILTER_MASK) | (((uint32_t)type & 0x1) <<
			FILTER_SHIFT);
	
	lwc_string *old_string = style->i.filter;
	
	if (string != NULL) {
		style->i.filter = lwc_string_ref(string);
	} else {
		style->i.filter = NULL;
	}
	
	if (old_string != NULL)
		lwc_string_unref(old_string);
	
	return CSS_OK;
}
#undef FILTER_INDEX
#undef FILTER_SHIFT
#undef FILTER_MASK

#define FLEX_BASIS_INDEX 8
#define FLEX_BASIS_SHIFT 25
#define FLEX_BASIS_MASK 0xfe000000

static inline css_error set_flex_basis(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FLEX_BASIS_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~FLEX_BASIS_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << FLEX_BASIS_SHIFT);
	
	style->i.flex_basis = length;
	
	return CSS_OK;
}
#undef FLEX_BASIS_INDEX
#undef FLEX_BASIS_SHIFT
#undef FLEX_BASIS_MASK

#define FLEX_DIRECTION_INDEX 12
#define FLEX_DIRECTION_SHIFT 17
#define FLEX_DIRECTION_MASK 0xe0000

static inline css_error set_flex_direction(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FLEX_DIRECTION_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~FLEX_DIRECTION_MASK) | (((uint32_t)type & 0x7) <<
			FLEX_DIRECTION_SHIFT);
	
	return CSS_OK;
}
#undef FLEX_DIRECTION_INDEX
#undef FLEX_DIRECTION_SHIFT
#undef FLEX_DIRECTION_MASK

#define FLEX_GROW_INDEX 19
#define FLEX_GROW_SHIFT 28
#define FLEX_GROW_MASK 0x10000000

static inline css_error set_flex_grow(css_computed_style *style, uint8_t type,
		css_fixed fixed)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FLEX_GROW_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~FLEX_GROW_MASK) | (((uint32_t)type & 0x1) <<
			FLEX_GROW_SHIFT);
	
	style->i.flex_grow = fixed;
	
	return CSS_OK;
}
#undef FLEX_GROW_INDEX
#undef FLEX_GROW_SHIFT
#undef FLEX_GROW_MASK

#define FLEX_SHRINK_INDEX 19
#define FLEX_SHRINK_SHIFT 21
#define FLEX_SHRINK_MASK 0x200000

static inline css_error set_flex_shrink(css_computed_style *style, uint8_t
		type, css_fixed fixed)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FLEX_SHRINK_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~FLEX_SHRINK_MASK) | (((uint32_t)type & 0x1) <<
			FLEX_SHRINK_SHIFT);
	
	style->i.flex_shrink = fixed;
	
	return CSS_OK;
}
#undef FLEX_SHRINK_INDEX
#undef FLEX_SHRINK_SHIFT
#undef FLEX_SHRINK_MASK

#define FLEX_WRAP_INDEX 14
#define FLEX_WRAP_SHIFT 16
#define FLEX_WRAP_MASK 0x30000

static inline css_error set_flex_wrap(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FLEX_WRAP_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~FLEX_WRAP_MASK) | (((uint32_t)type & 0x3) <<
			FLEX_WRAP_SHIFT);
	
	return CSS_OK;
}
#undef FLEX_WRAP_INDEX
#undef FLEX_WRAP_SHIFT
#undef FLEX_WRAP_MASK

#define FLOAT_INDEX 18
#define FLOAT_SHIFT 8
#define FLOAT_MASK 0x300

static inline css_error set_float(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FLOAT_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~FLOAT_MASK) | (((uint32_t)type & 0x3) << FLOAT_SHIFT);
	
	return CSS_OK;
}
#undef FLOAT_INDEX
#undef FLOAT_SHIFT
#undef FLOAT_MASK

#define FLOOD_COLOR_INDEX 19
#define FLOOD_COLOR_SHIFT 18
#define FLOOD_COLOR_MASK 0x40000

static inline css_error set_flood_color(css_computed_style *style, uint8_t
		type, css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FLOOD_COLOR_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~FLOOD_COLOR_MASK) | (((uint32_t)type & 0x1) <<
			FLOOD_COLOR_SHIFT);
	
	style->i.flood_color = color;
	
	return CSS_OK;
}
#undef FLOOD_COLOR_INDEX
#undef FLOOD_COLOR_SHIFT
#undef FLOOD_COLOR_MASK

#define FLOOD_OPACITY_INDEX 19
#define FLOOD_OPACITY_SHIFT 20
#define FLOOD_OPACITY_MASK 0x100000

static inline css_error set_flood_opacity(css_computed_style *style, uint8_t
		type, css_fixed fixed)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FLOOD_OPACITY_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~FLOOD_OPACITY_MASK) | (((uint32_t)type & 0x1) <<
			FLOOD_OPACITY_SHIFT);
	
	style->i.flood_opacity = fixed;
	
	return CSS_OK;
}
#undef FLOOD_OPACITY_INDEX
#undef FLOOD_OPACITY_SHIFT
#undef FLOOD_OPACITY_MASK

#define FONT_FAMILY_INDEX 14
#define FONT_FAMILY_SHIFT 26
#define FONT_FAMILY_MASK 0x1c000000

static inline css_error set_font_family(css_computed_style *style, uint8_t
		type, lwc_string **string_arr)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FONT_FAMILY_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~FONT_FAMILY_MASK) | (((uint32_t)type & 0x7) <<
			FONT_FAMILY_SHIFT);
	
	lwc_string **old_string_arr = style->font_family;
	lwc_string **s;
	
	for (s = string_arr; s != NULL && *s != NULL; s++)
		*s = lwc_string_ref(*s);
	
	style->font_family = string_arr;
	
	/* Free existing array */
	if (old_string_arr != NULL) {
		for (s = old_string_arr; *s != NULL; s++)
			lwc_string_unref(*s);
		
		if (old_string_arr != string_arr)
			free(old_string_arr);
	}
	
	return CSS_OK;
}
#undef FONT_FAMILY_INDEX
#undef FONT_FAMILY_SHIFT
#undef FONT_FAMILY_MASK

#define FONT_SIZE_INDEX 1
#define FONT_SIZE_SHIFT 23
#define FONT_SIZE_MASK 0xff800000

static inline css_error set_font_size(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FONT_SIZE_INDEX];
	
	/* 9bits: uuuuutttt : unit | type */
	*bits = (*bits & ~FONT_SIZE_MASK) | ((((uint32_t)type & 0xf) | (unit <<
			4)) << FONT_SIZE_SHIFT);
	
	style->i.font_size = length;
	
	return CSS_OK;
}
#undef FONT_SIZE_INDEX
#undef FONT_SIZE_SHIFT
#undef FONT_SIZE_MASK

#define FONT_STRETCH_INDEX 11
#define FONT_STRETCH_SHIFT 12
#define FONT_STRETCH_MASK 0x1f000

static inline css_error set_font_stretch(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FONT_STRETCH_INDEX];
	
	/* 5bits: ttttt : type */
	*bits = (*bits & ~FONT_STRETCH_MASK) | (((uint32_t)type & 0x1f) <<
			FONT_STRETCH_SHIFT);
	
	return CSS_OK;
}
#undef FONT_STRETCH_INDEX
#undef FONT_STRETCH_SHIFT
#undef FONT_STRETCH_MASK

#define FONT_STYLE_INDEX 14
#define FONT_STYLE_SHIFT 2
#define FONT_STYLE_MASK 0xc

static inline css_error set_font_style(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FONT_STYLE_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~FONT_STYLE_MASK) | (((uint32_t)type & 0x3) <<
			FONT_STYLE_SHIFT);
	
	return CSS_OK;
}
#undef FONT_STYLE_INDEX
#undef FONT_STYLE_SHIFT
#undef FONT_STYLE_MASK

#define FONT_VARIANT_INDEX 14
#define FONT_VARIANT_SHIFT 14
#define FONT_VARIANT_MASK 0xc000

static inline css_error set_font_variant(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FONT_VARIANT_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~FONT_VARIANT_MASK) | (((uint32_t)type & 0x3) <<
			FONT_VARIANT_SHIFT);
	
	return CSS_OK;
}
#undef FONT_VARIANT_INDEX
#undef FONT_VARIANT_SHIFT
#undef FONT_VARIANT_MASK

#define FONT_WEIGHT_INDEX 8
#define FONT_WEIGHT_SHIFT 0
#define FONT_WEIGHT_MASK 0xf

static inline css_error set_font_weight(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[FONT_WEIGHT_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~FONT_WEIGHT_MASK) | (((uint32_t)type & 0xf) <<
			FONT_WEIGHT_SHIFT);
	
	return CSS_OK;
}
#undef FONT_WEIGHT_INDEX
#undef FONT_WEIGHT_SHIFT
#undef FONT_WEIGHT_MASK

#define GRID_COLUMN_END_INDEX 5
#define GRID_COLUMN_END_SHIFT 4
#define GRID_COLUMN_END_MASK 0x7f0

static inline css_error set_grid_column_end(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[GRID_COLUMN_END_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~GRID_COLUMN_END_MASK) | ((((uint32_t)type & 0x3) | (
			unit << 2)) << GRID_COLUMN_END_SHIFT);
	
	style->i.grid_column_end = length;
	
	return CSS_OK;
}
#undef GRID_COLUMN_END_INDEX
#undef GRID_COLUMN_END_SHIFT
#undef GRID_COLUMN_END_MASK

#define GRID_COLUMN_START_INDEX 3
#define GRID_COLUMN_START_SHIFT 4
#define GRID_COLUMN_START_MASK 0x7f0

static inline css_error set_grid_column_start(css_computed_style *style,
		uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[GRID_COLUMN_START_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~GRID_COLUMN_START_MASK) | ((((uint32_t)type & 0x3) | (
			unit << 2)) << GRID_COLUMN_START_SHIFT);
	
	style->i.grid_column_start = length;
	
	return CSS_OK;
}
#undef GRID_COLUMN_START_INDEX
#undef GRID_COLUMN_START_SHIFT
#undef GRID_COLUMN_START_MASK

#define GRID_ROW_END_INDEX 6
#define GRID_ROW_END_SHIFT 25
#define GRID_ROW_END_MASK 0xfe000000

static inline css_error set_grid_row_end(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[GRID_ROW_END_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~GRID_ROW_END_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << GRID_ROW_END_SHIFT);
	
	style->i.grid_row_end = length;
	
	return CSS_OK;
}
#undef GRID_ROW_END_INDEX
#undef GRID_ROW_END_SHIFT
#undef GRID_ROW_END_MASK

#define GRID_ROW_START_INDEX 7
#define GRID_ROW_START_SHIFT 18
#define GRID_ROW_START_MASK 0x1fc0000

static inline css_error set_grid_row_start(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[GRID_ROW_START_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~GRID_ROW_START_MASK) | ((((uint32_t)type & 0x3) | (
			unit << 2)) << GRID_ROW_START_SHIFT);
	
	style->i.grid_row_start = length;
	
	return CSS_OK;
}
#undef GRID_ROW_START_INDEX
#undef GRID_ROW_START_SHIFT
#undef GRID_ROW_START_MASK

#define GRID_TEMPLATE_COLUMNS_INDEX 12
#define GRID_TEMPLATE_COLUMNS_SHIFT 0
#define GRID_TEMPLATE_COLUMNS_MASK 0x3
static inline css_error set_grid_template_columns(css_computed_style *style, uint8_t type, size_t size, css_fixed *values,
		css_unit *units)
{
    style->i.grid_template_columns_type = type;
    style->i.grid_template_columns_size = size;

    if (size == 0 || values == NULL || units == NULL)
    {
        return CSS_OK;
    }

    style->i.grid_template_columns = (css_fixed*) malloc(size * sizeof(css_fixed));
    style->i.grid_template_columns_unit = (css_unit*) malloc(size *sizeof(css_unit));
    for (int i = 0; i < size; i++)
    {
        style->i.grid_template_columns[i] = values[i];
        style->i.grid_template_columns_unit[i] = units[i];
    }
	return CSS_OK;
}
#undef GRID_TEMPLATE_COLUMNS_INDEX
#undef GRID_TEMPLATE_COLUMNS_SHIFT
#undef GRID_TEMPLATE_COLUMNS_MASK

#define GRID_TEMPLATE_ROWS_INDEX 18
#define GRID_TEMPLATE_ROWS_SHIFT 12
#define GRID_TEMPLATE_ROWS_MASK 0x3000
static inline css_error set_grid_template_rows(css_computed_style *style, uint8_t type, size_t size, css_fixed *values,
		css_unit *units)
{
    style->i.grid_template_rows_type = type;
    style->i.grid_template_rows_size = size;

    if (size == 0 || values == NULL || units == NULL)
    {
        return CSS_OK;
    }

    style->i.grid_template_rows = (css_fixed*) malloc(size * sizeof(css_fixed));
    style->i.grid_template_rows_unit = (css_unit*) malloc(size *sizeof(css_unit));
    for (int i = 0; i < size; i++)
    {
        style->i.grid_template_rows[i] = values[i];
        style->i.grid_template_rows_unit[i] = units[i];
    }
	return CSS_OK;
}
#undef GRID_TEMPLATE_ROWS_INDEX
#undef GRID_TEMPLATE_ROWS_SHIFT
#undef GRID_TEMPLATE_ROWS_MASK

#define HEIGHT_INDEX 9
#define HEIGHT_SHIFT 4
#define HEIGHT_MASK 0x7f0

static inline css_error set_height(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[HEIGHT_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~HEIGHT_MASK) | ((((uint32_t)type & 0x3) | (unit <<
			2)) << HEIGHT_SHIFT);
	
	style->i.height = length;
	
	return CSS_OK;
}
#undef HEIGHT_INDEX
#undef HEIGHT_SHIFT
#undef HEIGHT_MASK

#define JUSTIFY_CONTENT_INDEX 13
#define JUSTIFY_CONTENT_SHIFT 11
#define JUSTIFY_CONTENT_MASK 0x3800

static inline css_error set_justify_content(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[JUSTIFY_CONTENT_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~JUSTIFY_CONTENT_MASK) | (((uint32_t)type & 0x7) <<
			JUSTIFY_CONTENT_SHIFT);
	
	return CSS_OK;
}
#undef JUSTIFY_CONTENT_INDEX
#undef JUSTIFY_CONTENT_SHIFT
#undef JUSTIFY_CONTENT_MASK

#define LEFT_INDEX 3
#define LEFT_SHIFT 25
#define LEFT_MASK 0xfe000000

static inline css_error set_left(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[LEFT_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~LEFT_MASK) | ((((uint32_t)type & 0x3) | (unit << 2))
			<< LEFT_SHIFT);
	
	style->i.left = length;
	
	return CSS_OK;
}
#undef LEFT_INDEX
#undef LEFT_SHIFT
#undef LEFT_MASK

#define LETTER_SPACING_INDEX 6
#define LETTER_SPACING_SHIFT 4
#define LETTER_SPACING_MASK 0x7f0

static inline css_error set_letter_spacing(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[LETTER_SPACING_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~LETTER_SPACING_MASK) | ((((uint32_t)type & 0x3) | (
			unit << 2)) << LETTER_SPACING_SHIFT);
	
	style->i.letter_spacing = length;
	
	return CSS_OK;
}
#undef LETTER_SPACING_INDEX
#undef LETTER_SPACING_SHIFT
#undef LETTER_SPACING_MASK

#define LINE_HEIGHT_INDEX 8
#define LINE_HEIGHT_SHIFT 4
#define LINE_HEIGHT_MASK 0x7f0

static inline css_error set_line_height(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[LINE_HEIGHT_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~LINE_HEIGHT_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << LINE_HEIGHT_SHIFT);
	
	style->i.line_height = length;
	
	return CSS_OK;
}
#undef LINE_HEIGHT_INDEX
#undef LINE_HEIGHT_SHIFT
#undef LINE_HEIGHT_MASK

#define LIST_STYLE_IMAGE_INDEX 19
#define LIST_STYLE_IMAGE_SHIFT 23
#define LIST_STYLE_IMAGE_MASK 0x800000

static inline css_error set_list_style_image(css_computed_style *style, uint8_t
		type, lwc_string *string)
{
	uint32_t *bits;
	
	bits = &style->i.bits[LIST_STYLE_IMAGE_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~LIST_STYLE_IMAGE_MASK) | (((uint32_t)type & 0x1) <<
			LIST_STYLE_IMAGE_SHIFT);
	
	lwc_string *old_string = style->i.list_style_image;
	
	if (string != NULL) {
		style->i.list_style_image = lwc_string_ref(string);
	} else {
		style->i.list_style_image = NULL;
	}
	
	if (old_string != NULL)
		lwc_string_unref(old_string);
	
	return CSS_OK;
}
#undef LIST_STYLE_IMAGE_INDEX
#undef LIST_STYLE_IMAGE_SHIFT
#undef LIST_STYLE_IMAGE_MASK

#define LIST_STYLE_POSITION_INDEX 18
#define LIST_STYLE_POSITION_SHIFT 24
#define LIST_STYLE_POSITION_MASK 0x3000000

static inline css_error set_list_style_position(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[LIST_STYLE_POSITION_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~LIST_STYLE_POSITION_MASK) | (((uint32_t)type & 0x3)
			<< LIST_STYLE_POSITION_SHIFT);
	
	return CSS_OK;
}
#undef LIST_STYLE_POSITION_INDEX
#undef LIST_STYLE_POSITION_SHIFT
#undef LIST_STYLE_POSITION_MASK

#define LIST_STYLE_TYPE_INDEX 4
#define LIST_STYLE_TYPE_SHIFT 0
#define LIST_STYLE_TYPE_MASK 0xf

static inline css_error set_list_style_type(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[LIST_STYLE_TYPE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~LIST_STYLE_TYPE_MASK) | (((uint32_t)type & 0xf) <<
			LIST_STYLE_TYPE_SHIFT);
	
	return CSS_OK;
}
#undef LIST_STYLE_TYPE_INDEX
#undef LIST_STYLE_TYPE_SHIFT
#undef LIST_STYLE_TYPE_MASK

#define MARGIN_BOTTOM_INDEX 8
#define MARGIN_BOTTOM_SHIFT 18
#define MARGIN_BOTTOM_MASK 0x1fc0000

static inline css_error set_margin_bottom(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MARGIN_BOTTOM_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~MARGIN_BOTTOM_MASK) | ((((uint32_t)type & 0x3) | (
			unit << 2)) << MARGIN_BOTTOM_SHIFT);
	
	style->i.margin_bottom = length;
	
	return CSS_OK;
}
#undef MARGIN_BOTTOM_INDEX
#undef MARGIN_BOTTOM_SHIFT
#undef MARGIN_BOTTOM_MASK

#define MARGIN_LEFT_INDEX 5
#define MARGIN_LEFT_SHIFT 18
#define MARGIN_LEFT_MASK 0x1fc0000

static inline css_error set_margin_left(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MARGIN_LEFT_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~MARGIN_LEFT_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << MARGIN_LEFT_SHIFT);
	
	style->i.margin_left = length;
	
	return CSS_OK;
}
#undef MARGIN_LEFT_INDEX
#undef MARGIN_LEFT_SHIFT
#undef MARGIN_LEFT_MASK

#define MARGIN_RIGHT_INDEX 7
#define MARGIN_RIGHT_SHIFT 11
#define MARGIN_RIGHT_MASK 0x3f800

static inline css_error set_margin_right(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MARGIN_RIGHT_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~MARGIN_RIGHT_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << MARGIN_RIGHT_SHIFT);
	
	style->i.margin_right = length;
	
	return CSS_OK;
}
#undef MARGIN_RIGHT_INDEX
#undef MARGIN_RIGHT_SHIFT
#undef MARGIN_RIGHT_MASK

#define MARGIN_TOP_INDEX 4
#define MARGIN_TOP_SHIFT 11
#define MARGIN_TOP_MASK 0x3f800

static inline css_error set_margin_top(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MARGIN_TOP_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~MARGIN_TOP_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << MARGIN_TOP_SHIFT);
	
	style->i.margin_top = length;
	
	return CSS_OK;
}
#undef MARGIN_TOP_INDEX
#undef MARGIN_TOP_SHIFT
#undef MARGIN_TOP_MASK

#define MARKER_END_INDEX 19
#define MARKER_END_SHIFT 15
#define MARKER_END_MASK 0x8000

static inline css_error set_marker_end(css_computed_style *style, uint8_t type,
		lwc_string *string)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MARKER_END_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~MARKER_END_MASK) | (((uint32_t)type & 0x1) <<
			MARKER_END_SHIFT);
	
	lwc_string *old_string = style->i.marker_end;
	
	if (string != NULL) {
		style->i.marker_end = lwc_string_ref(string);
	} else {
		style->i.marker_end = NULL;
	}
	
	if (old_string != NULL)
		lwc_string_unref(old_string);
	
	return CSS_OK;
}
#undef MARKER_END_INDEX
#undef MARKER_END_SHIFT
#undef MARKER_END_MASK

#define MARKER_MID_INDEX 15
#define MARKER_MID_SHIFT 0
#define MARKER_MID_MASK 0x1

static inline css_error set_marker_mid(css_computed_style *style, uint8_t type,
		lwc_string *string)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MARKER_MID_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~MARKER_MID_MASK) | (((uint32_t)type & 0x1) <<
			MARKER_MID_SHIFT);
	
	lwc_string *old_string = style->i.marker_mid;
	
	if (string != NULL) {
		style->i.marker_mid = lwc_string_ref(string);
	} else {
		style->i.marker_mid = NULL;
	}
	
	if (old_string != NULL)
		lwc_string_unref(old_string);
	
	return CSS_OK;
}
#undef MARKER_MID_INDEX
#undef MARKER_MID_SHIFT
#undef MARKER_MID_MASK

#define MARKER_START_INDEX 19
#define MARKER_START_SHIFT 26
#define MARKER_START_MASK 0x4000000

static inline css_error set_marker_start(css_computed_style *style, uint8_t
		type, lwc_string *string)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MARKER_START_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~MARKER_START_MASK) | (((uint32_t)type & 0x1) <<
			MARKER_START_SHIFT);
	
	lwc_string *old_string = style->i.marker_start;
	
	if (string != NULL) {
		style->i.marker_start = lwc_string_ref(string);
	} else {
		style->i.marker_start = NULL;
	}
	
	if (old_string != NULL)
		lwc_string_unref(old_string);
	
	return CSS_OK;
}
#undef MARKER_START_INDEX
#undef MARKER_START_SHIFT
#undef MARKER_START_MASK

#define MASK_INDEX 19
#define MASK_SHIFT 25
#define MASK_MASK 0x2000000

static inline css_error set_mask(css_computed_style *style, uint8_t type,
		lwc_string *string)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MASK_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~MASK_MASK) | (((uint32_t)type & 0x1) << MASK_SHIFT);
	
	lwc_string *old_string = style->i.mask;
	
	if (string != NULL) {
		style->i.mask = lwc_string_ref(string);
	} else {
		style->i.mask = NULL;
	}
	
	if (old_string != NULL)
		lwc_string_unref(old_string);
	
	return CSS_OK;
}
#undef MASK_INDEX
#undef MASK_SHIFT
#undef MASK_MASK

#define MAX_HEIGHT_INDEX 8
#define MAX_HEIGHT_SHIFT 11
#define MAX_HEIGHT_MASK 0x3f800

static inline css_error set_max_height(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MAX_HEIGHT_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~MAX_HEIGHT_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << MAX_HEIGHT_SHIFT);
	
	style->i.max_height = length;
	
	return CSS_OK;
}
#undef MAX_HEIGHT_INDEX
#undef MAX_HEIGHT_SHIFT
#undef MAX_HEIGHT_MASK

#define MAX_WIDTH_INDEX 4
#define MAX_WIDTH_SHIFT 25
#define MAX_WIDTH_MASK 0xfe000000

static inline css_error set_max_width(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MAX_WIDTH_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~MAX_WIDTH_MASK) | ((((uint32_t)type & 0x3) | (unit <<
			2)) << MAX_WIDTH_SHIFT);
	
	style->i.max_width = length;
	
	return CSS_OK;
}
#undef MAX_WIDTH_INDEX
#undef MAX_WIDTH_SHIFT
#undef MAX_WIDTH_MASK

#define MIN_HEIGHT_INDEX 16
#define MIN_HEIGHT_SHIFT 25
#define MIN_HEIGHT_MASK 0xfe000000

static inline css_error set_min_height(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MIN_HEIGHT_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~MIN_HEIGHT_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << MIN_HEIGHT_SHIFT);
	
	style->i.min_height = length;
	
	return CSS_OK;
}
#undef MIN_HEIGHT_INDEX
#undef MIN_HEIGHT_SHIFT
#undef MIN_HEIGHT_MASK

#define MIN_WIDTH_INDEX 3
#define MIN_WIDTH_SHIFT 11
#define MIN_WIDTH_MASK 0x3f800

static inline css_error set_min_width(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[MIN_WIDTH_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~MIN_WIDTH_MASK) | ((((uint32_t)type & 0x3) | (unit <<
			2)) << MIN_WIDTH_SHIFT);
	
	style->i.min_width = length;
	
	return CSS_OK;
}
#undef MIN_WIDTH_INDEX
#undef MIN_WIDTH_SHIFT
#undef MIN_WIDTH_MASK

#define OPACITY_INDEX 19
#define OPACITY_SHIFT 12
#define OPACITY_MASK 0x1000

static inline css_error set_opacity(css_computed_style *style, uint8_t type,
		css_fixed fixed)
{
	uint32_t *bits;
	
	bits = &style->i.bits[OPACITY_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~OPACITY_MASK) | (((uint32_t)type & 0x1) <<
			OPACITY_SHIFT);
	
	style->i.opacity = fixed;
	
	return CSS_OK;
}
#undef OPACITY_INDEX
#undef OPACITY_SHIFT
#undef OPACITY_MASK

#define ORDER_INDEX 17
#define ORDER_SHIFT 0
#define ORDER_MASK 0x1

static inline css_error set_order(css_computed_style *style, uint8_t type,
		int32_t integer)
{
	uint32_t *bits;
	
	bits = &style->i.bits[ORDER_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~ORDER_MASK) | (((uint32_t)type & 0x1) << ORDER_SHIFT);
	
	style->i.order = integer;
	
	return CSS_OK;
}
#undef ORDER_INDEX
#undef ORDER_SHIFT
#undef ORDER_MASK

#define ORPHANS_INDEX 19
#define ORPHANS_SHIFT 13
#define ORPHANS_MASK 0x2000

static inline css_error set_orphans(css_computed_style *style, uint8_t type,
		int32_t integer)
{
	uint32_t *bits;
	
	bits = &style->i.bits[ORPHANS_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~ORPHANS_MASK) | (((uint32_t)type & 0x1) <<
			ORPHANS_SHIFT);
	
	style->i.orphans = integer;
	
	return CSS_OK;
}
#undef ORPHANS_INDEX
#undef ORPHANS_SHIFT
#undef ORPHANS_MASK

#define OUTLINE_COLOR_INDEX 14
#define OUTLINE_COLOR_SHIFT 22
#define OUTLINE_COLOR_MASK 0xc00000

static inline css_error set_outline_color(css_computed_style *style, uint8_t
		type, css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[OUTLINE_COLOR_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~OUTLINE_COLOR_MASK) | (((uint32_t)type & 0x3) <<
			OUTLINE_COLOR_SHIFT);
	
	style->i.outline_color = color;
	
	return CSS_OK;
}
#undef OUTLINE_COLOR_INDEX
#undef OUTLINE_COLOR_SHIFT
#undef OUTLINE_COLOR_MASK

#define OUTLINE_STYLE_INDEX 10
#define OUTLINE_STYLE_SHIFT 24
#define OUTLINE_STYLE_MASK 0xf000000

static inline css_error set_outline_style(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[OUTLINE_STYLE_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~OUTLINE_STYLE_MASK) | (((uint32_t)type & 0xf) <<
			OUTLINE_STYLE_SHIFT);
	
	return CSS_OK;
}
#undef OUTLINE_STYLE_INDEX
#undef OUTLINE_STYLE_SHIFT
#undef OUTLINE_STYLE_MASK

#define OUTLINE_WIDTH_INDEX 0
#define OUTLINE_WIDTH_SHIFT 8
#define OUTLINE_WIDTH_MASK 0xff00

static inline css_error set_outline_width(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[OUTLINE_WIDTH_INDEX];
	
	/* 8bits: uuuuuttt : unit | type */
	*bits = (*bits & ~OUTLINE_WIDTH_MASK) | ((((uint32_t)type & 0x7) | (
			unit << 3)) << OUTLINE_WIDTH_SHIFT);
	
	style->i.outline_width = length;
	
	return CSS_OK;
}
#undef OUTLINE_WIDTH_INDEX
#undef OUTLINE_WIDTH_SHIFT
#undef OUTLINE_WIDTH_MASK

#define OVERFLOW_X_INDEX 13
#define OVERFLOW_X_SHIFT 26
#define OVERFLOW_X_MASK 0x1c000000

static inline css_error set_overflow_x(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[OVERFLOW_X_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~OVERFLOW_X_MASK) | (((uint32_t)type & 0x7) <<
			OVERFLOW_X_SHIFT);
	
	return CSS_OK;
}
#undef OVERFLOW_X_INDEX
#undef OVERFLOW_X_SHIFT
#undef OVERFLOW_X_MASK

#define OVERFLOW_Y_INDEX 13
#define OVERFLOW_Y_SHIFT 14
#define OVERFLOW_Y_MASK 0x1c000

static inline css_error set_overflow_y(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[OVERFLOW_Y_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~OVERFLOW_Y_MASK) | (((uint32_t)type & 0x7) <<
			OVERFLOW_Y_SHIFT);
	
	return CSS_OK;
}
#undef OVERFLOW_Y_INDEX
#undef OVERFLOW_Y_SHIFT
#undef OVERFLOW_Y_MASK

#define PADDING_BOTTOM_INDEX 16
#define PADDING_BOTTOM_SHIFT 7
#define PADDING_BOTTOM_MASK 0x1f80

static inline css_error set_padding_bottom(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[PADDING_BOTTOM_INDEX];
	
	/* 6bits: uuuuut : unit | type */
	*bits = (*bits & ~PADDING_BOTTOM_MASK) | ((((uint32_t)type & 0x1) | (
			unit << 1)) << PADDING_BOTTOM_SHIFT);
	
	style->i.padding_bottom = length;
	
	return CSS_OK;
}
#undef PADDING_BOTTOM_INDEX
#undef PADDING_BOTTOM_SHIFT
#undef PADDING_BOTTOM_MASK

#define PADDING_LEFT_INDEX 16
#define PADDING_LEFT_SHIFT 1
#define PADDING_LEFT_MASK 0x7e

static inline css_error set_padding_left(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[PADDING_LEFT_INDEX];
	
	/* 6bits: uuuuut : unit | type */
	*bits = (*bits & ~PADDING_LEFT_MASK) | ((((uint32_t)type & 0x1) | (unit
			<< 1)) << PADDING_LEFT_SHIFT);
	
	style->i.padding_left = length;
	
	return CSS_OK;
}
#undef PADDING_LEFT_INDEX
#undef PADDING_LEFT_SHIFT
#undef PADDING_LEFT_MASK

#define PADDING_RIGHT_INDEX 16
#define PADDING_RIGHT_SHIFT 13
#define PADDING_RIGHT_MASK 0x7e000

static inline css_error set_padding_right(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[PADDING_RIGHT_INDEX];
	
	/* 6bits: uuuuut : unit | type */
	*bits = (*bits & ~PADDING_RIGHT_MASK) | ((((uint32_t)type & 0x1) | (
			unit << 1)) << PADDING_RIGHT_SHIFT);
	
	style->i.padding_right = length;
	
	return CSS_OK;
}
#undef PADDING_RIGHT_INDEX
#undef PADDING_RIGHT_SHIFT
#undef PADDING_RIGHT_MASK

#define PADDING_TOP_INDEX 2
#define PADDING_TOP_SHIFT 0
#define PADDING_TOP_MASK 0x3f

static inline css_error set_padding_top(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[PADDING_TOP_INDEX];
	
	/* 6bits: uuuuut : unit | type */
	*bits = (*bits & ~PADDING_TOP_MASK) | ((((uint32_t)type & 0x1) | (unit
			<< 1)) << PADDING_TOP_SHIFT);
	
	style->i.padding_top = length;
	
	return CSS_OK;
}
#undef PADDING_TOP_INDEX
#undef PADDING_TOP_SHIFT
#undef PADDING_TOP_MASK

#define PAGE_BREAK_AFTER_INDEX 13
#define PAGE_BREAK_AFTER_SHIFT 2
#define PAGE_BREAK_AFTER_MASK 0x1c

static inline css_error set_page_break_after(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[PAGE_BREAK_AFTER_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~PAGE_BREAK_AFTER_MASK) | (((uint32_t)type & 0x7) <<
			PAGE_BREAK_AFTER_SHIFT);
	
	return CSS_OK;
}
#undef PAGE_BREAK_AFTER_INDEX
#undef PAGE_BREAK_AFTER_SHIFT
#undef PAGE_BREAK_AFTER_MASK

#define PAGE_BREAK_BEFORE_INDEX 13
#define PAGE_BREAK_BEFORE_SHIFT 20
#define PAGE_BREAK_BEFORE_MASK 0x700000

static inline css_error set_page_break_before(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[PAGE_BREAK_BEFORE_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~PAGE_BREAK_BEFORE_MASK) | (((uint32_t)type & 0x7) <<
			PAGE_BREAK_BEFORE_SHIFT);
	
	return CSS_OK;
}
#undef PAGE_BREAK_BEFORE_INDEX
#undef PAGE_BREAK_BEFORE_SHIFT
#undef PAGE_BREAK_BEFORE_MASK

#define PAGE_BREAK_INSIDE_INDEX 18
#define PAGE_BREAK_INSIDE_SHIFT 16
#define PAGE_BREAK_INSIDE_MASK 0x30000

static inline css_error set_page_break_inside(css_computed_style *style,
		uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[PAGE_BREAK_INSIDE_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~PAGE_BREAK_INSIDE_MASK) | (((uint32_t)type & 0x3) <<
			PAGE_BREAK_INSIDE_SHIFT);
	
	return CSS_OK;
}
#undef PAGE_BREAK_INSIDE_INDEX
#undef PAGE_BREAK_INSIDE_SHIFT
#undef PAGE_BREAK_INSIDE_MASK

#define POSITION_INDEX 14
#define POSITION_SHIFT 29
#define POSITION_MASK 0xe0000000

static inline css_error set_position(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[POSITION_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~POSITION_MASK) | (((uint32_t)type & 0x7) <<
			POSITION_SHIFT);
	
	return CSS_OK;
}
#undef POSITION_INDEX
#undef POSITION_SHIFT
#undef POSITION_MASK

#define QUOTES_INDEX 19
#define QUOTES_SHIFT 22
#define QUOTES_MASK 0x400000

static inline css_error set_quotes(css_computed_style *style, uint8_t type,
		lwc_string **string_arr)
{
	uint32_t *bits;
	
	bits = &style->i.bits[QUOTES_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~QUOTES_MASK) | (((uint32_t)type & 0x1) <<
			QUOTES_SHIFT);
	
	lwc_string **old_string_arr = style->quotes;
	lwc_string **s;
	
	for (s = string_arr; s != NULL && *s != NULL; s++)
		*s = lwc_string_ref(*s);
	
	style->quotes = string_arr;
	
	/* Free existing array */
	if (old_string_arr != NULL) {
		for (s = old_string_arr; *s != NULL; s++)
			lwc_string_unref(*s);
		
		if (old_string_arr != string_arr)
			free(old_string_arr);
	}
	
	return CSS_OK;
}
#undef QUOTES_INDEX
#undef QUOTES_SHIFT
#undef QUOTES_MASK

#define RIGHT_INDEX 7
#define RIGHT_SHIFT 25
#define RIGHT_MASK 0xfe000000

static inline css_error set_right(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[RIGHT_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~RIGHT_MASK) | ((((uint32_t)type & 0x3) | (unit << 2))
			<< RIGHT_SHIFT);
	
	style->i.right = length;
	
	return CSS_OK;
}
#undef RIGHT_INDEX
#undef RIGHT_SHIFT
#undef RIGHT_MASK

#define SHAPE_RENDERING_INDEX 11
#define SHAPE_RENDERING_SHIFT 22
#define SHAPE_RENDERING_MASK 0x7c00000

static inline css_error set_shape_rendering(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[SHAPE_RENDERING_INDEX];
	
	/* 5bits: ttttt : type */
	*bits = (*bits & ~SHAPE_RENDERING_MASK) | (((uint32_t)type & 0x1f) <<
			SHAPE_RENDERING_SHIFT);
	
	return CSS_OK;
}
#undef SHAPE_RENDERING_INDEX
#undef SHAPE_RENDERING_SHIFT
#undef SHAPE_RENDERING_MASK

#define STOP_COLOR_INDEX 19
#define STOP_COLOR_SHIFT 27
#define STOP_COLOR_MASK 0x8000000

static inline css_error set_stop_color(css_computed_style *style, uint8_t type,
		css_color color)
{
	uint32_t *bits;
	
	bits = &style->i.bits[STOP_COLOR_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~STOP_COLOR_MASK) | (((uint32_t)type & 0x1) <<
			STOP_COLOR_SHIFT);
	
	style->i.stop_color = color;
	
	return CSS_OK;
}
#undef STOP_COLOR_INDEX
#undef STOP_COLOR_SHIFT
#undef STOP_COLOR_MASK

#define STOP_OPACITY_INDEX 19
#define STOP_OPACITY_SHIFT 31
#define STOP_OPACITY_MASK 0x80000000

static inline css_error set_stop_opacity(css_computed_style *style, uint8_t
		type, css_fixed fixed)
{
	uint32_t *bits;
	
	bits = &style->i.bits[STOP_OPACITY_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~STOP_OPACITY_MASK) | (((uint32_t)type & 0x1) <<
			STOP_OPACITY_SHIFT);
	
	style->i.stop_opacity = fixed;
	
	return CSS_OK;
}
#undef STOP_OPACITY_INDEX
#undef STOP_OPACITY_SHIFT
#undef STOP_OPACITY_MASK

#define STROKE_INDEX 13
#define STROKE_SHIFT 17
#define STROKE_MASK 0xe0000
static inline css_error set_stroke(css_computed_style *style, uint8_t type,
        lwc_string *string, css_color color)
{
    uint32_t *bits;

    bits = &style->i.bits[STROKE_INDEX];

    /* 3bits: ttt : type */
    *bits = (*bits & ~STROKE_MASK) | (((uint32_t)type & 0x7) << STROKE_SHIFT);

    lwc_string *old_string = style->i.stroke;

    if (string != NULL) {
        style->i.stroke = lwc_string_ref(string);
    } else {
        style->i.stroke = NULL;
    }

    if (old_string != NULL)
        lwc_string_unref(old_string);

    style->i.stroke_color = color;

    return CSS_OK;
}
#undef STROKE_INDEX
#undef STROKE_SHIFT
#undef STROKE_MASK

#define STROKE_DASHARRAY_INDEX 13
#define STROKE_DASHARRAY_SHIFT 0
#define STROKE_DASHARRAY_MASK 0x3
static inline css_error set_stroke_dasharray(css_computed_style *style, uint8_t type, size_t size, css_fixed *values,
                css_unit *units)
{
    uint32_t *bits;

    bits = &style->i.bits[STROKE_DASHARRAY_INDEX];

    /* 2bits: tt : type */
    *bits = (*bits & ~STROKE_DASHARRAY_MASK) | (((uint32_t)type & 0x3) <<
                    STROKE_DASHARRAY_SHIFT);

    style->i.stroke_dasharray_size = size;

    if (size == 0 || values == NULL || units == NULL)
    {
        return CSS_OK;
    }

    style->i.stroke_dasharray = (css_fixed*) malloc(size * sizeof(css_fixed));
    style->i.stroke_dasharray_unit = (css_unit*) malloc(size *sizeof(css_unit));
    for (int i = 0; i < size; i++)
    {
        style->i.stroke_dasharray[i] = values[i];
        style->i.stroke_dasharray_unit[i] = units[i];
    }
    return CSS_OK;
}
#undef STROKE_DASHARRAY_INDEX
#undef STROKE_DASHARRAY_SHIFT
#undef STROKE_DASHARRAY_MASK

#define STROKE_DASHOFFSET_INDEX 9
#define STROKE_DASHOFFSET_SHIFT 18
#define STROKE_DASHOFFSET_MASK 0x1fc0000

static inline css_error set_stroke_dashoffset(css_computed_style *style,
		uint8_t type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[STROKE_DASHOFFSET_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~STROKE_DASHOFFSET_MASK) | ((((uint32_t)type & 0x3) | (
			unit << 2)) << STROKE_DASHOFFSET_SHIFT);
	
	style->i.stroke_dashoffset = length;
	
	return CSS_OK;
}
#undef STROKE_DASHOFFSET_INDEX
#undef STROKE_DASHOFFSET_SHIFT
#undef STROKE_DASHOFFSET_MASK

#define STROKE_LINECAP_INDEX 10
#define STROKE_LINECAP_SHIFT 0
#define STROKE_LINECAP_MASK 0xf

static inline css_error set_stroke_linecap(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[STROKE_LINECAP_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~STROKE_LINECAP_MASK) | (((uint32_t)type & 0xf) <<
			STROKE_LINECAP_SHIFT);
	
	return CSS_OK;
}
#undef STROKE_LINECAP_INDEX
#undef STROKE_LINECAP_SHIFT
#undef STROKE_LINECAP_MASK

#define STROKE_LINEJOIN_INDEX 9
#define STROKE_LINEJOIN_SHIFT 0
#define STROKE_LINEJOIN_MASK 0xf

static inline css_error set_stroke_linejoin(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[STROKE_LINEJOIN_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~STROKE_LINEJOIN_MASK) | (((uint32_t)type & 0xf) <<
			STROKE_LINEJOIN_SHIFT);
	
	return CSS_OK;
}
#undef STROKE_LINEJOIN_INDEX
#undef STROKE_LINEJOIN_SHIFT
#undef STROKE_LINEJOIN_MASK

#define STROKE_MITERLIMIT_INDEX 19
#define STROKE_MITERLIMIT_SHIFT 29
#define STROKE_MITERLIMIT_MASK 0x20000000

static inline css_error set_stroke_miterlimit(css_computed_style *style,
		uint8_t type, css_fixed fixed)
{
	uint32_t *bits;
	
	bits = &style->i.bits[STROKE_MITERLIMIT_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~STROKE_MITERLIMIT_MASK) | (((uint32_t)type & 0x1) <<
			STROKE_MITERLIMIT_SHIFT);
	
	style->i.stroke_miterlimit = fixed;
	
	return CSS_OK;
}
#undef STROKE_MITERLIMIT_INDEX
#undef STROKE_MITERLIMIT_SHIFT
#undef STROKE_MITERLIMIT_MASK

#define STROKE_OPACITY_INDEX 18
#define STROKE_OPACITY_SHIFT 1
#define STROKE_OPACITY_MASK 0x2

static inline css_error set_stroke_opacity(css_computed_style *style, uint8_t
		type, css_fixed fixed)
{
	uint32_t *bits;
	
	bits = &style->i.bits[STROKE_OPACITY_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~STROKE_OPACITY_MASK) | (((uint32_t)type & 0x1) <<
			STROKE_OPACITY_SHIFT);
	
	style->i.stroke_opacity = fixed;
	
	return CSS_OK;
}
#undef STROKE_OPACITY_INDEX
#undef STROKE_OPACITY_SHIFT
#undef STROKE_OPACITY_MASK

#define STROKE_WIDTH_INDEX 9
#define STROKE_WIDTH_SHIFT 11
#define STROKE_WIDTH_MASK 0x3f800

static inline css_error set_stroke_width(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[STROKE_WIDTH_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~STROKE_WIDTH_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << STROKE_WIDTH_SHIFT);
	
	style->i.stroke_width = length;
	
	return CSS_OK;
}
#undef STROKE_WIDTH_INDEX
#undef STROKE_WIDTH_SHIFT
#undef STROKE_WIDTH_MASK

#define TABLE_LAYOUT_INDEX 18
#define TABLE_LAYOUT_SHIFT 26
#define TABLE_LAYOUT_MASK 0xc000000

static inline css_error set_table_layout(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TABLE_LAYOUT_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~TABLE_LAYOUT_MASK) | (((uint32_t)type & 0x3) <<
			TABLE_LAYOUT_SHIFT);
	
	return CSS_OK;
}
#undef TABLE_LAYOUT_INDEX
#undef TABLE_LAYOUT_SHIFT
#undef TABLE_LAYOUT_MASK

#define TEXT_ALIGN_INDEX 6
#define TEXT_ALIGN_SHIFT 0
#define TEXT_ALIGN_MASK 0xf

static inline css_error set_text_align(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TEXT_ALIGN_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~TEXT_ALIGN_MASK) | (((uint32_t)type & 0xf) <<
			TEXT_ALIGN_SHIFT);
	
	return CSS_OK;
}
#undef TEXT_ALIGN_INDEX
#undef TEXT_ALIGN_SHIFT
#undef TEXT_ALIGN_MASK

#define TEXT_ALIGN_LAST_INDEX 5
#define TEXT_ALIGN_LAST_SHIFT 0
#define TEXT_ALIGN_LAST_MASK 0xf

static inline css_error set_text_align_last(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TEXT_ALIGN_LAST_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~TEXT_ALIGN_LAST_MASK) | (((uint32_t)type & 0xf) <<
			TEXT_ALIGN_LAST_SHIFT);
	
	return CSS_OK;
}
#undef TEXT_ALIGN_LAST_INDEX
#undef TEXT_ALIGN_LAST_SHIFT
#undef TEXT_ALIGN_LAST_MASK

#define TEXT_ANCHOR_INDEX 10
#define TEXT_ANCHOR_SHIFT 28
#define TEXT_ANCHOR_MASK 0xf0000000

static inline css_error set_text_anchor(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TEXT_ANCHOR_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~TEXT_ANCHOR_MASK) | (((uint32_t)type & 0xf) <<
			TEXT_ANCHOR_SHIFT);
	
	return CSS_OK;
}
#undef TEXT_ANCHOR_INDEX
#undef TEXT_ANCHOR_SHIFT
#undef TEXT_ANCHOR_MASK

#define TEXT_DECORATION_INDEX 11
#define TEXT_DECORATION_SHIFT 17
#define TEXT_DECORATION_MASK 0x3e0000

static inline css_error set_text_decoration(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TEXT_DECORATION_INDEX];
	
	/* 5bits: ttttt : type */
	*bits = (*bits & ~TEXT_DECORATION_MASK) | (((uint32_t)type & 0x1f) <<
			TEXT_DECORATION_SHIFT);
	
	return CSS_OK;
}
#undef TEXT_DECORATION_INDEX
#undef TEXT_DECORATION_SHIFT
#undef TEXT_DECORATION_MASK

#define TEXT_INDENT_INDEX 16
#define TEXT_INDENT_SHIFT 19
#define TEXT_INDENT_MASK 0x1f80000

static inline css_error set_text_indent(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TEXT_INDENT_INDEX];
	
	/* 6bits: uuuuut : unit | type */
	*bits = (*bits & ~TEXT_INDENT_MASK) | ((((uint32_t)type & 0x1) | (unit
			<< 1)) << TEXT_INDENT_SHIFT);
	
	style->i.text_indent = length;
	
	return CSS_OK;
}
#undef TEXT_INDENT_INDEX
#undef TEXT_INDENT_SHIFT
#undef TEXT_INDENT_MASK

#define TEXT_JUSTIFY_INDEX 10
#define TEXT_JUSTIFY_SHIFT 4
#define TEXT_JUSTIFY_MASK 0xf0

static inline css_error set_text_justify(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TEXT_JUSTIFY_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~TEXT_JUSTIFY_MASK) | (((uint32_t)type & 0xf) <<
			TEXT_JUSTIFY_SHIFT);
	
	return CSS_OK;
}
#undef TEXT_JUSTIFY_INDEX
#undef TEXT_JUSTIFY_SHIFT
#undef TEXT_JUSTIFY_MASK

#define TEXT_OVERFLOW_INDEX 14
#define TEXT_OVERFLOW_SHIFT 18
#define TEXT_OVERFLOW_MASK 0xc0000

static inline css_error set_text_overflow(css_computed_style *style, uint8_t
		type, lwc_string *string)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TEXT_OVERFLOW_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~TEXT_OVERFLOW_MASK) | (((uint32_t)type & 0x3) <<
			TEXT_OVERFLOW_SHIFT);
	
	lwc_string *old_string = style->i.text_overflow;
	
	if (string != NULL) {
		style->i.text_overflow = lwc_string_ref(string);
	} else {
		style->i.text_overflow = NULL;
	}
	
	if (old_string != NULL)
		lwc_string_unref(old_string);
	
	return CSS_OK;
}
#undef TEXT_OVERFLOW_INDEX
#undef TEXT_OVERFLOW_SHIFT
#undef TEXT_OVERFLOW_MASK

#define TEXT_RENDERING_INDEX 12
#define TEXT_RENDERING_SHIFT 20
#define TEXT_RENDERING_MASK 0xf00000

static inline css_error set_text_rendering(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TEXT_RENDERING_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~TEXT_RENDERING_MASK) | (((uint32_t)type & 0xf) <<
			TEXT_RENDERING_SHIFT);
	
	return CSS_OK;
}
#undef TEXT_RENDERING_INDEX
#undef TEXT_RENDERING_SHIFT
#undef TEXT_RENDERING_MASK

#define TEXT_SHADOW_INDEX 11
#define TEXT_SHADOW_SHIFT 7
#define TEXT_SHADOW_MASK 0xf80
static inline css_error set_text_shadow(css_computed_style *style, uint8_t type,
        css_fixed text_shadow_h, css_unit text_shadow_h_unit,
        css_fixed text_shadow_v, css_unit text_shadow_v_unit,
        css_fixed text_shadow_blur, css_unit text_shadow_blur_unit, 
        css_color text_shadow_color)
{
        uint32_t *bits;
        
        bits = &style->i.bits[TEXT_SHADOW_INDEX];
        
        /* 5bits: ttttt : type */
        *bits = (*bits & ~TEXT_SHADOW_MASK) | (((uint32_t)type & 0x1f) <<
                        TEXT_SHADOW_SHIFT);

        style->i.text_shadow_h = text_shadow_h;
        style->i.text_shadow_h_unit = text_shadow_h_unit;
        style->i.text_shadow_v = text_shadow_v;
        style->i.text_shadow_v_unit = text_shadow_v_unit;
        style->i.text_shadow_blur = text_shadow_blur;
        style->i.text_shadow_blur_unit = text_shadow_blur_unit;
        style->i.text_shadow_color = text_shadow_color;
        
        return CSS_OK;
}
#undef TEXT_SHADOW_INDEX
#undef TEXT_SHADOW_SHIFT
#undef TEXT_SHADOW_MASK

#define TEXT_TRANSFORM_INDEX 12
#define TEXT_TRANSFORM_SHIFT 5
#define TEXT_TRANSFORM_MASK 0xe0

static inline css_error set_text_transform(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TEXT_TRANSFORM_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~TEXT_TRANSFORM_MASK) | (((uint32_t)type & 0x7) <<
			TEXT_TRANSFORM_SHIFT);
	
	return CSS_OK;
}
#undef TEXT_TRANSFORM_INDEX
#undef TEXT_TRANSFORM_SHIFT
#undef TEXT_TRANSFORM_MASK

#define TOP_INDEX 9
#define TOP_SHIFT 25
#define TOP_MASK 0xfe000000

static inline css_error set_top(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[TOP_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~TOP_MASK) | ((((uint32_t)type & 0x3) | (unit << 2))
			<< TOP_SHIFT);
	
	style->i.top = length;
	
	return CSS_OK;
}
#undef TOP_INDEX
#undef TOP_SHIFT
#undef TOP_MASK

#define UNICODE_BIDI_INDEX 11
#define UNICODE_BIDI_SHIFT 27
#define UNICODE_BIDI_MASK 0xf8000000

static inline css_error set_unicode_bidi(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[UNICODE_BIDI_INDEX];
	
	/* 5bits: ttttt : type */
	*bits = (*bits & ~UNICODE_BIDI_MASK) | (((uint32_t)type & 0x1f) <<
			UNICODE_BIDI_SHIFT);
	
	return CSS_OK;
}
#undef UNICODE_BIDI_INDEX
#undef UNICODE_BIDI_SHIFT
#undef UNICODE_BIDI_MASK

#define VERTICAL_ALIGN_INDEX 15
#define VERTICAL_ALIGN_SHIFT 1
#define VERTICAL_ALIGN_MASK 0x3fe

static inline css_error set_vertical_align(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[VERTICAL_ALIGN_INDEX];
	
	/* 9bits: uuuuutttt : unit | type */
	*bits = (*bits & ~VERTICAL_ALIGN_MASK) | ((((uint32_t)type & 0xf) | (
			unit << 4)) << VERTICAL_ALIGN_SHIFT);
	
	style->i.vertical_align = length;
	
	return CSS_OK;
}
#undef VERTICAL_ALIGN_INDEX
#undef VERTICAL_ALIGN_SHIFT
#undef VERTICAL_ALIGN_MASK

#define VISIBILITY_INDEX 18
#define VISIBILITY_SHIFT 2
#define VISIBILITY_MASK 0xc

static inline css_error set_visibility(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[VISIBILITY_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~VISIBILITY_MASK) | (((uint32_t)type & 0x3) <<
			VISIBILITY_SHIFT);
	
	return CSS_OK;
}
#undef VISIBILITY_INDEX
#undef VISIBILITY_SHIFT
#undef VISIBILITY_MASK

#define WHITE_SPACE_INDEX 13
#define WHITE_SPACE_SHIFT 23
#define WHITE_SPACE_MASK 0x3800000

static inline css_error set_white_space(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[WHITE_SPACE_INDEX];
	
	/* 3bits: ttt : type */
	*bits = (*bits & ~WHITE_SPACE_MASK) | (((uint32_t)type & 0x7) <<
			WHITE_SPACE_SHIFT);
	
	return CSS_OK;
}
#undef WHITE_SPACE_INDEX
#undef WHITE_SPACE_SHIFT
#undef WHITE_SPACE_MASK

#define WIDOWS_INDEX 19
#define WIDOWS_SHIFT 17
#define WIDOWS_MASK 0x20000

static inline css_error set_widows(css_computed_style *style, uint8_t type,
		int32_t integer)
{
	uint32_t *bits;
	
	bits = &style->i.bits[WIDOWS_INDEX];
	
	/* 1bit: t : type */
	*bits = (*bits & ~WIDOWS_MASK) | (((uint32_t)type & 0x1) <<
			WIDOWS_SHIFT);
	
	style->i.widows = integer;
	
	return CSS_OK;
}
#undef WIDOWS_INDEX
#undef WIDOWS_SHIFT
#undef WIDOWS_MASK

#define WIDTH_INDEX 3
#define WIDTH_SHIFT 18
#define WIDTH_MASK 0x1fc0000

static inline css_error set_width(css_computed_style *style, uint8_t type,
		css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[WIDTH_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~WIDTH_MASK) | ((((uint32_t)type & 0x3) | (unit << 2))
			<< WIDTH_SHIFT);
	
	style->i.width = length;
	
	return CSS_OK;
}
#undef WIDTH_INDEX
#undef WIDTH_SHIFT
#undef WIDTH_MASK

#define WORD_BREAK_INDEX 17
#define WORD_BREAK_SHIFT 1
#define WORD_BREAK_MASK 0x1e

static inline css_error set_word_break(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[WORD_BREAK_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~WORD_BREAK_MASK) | (((uint32_t)type & 0xf) <<
			WORD_BREAK_SHIFT);
	
	return CSS_OK;
}
#undef WORD_BREAK_INDEX
#undef WORD_BREAK_SHIFT
#undef WORD_BREAK_MASK

#define WORD_SPACING_INDEX 6
#define WORD_SPACING_SHIFT 18
#define WORD_SPACING_MASK 0x1fc0000

static inline css_error set_word_spacing(css_computed_style *style, uint8_t
		type, css_fixed length, css_unit unit)
{
	uint32_t *bits;
	
	bits = &style->i.bits[WORD_SPACING_INDEX];
	
	/* 7bits: uuuuutt : unit | type */
	*bits = (*bits & ~WORD_SPACING_MASK) | ((((uint32_t)type & 0x3) | (unit
			<< 2)) << WORD_SPACING_SHIFT);
	
	style->i.word_spacing = length;
	
	return CSS_OK;
}
#undef WORD_SPACING_INDEX
#undef WORD_SPACING_SHIFT
#undef WORD_SPACING_MASK

#define WORD_WRAP_INDEX 12
#define WORD_WRAP_SHIFT 24
#define WORD_WRAP_MASK 0xf000000

static inline css_error set_word_wrap(css_computed_style *style, uint8_t type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[WORD_WRAP_INDEX];
	
	/* 4bits: tttt : type */
	*bits = (*bits & ~WORD_WRAP_MASK) | (((uint32_t)type & 0xf) <<
			WORD_WRAP_SHIFT);
	
	return CSS_OK;
}
#undef WORD_WRAP_INDEX
#undef WORD_WRAP_SHIFT
#undef WORD_WRAP_MASK

#define WRITING_MODE_INDEX 18
#define WRITING_MODE_SHIFT 30
#define WRITING_MODE_MASK 0xc0000000

static inline css_error set_writing_mode(css_computed_style *style, uint8_t
		type)
{
	uint32_t *bits;
	
	bits = &style->i.bits[WRITING_MODE_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~WRITING_MODE_MASK) | (((uint32_t)type & 0x3) <<
			WRITING_MODE_SHIFT);
	
	return CSS_OK;
}
#undef WRITING_MODE_INDEX
#undef WRITING_MODE_SHIFT
#undef WRITING_MODE_MASK

#define Z_INDEX_INDEX 18
#define Z_INDEX_SHIFT 18
#define Z_INDEX_MASK 0xc0000

static inline css_error set_z_index(css_computed_style *style, uint8_t type,
		int32_t integer)
{
	uint32_t *bits;
	
	bits = &style->i.bits[Z_INDEX_INDEX];
	
	/* 2bits: tt : type */
	*bits = (*bits & ~Z_INDEX_MASK) | (((uint32_t)type & 0x3) <<
			Z_INDEX_SHIFT);
	
	style->i.z_index = integer;
	
	return CSS_OK;
}
#undef Z_INDEX_INDEX
#undef Z_INDEX_SHIFT
#undef Z_INDEX_MASK
