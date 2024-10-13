#include <iostream>
#include <libusb-1.0/libusb.h>

int main() {
    libusb_context *ctx = nullptr;
    libusb_device_handle *dev_handle = nullptr;
    int r;

    // Initialize the libusb library
    r = libusb_init(&ctx);
    if (r < 0) {
        std::cerr << "Initialization Error: " << libusb_error_name(r) << std::endl;
        return 1;
    }

    // Open USB device with VID = 0x1234 and PID = 0x5678
    dev_handle = libusb_open_device_with_vid_pid(ctx, 0x1234, 0x5678);
    if (!dev_handle) {
        std::cerr << "Cannot open device" << std::endl;
        libusb_exit(ctx);
        return 1;
    }
    std::cout << "Device Opened Successfully!" << std::endl;

    // Claim the interface (usually interface 0)
    r = libusb_claim_interface(dev_handle, 0);
    if (r < 0) {
        std::cerr << "Cannot Claim Interface: " << libusb_error_name(r) << std::endl;
        libusb_close(dev_handle);
        libusb_exit(ctx);
        return 1;
    }

    // Read data from endpoint 0x81 (adjust endpoint based on your device)
    unsigned char data[4];
    int actual_length;
    r = libusb_bulk_transfer(dev_handle, 0x81, data, sizeof(data), &actual_length, 1000);
    if (r == 0 && actual_length > 0) {
        std::cout << "Data received: ";
        for (int i = 0; i < actual_length; i++) {
            std::cout << std::hex << (int)data[i] << " ";
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Error in receiving data: " << libusb_error_name(r) << std::endl;
    }

    // Write data to endpoint 0x01
    unsigned char send_data[] = {0x01, 0x02, 0x03, 0x04};
    r = libusb_bulk_transfer(dev_handle, 0x01, send_data, sizeof(send_data), &actual_length, 1000);
    if (r == 0) {
        std::cout << "Data sent successfully!" << std::endl;
    } else {
        std::cerr << "Error in sending data: " << libusb_error_name(r) << std::endl;
    }

    // Release the interface and close the device
    libusb_release_interface(dev_handle, 0);
    libusb_close(dev_handle);
    libusb_exit(ctx);

    return 0;
}
