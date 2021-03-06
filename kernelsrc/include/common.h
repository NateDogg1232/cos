#ifndef _COMMON_H
#define _COMMON_H 1

#define bochs_magic_breakpoint outportw(0x8A00,0x8A00); outportw(0x8A00,0x08AE0);
#define bochs_char(c) outportb(0xe9, c);

#define ARCH x86

//Ignore int conversion warning, because I honestly couldn't give less of a crap
#pragma GCC diagnostic ignored "-Wint-conversion"


#define DEBUG 1

//0=None, for debugging, use COM1
//1=Bochs, for debugging, use the Bochs debugger
//2=QEMU, for debugging, use GDB (When implemented)
//3=Other, for debugging, use COM1
#define VM 1

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

bool strcmp(char* aptr, char* bptr);
int memcmp(const void* aptr, const void* bptr, size_t size);
void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size);
void* memmove(void* dstptr, const void* srcptr, size_t size);
void* memset(void* bufptr, int value, size_t size);
size_t strlen(const char* str);
void halt();
void halt_with_interrupts();
uint32_t strtol(char a[]);


typedef uint32_t phys_addr_t;
typedef uint32_t virt_addr_t;

#endif
