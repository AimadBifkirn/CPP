#pragma once

#include <iostream>
#include <stdint.h>
#include "Data.hpp"

class Serializer
{
	public:

		Serializer ();
		Serializer (const Serializer &other);
		Serializer &operator= (const Serializer &obj);
		~Serializer ();

		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};