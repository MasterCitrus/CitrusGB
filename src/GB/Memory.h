#pragma once

#include "Definitions.h"

#include <vector>

class Memory
{
public:
	Memory();
	~Memory();

	u8 Read(u16 address);

	void Write(u16 address, const u8 value);

private:
	std::vector<u8> bootROM;
	std::vector<u8> VRAM;
	std::vector<u8> ERAM;
	std::vector<u8> WRAM0;
	std::vector<u8> WRAM1;
	std::vector<u8> OAM;
	std::vector<u8> ioRegisters;
	std::vector<u8> HRAM;
	u8 interruptRegister;
	bool bootRomEnabled;
};