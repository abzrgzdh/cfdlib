add_executable(heat1d)
target_sources(heat1d PRIVATE heat1d/main.cpp)
target_link_libraries(heat1d PRIVATE cfd)
