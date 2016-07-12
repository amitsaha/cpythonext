Building the extension for Python 2
===================================

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

Building the extension for Python 3
===================================

TODO

References
==========

- http://dan.iel.fm/posts/python-c-extensions/
