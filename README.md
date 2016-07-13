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



## Python 3


### Building and using

TODO

### Packaging and distribution

TODO

References
==========

- http://dan.iel.fm/posts/python-c-extensions/
