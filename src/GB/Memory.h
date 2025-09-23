#pragma once

#include "Definitions.h"

#include <string>
#include <vector>

class Cartridge;

class Memory
{
public:
	Memory();
	~Memory();

	u8 Read(u16 address);

	void Write(u16 address, const u8 value);

	bool LoadBootROM();
	void SetCart(Cartridge* cart) { this->cart = cart; }
	void SetBootROMPath(const std::string& path);
	void SetSkipBootROM(bool skip);

	bool GetBootROMEnabled() const { return bootRomEnabled; }

	void Reset();

private:
	std::string bootROMPath;
	std::vector<u8> bootROM;
	std::vector<u8> VRAM;
	std::vector<u8> ERAM;
	std::vector<u8> WRAM0;
	std::vector<u8> WRAM1;
	std::vector<u8> OAM;
	std::vector<u8> ioRegisters;
	std::vector<u8> HRAM;
	Cartridge* cart;
	u8 interruptRegister;
	bool bootRomEnabled;
};