libscsi_srcs = [ 'scsi_command.c',
                 'scsi_INQUIRY.c',
                 'scsi_READ.c',
                 'scsi_open.c',
                 'scsi_READ_CAPACITY.c',
                 'scsi_TEST_UNIT_READY.c',
                 'scsi_INQUIRY.c',
                 'scsi_REQUEST_SENSE.c' ]
                 
libscsi_inc = include_directories('include')
libscsi_incs = [ libscsi_inc, libstream_inc ]

libscsi_deps = [ libmacos_dep ]
if bootloader
    libscsi_deps += picolibc_dep
endif

libscsi = static_library('libscsi', libscsi_srcs,
                         include_directories: libscsi_incs,
                         dependencies: libscsi_deps,
                         pic: not bootloader)

libscsi_dep = declare_dependency(link_with:
                                 libscsi,
                                 include_directories: libscsi_inc)
