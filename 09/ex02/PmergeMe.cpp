#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		this->_vector = other._vector;
		this->_deque = other._deque;
	}
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
}

void PmergeMe::run(int argc, char **argv)
{
	clock_t startVector;
	clock_t endVector;
	clock_t startDeque;
	clock_t endDeque;
	double vectorTime;
	double dequeTime;

	parseInput(argc, argv);
	printBefore();

	startVector = std::clock();
	sortVector();
	endVector = std::clock();

	startDeque = std::clock();
	sortDeque();
	endDeque = std::clock();

	printAfter();

	vectorTime = PmergeMe::getElapsedMicroseconds(startVector, endVector);
	dequeTime = PmergeMe::getElapsedMicroseconds(startDeque, endDeque);

	std::cout << "Time to process a range of "
			  << this->_vector.size()
			  << " elements with std::vector : "
			  << vectorTime
			  << " us"
			  << std::endl;

	std::cout << "Time to process a range of "
			  << this->_deque.size()
			  << " elements with std::deque : "
			  << dequeTime
			  << " us"
			  << std::endl;
}

void PmergeMe::parseInput(int argc, char **argv)
{
	int value;

	if (argc < 2)
		throw std::runtime_error("Error");

	for (int i = 1; i < argc; ++i)
	{
		value = PmergeMe::parsePositiveInt(argv[i]);
		this->_vector.push_back(value);
		this->_deque.push_back(value);
	}
}

int PmergeMe::parsePositiveInt(const std::string &s)
{
	char *endptr;
	long value;

	if (s.empty())
		throw std::runtime_error("Error");

	for (std::size_t i = 0; i < s.size(); ++i)
	{
		if (!std::isdigit(s[i]))
			throw std::runtime_error("Error");
	}

	value = std::strtol(s.c_str(), &endptr, 10);

	if (*endptr != '\0')
		throw std::runtime_error("Error");

	if (value <= 0 || value > INT_MAX)
		throw std::runtime_error("Error");

	return (static_cast<int>(value));
}

void PmergeMe::printBefore(void) const
{
	std::cout << "Before:";

	for (std::vector<int>::const_iterator it = this->_vector.begin();
		 it != this->_vector.end();
		 ++it)
	{
		std::cout << " " << *it;
	}

	std::cout << std::endl;
}

void PmergeMe::printAfter(void) const
{
	std::cout << "After:";

	for (std::vector<int>::const_iterator it = this->_vector.begin();
		 it != this->_vector.end();
		 ++it)
	{
		std::cout << " " << *it;
	}

	std::cout << std::endl;
}

double PmergeMe::getElapsedMicroseconds(clock_t start, clock_t end)
{
	return (static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC);
}

//
//
//	VECTOR Ford-Johnson
//
//

//section (11)
std::vector<std::size_t> PmergeMe::makeInsertionOrder(std::size_t bCount)
{
	std::vector<std::size_t> order;

	if (bCount <= 1)
		return order;

	std::size_t previous = 1; // t1
	std::size_t power = 4;    // 2^2

	while (previous < bCount)
	{
		std::size_t current = power - previous;

		//current follows:
		//3, 5, 11, 21, etc
		//
		//from :
		//t_k = 2^k - t_(k-1)
		std::size_t end = current;

		if (end > bCount)
			end = bCount;

		//Insert block backwards:
		//
		//for example :
		// 3,2
		// 5,4
		// 11,10,9,8,7,6 (always k max comparison)
		for (std::size_t i = end; i > previous; --i)
			order.push_back(i);

		previous = current;
		power *= 2;
	}

	return order;
}

void PmergeMe::binaryInsertVector(
	std::vector<Item> &chain,
	const Item &item,
	std::size_t boundId,
	bool hasBound)
{
	std::size_t right = chain.size();

	if (hasBound)
	{
		for (std::size_t i = 0; i < chain.size(); ++i)
		{
			if (chain[i].id == boundId)
			{
				right = i;
				break;
			}
		}
	}
	   std::size_t left = 0;

	while (left < right)
	{
		std::size_t middle = left + (right - left) / 2;

		if (chain[middle].value < item.value)
			left = middle + 1;
		else
			right = middle;
	}

	chain.insert(chain.begin() + left, item);
}

