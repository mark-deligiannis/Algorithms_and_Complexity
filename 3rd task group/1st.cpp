#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>

using namespace std;

int N, F, sizelim, buff[64], loop_count, rep_count;

long long combined, combined_mirror;
unordered_set<long long> mult_pairs;

class DisjSet {
	int *parent, *size, n, max_size, max_size_repr;

public:
	// Constructor to create and
	// initialize sets of n items
	DisjSet(int num) : n(num), max_size(1), max_size_repr(0)
	{
		parent = new int[n];
        size = new int[n];
		makeSet();
	}

    ~DisjSet() {
        delete[] parent;
        delete[] size;
    }

	// Creates n single item sets
	void makeSet()
	{
		for (int i = 0; i < n; i++) {
			parent[i] = i;
            size[i] = 1;
		}
	}

	// Finds set of given item x
	int find(int x)
	{
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}

		return parent[x];
	}

	// Do union of two sets represented
	// by x and y.
	bool Union(int x, int y)
	{
		// Find current sets of x and y
		int xset = find(x);
		int yset = find(y);

		// If they are already in same set
		if (xset == yset)
			return false;

        int new_size = size[xset] + size[yset];
		if (size[xset] < size[yset]) {
			parent[xset] = yset;
            size[yset] = new_size;
		}
		else {
			parent[yset] = xset;
            size[xset] = new_size;
		}

        if (new_size > max_size) {
            max_size = new_size;
            max_size_repr = size[xset] > size[yset] ? xset : yset;
        }

        return max_size >= sizelim;
	}
};


int main()
{
    // Read first two lines
    cin >> N >> F;
    DisjSet components(N);

    loop_count = rep_count = 0;

    sizelim = N*F/100;
    if (N*F%100) sizelim += 1;

    for (int i=0; i<63; i++) cin >> buff[i];
    buff[63] = (buff[0] + buff[32])%N;

    for (int pair_count=1;; pair_count++) {
        int i = (2*pair_count-2)%64;
        combined = ((long long) buff[i] << 32) + buff[i+1];
        combined_mirror = ((long long) buff[i+1] << 32) + buff[i];
        if (mult_pairs.find(combined) == mult_pairs.end() && mult_pairs.find(combined_mirror) == mult_pairs.end())
            mult_pairs.insert(combined);
        else rep_count++;
        if (buff[i] == buff[i+1]) loop_count++;
        if (components.Union(buff[i], buff[i+1])) {
            cout << pair_count - rep_count - loop_count << " " << rep_count << " " << loop_count << endl;
            return 0;
        }
        
        buff[i] = ( buff[(i+1)%64] + buff[(i+33)%64] ) % N;
        buff[i+1] = ( buff[(i+2)%64] + buff[(i+34)%64] ) % N;
    }
}
