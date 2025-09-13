#include "Memory.h"

Memory::Memory()
    : bootROM(0xFF, 0), ROM(0xA000, 0), VRAM(0x2000, 0), ERAM(0x2000, 0),
    OAM(0xFF, 0), ioRegisters(0x80, 0), HRAM(0x80, 0), interruptRegister(0)
{
}

u8 Memory::Read(u16 address)
{
    return u8();
}

void Memory::Write(u16 address, u8 value)
{
}
