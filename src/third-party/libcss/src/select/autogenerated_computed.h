/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 The NetSurf Project
 */


struct css_computed_style_i {
/*
 * Property                       Size (bits)     Size (bytes)
 * ---                            ---             ---
 * align_content                    3             
 * align_items                      3             
 * align_self                       3             
 * background_attachment            2             
 * background_color                 2               4
 * background_image                 1             sizeof(ptr)
 * background_position              1 + 10          8
 * background_repeat                3             
 * baseline_shift                   4             
 * border_bottom_color              2               4
 * border_bottom_left_radius        2 + 5           4
 * border_bottom_right_radius       2 + 5           4
 * border_bottom_style              4             
 * border_bottom_width              3 + 5           4
 * border_collapse                  2             
 * border_left_color                2               4
 * border_left_style                4             
 * border_left_width                3 + 5           4
 * border_right_color               2               4
 * border_right_style               4             
 * border_right_width               3 + 5           4
 * border_spacing                   1 + 10          8
 * border_top_color                 2               4
 * border_top_left_radius           2 + 5           4
 * border_top_right_radius          2 + 5           4
 * border_top_style                 4             
 * border_top_width                 3 + 5           4
 * bottom                           2 + 5           4
 * box_sizing                       2             
 * break_after                      4             
 * break_before                     4             
 * break_inside                     4             
 * caption_side                     2             
 * clear                            3             
 * clip                             6 + 20         16
 * clip_path                        1             sizeof(ptr)
 * clip_rule                        4             
 * color                            1               4
 * column_count                     2               4
 * column_fill                      2             
 * column_gap                       2 + 5           4
 * column_rule_color                2               4
 * column_rule_style                4             
 * column_rule_width                3 + 5           4
 * column_span                      2             
 * column_width                     2 + 5           4
 * comp_op                          5             
 * direction                        2             
 * display                          5             
 * empty_cells                      2             
 * enable_background                5             
 * fill                             3             
 * fill_opacity                     1               4
 * fill_rule                        3             
 * filter                           1             sizeof(ptr)
 * flex_basis                       2 + 5           4
 * flex_direction                   3             
 * flex_grow                        1               4
 * flex_shrink                      1               4
 * flex_wrap                        2             
 * float                            2             
 * flood_color                      1               4
 * flood_opacity                    1               4
 * font_size                        4 + 5           4
 * font_stretch                     5             
 * font_style                       2             
 * font_variant                     2             
 * font_weight                      4             
 * grid_column_end                  2 + 5           4
 * grid_column_start                2 + 5           4
 * grid_row_end                     2 + 5           4
 * grid_row_start                   2 + 5           4
 * grid_template_columns            2             
 * grid_template_rows               2             
 * height                           2 + 5           4
 * justify_content                  3             
 * left                             2 + 5           4
 * letter_spacing                   2 + 5           4
 * line_height                      2 + 5           4
 * list_style_image                 1             sizeof(ptr)
 * list_style_position              2             
 * list_style_type                  4             
 * margin_bottom                    2 + 5           4
 * margin_left                      2 + 5           4
 * margin_right                     2 + 5           4
 * margin_top                       2 + 5           4
 * marker_end                       1             sizeof(ptr)
 * marker_mid                       1             sizeof(ptr)
 * marker_start                     1             sizeof(ptr)
 * mask                             1             sizeof(ptr)
 * max_height                       2 + 5           4
 * max_width                        2 + 5           4
 * min_height                       2 + 5           4
 * min_width                        2 + 5           4
 * opacity                          1               4
 * order                            1               4
 * orphans                          1               4
 * outline_color                    2               4
 * outline_style                    4             
 * outline_width                    3 + 5           4
 * overflow_x                       3             
 * overflow_y                       3             
 * padding_bottom                   1 + 5           4
 * padding_left                     1 + 5           4
 * padding_right                    1 + 5           4
 * padding_top                      1 + 5           4
 * page_break_after                 3             
 * page_break_before                3             
 * page_break_inside                2             
 * position                         3             
 * right                            2 + 5           4
 * shape_rendering                  5             
 * stop_color                       1               4
 * stop_opacity                     1               4
 * stroke                           3             
 * stroke_dasharray                 2             
 * stroke_dashoffset                2 + 5           4
 * stroke_linecap                   4             
 * stroke_linejoin                  4             
 * stroke_miterlimit                1               4
 * stroke_opacity                   1               4
 * stroke_width                     2 + 5           4
 * table_layout                     2             
 * text_align                       4             
 * text_align_last                  4             
 * text_anchor                      4             
 * text_decoration                  5             
 * text_indent                      1 + 5           4
 * text_justify                     4             
 * text_overflow                    2             sizeof(ptr)
 * text_rendering                   4             
 * text_shadow                      5             
 * text_transform                   3             
 * top                              2 + 5           4
 * unicode_bidi                     5             
 * vertical_align                   4 + 5           4
 * visibility                       2             
 * white_space                      3             
 * widows                           1               4
 * width                            2 + 5           4
 * word_break                       4             
 * word_spacing                     2 + 5           4
 * word_wrap                        4             
 * writing_mode                     2             
 * z_index                          2               4
 * 
 * Encode content as an array of content items, terminated with a blank entry.
 * 
 * content                          2             sizeof(ptr)
 * 
 * Encode counter_increment as an array of name, value pairs, terminated with a
 * blank entry.
 * 
 * counter_increment                1             sizeof(ptr)
 * 
 * Encode counter_reset as an array of name, value pairs, terminated with a
 * blank entry.
 * 
 * counter_reset                    1             sizeof(ptr)
 * 
 * Encode cursor uri(s) as an array of string objects, terminated with a blank
 * entry
 * 
 * cursor                           5             sizeof(ptr)
 * 
 * Encode font family as an array of string objects, terminated with a blank
 * entry.
 * 
 * font_family                      3             sizeof(ptr)
 * 
 * Encode quotes as an array of string objects, terminated with a blank entry.
 * 
 * quotes                           1             sizeof(ptr)
 * 
 * ---                            ---             ---
 *                                628 bits        296 + 15sizeof(ptr) bytes
 *                                ===================
 *                                375 + 15sizeof(ptr) bytes
 * 
 * Bit allocations:
 * 
 * 0  bbbbbbbboooooooouuuuuuuurrrrrrrr
 * border_right_width; border_bottom_width; outline_width; border_left_width
 * 
 * 1  fffffffffbbbbbbbbccccccccooooooo
 * font_size; border_top_width; column_rule_width; border_top_right_radius
 * 
 * 2  ccccccccccccccccccccccccccpppppp
 * clip; padding_top
 * 
 * 3  lllllllwwwwwwwmmmmmmmgggggggcccc
 * left; width; min_width; grid_column_start; column_rule_style
 * 
 * 4  mmmmmmmbbbbbbbaaaaaaaooooooollll
 * max_width; bottom; margin_top; border_top_left_radius; list_style_type
 * 
 * 5  bbbbbbbmmmmmmmcccccccgggggggtttt
 * border_bottom_left_radius; margin_left; column_width; grid_column_end;
 * text_align_last
 * 
 * 6  gggggggwwwwwwwbbbbbbbllllllltttt
 * grid_row_end; word_spacing; border_bottom_right_radius; letter_spacing;
 * text_align
 * 
 * 7  rrrrrrrgggggggmmmmmmmcccccccbbbb
 * right; grid_row_start; margin_right; column_gap; break_before
 * 
 * 8  fffffffmmmmmmmaaaaaaallllllloooo
 * flex_basis; margin_bottom; max_height; line_height; font_weight
 * 
 * 9  tttttttsssssssrrrrrrrhhhhhhhoooo
 * top; stroke_dashoffset; stroke_width; height; stroke_linejoin
 * 
 * 10 ttttooooccccbbbbrrrrddddeeeessss
 * text_anchor; outline_style; clip_rule; border_top_style; border_right_style;
 * border_left_style; text_justify; stroke_linecap
 * 
 * 11 uuuuussssstttttfffffeeeeecccccbb
 * unicode_bidi; shape_rendering; text_decoration; font_stretch; text_shadow;
 * comp_op; border_right_color
 * 
 * 12 bbbbwwwwttttfffcccaaallleeekkkgg
 * break_inside; word_wrap; text_rendering; flex_direction; clear; align_items;
 * align_content; text_transform; background_repeat; grid_template_columns
 * 
 * 13 aaaooowwwpppsssvvvjjjfffiiigggtt
 * align_self; overflow_x; white_space; page_break_before; stroke; overflow_y;
 * justify_content; fill_rule; fill; page_break_after; stroke_dasharray
 * 
 * 14 pppfffbboorrttllnnddiicceeBBssuu
 * position; font_family; background_color; outline_color; border_collapse;
 * text_overflow; flex_wrap; font_variant; border_top_color; direction;
 * caption_side; empty_cells; border_left_color; font_style; column_count
 * 
 * 15 bbbbbbbbbbbooooooooooovvvvvvvvvm
 * background_position; border_spacing; vertical_align; marker_mid
 * 
 * 16 mmmmmmmttttttppppppaaaaaaddddddc
 * min_height; text_indent; padding_right; padding_bottom; padding_left;
 * clip_path
 * 
 * 17 dddddccccceeeeebbbbaaaaoooowwwwr
 * display; cursor; enable_background; break_after; baseline_shift;
 * border_bottom_style; word_break; order
 * 
 * 18 wwccttlloobbzzppuuggmmffrraavvsn
 * writing_mode; content; table_layout; list_style_position; column_rule_color;
 * box_sizing; z_index; page_break_inside; column_span; grid_template_rows;
 * column_fill; float; border_bottom_color; background_attachment; visibility;
 * stroke_opacity; counter_reset
 * 
 * 19 sbtfomailqedpcwurChy............
 * stop_opacity; background_image; stroke_miterlimit; flex_grow; stop_color;
 * marker_start; mask; filter; list_style_image; quotes; flex_shrink;
 * flood_opacity; fill_opacity; flood_color; widows; counter_increment;
 * marker_end; color; orphans; opacity
 */
	uint32_t bits[20];
	
