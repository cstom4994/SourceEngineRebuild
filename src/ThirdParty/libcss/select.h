// Copyright(c) 2019 - 2021, KaoruXun All rights reserved.

#ifndef __CSS_SELECT__
#define __CSS_SELECT__


#include "thirdparty/libcss/libwapcaplet/libwapcaplet.h"

#define UNUSED(value) (void)value
/*
*
#undef lwc_string_data
#define lwc_string_data(str) (const char*)((str) + 1)

#undef lwc_string_ref
inline lwc_string* lwc_string_ref(lwc_string* str) {
  lwc_string *__lwc_s = str;
  assert(__lwc_s != NULL);
  __lwc_s->refcnt++;
  return __lwc_s;
}


#undef lwc_string_caseless_isequal
inline lwc_error lwc_string_caseless_isequal(lwc_string* _str1, lwc_string* _str2, bool* _ret) {
    lwc_error __lwc_err = lwc_error_ok;
    lwc_string* __lwc_str1 = (_str1);
    lwc_string* __lwc_str2 = (_str2);
    bool* __lwc_ret = (_ret);
    if (__lwc_str1->insensitive == NULL) {
        __lwc_err = lwc__intern_caseless_string(__lwc_str1);
    }
    if (__lwc_err == lwc_error_ok && __lwc_str2->insensitive == NULL) {
        __lwc_err = lwc__intern_caseless_string(__lwc_str2);
    }
    if (__lwc_err == lwc_error_ok)
        *__lwc_ret = (__lwc_str1->insensitive == __lwc_str2->insensitive);
    return __lwc_err;
}

*/

namespace ImVue {
    css_error node_name(void* pw, void* node,
        css_qname* qname);
    css_error node_classes(void* pw, void* node,
        lwc_string*** classes, uint32_t* n_classes);
    css_error node_id(void* pw, void* node,
        lwc_string** id);
    css_error named_ancestor_node(void* pw, void* node,
        const css_qname* qname,
        void** ancestor);
    css_error named_parent_node(void* pw, void* node,
        const css_qname* qname,
        void** parent);
    css_error named_sibling_node(void* pw, void* node,
        const css_qname* qname,
        void** sibling);
    css_error named_generic_sibling_node(void* pw, void* node,
        const css_qname* qname,
        void** sibling);
    css_error parent_node(void* pw, void* node, void** parent);
    css_error sibling_node(void* pw, void* node, void** sibling);
    css_error node_has_name(void* pw, void* node,
        const css_qname* qname,
        bool* match);
    css_error node_has_class(void* pw, void* node,
        lwc_string* name,
        bool* match);
    css_error node_has_id(void* pw, void* node,
        lwc_string* name,
        bool* match);
    css_error node_has_attribute(void* pw, void* node,
        const css_qname* qname,
        bool* match);
    css_error node_has_attribute_equal(void* pw, void* node,
        const css_qname* qname,
        lwc_string* value,
        bool* match);
    css_error node_has_attribute_dashmatch(void* pw, void* node,
        const css_qname* qname,
        lwc_string* value,
        bool* match);
    css_error node_has_attribute_includes(void* pw, void* node,
        const css_qname* qname,
        lwc_string* value,
        bool* match);
    css_error node_has_attribute_prefix(void* pw, void* node,
        const css_qname* qname,
        lwc_string* value,
        bool* match);
    css_error node_has_attribute_suffix(void* pw, void* node,
        const css_qname* qname,
        lwc_string* value,
        bool* match);
    css_error node_has_attribute_substring(void* pw, void* node,
        const css_qname* qname,
        lwc_string* value,
        bool* match);
    css_error node_is_root(void* pw, void* node, bool* match);
    css_error node_count_siblings(void* pw, void* node,
        bool same_name, bool after, int32_t* count);
    css_error node_is_empty(void* pw, void* node, bool* match);
    css_error node_is_link(void* pw, void* node, bool* match);
    css_error node_is_visited(void* pw, void* node, bool* match);
    css_error node_is_hover(void* pw, void* node, bool* match);
    css_error node_is_active(void* pw, void* node, bool* match);
    css_error node_is_focus(void* pw, void* node, bool* match);
    css_error node_is_enabled(void* pw, void* node, bool* match);
    css_error node_is_disabled(void* pw, void* node, bool* match);
    css_error node_is_checked(void* pw, void* node, bool* match);
    css_error node_is_target(void* pw, void* node, bool* match);
    css_error node_is_lang(void* pw, void* node,
        lwc_string* lang, bool* match);
    css_error node_presentational_hint(void* pw, void* node,
        uint32_t* nhints, css_hint** hints);
    css_error ua_default_for_property(void* pw, uint32_t property,
        css_hint* hint);
    css_error compute_font_size(void* pw, const css_hint* parent,
        css_hint* size);
    css_error set_libcss_node_data(void* pw, void* n,
        void* libcss_node_data);
    css_error get_libcss_node_data(void* pw, void* n,
        void** libcss_node_data);

    css_error resolve_url(void* pw,
        const char* base, lwc_string* rel, lwc_string** abs);

    css_error resolve_font(void* pw,
        lwc_string* name, css_system_font* system_font);
}

#endif
