libcontainer_srcs = [ 'container_close.c',
                      'container_lseek.c',
                      'container_read.c',
                      'container_fstat.c',
                      'container_init.c',
                      'container_mount.c' ]
libcontainer_inc = include_directories('include')

libcontainer_deps = [ ]
if baremetal
    libcontainer_deps += picolibc_dep
endif

libcontainer = static_library('container',
                              libcontainer_srcs,
                              include_directories: [ libcontainer_inc, libstream_inc ],
                              dependencies: libcontainer_deps,
                              pic: not baremetal)
libcontainer_dep = declare_dependency(link_with: libcontainer,
                                      include_directories: libcontainer_inc)

libcontainer_native = static_library('container-native', libcontainer_srcs,
                              include_directories: [libcontainer_inc, libstream_inc],
                              native: true)
libcontainer_native_dep = declare_dependency(link_with: libcontainer_native,
                    include_directories: libcontainer_inc)
