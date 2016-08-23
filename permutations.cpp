#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void generateAllPermutations(vector< vector<int> > &vec, int n);

///////////////////////////////////////////////////////////
// Helper functions for I/O
///////////////////////////////////////////////////////////
template <typename T>
void stream_data(const T &data)
{
	cout << " " << data;
}

template <typename T>
ostream &operator <<(ostream & stream, const vector<T>& vec)
{
	for_each(vec.begin(), vec.end(), stream_data<T>);
	return stream;
}

template <typename T>
void printVector(const vector<T> &vec)
{
	typename vector<T>::const_iterator iter;
	for(iter = vec.begin(); iter < vec.end(); iter++)
	{
		cout << "    " << *iter << endl;
	}
	return;
}

///////////////////////////////////////////////////////////
// Entry point
///////////////////////////////////////////////////////////

#ifdef _BUILD_EXE
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "USAGE: " << argv[0] << " number_of_nodes" << endl
		     << "       Prints all permutations of n nodes." << endl;
		return -1;
	}
	
	int permSize = atoi(argv[1]);
	vector< vector<int> > perms;
	
	generateAllPermutations(perms, permSize);
	printVector(perms);
	return 0;
}
#endif

// TODO: This should be class-scope state. Avoid globals.
int g_compareAgainst;
bool isGreater(int value)
{
	return (value > g_compareAgainst);
}

int currentInteger(0);
int nextInteger() { return ++currentInteger; }

////////////////////////////////////////////////////////////////////////
// function generateAllPermutations(vec, n)
// Populates "vec" with the n! permutations of size n in ascending lexicographical order 
////////////////////////////////////////////////////////////////////////

void generateAllPermutations(vector< vector<int> > &vec, int n)
{
	// Initialize with the very first permutation
	vector<int> currentPerm(n);
	generate_n(currentPerm.begin(), n, nextInteger);
	vec.push_back(currentPerm);

	vector<int>::reverse_iterator backwardWalker = currentPerm.rbegin();
	vector<int>::reverse_iterator stoppingPoint = currentPerm.rend();

	vector<int> availableValues;

	while (true)
	{
		// Record the values we observe while walking backwards
		// Initialize with the very last digit of the previous permutation
		availableValues.push_back(*backwardWalker);
		backwardWalker++;
		// Termination condition = inspected all digits and not even the first is increasable
		if (backwardWalker == stoppingPoint)
			break;

		// Stop at the appropriate digit and increase the permutation
		if (*backwardWalker < availableValues.back())
		{
			// Swap in the smallest available element > the replacee.
			// Since they're in ascending order a linear search is acceptable.
			int swapInValue;
			vector<int>::iterator smallestGreaterIt;
// Thread-dangerous!!!
			g_compareAgainst = *backwardWalker;

			smallestGreaterIt = find_if(availableValues.begin(), availableValues.end(), isGreater);
			int smallestGreater = *smallestGreaterIt;
// up to here.

			// Step 1: Swap the increasable digit (*backwardWalker) with its next-greater
			//         in-place in the permutation
			*smallestGreaterIt = *backwardWalker; // change the entry, don't append
			*backwardWalker = smallestGreater;

			// Step 2: Write down the available values in-place within the permutation,
			//         in stored order to reverse them.
			copy(availableValues.begin(), availableValues.end(),
			     currentPerm.end()-availableValues.size());

			// We have produced the next permutation. Save it and clean up.
			vec.push_back(currentPerm);
			availableValues.clear();
			backwardWalker = currentPerm.rbegin();
		}
		else
		{
			// Keep backtracking since we haven't found a digit we can increase.
			// Nothing to do here; top of while loop does this.
		}
	}

	return;
}

