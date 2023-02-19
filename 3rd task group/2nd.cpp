#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <utility>
#include <limits>
#define N_MAX 1000
#define N_MAX_SQ N_MAX*N_MAX

using namespace std;
using std::cout;

typedef pair<int,int> pii;

// Globals
int N, M, B, s, t, temp1, temp2, temp3, answer, trans_u, u_dist;
int distances[N_MAX_SQ];
list<pii> neighbours[N_MAX];
vector<bool> visited;

struct compare_ht {
    bool operator() (const pii x, const pii y) { return x.second>y.second; }
};

priority_queue<pii, vector<pii>, compare_ht> pq;

int main() {
    cin >> N >> M >> s >> t >> B;
    s -= 1; t -= 1;
    answer = N;
    visited.resize(N*N, false);

    for (int i=0; i<M; i++) {
        cin >> temp1 >> temp2 >> temp3;
        neighbours[temp1-1].push_back({ temp2-1, temp3 });
    }

    int maximum = std::numeric_limits<int>::max();
    for (int i=0; i<N*N; i++) distances[i] = maximum;
    
    int trans_s = s;
    pq.push({trans_s, 0});
    distances[trans_s] = 0;

	while (!pq.empty()) {
		while (true) {
            if (pq.empty()) { cout << answer << endl; return 0; }
            auto x = pq.top();
            trans_u = x.first;
            u_dist = x.second;
            pq.pop();
            if (!visited[trans_u]) break;
        }
        visited[trans_u] = true;

        int u = trans_u % N, n_zeros = trans_u / N;

        if (n_zeros >= answer) continue;

        if (u == t)  {
            answer = n_zeros;
            continue;
        }

		for (const auto& x : neighbours[u]) {
			int v = x.first;
			int weight = x.second;
            int neigh = v + n_zeros*N;
            int candidate_v_weight = weight + u_dist;

            // Without zeroing out this edge
            if (candidate_v_weight <= B && distances[neigh] > candidate_v_weight) {
                // Updating distance of v
                distances[neigh] = candidate_v_weight;
                pq.push({ neigh, candidate_v_weight });
            }

            // With zeroing out of this edge
            if (n_zeros + 1 >= answer) continue;
            // adjust
            candidate_v_weight = u_dist;
            neigh+=N;
            // and repeat
            if (distances[neigh] > candidate_v_weight) {
                // Updating distance of v
                distances[neigh] = candidate_v_weight;
                pq.push({ neigh, candidate_v_weight });
            }
		}
	}

    cout << answer << endl;
}