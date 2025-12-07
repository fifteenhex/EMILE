project('emile-userspace-tools', 'c',
        meson_version: '>= 1.3.2')

libemile_proj = subproject('libemile')
libemile_dep = libemile_proj.get_variable('libemile_dep')

tools_inc = include_directories('include')

device_lib = static_library('device',
                            'device.c',
                            include_directories: tools_inc,
                            dependencies: libemile_dep)

device_dep = declare_dependency(link_with: device_lib,
             include_directories: tools_inc)
             device_dep

tools_installdir = 'sbin'
tools_deps = [ libemile_dep, device_dep ]

tools_cargs = [ '-DSIGNATURE="xxxx"', '-DPREFIX=""' ]

emile_set_cmdline = executable('emile-set-cmdline',
                               'emile-set-cmdline.c',
                               dependencies: tools_deps,
                               c_args: tools_cargs,
                               install : true,
                               install_dir: tools_installdir)

emile_first_tune = executable('emile-first-tune',
                              'emile-first-tune.c',
                              dependencies: tools_deps,
                              c_args: tools_cargs,
                              install : true,
                              install_dir: tools_installdir)

emile_install = executable('emile-install',
                           'emile-install.c',
                           dependencies: tools_deps,
                           c_args: tools_cargs,
                           install : true,
                           install_dir: tools_installdir)

emile_set_output = executable('emile-set-output',
                              'emile-set-output.c',
                              dependencies: tools_deps,
                              c_args: tools_cargs,
                              install : true,
                              install_dir: tools_installdir)

emile = executable('emile',
                   ['emile.c', 'emile_scanbus.c' ],
                   dependencies: tools_deps,
                   c_args: tools_cargs,
                   install : true,
                   install_dir: tools_installdir)

emile_map_set = executable('emile-map-set',
                           ['emile-map-set.c', 'emile_scanbus.c' ],
                           dependencies: tools_deps,
                           c_args: tools_cargs,
                           install : true,
                           install_dir: tools_installdir)



subdir('iso9660')
subdir('ext2')

#minigzip = executable('minigzip',
#                      ['minigzip.c', 'gzio.c'],
#                      dependencies: tools_deps,
#                      c_args: tools_cargs)

#read_vmlinuz = executable('read_vmlinuz',
#                          'read_vmlinuz.c',
#                          dependencies: tools_deps,
#                          c_args: tools_cargs,
#                          install : true,
#                          install_dir: tools_installdir)



emile_mktable = executable('emile-mktable',
                           'emile-mktable.c',
                           dependencies: tools_deps,
                           c_args: tools_cargs,
                           install : true,
                           install_dir: tools_installdir)

emile_conf = executable('emile-conf',
                        'emile-conf.c',
                        dependencies: tools_deps,
                        c_args: tools_cargs,
                        install : true,
                        install_dir: tools_installdir)
                        
if meson.is_cross_build()
#    tools_native_deps = [ libemile_native_dep,
#                          libcontainer_native_dep,
#                          libstream_native_dep,
#                          libconfig_native_dep,
#                          libmap_native_dep,
#                          libgzip_native_dep,
#                          libiso9660_native_dep ]
#
#    emile_install_native = executable('emile-install-native',
#                            'emile-install.c',
#                            dependencies: tools_native_deps,
#                            c_args: tools_cargs,
#                            native: true)
endif
