


set(PROJECT_NAME RmlCore)

################################################################################
# Source groups
################################################################################

set(Header_Files
        "Include/RmlUi/Config/Config.h"
        "Include/RmlUi/Core.h"
        "Include/RmlUi/Core/Animation.h"
        "Include/RmlUi/Core/BaseXMLParser.h"
        "Include/RmlUi/Core/Box.h"
        "Include/RmlUi/Core/Colour.h"
        "Include/RmlUi/Core/Colour.inl"
        "Include/RmlUi/Core/ComputedValues.h"
        "Include/RmlUi/Core/Containers/chobo/flat_map.hpp"
        "Include/RmlUi/Core/Containers/chobo/flat_set.hpp"
        "Include/RmlUi/Core/Containers/robin_hood.h"
        "Include/RmlUi/Core/Context.h"
        "Include/RmlUi/Core/ContextInstancer.h"
        "Include/RmlUi/Core/ConvolutionFilter.h"
        "Include/RmlUi/Core/Core.h"
        "Include/RmlUi/Core/DataController.h"
        "Include/RmlUi/Core/DataModel.h"
        "Include/RmlUi/Core/DataTypeRegister.h"
        "Include/RmlUi/Core/DataTypes.h"
        "Include/RmlUi/Core/DataVariable.h"
        "Include/RmlUi/Core/DataView.h"
        "Include/RmlUi/Core/Debug.h"
        "Include/RmlUi/Core/Decorator.h"
        "Include/RmlUi/Core/DecoratorInstancer.h"
        "Include/RmlUi/Core/Dictionary.h"
        "Include/RmlUi/Core/Element.h"
        "Include/RmlUi/Core/Element.inl"
        "Include/RmlUi/Core/ElementDocument.h"
        "Include/RmlUi/Core/ElementInstancer.h"
        "Include/RmlUi/Core/Elements/DataFormatter.h"
        "Include/RmlUi/Core/Elements/DataQuery.h"
        "Include/RmlUi/Core/Elements/DataSource.h"
        "Include/RmlUi/Core/Elements/DataSourceListener.h"
        "Include/RmlUi/Core/Elements/ElementDataGrid.h"
        "Include/RmlUi/Core/Elements/ElementDataGridCell.h"
        "Include/RmlUi/Core/Elements/ElementDataGridExpandButton.h"
        "Include/RmlUi/Core/Elements/ElementDataGridRow.h"
        "Include/RmlUi/Core/Elements/ElementForm.h"
        "Include/RmlUi/Core/Elements/ElementFormControl.h"
        "Include/RmlUi/Core/Elements/ElementFormControlDataSelect.h"
        "Include/RmlUi/Core/Elements/ElementFormControlInput.h"
        "Include/RmlUi/Core/Elements/ElementFormControlSelect.h"
        "Include/RmlUi/Core/Elements/ElementFormControlTextArea.h"
        "Include/RmlUi/Core/Elements/ElementProgressBar.h"
        "Include/RmlUi/Core/Elements/ElementTabSet.h"
        "Include/RmlUi/Core/Elements/SelectOption.h"
        "Include/RmlUi/Core/ElementScroll.h"
        "Include/RmlUi/Core/ElementText.h"
        "Include/RmlUi/Core/ElementUtilities.h"
        "Include/RmlUi/Core/Event.h"
        "Include/RmlUi/Core/EventInstancer.h"
        "Include/RmlUi/Core/EventListener.h"
        "Include/RmlUi/Core/EventListenerInstancer.h"
        "Include/RmlUi/Core/Factory.h"
        "Include/RmlUi/Core/FileInterface.h"
        "Include/RmlUi/Core/FontEffect.h"
        "Include/RmlUi/Core/FontEffectInstancer.h"
        "Include/RmlUi/Core/FontEngineInterface.h"
        "Include/RmlUi/Core/FontGlyph.h"
        "Include/RmlUi/Core/Geometry.h"
        "Include/RmlUi/Core/GeometryUtilities.h"
        "Include/RmlUi/Core/Header.h"
        "Include/RmlUi/Core/ID.h"
        "Include/RmlUi/Core/Input.h"
        "Include/RmlUi/Core/Log.h"
        "Include/RmlUi/Core/Math.h"
        "Include/RmlUi/Core/MathTypes.h"
        "Include/RmlUi/Core/Matrix4.h"
        "Include/RmlUi/Core/Matrix4.inl"
        "Include/RmlUi/Core/ObserverPtr.h"
        "Include/RmlUi/Core/Platform.h"
        "Include/RmlUi/Core/Plugin.h"
        "Include/RmlUi/Core/Profiling.h"
        "Include/RmlUi/Core/PropertiesIteratorView.h"
        "Include/RmlUi/Core/Property.h"
        "Include/RmlUi/Core/PropertyDefinition.h"
        "Include/RmlUi/Core/PropertyDictionary.h"
        "Include/RmlUi/Core/PropertyIdSet.h"
        "Include/RmlUi/Core/PropertyParser.h"
        "Include/RmlUi/Core/PropertySpecification.h"
        "Include/RmlUi/Core/RenderInterface.h"
        "Include/RmlUi/Core/ScriptInterface.h"
        "Include/RmlUi/Core/Spritesheet.h"
        "Include/RmlUi/Core/Stream.h"
        "Include/RmlUi/Core/StreamMemory.h"
        "Include/RmlUi/Core/StringUtilities.h"
        "Include/RmlUi/Core/StyleSheet.h"
        "Include/RmlUi/Core/StyleSheetSpecification.h"
        "Include/RmlUi/Core/SystemInterface.h"
        "Include/RmlUi/Core/Texture.h"
        "Include/RmlUi/Core/Traits.h"
        "Include/RmlUi/Core/Transform.h"
        "Include/RmlUi/Core/TransformPrimitive.h"
        "Include/RmlUi/Core/Tween.h"
        "Include/RmlUi/Core/TypeConverter.h"
        "Include/RmlUi/Core/TypeConverter.inl"
        "Include/RmlUi/Core/Types.h"
        "Include/RmlUi/Core/URL.h"
        "Include/RmlUi/Core/Variant.h"
        "Include/RmlUi/Core/Variant.inl"
        "Include/RmlUi/Core/Vector2.h"
        "Include/RmlUi/Core/Vector2.inl"
        "Include/RmlUi/Core/Vector3.h"
        "Include/RmlUi/Core/Vector3.inl"
        "Include/RmlUi/Core/Vector4.h"
        "Include/RmlUi/Core/Vector4.inl"
        "Include/RmlUi/Core/Vertex.h"
        "Include/RmlUi/Core/XMLNodeHandler.h"
        "Include/RmlUi/Core/XMLParser.h"
        "Source/Core/Clock.h"
        "Source/Core/ComputeProperty.h"
        "Source/Core/ContextInstancerDefault.h"
        "Source/Core/DataControllerDefault.h"
        "Source/Core/DataExpression.h"
        "Source/Core/DataViewDefault.h"
        "Source/Core/DecoratorGradient.h"
        "Source/Core/DecoratorNinePatch.h"
        "Source/Core/DecoratorTiled.h"
        "Source/Core/DecoratorTiledBox.h"
        "Source/Core/DecoratorTiledBoxInstancer.h"
        "Source/Core/DecoratorTiledHorizontal.h"
        "Source/Core/DecoratorTiledHorizontalInstancer.h"
        "Source/Core/DecoratorTiledImage.h"
        "Source/Core/DecoratorTiledImageInstancer.h"
        "Source/Core/DecoratorTiledInstancer.h"
        "Source/Core/DecoratorTiledVertical.h"
        "Source/Core/DecoratorTiledVerticalInstancer.h"
        "Source/Core/DocumentHeader.h"
        "Source/Core/ElementAnimation.h"
        "Source/Core/ElementBackground.h"
        "Source/Core/ElementBorder.h"
        "Source/Core/ElementDecoration.h"
        "Source/Core/ElementDefinition.h"
        "Source/Core/ElementHandle.h"
        "Source/Core/Elements/ElementImage.h"
        "Source/Core/Elements/ElementTextSelection.h"
        "Source/Core/Elements/InputType.h"
        "Source/Core/Elements/InputTypeButton.h"
        "Source/Core/Elements/InputTypeCheckbox.h"
        "Source/Core/Elements/InputTypeRadio.h"
        "Source/Core/Elements/InputTypeRange.h"
        "Source/Core/Elements/InputTypeSubmit.h"
        "Source/Core/Elements/InputTypeText.h"
        "Source/Core/Elements/WidgetDropDown.h"
        "Source/Core/Elements/WidgetSlider.h"
        "Source/Core/Elements/WidgetTextInput.h"
        "Source/Core/Elements/WidgetTextInputMultiLine.h"
        "Source/Core/Elements/WidgetTextInputSingleLine.h"
        "Source/Core/Elements/WidgetTextInputSingleLinePassword.h"
        "Source/Core/Elements/XMLNodeHandlerDataGrid.h"
        "Source/Core/Elements/XMLNodeHandlerTabSet.h"
        "Source/Core/Elements/XMLNodeHandlerTextArea.h"
        "Source/Core/ElementStyle.h"
        "Source/Core/ElementTextDefault.h"
        "Source/Core/EventDispatcher.h"
        "Source/Core/EventInstancerDefault.h"
        "Source/Core/EventIterators.h"
        "Source/Core/EventSpecification.h"
        "Source/Core/FileInterfaceDefault.h"
        "Source/Core/FontEffectBlur.h"
        "Source/Core/FontEffectGlow.h"
        "Source/Core/FontEffectOutline.h"
        "Source/Core/FontEffectShadow.h"
        "Source/Core/FontEngineDefault/FontEngineInterfaceDefault.h"
        "Source/Core/FontEngineDefault/FontFace.h"
        "Source/Core/FontEngineDefault/FontFaceHandleDefault.h"
        "Source/Core/FontEngineDefault/FontFaceLayer.h"
        "Source/Core/FontEngineDefault/FontFamily.h"
        "Source/Core/FontEngineDefault/FontProvider.h"
        "Source/Core/FontEngineDefault/FontTypes.h"
        "Source/Core/FontEngineDefault/FreeTypeInterface.h"
        "Source/Core/GeometryDatabase.h"
        "Source/Core/IdNameMap.h"
        "Source/Core/LayoutBlockBox.h"
        "Source/Core/LayoutBlockBoxSpace.h"
        "Source/Core/LayoutEngine.h"
        "Source/Core/LayoutInlineBox.h"
        "Source/Core/LayoutInlineBoxText.h"
        "Source/Core/LayoutLineBox.h"
        "Source/Core/Memory.h"
        "Source/Core/PluginRegistry.h"
        "Source/Core/Pool.h"
        "Source/Core/precompiled.h"
        "Source/Core/PropertiesIterator.h"
        "Source/Core/PropertyParserAnimation.h"
        "Source/Core/PropertyParserColour.h"
        "Source/Core/PropertyParserKeyword.h"
        "Source/Core/PropertyParserNumber.h"
        "Source/Core/PropertyParserString.h"
        "Source/Core/PropertyParserTransform.h"
        "Source/Core/PropertyShorthandDefinition.h"
        "Source/Core/StreamFile.h"
        "Source/Core/StyleSheetFactory.h"
        "Source/Core/StyleSheetNode.h"
        "Source/Core/StyleSheetNodeSelector.h"
        "Source/Core/StyleSheetNodeSelectorEmpty.h"
        "Source/Core/StyleSheetNodeSelectorFirstChild.h"
        "Source/Core/StyleSheetNodeSelectorFirstOfType.h"
        "Source/Core/StyleSheetNodeSelectorLastChild.h"
        "Source/Core/StyleSheetNodeSelectorLastOfType.h"
        "Source/Core/StyleSheetNodeSelectorNthChild.h"
        "Source/Core/StyleSheetNodeSelectorNthLastChild.h"
        "Source/Core/StyleSheetNodeSelectorNthLastOfType.h"
        "Source/Core/StyleSheetNodeSelectorNthOfType.h"
        "Source/Core/StyleSheetNodeSelectorOnlyChild.h"
        "Source/Core/StyleSheetNodeSelectorOnlyOfType.h"
        "Source/Core/StyleSheetParser.h"
        "Source/Core/Template.h"
        "Source/Core/TemplateCache.h"
        "Source/Core/TextureDatabase.h"
        "Source/Core/TextureLayout.h"
        "Source/Core/TextureLayoutRectangle.h"
        "Source/Core/TextureLayoutRow.h"
        "Source/Core/TextureLayoutTexture.h"
        "Source/Core/TextureResource.h"
        "Source/Core/TransformState.h"
        "Source/Core/TransformUtilities.h"
        "Source/Core/Utilities.h"
        "Source/Core/WidgetScroll.h"
        "Source/Core/XMLNodeHandlerBody.h"
        "Source/Core/XMLNodeHandlerDefault.h"
        "Source/Core/XMLNodeHandlerHead.h"
        "Source/Core/XMLNodeHandlerTemplate.h"
        "Source/Core/XMLParseTools.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "../../public/tier0/memoverride.cpp"
        "Source/Core/BaseXMLParser.cpp"
        "Source/Core/Box.cpp"
        "Source/Core/Clock.cpp"
        "Source/Core/ComputeProperty.cpp"
        "Source/Core/Context.cpp"
        "Source/Core/ContextInstancer.cpp"
        "Source/Core/ContextInstancerDefault.cpp"
        "Source/Core/ConvolutionFilter.cpp"
        "Source/Core/Core.cpp"
        "Source/Core/DataController.cpp"
        "Source/Core/DataControllerDefault.cpp"
        "Source/Core/DataExpression.cpp"
        "Source/Core/DataModel.cpp"
        "Source/Core/DataTypeRegister.cpp"
        "Source/Core/DataVariable.cpp"
        "Source/Core/DataView.cpp"
        "Source/Core/DataViewDefault.cpp"
        "Source/Core/Decorator.cpp"
        "Source/Core/DecoratorGradient.cpp"
        "Source/Core/DecoratorInstancer.cpp"
        "Source/Core/DecoratorNinePatch.cpp"
        "Source/Core/DecoratorTiled.cpp"
        "Source/Core/DecoratorTiledBox.cpp"
        "Source/Core/DecoratorTiledBoxInstancer.cpp"
        "Source/Core/DecoratorTiledHorizontal.cpp"
        "Source/Core/DecoratorTiledHorizontalInstancer.cpp"
        "Source/Core/DecoratorTiledImage.cpp"
        "Source/Core/DecoratorTiledImageInstancer.cpp"
        "Source/Core/DecoratorTiledInstancer.cpp"
        "Source/Core/DecoratorTiledVertical.cpp"
        "Source/Core/DecoratorTiledVerticalInstancer.cpp"
        "Source/Core/DocumentHeader.cpp"
        "Source/Core/Element.cpp"
        "Source/Core/ElementAnimation.cpp"
        "Source/Core/ElementBackground.cpp"
        "Source/Core/ElementBorder.cpp"
        "Source/Core/ElementDecoration.cpp"
        "Source/Core/ElementDefinition.cpp"
        "Source/Core/ElementDocument.cpp"
        "Source/Core/ElementHandle.cpp"
        "Source/Core/ElementInstancer.cpp"
        "Source/Core/Elements/DataFormatter.cpp"
        "Source/Core/Elements/DataQuery.cpp"
        "Source/Core/Elements/DataSource.cpp"
        "Source/Core/Elements/DataSourceListener.cpp"
        "Source/Core/Elements/ElementDataGrid.cpp"
        "Source/Core/Elements/ElementDataGridCell.cpp"
        "Source/Core/Elements/ElementDataGridExpandButton.cpp"
        "Source/Core/Elements/ElementDataGridRow.cpp"
        "Source/Core/Elements/ElementForm.cpp"
        "Source/Core/Elements/ElementFormControl.cpp"
        "Source/Core/Elements/ElementFormControlDataSelect.cpp"
        "Source/Core/Elements/ElementFormControlInput.cpp"
        "Source/Core/Elements/ElementFormControlSelect.cpp"
        "Source/Core/Elements/ElementFormControlTextArea.cpp"
        "Source/Core/Elements/ElementImage.cpp"
        "Source/Core/Elements/ElementProgressBar.cpp"
        "Source/Core/Elements/ElementTabSet.cpp"
        "Source/Core/Elements/ElementTextSelection.cpp"
        "Source/Core/Elements/InputType.cpp"
        "Source/Core/Elements/InputTypeButton.cpp"
        "Source/Core/Elements/InputTypeCheckbox.cpp"
        "Source/Core/Elements/InputTypeRadio.cpp"
        "Source/Core/Elements/InputTypeRange.cpp"
        "Source/Core/Elements/InputTypeSubmit.cpp"
        "Source/Core/Elements/InputTypeText.cpp"
        "Source/Core/Elements/SelectOption.cpp"
        "Source/Core/Elements/WidgetDropDown.cpp"
        "Source/Core/Elements/WidgetSlider.cpp"
        "Source/Core/Elements/WidgetTextInput.cpp"
        "Source/Core/Elements/WidgetTextInputMultiLine.cpp"
        "Source/Core/Elements/WidgetTextInputSingleLine.cpp"
        "Source/Core/Elements/WidgetTextInputSingleLinePassword.cpp"
        "Source/Core/Elements/XMLNodeHandlerDataGrid.cpp"
        "Source/Core/Elements/XMLNodeHandlerTabSet.cpp"
        "Source/Core/Elements/XMLNodeHandlerTextArea.cpp"
        "Source/Core/ElementScroll.cpp"
        "Source/Core/ElementStyle.cpp"
        "Source/Core/ElementText.cpp"
        "Source/Core/ElementTextDefault.cpp"
        "Source/Core/ElementUtilities.cpp"
        "Source/Core/Event.cpp"
        "Source/Core/EventDispatcher.cpp"
        "Source/Core/EventInstancer.cpp"
        "Source/Core/EventInstancerDefault.cpp"
        "Source/Core/EventListenerInstancer.cpp"
        "Source/Core/EventSpecification.cpp"
        "Source/Core/Factory.cpp"
        "Source/Core/FileInterface.cpp"
        "Source/Core/FileInterfaceDefault.cpp"
        "Source/Core/FontEffect.cpp"
        "Source/Core/FontEffectBlur.cpp"
        "Source/Core/FontEffectGlow.cpp"
        "Source/Core/FontEffectInstancer.cpp"
        "Source/Core/FontEffectOutline.cpp"
        "Source/Core/FontEffectShadow.cpp"
        "Source/Core/FontEngineDefault/FontEngineInterfaceDefault.cpp"
        "Source/Core/FontEngineDefault/FontFace.cpp"
        "Source/Core/FontEngineDefault/FontFaceHandleDefault.cpp"
        "Source/Core/FontEngineDefault/FontFaceLayer.cpp"
        "Source/Core/FontEngineDefault/FontFamily.cpp"
        "Source/Core/FontEngineDefault/FontProvider.cpp"
        "Source/Core/FontEngineDefault/FreeTypeInterface.cpp"
        "Source/Core/FontEngineInterface.cpp"
        "Source/Core/Geometry.cpp"
        "Source/Core/GeometryDatabase.cpp"
        "Source/Core/GeometryUtilities.cpp"
        "Source/Core/LayoutBlockBox.cpp"
        "Source/Core/LayoutBlockBoxSpace.cpp"
        "Source/Core/LayoutEngine.cpp"
        "Source/Core/LayoutInlineBox.cpp"
        "Source/Core/LayoutInlineBoxText.cpp"
        "Source/Core/LayoutLineBox.cpp"
        "Source/Core/Log.cpp"
        "Source/Core/Math.cpp"
        "Source/Core/Memory.cpp"
        "Source/Core/ObserverPtr.cpp"
        "Source/Core/Plugin.cpp"
        "Source/Core/PluginRegistry.cpp"
        "Source/Core/Profiling.cpp"
        "Source/Core/PropertiesIteratorView.cpp"
        "Source/Core/Property.cpp"
        "Source/Core/PropertyDefinition.cpp"
        "Source/Core/PropertyDictionary.cpp"
        "Source/Core/PropertyParserAnimation.cpp"
        "Source/Core/PropertyParserColour.cpp"
        "Source/Core/PropertyParserKeyword.cpp"
        "Source/Core/PropertyParserNumber.cpp"
        "Source/Core/PropertyParserString.cpp"
        "Source/Core/PropertyParserTransform.cpp"
        "Source/Core/PropertySpecification.cpp"
        "Source/Core/RenderInterface.cpp"
        "Source/Core/Spritesheet.cpp"
        "Source/Core/Stream.cpp"
        "Source/Core/StreamFile.cpp"
        "Source/Core/StreamMemory.cpp"
        "Source/Core/StringUtilities.cpp"
        "Source/Core/StyleSheet.cpp"
        "Source/Core/StyleSheetFactory.cpp"
        "Source/Core/StyleSheetNode.cpp"
        "Source/Core/StyleSheetNodeSelector.cpp"
        "Source/Core/StyleSheetNodeSelectorEmpty.cpp"
        "Source/Core/StyleSheetNodeSelectorFirstChild.cpp"
        "Source/Core/StyleSheetNodeSelectorFirstOfType.cpp"
        "Source/Core/StyleSheetNodeSelectorLastChild.cpp"
        "Source/Core/StyleSheetNodeSelectorLastOfType.cpp"
        "Source/Core/StyleSheetNodeSelectorNthChild.cpp"
        "Source/Core/StyleSheetNodeSelectorNthLastChild.cpp"
        "Source/Core/StyleSheetNodeSelectorNthLastOfType.cpp"
        "Source/Core/StyleSheetNodeSelectorNthOfType.cpp"
        "Source/Core/StyleSheetNodeSelectorOnlyChild.cpp"
        "Source/Core/StyleSheetNodeSelectorOnlyOfType.cpp"
        "Source/Core/StyleSheetParser.cpp"
        "Source/Core/StyleSheetSpecification.cpp"
        "Source/Core/SystemInterface.cpp"
        "Source/Core/Template.cpp"
        "Source/Core/TemplateCache.cpp"
        "Source/Core/Texture.cpp"
        "Source/Core/TextureDatabase.cpp"
        "Source/Core/TextureLayout.cpp"
        "Source/Core/TextureLayoutRectangle.cpp"
        "Source/Core/TextureLayoutRow.cpp"
        "Source/Core/TextureLayoutTexture.cpp"
        "Source/Core/TextureResource.cpp"
        "Source/Core/Transform.cpp"
        "Source/Core/TransformPrimitive.cpp"
        "Source/Core/TransformState.cpp"
        "Source/Core/TransformUtilities.cpp"
        "Source/Core/Tween.cpp"
        "Source/Core/TypeConverter.cpp"
        "Source/Core/URL.cpp"
        "Source/Core/Variant.cpp"
        "Source/Core/Vector3.cpp"
        "Source/Core/Vector4.cpp"
        "Source/Core/WidgetScroll.cpp"
        "Source/Core/XMLNodeHandler.cpp"
        "Source/Core/XMLNodeHandlerBody.cpp"
        "Source/Core/XMLNodeHandlerDefault.cpp"
        "Source/Core/XMLNodeHandlerHead.cpp"
        "Source/Core/XMLNodeHandlerTemplate.cpp"
        "Source/Core/XMLParser.cpp"
        "Source/Core/XMLParseTools.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Header_Files}
        ${Source_Files}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
        )
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "RmlCore"
        TARGET_NAME_RELEASE "RmlCore"
        TARGET_NAME_MINSIZEREL "RmlCore"
        TARGET_NAME_RELWITHDEBINFO "RmlCore"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/bin"
        )
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
        >
        $<$<CONFIG:Release>:
        MultiThreadedDLL
        >
        $<$<CONFIG:MinSizeRel>:
        MultiThreadedDLL
        >
        $<$<CONFIG:RelWithDebInfo>:
        MultiThreadedDLL
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>,$<CONFIG:MinSizeRel>,$<CONFIG:RelWithDebInfo>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
        )
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../freetype/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public"
        )

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "CMAKE_INTDIR=\"Debug\""
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "CMAKE_INTDIR=\"Release\""
        ">"
        "$<$<CONFIG:MinSizeRel>:"
        "NDEBUG;"
        "CMAKE_INTDIR=\"MinSizeRel\""
        ">"
        "$<$<CONFIG:RelWithDebInfo>:"
        "NDEBUG;"
        "CMAKE_INTDIR=\"RelWithDebInfo\""
        ">"
        "WIN32;"
        "_WINDOWS;"
        "_CRT_SECURE_NO_WARNINGS;"
        "RMLUI_VERSION=\"4.0-dev\";"
        "RMLUI_STATIC_LIB;"
        "_MBCS"
        )

