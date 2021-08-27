#include "logger.h"
#include "../../drivers/frame_buffer/frame_buffer.h"
#include "../../drivers/serial_port/serial_port.h"

void print_screen(s8int *buffer, u32int len) { fb_write(buffer, len); }

void print_serial(s8int *buffer, u32int len) {
  serial_write(SERIAL_COM1_BASE, buffer, len);
}
