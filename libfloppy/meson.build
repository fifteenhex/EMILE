libfloppy_srcs = ['floppy_read_sector.c',
                  'floppy_close.c',
                  'floppy_open.c',
                  'floppy_get_blocksize.c' ]
libfloppy_inc = include_directories('include')
libfloppy = static_library('floppy',
                           libfloppy_srcs,
                           include_directories: [libfloppy_inc],
                           dependencies: libmacos_dep)
libfloppy_dep = declare_dependency(link_with: libfloppy,
                                   include_directories: libfloppy_inc)
                                   
# Native
#if meson.is_cross_build()
#    libfloppy_native = static_library('floppy-native',
#                            libfloppy_srcs,
#                            include_directories: [libfloppy_inc])
#    libfloppy_native_dep = declare_dependency(link_with: libfloppy,
#                                            include_directories: libfloppy_inc)
#endif
