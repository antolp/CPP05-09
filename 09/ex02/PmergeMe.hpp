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

	void parseInput(int argc, char **argv);

	void sortVector(void);
	void sortDeque(void);

	void printBefore(void) const;
	void printAfter(void) const;

	static int parsePositiveInt(const std::string &s);
	static double getElapsedMicroseconds(clock_t start, clock_t end);

	// void mergeInsertVector(std::vector<int> &data);
	// void mergeInsertDeque(std::deque<int> &data);
};

#endif