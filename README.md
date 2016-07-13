## Python 2


### Building and using

First, we will have to install the dependencies we need to compile our C extension. On Fedora:

```
$sudo dnf -y install gcc python2 python2-devel python2-setuptools redhat-rpm-config
```

Now, we can build our extension:

```
$ python setup.py build_ext --inplace
running build_ext
building '_square' extension
creating build
creating build/temp.linux-x86_64-2.7
gcc -pthread -fno-strict-aliasing -O2 -g -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -m64 -mtune=generic -D_GNU_SOURCE -fPIC -fwrapv -DNDEBUG -O2 -g -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -m64 -mtune=generic -D_GNU_SOURCE -fPIC -fwrapv -fPIC -I/usr/include/python2.7 -c _square.c -o build/temp.linux-x86_64-2.7/_square.o
gcc -pthread -fno-strict-aliasing -O2 -g -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -m64 -mtune=generic -D_GNU_SOURCE -fPIC -fwrapv -DNDEBUG -O2 -g -pipe -Wall -Werror=format-security -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector-strong --param=ssp-buffer-size=4 -grecord-gcc-switches -specs=/usr/lib/rpm/redhat/redhat-hardened-cc1 -m64 -mtune=generic -D_GNU_SOURCE -fPIC -fwrapv -fPIC -I/usr/include/python2.7 -c square.c -o build/temp.linux-x86_64-2.7/square.o
gcc -pthread -shared -Wl,-z,relro -specs=/usr/lib/rpm/redhat/redhat-hardened-ld build/temp.linux-x86_64-2.7/_square.o build/temp.linux-x86_64-2.7/square.o -L/usr/lib64 -lpython2.7 -o /root/cpythonext/_square.so
```

Now, we will see a file ``_square.so`` in the current directory:

```
$ file _square.so 
_square.so: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, BuildID[sha1]=0caaefbdd159fc33c36ee8ab58d705ae7f2c952d, not stripped

```

We can import this module directly:

```
>>> import _square
>>> dir(_square)
['__doc__', '__file__', '__name__', '__package__', 'square']
>>> _square.__doc__
'This module exports a C function square().'
>>> _square.__name__
'_square'
>>> _square.square(1)
1
>>> _square.square(1.2)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: integer argument expected, got float
```

### Packaging and distribution

Build a wheel on Fedora 24, import `setup()` from `setuptools`:

```
$ python setup.py bdist_rpm
```

The wheel in `dist` will be installable, and you can do a `pip install` and it will copy the `.so` file which you can
then import.

However, if you now try to install this wheel on Ubuntu 14.04, you will get:

```
$ pip install cpython_extension_demo-0.0.0-cp27-cp27mu-linux_x86_64.whl 
cpython_extension_demo-0.0.0-cp27-cp27mu-linux_x86_64.whl is not a supported wheel on this platform.
Storing debug log for failure in /root/.pip/pip.log
root@53b45d51afba:/code# cat /root/.pip/pip.log 
cpython_extension_demo-0.0.0-cp27-cp27mu-linux_x86_64.whl is not a supported wheel on this platform.
Exception information:
Traceback (most recent call last):
  File "/usr/lib/python2.7/dist-packages/pip/basecommand.py", line 122, in main
    status = self.run(options, args)
  File "/usr/lib/python2.7/dist-packages/pip/commands/install.py", line 257, in run
    InstallRequirement.from_line(name, None))
  File "/usr/lib/python2.7/dist-packages/pip/req.py", line 168, in from_line
    raise UnsupportedWheel("%s is not a supported wheel on this platform." % wheel.filename)
UnsupportedWheel: cpython_extension_demo-0.0.0-cp27-cp27mu-linux_x86_64.whl is not a supported wheel on this platform.

```

### Building manylinux1 wheels

Instructions from https://github.com/pypa/python-manylinux-demo

```
$ docker pull quay.io/pypa/manylinux1_x86_64  
$ docker run --rm -v `pwd`:/workspace:z quay.io/pypa/manylinux1_x86_64  /workspace/build-manylinux1-wheels.sh
```

We will have `manylinux1` wheels in `wheelhouse`. On Fedora 24 (our host OS):

