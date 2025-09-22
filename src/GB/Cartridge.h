#pragma once

#include "Definitions.h"

#include <string>
#include <vector>

enum class MBCType
{
	None,
	MBC1,
	MBC2,
	MBC3,
	MBC5,
	MBC6,
	MBC7,
	MMM01,
	HuC1,
	HuC3
};

enum class CartFeatures : u8
{
	NONE = 0,
	RAM = 1 << 0,
	BATTERY = 1 << 1,
	TIMER = 1 << 2,
	RUMBLE = 1 << 3,
	SENSOR = 1 << 4
};

struct CartDetails
{
	std::string title;
	u16 newLicenceeCode;
	u8 CBGFlag;
	u8 SGBFlag;
	u8 romSize;
	u8 oldLicenceeCode;
	u8 destinationCode;
	u8 ROMSize;
	u8 RAMSize;
	u8 cartType;

};

class Cartridge
{
public:

	u8 Read(u16 address);
	void Write(u16 address, u8 value);

	bool LoadROM(const std::string& rom);
	void EjectROM();

private:

	void ReadCartHeader();

private:
	std::string cartTitle;
	std::vector<u8> ROM;
	int numROMBanks;
	int numRAMBanks;
	bool SGB;
	bool CGB;
	MBCType cartType;
	CartFeatures cartFeatures;
};