project('gmath', 'c', 'cpp', default_options : ['c_std=c99', 'cpp_std=c++11'])

add_global_arguments('-Wno-missing-braces', language : 'c')

gmath_dep = declare_dependency(include_directories: include_directories('.'))

subdir('tests')
