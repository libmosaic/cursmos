# libcursmos, the Curses wrapper for the Mosaic Asc Art library
# Created by Gil "gilzoide" Barbosa Reis

Help ("""
Welcome to the libcursmos' build script

The default build output is the build/ directory.
This package provide the shared libraries for mosaic and curses wrapper, 
and a cat application (moscat).

You can `scons install` everything in the /usr/{lib,include,bin}/ directories.
For installing only a part of libcursmos (maybe you want only the shared 
libraries), you can `scons install-lib` or `scons install-include` or
`scons install-pkgconfig` or `scons install-bin`.

Everything can be uninstalled running `scons uninstall`.
""")

if not GetOption ('help'):
    env = Environment (
        CCFLAGS = '-Wall -pipe -O2',
        CPPPATH = '#include',
        CC = 'gcc',
        LIBS = ['panel', 'curses'],
        LIBPATH = ['/usr/lib', '/usr/local/lib'],
    )
    env.Decider ('MD5-timestamp')

    # if user pass debug=0, don't add -g flag for the compiler
    debug = ARGUMENTS.get ('debug', 1)
    if int (debug):
        env.Append (CCFLAGS = ' -g')

    # build mosaic in the 'build' directory, without duplicating
    VariantDir ('build', 'src', duplicate = 0)
    SConscript ('build/SConscript', exports = 'env')

    # headers is defined in the SConscript file globally
    env.Command ("uninstall", None, Delete (FindInstalledFiles ()))
