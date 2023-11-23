#include <stdio.h>
#include <stdlib.h>

#define MAX_FEATURES 10
// Example data structure to represent a decision tree node
typedef struct TreeNode {
    int featureIndex;
    double threshold;
    int predictedClass;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

double calculateGiniImpurity(int* labels, int numSamples);
void findBestSplit(double features[][MAX_FEATURES], int* labels, int numSamples, int numFeatures, int* bestFeatureIndex, double* bestThreshold);
TreeNode* train(double features[][MAX_FEATURES], int* labels, int numSamples, int numFeatures);
void freeTree(TreeNode* root);
int predict(TreeNode* root, double* features);
