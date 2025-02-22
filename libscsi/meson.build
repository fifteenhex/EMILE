libscsi_srcs = [ 'scsi_read_sector.c',
                 'scsi_command.c',
                 'scsi_INQUIRY.c',
                 'scsi_READ.c',
                 'scsi_open.c',
                 'scsi_close.c',
                 'scsi_READ_CAPACITY.c',
                 'scsi_get_blocksize.c',
                 'scsi_TEST_UNIT_READY.c',
                 'scsi_INQUIRY.c',
                 'scsi_REQUEST_SENSE.c' ]
libscsi_inc = include_directories('include')
libscsi = static_library('libscsi', libscsi_srcs,
                         include_directories:libscsi_inc,
                         dependencies: libmacos_dep)
libscsi_dep = declare_dependency(link_with: libscsi, include_directories: libscsi_inc)
