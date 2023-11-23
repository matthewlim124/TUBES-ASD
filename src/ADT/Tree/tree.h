#define NiL_Tree NULL

typedef int ElType; 
typedef struct treeNode* Address;
typedef struct treeNode{
  ElType info; 
  Address left; 
  Address right; 
} TreeNode;

typedef Address BinTree;

