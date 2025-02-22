libemile_srcs = [ 'emile_first_get_param.c',
                  'emile_first_set_param.c',
                  'emile_first_set_param_scsi.c',
                  'emile_floppy_create_image.c',
                  'emile_second_create_mapfile.c',
                  'emile_scsi_create_container.c',
                  'emile_scsi_get_dev.c',
                  'emile_scsi_get_rdev.c',
                  'emile_second_get_configuration.c',
                  'emile_second_set_configuration.c',
                  'emile_second_set_param.c',
                  'emile_second_get_param.c',
                  'emile_first_set_param_scsi_extents.c' ]

libemile_incdirs = [ libemile_inc,
                     libconfig_inc,
                     libcontainer_inc,
                     libstream_inc ]

libemile = static_library('emile', libemile_srcs,
                          include_directories: libemile_incdirs,
                          dependencies: [libmap_dep, libcontainer_dep])

libemile_dep = declare_dependency(link_with: libemile, include_directories: libemile_inc)

# Native version for building native tools
if meson.is_cross_build()
    libemile_native = static_library('emile-native', libemile_srcs,
                            include_directories: libemile_incdirs,
                            dependencies: [libmap_native_dep, libcontainer_native_dep],
                            native: true)
    libemile_native_dep = declare_dependency(link_with: libemile_native, include_directories: libemile_inc)
endif
