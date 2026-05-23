#ifndef WhATEVER_HPP
# define WhATEVER_HPP

# include <cstddef>

template <typename T>
void iter(T *array, std::size_t const length, void (*function)(T&))
{
	for (std::size_t i = 0; i < length; ++i)
		function(array[i]);
}

template <typename T>
void iter(T const *array, std::size_t const length, void (*function)(T const&))
{
	for (std::size_t i = 0; i < length; ++i)
		function(array[i]);
}

#endif