std::vector<PmergeMe::Item> PmergeMe::fordJohnsonVector(
	const std::vector<Item> &input)
{
	if (input.size() <= 1)
		return input;

	//
	// === 1. Pair elements: b_i <= a_i ===
	//
	std::vector<Pair> pairs;
	std::vector<Item> winners;

	std::size_t i = 0;

	while (i + 1 < input.size())
	{
		Pair pair;

		if (input[i].value <= input[i + 1].value)
		{
			pair.small = input[i];
			pair.large = input[i + 1];
		}
		else
		{
			pair.small = input[i + 1];
			pair.large = input[i];
		}

		pairs.push_back(pair);
		winners.push_back(pair.large);

		i += 2;
	}

	bool hasOdd = false;
	Item odd;

	if (i < input.size())
	{
		odd = input[i];
		hasOdd = true;
	}

	//
	// === 2. recursively sort only the a_i's values ===
	//
	std::vector<Item> sortedWinners =
		fordJohnsonVector(winners);


	//reorder the ORIGINAL pairs according to the sorted a_i's
	std::vector<Pair> orderedPairs;

	for (std::size_t w = 0; w < sortedWinners.size(); ++w)
	{
		for (std::size_t p = 0; p < pairs.size(); ++p)
		{
			if (pairs[p].large.id == sortedWinners[w].id)
			{
				orderedPairs.push_back(pairs[p]);
				break;
			}
		}
	}

	//
	// === 3 . main chain = b1, a1, a2, a3, ... ===
	//
	std::vector<Item> chain;

	chain.push_back(orderedPairs[0].small);

	for (std::size_t p = 0; p < orderedPairs.size(); ++p)
		chain.push_back(orderedPairs[p].large);

	//pending items to be sorted : b1, b2, b3, etc
	//(b1 is already in the main chain, kept here for indexing)
	std::vector<Pending> pend;

	for (std::size_t p = 0; p < orderedPairs.size(); ++p)
	{
		Pending pending;

		pending.item = orderedPairs[p].small;
		pending.boundId = orderedPairs[p].large.id;
		pending.hasBound = true;

		pend.push_back(pending);
	}

	if (hasOdd)
	{
		Pending pending;

		pending.item = odd;
		pending.boundId = 0;
		pending.hasBound = false;

		pend.push_back(pending);
	}

	//FINALLY insert in t_k order
	std::vector<std::size_t> order = makeInsertionOrder(pend.size());

	for (std::size_t j = 0; j < order.size(); ++j)
	{
		Pending &pending = pend[order[j] - 1];

		binaryInsertVector(
			chain,
			pending.item,
			pending.boundId,
			pending.hasBound
		);
	}

	return chain;
}

void PmergeMe::sortVector(void)
{
	std::vector<Item> input;

	input.reserve(_vector.size());

	for (std::size_t i = 0; i < _vector.size(); ++i)
	{
		Item item;

		item.value = _vector[i];
		item.id = i;

		input.push_back(item);
	}

	std::vector<Item> sorted = fordJohnsonVector(input);

	for (std::size_t i = 0; i < sorted.size(); ++i)
		_vector[i] = sorted[i].value;
}

//
//
// DEQUE Ford-Johnson
//
//
std::deque<std::size_t> PmergeMe::makeInsertionOrderDeque(std::size_t bCount)
{
	std::deque<std::size_t> order;

	if (bCount <= 1)
		return order;

	std::size_t previous = 1;
	std::size_t power = 4;

	while (previous < bCount)
	{
		std::size_t current = power - previous;

		std::size_t end = current;

		if (end > bCount)
			end = bCount;

		for (std::size_t i = end; i > previous; --i)
			order.push_back(i);

		previous = current;
		power *= 2;
	}

	return order;
}

