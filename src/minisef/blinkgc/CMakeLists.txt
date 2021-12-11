set(PROJECT_NAME blinkgc)

################################################################################
# Source groups
################################################################################
set(blinkgc__platform

        "mem_gc.cpp"
        "mem_gc.h"

        "../blinkgc/platform/Platform.cpp"
        "../blinkgc/platform/Platform.h"
        "../blinkgc/platform/PlatformExport.h"
        "../blinkgc/platform/ScriptForbiddenScope.cpp"
        "../blinkgc/platform/ScriptForbiddenScope.h"
        "../blinkgc/platform/Task.h"
        "../blinkgc/platform/traceevent.h"
        )
source_group("blinkgc\\platform" FILES ${blinkgc__platform})

set(blinkgc__platform__asm
        #    "../blinkgc/platform/asm/SaveRegisters_win64.asm"
        "../blinkgc/platform/asm/SaveRegisters_x86.cpp"
        )
source_group("blinkgc\\platform\\asm" FILES ${blinkgc__platform__asm})

set(blinkgc__platform__heap
        "../blinkgc/platform/heap/blink_heap.gypi"
        "../blinkgc/platform/heap/BlinkGCMemoryDumpProvider.cpp"
        "../blinkgc/platform/heap/BlinkGCMemoryDumpProvider.h"
        "../blinkgc/platform/heap/BUILD.gn"
        "../blinkgc/platform/heap/CallbackStack.cpp"
        "../blinkgc/platform/heap/CallbackStack.h"
        "../blinkgc/platform/heap/DEPS"
        "../blinkgc/platform/heap/GarbageCollected.h"
        "../blinkgc/platform/heap/GCInfo.cpp"
        "../blinkgc/platform/heap/GCInfo.h"
        "../blinkgc/platform/heap/Handle.h"
        "../blinkgc/platform/heap/Heap.cpp"
        "../blinkgc/platform/heap/Heap.h"
        "../blinkgc/platform/heap/HeapAllocator.cpp"
        "../blinkgc/platform/heap/HeapAllocator.h"
        "../blinkgc/platform/heap/HeapLinkedStack.h"
        "../blinkgc/platform/heap/HeapTerminatedArray.h"
        "../blinkgc/platform/heap/HeapTerminatedArrayBuilder.h"
        "../blinkgc/platform/heap/InlinedGlobalMarkingVisitor.h"
        "../blinkgc/platform/heap/MarkingVisitor.h"
        "../blinkgc/platform/heap/MarkingVisitorImpl.h"
        "../blinkgc/platform/heap/OWNERS"
        "../blinkgc/platform/heap/PageMemory.h"
        "../blinkgc/platform/heap/PagePool.cpp"
        "../blinkgc/platform/heap/PagePool.h"
        "../blinkgc/platform/heap/PersistentNode.cpp"
        "../blinkgc/platform/heap/PersistentNode.h"
        "../blinkgc/platform/heap/SafePoint.cpp"
        "../blinkgc/platform/heap/SafePoint.h"
        "../blinkgc/platform/heap/StackFrameDepth.cpp"
        "../blinkgc/platform/heap/StackFrameDepth.h"
        "../blinkgc/platform/heap/ThreadingTraits.h"
        "../blinkgc/platform/heap/ThreadState.cpp"
        "../blinkgc/platform/heap/ThreadState.h"
        "../blinkgc/platform/heap/TraceTraits.h"
        "../blinkgc/platform/heap/Visitor.h"
        )
source_group("blinkgc\\platform\\heap" FILES ${blinkgc__platform__heap})

set(blinkgc__web
        "../blinkgc/web/CurrentTimeImpl.cpp"
        "../blinkgc/web/CurrentTimeImpl.h"
        "../blinkgc/web/WebKit.cpp"
        "../blinkgc/web/WebKit.h"
        "../blinkgc/web/WebMemoryDumpProvider.cpp"
        "../blinkgc/web/WebScheduler.cpp"
        "../blinkgc/web/WebSchedulerImpl.cpp"
        "../blinkgc/web/WebSchedulerImpl.h"
        "../blinkgc/web/WebThreadImpl.cpp"
        "../blinkgc/web/WebThreadImpl.h"
        "../blinkgc/web/WebTimerBase.cpp"
        "../blinkgc/web/WebTimerBase.h"
        "../blinkgc/web/WebTraceLocation.cpp"
        )
