project('libconfig', 'c',
        meson_version: '>= 1.3.2')
        
libconfig_srcs = [ 'config_get_indexed_property.c',
                   'config_get_next_property.c',
                   'config_get_property.c',
                   'config_remove_property.c',
                   'config_set_property.c',
                   'config_set_indexed_property.c',
                   'config_remove_indexed_property.c',
                   'config_find_indexed_property.c',
                   'config_find_entry.c',
                   'config_add_property.c' ]
libconfig_inc = include_directories('include')

libconfig = static_library('config',
                           libconfig_srcs,
                           include_directories: libconfig_inc)

libconfig_dep = declare_dependency(link_with: libconfig,
                                   include_directories: libconfig_inc)

# native version for building tools
libconfig_native = static_library('config-native',
                           libconfig_srcs,
                           include_directories: libconfig_inc,
                           native: true)

libconfig_native_dep = declare_dependency(link_with: libconfig_native,
                                          include_directories: libconfig_inc)
