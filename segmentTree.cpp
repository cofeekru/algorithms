#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class NumArray {
public:
    vector <int> segmentTree;
    int makeSegmentTree(int node) {
        if (2*node >= segmentTree.size()) {
            return segmentTree[node];
        } else {
            int l = makeSegmentTree(2*node);
            int r = makeSegmentTree(2*node + 1);
            segmentTree[node] = l + r;
            return l+r;
        }
    }
    
    NumArray(vector<int>& nums) {
        int exp = log2(nums.size()) + 1;
        int size = pow(2, exp);
        segmentTree.resize(2*size, 0);
        int nums_size = nums.size();
        for (int i = 0; i < nums_size; ++i) {
            segmentTree[size + i] = nums[i];
        }
        segmentTree[1] = makeSegmentTree(1);
        
    }
    
    void update(int index, int val) {
        int node = segmentTree.size()/2 + index;
        segmentTree[node] = val;
        while (node > 1) {
            node /= 2;
            segmentTree[node] = segmentTree[node*2] + segmentTree[node*2 + 1];
        }
    }
    int recursieSumRange(int l, int r, int lx, int rx, int node) {
        if (l <= lx && rx <= r) {
            return segmentTree[node];
        } else if (rx < l || lx > r) {
            return 0;
        } else {
            int middle = (rx + lx) / 2;
            return recursieSumRange(l, r, lx, middle, node * 2) + recursieSumRange(l, r, middle+1, rx, node * 2 + 1);
        }
    }
    int sumRange(int left, int right) {
        int result = recursieSumRange(left+1, right+1, 1, segmentTree.size()/2, 1);
        return result;
    }
};

int main() {
    vector <int> nums = {1,2,3,4,5};
    NumArray* obj = new NumArray(nums);
    //obj->update(2, 7);
    int result = obj->sumRange(1, 3);
    cout << result << endl;
}