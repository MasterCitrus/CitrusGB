#include "Register.h"

#include <iostream>

Register::Register()
	: data(0x0)
{
}

Register::Register(u16 value)
	: data(value)
{
}

Register::Register(const Register& other)
	: data(other.data)
{
}

void Register::SetHighByte(u8 value)
{
	high = value;
}

void Register::SetLowByte(u8 value)
{
	low = value;
}

void Register::SetRegister(u16 value)
{
	data = value;
}

Register& Register::operator++()
{
	++data;
	return *this;
}

Register Register::operator++(int)
{
	Register old = *this;
	operator++();
	return old;
}

Register& Register::operator--()
{
	--data;
	return *this;
}

Register Register::operator--(int)
{
	Register old = *this;
	operator--();
	return old;
}

Register& Register::operator=(const u16& value)
{
	if (data == value) return *this;

	data = value;
	return *this;
}

Register& Register::operator=(const Register& value)
{
	if (this->data == value.data) return *this;

	data = value.data;
}

Register Register::operator<<(int shift) const
{
	return Register(data << shift);
}

Register Register::operator>>(int shift) const
{
	return Register(data >> shift);
}

Register Register::operator&(int mask) const
{
	return Register(data & mask);
}

Register Register::operator|(int mask) const
{
	return Register(data | mask);
}

Register Register::operator^(int mask) const
{
	return Register(data ^ mask);
}

Register Register::operator~() const
{
	return Register(~data);
}

Register Register::operator&(const Register& other) const
{
	return Register(data & other.data);
}

Register Register::operator|(const Register& other) const
{
	return Register(data | other.data);
}

Register Register::operator^(const Register& other) const
{
	return Register(data ^ other.data);
}

Register& Register::operator&=(int mask)
{
	data &= mask;
	return *this;
}

Register& Register::operator|=(int mask)
{
	data |= mask;
	return *this;
}

Register& Register::operator^=(int mask)
{
	data ^= mask;
	return *this;
}

Register& Register::operator<<=(int shift)
{
	data <<= shift;
	return *this;
}

Register& Register::operator>>=(int shift)
{
	data >>= shift;
	return *this;
}

Register& Register::operator&=(const Register& other)
{
	data &= other.data;
	return *this;
}

Register& Register::operator|=(const Register& other)
{
	data |= other.data;
	return *this;
}

Register& Register::operator^=(const Register& other)
{
	data ^= other.data;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Register& reg)
{
	os << reg.data;
	return os;
}
