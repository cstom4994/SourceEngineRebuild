
/*********************************************************************************
align_content
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"

css_error css__cascade_align_content(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_ALIGN_CONTENT_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case ALIGN_CONTENT_STRETCH:
            value = CSS_ALIGN_CONTENT_STRETCH;
            break;
        case ALIGN_CONTENT_FLEX_START:
            value = CSS_ALIGN_CONTENT_FLEX_START;
            break;
        case ALIGN_CONTENT_FLEX_END:
            value = CSS_ALIGN_CONTENT_FLEX_END;
            break;
        case ALIGN_CONTENT_CENTER:
            value = CSS_ALIGN_CONTENT_CENTER;
            break;
        case ALIGN_CONTENT_SPACE_BETWEEN:
            value = CSS_ALIGN_CONTENT_SPACE_BETWEEN;
            break;
        case ALIGN_CONTENT_SPACE_AROUND:
            value = CSS_ALIGN_CONTENT_SPACE_AROUND;
            break;
        case ALIGN_CONTENT_SPACE_EVENLY:
            value = CSS_ALIGN_CONTENT_SPACE_EVENLY;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_align_content(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_align_content_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_align_content(style, hint->status);
}

css_error css__initial_align_content(css_select_state* state)
{
    return set_align_content(state->computed, CSS_ALIGN_CONTENT_STRETCH);
}

css_error css__compose_align_content(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_align_content(child);

    if (type == CSS_ALIGN_CONTENT_INHERIT) {
        type = get_align_content(parent);
    }

    return set_align_content(result, type);
}


/*********************************************************************************
align_items
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"

css_error css__cascade_align_items(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_ALIGN_ITEMS_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case ALIGN_ITEMS_STRETCH:
            value = CSS_ALIGN_ITEMS_STRETCH;
            break;
        case ALIGN_ITEMS_FLEX_START:
            value = CSS_ALIGN_ITEMS_FLEX_START;
            break;
        case ALIGN_ITEMS_FLEX_END:
            value = CSS_ALIGN_ITEMS_FLEX_END;
            break;
        case ALIGN_ITEMS_CENTER:
            value = CSS_ALIGN_ITEMS_CENTER;
            break;
        case ALIGN_ITEMS_BASELINE:
            value = CSS_ALIGN_ITEMS_BASELINE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_align_items(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_align_items_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_align_items(style, hint->status);
}

css_error css__initial_align_items(css_select_state* state)
{
    return set_align_items(state->computed, CSS_ALIGN_ITEMS_STRETCH);
}

css_error css__compose_align_items(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_align_items(child);

    if (type == CSS_ALIGN_ITEMS_INHERIT) {
        type = get_align_items(parent);
    }

    return set_align_items(result, type);
}


/*********************************************************************************
align_self
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_align_self(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_ALIGN_SELF_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case ALIGN_SELF_STRETCH:
            value = CSS_ALIGN_SELF_STRETCH;
            break;
        case ALIGN_SELF_FLEX_START:
            value = CSS_ALIGN_SELF_FLEX_START;
            break;
        case ALIGN_SELF_FLEX_END:
            value = CSS_ALIGN_SELF_FLEX_END;
            break;
        case ALIGN_SELF_CENTER:
            value = CSS_ALIGN_SELF_CENTER;
            break;
        case ALIGN_SELF_BASELINE:
            value = CSS_ALIGN_SELF_BASELINE;
            break;
        case ALIGN_SELF_AUTO:
            value = CSS_ALIGN_SELF_AUTO;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_align_self(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_align_self_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_align_self(style, hint->status);
}

css_error css__initial_align_self(css_select_state* state)
{
    return set_align_self(state->computed, CSS_ALIGN_SELF_AUTO);
}

css_error css__compose_align_self(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_align_self(child);

    if (type == CSS_ALIGN_SELF_INHERIT) {
        type = get_align_self(parent);
    }

    return set_align_self(result, type);
}


/*********************************************************************************
azimuth
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_azimuth(uint32_t opv, css_style* style,
    css_select_state* state)
{
    css_fixed val = 0;
    uint32_t unit = UNIT_DEG;

    if (isInherit(opv) == false) {
        switch (getValue(opv) & ~AZIMUTH_BEHIND) {
        case AZIMUTH_ANGLE:
            val = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(val));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case AZIMUTH_LEFTWARDS:
        case AZIMUTH_RIGHTWARDS:
        case AZIMUTH_LEFT_SIDE:
        case AZIMUTH_FAR_LEFT:
        case AZIMUTH_LEFT:
        case AZIMUTH_CENTER_LEFT:
        case AZIMUTH_CENTER:
        case AZIMUTH_CENTER_RIGHT:
        case AZIMUTH_RIGHT:
        case AZIMUTH_FAR_RIGHT:
        case AZIMUTH_RIGHT_SIDE:
            /** \todo azimuth values */
            break;
        }

        /** \todo azimuth behind */
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo set computed azimuth */
    }

    return CSS_OK;
}

