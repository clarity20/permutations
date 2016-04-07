#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void generateAllPermutations(vector< vector<int> > &vec, int size);

// How to recurse on this for vecs of vecs???
template <typename T>
void stream_data(const T &data)
{
	cout << " " << data;
}

template <typename T>
ostream &operator <<(ostream & stream, const vector<T>& vec)
{
	for_each(vec.begin(), vec.end(), stream_data<T>);
//cout << endl << "Finished special streaming operator..." << endl;
	return stream;
}

template <typename T>
void printVector(const vector<T> &vec)
{
//cout << "    Inside printVector...\n";
	typename vector<T>::const_iterator iter;
//cout << "    Printing... vec len = " << vec.size() << endl;
//begin = 0th elt
//end = 1 beyond last elt
	for(iter = vec.begin(); iter < vec.end(); iter++)
	{
//cout << "    Printing one..." << endl;
		cout << "    " << *iter << endl;
	}
	return;
}

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
cout << "Total number of perms is " << perms.size() << endl;
cout << "Length of each is " << perms[0].size() << endl;
	printVector(perms);
//cout << "All printed!\n";
	return 0;
}
#endif

int g_compareAgainst;
bool isGreater(int value)
{
//cout << "Comparing avail " << value << " against curr val " << g_compareAgainst << endl; 
	return (value > g_compareAgainst);
}

int currentInteger(0);
int nextInteger() { return ++currentInteger; }

void generateAllPermutations(vector< vector<int> > &vec, int size)
{
	vector<int> currentPerm(size);
	generate_n(currentPerm.begin(), size, nextInteger);
	vec.push_back(currentPerm);

	vector<int>::reverse_iterator backwardWalker = currentPerm.rbegin();
	vector<int>::reverse_iterator stoppingPoint = currentPerm.rend();

	vector<int> availableValues;

	while (true)
	{
		// Record the values we observe while walking backwards
//cout << "prev digit inspected: " << *backwardWalker << endl;
		// Initialize with the very last digit of the previous permutation
		availableValues.push_back(*backwardWalker);
		backwardWalker++;
//cout << "next digit to inspect: " << *backwardWalker << endl;
//cout << "now available: " << availableValues.back() << " num available: " << availableValues.size() << endl;
		// Termination condition = inspected all digits and not even the first is increasable
		if (backwardWalker == stoppingPoint)
			break;

		// Stop at the appropriate digit and increase the permutation
		if (*backwardWalker < availableValues.back())
		{
			// Swap in the smallest available element > the replacee.
			// Since they're in ascending order we need just a linear search.
			int swapInValue;
			vector<int>::iterator smallestGreaterIt;
// Thread-dangerous!!!
			g_compareAgainst = *backwardWalker;

			smallestGreaterIt = find_if(availableValues.begin(), availableValues.end(), isGreater);
			int smallestGreater = *smallestGreaterIt;
// up to here.

			// Step 1: Swap the increasable digit (*backwardWalker) and its next-greater
			//         in-place in the permutation
			*smallestGreaterIt = *backwardWalker; // change the entry, don't append
			*backwardWalker = smallestGreater;

			// Step 2: Write down the available values in-place within the permutation,
			//         in stored order to reverse them.

			copy(availableValues.begin(), availableValues.end(),
			     currentPerm.end()-availableValues.size());

//cout << "new perm, length " << currentPerm.size() << ": " << currentPerm[0];
//cout << " " << currentPerm[1] << " " << currentPerm[2] << endl << endl;

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

