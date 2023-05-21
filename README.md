# cxx-components

This is a number of CXX components for ESP-IDF which bridge C-based SDK
APIs to have an easier CXX interface.

### i2c

This is a ergonomic C++ library for the ESP32's I2C interface. Slave support
exists, but is very limited by the ESP32's hardware.

To interact with I2C devices, construct a global instance of an `i2c::Master`.
The master object can be used to perform I2C read/writes. It is recommended
to construct `i2c::RegEntry` objects for code clarity.

### spi

This provides SPI master and slave capabilities.

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

A C++ library for making HomeKit accessories. If you use this, there are
configuration parameters you might need to set to avoid getting build errors.
Specifically, NimBLE should be enabled and some ESP devices may need other
changes.

### qrcode

Wrapper for some qrcode library I found online along. Additionally, I've added
parts to spit out a QR code to the serial monitor.

## License

This code has no license. Feel free to leave an issue if you're using this
code in a place where there are licensing concerns.
