
set(TERMSRVRPC_RESOURCES
    TermSrvRpc.rc)

windows_rc_generate_version_info(
    NAME "TermSrvRpc" TYPE "DLL"
    VERSION "${TERMSRVRPC_VERSION}"
    FILENAME "TermSrvRpc.dll"
    VENDOR "${TERMSRVRPC_VENDOR}"
    COPYRIGHT "${TERMSRVRPC_COPYRIGHT}"
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/version.rc)

set(NATIVE_ARCH "${MSVC_PLATFORM_TARGET}")

set(MIDL_INPUT_DIR "${CMAKE_SOURCE_DIR}/idl")
set(MIDL_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/idl/${NATIVE_ARCH}")

include_directories("${MIDL_INPUT_DIR}")
include_directories("${MIDL_OUTPUT_DIR}")

add_library(TermSrvRpc_Dll SHARED
    "${MIDL_OUTPUT_DIR}/SessEnvRpc_c.c"
    "${MIDL_OUTPUT_DIR}/SessEnvRpc.h"
    "${MIDL_OUTPUT_DIR}/tspubrpc_c.c"
    "${MIDL_OUTPUT_DIR}/tspubrpc.h"
    "${MIDL_OUTPUT_DIR}/rcmpublic_c.c"
    "${MIDL_OUTPUT_DIR}/rcmpublic.h"
    "${MIDL_OUTPUT_DIR}/TSVIPRpc_c.c"
    "${MIDL_OUTPUT_DIR}/TSVIPRpc.h"
    midl_user.c
    TermSrvRpc.def
    TermSrvRpc.cpp
    TermSrvRpc.h)

target_link_libraries(TermSrvRpc_Dll rpcrt4.lib)

set_target_properties(TermSrvRpc_Dll PROPERTIES OUTPUT_NAME "TermSrvRpc")
