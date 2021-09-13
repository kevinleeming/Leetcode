vector<vector<int>> ans;
class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) { // Convex Hull : Graham-scan
        ans.clear();
        int startId = 0, startId2 = 0; // 分別為右下及左上的點id
        int p = 0;
        vector<int> temp;
        for(int i = 0; i < trees.size(); i++){ // 找出右下及左上點，作為找尋凸包的兩個起點
            if(comp(trees[i], trees[startId])) startId = i;
            if(compB(trees[i], trees[startId2])) startId2 = i;
        }
        temp = trees[startId2];
        ans.push_back(trees[startId]);
        sort(trees.begin(), trees.end(), compare_angle); // 以起點為中心，逆時針掃過所有點，依此為排序基準
        for(int i = 0; i < trees.size(); i++){
            while(p >= 2 && cross(ans[p-2], ans[p-1], trees[i]) < 0){ // 消除凹點
                p--;
                ans.pop_back();
            }
            p++;
            if(i) ans.push_back(trees[i]);
        }
        ans[0] = temp;
        sort(trees.begin(), trees.end(), compare_angle);
        p = 0;
        for(int i = 0; i < trees.size(); i++){
            while(p >= 2 && cross(ans[ans.size()-2], ans[ans.size()-1], trees[i]) < 0){
                p--;
                ans.pop_back();
            }
            p++;
            ans.push_back(trees[i]);
        }
        sort(ans.begin(), ans.end());
        ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
        return ans;
    }
    
    bool comp(vector<int>& pa, vector<int>& pb){ // Find the most left and bottom point
        return (pa[0] < pb[0]) || (pa[0] == pb[0] && pa[1] < pb[1]);
    }
    
    bool compB(vector<int>& pa, vector<int>& pb){ // Find the most right and top point
        return (pa[0] > pb[0]) || (pa[0] == pb[0] && pa[1] > pb[1]);
    }
    
    static int cross(vector<int>& o, vector<int>& a, vector<int>& b)
    {
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
    }
    
    static bool compare_angle(vector<int>& a, vector<int>& b)
    {
        int c = cross(ans[0], a, b);
        return c > 0 || (c == 0 && length2(ans[0], a) < length2(ans[0], b));
    }
    
    static int length2(vector<int>& a, vector<int>& b)
    {
        return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
    }
    
};