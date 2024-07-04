/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    bool res = false;
    if(p == NULL && q == NULL)res = true;;
    
    if((p != NULL && q != NULL) && (p->val == q->val)){
        if(isSameTree((p->left),(q->left)))
               res = isSameTree((p->right),(q->right));       
    }
    
    return res;
    
}