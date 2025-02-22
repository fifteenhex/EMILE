libiso9660_srcs = [ 'iso9660_mount.c',
                    'iso9660_opendir.c',
                    'iso9660_closedir.c',
                    'iso9660_readdir.c',
                    'iso9660_is_directory.c',
                    'iso9660_open.c',
                    'iso9660_read.c',
                    'iso9660_close.c',
                    'iso9660_lseek.c',
                    'iso9660_fstat.c',
                    'iso9660_init.c' ]
libiso9660_inc = include_directories('include')
libiso9660 = static_library('libiso9660', libiso9660_srcs,
                            include_directories: [libiso9660_inc, libstream_inc])
libiso9660_dep = declare_dependency(link_with: libiso9660,
                                    include_directories: libiso9660_inc)

if meson.is_cross_build()
    libiso9660_native = static_library('libiso9660-native',
                                    libiso9660_srcs,
                                    include_directories: [libiso9660_inc, libstream_inc],
                                    native: true)
    libiso9660_native_dep = declare_dependency(link_with: libiso9660_native, 
                                            include_directories: libiso9660_inc)
endif
