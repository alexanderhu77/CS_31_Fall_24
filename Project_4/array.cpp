#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value) {
	if (n < 0) {
		return  -1;
	}
	// iterate through and append elements up until n is reached
	for (int i = 0; i< n; i++) {
		a[i] +=value;
	}
	return n;
}

int lookup(const string a[], int n, string target) {
	if (n < 0) {
		return  -1;
	}
	// Iterates through and sees if an element matches the target
	for (int i = 0; i < n; i++) {
		if (a[i] == target){
			return i;
		}
	}
	return -1;
}

int positionOfMax(const string a[], int n) {
	if (n <= 0) {
		return  -1;
	}
	int max = 0;
	// constantly replace the max and update as the program iterates through
	for (int i = 0; i < n; i++) {
		if (a[i] > a[max]) {
			max = i;
		}
	}
	return max;
}

int rotateLeft(string a[], int n, int pos) {
	// some invalid cases other than when n< 0 
	if (n < 0 || pos<0 || pos >= n) {
		return  -1;
	}
	//store the element that will be copied to the end in a temporary variable
	string temp = a[pos];
	//copy elements to the left
	for (int i = pos; i < n-1; i++) {
		a[i] = a[i + 1];
	}
	// reassign temp to the end
	a[n-1] = temp;
	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0) {
		return -1;
	}
	if (n == 0) {
		return 0;
	}


	// check the elements in sequence and compare if different
	int count = 1;
	for (int i =1; i< n; i++) {
		if (a[i] != a[i - 1]) { // if elements in sequence are not different, then no increase in count
			count++;
		}
	}
	return count;
}

int flip(string a[], int n) {
	if (n < 0) {
		return -1;
	}
	string  temp;
	// go up to half of the string
	for (int i = 0; i < n/2; i++) {

		// swap elements a[i] and a[n-i-1] because 1 is subtracted because indexes start at 0 and that minus i is the index of element to be swapped
		temp=a[i];
		a[i] = a[n-i-1];
		a[n - i - 1] = temp;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	for (int i = 0; i < n1 && i < n2; i++) {
		// see if any difference between the arrays and return the first index which they are different
		if (a1[i] != a2[i]) {
			return i;
		}
	}
	if (n1 <= n2) {
		return n1;
	}
	else {
		return n2;
	}
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n2 > n1) {
		return -1;
	}
	bool found = false; //used to see if a potential match is found
	for (int i = 0; i < n1; i++) {
		if (a1[i] == a2[0]) {
			//store index variable in case we need to return this
			int indexFound = i;
			//iterate though a2 to see if each element matches a1
			for (int j = 0; j < n2 && i < n1; j++) {
				found = true;
				if (a1[i] != a2[j]) {
					found = false; // reset to false if the match verification fails
					break;
				}
				i++;
			}
			if (found) {
				return indexFound;
			}
		}
	}
	// if nothing is found
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 <0) {
		return -1;
	}
	// iterate through both arrays and see if any elements match
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j]) {
				return i;
			}
		}
	}
	return -1;
}

int separate(string a[], int n, string separator) {
	if (n < 0) {
		return -1;
	}

	int less = 0;
	int greater = n-1;

	for (int i = 0; i <= greater; i++) {
		if (a[i] < separator) {
			
			// if an element is less that the separator, then move to fromt
			string temp = a[i];
			a[i] = a[less];
			a[less] = temp;
			less++;
			
		}
		else if (a[i] > separator) {
			// if an element is greater than the separator, then move to the back
			
			string temp = a[i];
			a[i] = a[greater];
			a[greater] = temp;
			greater--;
			i--; // since the element has changed, it needs to be rechecked
			
		}
		
	}

	return less;


}

int main() 
{
	string h[7] = { "melania", "kamala", "donald", "tim", "", "doug", "jd" };
	assert(lookup(h, 7, "doug") == 5);
	assert(lookup(h, 7, "donald") == 2);
	assert(lookup(h, 2, "donald") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "melania", "kamala", "jd", "usha" };
	
	assert(appendToAll(g, 0, "?") == 0 && g[0] == "melania" && g[3] == "usha");
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "melania?" && g[3] == "usha?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jd?" && g[3] == "kamala?");

	string e[4] = { "donald", "tim", "", "doug" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "kamala", "kamala", "kamala", "tim", "tim" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "jd", "donald", "gwen" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "gwen" && f[2] == "jd");

	assert(separate(h, 7, "jd") == 3);
	
	
	

	assert(appendToAll(g, -1, "?") == -1);
	
	assert(lookup(h, 0, "doug") == -1);
	assert(lookup(h, 7, "dont exist") == -1);
	assert(positionOfMax(h, 0) == -1);
	assert(rotateLeft(g, 4, -1) == -1);
	assert(rotateLeft(g, 0, 1) == -1);
	assert(countRuns(g, 0) == 0);
	assert(flip(g, 0) == 0);
	assert(subsequence(h, 2, g, 6) == -1);
	assert(lookupAny(g, 4, e, 4) == -1);
	assert(separate(g, -1, "testing") == -1);
	// cerr << "All tests succeeded" << endl;
}