css_error css__set_azimuth_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_azimuth(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_azimuth(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
background_attachment
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_background_attachment(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_BACKGROUND_ATTACHMENT_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BACKGROUND_ATTACHMENT_FIXED:
            value = CSS_BACKGROUND_ATTACHMENT_FIXED;
            break;
        case BACKGROUND_ATTACHMENT_SCROLL:
            value = CSS_BACKGROUND_ATTACHMENT_SCROLL;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_background_attachment(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_background_attachment_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_background_attachment(style, hint->status);
}

css_error css__initial_background_attachment(css_select_state* state)
{
    return set_background_attachment(state->computed,
        CSS_BACKGROUND_ATTACHMENT_SCROLL);
}

css_error css__compose_background_attachment(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_background_attachment(child);

    if (type == CSS_BACKGROUND_ATTACHMENT_INHERIT) {
        type = get_background_attachment(parent);
    }

    return set_background_attachment(result, type);
}


/*********************************************************************************
background_color
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_background_color(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_bg_border_color(opv, style, state, set_background_color);
}

css_error css__set_background_color_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_background_color(style, hint->status, hint->data.color);
}

css_error css__initial_background_color(css_select_state* state)
{
    return set_background_color(state->computed,
        CSS_BACKGROUND_COLOR_COLOR, 0);
}

css_error css__compose_background_color(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_color color;
    uint8_t type = get_background_color(child, &color);

    if (type == CSS_BACKGROUND_COLOR_INHERIT) {
        type = get_background_color(parent, &color);
    }

    return set_background_color(result, type, color);
}


/*********************************************************************************
background_image
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_background_image(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_uri_none(opv, style, state, set_background_image);
}

css_error css__set_background_image_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    css_error error;

    error = set_background_image(style, hint->status, hint->data.string);

    if (hint->data.string != NULL)
        lwc_string_unref(hint->data.string);

    return error;
}

css_error css__initial_background_image(css_select_state* state)
{
    return set_background_image(state->computed,
        CSS_BACKGROUND_IMAGE_NONE, NULL);
}

css_error css__compose_background_image(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    lwc_string* url;
    uint8_t type = get_background_image(child, &url);

    if (type == CSS_BACKGROUND_IMAGE_INHERIT) {
        type = get_background_image(parent, &url);
    }

    return set_background_image(result, type, url);
}


/*********************************************************************************
background_position
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_background_position(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_BACKGROUND_POSITION_INHERIT;
    css_fixed hlength = 0;
    css_fixed vlength = 0;
    uint32_t hunit = UNIT_PX;
    uint32_t vunit = UNIT_PX;

    if (isInherit(opv) == false) {
        value = CSS_BACKGROUND_POSITION_SET;

        switch (getValue(opv) & 0xf0) {
        case BACKGROUND_POSITION_HORZ_SET:
            hlength = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(hlength));
            hunit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(hunit));
            break;
        case BACKGROUND_POSITION_HORZ_CENTER:
            hlength = INTTOFIX(50);
            hunit = UNIT_PCT;
            break;
        case BACKGROUND_POSITION_HORZ_RIGHT:
            hlength = INTTOFIX(100);
            hunit = UNIT_PCT;
            break;
        case BACKGROUND_POSITION_HORZ_LEFT:
            hlength = INTTOFIX(0);
            hunit = UNIT_PCT;
            break;
        }

        switch (getValue(opv) & 0x0f) {
        case BACKGROUND_POSITION_VERT_SET:
            vlength = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(vlength));
            vunit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(vunit));
            break;
        case BACKGROUND_POSITION_VERT_CENTER:
            vlength = INTTOFIX(50);
            vunit = UNIT_PCT;
            break;
        case BACKGROUND_POSITION_VERT_BOTTOM:
            vlength = INTTOFIX(100);
            vunit = UNIT_PCT;
            break;
        case BACKGROUND_POSITION_VERT_TOP:
            vlength = INTTOFIX(0);
            vunit = UNIT_PCT;
            break;
        }
    }

    hunit = css__to_css_unit(hunit);
    vunit = css__to_css_unit(vunit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_background_position(state->computed, value,
            hlength, hunit, vlength, vunit);
    }

    return CSS_OK;
}

css_error css__set_background_position_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_background_position(style, hint->status,
        hint->data.position.h.value, hint->data.position.h.unit,
        hint->data.position.v.value, hint->data.position.v.unit);
}

css_error css__initial_background_position(css_select_state* state)
{
    return set_background_position(state->computed,
        CSS_BACKGROUND_POSITION_SET,
        0, CSS_UNIT_PCT, 0, CSS_UNIT_PCT);
}

css_error css__compose_background_position(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed hlength = 0, vlength = 0;
    css_unit hunit = CSS_UNIT_PX, vunit = CSS_UNIT_PX;
    uint8_t type = get_background_position(child, &hlength, &hunit,
        &vlength, &vunit);

    if (type == CSS_BACKGROUND_POSITION_INHERIT) {
        type = get_background_position(parent,
            &hlength, &hunit, &vlength, &vunit);
    }

    return set_background_position(result, type, hlength, hunit,
        vlength, vunit);
}


/*********************************************************************************
background_repeat
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_background_repeat(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_BACKGROUND_REPEAT_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BACKGROUND_REPEAT_NO_REPEAT:
            value = CSS_BACKGROUND_REPEAT_NO_REPEAT;
            break;
        case BACKGROUND_REPEAT_REPEAT_X:
            value = CSS_BACKGROUND_REPEAT_REPEAT_X;
            break;
        case BACKGROUND_REPEAT_REPEAT_Y:
            value = CSS_BACKGROUND_REPEAT_REPEAT_Y;
            break;
        case BACKGROUND_REPEAT_REPEAT:
            value = CSS_BACKGROUND_REPEAT_REPEAT;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_background_repeat(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_background_repeat_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_background_repeat(style, hint->status);
}

css_error css__initial_background_repeat(css_select_state* state)
{
    return set_background_repeat(state->computed,
        CSS_BACKGROUND_REPEAT_REPEAT);
}

css_error css__compose_background_repeat(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_background_repeat(child);

    if (type == CSS_BACKGROUND_REPEAT_INHERIT) {
        type = get_background_repeat(parent);
    }

    return set_background_repeat(result, type);
}


/*********************************************************************************
border_bottom_color
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_bottom_color(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_bg_border_color(opv, style, state,
        set_border_bottom_color);
}

css_error css__set_border_bottom_color_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_bottom_color(style, hint->status, hint->data.color);
}

css_error css__initial_border_bottom_color(css_select_state* state)
{
    return set_border_bottom_color(state->computed,
        CSS_BORDER_COLOR_CURRENT_COLOR, 0);
}

css_error css__compose_border_bottom_color(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_color color;
    uint8_t type = get_border_bottom_color(child, &color);

    if (type == CSS_BORDER_COLOR_INHERIT) {
        type = get_border_bottom_color(parent, &color);
    }

    return set_border_bottom_color(result, type, color);
}


/*********************************************************************************
border_bottom_style
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_bottom_style(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_style(opv, style, state, set_border_bottom_style);
}

css_error css__set_border_bottom_style_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_bottom_style(style, hint->status);
}

css_error css__initial_border_bottom_style(css_select_state* state)
{
    return set_border_bottom_style(state->computed, CSS_BORDER_STYLE_NONE);
}

css_error css__compose_border_bottom_style(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_border_bottom_style(child);

    if (type == CSS_BORDER_STYLE_INHERIT) {
        type = get_border_bottom_style(parent);
    }

    return set_border_bottom_style(result, type);
}


/*********************************************************************************
border_bottom_width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_bottom_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_width(opv, style, state, set_border_bottom_width);
}

css_error css__set_border_bottom_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_bottom_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_border_bottom_width(css_select_state* state)
{
    return set_border_bottom_width(state->computed, CSS_BORDER_WIDTH_MEDIUM,
        0, CSS_UNIT_PX);
}

css_error css__compose_border_bottom_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_border_bottom_width(child, &length, &unit);

    if (type == CSS_BORDER_WIDTH_INHERIT) {
        type = get_border_bottom_width(parent, &length, &unit);
    }

    return set_border_bottom_width(result, type, length, unit);
}


/*********************************************************************************
border_collapse
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_collapse(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_BORDER_COLLAPSE_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BORDER_COLLAPSE_SEPARATE:
            value = CSS_BORDER_COLLAPSE_SEPARATE;
            break;
        case BORDER_COLLAPSE_COLLAPSE:
            value = CSS_BORDER_COLLAPSE_COLLAPSE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_border_collapse(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_border_collapse_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_collapse(style, hint->status);
}

css_error css__initial_border_collapse(css_select_state* state)
{
    return set_border_collapse(state->computed, CSS_BORDER_COLLAPSE_SEPARATE);
}

css_error css__compose_border_collapse(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_border_collapse(child);

    if (type == CSS_BORDER_COLLAPSE_INHERIT) {
        type = get_border_collapse(parent);
    }

    return set_border_collapse(result, type);
}


/*********************************************************************************
border_left_color
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_left_color(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_bg_border_color(opv, style, state,
        set_border_left_color);
}

css_error css__set_border_left_color_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_left_color(style, hint->status, hint->data.color);
}

css_error css__initial_border_left_color(css_select_state* state)
{
    return set_border_left_color(state->computed,
        CSS_BORDER_COLOR_CURRENT_COLOR, 0);
}

css_error css__compose_border_left_color(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_color color;
    uint8_t type = get_border_left_color(child, &color);

    if (type == CSS_BORDER_COLOR_INHERIT) {
        type = get_border_left_color(parent, &color);
    }

    return set_border_left_color(result, type, color);
}


/*********************************************************************************
border_left_style
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_left_style(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_style(opv, style, state, set_border_left_style);
}

css_error css__set_border_left_style_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_left_style(style, hint->status);
}

css_error css__initial_border_left_style(css_select_state* state)
{
    return set_border_left_style(state->computed, CSS_BORDER_STYLE_NONE);
}

css_error css__compose_border_left_style(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_border_left_style(child);

    if (type == CSS_BORDER_STYLE_INHERIT) {
        type = get_border_left_style(parent);
    }

    return set_border_left_style(result, type);
}


/*********************************************************************************
border_left_width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_left_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_width(opv, style, state, set_border_left_width);
}

css_error css__set_border_left_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_left_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_border_left_width(css_select_state* state)
{
    return set_border_left_width(state->computed, CSS_BORDER_WIDTH_MEDIUM,
        0, CSS_UNIT_PX);
}

css_error css__compose_border_left_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_border_left_width(child, &length, &unit);

    if (type == CSS_BORDER_WIDTH_INHERIT) {
        type = get_border_left_width(parent, &length, &unit);
    }

    return set_border_left_width(result, type, length, unit);
}


/*********************************************************************************
border_radius
*
*********************************************************************************/

/*********************************************************************************
border_radius_bottom_left
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 ZhuYaDong <aeix@foxmail.com>
 * 					 2020 Artem Chernyshev (unix4ever)
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_radius_bottom_left(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length(opv, style, state, set_border_radius_bottom_left);
}

css_error css__set_border_radius_bottom_left_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_radius_bottom_left(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_border_radius_bottom_left(css_select_state* state)
{
    return set_border_radius_bottom_left(state->computed, CSS_BORDER_RADIUS_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_border_radius_bottom_left(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_border_radius_bottom_left(child, &length, &unit);

    if (type == CSS_BORDER_RADIUS_INHERIT) {
        type = get_border_radius_bottom_left(parent, &length, &unit);
    }

    return set_border_radius_bottom_left(result, type, length, unit);
}

/*********************************************************************************
border_radius_bottom_right
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 ZhuYaDong <aeix@foxmail.com>
 * 					 2020 Artem Chernyshev (unix4ever)
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_radius_bottom_right(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length(opv, style, state, set_border_radius_bottom_right);
}

css_error css__set_border_radius_bottom_right_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_radius_bottom_right(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_border_radius_bottom_right(css_select_state* state)
{
    return set_border_radius_bottom_right(state->computed, CSS_BORDER_RADIUS_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_border_radius_bottom_right(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_border_radius_bottom_right(child, &length, &unit);

    if (type == CSS_BORDER_RADIUS_INHERIT) {
        type = get_border_radius_bottom_right(parent, &length, &unit);
    }

    return set_border_radius_bottom_right(result, type, length, unit);
}

/*********************************************************************************
border_radius_top_left
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 ZhuYaDong <aeix@foxmail.com>
 * 					 2020 Artem Chernyshev (unix4ever)
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_radius_top_left(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length(opv, style, state, set_border_radius_top_left);
}

css_error css__set_border_radius_top_left_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_radius_top_left(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_border_radius_top_left(css_select_state* state)
{
    return set_border_radius_top_left(state->computed, CSS_BORDER_RADIUS_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_border_radius_top_left(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_border_radius_top_left(child, &length, &unit);

    if (type == CSS_BORDER_RADIUS_INHERIT) {
        type = get_border_radius_top_left(parent, &length, &unit);
    }

    return set_border_radius_top_left(result, type, length, unit);
}

/*********************************************************************************
border_radius_top_right
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 ZhuYaDong <aeix@foxmail.com>
 * 					 2020 Artem Chernyshev (unix4ever)
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_radius_top_right(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length(opv, style, state, set_border_radius_top_right);
}

css_error css__set_border_radius_top_right_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_radius_top_right(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_border_radius_top_right(css_select_state* state)
{
    return set_border_radius_top_right(state->computed, CSS_BORDER_RADIUS_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_border_radius_top_right(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_border_radius_top_right(child, &length, &unit);

    if (type == CSS_BORDER_RADIUS_INHERIT) {
        type = get_border_radius_top_right(parent, &length, &unit);
    }

    return set_border_radius_top_right(result, type, length, unit);
}

/*********************************************************************************
border_right_color
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_right_color(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_bg_border_color(opv, style, state,
        set_border_right_color);
}

css_error css__set_border_right_color_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_right_color(style, hint->status, hint->data.color);
}

css_error css__initial_border_right_color(css_select_state* state)
{
    return set_border_right_color(state->computed,
        CSS_BORDER_COLOR_CURRENT_COLOR, 0);
}

css_error css__compose_border_right_color(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_color color;
    uint8_t type = get_border_right_color(child, &color);

    if (type == CSS_BORDER_COLOR_INHERIT) {
        type = get_border_right_color(parent, &color);
    }

    return set_border_right_color(result, type, color);
}


/*********************************************************************************
border_right_style
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_right_style(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_style(opv, style, state, set_border_right_style);
}

css_error css__set_border_right_style_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_right_style(style, hint->status);
}

css_error css__initial_border_right_style(css_select_state* state)
{
    return set_border_right_style(state->computed, CSS_BORDER_STYLE_NONE);
}

css_error css__compose_border_right_style(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_border_right_style(child);

    if (type == CSS_BORDER_STYLE_INHERIT) {
        type = get_border_right_style(parent);
    }

    return set_border_right_style(result, type);
}


/*********************************************************************************
border_right_width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_right_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_width(opv, style, state, set_border_right_width);
}

css_error css__set_border_right_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_right_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_border_right_width(css_select_state* state)
{
    return set_border_right_width(state->computed, CSS_BORDER_WIDTH_MEDIUM,
        0, CSS_UNIT_PX);
}

css_error css__compose_border_right_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_border_right_width(child, &length, &unit);

    if (type == CSS_BORDER_WIDTH_INHERIT) {
        type = get_border_right_width(parent, &length, &unit);
    }

    return set_border_right_width(result, type, length, unit);
}


/*********************************************************************************
border_spacing
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_spacing(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_BORDER_SPACING_INHERIT;
    css_fixed hlength = 0;
    css_fixed vlength = 0;
    uint32_t hunit = UNIT_PX;
    uint32_t vunit = UNIT_PX;

    if (isInherit(opv) == false) {
        value = CSS_BORDER_SPACING_SET;
        hlength = *((css_fixed*)style->bytecode);
        advance_bytecode(style, sizeof(hlength));
        hunit = *((uint32_t*)style->bytecode);
        advance_bytecode(style, sizeof(hunit));

        vlength = *((css_fixed*)style->bytecode);
        advance_bytecode(style, sizeof(vlength));
        vunit = *((uint32_t*)style->bytecode);
        advance_bytecode(style, sizeof(vunit));
    }

    hunit = css__to_css_unit(hunit);
    vunit = css__to_css_unit(vunit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_border_spacing(state->computed, value,
            hlength, hunit, vlength, vunit);
    }

    return CSS_OK;
}

css_error css__set_border_spacing_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_spacing(style, hint->status,
        hint->data.position.h.value, hint->data.position.h.unit,
        hint->data.position.v.value, hint->data.position.v.unit);
}

css_error css__initial_border_spacing(css_select_state* state)
{
    return set_border_spacing(state->computed, CSS_BORDER_SPACING_SET,
        0, CSS_UNIT_PX, 0, CSS_UNIT_PX);
}

css_error css__compose_border_spacing(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed hlength = 0, vlength = 0;
    css_unit hunit = CSS_UNIT_PX, vunit = CSS_UNIT_PX;
    uint8_t type = get_border_spacing(child, &hlength, &hunit,
        &vlength, &vunit);

    if (type == CSS_BORDER_SPACING_INHERIT) {
        type = get_border_spacing(parent,
            &hlength, &hunit, &vlength, &vunit);
    }

    return set_border_spacing(result, type, hlength, hunit, vlength, vunit);
}

/*********************************************************************************
border_top_color
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_top_color(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_bg_border_color(opv, style, state, set_border_top_color);
}

css_error css__set_border_top_color_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_top_color(style, hint->status, hint->data.color);
}

css_error css__initial_border_top_color(css_select_state* state)
{
    return set_border_top_color(state->computed, CSS_BORDER_COLOR_CURRENT_COLOR, 0);
}

css_error css__compose_border_top_color(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_color color;
    uint8_t type = get_border_top_color(child, &color);

    if (type == CSS_BORDER_COLOR_INHERIT) {
        type = get_border_top_color(parent, &color);
    }

    return set_border_top_color(result, type, color);
}


/*********************************************************************************
border_top_style
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_top_style(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_style(opv, style, state, set_border_top_style);
}

css_error css__set_border_top_style_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_top_style(style, hint->status);
}

css_error css__initial_border_top_style(css_select_state* state)
{
    return set_border_top_style(state->computed, CSS_BORDER_STYLE_NONE);
}

css_error css__compose_border_top_style(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_border_top_style(child);

    if (type == CSS_BORDER_STYLE_INHERIT) {
        type = get_border_top_style(parent);
    }

    return set_border_top_style(result, type);
}


/*********************************************************************************
border_top_width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_border_top_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_width(opv, style, state, set_border_top_width);
}

css_error css__set_border_top_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_border_top_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_border_top_width(css_select_state* state)
{
    return set_border_top_width(state->computed, CSS_BORDER_WIDTH_MEDIUM,
        0, CSS_UNIT_PX);
}

css_error css__compose_border_top_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_border_top_width(child, &length, &unit);

    if (type == CSS_BORDER_WIDTH_INHERIT) {
        type = get_border_top_width(parent, &length, &unit);
    }

    return set_border_top_width(result, type, length, unit);
}


/*********************************************************************************
bottom
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_bottom(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_bottom);
}

css_error css__set_bottom_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_bottom(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_bottom(css_select_state* state)
{
    return set_bottom(state->computed, CSS_BOTTOM_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_bottom(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_bottom(child, &length, &unit);

    if (type == CSS_BOTTOM_INHERIT) {
        type = get_bottom(parent, &length, &unit);
    }

    return set_bottom(result, type, length, unit);
}


/*********************************************************************************
box_sizing
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_box_sizing(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_BOX_SIZING_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BOX_SIZING_CONTENT_BOX:
            value = CSS_BOX_SIZING_CONTENT_BOX;
            break;
        case BOX_SIZING_BORDER_BOX:
            value = CSS_BOX_SIZING_BORDER_BOX;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_box_sizing(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_box_sizing_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_box_sizing(style, hint->status);
}

css_error css__initial_box_sizing(css_select_state* state)
{
    return set_box_sizing(state->computed, CSS_BOX_SIZING_CONTENT_BOX);
}

css_error css__compose_box_sizing(
    const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_box_sizing(child);

    if (type == CSS_BOX_SIZING_INHERIT) {
        type = get_box_sizing(parent);
    }

    return set_box_sizing(result, type);
}


/*********************************************************************************
break_after
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_break_after(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_break_after_before_inside(opv, style, state,
        set_break_after);
}

css_error css__set_break_after_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_break_after(style, hint->status);
}

css_error css__initial_break_after(css_select_state* state)
{
    return set_break_after(state->computed, CSS_BREAK_AFTER_AUTO);
}

css_error css__compose_break_after(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_break_after(child);

    if (type == CSS_BREAK_AFTER_INHERIT) {
        type = get_break_after(parent);
    }

    return set_break_after(result, type);
}


/*********************************************************************************
break_before
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_break_before(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_break_after_before_inside(opv, style, state,
        set_break_before);
}

css_error css__set_break_before_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_break_before(style, hint->status);
}

css_error css__initial_break_before(css_select_state* state)
{
    return set_break_before(state->computed, CSS_BREAK_BEFORE_AUTO);
}

css_error css__compose_break_before(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_break_before(child);

    if (type == CSS_BREAK_BEFORE_INHERIT) {
        type = get_break_before(parent);
    }

    return set_break_before(result, type);
}


/*********************************************************************************
break_inside
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_break_inside(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_BREAK_INSIDE_AUTO;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BREAK_INSIDE_AUTO:
            value = CSS_BREAK_INSIDE_AUTO;
            break;
        case BREAK_INSIDE_AVOID:
            value = CSS_BREAK_INSIDE_AVOID;
            break;
        case BREAK_INSIDE_AVOID_PAGE:
            value = CSS_BREAK_INSIDE_AVOID_PAGE;
            break;
        case BREAK_INSIDE_AVOID_COLUMN:
            value = CSS_BREAK_INSIDE_AVOID_COLUMN;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_break_inside(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_break_inside_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_break_inside(style, hint->status);
}

css_error css__initial_break_inside(css_select_state* state)
{
    return set_break_inside(state->computed, CSS_BREAK_INSIDE_AUTO);
}

css_error css__compose_break_inside(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_break_inside(child);

    if (type == CSS_BREAK_INSIDE_INHERIT) {
        type = get_break_inside(parent);
    }

    return set_break_inside(result, type);
}


/*********************************************************************************
caption_side
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_caption_side(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_CAPTION_SIDE_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case CAPTION_SIDE_TOP:
            value = CSS_CAPTION_SIDE_TOP;
            break;
        case CAPTION_SIDE_BOTTOM:
            value = CSS_CAPTION_SIDE_BOTTOM;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_caption_side(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_caption_side_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_caption_side(style, hint->status);
}

css_error css__initial_caption_side(css_select_state* state)
{
    return set_caption_side(state->computed, CSS_CAPTION_SIDE_TOP);
}

css_error css__compose_caption_side(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_caption_side(child);

    if (type == CSS_CAPTION_SIDE_INHERIT) {
        type = get_caption_side(parent);
    }

    return set_caption_side(result, type);
}


/*********************************************************************************
clear
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_clear(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_CLEAR_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case CLEAR_NONE:
            value = CSS_CLEAR_NONE;
            break;
        case CLEAR_LEFT:
            value = CSS_CLEAR_LEFT;
            break;
        case CLEAR_RIGHT:
            value = CSS_CLEAR_RIGHT;
            break;
        case CLEAR_BOTH:
            value = CSS_CLEAR_BOTH;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_clear(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_clear_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_clear(style, hint->status);
}

css_error css__initial_clear(css_select_state* state)
{
    return set_clear(state->computed, CSS_CLEAR_NONE);
}

css_error css__compose_clear(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_clear(child);

    if (type == CSS_CLEAR_INHERIT) {
        type = get_clear(parent);
    }

    return set_clear(result, type);
}


/*********************************************************************************
clip
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_clip(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_CLIP_INHERIT;
    css_computed_clip_rect rect = { 0, 0, 0, 0,
            CSS_UNIT_PX, CSS_UNIT_PX, CSS_UNIT_PX, CSS_UNIT_PX,
            false, false, false, false };

    if (isInherit(opv) == false) {
        switch (getValue(opv) & CLIP_SHAPE_MASK) {
        case CLIP_SHAPE_RECT:
            if (getValue(opv) & CLIP_RECT_TOP_AUTO) {
                rect.top_auto = true;
            }
            else {
                rect.top = *((css_fixed*)style->bytecode);
                advance_bytecode(style, sizeof(css_fixed));
                rect.tunit = *((uint32_t*)style->bytecode);
                advance_bytecode(style, sizeof(uint32_t));
            }
            if (getValue(opv) & CLIP_RECT_RIGHT_AUTO) {
                rect.right_auto = true;
            }
            else {
                rect.right = *((css_fixed*)style->bytecode);
                advance_bytecode(style, sizeof(css_fixed));
                rect.runit = *((uint32_t*)style->bytecode);
                advance_bytecode(style, sizeof(uint32_t));
            }
            if (getValue(opv) & CLIP_RECT_BOTTOM_AUTO) {
                rect.bottom_auto = true;
            }
            else {
                rect.bottom = *((css_fixed*)style->bytecode);
                advance_bytecode(style, sizeof(css_fixed));
                rect.bunit = *((uint32_t*)style->bytecode);
                advance_bytecode(style, sizeof(uint32_t));
            }
            if (getValue(opv) & CLIP_RECT_LEFT_AUTO) {
                rect.left_auto = true;
            }
            else {
                rect.left = *((css_fixed*)style->bytecode);
                advance_bytecode(style, sizeof(css_fixed));
                rect.lunit = *((uint32_t*)style->bytecode);
                advance_bytecode(style, sizeof(uint32_t));
            }
            value = CSS_CLIP_RECT;
            break;
        case CLIP_AUTO:
            value = CSS_CLIP_AUTO;
            break;
        }
    }

    rect.tunit = css__to_css_unit(rect.tunit);
    rect.runit = css__to_css_unit(rect.runit);
    rect.bunit = css__to_css_unit(rect.bunit);
    rect.lunit = css__to_css_unit(rect.lunit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_clip(state->computed, value, &rect);
    }

    return CSS_OK;
}

css_error css__set_clip_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_clip(style, hint->status, hint->data.clip);
}

css_error css__initial_clip(css_select_state* state)
{
    css_computed_clip_rect rect = { 0, 0, 0, 0,
            CSS_UNIT_PX, CSS_UNIT_PX, CSS_UNIT_PX, CSS_UNIT_PX,
            false, false, false, false };

    return set_clip(state->computed, CSS_CLIP_AUTO, &rect);
}

css_error css__compose_clip(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_computed_clip_rect rect = { 0, 0, 0, 0,
            CSS_UNIT_PX, CSS_UNIT_PX, CSS_UNIT_PX, CSS_UNIT_PX,
            false, false, false, false };
    uint8_t type = get_clip(child, &rect);

    if (type == CSS_CLIP_INHERIT) {
        type = get_clip(parent, &rect);
    }

    return set_clip(result, type, &rect);
}

/*********************************************************************************
color
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_color(uint32_t opv, css_style* style,
    css_select_state* state)
{
    bool inherit = isInherit(opv);
    uint16_t value = CSS_COLOR_INHERIT;
    css_color color = 0;

    if (inherit == false) {
        switch (getValue(opv)) {
        case COLOR_TRANSPARENT:
            value = CSS_COLOR_COLOR;
            break;
        case COLOR_CURRENT_COLOR:
            /* color: currentColor always computes to inherit */
            value = CSS_COLOR_INHERIT;
            inherit = true;
            break;
        case COLOR_SET:
            value = CSS_COLOR_COLOR;
            color = *((css_color*)style->bytecode);
            advance_bytecode(style, sizeof(color));
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        inherit)) {
        return set_color(state->computed, value, color);
    }

    return CSS_OK;
}

css_error css__set_color_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_color(style, hint->status, hint->data.color);
}

css_error css__initial_color(css_select_state* state)
{
    css_hint hint;
    css_error error;

    error = state->handler->ua_default_for_property(state->pw,
        CSS_PROP_COLOR, &hint);
    if (error != CSS_OK)
        return error;

    return css__set_color_from_hint(&hint, state->computed);
}

css_error css__compose_color(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_color color;
    uint8_t type = get_color(child, &color);

    if (type == CSS_COLOR_INHERIT) {
        type = get_color(parent, &color);
    }

    return set_color(result, type, color);
}