################################################################################
# Compile and link options
################################################################################
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /Od;
            /Ob0;
            /RTC1;
            /Zi
            >
            $<$<CONFIG:Release>:
            /O2;
            /Ob2;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:MinSizeRel>:
            /O1;
            /Ob1;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:RelWithDebInfo>:
            /O2;
            /Ob1;
            /Zi
            >
            /permissive-;
            /MP;
            /W4;
            /GR;
            /w44062;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
            )
endif ()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
        )


set(PROJECT_NAME RmlDebugger)

################################################################################
# Source groups
################################################################################

set(Header_Files
        "Include/RmlUi/Debugger.h"
        "Include/RmlUi/Debugger/Debugger.h"
        "Include/RmlUi/Debugger/Header.h"
        "Source/Debugger/BeaconSource.h"
        "Source/Debugger/CommonSource.h"
        "Source/Debugger/DebuggerPlugin.h"
        "Source/Debugger/DebuggerSystemInterface.h"
        "Source/Debugger/ElementContextHook.h"
        "Source/Debugger/ElementInfo.h"
        "Source/Debugger/ElementLog.h"
        "Source/Debugger/FontSource.h"
        "Source/Debugger/Geometry.h"
        "Source/Debugger/InfoSource.h"
        "Source/Debugger/LogSource.h"
        "Source/Debugger/MenuSource.h"
        )
