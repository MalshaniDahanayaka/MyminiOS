#include "src/segmentation/gdt.h"
#include "src/drivers/interrupts/idt.h"
#include "src/utils/logger/logger.h"
#include "src/drivers/serial_port/serial_port.h"
#include "src/drivers/timer/timer.h"
#include "src/utils/common/types.h"
#include "multiboot.h"

/* Function to initialize */
void init() {
  /* Initialize segment descriptor tables */
  init_gdt();

  /* Initialize segment descriptor tables */
  init_idt();

  /* Initialize timer interrupt */
//  init_timer(TIMER_FREQUENCY);

  /* Initialize serial port */
  serial_configure(SERIAL_COM1_BASE, Baud_115200);
}

/* Kernel Main */
s32int kmain(unsigned int ebx) {
  init();
  multiboot_info_t *mbinfo = (multiboot_info_t *) ebx;
  	multiboot_module_t* modules = (multiboot_module_t*) mbinfo->mods_addr; 
  	unsigned int address_of_module = modules->mod_start;
  	
  	if((mbinfo->mods_count) == 1){
  		char message[] = "ONE module loaded successfully!";
  		serial_write(0x3F8,message,sizeof(message));
  		
  		typedef void (*call_module_t)(void);
        	/* ... */
        	call_module_t start_program = (call_module_t) address_of_module;
        	start_program();
        	/* we'll never get here, unless the module code returns */

  	}else{
  		char message[] = "Error: More than ONE module loaded";
  		serial_write(0x3F8,message,sizeof(message));
  	}
  s8int buffer[20] = "This works!!!!!!!\n";
  print_screen(buffer, 20);
  print_serial(buffer, 20);
  asm volatile("int $0x3");
  asm volatile("int $0x22");
  return 0;
}