/*********************************************************************************
column_count
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_column_count(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_COLUMN_COUNT_INHERIT;
    css_fixed count = 0;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case COLUMN_COUNT_SET:
            value = CSS_COLUMN_COUNT_SET;
            count = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(count));
            break;
        case COLUMN_COUNT_AUTO:
            value = CSS_COLUMN_COUNT_AUTO;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_column_count(state->computed, value, count);
    }

    return CSS_OK;
}

css_error css__set_column_count_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_column_count(style, hint->status, hint->data.integer);
}

css_error css__initial_column_count(css_select_state* state)
{
    return set_column_count(state->computed, CSS_COLUMN_COUNT_AUTO, 0);
}

css_error css__compose_column_count(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    int32_t count = 0;
    uint8_t type = get_column_count(child, &count);

    if (type == CSS_COLUMN_COUNT_INHERIT) {
        type = get_column_count(parent, &count);
    }

    return set_column_count(result, type, count);
}

/*********************************************************************************
column_fill
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_column_fill(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_COLUMN_FILL_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case COLUMN_FILL_BALANCE:
            value = CSS_COLUMN_FILL_BALANCE;
            break;
        case COLUMN_FILL_AUTO:
            value = CSS_COLUMN_FILL_AUTO;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_column_fill(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_column_fill_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_column_fill(style, hint->status);
}

css_error css__initial_column_fill(css_select_state* state)
{
    return set_column_fill(state->computed, CSS_COLUMN_FILL_BALANCE);
}

css_error css__compose_column_fill(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_column_fill(child);

    if (type == CSS_COLUMN_FILL_INHERIT) {
        type = get_column_fill(parent);
    }

    return set_column_fill(result, type);
}


/*********************************************************************************
column_gap
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_column_gap(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_normal(opv, style, state, set_column_gap);
}

css_error css__set_column_gap_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_column_gap(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_column_gap(css_select_state* state)
{
    return set_column_gap(state->computed, CSS_COLUMN_GAP_NORMAL,
        INTTOFIX(1), CSS_UNIT_EM);
}

css_error css__compose_column_gap(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = INTTOFIX(1);
    css_unit unit = CSS_UNIT_EM;
    uint8_t type = get_column_gap(child, &length, &unit);

    if (type == CSS_COLUMN_GAP_INHERIT) {
        type = get_column_gap(parent, &length, &unit);
    }

    return set_column_gap(result, type, length, unit);
}

/*********************************************************************************
column_rule_color
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_column_rule_color(uint32_t opv, css_style* style,
    css_select_state* state)
{
    bool inherit = isInherit(opv);
    uint16_t value = CSS_COLUMN_RULE_COLOR_INHERIT;
    css_color color = 0;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case COLUMN_RULE_COLOR_TRANSPARENT:
            value = CSS_COLUMN_RULE_COLOR_COLOR;
            break;
        case COLUMN_RULE_COLOR_CURRENT_COLOR:
            value = CSS_COLUMN_RULE_COLOR_CURRENT_COLOR;
            break;
        case COLUMN_RULE_COLOR_SET:
            value = CSS_COLUMN_RULE_COLOR_COLOR;
            color = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(color));
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        inherit)) {
        return set_column_rule_color(state->computed, value, color);
    }

    return CSS_OK;
}

css_error css__set_column_rule_color_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_column_rule_color(style, hint->status, hint->data.color);
}

css_error css__initial_column_rule_color(css_select_state* state)
{
    return set_column_rule_color(state->computed,
        CSS_COLUMN_RULE_COLOR_CURRENT_COLOR, 0);
}

css_error css__compose_column_rule_color(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_color color;
    uint8_t type = get_column_rule_color(child, &color);

    if (type == CSS_COLUMN_RULE_COLOR_INHERIT) {
        type = get_column_rule_color(parent, &color);
    }

    return set_column_rule_color(result, type, color);
}


/*********************************************************************************
column_rule_style
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_column_rule_style(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_style(opv, style, state,
        set_column_rule_style);
}

css_error css__set_column_rule_style_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_column_rule_style(style, hint->status);
}

css_error css__initial_column_rule_style(css_select_state* state)
{
    return set_column_rule_style(state->computed,
        CSS_COLUMN_RULE_STYLE_NONE);
}

css_error css__compose_column_rule_style(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_column_rule_style(child);

    if (type == CSS_COLUMN_RULE_STYLE_INHERIT) {
        type = get_column_rule_style(parent);
    }

    return set_column_rule_style(result, type);
}


/*********************************************************************************
column_rule_width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_column_rule_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_width(opv, style, state,
        set_column_rule_width);
}

css_error css__set_column_rule_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_column_rule_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_column_rule_width(css_select_state* state)
{
    return set_column_rule_width(state->computed,
        CSS_COLUMN_RULE_WIDTH_MEDIUM, 0, CSS_UNIT_PX);
}

css_error css__compose_column_rule_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_column_rule_width(child, &length, &unit);

    if (type == CSS_COLUMN_RULE_WIDTH_INHERIT) {
        type = get_column_rule_width(parent, &length, &unit);
    }

    return set_column_rule_width(result, type, length, unit);
}


/*********************************************************************************
column_span
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_column_span(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_COLUMN_SPAN_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case COLUMN_SPAN_NONE:
            value = CSS_COLUMN_SPAN_NONE;
            break;
        case COLUMN_SPAN_ALL:
            value = CSS_COLUMN_SPAN_ALL;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_column_span(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_column_span_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_column_span(style, hint->status);
}

css_error css__initial_column_span(css_select_state* state)
{
    return set_column_span(state->computed, CSS_COLUMN_SPAN_NONE);
}

css_error css__compose_column_span(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_column_span(child);

    if (type == CSS_COLUMN_SPAN_INHERIT) {
        type = get_column_span(parent);
    }

    return set_column_span(result, type);
}


/*********************************************************************************
column_width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2012 Michael Drake <tlsa@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_column_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_normal(opv, style, state, set_column_width);
}

css_error css__set_column_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_column_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_column_width(css_select_state* state)
{
    return set_column_width(state->computed, CSS_COLUMN_WIDTH_AUTO,
        INTTOFIX(1), CSS_UNIT_EM);
}

css_error css__compose_column_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = INTTOFIX(1);
    css_unit unit = CSS_UNIT_EM;
    uint8_t type = get_column_width(child, &length, &unit);

    if (type == CSS_COLUMN_WIDTH_INHERIT) {
        type = get_column_width(parent, &length, &unit);
    }

    return set_column_width(result, type, length, unit);
}

/*********************************************************************************
content
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_content(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_CONTENT_INHERIT;
    css_computed_content_item* content = NULL;
    uint32_t n_contents = 0;

    if (isInherit(opv) == false) {
        uint32_t v = getValue(opv);

        if (v == CONTENT_NORMAL) {
            value = CSS_CONTENT_NORMAL;
        }
        else if (v == CONTENT_NONE) {
            value = CSS_CONTENT_NONE;
        }
        else {
            value = CSS_CONTENT_SET;

            while (v != CONTENT_NORMAL) {
                lwc_string* he;
                css_computed_content_item* temp;

                css__stylesheet_string_get(style->sheet,
                    *((css_code_t*)style->bytecode), &he);

                temp = realloc(content,
                    (n_contents + 1) *
                    sizeof(css_computed_content_item));
                if (temp == NULL) {
                    if (content != NULL) {
                        free(content);
                    }
                    return CSS_NOMEM;
                }

                content = temp;
                memset(content + n_contents, 0, sizeof(css_computed_content_item));

                switch (v & 0xff) {
                case CONTENT_COUNTER:
                    advance_bytecode(style, sizeof(css_code_t));

                    content[n_contents].type =
                        CSS_COMPUTED_CONTENT_COUNTER;
                    content[n_contents].data.counter.name = he;
                    content[n_contents].data.counter.style = v >> CONTENT_COUNTER_STYLE_SHIFT;
                    break;
                case CONTENT_COUNTERS:
                {
                    lwc_string* sep;

                    advance_bytecode(style, sizeof(css_code_t));

                    css__stylesheet_string_get(style->sheet, *((css_code_t*)style->bytecode), &sep);
                    advance_bytecode(style, sizeof(css_code_t));

                    content[n_contents].type =
                        CSS_COMPUTED_CONTENT_COUNTERS;
                    content[n_contents].data.counters.name = he;
                    content[n_contents].data.counters.sep = sep;
                    content[n_contents].data.counters.style = v >> CONTENT_COUNTERS_STYLE_SHIFT;
                }
                break;
                case CONTENT_URI:
                    advance_bytecode(style, sizeof(css_code_t));

                    content[n_contents].type =
                        CSS_COMPUTED_CONTENT_URI;
                    content[n_contents].data.uri = he;
                    break;
                case CONTENT_ATTR:
                    advance_bytecode(style, sizeof(css_code_t));

                    content[n_contents].type =
                        CSS_COMPUTED_CONTENT_ATTR;
                    content[n_contents].data.attr = he;
                    break;
                case CONTENT_STRING:
                    advance_bytecode(style, sizeof(css_code_t));

                    content[n_contents].type =
                        CSS_COMPUTED_CONTENT_STRING;
                    content[n_contents].data.string = he;
                    break;
                case CONTENT_OPEN_QUOTE:
                    content[n_contents].type =
                        CSS_COMPUTED_CONTENT_OPEN_QUOTE;
                    break;
                case CONTENT_CLOSE_QUOTE:
                    content[n_contents].type =
                        CSS_COMPUTED_CONTENT_CLOSE_QUOTE;
                    break;
                case CONTENT_NO_OPEN_QUOTE:
                    content[n_contents].type =
                        CSS_COMPUTED_CONTENT_NO_OPEN_QUOTE;
                    break;
                case CONTENT_NO_CLOSE_QUOTE:
                    content[n_contents].type =
                        CSS_COMPUTED_CONTENT_NO_CLOSE_QUOTE;
                    break;
                }

                n_contents++;

                v = *((uint32_t*)style->bytecode);
                advance_bytecode(style, sizeof(v));
            }
        }
    }

    /* If we have some content, terminate the array with a blank entry */
    if (n_contents > 0) {
        css_computed_content_item* temp;

        temp = realloc(content, (n_contents + 1) *
            sizeof(css_computed_content_item));
        if (temp == NULL) {
            free(content);
            return CSS_NOMEM;
        }

        content = temp;

        content[n_contents].type = CSS_COMPUTED_CONTENT_NONE;
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        css_error error;

        error = set_content(state->computed, value, content);
        if (error != CSS_OK && content != NULL)
            free(content);

        return error;
    }
    else if (content != NULL) {
        free(content);
    }

    return CSS_OK;
}

css_error css__set_content_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    css_computed_content_item* item;
    css_error error;

    error = set_content(style, hint->status, hint->data.content);

    for (item = hint->data.content; item != NULL &&
        item->type != CSS_COMPUTED_CONTENT_NONE;
        item++) {
        switch (item->type) {
        case CSS_COMPUTED_CONTENT_STRING:
            lwc_string_unref(item->data.string);
            break;
        case CSS_COMPUTED_CONTENT_URI:
            lwc_string_unref(item->data.uri);
            break;
        case CSS_COMPUTED_CONTENT_COUNTER:
            lwc_string_unref(item->data.counter.name);
            break;
        case CSS_COMPUTED_CONTENT_COUNTERS:
            lwc_string_unref(item->data.counters.name);
            lwc_string_unref(item->data.counters.sep);
            break;
        case CSS_COMPUTED_CONTENT_ATTR:
            lwc_string_unref(item->data.attr);
            break;
        default:
            break;
        }
    }

    if (error != CSS_OK && hint->data.content != NULL)
        free(hint->data.content);

    return error;
}

css_error css__initial_content(css_select_state* state)
{
    return set_content(state->computed, CSS_CONTENT_NORMAL, NULL);
}

css_error css__compose_content(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_error error;
    css_computed_content_item* copy = NULL;
    const css_computed_content_item* items = NULL;
    uint8_t type = get_content(child, &items);

    if (type == CSS_CONTENT_INHERIT) {
        type = get_content(parent, &items);
    }

    if (type == CSS_CONTENT_SET) {
        size_t n_items = 0;
        const css_computed_content_item* i;

        for (i = items; i->type != CSS_COMPUTED_CONTENT_NONE;
            i++)
            n_items++;

        copy = malloc((n_items + 1) *
            sizeof(css_computed_content_item));
        if (copy == NULL)
            return CSS_NOMEM;

        memcpy(copy, items, (n_items + 1) *
            sizeof(css_computed_content_item));
    }

    error = set_content(result, type, copy);
    if (error != CSS_OK && copy != NULL)
        free(copy);

    return error;
}

/*********************************************************************************
counter_increment
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_counter_increment(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_counter_increment_reset(opv, style, state,
        set_counter_increment);
}

css_error css__set_counter_increment_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    css_computed_counter* item;
    css_error error;

    error = set_counter_increment(style, hint->status, hint->data.counter);

    if (hint->status == CSS_COUNTER_INCREMENT_NAMED &&
        hint->data.counter != NULL) {
        for (item = hint->data.counter; item->name != NULL; item++) {
            lwc_string_unref(item->name);
        }
    }

    if (error != CSS_OK && hint->data.counter != NULL)
        free(hint->data.counter);

    return error;
}

css_error css__initial_counter_increment(css_select_state* state)
{
    return set_counter_increment(state->computed,
        CSS_COUNTER_INCREMENT_NONE, NULL);
}

css_error css__compose_counter_increment(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_error error;
    css_computed_counter* copy = NULL;
    const css_computed_counter* items = NULL;
    uint8_t type = get_counter_increment(child, &items);

    if (type == CSS_COUNTER_INCREMENT_INHERIT) {
        type = get_counter_increment(parent, &items);
    }

    if (type == CSS_COUNTER_INCREMENT_NAMED && items != NULL) {
        size_t n_items = 0;
        const css_computed_counter* i;

        for (i = items; i->name != NULL; i++)
            n_items++;

        copy = malloc((n_items + 1) *
            sizeof(css_computed_counter));
        if (copy == NULL)
            return CSS_NOMEM;

        memcpy(copy, items, (n_items + 1) *
            sizeof(css_computed_counter));
    }

    error = set_counter_increment(result, type, copy);
    if (error != CSS_OK && copy != NULL)
        free(copy);

    return error;
}

/*********************************************************************************
counter_reset
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_counter_reset(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_counter_increment_reset(opv, style, state,
        set_counter_reset);
}

css_error css__set_counter_reset_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    css_computed_counter* item;
    css_error error;

    error = set_counter_reset(style, hint->status, hint->data.counter);

    if (hint->status == CSS_COUNTER_RESET_NAMED &&
        hint->data.counter != NULL) {
        for (item = hint->data.counter; item->name != NULL; item++) {
            lwc_string_unref(item->name);
        }
    }

    if (error != CSS_OK && hint->data.counter != NULL)
        free(hint->data.counter);

    return error;
}

css_error css__initial_counter_reset(css_select_state* state)
{
    return set_counter_reset(state->computed, CSS_COUNTER_RESET_NONE, NULL);
}

css_error css__compose_counter_reset(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_error error;
    css_computed_counter* copy = NULL;
    const css_computed_counter* items = NULL;
    uint8_t type = get_counter_reset(child, &items);

    if (type == CSS_COUNTER_RESET_INHERIT) {
        type = get_counter_reset(parent, &items);
    }

    if (type == CSS_COUNTER_RESET_NAMED && items != NULL) {
        size_t n_items = 0;
        const css_computed_counter* i;

        for (i = items; i->name != NULL; i++)
            n_items++;

        copy = malloc((n_items + 1) *
            sizeof(css_computed_counter));
        if (copy == NULL)
            return CSS_NOMEM;

        memcpy(copy, items, (n_items + 1) *
            sizeof(css_computed_counter));
    }

    error = set_counter_reset(result, type, copy);
    if (error != CSS_OK && copy != NULL)
        free(copy);

    return error;
}

/*********************************************************************************
cue_after
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_cue_after(uint32_t opv, css_style* style,
    css_select_state* state)
{
    /** \todo cue-after */
    return css__cascade_uri_none(opv, style, state, NULL);
}

