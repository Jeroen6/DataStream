# DataStream
Binary data stream (de)serializer

While working on embedded systems communications on PC based systems C++ often got me bitshifting bytes to recreate the unsigned integer the data once was.
Now, C++ is supposed to look elegant and clean. And all these bitshifts look messy.
I therefore made this. It will be expanded with a C variant for the other side of the link.

Please point an instance of DataStream to an array of bytes, and use the overloaded operators with the type you would want to write << and read >>.
The endian is configurable. And it will assert when the array is exceeded.