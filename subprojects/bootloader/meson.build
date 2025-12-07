project('emile-baremetal', 'c',
        meson_version: '>= 1.3.2')

picolibc_proj = subproject('picolibc',
                            default_options: [ 'multilib=false',
                                               'freestanding=true',
                                               'picocrt=false',
                                               'single-thread=true',
                                               'initfini-array=false',
                                               'thread-local-storage=false',
                                               'enable-malloc=false',
                                               'semihost=false'])
picolibc_dep = picolibc_proj.get_variable('picolibc_dep')
#picolibc_semihosting = picolibc_proj.get_variable('lib_semihost')

libstream_proj = subproject('libstream')
                                               
objcopy = find_program('objcopy')

subdir('libui')
subdir('libunix')
subdir('first')
subdir('relocate_rela')
subdir('second')
