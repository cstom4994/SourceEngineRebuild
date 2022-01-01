﻿/*
 * This source file is part of RmlUi, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://github.com/mikke89/RmlUi
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 * Copyright (c) 2019 The RmlUi Team, and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef RMLUI_LUA_CONTEXT_H
#define RMLUI_LUA_CONTEXT_H

#include <RmlUi/Lua/LuaType.h>
#include <RmlUi/Lua/IncludeLua.h>
#include <RmlUi/Core/Context.h>


namespace Rml {
    namespace Lua {
        template<>
        void ExtraInit<Context>(lua_State *L, int metatable_index);

//methods
        int ContextAddEventListener(lua_State *L, Context *obj);

        int ContextCreateDocument(lua_State *L, Context *obj);

        int ContextLoadDocument(lua_State *L, Context *obj);

        int ContextRender(lua_State *L, Context *obj);

        int ContextUnloadAllDocuments(lua_State *L, Context *obj);

        int ContextUnloadDocument(lua_State *L, Context *obj);

        int ContextUpdate(lua_State *L, Context *obj);

//getters
        int ContextGetAttrdimensions(lua_State *L);

        int ContextGetAttrdocuments(lua_State *L);

        int ContextGetAttrfocus_element(lua_State *L);

        int ContextGetAttrhover_element(lua_State *L);

        int ContextGetAttrname(lua_State *L);

        int ContextGetAttrroot_element(lua_State *L);

//setters
        int ContextSetAttrdimensions(lua_State *L);


        extern RegType <Context> ContextMethods[];
        extern luaL_Reg ContextGetters[];
        extern luaL_Reg ContextSetters[];

        RMLUI_LUATYPE_DECLARE(Context)
    } // namespace Lua
} // namespace Rml
#endif
