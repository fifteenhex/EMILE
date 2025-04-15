libmacos_proj = subproject('libmacos')
libmacos_inc = libmacos_proj.get_variable('libmacos_inc')

libunix_srcs = [ 
    'free.c',
    'malloc.c',
    'read.c',
    'write.c',
]

libunix = static_library('libunix', libunix_srcs,
                         include_directories:  [ libmacos_inc ],
                         dependencies: picolibc_dep,
                         pic: false)

libunix_dep = declare_dependency(link_with: libunix)
