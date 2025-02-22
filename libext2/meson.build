libext2_srcs = [ 'ext2_mount.c',
                 'ext2_opendir.c',
                 'ext2_closedir.c',
                 'ext2_open.c',
                 'ext2_init.c',
                 'ext2_read.c',
                 'ext2_close.c',
                 'ext2_lseek.c',
                 'ext2_fstat.c',
                 'ext2_utils.c',
                 'ext2_readdir.c' ]
libext2_inc = include_directories('include')
libext2 = static_library('config', libext2_srcs,
                         include_directories: [ libext2_inc, libstream_inc ])
libext2_dep = declare_dependency(link_with: libext2, include_directories: libext2_inc)
