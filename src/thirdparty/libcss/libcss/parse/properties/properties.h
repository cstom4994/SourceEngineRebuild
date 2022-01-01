
/*********************************************************************************
properties
*
*********************************************************************************/
/*
 * This file is part of LibCSS.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#ifndef css_css__parse_properties_properties_h_
#define css_css__parse_properties_properties_h_

#include "thirdparty/libcss/libcss/stylesheetImpl.h"
#include "thirdparty/libcss/libcss/lex/lex.h"
#include "thirdparty/libcss/libcss/parse/language.h"
#include "thirdparty/libcss/libcss/parse/propstrings.h"

 /**
  * Type of property handler function
  */
typedef css_error(*css_prop_handler)(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);

extern const css_prop_handler property_handlers[LAST_PROP + 1 - FIRST_PROP];

css_error css__parse_align_content(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_align_items(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_align_self(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_azimuth(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_background(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_background_attachment(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_background_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_background_image(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_background_position(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_background_repeat(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_bottom(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_bottom_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_bottom_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_bottom_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_collapse(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_left(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_left_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_left_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_left_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_right(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_right_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_right_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_right_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_radius(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_radius_corner(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result, enum css_properties_e op);
css_error css__parse_border_radius_top_left(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_radius_top_right(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_radius_bottom_right(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_radius_bottom_left(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_spacing(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_top(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_top_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_top_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_top_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_border_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_bottom(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_box_sizing(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_break_after(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_break_before(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_break_inside(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_caption_side(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_clear(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_clip(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_columns(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_column_count(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_column_fill(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_column_gap(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_column_rule(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_column_rule_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_column_rule_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_column_rule_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_column_span(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_column_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_content(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_counter_increment(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_counter_reset(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_cue(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_cue_after(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_cue_before(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_cursor(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_direction(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_display(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_elevation(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_empty_cells(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_flex(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_flex_basis(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_flex_direction(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_flex_flow(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_flex_grow(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_flex_shrink(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_flex_wrap(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_float(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_font(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_font_family(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_font_size(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_font_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_font_variant(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_font_weight(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_height(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_justify_content(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_left(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_letter_spacing(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_line_height(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_list_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_list_style_image(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_list_style_position(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_list_style_type(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_margin(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_margin_bottom(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_margin_left(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_margin_right(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_margin_top(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_max_height(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_max_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_min_height(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_min_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_opacity(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_order(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_orphans(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_outline(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_outline_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_outline_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_outline_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_overflow(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_overflow_x(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_overflow_y(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_padding(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_padding_bottom(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_padding_left(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_padding_right(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_padding_top(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_page_break_after(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_page_break_before(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_page_break_inside(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_pause(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_pause_after(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_pause_before(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_pitch_range(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_pitch(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_play_during(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_position(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_quotes(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_richness(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_right(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_speak_header(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_speak_numeral(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_speak_punctuation(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_speak(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_speech_rate(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_stress(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_table_layout(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_text_align(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_text_decoration(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_text_indent(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_text_transform(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_top(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_unicode_bidi(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_vertical_align(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_visibility(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_voice_family(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_volume(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_white_space(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_widows(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_word_spacing(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_writing_mode(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);
css_error css__parse_z_index(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result);

#endif

/*********************************************************************************
utils
*
*********************************************************************************/
/*
 * This file is part of LibCSS.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2008 John-Mark Bell <jmb@netsurf-browser.org>
 */

#ifndef css_css__parse_properties_utils_h_
#define css_css__parse_properties_utils_h_

#include "thirdparty/libcss/libcss/parse/language.h"

static inline bool is_css_inherit(css_language* c, const css_token* token)
{
    bool match;
    return ((token->type == CSS_TOKEN_IDENT) &&
        (lwc_string_caseless_isequal(
            token->idata, c->strings[INHERIT],
            &match) == lwc_error_ok && match));
}

enum border_side_e { BORDER_SIDE_TOP = 0, BORDER_SIDE_RIGHT = 1, BORDER_SIDE_BOTTOM = 2, BORDER_SIDE_LEFT = 3 };

/**
 * Parse border-{top,right,bottom,left} shorthand
 *
 * \param c	  Parsing context.
 * \param vector  Vector of tokens to process.
 * \param ctx	  Pointer to vector iteration context.
 * \param result  Result style.
 * \param side	  The side we're parsing for.
 * \return CSS_OK on success,
 *	   CSS_NOMEM on memory exhaustion,
 *	   CSS_INVALID if the input is not valid
 *
 * Post condition: \a *ctx is updated with the next token to process
 *		   If the input is invalid, then \a *ctx remains unchanged.
 */
css_error css__parse_border_side(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result, enum border_side_e side);

/**
 * Parse border-{top,right,bottom,left}-color
 *
 * \param c	  Parsing context
 * \param vector  Vector of tokens to process
 * \param ctx	  Pointer to vector iteration context
 * \param result  Pointer to location to receive resulting style
 * \param op	  Opcode to parse for (encodes side)
 * \return CSS_OK on success,
 *	   CSS_NOMEM on memory exhaustion,
 *	   CSS_INVALID if the input is not valid
 *
 * Post condition: \a *ctx is updated with the next token to process
 *		   If the input is invalid, then \a *ctx remains unchanged.
 */
css_error css__parse_border_side_color(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result, enum css_properties_e op);

/**
 * Parse border-{top,right,bottom,left}-style
 *
 * \param c	  Parsing context
 * \param vector  Vector of tokens to process
 * \param ctx	  Pointer to vector iteration context
 * \param result  Pointer to location to receive resulting style
 * \param op	  Opcode to parse for (encodes side)
 * \return CSS_OK on success,
 *	   CSS_NOMEM on memory exhaustion,
 *	   CSS_INVALID if the input is not valid
 *
 * Post condition: \a *ctx is updated with the next token to process
 *		   If the input is invalid, then \a *ctx remains unchanged.
 */
css_error css__parse_border_side_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result, enum css_properties_e op);


/**
 * Parse border-{top,right,bottom,left}-width
 *
 * \param c	  Parsing context
 * \param vector  Vector of tokens to process
 * \param ctx	  Pointer to vector iteration context
 * \param result  Pointer to location to receive resulting style
 * \param op	  Opcode to parse for (encodes side)
 * \return CSS_OK on success,
 *	   CSS_NOMEM on memory exhaustion,
 *	   CSS_INVALID if the input is not valid
 *
 * Post condition: \a *ctx is updated with the next token to process
 *		   If the input is invalid, then \a *ctx remains unchanged.
 */
css_error css__parse_border_side_width(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result, enum css_properties_e op);


/**
 * Parse {top,right,bottom,left}
 *
 * \param c       Parsing context
 * \param vector  Vector of tokens to process
 * \param ctx     Pointer to vector iteration context
 * \param op      Opcode to parse for
 * \param result  Pointer to location to receive resulting style
 * \return CSS_OK on success,
 *         CSS_NOMEM on memory exhaustion,
 *         CSS_INVALID if the input is not valid
 *
 * Post condition: \a *ctx is updated with the next token to process
 *                 If the input is invalid, then \a *ctx remains unchanged.
 */
css_error css__parse_side(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result, enum css_properties_e op);


/**
 * Parse margin-{top,right,bottom,left}
 *
 * \param c	  Parsing context
 * \param vector  Vector of tokens to process
 * \param ctx	  Pointer to vector iteration context
 * \param result  Pointer to location to receive resulting style
 * \return CSS_OK on success,
 *	   CSS_NOMEM on memory exhaustion,
 *	   CSS_INVALID if the input is not valid
 *
 * Post condition: \a *ctx is updated with the next token to process
 *		   If the input is invalid, then \a *ctx remains unchanged.
 */
css_error css__parse_margin_side(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result, enum css_properties_e op);

/**
 * Parse padding-{top,right,bottom,left}
 *
 * \param c	  Parsing context
 * \param vector  Vector of tokens to process
 * \param ctx	  Pointer to vector iteration context
 * \param result  Pointer to location to receive resulting style
 * \return CSS_OK on success,
 *	   CSS_NOMEM on memory exhaustion,
 *	   CSS_INVALID if the input is not valid
 *
 * Post condition: \a *ctx is updated with the next token to process
 *		   If the input is invalid, then \a *ctx remains unchanged.
 */
css_error css__parse_padding_side(css_language* c,
    const parserutils_vector* vector, int* ctx,
    css_style* result, enum css_properties_e op);







css_error css__parse_list_style_type_value(css_language* c,
    const css_token* token, uint16_t* value);

css_error css__parse_colour_specifier(css_language* c,
    const parserutils_vector* vector, int* ctx,
    uint16_t* value, uint32_t* result);

css_error css__parse_named_colour(css_language* c, lwc_string* data,
    uint32_t* result);

css_error css__parse_hash_colour(lwc_string* data, uint32_t* result);

css_error css__parse_unit_specifier(css_language* c,
    const parserutils_vector* vector, int* ctx,
    uint32_t default_unit,
    css_fixed* length, uint32_t* unit);

css_error css__parse_unit_keyword(const char* ptr, size_t len,
    uint32_t* unit);

css_error css__ident_list_or_string_to_string(css_language* c,
    const parserutils_vector* vector, int* ctx,
    bool (*reserved)(css_language* c, const css_token* ident),
    lwc_string** result);

css_error css__ident_list_to_string(css_language* c,
    const parserutils_vector* vector, int* ctx,
    bool (*reserved)(css_language* c, const css_token* ident),
    lwc_string** result);

css_error css__comma_list_to_style(css_language* c,
    const parserutils_vector* vector, int* ctx,
    bool (*reserved)(css_language* c, const css_token* ident),
    css_code_t(*get_value)(css_language* c,
        const css_token* token,
        bool first),
    css_style* result);

#endif
