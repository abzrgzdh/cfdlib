add_library(cfd_linear_algebra STATIC)
add_library(cfd::linear_algebra ALIAS cfd_linear_algebra)

target_include_directories(cfd_linear_algebra
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(cfd_linear_algebra
    PRIVATE vector.cpp dense_matrix.cpp linear_solver.cpp conjugate_gradient.cpp
)

target_link_libraries(cfd_linear_algebra
    PUBLIC cfd::base cfd::core
)
