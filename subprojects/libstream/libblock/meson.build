libblock_srcs = [ 'block_close.c',
                  'block_fstat.c',
                  'block_lseek.c',
                  'block_read.c',
                  'block_init.c',
                  'block_mount.c' ]
libblock_inc = include_directories('include')

libblock_deps = [ ]
if baremetal
    libblock_deps += picolibc_dep
endif

libblock = static_library('block', libblock_srcs,
                          include_directories: [libblock_inc, libstream_inc],
                          dependencies: libblock_deps,
                          pic: not baremetal)
libblock_dep = declare_dependency(link_with: libblock, include_directories: libblock_inc)
