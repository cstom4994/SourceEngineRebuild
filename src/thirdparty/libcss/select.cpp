/*
Copyright (c) 2019 Artem Chernyshev

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

extern "C" {
#include "thirdparty/libcss/libcss/libcss.h"
}

#include "thirdparty/libcss/select.h"
#include "engine/cppcore/imgui/ImVue/ImVue.h"

// This module implements libcss selector interface

namespace ImVue {

    // special element iterator that takes in account PSEUDO_ELEMENT
    class ElementIterator {
    public:

        int index;

        ElementIterator(ContainerElement* target, int i = 0)
            : index(i)
        {
            setActiveElement(target);
        }

        Element* prev()
        {
            if (index > -1) {
                index--;
                onIndexChange();
            }

            return current();
        }

        Element* next()
        {
            if (index < (int)mChildren.size()) {
                index++;
                onIndexChange();
            }

            return current();
        }

        Element* current()
        {
            if (index >= 0 && index < (int)mChildren.size()) {
                return mChildren[index];
            }

            return NULL;
        }

    private:

        void onIndexChange()
        {
            Element* el = current();
            if (el) {
                if (el->isPseudoElement()) {
                    setActiveElement(static_cast<ContainerElement*>(el));
                    index = 0;
                }
            }
            else if (mElement->isPseudoElement() && mElement->getParent() && index != 0 && mElement->index > 0) {
                int direction = index / abs(index);
                index = (int)mElement->index + direction;
                setActiveElement(mElement->getParent());
            }
        }

        void setActiveElement(ContainerElement* element)
        {
            mElement = element;
            mChildren = element->getChildren();
        }

        Element* mElement;
        Element::Elements mChildren;
    };


    lwc_string* lwc_string_from_char(const char* s) {
        lwc_string* res = NULL;
        lwc_intern_string(s, strlen(s), &res);
        return res;
    }

    // resolve

    css_error resolve_url(void* pw,
        const char* base, lwc_string* rel, lwc_string** abs)
    {
        (void)pw;
        (void)base;

        /* About as useless as possible */
        *abs = rel; assert(abs != NULL); (*abs)->refcnt++;

        return CSS_OK;
    }

    css_error resolve_font(void* pw,
        lwc_string* name, css_system_font* system_font)
    {
        UNUSED(pw);
        UNUSED(name);
        UNUSED(system_font);
        return CSS_INVALID;
    }

    // select handlers

    css_error node_name(void* pw, void* n, css_qname* qname)
    {
        UNUSED(pw);

        const char* name = ((Element*)n)->getType();
        lwc_intern_string(name, strlen(name), &qname->name);

        return CSS_OK;
    }

    css_error node_classes(void* pw, void* n,
        lwc_string*** classes, uint32_t* n_classes)
    {
        UNUSED(pw);
        Element* element = (Element*)n;
        ImVector<lwc_string*>& classList = element->style()->getClasses();

        *classes = &classList.Data[0];
        *n_classes = classList.size();
        for (int i = 0; i < classList.size(); i++) {
            (*classes)[i] = lwc_string_ref(classList[i]);
        }

        return CSS_OK;
    }

    css_error node_id(void* pw, void* n, lwc_string** id)
    {
        UNUSED(pw);
        UNUSED(n);

        const char* elementID = ((Element*)n)->id;
        if (elementID == NULL) {
            *id = NULL;
            return CSS_OK;
        }
        lwc_intern_string(elementID, strlen(elementID), id);
        return CSS_OK;
    }


    css_error named_ancestor_node(void* pw, void* n,
        const css_qname* qname,
        void** ancestor)
    {
        UNUSED(pw);

        Element* element = ((Element*)n)->getParent();
        *ancestor = NULL;
        while (element) {
            if (ImStricmp(element->getType(), lwc_string_data(qname->name)) == 0) {
                *ancestor = element;
                break;
            }

            element = element->getParent();
        }
        return CSS_OK;
    }

    css_error named_parent_node(void* pw, void* n,
        const css_qname* qname,
        void** parent)
    {
        UNUSED(pw);
        Element* parentElement = ((Element*)n)->getParent();
        if (parentElement && ImStricmp(parentElement->getType(), lwc_string_data(qname->name)) == 0) {
            *parent = parentElement;
        }
        else {
            *parent = NULL;
        }

        return CSS_OK;
    }

    css_error named_generic_sibling_node(void* pw, void* n,
        const css_qname* qname,
        void** sibling)
    {
        UNUSED(pw);
        *sibling = NULL;
        Element* element = (Element*)n;
        ContainerElement* parent = element->getParent();
        if (!parent || !element->enabled) {
            return CSS_OK;
        }

        ElementIterator iter(parent, element->index);
        for (iter.prev(); iter.current(); iter.prev()) {
            Element* previous = iter.current();
            if (!previous->visible()) {
                continue;
            }

            bool match = false;
            lwc_error status = lwc_string_caseless_isequal(
                qname->name, lwc_string_from_char(previous->getType()), &match);
            UNUSED(status);
            IM_ASSERT(status == lwc_error_ok);
            if (match == true) {
                *sibling = (void*)previous;
                break;
            }
        }
        return CSS_OK;
    }

    css_error named_sibling_node(void* pw, void* n,
        const css_qname* qname,
        void** sibling)
    {
        UNUSED(pw);
        Element* element = (Element*)n;

        *sibling = NULL;
        ContainerElement* parent = element->getParent();
        if (!parent || !element->enabled) {
            return CSS_OK;
        }

        ElementIterator iter(parent, element->index);
        Element* previous = iter.prev();
        if (previous) {
            if (!previous->visible()) {
                return CSS_OK;
            }
            bool match = false;

            lwc_error status = lwc_string_caseless_isequal(
                qname->name, lwc_string_from_char(previous->getType()), &match);
            UNUSED(status);
            IM_ASSERT(status == lwc_error_ok);
            if (match == true)
                *sibling = (void*)previous;
        }

        return CSS_OK;
    }

    css_error parent_node(void* pw, void* n, void** parent)
    {
        UNUSED(pw);
        Element* p = ((Element*)n)->getParent();
        if (p && p->isPseudoElement()) {
            p = p->getParent();
        }

        *parent = p;
        return CSS_OK;
    }

    css_error sibling_node(void* pw, void* n, void** sibling)
    {
        UNUSED(pw);
        Element* element = (Element*)n;
        *sibling = NULL;
        if (element->index == 0) {
            return CSS_OK;
        }

        ContainerElement* parent = element->getParent();
        if (!parent || !element->enabled) {
            return CSS_OK;
        }

        *sibling = ElementIterator(parent, element->index).prev();
        return CSS_OK;
    }

    css_error node_has_name(void* pw, void* n,
        const css_qname* qname,
        bool* match)
    {
        lwc_string* node = lwc_string_from_char(((Element*)n)->getType());

        UNUSED(pw);
        lwc_error status = lwc_string_caseless_isequal(node, qname->name, match);
        UNUSED(status);
        IM_ASSERT(status ==
            lwc_error_ok);
        return CSS_OK;
    }

    css_error node_has_class(void* pw, void* n,
        lwc_string* name,
        bool* match)
    {
        UNUSED(pw);
        *match = ((Element*)n)->hasClass(lwc_string_data(name));
        return CSS_OK;
    }

    css_error node_has_id(void* pw, void* n,
        lwc_string* name,
        bool* match)
    {
        UNUSED(pw);
        *match = ImStricmp(((Element*)n)->id, lwc_string_data(name)) == 0;
        return CSS_OK;
    }

    css_error node_has_attribute(void* pw, void* n,
        const css_qname* qname,
        bool* match)
    {
        UNUSED(pw);
        *match = ((Element*)n)->hasAttribute(lwc_string_data(qname->name));
        return CSS_OK;
    }

    css_error node_has_attribute_equal(void* pw, void* n,
        const css_qname* qname,
        lwc_string* expected,
        bool* match)
    {
        UNUSED(pw);
        char* actual = NULL;
        if (((Element*)n)->evalAttribute(lwc_string_data(qname->name), &actual) && actual) {
            *match = ImStricmp(lwc_string_data(expected), actual) == 0;
        }
        else {
            *match = false;
        }
        ImGui::MemFree(actual);
        return CSS_OK;
    }

    css_error node_has_attribute_dashmatch(void* pw, void* n,
        const css_qname* qname,
        lwc_string* value,
        bool* match)
    {
        UNUSED(pw);
        UNUSED(n);
        UNUSED(qname);
        UNUSED(value);
        *match = false;
        return CSS_OK;
    }

    css_error node_has_attribute_includes(void* pw, void* n,
        const css_qname* qname,
        lwc_string* value,
        bool* match)
    {
        UNUSED(pw);
        UNUSED(n);
        UNUSED(qname);
        UNUSED(value);
        *match = false;
        return CSS_OK;
    }

    css_error node_has_attribute_prefix(void* pw, void* n,
        const css_qname* qname,
        lwc_string* value,
        bool* match)
    {
        UNUSED(pw);
        UNUSED(n);
        UNUSED(qname);
        UNUSED(value);
        *match = false;
        return CSS_OK;
    }

    css_error node_has_attribute_suffix(void* pw, void* n,
        const css_qname* qname,
        lwc_string* value,
        bool* match)
    {
        UNUSED(pw);
        UNUSED(n);
        UNUSED(qname);
        UNUSED(value);
        *match = false;
        return CSS_OK;
    }

    css_error node_has_attribute_substring(void* pw, void* n,
        const css_qname* qname,
        lwc_string* value,
        bool* match)
    {
        UNUSED(pw);
        UNUSED(n);
        UNUSED(qname);
        UNUSED(value);
        *match = false;
        return CSS_OK;
    }

    css_error node_is_first_child(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        Element* element = (Element*)n;
        ContainerElement* parent = element->getParent();
        *match = element->enabled && (!parent || ElementIterator(parent, element->index).prev() == NULL);
        return CSS_OK;
    }

    css_error node_is_root(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        Element* parent = ((Element*)n)->getParent();
        *match = parent == NULL || ImStricmp(parent->getType(), "template") == 0;
        return CSS_OK;
    }

    css_error node_count_siblings(void* pw, void* n,
        bool same_name, bool after, int32_t* count)
    {
        UNUSED(pw);
        int cnt = 0;
        *count = 0;
        Element* element = (Element*)n;
        ContainerElement* parent = element->getParent();
        if (!parent || !element->enabled) {
            return CSS_OK;
        }

        ElementIterator iter(parent, element->index);
        const char* name = element->getType();

        while (true) {
            Element* el = NULL;
            if (after) {
                el = iter.next();
            }
            else {
                el = iter.prev();
            }

            if (!el) {
                break;
            }

            if (!el->visible()) {
                continue;
            }

            if (!same_name || ImStricmp(name, el->getType()) == 0)
                cnt++;
        }

        *count = cnt;
        return CSS_OK;
    }

    css_error node_is_empty(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        Element* element = (Element*)n;
        if (!element->isContainer()) {
            *match = false;
        }
        else {
            *match = ElementIterator(static_cast<ContainerElement*>(element), 0).current() == 0;
        }
        return CSS_OK;
    }

    css_error node_is_link(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        *match = ((Element*)n)->hasState(Element::LINK);
        return CSS_OK;
    }

    css_error node_is_visited(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        *match = ((Element*)n)->hasState(Element::VISITED);
        return CSS_OK;
    }

    css_error node_is_hover(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        *match = ((Element*)n)->hasState(Element::HOVERED);
        return CSS_OK;
    }

    css_error node_is_active(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        *match = ((Element*)n)->hasState(Element::ACTIVE);
        return CSS_OK;
    }

    css_error node_is_focus(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        *match = ((Element*)n)->hasState(Element::FOCUSED);
        return CSS_OK;
    }

    css_error node_is_enabled(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        UNUSED(n);
        Element* element = (Element*)n;
        *match = !element->hasState(Element::DISABLED) && element->enabled;
        return CSS_OK;
    }

    css_error node_is_disabled(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        UNUSED(n);
        *match = ((Element*)n)->hasState(Element::DISABLED);
        return CSS_OK;
    }

    css_error node_is_checked(void* pw, void* n, bool* match)
    {
        UNUSED(pw);
        UNUSED(n);
        *match = ((Element*)n)->hasState(Element::CHECKED);
        return CSS_OK;
    }

    css_error node_is_target(void* pw, void* n, bool* match)
    {
        // this makes no sense in our usecase
        UNUSED(pw);
        UNUSED(n);
        *match = false;
        return CSS_OK;
    }

    css_error node_is_lang(void* pw, void* n,
        lwc_string* lang,
        bool* match)
    {
        UNUSED(pw);
        char* value = NULL;
        if (((Element*)n)->evalAttribute("lang", &value) && value) {
            *match = strcmp(value, lwc_string_data(lang)) == 0;
        }
        else {
            *match = false;
        }
        return CSS_OK;
    }

    css_error node_presentational_hint(void* pw, void* node,
        uint32_t* nhints, css_hint** hints)
    {
        UNUSED(pw);
        UNUSED(node);
        *nhints = 0;
        *hints = NULL;
        return CSS_OK;
    }

    css_error ua_default_for_property(void* pw, uint32_t property, css_hint* hint)
    {
        UNUSED(pw);

        if (property == CSS_PROP_COLOR) {
            hint->data.color = 0x00000000;
            hint->status = CSS_COLOR_INHERIT;
        }
        else if (property == CSS_PROP_FONT_FAMILY) {
            hint->data.strings = NULL;
            hint->status = CSS_FONT_FAMILY_INHERIT;
        }
        else if (property == CSS_PROP_QUOTES) {
            // Not exactly useful
            hint->data.strings = NULL;
            hint->status = CSS_QUOTES_NONE;
        }
        else if (property == CSS_PROP_VOICE_FAMILY) {
            hint->data.strings = NULL;
            hint->status = 0;
        }
        else {
            return CSS_INVALID;
        }

        return CSS_OK;
    }

    css_error compute_font_size(void* pw, const css_hint* parent, css_hint* size)
    {
        static css_hint_length sizes[] = {
          { FLTTOFIX(6.75), CSS_UNIT_PX },
          { FLTTOFIX(7.50), CSS_UNIT_PX },
          { FLTTOFIX(9.75), CSS_UNIT_PX },
          { FLTTOFIX(12.0), CSS_UNIT_PX },
          { FLTTOFIX(15.0), CSS_UNIT_PX },
          { FLTTOFIX(18.0), CSS_UNIT_PX },
          { FLTTOFIX(24.0), CSS_UNIT_PX }
        };

        if (size->status == CSS_FONT_SIZE_DIMENSION)
        {
            return CSS_OK;
        }

        ImFont* font = ImGui::GetFont();
        if (!font) {
            font = ImGui::GetDefaultFont();
        }

        const css_hint_length* parent_size;
        if (!parent) {
            size->status = CSS_FONT_SIZE_DIMENSION;
            size->data.length = { FLTTOFIX(font->FontSize), CSS_UNIT_PX };
            return CSS_OK;
        }

        css_hint_length font_size = { FLTTOFIX(font ? font->FontSize : 0), CSS_UNIT_PX };

        UNUSED(pw);

        // Grab parent size, defaulting to medium if none 
        if (parent == NULL) {
            parent_size = &sizes[CSS_FONT_SIZE_MEDIUM + 1];
        }
        else {
            assert(parent->data.length.unit != CSS_UNIT_EM);
            assert(parent->data.length.unit != CSS_UNIT_EX);

            if (parent->status == CSS_FONT_SIZE_INHERIT) {
                parent_size = &font_size;
            }

            parent_size = &parent->data.length;
        }

        assert(size->status != CSS_FONT_SIZE_INHERIT);

        if (size->status < CSS_FONT_SIZE_LARGER) {
            // Keyword -- simple
            size->data.length = sizes[size->status - 1];
        }
        else if (size->status == CSS_FONT_SIZE_LARGER) {
            // \todo Step within table, if appropriate
            size->data.length.value =
                FMUL(parent_size->value, FLTTOFIX(1.2));
            size->data.length.unit = parent_size->unit;
        }
        else if (size->status == CSS_FONT_SIZE_SMALLER) {
            // \todo Step within table, if appropriate
            size->data.length.value =
                FMUL(parent_size->value, FLTTOFIX(1.2));
            size->data.length.unit = parent_size->unit;
        }
        else if (size->data.length.unit == CSS_UNIT_EM ||
            size->data.length.unit == CSS_UNIT_EX) {
            size->data.length.value =
                FMUL(size->data.length.value, parent_size->value);

            if (size->data.length.unit == CSS_UNIT_EX) {
                size->data.length.value = FMUL(size->data.length.value,
                    FLTTOFIX(0.6));
            }

            size->data.length.unit = parent_size->unit;
        }
        else if (size->data.length.unit == CSS_UNIT_PCT) {
            size->data.length.value = FDIV(FMUL(size->data.length.value,
                parent_size->value), FLTTOFIX(100));
            size->data.length.unit = parent_size->unit;
        }

        size->status = CSS_FONT_SIZE_DIMENSION;

        return CSS_OK;
    }

    css_error set_libcss_node_data(void* pw, void* n,
        void* libcss_node_data)
    {
        UNUSED(pw);

        Element* element = (Element*)n;
        if (element->style()->libcssData) {
            css_libcss_node_data_handler((css_select_handler*)pw, CSS_NODE_DELETED,
                NULL, element, NULL, element->style()->libcssData);
            element->style()->libcssData = 0;
        }

        element->style()->libcssData = libcss_node_data;

        return CSS_OK;
    }

    css_error get_libcss_node_data(void* pw, void* n,
        void** libcss_node_data)
    {
        UNUSED(pw);

        *libcss_node_data = ((Element*)n)->style()->libcssData;

        return CSS_OK;
    }
}