```
$ pip install --no-index --find-links file:///`pwd`/wheelhouse cpython_extension_demo --verbose
Ignoring indexes: https://pypi.python.org/simple
Collecting cpython_extension_demo
  0 location(s) to search for versions of cpython-extension-demo:
  Skipping link file:////home/asaha/work/amitsaha/cpythonextension-demo/wheelhouse (from -f); not a file
  Skipping link file:///home/asaha/work/amitsaha/cpythonextension-demo/wheelhouse/cpython_extension_demo-0.0.0-cp27-cp27m-manylinux1_x86_64.whl; it is not compatible with this Python
  Found link file:///home/asaha/work/amitsaha/cpythonextension-demo/wheelhouse/cpython_extension_demo-0.0.0-cp27-cp27mu-manylinux1_x86_64.whl, version: 0.0.0
  Skipping link file:///home/asaha/work/amitsaha/cpythonextension-demo/wheelhouse/cpython_extension_demo-0.0.0-cp26-cp26mu-manylinux1_x86_64.whl; it is not compatible with this Python
  Skipping link file:///home/asaha/work/amitsaha/cpythonextension-demo/wheelhouse/cpython_extension_demo-0.0.0-cp33-cp33m-manylinux1_x86_64.whl; it is not compatible with this Python
  Skipping link file:///home/asaha/work/amitsaha/cpythonextension-demo/wheelhouse/cpython_extension_demo-0.0.0-cp34-cp34m-manylinux1_x86_64.whl; it is not compatible with this Python
  Skipping link file:///home/asaha/work/amitsaha/cpythonextension-demo/wheelhouse/cpython_extension_demo-0.0.0-cp26-cp26m-manylinux1_x86_64.whl; it is not compatible with this Python
  Skipping link file:///home/asaha/work/amitsaha/cpythonextension-demo/wheelhouse/cpython_extension_demo-0.0.0-cp35-cp35m-manylinux1_x86_64.whl; it is not compatible with this Python
  Local files found: /home/asaha/work/amitsaha/cpythonextension-demo/wheelhouse/cpython_extension_demo-0.0.0-cp27-cp27mu-manylinux1_x86_64.whl
  Using version 0.0.0 (newest of versions: 0.0.0)
Installing collected packages: cpython-extension-demo

Successfully installed cpython-extension-demo-0.0.0
Cleaning up...
```


Now, in Ubuntu 14.04:

```
$ # ensure pip >= 8.1

$ /usr/local/bin/pip install --no-index --find-links file:///code/wheelhouse cpython_extension_demo --verbose
Ignoring indexes: https://pypi.python.org/simple
Collecting cpython_extension_demo
  0 location(s) to search for versions of cpython-extension-demo:
  Skipping link file:///code/wheelhouse (from -f); not a file
  Skipping link file:///code/wheelhouse/cpython_extension_demo-0.0.0-cp27-cp27m-manylinux1_x86_64.whl; it is not compatible with this Python
  Found link file:///code/wheelhouse/cpython_extension_demo-0.0.0-cp27-cp27mu-manylinux1_x86_64.whl, version: 0.0.0
  Skipping link file:///code/wheelhouse/cpython_extension_demo-0.0.0-cp26-cp26mu-manylinux1_x86_64.whl; it is not compatible with this Python
  Skipping link file:///code/wheelhouse/cpython_extension_demo-0.0.0-cp33-cp33m-manylinux1_x86_64.whl; it is not compatible with this Python
  Skipping link file:///code/wheelhouse/cpython_extension_demo-0.0.0-cp34-cp34m-manylinux1_x86_64.whl; it is not compatible with this Python
  Skipping link file:///code/wheelhouse/cpython_extension_demo-0.0.0-cp26-cp26m-manylinux1_x86_64.whl; it is not compatible with this Python
  Skipping link file:///code/wheelhouse/cpython_extension_demo-0.0.0-cp35-cp35m-manylinux1_x86_64.whl; it is not compatible with this Python
  Local files found: /code/wheelhouse/cpython_extension_demo-0.0.0-cp27-cp27mu-manylinux1_x86_64.whl
  Using version 0.0.0 (newest of versions: 0.0.0)
Installing collected packages: cpython-extension-demo

Successfully installed cpython-extension-demo-0.0.0
Cleaning up...

```




## Python 3


### Building and using

TODO

### Packaging and distribution

TODO

References
==========

- http://dan.iel.fm/posts/python-c-extensions/