source_group("blinkgc\\web" FILES ${blinkgc__web})

set(blinkgc__wtf
        "../blinkgc/wtf/AddressSanitizer.h"
        "../blinkgc/wtf/AddressSpaceRandomization.cpp"
        "../blinkgc/wtf/AddressSpaceRandomization.h"
        "../blinkgc/wtf/Alignment.h"
        "../blinkgc/wtf/ArrayBuffer.cpp"
        "../blinkgc/wtf/ArrayBuffer.h"
        "../blinkgc/wtf/ArrayBufferBuilder.cpp"
        "../blinkgc/wtf/ArrayBufferBuilder.h"
        "../blinkgc/wtf/ArrayBufferContents.cpp"
        "../blinkgc/wtf/ArrayBufferContents.h"
        "../blinkgc/wtf/ArrayBufferView.cpp"
        "../blinkgc/wtf/ArrayBufferView.h"
        "../blinkgc/wtf/ArrayPiece.cpp"
        "../blinkgc/wtf/ArrayPiece.h"
        "../blinkgc/wtf/ASCIICType.h"
        "../blinkgc/wtf/Assertions.cpp"
        "../blinkgc/wtf/Assertions.h"
        "../blinkgc/wtf/Atomics.h"
        "../blinkgc/wtf/BitArray.h"
        "../blinkgc/wtf/BitVector.cpp"
        "../blinkgc/wtf/BitVector.h"
        "../blinkgc/wtf/BitwiseOperations.h"
        "../blinkgc/wtf/BloomFilter.h"
        "../blinkgc/wtf/BUILD.gn"
        "../blinkgc/wtf/ByteOrder.h"
        "../blinkgc/wtf/ByteSwap.h"
        "../blinkgc/wtf/CheckedArithmetic.h"
        "../blinkgc/wtf/Compiler.h"
        "../blinkgc/wtf/ConditionalDestructor.h"
        "../blinkgc/wtf/ContainerAnnotations.h"
        "../blinkgc/wtf/CONTRIBUTORS.pthreads-win32"
        "../blinkgc/wtf/CPU.h"
        "../blinkgc/wtf/CryptographicallyRandomNumber.cpp"
        "../blinkgc/wtf/CryptographicallyRandomNumber.h"
        "../blinkgc/wtf/CurrentTime.cpp"
        "../blinkgc/wtf/CurrentTime.h"
        "../blinkgc/wtf/DataLog.cpp"
        "../blinkgc/wtf/DataLog.h"
        "../blinkgc/wtf/DateMath.cpp"
        "../blinkgc/wtf/DateMath.h"
        "../blinkgc/wtf/DefaultAllocator.cpp"
        "../blinkgc/wtf/DefaultAllocator.h"
        "../blinkgc/wtf/Deque.h"
        "../blinkgc/wtf/DoublyLinkedList.h"
        "../blinkgc/wtf/dtoa.cpp"
        "../blinkgc/wtf/dtoa.h"
        "../blinkgc/wtf/DynamicAnnotations.cpp"
        "../blinkgc/wtf/DynamicAnnotations.h"
        "../blinkgc/wtf/FastAllocBase.h"
        "../blinkgc/wtf/FastMalloc.cpp"
        "../blinkgc/wtf/FastMalloc.h"
        "../blinkgc/wtf/FilePrintStream.cpp"
        "../blinkgc/wtf/FilePrintStream.h"
        "../blinkgc/wtf/Float32Array.h"
        "../blinkgc/wtf/Float64Array.h"
        "../blinkgc/wtf/Forward.h"
        "../blinkgc/wtf/Functional.h"
        "../blinkgc/wtf/GetPtr.h"
        "../blinkgc/wtf/HashCountedSet.h"
        "../blinkgc/wtf/HashFunctions.h"
        "../blinkgc/wtf/HashIterators.h"
        "../blinkgc/wtf/HashMap.h"
        "../blinkgc/wtf/HashSet.h"
        "../blinkgc/wtf/HashTable.cpp"
        "../blinkgc/wtf/HashTable.h"
        "../blinkgc/wtf/HashTableDeletedValueType.h"
        "../blinkgc/wtf/HashTraits.h"
        "../blinkgc/wtf/HexNumber.h"
        "../blinkgc/wtf/InstanceCounter.cpp"
        "../blinkgc/wtf/InstanceCounter.h"
        "../blinkgc/wtf/Int16Array.h"
        "../blinkgc/wtf/Int32Array.h"
        "../blinkgc/wtf/Int8Array.h"
        "../blinkgc/wtf/IntegralTypedArrayBase.h"
        "../blinkgc/wtf/LeakAnnotations.h"
        "../blinkgc/wtf/LinkedHashSet.h"
        "../blinkgc/wtf/LinkedStack.h"
        "../blinkgc/wtf/ListHashSet.h"
        "../blinkgc/wtf/Locker.h"
        "../blinkgc/wtf/MainThread.cpp"
        "../blinkgc/wtf/MainThread.h"
        "../blinkgc/wtf/MathExtras.h"
        "../blinkgc/wtf/MessageQueue.h"
        "../blinkgc/wtf/Noncopyable.h"
        "../blinkgc/wtf/NonCopyingSort.h"
        "../blinkgc/wtf/NotFound.h"
        "../blinkgc/wtf/NullPtr.h"
        "../blinkgc/wtf/Optional.h"
        "../blinkgc/wtf/OWNERS"
        "../blinkgc/wtf/OwnPtr.h"
        "../blinkgc/wtf/OwnPtrCommon.h"
        "../blinkgc/wtf/PageAllocator.cpp"
        "../blinkgc/wtf/PageAllocator.h"
        "../blinkgc/wtf/PartitionAlloc.cpp"
        "../blinkgc/wtf/PartitionAlloc.h"
        "../blinkgc/wtf/Partitions.cpp"
        "../blinkgc/wtf/Partitions.h"
        "../blinkgc/wtf/PassOwnPtr.h"
        "../blinkgc/wtf/PassRefPtr.h"
        "../blinkgc/wtf/PassTraits.h"
        "../blinkgc/wtf/PrintStream.cpp"
        "../blinkgc/wtf/PrintStream.h"
        "../blinkgc/wtf/RawPtr.h"
        "../blinkgc/wtf/RefCounted.h"
        "../blinkgc/wtf/RefCountedLeakCounter.cpp"
        "../blinkgc/wtf/RefCountedLeakCounter.h"
        "../blinkgc/wtf/RefPtr.h"
        "../blinkgc/wtf/RefVector.h"
        "../blinkgc/wtf/RetainPtr.h"
        "../blinkgc/wtf/SaturatedArithmetic.h"
        "../blinkgc/wtf/SizeLimits.cpp"
        "../blinkgc/wtf/SpinLock.h"
        "../blinkgc/wtf/StaticConstructors.h"
        "../blinkgc/wtf/StdLibExtras.h"
        "../blinkgc/wtf/StreamBuffer.h"
        "../blinkgc/wtf/StringExtras.h"
        "../blinkgc/wtf/StringHasher.h"
        "../blinkgc/wtf/TemporaryChange.h"
        "../blinkgc/wtf/TerminatedArray.h"
        "../blinkgc/wtf/TerminatedArrayBuilder.h"
        "../blinkgc/wtf/Threading.h"
        "../blinkgc/wtf/ThreadingPrimitives.h"
        "../blinkgc/wtf/ThreadingPthreads.cpp"
        "../blinkgc/wtf/ThreadingWin.cpp"
        "../blinkgc/wtf/ThreadRestrictionVerifier.h"
        "../blinkgc/wtf/ThreadSafeRefCounted.h"
        "../blinkgc/wtf/ThreadSpecific.h"
        "../blinkgc/wtf/ThreadSpecificWin.cpp"
        "../blinkgc/wtf/TreeNode.h"
        "../blinkgc/wtf/TriState.h"
        "../blinkgc/wtf/TypedArrayBase.h"
        "../blinkgc/wtf/TypeTraits.cpp"
        "../blinkgc/wtf/TypeTraits.h"
        "../blinkgc/wtf/Uint16Array.h"
        "../blinkgc/wtf/Uint32Array.h"
        "../blinkgc/wtf/Uint8Array.h"
        "../blinkgc/wtf/Uint8ClampedArray.h"
        "../blinkgc/wtf/Utility.h"
        "../blinkgc/wtf/Vector.h"
        "../blinkgc/wtf/VectorTraits.h"
        "../blinkgc/wtf/WeakPtr.h"
        "../blinkgc/wtf/WTF.cpp"
        "../blinkgc/wtf/wtf.gyp"
        "../blinkgc/wtf/wtf.gypi"
        "../blinkgc/wtf/WTF.h"
        "../blinkgc/wtf/wtf.sln"
        "../blinkgc/wtf/wtf.vcxproj"
        "../blinkgc/wtf/wtf.vcxproj.filters"
        "../blinkgc/wtf/wtf_config.vcxproj"
        "../blinkgc/wtf/wtf_config.vcxproj.filters"
        "../blinkgc/wtf/wtf_tests.gyp"
        "../blinkgc/wtf/wtf_tests.sln"
        "../blinkgc/wtf/wtf_unittest_helpers.vcxproj"
        "../blinkgc/wtf/wtf_unittest_helpers.vcxproj.filters"
        "../blinkgc/wtf/wtf_unittests.vcxproj"
        "../blinkgc/wtf/wtf_unittests.vcxproj.filters"
        "../blinkgc/wtf/WTFExport.h"
        "../blinkgc/wtf/WTFThreadData.cpp"
        "../blinkgc/wtf/WTFThreadData.h"
        )
