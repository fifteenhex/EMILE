libiso9660_srcs = [ 'iso9660_mount.c',
                    'iso9660_opendir.c',
                    'iso9660_closedir.c',
                    'iso9660_readdir.c',
                    'iso9660_is_directory.c',
                    'iso9660_lseek.c',
                    'iso9660_init.c' ]

libiso9660_deps = [ ]
if bootloader
    libiso9660_deps += picolibc_dep
endif

libiso9660_inc = include_directories('include')
libiso9660 = static_library('libiso9660', libiso9660_srcs,
                            include_directories: [libiso9660_inc, libstream_inc],
                            dependencies: libiso9660_deps,
                            pic: not bootloader)
libiso9660_dep = declare_dependency(link_with: libiso9660,
                                    include_directories: libiso9660_inc)
