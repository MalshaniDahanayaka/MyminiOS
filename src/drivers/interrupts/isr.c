#include "isr.h"
#include "../../utils/common/helpers.h"
#include "../io/io.h"
#include "../../utils/logger/logger.h"

isr_t interrupt_handlers[256];


void register_interrupt_handler(u8int n, isr_t handler) {
  interrupt_handlers[n] = handler;
}


void interrupt_handler(registers_t regs) {
  
  if (regs.stack_contents.int_no >= 40) {
    outb(0xA0, 0x20);
  }
 
  if (regs.stack_contents.int_no >= 32) {
    outb(0x20, 0x20);
  }

  s8int buffer[36] = "Hello kmOS , recieved intterupt..!\n";
  print_serial(buffer, 36);
  print_screen(buffer, 36);

 
  s8int buffer2[4] = " ";
  integer_to_string(buffer2, regs.stack_contents.int_no);
  buffer2[3] = '\n';
  print_serial(buffer2, 4);
  print_screen(buffer2, 4);

 
  if (interrupt_handlers[regs.stack_contents.int_no] != 0) {
    isr_t handler = interrupt_handlers[regs.stack_contents.int_no];
    handler(regs);
  }
}
