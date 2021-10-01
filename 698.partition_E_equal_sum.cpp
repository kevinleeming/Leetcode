class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int ac = 0;
        for(const int n: nums){
            ac += n;
        }
        if(ac % k) return false;
        int target = ac / k;
        sort(nums.begin(), nums.end(), [](int a, int b){
            return a > b;
        });
        for(int j = 0; j < k; j++){
            if(!findCompl(nums, nums.begin(), target)) return false;
        }
        return true;
    }
    
    bool findCompl(vector<int>& v, vector<int>::iterator begin, int target){
        for(auto i = begin; i != v.end(); i++){
            if(*i > target) continue;
            if(*i == target){
                v.erase(i);
                return true;
            } 
            if(i+1 == v.end()) return false;
            if(findCompl(v, i+1, target-*i)){
                v.erase(i);
                return true;
            }
        }
        return false;
    }
};