	css_color background_color;
	lwc_string *background_image;
	css_fixed background_position_a;
	css_fixed background_position_b;
	css_color border_bottom_color;
	css_fixed border_bottom_left_radius;
	css_fixed border_bottom_right_radius;
	css_fixed border_bottom_width;
	css_color border_left_color;
	css_fixed border_left_width;
	css_color border_right_color;
	css_fixed border_right_width;
	css_fixed border_spacing_a;
	css_fixed border_spacing_b;
	css_color border_top_color;
	css_fixed border_top_left_radius;
	css_fixed border_top_right_radius;
	css_fixed border_top_width;
	css_fixed bottom;
	css_fixed clip_a;
	css_fixed clip_b;
	css_fixed clip_c;
	css_fixed clip_d;
	lwc_string *clip_path;
	css_color color;
	int32_t column_count;
	css_fixed column_gap;
	css_color column_rule_color;
	css_fixed column_rule_width;
	css_fixed column_width;
	css_fixed fill_opacity;
	lwc_string *filter;
	css_fixed flex_basis;
	css_fixed flex_grow;
	css_fixed flex_shrink;
	css_color flood_color;
	css_fixed flood_opacity;
	css_fixed font_size;
	css_fixed grid_column_end;
	css_fixed grid_column_start;
	css_fixed grid_row_end;
	css_fixed grid_row_start;
	css_fixed height;
	css_fixed left;
	css_fixed letter_spacing;
	css_fixed line_height;
	lwc_string *list_style_image;
	css_fixed margin_bottom;
	css_fixed margin_left;
	css_fixed margin_right;
	css_fixed margin_top;
	lwc_string *marker_end;
	lwc_string *marker_mid;
	lwc_string *marker_start;
	lwc_string *mask;
	css_fixed max_height;
	css_fixed max_width;
	css_fixed min_height;
	css_fixed min_width;
	css_fixed opacity;
	int32_t order;
	int32_t orphans;
	css_color outline_color;
	css_fixed outline_width;
	css_fixed padding_bottom;
	css_fixed padding_left;
	css_fixed padding_right;
	css_fixed padding_top;
	css_fixed right;
	css_color stop_color;
	css_fixed stop_opacity;
	css_fixed stroke_dashoffset;
	css_fixed stroke_miterlimit;
	css_fixed stroke_opacity;
	css_fixed stroke_width;
	css_fixed text_indent;
	lwc_string *text_overflow;
	css_fixed top;
	css_fixed vertical_align;
	int32_t widows;
	css_fixed width;
	css_fixed word_spacing;
	int32_t z_index;
	
	size_t grid_template_columns_size;
	uint8_t grid_template_columns_type;
	css_fixed* grid_template_columns;
	css_unit*  grid_template_columns_unit;
	
	size_t grid_template_rows_size;
	uint8_t grid_template_rows_type;
	css_fixed* grid_template_rows;
	css_unit*  grid_template_rows_unit;
	
	css_fixed  text_shadow_h;
	css_unit  text_shadow_h_unit;
	css_fixed  text_shadow_v;
	css_unit  text_shadow_v_unit;
	css_fixed  text_shadow_blur;
	css_unit  text_shadow_blur_unit;
	css_color  text_shadow_color;
	
	size_t stroke_dasharray_size;
	css_fixed* stroke_dasharray;
	css_unit*  stroke_dasharray_unit;
	
	lwc_string* fill;
	css_color fill_color;
	lwc_string* stroke;
	css_color stroke_color;
};

struct css_computed_style {
	struct css_computed_style_i i;
	
	css_computed_content_item *content;
	css_computed_counter *counter_increment;
	css_computed_counter *counter_reset;
	lwc_string **cursor;
	lwc_string **font_family;
	lwc_string **quotes;
	
	struct css_computed_style *next;
	uint32_t count;
	uint32_t bin;
};
