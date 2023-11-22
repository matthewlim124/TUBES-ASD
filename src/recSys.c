#include "recSys.h"

// Sigmoid function
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// Function to make predictions using the logistic regression model
double predictModel(double features[], LogisticRegressionModel model, int numFeatures) {
    double prediction = model.bias;
    for (int i = 0; i < numFeatures; ++i) {
        prediction += model.weights[i] * features[i];
    }
    return sigmoid(prediction);
}

// Function to initialize the logistic regression model
void initializeModel(LogisticRegressionModel *model, int numFeatures) {
    for (int i = 0; i < numFeatures; i++) {
        model->weights[i] = 0.0;
    }
    model->bias = 0.0;
}

// Function to train the logistic regression model
void trainModel(DataPoint *data, int numSamples, int numFeatures, LogisticRegressionModel *model) {
    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        // Gradient descent update
        for (int i = 0; i < numSamples; i++) {
            double prediction = model->bias;
            for (int j = 0; j < numFeatures; j++) {
                prediction += model->weights[j] * data[i].features[j];
            }

            double error = sigmoid(prediction) - data[i].label;
            model->bias -= LEARNING_RATE * error;
            for (int j = 0; j < numFeatures; ++j) {
                model->weights[j] -= LEARNING_RATE * error * data[i].features[j]/ numSamples;
            }
        }
    }
}