css_error css__set_cue_after_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_cue_after(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_cue_after(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
cue_before
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_cue_before(uint32_t opv, css_style* style,
    css_select_state* state)
{
    /** \todo cue-before */
    return css__cascade_uri_none(opv, style, state, NULL);
}

css_error css__set_cue_before_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_cue_before(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_cue_before(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
cursor
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_cursor(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_CURSOR_INHERIT;
    lwc_string** uris = NULL;
    uint32_t n_uris = 0;

    if (isInherit(opv) == false) {
        uint32_t v = getValue(opv);

        while (v == CURSOR_URI) {
            lwc_string* uri;
            lwc_string** temp;

            css__stylesheet_string_get(style->sheet,
                *((css_code_t*)style->bytecode),
                &uri);
            advance_bytecode(style, sizeof(css_code_t));

            temp = realloc(uris,
                (n_uris + 1) * sizeof(lwc_string*));
            if (temp == NULL) {
                if (uris != NULL) {
                    free(uris);
                }
                return CSS_NOMEM;
            }

            uris = temp;

            uris[n_uris] = uri;

            n_uris++;

            v = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(v));
        }

        switch (v) {
        case CURSOR_AUTO:
            value = CSS_CURSOR_AUTO;
            break;
        case CURSOR_CROSSHAIR:
            value = CSS_CURSOR_CROSSHAIR;
            break;
        case CURSOR_DEFAULT:
            value = CSS_CURSOR_DEFAULT;
            break;
        case CURSOR_POINTER:
            value = CSS_CURSOR_POINTER;
            break;
        case CURSOR_MOVE:
            value = CSS_CURSOR_MOVE;
            break;
        case CURSOR_E_RESIZE:
            value = CSS_CURSOR_E_RESIZE;
            break;
        case CURSOR_NE_RESIZE:
            value = CSS_CURSOR_NE_RESIZE;
            break;
        case CURSOR_NW_RESIZE:
            value = CSS_CURSOR_NW_RESIZE;
            break;
        case CURSOR_N_RESIZE:
            value = CSS_CURSOR_N_RESIZE;
            break;
        case CURSOR_SE_RESIZE:
            value = CSS_CURSOR_SE_RESIZE;
            break;
        case CURSOR_SW_RESIZE:
            value = CSS_CURSOR_SW_RESIZE;
            break;
        case CURSOR_S_RESIZE:
            value = CSS_CURSOR_S_RESIZE;
            break;
        case CURSOR_W_RESIZE:
            value = CSS_CURSOR_W_RESIZE;
            break;
        case CURSOR_TEXT:
            value = CSS_CURSOR_TEXT;
            break;
        case CURSOR_WAIT:
            value = CSS_CURSOR_WAIT;
            break;
        case CURSOR_HELP:
            value = CSS_CURSOR_HELP;
            break;
        case CURSOR_PROGRESS:
            value = CSS_CURSOR_PROGRESS;
            break;
        }
    }

    /* Terminate array with blank entry, if needed */
    if (n_uris > 0) {
        lwc_string** temp;

        temp = realloc(uris,
            (n_uris + 1) * sizeof(lwc_string*));
        if (temp == NULL) {
            free(uris);
            return CSS_NOMEM;
        }

        uris = temp;

        uris[n_uris] = NULL;
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        css_error error;

        error = set_cursor(state->computed, value, uris);
        if (error != CSS_OK && n_uris > 0)
            free(uris);

        return error;
    }
    else {
        if (n_uris > 0)
            free(uris);
    }

    return CSS_OK;
}

css_error css__set_cursor_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    lwc_string** item;
    css_error error;

    error = set_cursor(style, hint->status, hint->data.strings);

    for (item = hint->data.strings;
        item != NULL && (*item) != NULL; item++) {
        lwc_string_unref(*item);
    }

    if (error != CSS_OK && hint->data.strings != NULL)
        free(hint->data.strings);

    return error;
}

css_error css__initial_cursor(css_select_state* state)
{
    return set_cursor(state->computed, CSS_CURSOR_AUTO, NULL);
}

css_error css__compose_cursor(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_error error;
    lwc_string** copy = NULL;
    lwc_string** urls = NULL;
    uint8_t type = get_cursor(child, &urls);

    if (type == CSS_CURSOR_INHERIT) {
        type = get_cursor(parent, &urls);
    }

    if (urls != NULL) {
        lwc_string** i;
        size_t n_urls = 0;

        for (i = urls; (*i) != NULL; i++)
            n_urls++;

        copy = malloc((n_urls + 1) *
            sizeof(lwc_string*));
        if (copy == NULL)
            return CSS_NOMEM;

        memcpy(copy, urls, (n_urls + 1) *
            sizeof(lwc_string*));
    }

    error = set_cursor(result, type, copy);
    if (error != CSS_OK && copy != NULL)
        free(copy);

    return error;
}

/*********************************************************************************
direction
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_direction(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_DIRECTION_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case DIRECTION_LTR:
            value = CSS_DIRECTION_LTR;
            break;
        case DIRECTION_RTL:
            value = CSS_DIRECTION_RTL;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_direction(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_direction_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_direction(style, hint->status);
}

css_error css__initial_direction(css_select_state* state)
{
    return set_direction(state->computed, CSS_DIRECTION_LTR);
}

css_error css__compose_direction(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_direction(child);

    if (type == CSS_DIRECTION_INHERIT) {
        type = get_direction(parent);
    }

    return set_direction(result, type);
}


/*********************************************************************************
display
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_display(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_DISPLAY_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case DISPLAY_INLINE:
            value = CSS_DISPLAY_INLINE;
            break;
        case DISPLAY_BLOCK:
            value = CSS_DISPLAY_BLOCK;
            break;
        case DISPLAY_LIST_ITEM:
            value = CSS_DISPLAY_LIST_ITEM;
            break;
        case DISPLAY_RUN_IN:
            value = CSS_DISPLAY_RUN_IN;
            break;
        case DISPLAY_INLINE_BLOCK:
            value = CSS_DISPLAY_INLINE_BLOCK;
            break;
        case DISPLAY_TABLE:
            value = CSS_DISPLAY_TABLE;
            break;
        case DISPLAY_INLINE_TABLE:
            value = CSS_DISPLAY_INLINE_TABLE;
            break;
        case DISPLAY_TABLE_ROW_GROUP:
            value = CSS_DISPLAY_TABLE_ROW_GROUP;
            break;
        case DISPLAY_TABLE_HEADER_GROUP:
            value = CSS_DISPLAY_TABLE_HEADER_GROUP;
            break;
        case DISPLAY_TABLE_FOOTER_GROUP:
            value = CSS_DISPLAY_TABLE_FOOTER_GROUP;
            break;
        case DISPLAY_TABLE_ROW:
            value = CSS_DISPLAY_TABLE_ROW;
            break;
        case DISPLAY_TABLE_COLUMN_GROUP:
            value = CSS_DISPLAY_TABLE_COLUMN_GROUP;
            break;
        case DISPLAY_TABLE_COLUMN:
            value = CSS_DISPLAY_TABLE_COLUMN;
            break;
        case DISPLAY_TABLE_CELL:
            value = CSS_DISPLAY_TABLE_CELL;
            break;
        case DISPLAY_TABLE_CAPTION:
            value = CSS_DISPLAY_TABLE_CAPTION;
            break;
        case DISPLAY_NONE:
            value = CSS_DISPLAY_NONE;
            break;
        case DISPLAY_FLEX:
            value = CSS_DISPLAY_FLEX;
            break;
        case DISPLAY_INLINE_FLEX:
            value = CSS_DISPLAY_INLINE_FLEX;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_display(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_display_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_display(style, hint->status);
}

css_error css__initial_display(css_select_state* state)
{
    return set_display(state->computed, CSS_DISPLAY_INLINE);
}

css_error css__compose_display(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_display(child);

    if (type == CSS_DISPLAY_INHERIT) {
        type = get_display(parent);
    }

    return set_display(result, type);
}


/*********************************************************************************
elevation
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_elevation(uint32_t opv, css_style* style,
    css_select_state* state)
{
    css_fixed val = 0;
    uint32_t unit = UNIT_DEG;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case ELEVATION_ANGLE:
            val = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(val));

            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case ELEVATION_BELOW:
        case ELEVATION_LEVEL:
        case ELEVATION_ABOVE:
        case ELEVATION_HIGHER:
        case ELEVATION_LOWER:
            /** \todo convert to public values */
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo set computed elevation */
    }

    return CSS_OK;
}

css_error css__set_elevation_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_elevation(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_elevation(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
empty_cells
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_empty_cells(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_EMPTY_CELLS_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case EMPTY_CELLS_SHOW:
            value = CSS_EMPTY_CELLS_SHOW;
            break;
        case EMPTY_CELLS_HIDE:
            value = CSS_EMPTY_CELLS_HIDE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_empty_cells(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_empty_cells_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_empty_cells(style, hint->status);
}

css_error css__initial_empty_cells(css_select_state* state)
{
    return set_empty_cells(state->computed, CSS_EMPTY_CELLS_SHOW);
}

css_error css__compose_empty_cells(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_empty_cells(child);

    if (type == CSS_EMPTY_CELLS_INHERIT) {
        type = get_empty_cells(parent);
    }

    return set_empty_cells(result, type);
}


/*********************************************************************************
flex_basis
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_flex_basis(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FLEX_BASIS_INHERIT;
    css_fixed length = 0;
    uint32_t unit = UNIT_PX;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case FLEX_BASIS_AUTO:
            value = CSS_FLEX_BASIS_AUTO;
            break;
        case FLEX_BASIS_CONTENT:
            value = CSS_FLEX_BASIS_CONTENT;
            break;
        case FLEX_BASIS_SET:
            value = CSS_FLEX_BASIS_SET;
            length = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(length));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_flex_basis(state->computed, value, length, unit);
    }

    return CSS_OK;
}

css_error css__set_flex_basis_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_flex_basis(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_flex_basis(css_select_state* state)
{
    return set_flex_basis(state->computed, CSS_FLEX_BASIS_AUTO, 0,
        CSS_UNIT_PX);
}

css_error css__compose_flex_basis(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_flex_basis(child, &length, &unit);

    if (type == CSS_FLEX_BASIS_INHERIT) {
        type = get_flex_basis(parent, &length, &unit);
    }

    return set_flex_basis(result, type, length, unit);
}


/*********************************************************************************
flex_direction
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_flex_direction(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FLEX_DIRECTION_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case FLEX_DIRECTION_ROW:
            value = CSS_FLEX_DIRECTION_ROW;
            break;
        case FLEX_DIRECTION_ROW_REVERSE:
            value = CSS_FLEX_DIRECTION_ROW_REVERSE;
            break;
        case FLEX_DIRECTION_COLUMN:
            value = CSS_FLEX_DIRECTION_COLUMN;
            break;
        case FLEX_DIRECTION_COLUMN_REVERSE:
            value = CSS_FLEX_DIRECTION_COLUMN_REVERSE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_flex_direction(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_flex_direction_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_flex_direction(style, hint->status);
}

css_error css__initial_flex_direction(css_select_state* state)
{
    return set_flex_direction(state->computed, CSS_FLEX_DIRECTION_ROW);
}

css_error css__compose_flex_direction(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_flex_direction(child);

    if (type == CSS_FLEX_DIRECTION_INHERIT) {
        type = get_flex_direction(parent);
    }

    return set_flex_direction(result, type);
}


/*********************************************************************************
flex_grow
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_flex_grow(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FLEX_GROW_INHERIT;
    css_fixed flex_grow = 0;

    if (isInherit(opv) == false) {
        value = CSS_FLEX_GROW_SET;

        flex_grow = *((css_fixed*)style->bytecode);
        advance_bytecode(style, sizeof(flex_grow));
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_flex_grow(state->computed, value, flex_grow);
    }

    return CSS_OK;
}

css_error css__set_flex_grow_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_flex_grow(style, hint->status, hint->data.fixed);
}

css_error css__initial_flex_grow(css_select_state* state)
{
    return set_flex_grow(state->computed, CSS_FLEX_GROW_SET, INTTOFIX(0));
}

css_error css__compose_flex_grow(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed flex_grow = 0;
    uint8_t type = get_flex_grow(child, &flex_grow);

    if (type == CSS_FLEX_GROW_INHERIT) {
        type = get_flex_grow(parent, &flex_grow);
    }

    return set_flex_grow(result, type, flex_grow);
}


/*********************************************************************************
flex_shrink
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_flex_shrink(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FLEX_SHRINK_INHERIT;
    css_fixed flex_shrink = 0;

    if (isInherit(opv) == false) {
        value = CSS_FLEX_SHRINK_SET;

        flex_shrink = *((css_fixed*)style->bytecode);
        advance_bytecode(style, sizeof(flex_shrink));
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_flex_shrink(state->computed, value, flex_shrink);
    }

    return CSS_OK;
}

css_error css__set_flex_shrink_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_flex_shrink(style, hint->status, hint->data.fixed);
}

css_error css__initial_flex_shrink(css_select_state* state)
{
    return set_flex_shrink(state->computed, CSS_FLEX_SHRINK_SET, INTTOFIX(1));
}

css_error css__compose_flex_shrink(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed flex_shrink = 0;
    uint8_t type = get_flex_shrink(child, &flex_shrink);

    if (type == CSS_FLEX_SHRINK_INHERIT) {
        type = get_flex_shrink(parent, &flex_shrink);
    }

    return set_flex_shrink(result, type, flex_shrink);
}


/*********************************************************************************
flex_wrap
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_flex_wrap(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FLEX_WRAP_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case FLEX_WRAP_NOWRAP:
            value = CSS_FLEX_WRAP_NOWRAP;
            break;
        case FLEX_WRAP_WRAP:
            value = CSS_FLEX_WRAP_WRAP;
            break;
        case FLEX_WRAP_WRAP_REVERSE:
            value = CSS_FLEX_WRAP_WRAP_REVERSE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_flex_wrap(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_flex_wrap_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_flex_wrap(style, hint->status);
}

css_error css__initial_flex_wrap(css_select_state* state)
{
    return set_flex_wrap(state->computed, CSS_FLEX_WRAP_NOWRAP);
}

css_error css__compose_flex_wrap(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_flex_wrap(child);

    if (type == CSS_FLEX_WRAP_INHERIT) {
        type = get_flex_wrap(parent);
    }

    return set_flex_wrap(result, type);
}


/*********************************************************************************
float
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_float(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FLOAT_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case FLOAT_LEFT:
            value = CSS_FLOAT_LEFT;
            break;
        case FLOAT_RIGHT:
            value = CSS_FLOAT_RIGHT;
            break;
        case FLOAT_NONE:
            value = CSS_FLOAT_NONE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_float(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_float_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_float(style, hint->status);
}

css_error css__initial_float(css_select_state* state)
{
    return set_float(state->computed, CSS_FLOAT_NONE);
}

css_error css__compose_float(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_float(child);

    if (type == CSS_FLOAT_INHERIT) {
        type = get_float(parent);
    }

    return set_float(result, type);
}


/*********************************************************************************
font_family
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_font_family(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FONT_FAMILY_INHERIT;
    lwc_string** fonts = NULL;
    uint32_t n_fonts = 0;

    if (isInherit(opv) == false) {
        uint32_t v = getValue(opv);

        while (v != FONT_FAMILY_END) {
            lwc_string* font = NULL;
            lwc_string** temp;

            switch (v) {
            case FONT_FAMILY_STRING:
            case FONT_FAMILY_IDENT_LIST:
                css__stylesheet_string_get(style->sheet,
                    *((css_code_t*)style->bytecode),
                    &font);
                advance_bytecode(style, sizeof(css_code_t));
                break;
            case FONT_FAMILY_SERIF:
                if (value == CSS_FONT_FAMILY_INHERIT)
                    value = CSS_FONT_FAMILY_SERIF;
                break;
            case FONT_FAMILY_SANS_SERIF:
                if (value == CSS_FONT_FAMILY_INHERIT)
                    value = CSS_FONT_FAMILY_SANS_SERIF;
                break;
            case FONT_FAMILY_CURSIVE:
                if (value == CSS_FONT_FAMILY_INHERIT)
                    value = CSS_FONT_FAMILY_CURSIVE;
                break;
            case FONT_FAMILY_FANTASY:
                if (value == CSS_FONT_FAMILY_INHERIT)
                    value = CSS_FONT_FAMILY_FANTASY;
                break;
            case FONT_FAMILY_MONOSPACE:
                if (value == CSS_FONT_FAMILY_INHERIT)
                    value = CSS_FONT_FAMILY_MONOSPACE;
                break;
            }

            /* Only use family-names which occur before the first
             * generic-family. Any values which occur after the
             * first generic-family are ignored. */
             /** \todo Do this at bytecode generation time? */
            if (value == CSS_FONT_FAMILY_INHERIT && font != NULL) {
                temp = realloc(fonts,
                    (n_fonts + 1) * sizeof(lwc_string*));
                if (temp == NULL) {
                    if (fonts != NULL) {
                        free(fonts);
                    }
                    return CSS_NOMEM;
                }

                fonts = temp;

                fonts[n_fonts] = font;

                n_fonts++;
            }

            v = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(v));
        }
    }

    /* Terminate array with blank entry, if needed */
    if (n_fonts > 0) {
        lwc_string** temp;

        temp = realloc(fonts, (n_fonts + 1) * sizeof(lwc_string*));
        if (temp == NULL) {
            free(fonts);
            return CSS_NOMEM;
        }

        fonts = temp;

        fonts[n_fonts] = NULL;

        if (value == CSS_FONT_FAMILY_INHERIT) {
            /* The stylesheet doesn't specify a generic family,
             * but it has specified named fonts.
             * Fall back to the user agent's default family.
             * We don't want to inherit, because that will
             * incorrectly overwrite the named fonts list too.
             */
            css_hint hint;
            css_error error;

            error = state->handler->ua_default_for_property(
                state->pw, CSS_PROP_FONT_FAMILY, &hint);
            if (error == CSS_OK) {
                lwc_string** item;

                value = hint.status;

                for (item = hint.data.strings;
                    item != NULL && (*item) != NULL;
                    item++) {
                    lwc_string_unref(*item);
                }

                if (hint.data.strings != NULL) {
                    free(hint.data.strings);
                }
            }

            if (value == CSS_FONT_FAMILY_INHERIT) {
                /* No sane UA default: assume sans-serif */
                value = CSS_FONT_FAMILY_SANS_SERIF;
            }
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        css_error error;

        error = set_font_family(state->computed, value, fonts);
        if (error != CSS_OK && n_fonts > 0)
            free(fonts);

        return error;
    }
    else {
        if (n_fonts > 0)
            free(fonts);
    }

    return CSS_OK;
}

css_error css__set_font_family_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    lwc_string** item;
    css_error error;

    error = set_font_family(style, hint->status, hint->data.strings);

    for (item = hint->data.strings;
        item != NULL && (*item) != NULL; item++) {
        lwc_string_unref(*item);
    }

    if (error != CSS_OK && hint->data.strings != NULL)
        free(hint->data.strings);

    return error;
}

css_error css__initial_font_family(css_select_state* state)
{
    css_hint hint;
    css_error error;

    error = state->handler->ua_default_for_property(state->pw,
        CSS_PROP_FONT_FAMILY, &hint);
    if (error != CSS_OK)
        return error;

    return css__set_font_family_from_hint(&hint, state->computed);
}

css_error css__compose_font_family(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_error error;
    lwc_string** names = NULL;
    uint8_t type = get_font_family(child, &names);

    if (type == CSS_FONT_FAMILY_INHERIT || result != child) {
        size_t n_names = 0;
        lwc_string** copy = NULL;

        if (type == CSS_FONT_FAMILY_INHERIT)
            type = get_font_family(parent, &names);

        if (names != NULL) {
            lwc_string** i;

            for (i = names; (*i) != NULL; i++)
                n_names++;

            copy = malloc((n_names + 1) * sizeof(lwc_string*));
            if (copy == NULL)
                return CSS_NOMEM;

            memcpy(copy, names, (n_names + 1) *
                sizeof(lwc_string*));
        }

        error = set_font_family(result, type, copy);
        if (error != CSS_OK && copy != NULL)
            free(copy);

        return error;
    }

    return CSS_OK;
}


