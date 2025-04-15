second_srcs_common = [ 'head.S',
                       'main.c',
                       'console.c',
                       'font_8x16.c',
                       'misc.c',
                       'bank.c',
                       'arch.c',
                       'load.c',
                       'serial.c',
                       'vga.c',
                       'driver.c',
                       'enter_kernel.c',
                       'config.c',
                       'cli.c',
                       'keyboard.c' ]
                
second_src_linux = [ 'bootinfo.c' ]

second_cargs = ['-fpic', '-DUSE_CLI', '-DBANK_DUMP']
second_linkerscript = files('ld.script')

second_lto_args = [ '-Wl,--undefined=start',
		    '-Wl,--undefined=printf',
		    '-Wl,--undefined=puts',
		    '-Wl,--undefined=malloc',
		    '-Wl,--undefined=memset',
		    '-Wl,--undefined=memcpy',
		    '-Wl,--undefined=free',
		    '-Wl,--undefined=strcpy',
		    '-Wl,--undefined=strncpy',
		    '-Wl,--undefined=putchar',
		    '-Wl,--undefined=strcmp',
		    '-Wl,--undefined=strlen',
		    '-Wl,--undefined=sprintf',
		    '-Wl,--undefined=vsprintf',
		    '-Wl,--undefined=strdup', 
		    '-Wl,--undefined=strncmp']
second_linkargs = [ '-no-pie', '-nostdlib', '-fpic', '-lgcc' ] + second_lto_args
second_linkargs += [ '-L' + meson.source_root(), '-T' + '@0@'.format(second_linkerscript[0])]

second_target = get_option('ostype')
if second_target == 'm68k-linux'
    second_srcs_030 = [ 'asm_MMU030.S', 'MMU030.c', 'enter_kernel030.S' ]
    second_srcs_040 = [ 'asm_MMU040.S', 'MMU040.c', 'enter_kernel040.S' ]
    second_srcs_nommu = [ 'enter_kernelnoMMU.S' ]
    second_srcs = [ second_srcs_common,
                  second_src_linux,
                  second_srcs_030,
                  second_srcs_040,
                  second_srcs_nommu ]
    second_cargs += ['-D__LINUX__', '-DARCH_M68K', '-DUSE_MMU030', '-DUSE_MMU040']
endif

second_deps = [libmacos_dep, libui_dep, libconfig_dep, libunix_dep]

second_objcopy = [objcopy, '-Obinary', '-j.text','-j.data','-j.rodata','-j.got','@INPUT@', '@OUTPUT@']

second_floppy = executable('second_floppy_elf', second_srcs,
                    link_args: second_linkargs,
                    dependencies: second_deps + libstream_dep,
                    c_args: second_cargs,
                    pie: false)

second_floppy_bin = custom_target('second_floppy_binary',
                           input: second_floppy,
                           output: 'second_floppy',
                           command: second_objcopy,
                           install: true,
                           install_dir: '/boot/emile/')

second_scsi = executable('second_scsi_elf', second_srcs,
                    link_args: second_linkargs,
                    dependencies: second_deps + libstream_dep,
                    c_args: second_cargs)

second_scsi_bin = custom_target('second_scsi_binary',
                           input: second_scsi,
                           output: 'second_scsi',
                           command: second_objcopy,
                           install: true,
                           install_dir: '/boot/emile/')

second_full = executable('second_full_elf', second_srcs,
                    link_args: second_linkargs,
                    dependencies: second_deps + libstream_dep,
                    c_args: second_cargs)

second_full_bin = custom_target('second_full_binary',
                           input: second_full,
                           output: 'second_full',
                           command: second_objcopy,
                           install: true,
                           install_dir: '/boot/emile/')
                           
appledriver = executable('appledriver_elf',
                    second_srcs,
                    dependencies: second_deps + libstream_dep,
                    c_args: second_cargs + '-DAPPLE_DRIVER',
                    link_args: second_linkargs)
                    
appledriver_bin = custom_target('appledriver_binary',
                           input: appledriver,
                           output: 'appledriver',
                           command: second_objcopy,
                           install: true,
                           install_dir: '/boot/emile/')