source_group("blinkgc\\wtf" FILES ${blinkgc__wtf})

set(blinkgc__wtf__dtoa
        "../blinkgc/wtf/dtoa/bignum-dtoa.cc"
        "../blinkgc/wtf/dtoa/bignum-dtoa.h"
        "../blinkgc/wtf/dtoa/bignum.cc"
        "../blinkgc/wtf/dtoa/bignum.h"
        "../blinkgc/wtf/dtoa/cached-powers.cc"
        "../blinkgc/wtf/dtoa/cached-powers.h"
        "../blinkgc/wtf/dtoa/COPYING"
        "../blinkgc/wtf/dtoa/diy-fp.cc"
        "../blinkgc/wtf/dtoa/diy-fp.h"
        "../blinkgc/wtf/dtoa/double-conversion.cc"
        "../blinkgc/wtf/dtoa/double-conversion.h"
        "../blinkgc/wtf/dtoa/double.h"
        "../blinkgc/wtf/dtoa/fast-dtoa.cc"
        "../blinkgc/wtf/dtoa/fast-dtoa.h"
        "../blinkgc/wtf/dtoa/fixed-dtoa.cc"
        "../blinkgc/wtf/dtoa/fixed-dtoa.h"
        "../blinkgc/wtf/dtoa/LICENSE"
        "../blinkgc/wtf/dtoa/README"
        "../blinkgc/wtf/dtoa/strtod.cc"
        "../blinkgc/wtf/dtoa/strtod.h"
        "../blinkgc/wtf/dtoa/utils.h"
        )