/*********************************************************************************
font_size
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_font_size(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FONT_SIZE_INHERIT;
    css_fixed size = 0;
    uint32_t unit = UNIT_PX;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case FONT_SIZE_DIMENSION:
            value = CSS_FONT_SIZE_DIMENSION;

            size = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(size));

            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case FONT_SIZE_XX_SMALL:
            value = CSS_FONT_SIZE_XX_SMALL;
            break;
        case FONT_SIZE_X_SMALL:
            value = CSS_FONT_SIZE_X_SMALL;
            break;
        case FONT_SIZE_SMALL:
            value = CSS_FONT_SIZE_SMALL;
            break;
        case FONT_SIZE_MEDIUM:
            value = CSS_FONT_SIZE_MEDIUM;
            break;
        case FONT_SIZE_LARGE:
            value = CSS_FONT_SIZE_LARGE;
            break;
        case FONT_SIZE_X_LARGE:
            value = CSS_FONT_SIZE_X_LARGE;
            break;
        case FONT_SIZE_XX_LARGE:
            value = CSS_FONT_SIZE_XX_LARGE;
            break;
        case FONT_SIZE_LARGER:
            value = CSS_FONT_SIZE_LARGER;
            break;
        case FONT_SIZE_SMALLER:
            value = CSS_FONT_SIZE_SMALLER;
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_font_size(state->computed, value, size, unit);
    }

    return CSS_OK;
}

css_error css__set_font_size_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_font_size(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_font_size(css_select_state* state)
{
    return set_font_size(state->computed, CSS_FONT_SIZE_MEDIUM,
        0, CSS_UNIT_PX);
}

css_error css__compose_font_size(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed size = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_font_size(child, &size, &unit);

    if (type == CSS_FONT_SIZE_INHERIT) {
        type = get_font_size(parent, &size, &unit);
    }

    return set_font_size(result, type, size, unit);
}


/*********************************************************************************
font_style
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_font_style(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FONT_STYLE_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case FONT_STYLE_NORMAL:
            value = CSS_FONT_STYLE_NORMAL;
            break;
        case FONT_STYLE_ITALIC:
            value = CSS_FONT_STYLE_ITALIC;
            break;
        case FONT_STYLE_OBLIQUE:
            value = CSS_FONT_STYLE_OBLIQUE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_font_style(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_font_style_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_font_style(style, hint->status);
}

css_error css__initial_font_style(css_select_state* state)
{
    return set_font_style(state->computed, CSS_FONT_STYLE_NORMAL);
}

css_error css__compose_font_style(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_font_style(child);

    if (type == CSS_FONT_STYLE_INHERIT) {
        type = get_font_style(parent);
    }

    return set_font_style(result, type);
}


/*********************************************************************************
font_variant
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_font_variant(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FONT_VARIANT_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case FONT_VARIANT_NORMAL:
            value = CSS_FONT_VARIANT_NORMAL;
            break;
        case FONT_VARIANT_SMALL_CAPS:
            value = CSS_FONT_VARIANT_SMALL_CAPS;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_font_variant(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_font_variant_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_font_variant(style, hint->status);
}

css_error css__initial_font_variant(css_select_state* state)
{
    return set_font_variant(state->computed, CSS_FONT_VARIANT_NORMAL);
}

css_error css__compose_font_variant(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_font_variant(child);

    if (type == CSS_FONT_VARIANT_INHERIT) {
        type = get_font_variant(parent);
    }

    return set_font_variant(result, type);
}


/*********************************************************************************
font_weight
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_font_weight(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_FONT_WEIGHT_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case FONT_WEIGHT_NORMAL:
            value = CSS_FONT_WEIGHT_NORMAL;
            break;
        case FONT_WEIGHT_BOLD:
            value = CSS_FONT_WEIGHT_BOLD;
            break;
        case FONT_WEIGHT_BOLDER:
            value = CSS_FONT_WEIGHT_BOLDER;
            break;
        case FONT_WEIGHT_LIGHTER:
            value = CSS_FONT_WEIGHT_LIGHTER;
            break;
        case FONT_WEIGHT_100:
            value = CSS_FONT_WEIGHT_100;
            break;
        case FONT_WEIGHT_200:
            value = CSS_FONT_WEIGHT_200;
            break;
        case FONT_WEIGHT_300:
            value = CSS_FONT_WEIGHT_300;
            break;
        case FONT_WEIGHT_400:
            value = CSS_FONT_WEIGHT_400;
            break;
        case FONT_WEIGHT_500:
            value = CSS_FONT_WEIGHT_500;
            break;
        case FONT_WEIGHT_600:
            value = CSS_FONT_WEIGHT_600;
            break;
        case FONT_WEIGHT_700:
            value = CSS_FONT_WEIGHT_700;
            break;
        case FONT_WEIGHT_800:
            value = CSS_FONT_WEIGHT_800;
            break;
        case FONT_WEIGHT_900:
            value = CSS_FONT_WEIGHT_900;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_font_weight(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_font_weight_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_font_weight(style, hint->status);
}

css_error css__initial_font_weight(css_select_state* state)
{
    return set_font_weight(state->computed, CSS_FONT_WEIGHT_NORMAL);
}

css_error css__compose_font_weight(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_font_weight(child);

    if (type == CSS_FONT_WEIGHT_INHERIT) {
        type = get_font_weight(parent);
    }

    return set_font_weight(result, type);
}


/*********************************************************************************
height
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_height(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_height);
}

css_error css__set_height_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_height(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_height(css_select_state* state)
{
    return set_height(state->computed, CSS_HEIGHT_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_height(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_height(child, &length, &unit);

    if (type == CSS_HEIGHT_INHERIT) {
        type = get_height(parent, &length, &unit);
    }

    return set_height(result, type, length, unit);
}


/*********************************************************************************
helpers
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include <assert.h>

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/properties/properties.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/utils/utils.h"



 /* Useful helpers */

css_unit css__to_css_unit(uint32_t u)
{
    switch (u) {
    case UNIT_PX: return CSS_UNIT_PX;
    case UNIT_EX: return CSS_UNIT_EX;
    case UNIT_EM: return CSS_UNIT_EM;
    case UNIT_IN: return CSS_UNIT_IN;
    case UNIT_CM: return CSS_UNIT_CM;
    case UNIT_MM: return CSS_UNIT_MM;
    case UNIT_PT: return CSS_UNIT_PT;
    case UNIT_PC: return CSS_UNIT_PC;
    case UNIT_CAP: return CSS_UNIT_CAP;
    case UNIT_CH: return CSS_UNIT_CH;
    case UNIT_IC: return CSS_UNIT_IC;
    case UNIT_REM: return CSS_UNIT_REM;
    case UNIT_LH: return CSS_UNIT_LH;
    case UNIT_RLH: return CSS_UNIT_RLH;
    case UNIT_VH: return CSS_UNIT_VH;
    case UNIT_VW: return CSS_UNIT_VW;
    case UNIT_VI: return CSS_UNIT_VI;
    case UNIT_VB: return CSS_UNIT_VB;
    case UNIT_VMIN: return CSS_UNIT_VMIN;
    case UNIT_VMAX: return CSS_UNIT_VMAX;
    case UNIT_Q: return CSS_UNIT_Q;
    case UNIT_PCT: return CSS_UNIT_PCT;
    case UNIT_DEG: return CSS_UNIT_DEG;
    case UNIT_GRAD: return CSS_UNIT_GRAD;
    case UNIT_RAD: return CSS_UNIT_RAD;
    case UNIT_MS: return CSS_UNIT_MS;
    case UNIT_S: return CSS_UNIT_S;
    case UNIT_HZ: return CSS_UNIT_HZ;
    case UNIT_KHZ: return CSS_UNIT_KHZ;
    }

    return 0;
}

/******************************************************************************
 * Utilities below here							      *
 ******************************************************************************/
css_error css__cascade_bg_border_color(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t, css_color))
{
    uint16_t value = CSS_BACKGROUND_COLOR_INHERIT;
    css_color color = 0;

    assert(CSS_BACKGROUND_COLOR_INHERIT ==
        (enum css_background_color_e)CSS_BORDER_COLOR_INHERIT);
    assert(CSS_BACKGROUND_COLOR_COLOR ==
        (enum css_background_color_e)CSS_BORDER_COLOR_COLOR);
    assert(CSS_BACKGROUND_COLOR_CURRENT_COLOR ==
        (enum css_background_color_e)CSS_BORDER_COLOR_CURRENT_COLOR);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BACKGROUND_COLOR_TRANSPARENT:
            value = CSS_BACKGROUND_COLOR_COLOR;
            break;
        case BACKGROUND_COLOR_CURRENT_COLOR:
            value = CSS_BACKGROUND_COLOR_CURRENT_COLOR;
            break;
        case BACKGROUND_COLOR_SET:
            value = CSS_BACKGROUND_COLOR_COLOR;
            color = *((css_color*)style->bytecode);
            advance_bytecode(style, sizeof(color));
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return fun(state->computed, value, color);
    }

    return CSS_OK;
}

css_error css__cascade_uri_none(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t,
        lwc_string*))
{
    uint16_t value = CSS_BACKGROUND_IMAGE_INHERIT;
    lwc_string* uri = NULL;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BACKGROUND_IMAGE_NONE:
            value = CSS_BACKGROUND_IMAGE_NONE;
            break;
        case BACKGROUND_IMAGE_URI:
            value = CSS_BACKGROUND_IMAGE_IMAGE;
            css__stylesheet_string_get(style->sheet, *((css_code_t*)style->bytecode), &uri);
            advance_bytecode(style, sizeof(css_code_t));
            break;
        }
    }

    /** \todo lose fun != NULL once all properties have set routines */
    if (fun != NULL && css__outranks_existing(getOpcode(opv),
        isImportant(opv), state, isInherit(opv))) {
        return fun(state->computed, value, uri);
    }

    return CSS_OK;
}

css_error css__cascade_border_style(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t))
{
    uint16_t value = CSS_BORDER_STYLE_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BORDER_STYLE_NONE:
            value = CSS_BORDER_STYLE_NONE;
            break;
        case BORDER_STYLE_HIDDEN:
            value = CSS_BORDER_STYLE_HIDDEN;
            break;
        case BORDER_STYLE_DOTTED:
            value = CSS_BORDER_STYLE_DOTTED;
            break;
        case BORDER_STYLE_DASHED:
            value = CSS_BORDER_STYLE_DASHED;
            break;
        case BORDER_STYLE_SOLID:
            value = CSS_BORDER_STYLE_SOLID;
            break;
        case BORDER_STYLE_DOUBLE:
            value = CSS_BORDER_STYLE_DOUBLE;
            break;
        case BORDER_STYLE_GROOVE:
            value = CSS_BORDER_STYLE_GROOVE;
            break;
        case BORDER_STYLE_RIDGE:
            value = CSS_BORDER_STYLE_RIDGE;
            break;
        case BORDER_STYLE_INSET:
            value = CSS_BORDER_STYLE_INSET;
            break;
        case BORDER_STYLE_OUTSET:
            value = CSS_BORDER_STYLE_OUTSET;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return fun(state->computed, value);
    }

    return CSS_OK;
}

css_error css__cascade_border_width(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t, css_fixed,
        css_unit))
{
    uint16_t value = CSS_BORDER_WIDTH_INHERIT;
    css_fixed length = 0;
    uint32_t unit = UNIT_PX;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BORDER_WIDTH_SET:
            value = CSS_BORDER_WIDTH_WIDTH;
            length = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(length));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case BORDER_WIDTH_THIN:
            value = CSS_BORDER_WIDTH_THIN;
            break;
        case BORDER_WIDTH_MEDIUM:
            value = CSS_BORDER_WIDTH_MEDIUM;
            break;
        case BORDER_WIDTH_THICK:
            value = CSS_BORDER_WIDTH_THICK;
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return fun(state->computed, value, length, unit);
    }

    return CSS_OK;
}

css_error css__cascade_length_auto(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t, css_fixed,
        css_unit))
{
    uint16_t value = CSS_BOTTOM_INHERIT;
    css_fixed length = 0;
    uint32_t unit = UNIT_PX;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BOTTOM_SET:
            value = CSS_BOTTOM_SET;
            length = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(length));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case BOTTOM_AUTO:
            value = CSS_BOTTOM_AUTO;
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return fun(state->computed, value, length, unit);
    }

    return CSS_OK;
}

css_error css__cascade_length_normal(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t, css_fixed,
        css_unit))
{
    uint16_t value = CSS_LETTER_SPACING_INHERIT;
    css_fixed length = 0;
    uint32_t unit = UNIT_PX;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case LETTER_SPACING_SET:
            value = CSS_LETTER_SPACING_SET;
            length = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(length));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case LETTER_SPACING_NORMAL:
            value = CSS_LETTER_SPACING_NORMAL;
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return fun(state->computed, value, length, unit);
    }

    return CSS_OK;
}

css_error css__cascade_length_none(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t, css_fixed,
        css_unit))
{
    uint16_t value = CSS_MAX_HEIGHT_INHERIT;
    css_fixed length = 0;
    uint32_t unit = UNIT_PX;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case MAX_HEIGHT_SET:
            value = CSS_MAX_HEIGHT_SET;
            length = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(length));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case MAX_HEIGHT_NONE:
            value = CSS_MAX_HEIGHT_NONE;
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return fun(state->computed, value, length, unit);
    }

    return CSS_OK;
}

css_error css__cascade_length(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t, css_fixed,
        css_unit))
{
    uint16_t value = CSS_MIN_HEIGHT_INHERIT;
    css_fixed length = 0;
    uint32_t unit = UNIT_PX;

    if (isInherit(opv) == false) {
        value = CSS_MIN_HEIGHT_SET;
        length = *((css_fixed*)style->bytecode);
        advance_bytecode(style, sizeof(length));
        unit = *((uint32_t*)style->bytecode);
        advance_bytecode(style, sizeof(unit));
    }

    unit = css__to_css_unit(unit);

    /** \todo lose fun != NULL once all properties have set routines */
    if (fun != NULL && css__outranks_existing(getOpcode(opv),
        isImportant(opv), state, isInherit(opv))) {
        return fun(state->computed, value, length, unit);
    }

    return CSS_OK;
}

css_error css__cascade_number(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t, css_fixed))
{
    uint16_t value = 0;
    css_fixed length = 0;

    /** \todo values */

    if (isInherit(opv) == false) {
        value = 0;
        length = *((css_fixed*)style->bytecode);
        advance_bytecode(style, sizeof(length));
    }

    /** \todo lose fun != NULL once all properties have set routines */
    if (fun != NULL && css__outranks_existing(getOpcode(opv),
        isImportant(opv), state, isInherit(opv))) {
        return fun(state->computed, value, length);
    }

    return CSS_OK;
}

css_error css__cascade_page_break_after_before_inside(uint32_t opv,
    css_style* style, css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t))
{
    uint16_t value = CSS_PAGE_BREAK_AFTER_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case PAGE_BREAK_AFTER_AUTO:
            value = CSS_PAGE_BREAK_AFTER_AUTO;
            break;
        case PAGE_BREAK_AFTER_ALWAYS:
            value = CSS_PAGE_BREAK_AFTER_ALWAYS;
            break;
        case PAGE_BREAK_AFTER_AVOID:
            value = CSS_PAGE_BREAK_AFTER_AVOID;
            break;
        case PAGE_BREAK_AFTER_LEFT:
            value = CSS_PAGE_BREAK_AFTER_LEFT;
            break;
        case PAGE_BREAK_AFTER_RIGHT:
            value = CSS_PAGE_BREAK_AFTER_RIGHT;
            break;
        }
    }

    /** \todo lose fun != NULL */
    if (fun != NULL && css__outranks_existing(getOpcode(opv),
        isImportant(opv), state, isInherit(opv))) {
        return fun(state->computed, value);
    }

    return CSS_OK;
}

css_error css__cascade_break_after_before_inside(uint32_t opv,
    css_style* style, css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t))
{
    uint16_t value = CSS_BREAK_AFTER_AUTO;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case BREAK_AFTER_AUTO:
            value = CSS_BREAK_AFTER_AUTO;
            break;
        case BREAK_AFTER_ALWAYS:
            value = CSS_BREAK_AFTER_ALWAYS;
            break;
        case BREAK_AFTER_AVOID:
            value = CSS_BREAK_AFTER_AVOID;
            break;
        case BREAK_AFTER_LEFT:
            value = CSS_BREAK_AFTER_LEFT;
            break;
        case BREAK_AFTER_RIGHT:
            value = CSS_BREAK_AFTER_RIGHT;
            break;
        case BREAK_AFTER_PAGE:
            value = CSS_BREAK_AFTER_PAGE;
            break;
        case BREAK_AFTER_COLUMN:
            value = CSS_BREAK_AFTER_COLUMN;
            break;
        case BREAK_AFTER_AVOID_PAGE:
            value = CSS_BREAK_AFTER_AVOID_PAGE;
            break;
        case BREAK_AFTER_AVOID_COLUMN:
            value = CSS_BREAK_AFTER_AVOID_COLUMN;
            break;
        }
    }

    /** \todo lose fun != NULL */
    if (fun != NULL && css__outranks_existing(getOpcode(opv),
        isImportant(opv), state, isInherit(opv))) {
        return fun(state->computed, value);
    }

    return CSS_OK;
}

