subdir('unity')

glm_tests = executable('glm_tests', ['glm_tests.cpp'], dependencies: [gmath_dep, unity_dep, dependency('glm')])
test('glm_tests', glm_tests)

mat4_tests = executable('mat4_tests', ['mat4_tests.c'], dependencies: [gmath_dep, unity_dep])
test('mat4_tests', mat4_tests)

vec4_tests = executable('vec4_tests', ['vec4_tests.c'], dependencies: [gmath_dep, unity_dep])
test('vec4_tests', vec4_tests)

vec3_tests = executable('vec3_tests', ['vec3_tests.c'], dependencies: [gmath_dep, unity_dep])
test('vec3_tests', vec3_tests)
