#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <stdint.h>

struct Data;

class Serializer
{
private:
	Serializer();
	Serializer(const Serializer& other);
	~Serializer();
	Serializer& operator=(const Serializer& other);

public:
	static uintptr_t serialize(Data* ptr);
	static Data* deserialize(uintptr_t raw);
};

#endif