css_error css__cascade_counter_increment_reset(uint32_t opv, css_style* style,
    css_select_state* state,
    css_error(*fun)(css_computed_style*, uint8_t,
        css_computed_counter*))
{
    uint16_t value = CSS_COUNTER_INCREMENT_INHERIT;
    css_computed_counter* counters = NULL;
    uint32_t n_counters = 0;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case COUNTER_INCREMENT_NAMED:
        {
            uint32_t v = getValue(opv);

            while (v != COUNTER_INCREMENT_NONE) {
                css_computed_counter* temp;
                lwc_string* name;
                css_fixed val = 0;

                css__stylesheet_string_get(style->sheet, *((css_code_t*)style->bytecode), &name);
                advance_bytecode(style, sizeof(css_code_t));

                val = *((css_fixed*)style->bytecode);
                advance_bytecode(style, sizeof(css_code_t));

                temp = realloc(counters,
                    (n_counters + 1) *
                    sizeof(css_computed_counter));
                if (temp == NULL) {
                    if (counters != NULL) {
                        free(counters);
                    }
                    return CSS_NOMEM;
                }

                counters = temp;

                counters[n_counters].name = name;
                counters[n_counters].value = val;

                n_counters++;

                v = *((uint32_t*)style->bytecode);
                advance_bytecode(style, sizeof(css_code_t));
            }
        }
        break;
        case COUNTER_INCREMENT_NONE:
            value = CSS_COUNTER_INCREMENT_NONE;
            break;
        }
    }

    /* If we have some counters, terminate the array with a blank entry */
    if (n_counters > 0) {
        css_computed_counter* temp;

        temp = realloc(counters, (n_counters + 1) *
            sizeof(css_computed_counter));
        if (temp == NULL) {
            free(counters);
            return CSS_NOMEM;
        }

        counters = temp;

        counters[n_counters].name = NULL;
        counters[n_counters].value = 0;
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        css_error error;

        error = fun(state->computed, value, counters);
        if (error != CSS_OK && n_counters > 0)
            free(counters);

        return error;
    }
    else if (n_counters > 0) {
        free(counters);
    }

    return CSS_OK;
}


/*********************************************************************************
justify_content
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_justify_content(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_JUSTIFY_CONTENT_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case JUSTIFY_CONTENT_FLEX_START:
            value = CSS_JUSTIFY_CONTENT_FLEX_START;
            break;
        case JUSTIFY_CONTENT_FLEX_END:
            value = CSS_JUSTIFY_CONTENT_FLEX_END;
            break;
        case JUSTIFY_CONTENT_CENTER:
            value = CSS_JUSTIFY_CONTENT_CENTER;
            break;
        case JUSTIFY_CONTENT_SPACE_BETWEEN:
            value = CSS_JUSTIFY_CONTENT_SPACE_BETWEEN;
            break;
        case JUSTIFY_CONTENT_SPACE_AROUND:
            value = CSS_JUSTIFY_CONTENT_SPACE_AROUND;
            break;
        case JUSTIFY_CONTENT_SPACE_EVENLY:
            value = CSS_JUSTIFY_CONTENT_SPACE_EVENLY;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_justify_content(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_justify_content_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_justify_content(style, hint->status);
}

css_error css__initial_justify_content(css_select_state* state)
{
    return set_justify_content(state->computed,
        CSS_JUSTIFY_CONTENT_FLEX_START);
}

css_error css__compose_justify_content(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_justify_content(child);

    if (type == CSS_JUSTIFY_CONTENT_INHERIT) {
        type = get_justify_content(parent);
    }

    return set_justify_content(result, type);
}


/*********************************************************************************
left
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_left(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_left);
}

css_error css__set_left_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_left(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_left(css_select_state* state)
{
    return set_left(state->computed, CSS_LEFT_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_left(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_left(child, &length, &unit);

    if (type == CSS_LEFT_INHERIT) {
        type = get_left(parent, &length, &unit);
    }

    return set_left(result, type, length, unit);
}


/*********************************************************************************
letter_spacing
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_letter_spacing(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_normal(opv, style, state, set_letter_spacing);
}

css_error css__set_letter_spacing_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_letter_spacing(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_letter_spacing(css_select_state* state)
{
    return set_letter_spacing(state->computed, CSS_LETTER_SPACING_NORMAL,
        0, CSS_UNIT_PX);
}

css_error css__compose_letter_spacing(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_letter_spacing(child, &length, &unit);

    if (type == CSS_LETTER_SPACING_INHERIT) {
        type = get_letter_spacing(parent, &length, &unit);
    }

    return set_letter_spacing(result, type, length, unit);
}

/*********************************************************************************
line_height
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_line_height(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_LINE_HEIGHT_INHERIT;
    css_fixed val = 0;
    uint32_t unit = UNIT_PX;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case LINE_HEIGHT_NUMBER:
            value = CSS_LINE_HEIGHT_NUMBER;
            val = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(val));
            break;
        case LINE_HEIGHT_DIMENSION:
            value = CSS_LINE_HEIGHT_DIMENSION;
            val = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(val));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case LINE_HEIGHT_NORMAL:
            value = CSS_LINE_HEIGHT_NORMAL;
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_line_height(state->computed, value, val, unit);
    }

    return CSS_OK;
}

css_error css__set_line_height_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_line_height(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_line_height(css_select_state* state)
{
    return set_line_height(state->computed, CSS_LINE_HEIGHT_NORMAL,
        0, CSS_UNIT_PX);
}

css_error css__compose_line_height(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_line_height(child, &length, &unit);

    if (type == CSS_LINE_HEIGHT_INHERIT) {
        type = get_line_height(parent, &length, &unit);
    }

    return set_line_height(result, type, length, unit);
}


/*********************************************************************************
list_style_image
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_list_style_image(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_uri_none(opv, style, state, set_list_style_image);
}

css_error css__set_list_style_image_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    css_error error;

    error = set_list_style_image(style, hint->status, hint->data.string);

    if (hint->data.string != NULL)
        lwc_string_unref(hint->data.string);

    return error;
}

css_error css__initial_list_style_image(css_select_state* state)
{
    return set_list_style_image(state->computed,
        CSS_LIST_STYLE_IMAGE_NONE, NULL);
}

css_error css__compose_list_style_image(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    lwc_string* url;
    uint8_t type = get_list_style_image(child, &url);

    if (type == CSS_LIST_STYLE_IMAGE_INHERIT) {
        type = get_list_style_image(parent, &url);
    }

    return set_list_style_image(result, type, url);
}


/*********************************************************************************
list_style_position
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_list_style_position(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_LIST_STYLE_POSITION_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case LIST_STYLE_POSITION_INSIDE:
            value = CSS_LIST_STYLE_POSITION_INSIDE;
            break;
        case LIST_STYLE_POSITION_OUTSIDE:
            value = CSS_LIST_STYLE_POSITION_OUTSIDE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_list_style_position(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_list_style_position_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_list_style_position(style, hint->status);
}

css_error css__initial_list_style_position(css_select_state* state)
{
    return set_list_style_position(state->computed,
        CSS_LIST_STYLE_POSITION_OUTSIDE);
}

css_error css__compose_list_style_position(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_list_style_position(child);

    if (type == CSS_LIST_STYLE_POSITION_INHERIT) {
        type = get_list_style_position(parent);
    }

    return set_list_style_position(result, type);
}


/*********************************************************************************
list_style_type
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_list_style_type(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_LIST_STYLE_TYPE_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case LIST_STYLE_TYPE_DISC:
            value = CSS_LIST_STYLE_TYPE_DISC;
            break;
        case LIST_STYLE_TYPE_CIRCLE:
            value = CSS_LIST_STYLE_TYPE_CIRCLE;
            break;
        case LIST_STYLE_TYPE_SQUARE:
            value = CSS_LIST_STYLE_TYPE_SQUARE;
            break;
        case LIST_STYLE_TYPE_DECIMAL:
            value = CSS_LIST_STYLE_TYPE_DECIMAL;
            break;
        case LIST_STYLE_TYPE_DECIMAL_LEADING_ZERO:
            value = CSS_LIST_STYLE_TYPE_DECIMAL_LEADING_ZERO;
            break;
        case LIST_STYLE_TYPE_LOWER_ROMAN:
            value = CSS_LIST_STYLE_TYPE_LOWER_ROMAN;
            break;
        case LIST_STYLE_TYPE_UPPER_ROMAN:
            value = CSS_LIST_STYLE_TYPE_UPPER_ROMAN;
            break;
        case LIST_STYLE_TYPE_LOWER_GREEK:
            value = CSS_LIST_STYLE_TYPE_LOWER_GREEK;
            break;
        case LIST_STYLE_TYPE_LOWER_LATIN:
            value = CSS_LIST_STYLE_TYPE_LOWER_LATIN;
            break;
        case LIST_STYLE_TYPE_UPPER_LATIN:
            value = CSS_LIST_STYLE_TYPE_UPPER_LATIN;
            break;
        case LIST_STYLE_TYPE_ARMENIAN:
            value = CSS_LIST_STYLE_TYPE_ARMENIAN;
            break;
        case LIST_STYLE_TYPE_GEORGIAN:
            value = CSS_LIST_STYLE_TYPE_GEORGIAN;
            break;
        case LIST_STYLE_TYPE_LOWER_ALPHA:
            value = CSS_LIST_STYLE_TYPE_LOWER_ALPHA;
            break;
        case LIST_STYLE_TYPE_UPPER_ALPHA:
            value = CSS_LIST_STYLE_TYPE_UPPER_ALPHA;
            break;
        case LIST_STYLE_TYPE_NONE:
            value = CSS_LIST_STYLE_TYPE_NONE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_list_style_type(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_list_style_type_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_list_style_type(style, hint->status);
}

css_error css__initial_list_style_type(css_select_state* state)
{
    return set_list_style_type(state->computed, CSS_LIST_STYLE_TYPE_DISC);
}

css_error css__compose_list_style_type(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_list_style_type(child);

    if (type == CSS_LIST_STYLE_TYPE_INHERIT) {
        type = get_list_style_type(parent);
    }

    return set_list_style_type(result, type);
}


/*********************************************************************************
margin_bottom
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_margin_bottom(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_margin_bottom);
}

css_error css__set_margin_bottom_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_margin_bottom(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_margin_bottom(css_select_state* state)
{
    return set_margin_bottom(state->computed, CSS_MARGIN_SET, 0, CSS_UNIT_PX);
}

css_error css__compose_margin_bottom(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_margin_bottom(child, &length, &unit);

    if (type == CSS_MARGIN_INHERIT) {
        type = get_margin_bottom(parent, &length, &unit);
    }

    return set_margin_bottom(result, type, length, unit);
}


/*********************************************************************************
margin_left
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_margin_left(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_margin_left);
}

css_error css__set_margin_left_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_margin_left(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_margin_left(css_select_state* state)
{
    return set_margin_left(state->computed, CSS_MARGIN_SET, 0, CSS_UNIT_PX);
}

css_error css__compose_margin_left(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_margin_left(child, &length, &unit);

    if (type == CSS_MARGIN_INHERIT) {
        type = get_margin_left(parent, &length, &unit);
    }

    return set_margin_left(result, type, length, unit);
}


/*********************************************************************************
margin_right
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_margin_right(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_margin_right);
}

css_error css__set_margin_right_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_margin_right(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_margin_right(css_select_state* state)
{
    return set_margin_right(state->computed, CSS_MARGIN_SET, 0, CSS_UNIT_PX);
}

css_error css__compose_margin_right(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_margin_right(child, &length, &unit);

    if (type == CSS_MARGIN_INHERIT) {
        type = get_margin_right(parent, &length, &unit);
    }

    return set_margin_right(result, type, length, unit);
}


/*********************************************************************************
margin_top
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_margin_top(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_margin_top);
}

css_error css__set_margin_top_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_margin_top(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_margin_top(css_select_state* state)
{
    return set_margin_top(state->computed, CSS_MARGIN_SET, 0, CSS_UNIT_PX);
}

css_error css__compose_margin_top(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_margin_top(child, &length, &unit);

    if (type == CSS_MARGIN_INHERIT) {
        type = get_margin_top(parent, &length, &unit);
    }

    return set_margin_top(result, type, length, unit);
}


/*********************************************************************************
max_height
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_max_height(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_none(opv, style, state, set_max_height);
}

css_error css__set_max_height_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_max_height(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_max_height(css_select_state* state)
{
    return set_max_height(state->computed, CSS_MAX_HEIGHT_NONE,
        0, CSS_UNIT_PX);
}

css_error css__compose_max_height(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_max_height(child, &length, &unit);

    if (type == CSS_MAX_HEIGHT_INHERIT) {
        type = get_max_height(parent, &length, &unit);
    }

    return set_max_height(result, type, length, unit);
}


/*********************************************************************************
max_width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_max_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_none(opv, style, state, set_max_width);;
}

css_error css__set_max_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_max_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_max_width(css_select_state* state)
{
    return set_max_width(state->computed, CSS_MAX_WIDTH_NONE, 0, CSS_UNIT_PX);
}

css_error css__compose_max_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_max_width(child, &length, &unit);

    if (type == CSS_MAX_WIDTH_INHERIT) {
        type = get_max_width(parent, &length, &unit);
    }

    return set_max_width(result, type, length, unit);
}


/*********************************************************************************
min_height
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_min_height(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_min_height);
}

css_error css__set_min_height_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_min_height(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_min_height(css_select_state* state)
{
    return set_min_height(state->computed, CSS_MIN_HEIGHT_AUTO,
        0, CSS_UNIT_PX);
}

css_error css__compose_min_height(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_min_height(child, &length, &unit);

    if (type == CSS_MIN_HEIGHT_INHERIT) {
        type = get_min_height(parent, &length, &unit);
    }

    return set_min_height(result, type, length, unit);
}


/*********************************************************************************
min_width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_min_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_min_width);
}

css_error css__set_min_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_min_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_min_width(css_select_state* state)
{
    return set_min_width(state->computed, CSS_MIN_WIDTH_AUTO,
        0, CSS_UNIT_PX);
}

css_error css__compose_min_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_min_width(child, &length, &unit);

    if (type == CSS_MIN_WIDTH_INHERIT) {
        type = get_min_width(parent, &length, &unit);
    }

    return set_min_width(result, type, length, unit);
}


/*********************************************************************************
opacity
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2011 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_opacity(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_OPACITY_INHERIT;
    css_fixed opacity = 0;

    if (isInherit(opv) == false) {
        value = CSS_Z_INDEX_SET;

        opacity = *((css_fixed*)style->bytecode);
        advance_bytecode(style, sizeof(opacity));
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_opacity(state->computed, value, opacity);
    }

    return CSS_OK;
}

css_error css__set_opacity_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_opacity(style, hint->status, hint->data.fixed);
}

css_error css__initial_opacity(css_select_state* state)
{
    return set_opacity(state->computed, CSS_OPACITY_SET, INTTOFIX(1));
}

css_error css__compose_opacity(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed opacity = 0;
    uint8_t type = get_opacity(child, &opacity);

    if (type == CSS_OPACITY_INHERIT) {
        type = get_opacity(parent, &opacity);
    }

    return set_opacity(result, type, opacity);
}


/*********************************************************************************
order
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2017 Lucas Neves <lcneves@gmail.com>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_order(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_ORDER_INHERIT;
    css_fixed order = 0;

    if (isInherit(opv) == false) {
        value = CSS_ORDER_SET;

        order = FIXTOINT(*((css_fixed*)style->bytecode));
        advance_bytecode(style, sizeof(order));
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_order(state->computed, value, order);
    }

    return CSS_OK;
}

css_error css__set_order_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_order(style, hint->status, hint->data.integer);
}

css_error css__initial_order(css_select_state* state)
{
    return set_order(state->computed, CSS_ORDER_SET, 0);
}

css_error css__compose_order(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    int32_t order = 0;
    uint8_t type = get_order(child, &order);

    if (type == CSS_ORDER_INHERIT) {
        type = get_order(parent, &order);
    }

    return set_order(result, type, order);
}


/*********************************************************************************
orphans
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_orphans(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_number(opv, style, state, set_orphans);
}

css_error css__set_orphans_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_orphans(style, hint->status, hint->data.integer);
}

css_error css__initial_orphans(css_select_state* state)
{
    return set_orphans(state->computed, CSS_ORPHANS_SET, 2);
}

css_error css__compose_orphans(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    int32_t count = 0;
    uint8_t type = get_orphans(child, &count);

    if (type == CSS_ORPHANS_INHERIT) {
        type = get_orphans(parent, &count);
    }

    return set_orphans(result, type, count);
}


/*********************************************************************************
outline_color
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_outline_color(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_OUTLINE_COLOR_INHERIT;
    css_color color = 0;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case OUTLINE_COLOR_TRANSPARENT:
            value = CSS_OUTLINE_COLOR_COLOR;
            break;
        case OUTLINE_COLOR_CURRENT_COLOR:
            value = CSS_OUTLINE_COLOR_CURRENT_COLOR;
            break;
        case OUTLINE_COLOR_SET:
            value = CSS_OUTLINE_COLOR_COLOR;
            color = *((css_color*)style->bytecode);
            advance_bytecode(style, sizeof(color));
            break;
        case OUTLINE_COLOR_INVERT:
            value = CSS_OUTLINE_COLOR_INVERT;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_outline_color(state->computed, value, color);
    }

    return CSS_OK;
}

css_error css__set_outline_color_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_outline_color(style, hint->status, hint->data.color);
}

css_error css__initial_outline_color(css_select_state* state)
{
    return set_outline_color(state->computed, CSS_OUTLINE_COLOR_INVERT, 0);
}

css_error css__compose_outline_color(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_color color = 0;
    uint8_t type = get_outline_color(child, &color);

    if (type == CSS_OUTLINE_COLOR_INHERIT) {
        type = get_outline_color(parent, &color);
    }

    return set_outline_color(result, type, color);
}

/*********************************************************************************
outline_style
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_outline_style(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_style(opv, style, state, set_outline_style);
}

css_error css__set_outline_style_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_outline_style(style, hint->status);
}

css_error css__initial_outline_style(css_select_state* state)
{
    return set_outline_style(state->computed, CSS_OUTLINE_STYLE_NONE);
}

css_error css__compose_outline_style(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_outline_style(child);

    if (type == CSS_OUTLINE_STYLE_INHERIT) {
        type = get_outline_style(parent);
    }

    return set_outline_style(result, type);
}


/*********************************************************************************
outline_width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_outline_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_border_width(opv, style, state, set_outline_width);
}

css_error css__set_outline_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_outline_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_outline_width(css_select_state* state)
{
    return set_outline_width(state->computed, CSS_OUTLINE_WIDTH_MEDIUM,
        0, CSS_UNIT_PX);
}

css_error css__compose_outline_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_outline_width(child, &length, &unit);

    if (type == CSS_OUTLINE_WIDTH_INHERIT) {
        type = get_outline_width(parent, &length, &unit);
    }

    return set_outline_width(result, type, length, unit);
}


/*********************************************************************************
overflow_x
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_overflow_x(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_OVERFLOW_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case OVERFLOW_VISIBLE:
            value = CSS_OVERFLOW_VISIBLE;
            break;
        case OVERFLOW_HIDDEN:
            value = CSS_OVERFLOW_HIDDEN;
            break;
        case OVERFLOW_SCROLL:
            value = CSS_OVERFLOW_SCROLL;
            break;
        case OVERFLOW_AUTO:
            value = CSS_OVERFLOW_AUTO;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_overflow_x(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_overflow_x_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_overflow_x(style, hint->status);
}

css_error css__initial_overflow_x(css_select_state* state)
{
    return set_overflow_x(state->computed, CSS_OVERFLOW_VISIBLE);
}

css_error css__compose_overflow_x(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_overflow_x(child);

    if (type == CSS_OVERFLOW_INHERIT) {
        type = get_overflow_x(parent);
    }

    return set_overflow_x(result, type);
}


/*********************************************************************************
overflow_y
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_overflow_y(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_OVERFLOW_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case OVERFLOW_VISIBLE:
            value = CSS_OVERFLOW_VISIBLE;
            break;
        case OVERFLOW_HIDDEN:
            value = CSS_OVERFLOW_HIDDEN;
            break;
        case OVERFLOW_SCROLL:
            value = CSS_OVERFLOW_SCROLL;
            break;
        case OVERFLOW_AUTO:
            value = CSS_OVERFLOW_AUTO;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_overflow_y(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_overflow_y_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_overflow_y(style, hint->status);
}

css_error css__initial_overflow_y(css_select_state* state)
{
    return set_overflow_y(state->computed, CSS_OVERFLOW_VISIBLE);
}

css_error css__compose_overflow_y(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_overflow_y(child);

    if (type == CSS_OVERFLOW_INHERIT) {
        type = get_overflow_y(parent);
    }

    return set_overflow_y(result, type);
}


/*********************************************************************************
padding_bottom
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_padding_bottom(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length(opv, style, state, set_padding_bottom);
}

css_error css__set_padding_bottom_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_padding_bottom(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_padding_bottom(css_select_state* state)
{
    return set_padding_bottom(state->computed, CSS_PADDING_SET,
        0, CSS_UNIT_PX);
}

css_error css__compose_padding_bottom(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_padding_bottom(child, &length, &unit);

    if (type == CSS_PADDING_INHERIT) {
        type = get_padding_bottom(parent, &length, &unit);
    }

    return set_padding_bottom(result, type, length, unit);
}


/*********************************************************************************
padding_left
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_padding_left(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length(opv, style, state, set_padding_left);
}

css_error css__set_padding_left_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_padding_left(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_padding_left(css_select_state* state)
{
    return set_padding_left(state->computed, CSS_PADDING_SET, 0, CSS_UNIT_PX);
}

css_error css__compose_padding_left(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_padding_left(child, &length, &unit);

    if (type == CSS_PADDING_INHERIT) {
        type = get_padding_left(parent, &length, &unit);
    }

    return set_padding_left(result, type, length, unit);
}


/*********************************************************************************
padding_right
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_padding_right(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length(opv, style, state, set_padding_right);
}

css_error css__set_padding_right_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_padding_right(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_padding_right(css_select_state* state)
{
    return set_padding_right(state->computed, CSS_PADDING_SET,
        0, CSS_UNIT_PX);
}

css_error css__compose_padding_right(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_padding_right(child, &length, &unit);

    if (type == CSS_PADDING_INHERIT) {
        type = get_padding_right(parent, &length, &unit);
    }

    return set_padding_right(result, type, length, unit);
}


/*********************************************************************************
padding_top
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_padding_top(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length(opv, style, state, set_padding_top);
}

css_error css__set_padding_top_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_padding_top(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_padding_top(css_select_state* state)
{
    return set_padding_top(state->computed, CSS_PADDING_SET, 0, CSS_UNIT_PX);
}

css_error css__compose_padding_top(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_padding_top(child, &length, &unit);

    if (type == CSS_PADDING_INHERIT) {
        type = get_padding_top(parent, &length, &unit);
    }

    return set_padding_top(result, type, length, unit);
}


/*********************************************************************************
page_break_after
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_page_break_after(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_page_break_after_before_inside(opv, style, state,
        set_page_break_after);
}

css_error css__set_page_break_after_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_page_break_after(style, hint->status);
}

css_error css__initial_page_break_after(css_select_state* state)
{
    return set_page_break_after(state->computed,
        CSS_PAGE_BREAK_AFTER_AUTO);
}

css_error css__compose_page_break_after(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_page_break_after(child);

    if (type == CSS_PAGE_BREAK_AFTER_INHERIT) {
        type = get_page_break_after(parent);
    }

    return set_page_break_after(result, type);
}


/*********************************************************************************
page_break_before
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_page_break_before(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_page_break_after_before_inside(opv, style, state,
        set_page_break_before);
}

css_error css__set_page_break_before_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_page_break_before(style, hint->status);
}

css_error css__initial_page_break_before(css_select_state* state)
{
    return set_page_break_before(state->computed,
        CSS_PAGE_BREAK_BEFORE_AUTO);
}

css_error css__compose_page_break_before(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_page_break_before(child);

    if (type == CSS_PAGE_BREAK_BEFORE_INHERIT) {
        type = get_page_break_before(parent);
    }

    return set_page_break_before(result, type);
}

/*********************************************************************************
page_break_inside
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_page_break_inside(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_page_break_after_before_inside(opv, style, state,
        set_page_break_inside);
}

css_error css__set_page_break_inside_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_page_break_inside(style, hint->status);
}

css_error css__initial_page_break_inside(css_select_state* state)
{
    return set_page_break_inside(state->computed,
        CSS_PAGE_BREAK_INSIDE_AUTO);
}

css_error css__compose_page_break_inside(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_page_break_inside(child);

    if (type == CSS_PAGE_BREAK_INSIDE_INHERIT) {
        type = get_page_break_inside(parent);
    }

    return set_page_break_inside(result, type);
}


/*********************************************************************************
pause_after
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_pause_after(uint32_t opv, css_style* style,
    css_select_state* state)
{
    /** \todo pause-after */
    return css__cascade_length(opv, style, state, NULL);
}

