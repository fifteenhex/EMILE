first_srcs = [ 'first.S' ]
first_linkargs = [ '-nostdlib', '-ffreestanding' ]

first_objcopy_cmd = [objcopy, '-Obinary', '-j.text', '@INPUT@', '@OUTPUT@']
first_floppy = executable('first_floppy_elf',
                          first_srcs,
                          link_args: first_linkargs,
                          c_args: '-Wa,--defsym,FLOPPY_SUPPORT=1')
first_floppy_bin = custom_target('first_floppy_binary',
                           input: first_floppy,
                           output: 'first_floppy',
                           command: first_objcopy_cmd,
                           install: true,
                           install_dir: '/boot/emile/')

first_scsi = executable('first_scsi_elf',
                        first_srcs,
                        link_args: first_linkargs,
                        c_args: '-Wa,--defsym,SCSI_SUPPORT=1')
first_scsi_bin = custom_target('first_scsi_binary',
                           input: first_scsi,
                           output: 'first_scsi',
                           command: first_objcopy_cmd,
                           install: true,
                           install_dir: '/boot/emile/')
