1._ Series
==========

*TODO*

0._ Series
==========

[0.3 (future)](https://bitbucket.org/tgockel/json-voorhees/issues?version=0.3)
------------------------------------------------------------------------------

The main focus of this release is access and modification of the low-level parsing and encoding system.

[0.2 (future)](https://bitbucket.org/tgockel/json-voorhees/issues?version=0.2)
------------------------------------------------------------------------------

The main focus of this release is full support for parsing and emitting Unicode strings.
With `0.2.0`, the parsing API should be fairly close to the `1.0` version.

[0.1](https://bitbucket.org/tgockel/json-voorhees/issues?version=0.1)
---------------------------------------------------------------------

The original prototype, which allows for parsing input to the JSON AST, manipulation of said AST and eventually encoding
 it as a string.

 - [0.1.1](https://bitbucket.org/tgockel/json-voorhees/src/3446343a4b591d7e1ecf0d6499450829ae5809c6/?at=v0.1.1)
   2014 April 30
    - Minor parsing performance improvements by batching the string read for `parse_number`
    - Move to GNU Make as the build system
 - [0.1.0](https://bitbucket.org/tgockel/json-voorhees/src/97e5e8efa76f4eacc4cf2a9e25351e6aad01bf4d/?at=v0.1.0)
   2014 April 24