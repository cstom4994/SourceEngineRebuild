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

#include "DecoratorTiledBoxInstancer.h"
#include "DecoratorTiledBox.h"

namespace Rml {

DecoratorTiledBoxInstancer::DecoratorTiledBoxInstancer() : DecoratorTiledInstancer(9)
{
	RegisterTileProperty("top-left-image");
	RegisterTileProperty("top-right-image");
	RegisterTileProperty("bottom-left-image");
	RegisterTileProperty("bottom-right-image");

	RegisterTileProperty("left-image");
	RegisterTileProperty("right-image");
	RegisterTileProperty("top-image");
	RegisterTileProperty("bottom-image");

	RegisterTileProperty("center-image");

	RegisterShorthand("decorator", "top-left-image, top-image, top-right-image, left-image, center-image, right-image, bottom-left-image, bottom-image, bottom-right-image", ShorthandType::RecursiveCommaSeparated);
}

DecoratorTiledBoxInstancer::~DecoratorTiledBoxInstancer()
{
}

// Instances a box decorator.
SharedPtr<Decorator>DecoratorTiledBoxInstancer::InstanceDecorator(const String& RMLUI_UNUSED_PARAMETER(name), const PropertyDictionary& properties, const DecoratorInstancerInterface& interface)
{
	RMLUI_UNUSED(name);

	constexpr size_t num_tiles = 9;

	DecoratorTiled::Tile tiles[num_tiles];
	Texture textures[num_tiles];

	if (!GetTileProperties(tiles, textures, num_tiles, properties, interface))
		return nullptr;

	auto decorator = MakeShared<DecoratorTiledBox>();
	if (!decorator->Initialise(tiles, textures))
		return nullptr;

	return decorator;
}

} // namespace Rml
