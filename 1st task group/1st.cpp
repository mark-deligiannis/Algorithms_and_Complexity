#include <iostream>

using namespace std;

int N, K, *table, *res_sum;

bool check_median(int median) {
    res_sum[0] = (table[0]>=median) ? 1 : -1;
    
    for (int i=1; i<N; ++i) 
        if (table[i]>=median)
            res_sum[i] = res_sum[i-1] + 1;
        else
            res_sum[i] = res_sum[i-1] - 1;
    
    int maximum = res_sum[K-1], minimum = 0;
    
    for (int i=K; i<N; ++i) {
        minimum = min(minimum, res_sum[i-K]);
        maximum = max(maximum, res_sum[i] - minimum);
    }

    return maximum > 0;
}

int main() {
    // get input
    cin >> N >> K;
    table = new int[N];
    res_sum = new int[N];

    for (int i=0; i<N; ++i)
        cin >> table[i];
    // end get input

    int ret = -1, st = 1, fin = N + 1, mid;
    while(st <= fin)
    {
        mid = (st + fin) / 2;
        if (check_median(mid))
        {
            ret = mid;
            st = mid + 1;
        }
        else fin = mid - 1;
    }

    // free memory
    delete[] res_sum;
    delete[] table;

    cout << ret << endl;
}