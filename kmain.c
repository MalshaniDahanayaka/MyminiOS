#include "segmentation/gdt.h"
#include "drivers/serial_port/serial_port.h"
#include "drivers/frame_buffer/frame_buffer.h"

/* Function to initialize */
void init() {
  /* Initialize segment descriptor tables */
  init_gdt();

  /* Initialize serial port */
  serial_configure(SERIAL_COM1_BASE, Baud_115200);
}

/* Kernel Main */
int kmain() {
  init();
  char buffer[50] = "Welcome to MyminiOS...This works!!!!!!!\n";
  fb_write(buffer, 50);
  serial_write(SERIAL_COM1_BASE, buffer, 50);
  return 0;
}
