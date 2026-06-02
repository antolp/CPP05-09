#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>

template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
public:
	typedef typename std::stack<T, Container>::container_type container_type;

	typedef typename container_type::iterator iterator;
	typedef typename container_type::const_iterator const_iterator;
	typedef typename container_type::reverse_iterator reverse_iterator;
	typedef typename container_type::const_reverse_iterator const_reverse_iterator;

	MutantStack(void) : std::stack<T, Container>()
	{
	}

	MutantStack(MutantStack const &other) : std::stack<T, Container>(other)
	{
	}

	MutantStack& operator=(MutantStack const& other)
	{
		if (this != &other)
			std::stack<T>::operator=(other);
		return *this;
	}

	~MutantStack(void)
	{
	}

	iterator begin(void)
	{
		return this->c.begin();
	}

	iterator end(void)
	{
		return this->c.end();
	}

	const_iterator begin(void) const
	{
		return this->c.begin();
	}

	const_iterator end(void) const
	{
		return this->c.end();
	}
};

#endif
