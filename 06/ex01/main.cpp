#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main()
{
	Data data;

	data.name = "fake mesh";
	data.type = 0;
	data.scale = 1.2;
	data.angle = 1.62;

	Data* original = &data;
	uintptr_t raw = Serializer::serialize(original);
	Data* result = Serializer::deserialize(raw);

	std::cout << "original pointer: " << original << std::endl;
	std::cout << "raw value:        " << raw << std::endl;
	std::cout << "result pointer:   " << result << std::endl;

	if (result == original)
		std::cout << "Success: pointers are equal" << std::endl;
	else
		std::cout << "Failure: pointers are different" << std::endl;

	std::cout << "result->name:  " << result->name << std::endl;
	std::cout << "result->type: " << result->type << std::endl;
	std::cout << "result->scale: " << result->scale << std::endl;
	std::cout << "result->angle: " << result->angle << std::endl;

	return 0;
}