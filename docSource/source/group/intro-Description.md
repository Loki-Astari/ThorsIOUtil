---
layout: plain
generate: false
---
This utility is designed to mimic the string format arguments used by the C function `printf()`. A `Format` object takes a "format string" that specify a printable string with *conversion specifications* introduced by the `'%'` character. For each *conversion specifications* there must also be a matching argument of the correct type.

If there are not enough arguments or they are the wrong type this is a runtime error as the format string is parsed at runtime during the construction of the `Format` object.

When the format object is passed to a `std::iostream` using the serialization operator `operator<<` all the arguments are serialized to the stream according to the *conversion specifications*.


