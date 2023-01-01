#include <iostream>
#include <vector>
#include <list>
#include <inttypes.h>
#include <utility>
#include <limits> 

using namespace std;

typedef pair<int,int> pii;
int N, temp1, temp2, temp3, current, nodes_done;
vector<list<pii>> neighbours;
vector<int> parents, Dist_to_parent, P, S;
vector<uint64_t> Dist_to_root, results;

uint64_t solve_memo(int node) {
    if (!node) return 0;
    if (results[node]) return results[node];
    uint64_t minimum = numeric_limits<uint64_t>::max();
    // cout << "NODE " << node << " is being calculated" << endl;;
    for (int x=parents[node]; x!=-1; x=parents[x]) {
        // cout << x << endl;
        minimum = min( minimum, solve_memo(x) + S[node] * ( Dist_to_root[node] - Dist_to_root[x] ) );
        // cout << "AAAA: " << results[0] << " " << results[1] << " " << results[2] << " " << results[3] << " " << results[4]  << endl;
    }
    
    nodes_done++;
    minimum += P[node];
    return results[node] = minimum;
}

int main() {
    cin >> N;

    parents.resize(N);
    Dist_to_parent.resize(N);
    Dist_to_root.resize(N);
    P.resize(N);
    S.resize(N);
    neighbours.resize(N);
    results.resize(N,0);

    // Get input and construct undirected graph
    for (int i=0; i<N-1; ++i) {
        cin >> temp1 >> temp2 >> temp3;
        neighbours[temp1-1].push_back({temp2-1,temp3});
        neighbours[temp2-1].push_back({temp1-1,temp3});
    }

    // Get rest of input
    for (int i=1; i<N; ++i)
        cin >> P[i] >> S[i];

    parents[0] = -1;
    Dist_to_parent[0] = Dist_to_root[0] = results[0] = 0;

    // Determine parents with BFS
    // Mark all the vertices as not visited
    vector<bool> visited;
    visited.resize(N, false);

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[0] = true;
    queue.push_back(0);

    while (!queue.empty()) {
        // Dequeue a vertex from queue and print it
        current = queue.front();
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (const auto& adjacent : neighbours[current]) {
            const int &temp = adjacent.first;
            if (!visited[temp]) {
                visited[temp] = true;
                parents[temp] = current;
                Dist_to_parent[temp] = adjacent.second;
                Dist_to_root[temp] = Dist_to_root[current]+adjacent.second;
                queue.push_back(temp);
            }
        }
    }

    // Find answer for everyone using memoisation
    nodes_done=1;
    for (int i=1; nodes_done<N; ++i) solve_memo(i);
    
    // Output results
    for (int i=1; i<N-1; ++i) cout << results[i] << " ";
    cout << results[N-1] << endl;
}