source_group("Header Files" FILES ${Header_Files})

set(Source_Files
        "../../public/tier0/memoverride.cpp"
        "Source/Debugger/Debugger.cpp"
        "Source/Debugger/DebuggerPlugin.cpp"
        "Source/Debugger/DebuggerSystemInterface.cpp"
        "Source/Debugger/ElementContextHook.cpp"
        "Source/Debugger/ElementInfo.cpp"
        "Source/Debugger/ElementLog.cpp"
        "Source/Debugger/Geometry.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Header_Files}
        ${Source_Files}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
        )
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "RmlDebugger"
        TARGET_NAME_RELEASE "RmlDebugger"
        TARGET_NAME_MINSIZEREL "RmlDebugger"
        TARGET_NAME_RELWITHDEBINFO "RmlDebugger"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/bin"
        )
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
        MultiThreadedDebugDLL
        >
        $<$<CONFIG:Release>:
        MultiThreadedDLL
        >
        $<$<CONFIG:MinSizeRel>:
        MultiThreadedDLL
        >
        $<$<CONFIG:RelWithDebInfo>:
        MultiThreadedDLL
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>,$<CONFIG:MinSizeRel>,$<CONFIG:RelWithDebInfo>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
        )
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Include"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../public"
        )

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "CMAKE_INTDIR=\"Debug\""
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG;"
        "CMAKE_INTDIR=\"Release\""
        ">"
        "$<$<CONFIG:MinSizeRel>:"
        "NDEBUG;"
        "CMAKE_INTDIR=\"MinSizeRel\""
        ">"
        "$<$<CONFIG:RelWithDebInfo>:"
        "NDEBUG;"
        "CMAKE_INTDIR=\"RelWithDebInfo\""
        ">"
        "WIN32;"
        "_WINDOWS;"
        "_CRT_SECURE_NO_WARNINGS;"
        "RMLUI_STATIC_LIB;"
        "_MBCS"
        )

################################################################################
# Compile and link options
################################################################################
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /Od;
            /Ob0;
            /RTC1;
            /Zi
            >
            $<$<CONFIG:Release>:
            /O2;
            /Ob2;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:MinSizeRel>:
            /O1;
            /Ob1;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:RelWithDebInfo>:
            /O2;
            /Ob1;
            /Zi
            >
            /permissive-;
            /MP;
            /W4;
            /GR;
            /w44062;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
            )
endif ()

################################################################################
# Dependencies
################################################################################
# Link with other targets.
target_link_libraries(${PROJECT_NAME} PUBLIC
        RmlCore
        )

