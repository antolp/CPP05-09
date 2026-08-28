#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>
# include <iostream>
# include <stdexcept>
# include <cstdlib>
# include <climits>
# include <ctime>
# include <cctype>

class PmergeMe
{
public:
	PmergeMe(void);
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe(void);

	void run(int argc, char **argv);

private:
	std::vector<int> _vector;
	std::deque<int>  _deque;

    struct Item
    {
        int         value;
        std::size_t id;
    };

    struct Pair
    {
        Item small; // b_i
        Item large; // a_i
    };

    struct Pending
    {
        Item        item;
        std::size_t boundId;
        bool        hasBound;
    };

	void parseInput(int argc, char **argv);

	void printBefore(void) const;
	void printAfter(void) const;

	static int parsePositiveInt(const std::string &s);
	static double getElapsedMicroseconds(clock_t start, clock_t end);

	void sortVector(void);
	void sortDeque(void);

	//actual solve
    static std::vector<Item> fordJohnsonVector(const std::vector<Item> &input);
    static std::deque<Item> fordJohnsonDeque(const std::deque<Item> &input);

    static void binaryInsertVector(
        std::vector<Item> &chain,
        const Item &item,
        std::size_t boundId,
        bool hasBound
    );

	static void binaryInsertDeque(
        std::deque<Item> &chain,
        const Item &item,
        std::size_t boundId,
        bool hasBound
    );

    static std::vector<std::size_t> makeInsertionOrder(std::size_t bCount);
    static std::deque<std::size_t> makeInsertionOrderDeque(std::size_t bCount);
};

#endif