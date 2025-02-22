libui_srcs = [ 'window.c',
               'progressbar.c',
               'scrolllist.c',
               'edit.c' ]
libui_inc = include_directories('include')
libui = static_library('libui', libui_srcs, include_directories: libui_inc)
libui_dep = declare_dependency(link_with: libui, include_directories: libui_inc)
