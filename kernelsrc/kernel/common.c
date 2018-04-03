#include <common.h>

#pragma GCC diagnostic ignored "-Wsign-compare"

bool strcmp(char *aptr, char *bptr)
{
    uint8_t c1, c2;
    while (1)
    {
        c1 = *aptr++;
        c2 = *bptr++;
        if (c1 != c2) return false;
        if (!c1) break;
    }

    return true;
}

void* memmove(void* dstptr, const void* srcptr, size_t size)
{
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	if (dst < src)
	{
		for (size_t i = 0; i < size; i++)
			dst[i] = src[i];
	}
	else
    {
		for (size_t i = size; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return dstptr;
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

int memcmp(const void* aptr, const void* bptr, size_t size)
{
	const unsigned char* a = (const unsigned char*) aptr;
	const unsigned char* b = (const unsigned char*) bptr;
	for (size_t i = 0; i < size; i++)
	{
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}

void* memset(void* bufptr, int value, size_t size)
{
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = (unsigned char) value;
	return bufptr;
}

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size)
{
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}

void halt()
{
    #if ARCH == x86
	asm volatile("cli");
    #endif
	for (;;);
}

void halt_with_interrupts()
{
	for (;;);
}

void clear_interrupts()
{
	asm volatile("cli");
}
void set_interrupts()
{
	asm volatile("sti");
}

uint32_t strtol(char a[])
{
    int n = 0;
    for (int c = 0; c < strlen(a); c++)
        n = n * 10 + a[c] - '0';
    return n;
}
