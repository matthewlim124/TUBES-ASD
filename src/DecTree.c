#include "DecTree.h"
#include <stdio.h>
#include <stdlib.h>
// Function to free the memory used by the decision tree
void freeTree(TreeNode* root) {
  if (root == NULL) {
        return;
  }
  freeTree(root->left);
  freeTree(root->right);
  free(root);
}

double calculateGiniImpurity(int *labels, int numSamples){
  double impurity = 1.0; 
  for(int i = 0; i<=1; i++){
    double classProb=0; // Count when class is 0 or 1; 

    for(int j =0; j<numSamples; j++){
      if(labels[j] == i){
        classProb += 1;
      }
    }
    classProb/= numSamples; 
    impurity -= classProb * classProb;
  }
  return impurity;
}

void findBestSplit(double features[][MAX_FEATURES], int *labels, int numSamples, int numFeatures, int *bestFeatureIndex, double *bestThreshold){
  double minGini = 9999; //Random Max Value; 
  for(int featureIndex = 0; featureIndex< numFeatures; featureIndex++){
    for(int sampleIndex= 0; sampleIndex< numSamples; sampleIndex++){
      double threshold = features[sampleIndex][featureIndex];

      int leftCount =0; 
      int rightCount =0; 

      int leftClassCount[2] = {0};
      int rightClassCount[2] = {0};
      
      for(int i = 0; i < numSamples; i++){
        if(features[i][featureIndex] <= threshold){
          leftCount++; 
          leftClassCount[labels[i]]++;
        }
        else{
          rightCount++;
          rightClassCount[labels[i]]++;
        }
      }

      double leftGini = calculateGiniImpurity(leftClassCount, leftCount);
      double rightGini = calculateGiniImpurity(rightClassCount, rightCount);
      double weightedGini = (leftCount*leftGini + rightCount*rightGini)/numSamples;

      if(weightedGini < minGini){
        minGini = weightedGini; 
        *bestThreshold = threshold; 
        *bestFeatureIndex = featureIndex; 
      }
    }
  }
}

TreeNode* train(double features[][MAX_FEATURES], int* labels, int numSamples, int numFeatures){
  TreeNode* node =  (TreeNode*) malloc(sizeof(TreeNode));
  //Checking for unique label 
  int uniqueLabelCount =0; 
  int uniqueLabel = -1; //Random value for unique label
  
  //Check if already one label per node 
  for(int i = 0; i < numSamples; i++){
    if(uniqueLabelCount ==0 || uniqueLabel == labels[i]){
      uniqueLabelCount++; 
      uniqueLabel = labels[i];
    }
    else{
      break;
    }
  }
  
  if(uniqueLabelCount == 1){
    node->featureIndex = -1; 
    node->left = NULL; 
    node->predictedClass = uniqueLabel; 
    node->right = NULL;
    node->threshold =0; 
  }
  else{
    int bestFeatureIndex; double bestThreshold; 
    findBestSplit(features, labels, numSamples, numFeatures, &bestFeatureIndex, &bestThreshold);

    int leftCount = 0;
    int rightCount = 0;

    for (int i = 0; i < numSamples; i++) {
      if (features[i][bestFeatureIndex] <= bestThreshold) {
        leftCount++;
      } 
      else{
        rightCount++;
      }
    }

    //Allocate memory for left and right subsets
    double leftFeatures[leftCount][numFeatures];
    double rightFeatures[rightCount][numFeatures];
    int leftLabels[leftCount];
    int rightLabels[rightCount];

    // Split the data
    int leftIndex = 0;
    int rightIndex = 0;

    for (int i = 0; i < numSamples; i++) {
      if (features[i][bestFeatureIndex] <= bestThreshold) {
        for (int j = 0; j < numFeatures; j++) {
          leftFeatures[leftIndex][j] = features[i][j];
        }
        leftLabels[leftIndex] = labels[i];
        leftIndex++;
      } 
      else{
        for (int j = 0; j < numFeatures; j++){
          rightFeatures[rightIndex][j] = features[i][j];
        }
        rightLabels[rightIndex] = labels[i];
        rightIndex++;
      }
    }
    node->featureIndex = bestFeatureIndex;
    node->threshold = bestThreshold;
    node->predictedClass = -1;
    node->left = train(leftFeatures, leftLabels, leftCount, numFeatures);
    node->right = train(rightFeatures, rightLabels, rightCount, numFeatures);
  }

  return node;
}

int predict(TreeNode* root, double* features) {
  if (root->left == NULL && root->right == NULL) {
    return root->predictedClass;
  }
  if (features[root->featureIndex] <= root->threshold) {
    return predict(root->left, features);
  } 
  else {
    return predict(root->right, features);
  }
}


