project('libstream', 'c')

cc = meson.get_compiler('c')
        
compiler_proj = subproject('compiler')
compiler_inc = compiler_proj.get_variable('compiler_inc')

libstream_inc = [ include_directories('include') ]
libstream_inc += compiler_inc

# Are we building this for the userspace tools or for the baremetal part?
baremetal = get_option('baremetal')
enable_gzip = get_option('gzip')

libstream_dep = [ ]
if baremetal
    picolibc_proj = subproject('picolibc',
                            default_options: [ 'multilib=false',
                                                'freestanding=true',
                                                'picocrt=false',
                                                'single-thread=true',
                                                'initfini-array=false',
                                                'thread-local-storage=false',
                                                'newlib-nano-malloc=false',
                                                'semihost=false'])
    picolibc_dep = picolibc_proj.get_variable('picolibc_dep')
    libstream_dep += picolibc_dep
endif

subdir('libcontainer')
subdir('libblock')
subdir('libext2')
subdir('libiso9660')
subdir('libmap')

if baremetal
    libmacos_proj = subproject('libmacos')
    libmacos_dep = libmacos_proj.get_variable('libmacos_dep')
    libstream_dep += libmacos_dep
    subdir('libfloppy')
    subdir('libscsi')
endif

libstream_srcs = [ 'stream_open.c',
                   'stream_uncompress.c',
                   'stream_set_default.c' ]

libstream_scsi_flag      = '-DSCSI_SUPPORT'
libstream_scsi_flags     = [ ] + libstream_scsi_flag

libstream_iso9660_flags   = '-DISO9660_SUPPORT'
libstream_ext2_flag       = '-DEXT2_SUPPORT'
libstream_container_flags = '-DCONTAINER_SUPPORT'

libstream_floppy_flag    = '-DFLOPPY_SUPPORT'
libstream_floppy_flags    = [ ] + libstream_floppy_flag

libstream_block_flags     = '-DBLOCK_SUPPORT'
libstream_map_flags       = '-DMAP_SUPPORT'
libstream_gzip_flag       = '-DGZIP_SUPPORT'


libstream_full_flags = [ libstream_map_flags ]
                   
if enable_gzip
    rtgz_tinf_util = subproject('rtgz-tinf-util')
    rtgz_tinf_util_dep = rtgz_tinf_util.get_variable('rtgz_tinf_util_dep')

    libstream_dep += rtgz_tinf_util_dep
    libstream_full_flags += libstream_gzip_flag
    libstream_scsi_flags += libstream_gzip_flag
    libstream_floppy_flags += libstream_gzip_flag
    libstream_srcs += 'stream_uncompress_gzip.c'
endif

if baremetal
    libstream_dep += picolibc_dep

    libstream_full_flags += [ libstream_scsi_flag,
                             libstream_iso9660_flags,
                             libstream_ext2_flag,
                             libstream_container_flags,
                             libstream_floppy_flag,
                             libstream_block_flags ]

    libstream_floppy = static_library('stream_floppy',
                            libstream_srcs,
                            include_directories: libstream_inc,
                            dependencies: libstream_dep + libfloppy_dep,
                            c_args: [libstream_floppy_flags])

    libstream_scsi = static_library('stream_scsi',
                            libstream_srcs,
                            include_directories: libstream_inc,
                            dependencies: libstream_dep + libscsi_dep,
                            c_args: [libstream_scsi_flags])
    libstream = static_library('stream',
                            libstream_srcs,
                            include_directories: libstream_inc,
                            dependencies: [ libstream_dep,
                                            libscsi_dep,
                                            libiso9660_dep,
                                            libext2_dep,
                                            libcontainer_dep,
                                            libfloppy_dep,
                                            libblock_dep,
                                            libmap_dep ],
                            c_args: libstream_full_flags,
                            pic: false)
else
    libstream = static_library('stream',
                                libstream_srcs,
                                include_directories: libstream_inc,
                                dependencies: [ libstream_dep, libmap_dep ],
                                c_args: libstream_full_flags)
endif

libstream_link_libs = [ libstream,
                        libiso9660,
                        libext2 ]

libstream_inc_dirs = [ libstream_inc,
                       libcontainer_inc,
                       libext2_inc,
                       libiso9660_inc,
                       libmap_inc,
                       compiler_inc ]

libstream_dep = declare_dependency(link_with: libstream_link_libs,
                                   include_directories: libstream_inc_dirs)
