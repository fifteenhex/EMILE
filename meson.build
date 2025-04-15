project('EMILE', 'c',
        meson_version: '>= 1.3.2')

# Set the global version
add_global_arguments('-DVERSION="xxx"', language: 'c')

# Force PIC on
add_global_arguments('-fpic', language: 'c')

# For now disable the stack protector globally so the second stage can link
add_global_arguments('-fno-stack-protector', language: 'c')

# This stops GCC from converting some manual mem[set|move|cpy] loops into
# which cause the link to fail function calls
add_global_arguments('-fno-tree-loop-distribute-patterns', language: 'c')

add_global_arguments('--param=min-pagesize=0', language: 'c')


# Make some warnings into errors
cc = meson.get_compiler('c')
warning_cflags = cc.get_supported_arguments([
    '-Wall',
    '-Werror=incompatible-pointer-types',
    '-Werror=implicit-function-declaration',
])

add_global_arguments(warning_cflags, language: 'c')

# Supress some warnings that need code fixes
add_global_arguments('-Wno-multichar', language: 'c')
add_global_arguments('-Wno-address-of-packed-member', language: 'c')

objcopy = find_program('objcopy')

subdir('libgzip')
subdir('libconfig')

libstream_inc = include_directories('libstream/include')
subdir('libiso9660')
subdir('libmacos')
subdir('libfloppy')
subdir('libscsi')
subdir('libext2')
subdir('libblock')
subdir('libcontainer')
libemile_inc = include_directories('libemile/include')
subdir('libmap')
subdir('libstream')



subdir('libemile')


subdir('libui')
subdir('libunix')
subdir('first')
subdir('second')
subdir('tools')
