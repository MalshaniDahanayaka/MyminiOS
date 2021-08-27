#include "idt.h"
#include "../io/io.h"


extern void idt_flush(u32int);


idt_entry_t idt_entries[256];


void init_pic() {

  outb(PIC1, INITIALISE_COMMAND);
  outb(PIC2, INITIALISE_COMMAND);

  
  outb(PIC1_DATA, PIC1_VECTOR_OFFSET);
  outb(PIC2_DATA, PIC2_VECTOR_OFFSET);

  
  outb(PIC1_DATA, PIC2_PORT_IN_PIC1);


  outb(PIC2_DATA, PIC2_CASCADED_IDEN);

  
  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);


  outb(PIC1_DATA, 0x0);
  outb(PIC2_DATA, 0x0);
}


static void idt_set_gate(u8int num, u32int addressISR, u16int segmentSelector,
                         u8int accessGran) {
  idt_entries[num].offset_low = (addressISR & 0xFFFF);
  idt_entries[num].segment_selector = segmentSelector;
  idt_entries[num].alwaysZero = 0;

  idt_entries[num].access_gran = accessGran;

  idt_entries[num].offset_high = addressISR >> 16;
}

void init_idt() {
  idt_ptr_t idt_ptr;
  idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_ptr.base = (u32int)&idt_entries;

  
  init_pic();

 
  idt_set_gate(0, (u32int)isr0, 0x08, 0x8E);   // ISR 0
  idt_set_gate(1, (u32int)isr1, 0x08, 0x8E);   // ISR 1
  idt_set_gate(2, (u32int)isr2, 0x08, 0x8E);   // ISR 2
  idt_set_gate(3, (u32int)isr3, 0x08, 0x8E);   // ISR 3
  idt_set_gate(4, (u32int)isr4, 0x08, 0x8E);   // ISR 4
  idt_set_gate(5, (u32int)isr5, 0x08, 0x8E);   // ISR 5
  idt_set_gate(6, (u32int)isr6, 0x08, 0x8E);   // ISR 6
  idt_set_gate(7, (u32int)isr7, 0x08, 0x8E);   // ISR 7
  idt_set_gate(8, (u32int)isr8, 0x08, 0x8E);   // ISR 8
  idt_set_gate(9, (u32int)isr9, 0x08, 0x8E);   // ISR 9
  idt_set_gate(10, (u32int)isr10, 0x08, 0x8E); // ISR 10
  idt_set_gate(11, (u32int)isr11, 0x08, 0x8E); // ISR 11
  idt_set_gate(12, (u32int)isr12, 0x08, 0x8E); // ISR 12
  idt_set_gate(13, (u32int)isr13, 0x08, 0x8E); // ISR 13
  idt_set_gate(14, (u32int)isr14, 0x08, 0x8E); // ISR 14
  idt_set_gate(15, (u32int)isr15, 0x08, 0x8E); // ISR 15
  idt_set_gate(16, (u32int)isr16, 0x08, 0x8E); // ISR 16
  idt_set_gate(17, (u32int)isr17, 0x08, 0x8E); // ISR 17
  idt_set_gate(18, (u32int)isr18, 0x08, 0x8E); // ISR 18
  idt_set_gate(19, (u32int)isr19, 0x08, 0x8E); // ISR 19
  idt_set_gate(20, (u32int)isr20, 0x08, 0x8E); // ISR 20
  idt_set_gate(21, (u32int)isr21, 0x08, 0x8E); // ISR 21
  idt_set_gate(22, (u32int)isr22, 0x08, 0x8E); // ISR 22
  idt_set_gate(23, (u32int)isr23, 0x08, 0x8E); // ISR 23
  idt_set_gate(24, (u32int)isr24, 0x08, 0x8E); // ISR 24
  idt_set_gate(25, (u32int)isr25, 0x08, 0x8E); // ISR 25
  idt_set_gate(26, (u32int)isr26, 0x08, 0x8E); // ISR 26
  idt_set_gate(27, (u32int)isr27, 0x08, 0x8E); // ISR 27
  idt_set_gate(28, (u32int)isr28, 0x08, 0x8E); // ISR 28
  idt_set_gate(29, (u32int)isr29, 0x08, 0x8E); // ISR 29
  idt_set_gate(30, (u32int)isr30, 0x08, 0x8E); // ISR 30
  idt_set_gate(31, (u32int)isr31, 0x08, 0x8E); // ISR 31

  
  idt_set_gate(32, (u32int)irq0, 0x08, 0x8E);  // IRQ 0
  idt_set_gate(33, (u32int)irq1, 0x08, 0x8E);  // IRQ 1
  idt_set_gate(34, (u32int)irq2, 0x08, 0x8E);  // IRQ 2
  idt_set_gate(35, (u32int)irq3, 0x08, 0x8E);  // IRQ 3
  idt_set_gate(36, (u32int)irq4, 0x08, 0x8E);  // IRQ 4
  idt_set_gate(37, (u32int)irq5, 0x08, 0x8E);  // IRQ 5
  idt_set_gate(38, (u32int)irq6, 0x08, 0x8E);  // IRQ 6
  idt_set_gate(39, (u32int)irq7, 0x08, 0x8E);  // IRQ 7
  idt_set_gate(40, (u32int)irq8, 0x08, 0x8E);  // IRQ 8
  idt_set_gate(41, (u32int)irq9, 0x08, 0x8E);  // IRQ 9
  idt_set_gate(42, (u32int)irq10, 0x08, 0x8E); // IRQ 10
  idt_set_gate(43, (u32int)irq11, 0x08, 0x8E); // IRQ 11
  idt_set_gate(44, (u32int)irq12, 0x08, 0x8E); // IRQ 12
  idt_set_gate(45, (u32int)irq13, 0x08, 0x8E); // IRQ 13
  idt_set_gate(46, (u32int)irq14, 0x08, 0x8E); // IRQ 14
  idt_set_gate(47, (u32int)irq15, 0x08, 0x8E); // IRQ 15

  idt_flush((u32int)&idt_ptr);
}
