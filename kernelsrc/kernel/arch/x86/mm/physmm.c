#include <arch/x86/mm/physmm.h>

//We first set up our physical memory table
//We set this up to cover all 4GB of the address space
//This bitmap takes up 32KB. There are two states of this bitmap. 1 = used, 0 = free

uint32_t* membitmap;
uint32_t memmapsize;
bool mmap_initialized = false;

//Allocates a certain ammount of memory.
uint32_t* phys_allocatemem(uint32_t size)
{

}

uint32_t pmm_init(uint32_t* bitmap, uint32_t bitmap_size)
{
    membitmap = bitmap;
    memmapsize = bitmap_size;
    mmap_initialized = true;
}

void phys_parsememtable(multiboot_memory_map_t* grub_memtable, uint32_t grub_memmap_size)
{
    for (uint32_t i = 0; i < grub_memmap_size; i++)
    {
        multiboot_memory_map_t* tmp_map = grub_memtable;
        

    }
}

//Sets a certain block of memory used
void phys_setmemused(uint32_t block)
{
    //Expanded version
    // //First we figure out what index this is
    // uint32_t index = block / 32;
    // //Then we figure out which bit it is
    // uint8_t bit = block % 32;
    //
    // //And now we set that bit
    // bitmap[index] |= 1 << bit;

    membitmap[block / 32] |= 1 << (block % 32);
}

//And now we set a certain block of memory free
void phys_setmemfree(uint32_t block)
{
    //The expanded version is virtually the same as the phys_setmemused() function
    membitmap[block / 32] &= ~(1 << (block % 32));
}

//Get if a block is free or not
bool phys_getblockstatus(uint32_t block)
{
    return membitmap[block / 32] & ~(1 << (block % 32));
}

uint32_t phys_findfreemem(uint32_t size)
{
    bool found = true;
    for (uint32_t i = 0; i < memmapsize; i++)
    {
        if (!phys_getblockstatus(i))
        {
            found = true;
            for (uint32_t j = 0; j < size; j++)
            {
                if (phys_getblockstatus(i + j))
                {
                    found = false;
                    break;
                }
            }
            if (found)
                return i;
        }
    }
}
