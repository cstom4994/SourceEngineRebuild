

set(PROTO_COMPILER "protoc.exe")

#Built a .proto file and add the resulting C++ to the target.
macro(TargetBuildAndAddProto TARGET_NAME PROTO_FILE PROTO_OUTPUT_FOLDER)
    set(PROTO_FILENAME)
    get_filename_component(PROTO_FILENAME ${PROTO_FILE} NAME_WLE)

    add_custom_command(
            OUTPUT "${PROTO_OUTPUT_FOLDER}/${PROTO_FILENAME}.pb.cc"
            "${PROTO_OUTPUT_FOLDER}/${PROTO_FILENAME}.pb.h"
            COMMAND ${PROTO_COMPILER}
            ARGS --cpp_out=. --proto_path=${MYROOTDIR}/game/shared --proto_path=${MYROOTDIR}/thirdparty/protobuf-2.6.1/src --proto_path=${MYROOTDIR}/gcsdk --proto_path=${MYROOTDIR}/game/shared --proto_path=${MYROOTDIR}/common ${PROTO_FILE}
            DEPENDS ${PROTO_FILE} ${PROTO_COMPILER}
            WORKING_DIRECTORY ${PROTO_OUTPUT_FOLDER}
            COMMENT "Running homemade protoc compiler on ${PROTO_FILE} - output (${PROTO_OUTPUT_FOLDER}/${PROTO_FILENAME}.pb.cc)"
            VERBATIM
    )

    #add the output folder in the include path.
    target_include_directories(${TARGET_NAME} INTERFACE ${PROTO_OUTPUT_FOLDER})
    target_sources(${TARGET_NAME} INTERFACE ${PROTO_OUTPUT_FOLDER}/${PROTO_FILENAME}.pb.cc)
endmacro()