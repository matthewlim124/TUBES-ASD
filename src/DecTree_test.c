# include "DecTree.h"
int main() {
    // Example: Create a decision tree
    double features[][2] = {{1.0, 2.0}, {2.0, 3.0}, {3.0, 4.0}, {4.0, 5.0}};
    int labels[] = {0, 0, 1, 1};
    int numSamples = 4;
    int numFeatures = 2;

    TreeNode* root = train(features, labels, numSamples, numFeatures);

    // Example: Make a prediction
    double testFeatures[] = {3.5, 4.5};
    int prediction = predict(root, testFeatures);
    printf("Prediction: %d\n", prediction);

    // Example: Free the memory used by the decision tree
    freeTree(root);

    return 0;
}
