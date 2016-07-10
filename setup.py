from distutils.core import setup, Extension
#import numpy.distutils.misc_util

setup(
    ext_modules=[Extension("_square", ["_square.c", "square.c"])],
    #include_dirs=numpy.distutils.misc_util.get_numpy_include_dirs(),
)
