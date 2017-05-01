/*
 *The GDT handler.
 *I'll be honest, most of this code was from Bran's kernel development tutorial
 *http://www.osdever.net/bkerndev/Docs/gdt.htm
 */

#include <sys/gdt.h>
#include <display/term.h>

void init_gdt()
{
	//setup the pointer for the GDT
	gdt_ptr.limit = (sizeof(gdt_entry_t)*3)-1;
	gdt_ptr.base = (uint32_t)&gdt_entries;
	//Make our GDT entries (Flat setup)
	gdt_set_gate(0,0,0,0,0);					//Our null segment
	gdt_set_gate(1,0,0xFFFFFFFF, 0x9A, 0xCF);	//Our code segment
	gdt_set_gate(2,0,0xFFFFFFFF, 0x92, 0xCF);	//Our data segment
	
	//Call the asm function in loadtables.asm to load the GDT
	load_gdt((uint32_t)&gdt_ptr);
	
	terminal_bootInfo("GDT loaded\n", 0);
}


//Adds an entry to the GDT
void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}
