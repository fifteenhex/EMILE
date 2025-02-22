libstream_srcs = [ 'stream_close.c',
                   'stream_open.c',
                   'stream_read.c',
                   'stream_lseek.c',
                   'stream_uncompress.c',
                   'gzio.c',
                   'stream_fstat.c',
                   'stream_set_default.c' ]

libstream_dep = [ libgzip_dep, libmacos_dep ]
libstream_native_dep = [ libgzip_native_dep ]

libstream_scsi_flags      = '-DSCSI_SUPPORT'
libstream_iso9660_flags   = '-DISO9660_SUPPORT'
libstream_ext2_flag       = '-DEXT2_SUPPORT'
libstream_container_flags = '-DCONTAINER_SUPPORT'
libstream_floppy_flags    = '-DFLOPPY_SUPPORT'
libstream_block_flags     = '-DBLOCK_SUPPORT'
libstream_map_flags       = '-DMAP_SUPPORT'

libstream_full_flags      = [ libstream_scsi_flags,
                              libstream_iso9660_flags,
                              libstream_ext2_flag,
                              libstream_container_flags,
                              libstream_floppy_flags,
                              libstream_block_flags,
                              libstream_map_flags ]

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
                           c_args: libstream_full_flags)

libstream_dep = declare_dependency(link_with: libstream, include_directories: libstream_inc)

# native version
if meson.is_cross_build()
    libstream_native = static_library('stream-native',
                            libstream_srcs,
                            include_directories: libstream_inc,
                            dependencies: libstream_native_dep,
                            native: true)
    libstream_native_dep = declare_dependency(link_with: libstream_native, include_directories: libstream_inc)
endif
