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

vector<int> get_maxl(vector<int> &max_len) {
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

vector<int> longest_two_palindrome(vector<int> &arr){
    vector<int> max_len = manacher(arr);
    vector<int> maxl = get_maxl(max_len);
    reverse(max_len.begin(), max_len.end());
    vector<int> maxr = get_maxl(max_len);
    reverse(maxr.begin(), maxr.end());

    int n = arr.size();
    pair<int, int> max_length {-1, -1}; // first: length, second: begin index
    for (int i = 0; i < n; i++) {
        pair<int, int> new_length {maxl[i] + maxr[i + 1], i - maxl[i] + 1};
        max_length = max(max_length, new_length);
    }
    auto answer_begin = arr.begin() + max_length.second;
    auto answer_end = arr.begin() + max_length.second + max_length.first;
    vector<int> answer(answer_begin, answer_end);
    return answer;
}

int main(){
    int tmp;
    vector<int> arr;
    while(cin >> tmp) arr.push_back(tmp);
    
    vector<int> answer = longest_two_palindrome(arr);

    for (int i = 0; i < (int) answer.size(); i++) {
        cout << answer[i];
        if (i != (int) answer.size() - 1) cout << " ";
        else cout << '\n';
    }
}