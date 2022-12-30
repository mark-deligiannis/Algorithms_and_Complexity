#include <iostream>  
  
using namespace std;  
  
int N, K, *table, *best, res=-1;  
  
int main() {  
    // get input  
    cin >> N >> K;  
    table = new int[N];  
    best = new int[K];  
  
    for (int i=0; i<N; ++i)  
    {  
        cin >> table[i];  
        if (table[i]==K) {  
            cout << 1 << endl;  
            return 0;  
        }  
    }  
    // end get input  
  
    // zero out best  
    for (int i=0; i<K; ++i)   
        best[i] = 0;  
  
    for (int i=1; i<N; ++i)  
    {  
        // update best  
        int sum = 0;  
        for (int j=i-1; j>=0; --j)  
        {  
            sum += table[j];  
            if (sum>K) break;  
            if (sum==0) continue;  
            int &elem = best[sum-1];  
            if (!elem || i-j < elem) elem = i-j;  
        }  
  
        sum = 0;  
        // deal with intervals [i,something]  
        for (int j=i; j<N; ++j)  
        {  
            sum += table[j];  
            if (sum>K) break;  
            int curr_len = j-i+1;  
            if (sum!=K)  
            {      
                int &elem = best[K-sum-1];  
                if (!elem) continue;  
                curr_len += elem;  
            }  
            if (res==-1 || curr_len<res) res = curr_len;   
        }  
    }  
  
    // free memory  
    delete[] best;  
    delete[] table;  
  
    cout << res << endl;  
  
}  