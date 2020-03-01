#include <vector>
#include <iostream>

using namespace std;

class NumArray
{
public:
    NumArray(vector<int> &nums)
    {
        sums.push_back(nums[0]);
        for (int i = 1; i <= nums.size(); i++)
            sums[i] = sums[i - 1] + nums[i];
    }

    int sumRange(int i, int j)
    {
        return sums[j + 1] - sums[i];
    }

private:
    vector<int> sums;
};


int main(){
    vector<int> nums;
    nums.push_back(-2);
    nums.push_back(0);
    nums.push_back(3);
    nums.push_back(-5);
    nums.push_back(2);
    nums.push_back(-1);
    NumArray * obj = new NumArray(nums);
    cout << obj->sumRange(0, 2) << endl;
    cout << obj->sumRange(2, 5) << endl;
    cout << obj->sumRange(0, 5) << endl;
}