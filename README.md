# cxx-components

This is a number of CXX components for ESP-IDF which bridge C-based SDK
APIs to have an easier CXX interface.

### Remote

This is a bridge for the RMT module. It exposes a `Remote::Channel` class
which provides an RAII and easy-to-use way to use the RMT module. I've added
a few subclasses which already implement the interfaces for various remotes.

### homekit

The HomeKit bridge is pretty straightforward to use, however it does
require `esp-homekit-sdk` as an `EXTRA_COMPONENT`. One day I will figure
out how to make this a subdependency of these components, but for now,
clone in seperately.

### qrcode

Wrapper for some qrcode library I found online along. Additionally, I've added
parts to spit out a QR code to the serial monitor.

### init_wifi

A basic component to initialize WiFi and support WiFi provisioning. I'll probably
replace this with a better all-powerful 'Wifi' module later.

## License

This code has no license. Feel free to leave an issue if you're using this
code in a place where there are licensing concerns.
