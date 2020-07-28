#include <usb_names.h>

#define MANUFACTURER_NAME          \
  {                          \
    'N', 'E', 'T', '8', 'F', 'L', 'O', 'Z' \
  }
#define MANUFACTURER_NAME_LEN 8

#define PRODUCT_NAME                                                            \
  {                                                                       \
    'S', 'T', 'O', 'M', 'P', 'B', 'O', 'X' \
  }
#define PRODUCT_NAME_LEN 8

#define SERIAL_NUMBER                                            \
  {                                                        \
    '420-69' \
  }
#define SERIAL_NUMBER_LEN 1

struct usb_string_descriptor_struct usb_string_manufacturer_name = {
  2 + MANUFACTURER_NAME_LEN * 2,
  3,
  MANUFACTURER_NAME};

struct usb_string_descriptor_struct usb_string_product_name = {
  2 + PRODUCT_NAME_LEN * 2,
  3,
  PRODUCT_NAME};

struct usb_string_descriptor_struct usb_string_serial_number = {
  2 + SERIAL_NUMBER_LEN * 2,
  3,
  SERIAL_NUMBER};
