iso9660_ls = executable('iso9660_ls',
                        'iso9660_ls.c',
                        dependencies: tools_deps,
                        c_args: tools_cargs,
                        install : true,
                        install_dir : tools_installdir)

iso9660_cat = executable('iso9660_cat',
                         'iso9660_cat.c',
                         dependencies: tools_deps,
                         link_with: device_lib,
                         c_args: tools_cargs,
                         install : true,
                         install_dir: tools_installdir)
                         
emile_mkisofs = executable('emile-mkisofs',
                           'emile-mkisofs.c',
                           dependencies: tools_deps,
                           c_args: tools_cargs,
                           install : true,
                           install_dir: tools_installdir)
