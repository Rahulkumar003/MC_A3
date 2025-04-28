#include "matrix_operations.h"
#include <Eigen/Dense>
#include <jni.h>
#include <vector>
#include <android/log.h>

#define LOG_TAG "MatrixOperations"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

using namespace Eigen;

// Helper function to convert Java array to Eigen Matrix
MatrixXd jArrayToMatrix(JNIEnv *env, jdoubleArray jArray, jint rows, jint cols) {
    jdouble *elements = env->GetDoubleArrayElements(jArray, nullptr);
    MatrixXd matrix(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix(i, j) = elements[i * cols + j];
        }
    }

    env->ReleaseDoubleArrayElements(jArray, elements, 0);
    return matrix;
}

// Helper function to convert Eigen Matrix to Java array
jdoubleArray matrixToJArray(JNIEnv *env, const MatrixXd &matrix) {
    int rows = matrix.rows();
    int cols = matrix.cols();
    jdoubleArray result = env->NewDoubleArray(rows * cols);

    jdouble *elements = new jdouble[rows * cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            elements[i * cols + j] = matrix(i, j);
        }
    }

    env->SetDoubleArrayRegion(result, 0, rows * cols, elements);
    delete[] elements;

    return result;
}

extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_matrixcalculator_MatrixOperations_addMatrices(
        JNIEnv *env, jobject /* this */,
        jdoubleArray jMatrix1, jint rows1, jint cols1,
        jdoubleArray jMatrix2, jint rows2, jint cols2) {

    try {
        // Check dimensions
        if (rows1 != rows2 || cols1 != cols2) {
            LOGE("Matrix addition error: Dimensions don't match");
            return nullptr;
        }

        // Convert Java arrays to Eigen matrices
        MatrixXd matrix1 = jArrayToMatrix(env, jMatrix1, rows1, cols1);
        MatrixXd matrix2 = jArrayToMatrix(env, jMatrix2, rows2, cols2);

        // Perform addition
        MatrixXd result = matrix1 + matrix2;

        // Convert result back to Java array
        return matrixToJArray(env, result);
    } catch (const std::exception& e) {
        LOGE("Matrix addition exception: %s", e.what());
        return nullptr;
    }
}

extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_matrixcalculator_MatrixOperations_subtractMatrices(
        JNIEnv *env, jobject /* this */,
        jdoubleArray jMatrix1, jint rows1, jint cols1,
        jdoubleArray jMatrix2, jint rows2, jint cols2) {

    try {
        // Check dimensions
        if (rows1 != rows2 || cols1 != cols2) {
            LOGE("Matrix subtraction error: Dimensions don't match");
            return nullptr;
        }

        // Convert Java arrays to Eigen matrices
        MatrixXd matrix1 = jArrayToMatrix(env, jMatrix1, rows1, cols1);
        MatrixXd matrix2 = jArrayToMatrix(env, jMatrix2, rows2, cols2);

        // Perform subtraction
        MatrixXd result = matrix1 - matrix2;

        // Convert result back to Java array
        return matrixToJArray(env, result);
    } catch (const std::exception& e) {
        LOGE("Matrix subtraction exception: %s", e.what());
        return nullptr;
    }
}

extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_matrixcalculator_MatrixOperations_multiplyMatrices(
        JNIEnv *env, jobject /* this */,
        jdoubleArray jMatrix1, jint rows1, jint cols1,
        jdoubleArray jMatrix2, jint rows2, jint cols2) {

    try {
        // Check dimensions for multiplication
        if (cols1 != rows2) {
            LOGE("Matrix multiplication error: Incompatible dimensions");
            return nullptr;
        }

        // Convert Java arrays to Eigen matrices
        MatrixXd matrix1 = jArrayToMatrix(env, jMatrix1, rows1, cols1);
        MatrixXd matrix2 = jArrayToMatrix(env, jMatrix2, rows2, cols2);

        // Perform multiplication
        MatrixXd result = matrix1 * matrix2;

        // Convert result back to Java array
        return matrixToJArray(env, result);
    } catch (const std::exception& e) {
        LOGE("Matrix multiplication exception: %s", e.what());
        return nullptr;
    }
}

extern "C" JNIEXPORT jdoubleArray JNICALL
Java_com_example_matrixcalculator_MatrixOperations_divideMatrices(
        JNIEnv *env, jobject /* this */,
        jdoubleArray jMatrix1, jint rows1, jint cols1,
        jdoubleArray jMatrix2, jint rows2, jint cols2) {

    try {
        // For division, we multiply matrix1 by the inverse of matrix2
        // This means matrix2 must be square
        if (rows2 != cols2) {
            LOGE("Matrix division error: Second matrix must be square");
            return nullptr;
        }

        // Convert Java arrays to Eigen matrices
        MatrixXd matrix1 = jArrayToMatrix(env, jMatrix1, rows1, cols1);
        MatrixXd matrix2 = jArrayToMatrix(env, jMatrix2, rows2, cols2);

        // Check if matrix2 is invertible
        double determinant = matrix2.determinant();
        if (std::abs(determinant) < 1e-10) {
            LOGE("Matrix division error: Second matrix is not invertible");
            return nullptr;
        }

        // For A/B, we compute A * B^-1
        // First, compute the inverse of matrix2
        MatrixXd matrix2Inv = matrix2.inverse();

        // Now check dimensions for multiplication
        if (cols1 != rows2) {
            LOGE("Matrix division error: Incompatible dimensions for multiplication");
            return nullptr;
        }

        // Perform division (multiplication by inverse)
        MatrixXd result = matrix1 * matrix2Inv;

        // Convert result back to Java array
        return matrixToJArray(env, result);
    } catch (const std::exception& e) {
        LOGE("Matrix division exception: %s", e.what());
        return nullptr;
    }
}