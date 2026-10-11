add_library(cfd_core INTERFACE)
add_library(cfd::core ALIAS cfd_core)

target_include_directories(cfd_core INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(cfd_core INTERFACE cfd::base)
