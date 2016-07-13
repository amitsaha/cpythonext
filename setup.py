#from distutils.core import setup, Extension
from setuptools import setup, Extension
#import numpy.distutils.misc_util

setup(
    name="cpython-extension-demo",
    ext_modules=[Extension("_square", ["_square.c", "square.c"])],
    #include_dirs=numpy.distutils.misc_util.get_numpy_include_dirs(),
)