source_group("blinkgc\\wtf\\dtoa" FILES ${blinkgc__wtf__dtoa})

set(blinkgc__wtf__text
        "../blinkgc/wtf/text/ASCIIFastPath.h"
        "../blinkgc/wtf/text/AtomicString.cpp"
        "../blinkgc/wtf/text/AtomicString.h"
        "../blinkgc/wtf/text/AtomicStringCF.cpp"
        "../blinkgc/wtf/text/AtomicStringHash.h"
        "../blinkgc/wtf/text/Base64.cpp"
        "../blinkgc/wtf/text/Base64.h"
        "../blinkgc/wtf/text/CharacterNames.h"
        "../blinkgc/wtf/text/Collator.h"
        "../blinkgc/wtf/text/CString.cpp"
        "../blinkgc/wtf/text/CString.h"
        "../blinkgc/wtf/text/IntegerToStringConversion.h"
        "../blinkgc/wtf/text/StringBuffer.h"
        "../blinkgc/wtf/text/StringBuilder.cpp"
        "../blinkgc/wtf/text/StringBuilder.h"
        "../blinkgc/wtf/text/StringCF.cpp"
        "../blinkgc/wtf/text/StringConcatenate.cpp"
        "../blinkgc/wtf/text/StringConcatenate.h"
        "../blinkgc/wtf/text/StringHash.h"
        "../blinkgc/wtf/text/StringImpl.cpp"
        "../blinkgc/wtf/text/StringImpl.h"
        "../blinkgc/wtf/text/StringImplCF.cpp"
        #        "../blinkgc/wtf/text/StringImplMac.mm"
        #        "../blinkgc/wtf/text/StringMac.mm"
        "../blinkgc/wtf/text/StringOperators.h"
        "../blinkgc/wtf/text/StringStatics.cpp"
        "../blinkgc/wtf/text/StringStatics.h"
        "../blinkgc/wtf/text/StringUTF8Adaptor.h"
        "../blinkgc/wtf/text/StringView.h"
        "../blinkgc/wtf/text/TextCodec.cpp"
        "../blinkgc/wtf/text/TextCodec.h"
        "../blinkgc/wtf/text/TextCodecASCIIFastPath.h"
        "../blinkgc/wtf/text/TextCodecICU.h"
        "../blinkgc/wtf/text/TextCodecLatin1.cpp"
        "../blinkgc/wtf/text/TextCodecLatin1.h"
        "../blinkgc/wtf/text/TextCodecReplacement.cpp"
        "../blinkgc/wtf/text/TextCodecReplacement.h"
        "../blinkgc/wtf/text/TextCodecUserDefined.cpp"
        "../blinkgc/wtf/text/TextCodecUserDefined.h"
        "../blinkgc/wtf/text/TextCodecUTF16.cpp"
        "../blinkgc/wtf/text/TextCodecUTF16.h"
        "../blinkgc/wtf/text/TextCodecUTF8.cpp"
        "../blinkgc/wtf/text/TextCodecUTF8.h"
        "../blinkgc/wtf/text/TextEncoding.h"
        "../blinkgc/wtf/text/TextEncodingRegistry.h"
        "../blinkgc/wtf/text/TextPosition.cpp"
        "../blinkgc/wtf/text/TextPosition.h"
        "../blinkgc/wtf/text/Unicode.h"
        "../blinkgc/wtf/text/UTF8.cpp"
        "../blinkgc/wtf/text/UTF8.h"
        "../blinkgc/wtf/text/WTFString.cpp"
        "../blinkgc/wtf/text/WTFString.h"
        "../blinkgc/wtf/text/WTFStringUtil.cpp"
        "../blinkgc/wtf/text/WTFStringUtil.h"
        )
