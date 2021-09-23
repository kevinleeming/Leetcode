class Solution {
public:
    int maxLength(vector<string>& arr) {
        vector<int> vl;
        for(auto& s: arr){
            int m = 0;
            for(const char c: s) m |= (1 << (c-'a'));
            if(__builtin_popcount(m) != s.size()) continue;
            vl.push_back(m);
        }
        
        int ans = 0;
        dfs(0, 0, &ans, vl);
        return ans;
    }
    void dfs(int i, int m, int* a, vector<int>& v){
        *a = max(*a, __builtin_popcount(m));
        for(int j = i; j < v.size(); j++){
            if(m & v[j]) continue;
            dfs(j+1, m | v[j], a, v);
        }
    }
};