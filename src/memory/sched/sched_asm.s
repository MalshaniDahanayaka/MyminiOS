[GLOBAL read_eip]
read_eip:
  ; Get the return address
  pop eax
  ; Can't use RET because return address popped off the stack.
  jmp eax



[GLOBAL task_switch]
task_switch:
     cli;
     mov ecx, [esp+4]   ; EIP
     mov eax, [esp+8]   ; physical address of current directory
     mov ebp, [esp+12]  ; EBP
     mov esp, [esp+16]  ; ESP
     mov cr3, eax       ; set the page directory
     mov eax, 0x12345   ; magic number to detect a task switch
     sti;
     jmp ecx
