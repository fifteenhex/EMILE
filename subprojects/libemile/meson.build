project('libemile', 'c')

libstream_proj = subproject('libstream')
libstream_dep = libstream_proj.get_variable('libstream_dep')
libstream_inc = libstream_proj.get_variable('libstream_inc_dirs')

libconfig_proj = subproject('libconfig')
libconfig_dep = libconfig_proj.get_variable('libconfig_dep')
libconfig_inc = libconfig_proj.get_variable('libconfig_inc')

libemile_inc = include_directories('include')
        
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

libemile_incdirs = [ libemile_inc ]

libemile = static_library('emile', libemile_srcs,
                          include_directories: libemile_incdirs,
                          dependencies: [ libstream_dep, libconfig_dep ])

libemile_inc_dirs = [ libemile_inc, libstream_inc, libconfig_inc ]
libemile_dep = declare_dependency(link_with: libemile,
                                  include_directories: libemile_inc_dirs)
