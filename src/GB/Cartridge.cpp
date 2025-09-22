#include "Cartridge.h"

#include <fstream>

bool Cartridge::LoadROM(const std::string& rom)
{
	std::ifstream file(rom, std::ios::binary | std::ios::ate);
	if (!file) return false;

	size_t size = file.tellg();
	ROM.assign(size, 0);
	file.seekg(0);

	file.read(reinterpret_cast<char*>(ROM.data()), size);

	ReadCartHeader();

	return true;
}

void Cartridge::EjectROM()
{
	cartTitle = "";
	ROM.clear();
	numROMBanks = 0;
	numRAMBanks = 0;
	SGB = false;
	CGB = false;
	cartType = MBCType::None;
	cartFeatures = CartFeatures::NONE;
}

void Cartridge::ReadCartHeader()
{
	// TODO Get Cart Details here
}
