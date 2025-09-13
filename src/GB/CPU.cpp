#include "CPU.h"
#include "Memory.h"

void CPU::Step()
{

}

int CPU::Decode()
{
}

u8 CPU::FetchByte()
{
	return memory->Read(PC++);
}

u16 CPU::FetchWord()
{
	u8 low = FetchByte();
	u8 high = FetchByte();
	return (high << 8) | low;
}
