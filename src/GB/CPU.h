#pragma once

#include "Register.h"

class Memory;

class CPU
{
public:
	void Step();
	int Decode();

	u8 FetchByte();
	u16 FetchWord();

private:


private:
	Memory* memory;
	int mCycles = 0;
	int tCycles = 0;
	Register AF;
	Register BC;
	Register DE;
	Register HL;
	u16 PC;
	u16 SP;
};