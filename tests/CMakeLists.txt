add_subdirectory(unity)

add_executable(mat4_tests mat4_tests.c)
target_link_libraries(mat4_tests PRIVATE unity gmath)
target_compile_options(mat4_tests PRIVATE "-std=c99")

add_executable(vec3_tests vec3_tests.c)
target_link_libraries(vec3_tests PRIVATE unity gmath)
target_compile_options(vec3_tests PRIVATE "-std=c99")

add_executable(vec4_tests vec4_tests.c)
target_link_libraries(vec4_tests PRIVATE unity gmath)
target_compile_options(vec4_tests PRIVATE "-std=c99")

find_package(GLM)
if (GLM_FOUND)
  add_executable(glm_tests glm_tests.cpp)
  target_include_directories(glm_tests PRIVATE GLM_INCLUDE_DIRS)
  target_link_libraries(glm_tests PRIVATE unity gmath)
endif()
