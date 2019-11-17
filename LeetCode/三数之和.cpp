/*
给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
思路：首先排序，然后固定一个索引i,再使用另外两个索引L，R来遍历整个数组；
其中，L = i+1 ,R 指向数组结尾。 
注意要去重。
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int len = nums.size();
        sort(nums.begin(), nums.end());
        for(int i = 0; i < len; i++) {
            if(nums[i] > 0 ) break; //若第一个元素就大于0，那么后面再加啥也大于0了，结束遍历
            if( i > 0 && nums[i-1] == nums[i]) continue; //去重，注意第一次是可以重复的
            int L = i + 1;
            int R = len - 1;
            while(L < R){
                int sum = nums[i] + nums[L] + nums[R];
                if(sum == 0){
                    vector<int> tmp;
                    tmp.push_back(nums[i]);
                    tmp.push_back(nums[L]);
                    tmp.push_back(nums[R]);
                    res.push_back(tmp);
                    while(L < R && nums[L] == nums[L+1]) L++;
                    while(L < R  && nums[R-1] == nums[R]) R--;
                    L++;
                    R--;
                }
                else if (sum < 0){
                    
                    L++;
                }
                else if (sum > 0){
                    
                    R--;
                }
            }
        }
        return res;
    }
   
};