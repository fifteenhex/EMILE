libfloppy_srcs = [ 'floppy_open.c' ]
libfloppy_inc = include_directories('include')
libfloppy_incs = [ libfloppy_inc, libstream_inc ]

libfloppy_deps = [ libmacos_dep]
if bootloader
    libfloppy_deps += picolibc_dep
endif

libfloppy = static_library('floppy',
                           libfloppy_srcs,
                           include_directories: libfloppy_incs,
                           dependencies: libfloppy_deps,
                           pic: not bootloader)
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
