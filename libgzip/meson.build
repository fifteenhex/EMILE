libgzip_cargs = [ '-DFATFREE',
                  '-DNOBYFOUR',
                  '-DBUILDFIXED',
                  '-DNO_GZCOMPRESS',
                  '-DDYNAMIC_CRC_TABLE' ]

libgzip_srcs = [ 'inflate.c',
                 'adler32.c',
                 'inftrees.c',
                 'zutil.c',
                 'inffast.c',
                 'crc32.c' ]

libgzip_inc = include_directories('include')

libgzip = static_library('gzip', libgzip_srcs,
                         include_directories: libgzip_inc,
                         c_args: libgzip_cargs)
libgzip_dep = declare_dependency(link_with: libgzip,
                                 include_directories: libgzip_inc)

# Native
if meson.is_cross_build()
    libgzip_native = static_library('gzip-native', libgzip_srcs,
                            include_directories: libgzip_inc,
                            c_args : libgzip_cargs,
                            native: true)
    libgzip_native_dep = declare_dependency(link_with: libgzip_native,
                                            include_directories: libgzip_inc)
endif
