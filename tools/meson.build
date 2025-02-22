tools_installdir = 'sbin'
tools_deps = [ libemile_dep,
               libcontainer_dep,
               libstream_dep,
               libmap_dep,
               libconfig_dep,
               libiso9660_dep,
               libext2_dep,
               libgzip_dep ]

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
                   ['emile.c', 'emile_scanbus.c', 'device.c'],
                   dependencies: tools_deps,
                   c_args: tools_cargs,
                   install : true,
                   install_dir: tools_installdir)

emile_map_set = executable('emile-map-set',
                           ['emile-map-set.c', 'emile_scanbus.c', 'device.c'],
                           dependencies: tools_deps,
                           c_args: tools_cargs,
                           install : true,
                           install_dir: tools_installdir)

iso9660_ls = executable('iso9660_ls',
                        ['iso9660_ls.c', 'device.c'],
                        dependencies: tools_deps,
                        c_args: tools_cargs,
                        install : true,
                        install_dir : tools_installdir)

iso9660_cat = executable('iso9660_cat',
                         ['iso9660_cat.c', 'device.c'],
                         dependencies: tools_deps,
                         c_args: tools_cargs,
                         install : true,
                         install_dir: tools_installdir)

#minigzip = executable('minigzip',
#                      ['minigzip.c', 'gzio.c'],
#                      dependencies: tools_deps,
#                      c_args: tools_cargs)

read_vmlinuz = executable('read_vmlinuz',
                          'read_vmlinuz.c',
                          dependencies: tools_deps,
                          c_args: tools_cargs,
                          install : true,
                          install_dir: tools_installdir)

emile_mkisofs = executable('emile-mkisofs',
                           ['emile-mkisofs.c', 'device.c'],
                           dependencies: tools_deps,
                           c_args: tools_cargs,
                           install : true,
                           install_dir: tools_installdir)

ext2_ls = executable('ext2_ls',
                     ['ext2_ls.c', 'device.c'],
                     dependencies: tools_deps,
                     c_args: tools_cargs,
                     install : true,
                     install_dir: tools_installdir)

ext2_cat = executable('ext2_cat', ['ext2_cat.c', 'device.c'],
                      dependencies: tools_deps,
                      c_args: tools_cargs,
                      install : true,
                      install_dir: tools_installdir)

emile_mktable = executable('emile-mktable',
                           'emile-mktable.c',
                           dependencies: tools_deps,
                           c_args: tools_cargs,
                           install : true,
                           install_dir: tools_installdir)

emile_conf = executable('emile-conf',
                        ['emile-conf.c', 'device.c'],
                        dependencies: tools_deps,
                        c_args: tools_cargs,
                        install : true,
                        install_dir: tools_installdir)
                        
if meson.is_cross_build()
    tools_native_deps = [ libemile_native_dep,
                          libcontainer_native_dep,
                          libstream_native_dep,
                          libconfig_native_dep,
                          libmap_native_dep,
                          libgzip_native_dep,
                          libiso9660_native_dep ]

    emile_install_native = executable('emile-install-native',
                            'emile-install.c',
                            dependencies: tools_native_deps,
                            c_args: tools_cargs,
                            native: true)

    emile_mkisofs_native = executable('emile-mkisofs-native',
                            ['emile-mkisofs.c', 'device.c'],
                            dependencies: tools_native_deps,
                            c_args: tools_cargs,
                            native: true)
endif
