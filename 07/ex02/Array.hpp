#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <cstddef>
# include <stdexcept>


template <typename T>
class Array
{
private:
	T*				_data;
	unsigned int	_size;

public:
	//empty array
	Array() : _data(NULL), _size(0)
	{
	}

	//constructor from paramether
	Array(unsigned int n) : _data(NULL), _size(n)
	{
		if (n > 0)
			_data = new T[n]();
	}

	//copy constructor
	Array(const Array& other) : _data(NULL), _size(0)
	{
		*this = other;
	}

	//assignment operator
	Array& operator=(const Array& other)
	{
		if (this != &other)
		{
			T* newData = NULL;

			if (other._size > 0)
				newData = new T[other._size]();

			for (unsigned int i = 0; i < other._size; i++)
				newData[i] = other._data[i];

			delete[] _data;

			_data = newData;
			_size = other._size;
		}
		return *this;
	}

	~Array()
	{
		delete[] _data;
	}

	// [] operator
	T& operator[](unsigned int index)
	{
		if (index >= _size)
			throw std::out_of_range("Array index out of bounds");
		return _data[index];
	}

	//const operator read only + exception handling
	const T& operator[](unsigned int index) const
	{
		if (index >= _size)
			throw std::out_of_range("Array index out of bounds");
		return _data[index];
	}

	unsigned int size() const
	{
		return _size;
	}
};

#endif