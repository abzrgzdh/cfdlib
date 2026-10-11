add_library(cfd_base INTERFACE)
add_library(cfd::base ALIAS cfd_base)

target_compile_features(cfd_base
    INTERFACE cxx_std_23
)

set_target_properties(cfd_base PROPERTIES
    INTERFACE_CXX_STANDARD_REQUIRED ON
    INTERFACE_CXX_EXTENSIONS OFF
)

set(CFD_GCC_LIKE_CXX "$<COMPILE_LANG_AND_ID:CXX,AppleClang,Clang,GNU>")
set(CFD_MSVC_CXX "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(cfd_base INTERFACE
    "$<${CFD_GCC_LIKE_CXX}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wconversion;-Wsign-conversion;-Wshadow;-Wpedantic;>>"
    "$<${CFD_MSVC_CXX}:$<BUILD_INTERFACE:/W4>>"
)
