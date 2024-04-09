#include<bits/stdc++.h>
using namespace std;

int arr[105], ansl[105], ansr[105], m[205], max_len[205];

// ansl[i] : 以 i 為左端點的最長回文
// ansr[i] : 以 i 為右端點的最長回文

const int INF = -1;
void manacher(int n){
    int idx = 0;
    for(int i = 1; i <= n; i++){
        idx++;
        m[idx] = INF; 
        idx++;
        m[idx] = arr[i];
    }
    idx++;
    m[idx] = INF;

    for(int i = 1, l = 0, r = -1; i <= idx; i++) {
		max_len[i] = (i <= r ? min(max_len[2 * l - i], r - i) : 0);
		while(i - max_len[i] >= 1 && i + max_len[i] <= idx && m[i - max_len[i]] == m[i + max_len[i]]) max_len[i]++;
		max_len[i]--;
		if(i + max_len[i] > r) l = i, r = i + max_len[i];
	}
}

int main(){
    int tmp, n = 0;
    while(scanf("%d", &tmp) != EOF){
        n++;
        arr[n] = tmp; 
    }
    
    manacher(n);

    queue<pair<int, int>> q;
    // first 存放中點位置, second 存放以中點為回文中心能達到的最右位置
    // 因為是 manacher 後的陣列，i - q.front().first (中點) + 1 即為回文長度
    for(int i = 1; i <= 2 * n + 1; i++){
        while(!q.empty() && q.front().second < i) q.pop();
        if(i % 2 == 0){
            if(q.empty()) ansr[i / 2] = 1;
            else ansr[i / 2] = i - q.front().first + 1;
        }
        if(q.empty() || i + max_len[i] > q.back().second){
            q.push({i, i + max_len[i]});
        }
    }

    reverse(max_len + 1, max_len + 2 * n + 2);

    while(!q.empty()) q.pop();
    for(int i = 1; i <= 2 * n + 1; i++){
        while(!q.empty() && q.front().second < i) q.pop();
        if(i % 2 == 0){
            if(q.empty()) ansl[n + 1 - (i / 2)] = 1;
            else ansl[n + 1 - (i / 2)] = i - q.front().first + 1;
        }
        if(q.empty() || i + max_len[i] > q.back().second){
            q.push({i, i + max_len[i]});
        }
    }    
    // 枚舉相鄰兩項作為第一回文結尾與第二回文頭
    int al = -1, ar = -1;
    for(int i = 1; i <= n; i++){
        if(ansr[i] + ansl[i+1] > ar - al + 1){
            al = i - ansr[i] + 1;
            ar = i + ansl[i+1];
        }
        else if(ansr[i] + ansl[i+1] == ar - al + 1 && i - ansr[i] + 1 > al){
            al = i - ansr[i] + 1;
            ar = i + ansl[i+1];
        }
    }

    for(int i = al; i <= ar; i++){
        if(i != al) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}