void PmergeMe::binaryInsertDeque(
	std::deque<PmergeMe::Item> &chain,
	const Item &item,
	std::size_t boundId,
	bool hasBound)
{
	std::size_t right = chain.size();

	if (hasBound)
	{
		for (std::size_t i = 0; i < chain.size(); ++i)
		{
			if (chain[i].id == boundId)
			{
				right = i;
				break;
			}
		}
	}

	std::size_t left = 0;

	while (left < right)
	{
		std::size_t middle = left + (right - left) / 2;

		if (chain[middle].value < item.value)
			left = middle + 1;
		else
			right = middle;
	}

	chain.insert(chain.begin() + left, item);
}

std::deque<PmergeMe::Item> PmergeMe::fordJohnsonDeque(
	const std::deque<Item> &input)
{
	if (input.size() <= 1)
		return input;

	//
	// === 1. Pair elements: b_i <= a_i ===
	//
	std::deque<Pair> pairs;
	std::deque<Item> winners;

	std::size_t i = 0;

	while (i + 1 < input.size())
	{
		Pair pair;

		if (input[i].value <= input[i + 1].value)
		{
			pair.small = input[i];
			pair.large = input[i + 1];
		}
		else
		{
			pair.small = input[i + 1];
			pair.large = input[i];
		}

		pairs.push_back(pair);
		winners.push_back(pair.large);

		i += 2;
	}

	bool hasOdd = false;
	Item odd;

	if (i < input.size())
	{
		odd = input[i];
		hasOdd = true;
	}

	//
	// === 2. Recursively sort the a_i values ===
	//
	std::deque<Item> sortedWinners =
		fordJohnsonDeque(winners);

	//
	// Reorder the ORIGINAL pairs according to the
	// recursively sorted winners.
	//
	std::deque<Pair> orderedPairs;

	for (std::size_t w = 0; w < sortedWinners.size(); ++w)
	{
		for (std::size_t p = 0; p < pairs.size(); ++p)
		{
			if (pairs[p].large.id == sortedWinners[w].id)
			{
				orderedPairs.push_back(pairs[p]);
				break;
			}
		}
	}

	//
	// === 3. Main chain = b1, a1, a2, a3, ... ===
	//
	std::deque<Item> chain;

	chain.push_back(orderedPairs[0].small);

	for (std::size_t p = 0; p < orderedPairs.size(); ++p)
		chain.push_back(orderedPairs[p].large);

	//
	// Pending = b1, b2, b3, ...
	//
	std::deque<Pending> pend;

	for (std::size_t p = 0; p < orderedPairs.size(); ++p)
	{
		Pending pending;

		pending.item = orderedPairs[p].small;
		pending.boundId = orderedPairs[p].large.id;
		pending.hasBound = true;

		pend.push_back(pending);
	}

	if (hasOdd)
	{
		Pending pending;

		pending.item = odd;
		pending.boundId = 0;
		pending.hasBound = false;

		pend.push_back(pending);
	}

	//
	// Insert in Ford-Johnson insertion order
	//
	std::deque<std::size_t> order =
		makeInsertionOrderDeque(pend.size());

	for (std::size_t j = 0; j < order.size(); ++j)
	{
		Pending &pending = pend[order[j] - 1];

		binaryInsertDeque(
			chain,
			pending.item,
			pending.boundId,
			pending.hasBound
		);
	}

	return chain;
}

void PmergeMe::sortDeque(void)
{
	std::deque<Item> input;

	for (std::size_t i = 0; i < _deque.size(); ++i)
	{
		Item item;

		item.value = _deque[i];
		item.id = i;

		input.push_back(item);
	}

	std::deque<Item> sorted = fordJohnsonDeque(input);

	for (std::size_t i = 0; i < sorted.size(); ++i)
		_deque[i] = sorted[i].value;
}