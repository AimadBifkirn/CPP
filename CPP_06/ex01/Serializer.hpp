#pragma once

#include <iostream>
#include <cstdint>

class Serializer
{
	public:

		Serializer ();
		Serializer (const Serializer &other);
		Serializer &operator= (const Serializer &obj);
		~Serializer ();

		static uintptr_t serialize(void* ptr);
		static void *deserialize(uintptr_t raw);
};