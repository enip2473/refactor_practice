#include<bits/stdc++.h>
using namespace std;

vector<int> manacher(vector<int> &arr){
    vector<int> m(2 * arr.size() + 1, -1);
    vector<int> max_len(2 * arr.size() + 1, 0);
    int n = arr.size();
    int idx = 0;
    for(int i = 0; i < n; i++){
        m[idx++] = -1; 
        m[idx++] = arr[i];
    }
    m[idx++] = -1;

    for(int i = 0, l = 0, r = -1; i < idx; i++) {
		max_len[i] = (i <= r ? min(max_len[2 * l - i], r - i) : 0);
		while(i - max_len[i] >= 0 && i + max_len[i] < idx && m[i - max_len[i]] == m[i + max_len[i]]) max_len[i]++;
		max_len[i]--;
		if(i + max_len[i] > r) l = i, r = i + max_len[i];
	}
    return max_len;
}

vector<int> get_maxr(vector<int> &max_len) {
    vector<int> ans(max_len.size() / 2);
    queue<pair<int, int>> q;
    int n = ans.size();
    // first 存放中點位置, second 存放以中點為回文中心能達到的最右位置
    // 因為是 manacher 後的陣列，i - q.front().first (中點) + 1 即為回文長度
    for(int i = 0; i < 2 * n + 1; i++){
        while(!q.empty() && q.front().second < i) q.pop();
        if(i % 2 == 1){
            if(q.empty()) ans[i / 2] = 1;
            else ans[i / 2] = (i - q.front().first + 1);
        }
        if(q.empty() || i + max_len[i] > q.back().second){
            q.push({i, i + max_len[i]});
        }
    }
    return ans;
}

int main(){
    int tmp;
    vector<int> arr;
    while(cin >> tmp) arr.push_back(tmp);
    
    int n = arr.size();
    vector<int> max_len = manacher(arr);
    vector<int> ansr = get_maxr(max_len);
    reverse(max_len.begin(), max_len.end());
    vector<int> ansl = get_maxr(max_len);
    reverse(ansl.begin(), ansl.end());

    // ansr[i] : 以 i 為右界的最長回文

    // 枚舉相鄰兩項作為第一回文結尾與第二回文頭
    int al = -1, ar = -1;
    for(int i = 0; i < n - 1; i++){
        if(ansr[i] + ansl[i+1] > ar - al + 1){
            al = i - ansr[i] + 1;
            ar = i + ansl[i+1];
        }
        else if(ansr[i] + ansl[i+1] == ar - al + 1 && i - ansr[i] + 1 > al){
            al = i - ansr[i] + 1;
            ar = i + ansl[i+1];
        }
    }

    if (ansr[n - 1] >= ar - al + 1) al = n - ansr[n - 1], ar = n - 1;

    for(int i = al; i <= ar; i++){
        if(i != al) printf(" ");
        printf("%d", arr[i]);
    }
    printf("\n");
}