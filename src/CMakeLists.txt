add_subdirectory(core)
add_subdirectory(linear_algebra)

add_library(cfd INTERFACE)
target_link_libraries(cfd
    INTERFACE cfd::base cfd::core cfd::linear_algebra
)
target_include_directories(cfd INTERFACE ${CMAKE_CURRENT_LIST_DIR})