source_group("blinkgc\\wtf\\text" FILES ${blinkgc__wtf__text})

set(blinkgc__wtf__text__qt4
        "../blinkgc/wtf/text/qt4/QChar.h"
        "../blinkgc/wtf/text/qt4/QString.h"
        "../blinkgc/wtf/text/qt4/QtGlobal.h"
        "../blinkgc/wtf/text/qt4/qunicodetables.h"
        "../blinkgc/wtf/text/qt4/UnicodeMacrosFromICU.h"
        "../blinkgc/wtf/text/qt4/UnicodeQt4.cpp"
        "../blinkgc/wtf/text/qt4/UnicodeQt4.h"
        )
source_group("blinkgc\\wtf\\text\\qt4" FILES ${blinkgc__wtf__text__qt4})


set(ALL_FILES
        ${blinkgc__platform}
        ${blinkgc__platform__asm}
        ${blinkgc__platform__heap}
        ${blinkgc__web}
        ${blinkgc__wtf}
        ${blinkgc__wtf__dtoa}
        ${blinkgc__wtf__text}
        ${blinkgc__wtf__text__qt4}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG "blinkgc"
        TARGET_NAME_RELEASE "blinkgc"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG "${MYROOTDIR}/../game/bin"
        OUTPUT_DIRECTORY_RELEASE "${MYROOTDIR}/../game/bin"
        )
################################################################################
# Include directories
################################################################################

target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/../blinkgc"
        )


################################################################################
# Compile definitions
################################################################################

target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
        "NDEBUG"
        ">"
        "WIN32;"
        "_CONSOLE;"
        "UNICODE;"
        "_UNICODE"
        )


################################################################################
# Compile and link options
################################################################################

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
        /Od
        >
        $<$<CONFIG:Release>:
        /O2;
        /Oi;
        /Gy
        >
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING};
        /Y-
        )

target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
        /INCREMENTAL
        >
        $<$<CONFIG:Release>:
        /OPT:REF;
        /OPT:ICF;
        /INCREMENTAL:NO
        >
        /DEBUG;
        /SUBSYSTEM:CONSOLE
        )


