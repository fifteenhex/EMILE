project('libmacos', 'c')

libmacos_srcs = [ 'CloseDriver.c',
                  'OpenDriver.c',
                  'SerGetBuf.c',
                  'GetDCtlEntry.c' ]

libmacos_inc = include_directories('include')
libmacos = static_library('macos',
                          libmacos_srcs,
                          include_directories: libmacos_inc,
                          pic: false)
libmacos_dep = declare_dependency(link_with: libmacos, include_directories: libmacos_inc)
