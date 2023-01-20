# cxx-components

This is a number of CXX components for ESP-IDF which bridge C-based SDK
APIs to have an easier CXX interface.

### CXXFreeRTOS
Adds RAII-friendly CXX APIs for FreeRTOS. For basic primitives use
C++11 headers.

The name "CXXFreeRTOS" is ugly, but due to a bug in the ESP-IDF toolchain,
I can't use "FreeRTOS" due to a conflict. The namespace is still
`::FreeRTOS`.

### WiFi
A basic component to initialize WiFi and support WiFi provisioning. 

### Remote

This is a bridge for the RMT module. It exposes a `Remote::Channel` class
which provides an RAII and easy-to-use way to use the RMT module. I've added
a few subclasses which already implement the interfaces for various remotes.

### homekit

The HomeKit bridge is pretty straightforward to use, however it does
require `esp-homekit-sdk` as an `EXTRA_COMPONENT`. One day I will figure
out how to make this a subdependency of these components, but for now,
clone in separately.

### qrcode

Wrapper for some qrcode library I found online along. Additionally, I've added
parts to spit out a QR code to the serial monitor.

## License

This code has no license. Feel free to leave an issue if you're using this
code in a place where there are licensing concerns.
