libmacos_proj = subproject('libmacos')
libmacos_dep = libmacos_proj.get_variable('libmacos_dep')
libconfig_proj = subproject('libconfig')
libconfig_dep = libconfig_proj.get_variable('libconfig_dep')
libstream_proj = subproject('libstream')
libstream_dep = libstream_proj.get_variable('libstream_dep')

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
                       'keyboard.c',
                       'reloc.c' ]
                
second_src_linux = [ 'bootinfo.c' ]

second_cargs = ['-DUSE_CLI', '-DBANK_DUMP']
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

second_linkargs = [ ]
# !LINK! with PIE to make sure that relocation info for function pointers etc is present
second_linkargs += '-Wl,-pie'

second_linkargs += '-Wl,--gc-sections'

second_linkwith = [ ]
# picolibc_semihosting

second_linkargs += [ '-Wl,--no-dynamic-linker', '-Wl,-z', '-Wl,noexecstack', '-nostdlib', '-lgcc' ] + second_lto_args
second_linkargs += [ '-L' + meson.source_root(), '-T' + '@0@'.format(second_linkerscript[0])]
second_linkargs += [ '-Wl,-z', 'notext' ]


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

# picolibc_dep, 
second_deps = [ picolibc_dep, libmacos_dep, libui_dep, libconfig_dep, libunix_dep ]

second_objcopy_wantedsections = [ '-j.text','-j.data','-j.rodata','-j.got', '-j.rela.dyn', '-j.bss' ]

# Tell objcopy to keep the BSS and set it as zero, this will make the binary bigger but we
# will get the BSS alloc'd and zero'd for free by first
second_objcopy_keepbss = [ '--set-section-flags', '.bss=alloc,load,contents' ] 

second_objcopy = [objcopy, '-Obinary',  ] + second_objcopy_wantedsections + second_objcopy_keepbss + ['@INPUT@', '@OUTPUT@']

second_relocate_rela = [relocate_rela, '@OUTPUT@', '@INPUT@']

second_floppy = executable('second_floppy_elf', second_srcs,
                    link_args: second_linkargs,
                    link_with: second_linkwith,
                    dependencies: second_deps + libstream_dep,
                    c_args: second_cargs)

second_floppy_bin = custom_target('second_floppy_binary',
                           input: second_floppy,
                           output: 'second_floppy',
                           command: second_objcopy,
                           install: true,
                           install_dir: '/boot/emile/')

second_scsi = executable('second_scsi_elf', second_srcs,
                    link_args: second_linkargs,
                     link_with: second_linkwith,
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
                     link_with: second_linkwith,
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
                    link_args: second_linkargs,
                    link_with: second_linkwith,
                    pie: false)
                    
appledriver_bin = custom_target('appledriver_binary',
                           input: appledriver,
                           output: 'appledriver',
                           command: second_objcopy,
                           install: true,
                           install_dir: '/boot/emile/')
