#pragma once

#include "Register.h"

class Memory;

enum class RegisterTarget
{
	A,
	AF,
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
	NotCarry,
	HL,
};

enum class Flag : u8
{
	Zero = 7,
	Subtract = 6,
	HalfCarry = 5,
	Carry = 4
};

class CPU
{
public:
	CPU(Memory* memory);
	~CPU();

	void Step();
	int Decode();

	u8 FetchByte();
	u16 FetchWord();

	int GetTCycles() const { return tCycles; }
	int GetMCycles() const { return mCycles; }

	bool GetZeroFlag() const { return zero; }
	bool GetSubtractFlag() const { return subtract; }
	bool GetHalfCarryFlag() const { return halfCarry; }
	bool GetCarryFlag() const { return carry; }

	Register GetAF() const { return AF; }
	Register GetBC() const { return BC; }
	Register GetDE() const { return DE; }
	Register GetHL() const { return HL; }
	u16 GetSP() const { return SP; }
	u16 GetPC() const { return PC; }

private:

	// Flag Functions
	void SetFlag(Flag flag, bool enabled);

	// Instruction Functions

	// Load register into register
	// Load memory into register
	// Load register into memory
	// Load immediate byte into register
	// Load immediate word into register
	void LD(RegisterTarget to, RegisterTarget from);
	// Increment register value
	void INC(RegisterTarget reg);
	// Decrement register value
	void DEC(RegisterTarget reg);
	// Jump to address if condition is true
	void JP(Condition condition);
	// Jump PC to offset if condition is true
	void JR(Condition condition);
	// Add register N to register A and store result in register A
	// Add register NN to register HL and store result in register HL
	void ADD(RegisterTarget to = RegisterTarget::A, RegisterTarget from = RegisterTarget::A);
	// Add register N and carry flag to register A and store result in register A
	void ADC(RegisterTarget reg);
	// Subtract register N from register A and store result in register A
	void SUB(RegisterTarget reg);
	// Subtract register N and carry flag from register A and store result in register A
	void SBC(RegisterTarget reg);
	// Bitwise AND the bits of register N and register A and store the result in register A
	void AND(RegisterTarget reg);
	// Bitwise XOR the bits of register N and register A and store the result in register A
	void XOR(RegisterTarget reg);
	// Bitwise OR the bits of register N and register A and store the result in register A
	void OR(RegisterTarget reg);
	// Subtract register N from register A without storing the result. Set flags affected by the subtraction
	void CP(RegisterTarget reg);
	// If condition is true push PC after this instruction to stack and set PC to the immediate word
	void CALL(Condition condition);
	// Load the word pointed to by SP into the associated register
	void POP(RegisterTarget reg);
	// Write the value of the associated register to the memory address SP points to
	void PUSH(RegisterTarget reg);

	// Prefix Instruction Functions

	void BIT(int bit, RegisterTarget reg);
	void RES(int bit, RegisterTarget reg);
	void SET(int bit, RegisterTarget reg);
	void RLC(RegisterTarget reg);
	void RL(RegisterTarget reg);
	void RRC(RegisterTarget reg);
	void RR(RegisterTarget reg);
	void SLA(RegisterTarget reg);
	void SRA(RegisterTarget reg);
	void SWAP(RegisterTarget reg);
	void SRL(RegisterTarget reg);

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
	bool zero;
	bool subtract;
	bool halfCarry;
	bool carry;
};