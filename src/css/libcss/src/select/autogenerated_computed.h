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
 * fill                             1             sizeof(ptr)
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
 * stroke                           1               4
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
 * text_shadow                      4             
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
 *                                623 bits        300 + 16sizeof(ptr) bytes
 *                                ===================
 *                                378 + 16sizeof(ptr) bytes
 * 
 * Bit allocations:
 * 
 * 0  bbbbbbbboooooooouuuuuuuurrrrrrrr
 * border_bottom_width; border_top_width; outline_width; border_right_width
 * 
 * 1  vvvvvvvvvccccccccbbbbbbbbooooooo
 * vertical_align; column_rule_width; border_left_width; border_top_right_radius
 * 
 * 2  cccccccccccccccccccccccccctttttt
 * clip; text_indent
 * 
 * 3  lllllllcccccccbbbbbbbmmmmmmmiiii
 * line_height; column_gap; border_bottom_right_radius; max_width; clip_rule
 * 
 * 4  gggggggrrrrrrrbbbbbbbooooooocccc
 * grid_row_start; grid_column_end; border_top_left_radius;
 * border_bottom_left_radius; column_rule_style
 * 
 * 5  ssssssstttttttlllllllmmmmmmmrrrr
 * stroke_dashoffset; stroke_width; left; margin_right; stroke_linejoin
 * 
 * 6  fffffffwwwwwwwgggggggmmmmmmmbbbb
 * flex_basis; width; grid_row_end; margin_top; border_left_style
 * 
 * 7  mmmmmmmiiiiiiirrrrrrrwwwwwwwtttt
 * min_height; min_width; right; word_spacing; text_justify
 * 
 * 8  hhhhhhhmmmmmmmbbbbbbbtttttttwwww
 * height; max_height; bottom; top; word_wrap
 * 
 * 9  ccccccclllllllmmmmmmmaaaaaaatttt
 * column_width; letter_spacing; margin_bottom; margin_left; text_shadow
 * 
 * 10 bbbbtttteeeerrrrooooaaaauuuuwwww
 * break_before; text_rendering; text_align_last; break_inside;
 * border_bottom_style; baseline_shift; outline_style; word_break
 * 
 * 11 dddddtttttccccceeeeefffffsssssbb
 * display; text_decoration; cursor; enable_background; font_stretch;
 * shape_rendering; background_attachment
 * 
 * 12 uuuuucccccssssffffbbbbttttooooll
 * unicode_bidi; comp_op; stroke_linecap; font_weight; border_right_style;
 * text_align; border_top_style; column_count
 * 
 * 13 llllttttbbbbooojjjpppwwwaaasssee
 * list_style_type; text_anchor; break_after; overflow_y; justify_content;
 * page_break_after; white_space; page_break_before; position; table_layout
 * 
 * 14 aaatttlllfffiiiooonnncccbbbrrruu
 * align_content; text_transform; align_items; flex_direction; align_self;
 * overflow_x; font_family; clear; background_repeat; fill_rule; column_span
 * 
 * 15 ccbboottaaddpprrffllwwssuuvvnngg
 * content; border_collapse; column_fill; text_overflow; caption_side;
 * direction; page_break_inside; border_right_color; float;
 * list_style_position; writing_mode; stroke_dasharray; column_rule_color;
 * visibility; font_style; grid_template_rows
 * 
 * 16 bbbbbbbbbbbooooooooooofffffffffl
 * background_position; border_spacing; font_size; list_style_image
 * 
 * 17 gggggggppppppaaaaaaddddddiiiiiis
 * grid_column_start; padding_left; padding_right; padding_bottom; padding_top;
 * stroke
 * 
 * 18 bbffggeeoorrzzaaxxnnuucikmdstpOl
 * border_top_color; flex_wrap; grid_template_columns; empty_cells;
 * border_left_color; border_bottom_color; z_index; background_color;
 * box_sizing; font_variant; outline_color; counter_reset; fill_opacity;
 * background_image; marker_start; marker_mid; stroke_opacity;
 * stroke_miterlimit; stop_opacity; order; color
 * 
 * 19 wfoildmqcsepxar.................
 * widows; flood_color; orphans; fill; filter; flood_opacity; mask; quotes;
 * counter_increment; stop_color; flex_shrink; opacity; flex_grow; clip_path;
 * marker_end
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
	lwc_string *fill;
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
	css_color stroke;
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
	css_fixed  text_shadow_v;
	css_fixed  text_shadow_blur;
	css_color  text_shadow_color;
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
