# StreamOverlay
This project will be creating an open source stream overlay program that will satisfy the following conditions:

1. Multi-platform code using either: multi-platform libraries, or separate c/cpp files.
2. Uses an interface system, similar to Microsoft’s COM standard, to implement OOP classes in a C compatible fashion for wider support.
3. Minimal JavaScript interpreter, will be used to enable custom script functionality.
4. Uses libraries wrapped in mentioned interface system, we will attempt to compile or runtime link these libraries into the main program whenever its applicable.

## Minimum Viable Product (MVP):
The minimum viable product for this project will need to include a few things:

1. The ability to capture the audio and visuals from a certain window and/or monitor.
2. The ability to overlay images onto the final image frame.
3. The ability to stream to multiple destinations, including networked streams such as Twitch or YouTube; and must be able to support rendering to a file.
4. The ability to do some audio mixing, at least volume control.
5. A simple yet cross-platform UI design that can be easily implemented into any OS, may use a library for this but should aim for simplicity.

## Current Tasks:
    [ ]  Setup Environment
    [ ]  Basic Project Layout + Makefile
    [ ]  Basic Interface System