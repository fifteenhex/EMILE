project('EMILE', 'c',
        meson_version: '>= 1.3.2',
        default_options: ['c_std=gnu18'])

# Set the global version
add_global_arguments('-DVERSION="xxx"', language: 'c')

# Are we building the bootloader or the userspace tools?
bootloader = get_option('bootloader')

# Make some warnings into errors
cc = meson.get_compiler('c')
warning_cflags = cc.get_supported_arguments([
    '-Wall',
    '-Werror=incompatible-pointer-types',
    '-Werror=implicit-function-declaration',
])

add_global_arguments(warning_cflags, language: 'c')

# Supress some warnings that need code fixes
add_global_arguments('-Wno-multichar', language: 'c')
add_global_arguments('-Wno-address-of-packed-member', language: 'c')

if bootloader
    # Set some global cflags, these cannot be set in the baremetal subproject
    # as I'd prefer

    # If the toolchain is configured with musl picolibc is borked so..
    # 1. remove musl's (and everything else..) headers from the search path
    add_global_arguments('-nostdinc', language: 'c')
    # 2. work out where the compiler headers are..    
    compiler_install = run_command(cc.cmd_array() + ['-print-search-dirs'], check : true).stdout().split('\n')[0].split(' ')[1]
    compiler_include = compiler_install / 'include'

    add_global_arguments('-I' + compiler_include, language: 'c')

    #libext2 and libiso9660 use linux headers so add the sysroot back
    add_global_arguments('-I$SYSROOT/usr/include/', language: 'c')

    add_global_arguments('-ffreestanding', language: 'c')

    # Force pie
    add_global_arguments('-fpie', language: 'c')
    
    # reduce the got, get rid of the plt
    add_global_arguments('-fno-pic', language: 'c')
    add_global_arguments('-fno-plt', language: 'c')
    
    # This removes a jmp slot relocation
    add_global_arguments('-fvisibility=hidden', language: 'c')

    # For now disable the stack protector globally so the second stage can link
    add_global_arguments('-fno-stack-protector', language: 'c')
    
    add_global_arguments('--param=min-pagesize=0', language: 'c')

    # Tell picolibc we have our own malloc
    add_global_arguments('-DMALLOC_PROVIDED', language: 'c')
    
    bootloader_proj = subproject('bootloader')
else
    tools_proj = subproject('tools')
endif
