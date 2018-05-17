;    Copyright © 2017 DiamondSoft. All rights reserved.
;    Author: Artem Pityrenko 
;
;    This code belongs to the DiamondSoft development team.
;	
;	from Project: DiamOS 
;	
;	Contact information:
;	GitHub:   <https://github.com/DiamSoft>
;	@E-Mail:  <os.dever@yandex.ru>


global loader     ;Entry point
extern _kmain     ;Function on C/C++

;#### multi boot header ####;
MODULEALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ  MODULEALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .text
align 4
MultiBootHeader:
dd MAGIC
dd FLAGS
dd CHECKSUM
    dd 0
    dd 0
    dd 0

STACKSIZE equ 0x4000

loader:
   mov esp,stack+STACKSIZE
   push eax
   push ebx

	;jmp $
    jmp _kmain   ; Jump to kernel main
   
   cli
halt:
   hlt
   jmp halt
   

section .bss
align 4
stack:
 resb STACKSIZE
 
 section .data
 