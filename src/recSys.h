#include <stdio.h>
#include <math.h>

#define MAX_FEATURES 10
#define LEARNING_RATE 0.01
#define EPOCHS 1000

typedef struct {
    double features[MAX_FEATURES];
    int label;
} DataPoint;

// Structure to represent logistic regression model parameters
typedef struct {
    double weights[MAX_FEATURES];
    double bias;
} LogisticRegressionModel;

void initializeModel(LogisticRegressionModel *model, int numFeatures);

void trainModel(DataPoint *data, int numSamples, int numFeatures, LogisticRegressionModel *model);

double sigmoid(double x);

double predictModel(double features[], LogisticRegressionModel model, int numFeatures);
