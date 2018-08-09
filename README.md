# ezNet
Small, modern C++ library for networking (sockets, serialization,...)

###This library is still in development.

I was working on some projects where all that stuff was written
and I thought sharing it might be useful for somebody out there wrestling with
native C sockets.

###!!!ezNet is currently only compatible with Windows!!!

## What ezNet offers:

1. Object oriented socket programming.
2. Object oriented and polymorphic stream concept, that allows you to read/write binary data from/to different kinds
of storages (MemoryStream - memory, NetworkStream - network, sockets).
3. Serialization/deserialization of primitive data types to/from streams.
4. Compressing/decompressing data streams.
5. The ability for the user to add further functionality to the polymorphic structure.

## Notes

You will probably notice, that I often used debug asserts to ensure detection of all errors.
Feel free to remove them, if they bother you.
