#include <iostream>
#include <vector>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        auto resl = levelOrderBottom(root->left);
        auto resr = levelOrderBottom(root->right);
        res.insert(res.end(), resl.begin(), resl.end());
        res.insert(res.end(), resr.begin(), resr.end());
        res.push_back({root->val});
        return res;
    }
};

int main()
{
    Solution s;
}
