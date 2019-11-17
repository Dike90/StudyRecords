/*
给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

注意：

答案中不可以包含重复的四元组。

示例：

给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

满足要求的四元组集合为：
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
思路：类似三数之和，首先排序，然后固定两个索引i,j,再使用另外两个索引L，R来遍历整个数组；
其中，L = j+1 ,R 指向数组结尾。 
注意要去重。
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int len = nums.size();
        for(int i = 0; i < len - 3 ; i++ ){
            //if(nums[i] > target) break;
            if ( i > 0 && nums[i-1] == nums[i]) continue;
            for (int j = i + 1; j < len - 2; j++ ) {
                if ( j > i + 1 && nums[j-1] == nums[j]) continue;               
                int L = j + 1;
                int R = len - 1;
                while(L < R) {
                    int sum = nums[i] + nums[j] + nums[L] +nums[R];
                    if(sum == target) {
                        res.push_back({nums[i],nums[j],nums[L],nums[R]});
                        while(L < R && nums[L] == nums[L + 1]) L++;
                        while(L < R && nums[R-1] == nums[R]) R--; 
                        L++;
                        R--;
                    }
                    else if(sum > target){
                        R--;
                    }
                    else{
                        L++;
                    }
                }
            }
        }
        return res;
    }
};