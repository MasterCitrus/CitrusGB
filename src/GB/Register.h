#pragma once

#include "Definitions.h"
#include <iosfwd>

class Register
{
public:
	Register();
	Register(u16 value);
	Register(const Register& other);

	// Set Values
	void SetHighByte(const u8 value);
	void SetLowByte(const u8 value);
	void SetRegister(const u16 value);

	// Get values const
	u8 GetHighByte() const { return high; }
	u8 GetLowByte() const { return low; }
	u16 GetRegister() const { return data; }

	// Get value ref
	u8& GetHighByte() { return high; }
	u8& GetLowByte() { return low; }
	u16& GetRegister() { return data; }

	// Operator Overloads - Only afffects the Register pair
	Register& operator++();
	Register operator++(int);
	Register& operator--();
	Register operator--(int);

	Register& operator=(const u16& value);
	Register& operator=(const Register& value);

	friend std::ostream& operator<<(std::ostream& os, const Register& reg);

	// Bitwise Operations - Only affects the Register pair
	Register operator<<(int shift) const;
	Register operator>>(int shift) const;

	Register operator&(int mask) const;
	Register operator|(int mask) const;
	Register operator^(int mask) const;
	Register operator~() const;
	Register operator&(const Register& other) const;
	Register operator|(const Register& other) const;
	Register operator^(const Register& other) const;

	Register& operator&=(int mask);
	Register& operator|=(int mask);
	Register& operator^=(int mask);
	Register& operator<<=(int shift);
	Register& operator>>=(int shift);

	Register& operator&=(const Register& other);
	Register& operator|=(const Register& other);
	Register& operator^=(const Register& other);

private:
	union
	{
		struct
		{
			u8 low;
			u8 high;
		};
		u16 data;
	};
};