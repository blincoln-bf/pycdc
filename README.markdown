# Custom fork of Decompyle++ for use in batch scripts

This project is a customized fork of [Decompyle++](https://github.com/zrax/pycdc). It works identically to the original, except for the following changes:

* This fork supports recursion depth limiting during both loading and rendering data. This prevents it from entering an infinite loop and eventually exhausting available memory.
* This fork only warns on an invalid Python version, but still tries to decompile it.

By default, the modified Decompyle++ limits recursion to a depth of 100, which should hopefully be more than enough for most real code. You can specify a different value by using the `-m <DEPTH>` command-line option, e.g. `-m 10` or `-m 1000`.

See the original project for more complete documentation of the overall functionality.

## Building Decompyle++

Quick build instructions for Linux, assuming your are in the `pycdc` directory:

```
% mkdir ../build

% cmake -S . -B ../build

% cd ../build

% make
```

Original build instructions:

* Generate a project or makefile with [CMake](http://www.cmake.org) (See CMake's documentation for details)
  * The following options can be passed to CMake to control debug features:

    | Option | Description |
    | --- | --- |
    | `-DCMAKE_BUILD_TYPE=Debug` | Produce debugging symbols |
    | `-DENABLE_BLOCK_DEBUG=ON` | Enable block debugging output |
    | `-DENABLE_STACK_DEBUG=ON` | Enable stack debugging output |

* Build the generated project or makefile
  * For projects (e.g. MSVC), open the generated project file and build it
  * For makefiles, just run `make`
  * To run tests (on \*nix or MSYS), run `make check`

## Usage
**To run pycdas**, the PYC Disassembler:
`./pycdas [PATH TO PYC FILE]`
The byte-code disassembly is printed to stdout.

**To run pycdc**, the PYC Decompiler: 
`./pycdc [PATH TO PYC FILE]`
The decompiled Python source is printed to stdout.
Any errors are printed to stderr.

**Marshalled code objects**:
Both tools support Python marshalled code objects, as output from `marshal.dumps(compile(...))`.

To use this feature, specify `-c -v <version>` on the command line - the version must be specified as the objects themselves do not contain version metadata.

## Authors, Licence, Credits
Decompyle++ is the work of Michael Hansen and Darryl Pogue.

Additional contributions from:
* charlietang98
* Kunal Parmar
* Olivier Iffrig
* Zlodiy
* Ben Lincoln (this fork only)

It is released under the terms of the GNU General Public License, version 3;
See LICENSE file for details.