css_error css__set_pause_after_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_pause_after(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_pause_after(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
pause_before
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_pause_before(uint32_t opv, css_style* style,
    css_select_state* state)
{
    /** \todo pause-before */
    return css__cascade_length(opv, style, state, NULL);
}

css_error css__set_pause_before_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_pause_before(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_pause_before(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
pitch
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_pitch(uint32_t opv, css_style* style,
    css_select_state* state)
{
    css_fixed freq = 0;
    uint32_t unit = UNIT_HZ;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case PITCH_FREQUENCY:
            freq = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(freq));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case PITCH_X_LOW:
        case PITCH_LOW:
        case PITCH_MEDIUM:
        case PITCH_HIGH:
        case PITCH_X_HIGH:
            /** \todo convert to public values */
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo pitch */
    }

    return CSS_OK;
}

css_error css__set_pitch_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_pitch(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_pitch(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
pitch_range
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_pitch_range(uint32_t opv, css_style* style,
    css_select_state* state)
{
    /** \todo pitch-range */
    return css__cascade_number(opv, style, state, NULL);
}

css_error css__set_pitch_range_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_pitch_range(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_pitch_range(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
play_during
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_play_during(uint32_t opv, css_style* style,
    css_select_state* state)
{
    lwc_string* uri = NULL;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case PLAY_DURING_URI:
            css__stylesheet_string_get(style->sheet, *((css_code_t*)style->bytecode), &uri);
            advance_bytecode(style, sizeof(css_code_t));
            break;
        case PLAY_DURING_AUTO:
        case PLAY_DURING_NONE:
            /** \todo convert to public values */
            break;
        }

        /** \todo mix & repeat */
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo play-during */
    }

    return CSS_OK;
}

css_error css__set_play_during_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_play_during(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_play_during(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
position
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_position(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_POSITION_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case POSITION_STATIC:
            value = CSS_POSITION_STATIC;
            break;
        case POSITION_RELATIVE:
            value = CSS_POSITION_RELATIVE;
            break;
        case POSITION_ABSOLUTE:
            value = CSS_POSITION_ABSOLUTE;
            break;
        case POSITION_FIXED:
            value = CSS_POSITION_FIXED;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_position(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_position_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_position(style, hint->status);
}

css_error css__initial_position(css_select_state* state)
{
    return set_position(state->computed, CSS_POSITION_STATIC);
}

css_error css__compose_position(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_position(child);

    if (type == CSS_POSITION_INHERIT) {
        type = get_position(parent);
    }

    return set_position(result, type);
}


/*********************************************************************************
quotes
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_quotes(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_QUOTES_INHERIT;
    lwc_string** quotes = NULL;
    uint32_t n_quotes = 0;

    if (isInherit(opv) == false) {
        uint32_t v = getValue(opv);

        value = CSS_QUOTES_STRING;

        while (v != QUOTES_NONE) {
            lwc_string* open, * close;
            lwc_string** temp;

            css__stylesheet_string_get(style->sheet,
                *((css_code_t*)style->bytecode),
                &open);
            advance_bytecode(style, sizeof(css_code_t));

            css__stylesheet_string_get(style->sheet,
                *((css_code_t*)style->bytecode),
                &close);
            advance_bytecode(style, sizeof(css_code_t));

            temp = realloc(quotes,
                (n_quotes + 2) * sizeof(lwc_string*));
            if (temp == NULL) {
                if (quotes != NULL) {
                    free(quotes);
                }
                return CSS_NOMEM;
            }

            quotes = temp;

            quotes[n_quotes++] = open;
            quotes[n_quotes++] = close;

            v = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(v));
        }
    }

    /* Terminate array, if required */
    if (n_quotes > 0) {
        lwc_string** temp;

        temp = realloc(quotes, (n_quotes + 1) * sizeof(lwc_string*));
        if (temp == NULL) {
            free(quotes);
            return CSS_NOMEM;
        }

        quotes = temp;

        quotes[n_quotes] = NULL;
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        css_error error;

        error = set_quotes(state->computed, value, quotes);
        if (error != CSS_OK && quotes != NULL)
            free(quotes);

        return error;
    }
    else {
        if (quotes != NULL)
            free(quotes);
    }

    return CSS_OK;
}

css_error css__set_quotes_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    lwc_string** item;
    css_error error;

    error = set_quotes(style, hint->status, hint->data.strings);

    for (item = hint->data.strings;
        item != NULL && (*item) != NULL; item++) {
        lwc_string_unref(*item);
    }

    if (error != CSS_OK && hint->data.strings != NULL)
        free(hint->data.strings);

    return error;
}

css_error css__initial_quotes(css_select_state* state)
{
    css_hint hint;
    css_error error;

    error = state->handler->ua_default_for_property(state->pw,
        CSS_PROP_QUOTES, &hint);
    if (error != CSS_OK)
        return error;

    return css__set_quotes_from_hint(&hint, state->computed);
}

css_error css__compose_quotes(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_error error;
    lwc_string** quotes = NULL;
    uint8_t type = get_quotes(child, &quotes);

    if (type == CSS_QUOTES_INHERIT || result != child) {
        size_t n_quotes = 0;
        lwc_string** copy = NULL;

        if (type == CSS_QUOTES_INHERIT) {
            type = get_quotes(parent, &quotes);
        }

        if (quotes != NULL) {
            lwc_string** i;

            for (i = quotes; (*i) != NULL; i++)
                n_quotes++;

            copy = malloc((n_quotes + 1) * sizeof(lwc_string*));
            if (copy == NULL)
                return CSS_NOMEM;

            memcpy(copy, quotes, (n_quotes + 1) *
                sizeof(lwc_string*));
        }

        error = set_quotes(result, type, copy);
        if (error != CSS_OK && copy != NULL)
            free(copy);

        return error;
    }

    return CSS_OK;
}


/*********************************************************************************
richness
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_richness(uint32_t opv, css_style* style,
    css_select_state* state)
{
    /** \todo richness */
    return css__cascade_number(opv, style, state, NULL);
}

css_error css__set_richness_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_richness(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_richness(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
right
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_right(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_right);
}

css_error css__set_right_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_right(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_right(css_select_state* state)
{
    return set_right(state->computed, CSS_RIGHT_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_right(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_right(child, &length, &unit);

    if (type == CSS_RIGHT_INHERIT) {
        type = get_right(parent, &length, &unit);
    }

    return set_right(result, type, length, unit);
}


/*********************************************************************************
speak
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_speak(uint32_t opv, css_style* style,
    css_select_state* state)
{
    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case SPEAK_NORMAL:
        case SPEAK_NONE:
        case SPEAK_SPELL_OUT:
            /** \todo convert to public values */
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo speak */
    }

    return CSS_OK;
}

css_error css__set_speak_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_speak(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_speak(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
speak_header
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_speak_header(uint32_t opv, css_style* style,
    css_select_state* state)
{
    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case SPEAK_HEADER_ONCE:
        case SPEAK_HEADER_ALWAYS:
            /** \todo convert to public values */
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo speak-header */
    }

    return CSS_OK;
}

css_error css__set_speak_header_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_speak_header(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_speak_header(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
speak_numeral
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_speak_numeral(uint32_t opv, css_style* style,
    css_select_state* state)
{
    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case SPEAK_NUMERAL_DIGITS:
        case SPEAK_NUMERAL_CONTINUOUS:
            /** \todo convert to public values */
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo speak-numeral */
    }

    return CSS_OK;
}

css_error css__set_speak_numeral_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_speak_numeral(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_speak_numeral(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
speak_punctuation
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_speak_punctuation(
    uint32_t opv, css_style* style, css_select_state* state)
{
    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case SPEAK_PUNCTUATION_CODE:
        case SPEAK_PUNCTUATION_NONE:
            /** \todo convert to public values */
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo speak-punctuation */
    }

    return CSS_OK;
}

css_error css__set_speak_punctuation_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_speak_punctuation(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_speak_punctuation(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
speech_rate
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_speech_rate(uint32_t opv, css_style* style,
    css_select_state* state)
{
    css_fixed rate = 0;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case SPEECH_RATE_SET:
            rate = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(rate));
            break;
        case SPEECH_RATE_X_SLOW:
        case SPEECH_RATE_SLOW:
        case SPEECH_RATE_MEDIUM:
        case SPEECH_RATE_FAST:
        case SPEECH_RATE_X_FAST:
        case SPEECH_RATE_FASTER:
        case SPEECH_RATE_SLOWER:
            /** \todo convert to public values */
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo speech-rate */
    }

    return CSS_OK;
}

css_error css__set_speech_rate_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_speech_rate(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_speech_rate(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
stress
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_stress(uint32_t opv, css_style* style,
    css_select_state* state)
{
    /** \todo stress */
    return css__cascade_number(opv, style, state, NULL);
}

css_error css__set_stress_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_stress(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_stress(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
table_layout
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_table_layout(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_TABLE_LAYOUT_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case TABLE_LAYOUT_AUTO:
            value = CSS_TABLE_LAYOUT_AUTO;
            break;
        case TABLE_LAYOUT_FIXED:
            value = CSS_TABLE_LAYOUT_FIXED;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_table_layout(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_table_layout_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_table_layout(style, hint->status);
}

css_error css__initial_table_layout(css_select_state* state)
{
    return set_table_layout(state->computed, CSS_TABLE_LAYOUT_AUTO);
}

css_error css__compose_table_layout(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_table_layout(child);

    if (type == CSS_TABLE_LAYOUT_INHERIT) {
        type = get_table_layout(parent);
    }

    return set_table_layout(result, type);
}


/*********************************************************************************
text_align
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_text_align(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_TEXT_ALIGN_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case TEXT_ALIGN_LEFT:
            value = CSS_TEXT_ALIGN_LEFT;
            break;
        case TEXT_ALIGN_RIGHT:
            value = CSS_TEXT_ALIGN_RIGHT;
            break;
        case TEXT_ALIGN_CENTER:
            value = CSS_TEXT_ALIGN_CENTER;
            break;
        case TEXT_ALIGN_JUSTIFY:
            value = CSS_TEXT_ALIGN_JUSTIFY;
            break;
        case TEXT_ALIGN_LIBCSS_LEFT:
            value = CSS_TEXT_ALIGN_LIBCSS_LEFT;
            break;
        case TEXT_ALIGN_LIBCSS_CENTER:
            value = CSS_TEXT_ALIGN_LIBCSS_CENTER;
            break;
        case TEXT_ALIGN_LIBCSS_RIGHT:
            value = CSS_TEXT_ALIGN_LIBCSS_RIGHT;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_text_align(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_text_align_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_text_align(style, hint->status);
}

css_error css__initial_text_align(css_select_state* state)
{
    return set_text_align(state->computed, CSS_TEXT_ALIGN_DEFAULT);
}

css_error css__compose_text_align(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_text_align(child);

    if (type == CSS_TEXT_ALIGN_INHERIT) {
        type = get_text_align(parent);
    }
    else if (type == CSS_TEXT_ALIGN_INHERIT_IF_NON_MAGIC) {
        /* This is purely for the benefit of HTML tables */
        type = get_text_align(parent);

        /* If the parent's text-align is a magical one,
         * then reset to the default value. Otherwise,
         * inherit as normal. */
        if (type == CSS_TEXT_ALIGN_LIBCSS_LEFT ||
            type == CSS_TEXT_ALIGN_LIBCSS_CENTER ||
            type == CSS_TEXT_ALIGN_LIBCSS_RIGHT)
            type = CSS_TEXT_ALIGN_DEFAULT;
    }

    return set_text_align(result, type);
}


/*********************************************************************************
text_decoration
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include <assert.h>

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_text_decoration(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_TEXT_DECORATION_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        if (getValue(opv) == TEXT_DECORATION_NONE) {
            value = CSS_TEXT_DECORATION_NONE;
        }
        else {
            assert(value == 0);

            if (getValue(opv) & TEXT_DECORATION_UNDERLINE)
                value |= CSS_TEXT_DECORATION_UNDERLINE;
            if (getValue(opv) & TEXT_DECORATION_OVERLINE)
                value |= CSS_TEXT_DECORATION_OVERLINE;
            if (getValue(opv) & TEXT_DECORATION_LINE_THROUGH)
                value |= CSS_TEXT_DECORATION_LINE_THROUGH;
            if (getValue(opv) & TEXT_DECORATION_BLINK)
                value |= CSS_TEXT_DECORATION_BLINK;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_text_decoration(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_text_decoration_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_text_decoration(style, hint->status);
}

css_error css__initial_text_decoration(css_select_state* state)
{
    return set_text_decoration(state->computed, CSS_TEXT_DECORATION_NONE);
}

css_error css__compose_text_decoration(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_text_decoration(child);

    if (type == CSS_TEXT_DECORATION_INHERIT) {
        type = get_text_decoration(parent);
    }

    return set_text_decoration(result, type);
}


/*********************************************************************************
text_indent
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_text_indent(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length(opv, style, state, set_text_indent);
}

css_error css__set_text_indent_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_text_indent(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_text_indent(css_select_state* state)
{
    return set_text_indent(state->computed, CSS_TEXT_INDENT_SET,
        0, CSS_UNIT_PX);
}

css_error css__compose_text_indent(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_text_indent(child, &length, &unit);

    if (type == CSS_TEXT_INDENT_INHERIT) {
        type = get_text_indent(parent, &length, &unit);
    }

    return set_text_indent(result, type, length, unit);
}


/*********************************************************************************
text_transform
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_text_transform(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_TEXT_TRANSFORM_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case TEXT_TRANSFORM_CAPITALIZE:
            value = CSS_TEXT_TRANSFORM_CAPITALIZE;
            break;
        case TEXT_TRANSFORM_UPPERCASE:
            value = CSS_TEXT_TRANSFORM_UPPERCASE;
            break;
        case TEXT_TRANSFORM_LOWERCASE:
            value = CSS_TEXT_TRANSFORM_LOWERCASE;
            break;
        case TEXT_TRANSFORM_NONE:
            value = CSS_TEXT_TRANSFORM_NONE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_text_transform(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_text_transform_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_text_transform(style, hint->status);
}

css_error css__initial_text_transform(css_select_state* state)
{
    return set_text_transform(state->computed, CSS_TEXT_TRANSFORM_NONE);
}

css_error css__compose_text_transform(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_text_transform(child);

    if (type == CSS_TEXT_TRANSFORM_INHERIT) {
        type = get_text_transform(parent);
    }

    return set_text_transform(result, type);
}


/*********************************************************************************
top
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_top(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_top);
}

css_error css__set_top_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_top(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_top(css_select_state* state)
{
    return set_top(state->computed, CSS_TOP_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_top(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_top(child, &length, &unit);

    if (type == CSS_TOP_INHERIT) {
        type = get_top(parent, &length, &unit);
    }

    return set_top(result, type, length, unit);
}


/*********************************************************************************
unicode_bidi
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_unicode_bidi(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_UNICODE_BIDI_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case UNICODE_BIDI_NORMAL:
            value = CSS_UNICODE_BIDI_NORMAL;
            break;
        case UNICODE_BIDI_EMBED:
            value = CSS_UNICODE_BIDI_EMBED;
            break;
        case UNICODE_BIDI_BIDI_OVERRIDE:
            value = CSS_UNICODE_BIDI_BIDI_OVERRIDE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_unicode_bidi(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_unicode_bidi_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_unicode_bidi(style, hint->status);
}

css_error css__initial_unicode_bidi(css_select_state* state)
{
    return set_unicode_bidi(state->computed, CSS_UNICODE_BIDI_NORMAL);
}

css_error css__compose_unicode_bidi(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_unicode_bidi(child);

    if (type == CSS_UNICODE_BIDI_INHERIT) {
        type = get_unicode_bidi(parent);
    }

    return set_unicode_bidi(result, type);
}


/*********************************************************************************
vertical_align
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_vertical_align(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_VERTICAL_ALIGN_INHERIT;
    css_fixed length = 0;
    uint32_t unit = UNIT_PX;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case VERTICAL_ALIGN_SET:
            value = CSS_VERTICAL_ALIGN_SET;

            length = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(length));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case VERTICAL_ALIGN_BASELINE:
            value = CSS_VERTICAL_ALIGN_BASELINE;
            break;
        case VERTICAL_ALIGN_SUB:
            value = CSS_VERTICAL_ALIGN_SUB;
            break;
        case VERTICAL_ALIGN_SUPER:
            value = CSS_VERTICAL_ALIGN_SUPER;
            break;
        case VERTICAL_ALIGN_TOP:
            value = CSS_VERTICAL_ALIGN_TOP;
            break;
        case VERTICAL_ALIGN_TEXT_TOP:
            value = CSS_VERTICAL_ALIGN_TEXT_TOP;
            break;
        case VERTICAL_ALIGN_MIDDLE:
            value = CSS_VERTICAL_ALIGN_MIDDLE;
            break;
        case VERTICAL_ALIGN_BOTTOM:
            value = CSS_VERTICAL_ALIGN_BOTTOM;
            break;
        case VERTICAL_ALIGN_TEXT_BOTTOM:
            value = CSS_VERTICAL_ALIGN_TEXT_BOTTOM;
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_vertical_align(state->computed, value, length, unit);
    }

    return CSS_OK;
}

css_error css__set_vertical_align_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_vertical_align(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_vertical_align(css_select_state* state)
{
    return set_vertical_align(state->computed, CSS_VERTICAL_ALIGN_BASELINE,
        0, CSS_UNIT_PX);
}

css_error css__compose_vertical_align(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_vertical_align(child, &length, &unit);

    if (type == CSS_VERTICAL_ALIGN_INHERIT) {
        type = get_vertical_align(parent, &length, &unit);
    }

    return set_vertical_align(result, type, length, unit);
}


/*********************************************************************************
visibility
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_visibility(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_VISIBILITY_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case VISIBILITY_VISIBLE:
            value = CSS_VISIBILITY_VISIBLE;
            break;
        case VISIBILITY_HIDDEN:
            value = CSS_VISIBILITY_HIDDEN;
            break;
        case VISIBILITY_COLLAPSE:
            value = CSS_VISIBILITY_COLLAPSE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_visibility(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_visibility_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_visibility(style, hint->status);
}

css_error css__initial_visibility(css_select_state* state)
{
    return set_visibility(state->computed, CSS_VISIBILITY_VISIBLE);
}

css_error css__compose_visibility(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_visibility(child);

    if (type == CSS_VISIBILITY_INHERIT) {
        type = get_visibility(parent);
    }

    return set_visibility(result, type);
}


/*********************************************************************************
voice_family
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_voice_family(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = 0;
    lwc_string** voices = NULL;
    uint32_t n_voices = 0;

    if (isInherit(opv) == false) {
        uint32_t v = getValue(opv);

        while (v != VOICE_FAMILY_END) {
            lwc_string* voice = NULL;
            lwc_string** temp;

            switch (v) {
            case VOICE_FAMILY_STRING:
            case VOICE_FAMILY_IDENT_LIST:
                css__stylesheet_string_get(style->sheet,
                    *((css_code_t*)style->bytecode),
                    &voice);
                advance_bytecode(style, sizeof(css_code_t));
                break;
            case VOICE_FAMILY_MALE:
                if (value == 0)
                    value = 1;
                break;
            case VOICE_FAMILY_FEMALE:
                if (value == 0)
                    value = 1;
                break;
            case VOICE_FAMILY_CHILD:
                if (value == 0)
                    value = 1;
                break;
            }

            /* Only use family-names which occur before the first
             * generic-family. Any values which occur after the
             * first generic-family are ignored. */
             /** \todo Do this at bytecode generation time? */
            if (value == 0 && voice != NULL) {
                temp = realloc(voices,
                    (n_voices + 1) * sizeof(lwc_string*));
                if (temp == NULL) {
                    if (voices != NULL) {
                        free(voices);
                    }
                    return CSS_NOMEM;
                }

                voices = temp;

                voices[n_voices] = voice;

                n_voices++;
            }

            v = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(v));
        }
    }

    /* Terminate array with blank entry, if needed */
    if (n_voices > 0) {
        lwc_string** temp;

        temp = realloc(voices, (n_voices + 1) * sizeof(lwc_string*));
        if (temp == NULL) {
            free(voices);
            return CSS_NOMEM;
        }

        voices = temp;

        voices[n_voices] = NULL;
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo voice-family */
        if (n_voices > 0)
            free(voices);
    }
    else {
        if (n_voices > 0)
            free(voices);
    }

    return CSS_OK;
}

css_error css__set_voice_family_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_voice_family(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_voice_family(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
volume
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_volume(uint32_t opv, css_style* style,
    css_select_state* state)
{
    css_fixed val = 0;
    uint32_t unit = UNIT_PCT;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case VOLUME_NUMBER:
            val = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(val));
            break;
        case VOLUME_DIMENSION:
            val = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(val));
            unit = *((uint32_t*)style->bytecode);
            advance_bytecode(style, sizeof(unit));
            break;
        case VOLUME_SILENT:
        case VOLUME_X_SOFT:
        case VOLUME_SOFT:
        case VOLUME_MEDIUM:
        case VOLUME_LOUD:
        case VOLUME_X_LOUD:
            /** \todo convert to public values */
            break;
        }
    }

    unit = css__to_css_unit(unit);

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        /** \todo volume */
    }

    return CSS_OK;
}

css_error css__set_volume_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    UNUSED(hint);
    UNUSED(style);

    return CSS_OK;
}

css_error css__initial_volume(css_select_state* state)
{
    UNUSED(state);

    return CSS_OK;
}

css_error css__compose_volume(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    UNUSED(parent);
    UNUSED(child);
    UNUSED(result);

    return CSS_OK;
}


/*********************************************************************************
white_space
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_white_space(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_WHITE_SPACE_INHERIT;

    UNUSED(style);

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case WHITE_SPACE_NORMAL:
            value = CSS_WHITE_SPACE_NORMAL;
            break;
        case WHITE_SPACE_PRE:
            value = CSS_WHITE_SPACE_PRE;
            break;
        case WHITE_SPACE_NOWRAP:
            value = CSS_WHITE_SPACE_NOWRAP;
            break;
        case WHITE_SPACE_PRE_WRAP:
            value = CSS_WHITE_SPACE_PRE_WRAP;
            break;
        case WHITE_SPACE_PRE_LINE:
            value = CSS_WHITE_SPACE_PRE_LINE;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_white_space(state->computed, value);
    }

    return CSS_OK;
}

css_error css__set_white_space_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_white_space(style, hint->status);
}

css_error css__initial_white_space(css_select_state* state)
{
    return set_white_space(state->computed, CSS_WHITE_SPACE_NORMAL);
}

css_error css__compose_white_space(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t type = get_white_space(child);

    if (type == CSS_WHITE_SPACE_INHERIT) {
        type = get_white_space(parent);
    }

    return set_white_space(result, type);
}


/*********************************************************************************
widows
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_widows(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_number(opv, style, state, set_widows);
}

css_error css__set_widows_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_widows(style, hint->status, hint->data.integer);
}

css_error css__initial_widows(css_select_state* state)
{
    return set_widows(state->computed, CSS_WIDOWS_SET, 2);
}

css_error css__compose_widows(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    int32_t count = 0;
    uint8_t type = get_widows(child, &count);

    if (type == CSS_WIDOWS_INHERIT) {
        type = get_widows(parent, &count);
    }

    return set_widows(result, type, count);
}


/*********************************************************************************
width
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_width(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_auto(opv, style, state, set_width);
}

css_error css__set_width_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_width(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_width(css_select_state* state)
{
    return set_width(state->computed, CSS_WIDTH_AUTO, 0, CSS_UNIT_PX);
}

css_error css__compose_width(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_width(child, &length, &unit);

    if (type == CSS_WIDTH_INHERIT) {
        type = get_width(parent, &length, &unit);
    }

    return set_width(result, type, length, unit);
}


/*********************************************************************************
word_spacing
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_word_spacing(uint32_t opv, css_style* style,
    css_select_state* state)
{
    return css__cascade_length_normal(opv, style, state, set_word_spacing);
}

css_error css__set_word_spacing_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_word_spacing(style, hint->status,
        hint->data.length.value, hint->data.length.unit);
}

css_error css__initial_word_spacing(css_select_state* state)
{
    return set_word_spacing(state->computed, CSS_WORD_SPACING_NORMAL,
        0, CSS_UNIT_PX);
}

css_error css__compose_word_spacing(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    css_fixed length = 0;
    css_unit unit = CSS_UNIT_PX;
    uint8_t type = get_word_spacing(child, &length, &unit);

    if (type == CSS_WORD_SPACING_INHERIT) {
        type = get_word_spacing(parent, &length, &unit);
    }

    return set_word_spacing(result, type, length, unit);
}

/*********************************************************************************
writing_mode
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_writing_mode(uint32_t opv, css_style* style,
    css_select_state* state)
{
    bool inherit = isInherit(opv);
    uint16_t writing_mode = CSS_WRITING_MODE_INHERIT;
    UNUSED(style);

    if (inherit == false) {
        switch (getValue(opv)) {
        case WRITING_MODE_HORIZONTAL_TB:
            writing_mode = CSS_WRITING_MODE_HORIZONTAL_TB;
            break;
        case WRITING_MODE_VERTICAL_RL:
            writing_mode = CSS_WRITING_MODE_VERTICAL_RL;
            break;
        case WRITING_MODE_VERTICAL_LR:
            writing_mode = CSS_WRITING_MODE_VERTICAL_LR;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        inherit)) {
        return set_writing_mode(state->computed, writing_mode);
    }

    return CSS_OK;
}

css_error css__set_writing_mode_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_writing_mode(style, hint->status);
}

css_error css__initial_writing_mode(css_select_state* state)
{
    return set_writing_mode(state->computed,
        CSS_WRITING_MODE_HORIZONTAL_TB);
}

css_error css__compose_writing_mode(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    uint8_t writing_mode = get_writing_mode(child);

    if (writing_mode == CSS_WRITING_MODE_INHERIT) {
        writing_mode = get_writing_mode(parent);
    }

    return set_writing_mode(result, writing_mode);
}


/*********************************************************************************
z_index
*
*********************************************************************************/
/*
 * This file is part of LibCSS
 * Licensed under the MIT License,
 *		  http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include "thirdparty/libcss/libcss/bytecode/bytecode.h"
#include "thirdparty/libcss/libcss/bytecode/opcodes.h"
#include "thirdparty/libcss/libcss/select/propset.h"
#include "thirdparty/libcss/libcss/select/propget.h"
#include "thirdparty/libcss/libcss/utils/utils.h"

#include "thirdparty/libcss/libcss/select/properties/properties.h"


css_error css__cascade_z_index(uint32_t opv, css_style* style,
    css_select_state* state)
{
    uint16_t value = CSS_Z_INDEX_INHERIT;
    css_fixed index = 0;

    if (isInherit(opv) == false) {
        switch (getValue(opv)) {
        case Z_INDEX_SET:
            value = CSS_Z_INDEX_SET;

            index = *((css_fixed*)style->bytecode);
            advance_bytecode(style, sizeof(index));
            break;
        case Z_INDEX_AUTO:
            value = CSS_Z_INDEX_AUTO;
            break;
        }
    }

    if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
        isInherit(opv))) {
        return set_z_index(state->computed, value, index);
    }

    return CSS_OK;
}

css_error css__set_z_index_from_hint(const css_hint* hint,
    css_computed_style* style)
{
    return set_z_index(style, hint->status, hint->data.integer);
}

css_error css__initial_z_index(css_select_state* state)
{
    return set_z_index(state->computed, CSS_Z_INDEX_AUTO, 0);
}

css_error css__compose_z_index(const css_computed_style* parent,
    const css_computed_style* child,
    css_computed_style* result)
{
    int32_t index = 0;
    uint8_t type = get_z_index(child, &index);

    if (type == CSS_Z_INDEX_INHERIT) {
        type = get_z_index(parent, &index);
    }

    return set_z_index(result, type, index);
}

