#pragma once

#include "Register.h"

class Memory;

enum class RegisterTarget
{
	A,
	B,
	C,
	BC,
	D,
	E,
	DE,
	H,
	L,
	HL,
	SP,
	Byte,
	Word,
	Offset,
	MemBC,
	MemC,
	MemDE,
	MemHL,
	MemHLDec,
	MemHLInc,
};

enum class Condition
{
	None,
	Zero,
	NotZero,
	Carry,
	NotCarry
};

class CPU
{
public:
	void Step();
	int Decode();

	u8 FetchByte();
	u16 FetchWord();

	int GetTCycles() const { return tCycles; }
	int GetMCycles() const { return mCycles; }

private:

	void LD(RegisterTarget to, RegisterTarget from);

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
	bool IME;
};