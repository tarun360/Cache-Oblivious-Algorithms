#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode* sortedArrayToBST(vector<int>& nums, int s, int e) {
  if(s>e)
    return NULL;
  int m=(s+e)/2;
  TreeNode* temp = new TreeNode(nums[m]);
  temp->left = sortedArrayToBST(nums,s,m-1);
  temp->right = sortedArrayToBST(nums,m+1,e);
  return temp;
}

int GetHeight(TreeNode* root){
  if(root==NULL)
    return 0;
  else
    return max(1+GetHeight(root->left),1+GetHeight(root->right));
}

void dfs(TreeNode* root, int curlevel, int targetlevel, vector<TreeNode*>& BottomNodes){
  if(root==NULL)
    return;
  if(curlevel == targetlevel){
    BottomNodes.push_back(root);
    return;
  }
  dfs(root->left,curlevel+1,targetlevel,BottomNodes);
  dfs(root->right,curlevel+1,targetlevel,BottomNodes);
}

void GetVEBLayout(TreeNode* root, int leveltop, int levelbottom, vector<TreeNode*>& VEBlayout){
  if(leveltop==levelbottom){
    VEBlayout.push_back(root);
    return;
  }
  int leveldiv = (leveltop+levelbottom)/2;
  GetVEBLayout(root,leveltop,leveldiv,VEBlayout);
  vector<TreeNode*> BottomNodes;
  dfs(root,leveltop,leveldiv+1,BottomNodes);
  for(auto it:BottomNodes){
    GetVEBLayout(it,leveldiv+1,levelbottom,VEBlayout);
  }
}

bool VEBSearch(TreeNode *root, int key, vector<TreeNode>& VEBarray){
  if(root==NULL)
   return false;
  if(root->val == key)
    return true;
  else if(key < root->val)
    return VEBSearch(root->left,key,VEBarray);
  else
    return VEBSearch(root->right,key,VEBarray);
}

void inorder(TreeNode* root){
  if(root==NULL)
    return;
  inorder(root->left);
  cout<<root->val<<" ";
  inorder(root->right);
}

int main()
{
  int n,key;
  cin>>n;
  vector<int> nums(n);
  for(int i=0;i<n;i++)
    cin>>nums[i];
  cin>>key;
  TreeNode* root = sortedArrayToBST(nums,0,n-1);
  int levelmax = GetHeight(root)-1;
  vector<TreeNode*> VEBlayout;
  GetVEBLayout(root,0,levelmax,VEBlayout);
  vector<TreeNode> VEBarray;
  vector<TreeNode*> address(n+1,NULL);
  for(auto it:VEBlayout){
    TreeNode temp(it->val);
    VEBarray.push_back(temp);
  }
  for(int i=0;i<VEBarray.size();i++)
    address[VEBarray[i].val] = &VEBarray[i];
  for(int i=0;i<n;i++){
    if(VEBlayout[i]->left!=NULL){
      VEBarray[i].left = address[VEBlayout[i]->left->val];
    }
    if(VEBlayout[i]->right!=NULL){
      VEBarray[i].right = address[VEBlayout[i]->right->val];
    }
  }

  if(VEBSearch(addressof(VEBarray[0]),key,VEBarray)){
    cout<<"Element Found\n";
  }else
    cout<<"Element Not Found\n";

  return 0;
}
