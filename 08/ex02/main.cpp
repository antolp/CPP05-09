#include <iostream>
#include <stack>
#include <list>
#include "MutantStack.hpp"

static void printTitle(const std::string& title)
{
	std::cout << "\n\t=== " << title << " ===" << std::endl;
}

template <typename Stack>
void printMutantStack(Stack& stack)
{
	typename Stack::iterator it = stack.begin();
	typename Stack::iterator ite = stack.end();

	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
}

template <typename Stack>
void printConstMutantStack(const Stack& stack)
{
	typename Stack::const_iterator it = stack.begin();
	typename Stack::const_iterator ite = stack.end();

	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
}

void testOCF()
{
		{
		printTitle("OCF : Copy constructor");

		MutantStack<int> original;

		original.push(10);
		original.push(20);
		original.push(30);

		MutantStack<int> copy(original);

		std::cout << "Original:" << std::endl;
		printMutantStack(original);

		std::cout << "Copy:" << std::endl;
		printMutantStack(copy);

		original.pop();
		original.push(99);

		std::cout << "Original after modification:" << std::endl;
		printMutantStack(original);

		std::cout << "Copy after original modification:" << std::endl;
		printMutantStack(copy);
	}

	{
		printTitle("OCF : Assignment operator");

		MutantStack<int> first;
		MutantStack<int> second;

		first.push(1);
		first.push(2);
		first.push(3);

		second.push(100);
		second.push(200);

		std::cout << "Second before assignment:" << std::endl;
		printMutantStack(second);

		second = first;

		std::cout << "Second after assignment:" << std::endl;
		printMutantStack(second);
	}
}

int main()
{
	// testOCF();

	{
		printTitle("Subject test");

		MutantStack<int> mstack;

		mstack.push(5);
		mstack.push(17);

		std::cout << "top: " << mstack.top() << std::endl;

		mstack.pop();

		std::cout << "size: " << mstack.size() << std::endl;

		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);

		MutantStack<int>::iterator it = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();

		++it;
		--it;

		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}

		std::stack<int> normalStack(mstack);

		std::cout << "normalStack top: " << normalStack.top() << std::endl;
		std::cout << "normalStack size: " << normalStack.size() << std::endl;
	}

	{
		printTitle("Compare with std::list");

		std::list<int> list;

		list.push_back(3);
		list.push_back(5);
		list.push_back(737);
		list.push_back(0);

		std::list<int>::iterator it = list.begin();
		std::list<int>::iterator ite = list.end();

		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
	}

	{
		printTitle("Const iterators");

		MutantStack<int> tmp;

		tmp.push(42);
		tmp.push(21);
		tmp.push(84);

		const MutantStack<int> constStack(tmp);

		printConstMutantStack(constStack);
	}

	return 0;
}