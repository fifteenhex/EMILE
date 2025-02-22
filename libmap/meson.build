libmap_srcs = [ 'map_bootblock_get_type.c',
                'map_bootblock_is_valid.c',
                'map_bootblock_read.c',
                'map_bootblock_write.c',
                'map_close.c',
                'map_geometry.c',
                'map_get_bootinfo.c',
                'map_get_driver_info.c',
                'map_get_driver_number.c',
                'map_get_driver_signature.c',
                'map_get_number.c',
                'map_get_partition_geometry.c',
                'map_get_partition_name.c',
                'map_get_partition_type.c',
                'map_has_apple_driver.c',
                'map_is_valid.c',
                'map_open.c',
                'map_partition_get_flags.c',
                'map_partition_is_bootable.c',
                'map_partition_is_startup.c',
                'map_partition_is_valid.c',
                'map_partition_set_bootable.c',
                'map_partition_set_flags.c',
                'map_partition_set_startup.c',
                'map_read.c',
                'map_seek_driver_partition.c',
                'map_set_bootinfo.c',
                'map_set_driver_info.c',
                'map_set_driver_number.c',
                'map_set_partition_name.c',
                'map_set_partition_type.c',
                'map_set_startup.c',
                'map_write.c',
                'map_block0_write.c',
                'map_read_sector.c',
                'map_checksum.c',
                'map_write_sector.c',
                'map_get_blocksize.c',
                'map_init.c',
                'map_read_driver.c',
                'map_write_driver.c',
                'map_update_checksum.c' ]
libmap_inc = include_directories('include')
libmap = static_library('map', libmap_srcs,
                        include_directories: [libmap_inc, libstream_inc, libemile_inc])
libmap_dep = declare_dependency(link_with: libmap, include_directories: [libmap_inc, libemile_inc])

# native version
if meson.is_cross_build()
    libmap_native = static_library('map-native', libmap_srcs,
                                include_directories: [libmap_inc, libstream_inc, libemile_inc],
                                native: true)
    libmap_native_dep = declare_dependency(link_with: libmap_native,
                                           include_directories: [libmap_inc, libemile_inc])
endif


