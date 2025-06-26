
include_external_msproject(Devolutions.TermSrvRpc
    "${CMAKE_CURRENT_SOURCE_DIR}/Devolutions.TermSrvRpc/Devolutions.TermSrvRpc.csproj")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Directory.Build.props.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/Directory.Build.props" @ONLY)
