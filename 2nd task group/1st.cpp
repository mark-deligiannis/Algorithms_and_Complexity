#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <limits>

using namespace std;

typedef pair<int,int> pii;

int N,K,l,max_l,help_l;
vector<int> numbers;
vector<pii> results_left, results_right, transition_stack;
int current, previous;


bool compare_less(pii x, pii y) { return x.second<y.second; }
bool compare_more(pii x, pii y) { return x.second>y.second; }

void apply_transition() {
    pii temp = transition_stack.back();
    transition_stack.pop_back();
    if (temp.second == -1) results_left.pop_back();
    else results_left[temp.first] = temp;
}

int main() {
    // Get N, K
    cin >> N >> K;
    
    // Add dummies
    results_left.push_back({0, -1});
    results_right.push_back({0, numeric_limits<int>::max()});

    // Initalize
    cin >> current;
    numbers.push_back(current);
    results_left.push_back({1, current});
    transition_stack.push_back({1,-1});

    // Scan array from left to right and construct transition_stack
    for (int i=1; i<N-1; ++i) {
        // Get i-th number
        cin >> current;
        numbers.push_back(current);
        
        // Calculations for first array
        auto result = lower_bound(results_left.begin(),results_left.end(),make_pair(0,current),compare_less) - 1;
        l = result->first + 1;

        // Update transition_stack and results_left
        if (l == results_left.size()) {
            transition_stack.push_back({l,-1});
            results_left.push_back({l, current});
        }
        else {
            transition_stack.push_back(results_left[l]);
            results_left[l] = {l, current};
        }
    }

    // Get N-th number
    cin >> current;
    numbers.push_back(current);

    // Small preparations
    max_l = 0;
    // results_right.push_back({1,numbers[N-1]});

    // Scan array from right to left and construct solution
    for (int i=1; i<N; ++i) {
        // Get current number
        current = numbers[N-i-1];
        previous = numbers[N-i];

        // Get relevant "version" of results_left
        apply_transition();

        // Calculations for first array
        auto result = lower_bound(results_left.begin(),results_left.end(),make_pair(0,current),compare_less) - 1;
        help_l = result->first;

        // Calculations for second array
        result = lower_bound(results_right.begin(),results_right.end(),make_pair(0,previous),compare_more) - 1;
        l = result->first + 1;
        // Update results_right
        if (l == results_right.size()) results_right.push_back({l, previous});
        else results_right[l] = {l, previous};


        result = lower_bound(results_right.begin(),results_right.end(),make_pair(0,current-K),compare_more) - 1;
        l = result->first + 1;

        // update max_l
        max_l = max(max_l,help_l+l);

        // // Update results_right
        // if (l == results_right.size()) results_right.push_back({l, current-K});
        // else results_right[l] = {l, current-K};
    }

    cout << max_l << endl;
}