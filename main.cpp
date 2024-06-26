#include<bits/stdc++.h>
using namespace std;

class PalindromeFinder {
private:
    vector<int> arr;

    vector<int> manacher() {
        int n = arr.size();
        int manacher_len = n * 2 + 1;
        vector<int> m(manacher_len, -1), max_len(manacher_len);
        for(int i = 0; i < n; i++) m[2 * i + 1] = arr[i];

        for(int i = 0, l = 0, r = -1; i < manacher_len; i++) {
            max_len[i] = (i <= r ? min(max_len[2 * l - i], r - i) : 0);
            while(i - max_len[i] >= 0 && i + max_len[i] < manacher_len && m[i - max_len[i]] == m[i + max_len[i]])
                max_len[i]++;
            max_len[i]--;
            if(i + max_len[i] > r) l = i, r = i + max_len[i];
        }
        return max_len;
    }

    vector<int> get_maxl(const vector<int> &max_len) {
        vector<int> ans(max_len.size() / 2);
        queue<pair<int, int>> q;
        int n = ans.size();
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

    vector<int> longest_two_palindrome() {
        vector<int> max_len = manacher();
        vector<int> maxl = get_maxl(max_len);
        reverse(max_len.begin(), max_len.end());
        vector<int> maxr = get_maxl(max_len);
        reverse(maxr.begin(), maxr.end());

        int n = arr.size();
        pair<int, int> max_length {maxr[0], 0};
        for (int i = 0; i < n - 1; i++) {
            pair<int, int> new_length {maxl[i] + maxr[i + 1], i - maxl[i] + 1};
            max_length = max(max_length, new_length);
        }
        auto answer_begin = arr.begin() + max_length.second;
        auto answer_end = arr.begin() + max_length.second + max_length.first;
        vector<int> answer;
        for (auto i = answer_begin; i != answer_end; i++) answer.push_back(*i);
        return answer;
    }

public:
    PalindromeFinder(const vector<int>& inputArr) : arr(inputArr) {}

    vector<int> findLongestTwoPalindrome() {
        return longest_two_palindrome();
    }
};

int main(){
    int tmp;
    vector<int> arr;
    while (cin >> tmp) arr.push_back(tmp);
    // Example input: 1 1 2 3 4 5 5 4 3 1 1 2 3
    
    PalindromeFinder finder(arr);
    vector<int> answer = finder.findLongestTwoPalindrome();

    for (int i = 0; i < (int)answer.size(); i++) {
        cout << answer[i];
        if (i != (int)answer.size() - 1) cout << " ";
        else cout << '\n';
    }

    // Example output: 3 4 5 5 4 3 1 1

    return 0;
}
