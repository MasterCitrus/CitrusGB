#pragma once

#include "Instruction.h"
#include "Register.h"

#include <vector>

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
	OffsetC,
	MemBC,
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
	Interrupt,
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
	void Decode();

	void Reset();

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

	std::vector<Instruction> GetInstructions() const { return instructions; }

private:

	// Flag Functions
	void SetFlag(Flag flag, bool enabled);

	// Instruction Functions

	// Select a prefix instruction
	void Prefix();
	// No instruction
	void NOP();
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
	void ADD(RegisterTarget from, RegisterTarget to = RegisterTarget::A);
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
	// Return to PC if condition is met
	void RET(Condition condition);
	// Push PC to stack and jump to a specific address
	void RST(int num);
	// TODO STOP instructiom
	// void STOP();
	// TODO HALT instruction
	// void HALT();
	// TODO EI instruction
	// void EI();
	// TODO DI instruction
	// void DI();
	// TODO DAA instruction
	// void DAA();
	// Sets the carry flag
	void SCF();
	// Shift register A bits left, bit 7 becomes carry flag
	void RLCA();
	// Shift register A bits left
	void RLA();
	// Shift register A bits right, bit 0 becomes carry flag
	void RRCA();
	// Shift register A bits right
	void RRA();
	// Get one's complement of register A
	void CPL();
	// Flips carry flag
	void CCF();

	// Prefix Instruction Functions

	// Checks if bit of register is set
	void BIT(RegisterTarget reg, int bit);
	// Unsets bit of register
	void RES(RegisterTarget reg, int bit);
	// Sets bit of register
	void SET(RegisterTarget reg, int bit);
	// Shift bits left, bit 7 becomes carry flag
	void RLC(RegisterTarget reg);
	// Shift bits left
	void RL(RegisterTarget reg);
	// Shift bits right, bit 0 becomes carry flag
	void RRC(RegisterTarget reg);
	// Shift bits right
	void RR(RegisterTarget reg);
	// Shift bits left, bit 0 reset
	void SLA(RegisterTarget reg);
	// Shift bits right, most significant byte is preserved
	void SRA(RegisterTarget reg);
	// Swap bits 0-3 to 4-7 and bits 4-7 to 0-3
	void SWAP(RegisterTarget reg);
	// Shift bits right, bit 7 reset
	void SRL(RegisterTarget reg);

private:
	Instruction currentInstruction;
	std::vector<Instruction> instructions;
	int mCycles = 0;
	int tCycles = 0;
	Memory* memory;
	Register AF;
	Register BC;
	Register DE;
	Register HL;
	u16 PC;
	u16 SP;
	u8 OP;
	bool IME;
	bool zero;
	bool subtract;
	bool halfCarry;
	bool carry;
};