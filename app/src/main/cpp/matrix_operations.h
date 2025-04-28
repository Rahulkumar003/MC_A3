#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include <jni.h>

extern "C" {
JNIEXPORT jdoubleArray JNICALL
Java_com_example_matrixcalculator_MatrixOperations_addMatrices(
        JNIEnv *env, jobject obj,
        jdoubleArray jMatrix1, jint rows1, jint cols1,
        jdoubleArray jMatrix2, jint rows2, jint cols2);

JNIEXPORT jdoubleArray JNICALL
Java_com_example_matrixcalculator_MatrixOperations_subtractMatrices(
        JNIEnv *env, jobject obj,
        jdoubleArray jMatrix1, jint rows1, jint cols1,
        jdoubleArray jMatrix2, jint rows2, jint cols2);

JNIEXPORT jdoubleArray JNICALL
Java_com_example_matrixcalculator_MatrixOperations_multiplyMatrices(
        JNIEnv *env, jobject obj,
        jdoubleArray jMatrix1, jint rows1, jint cols1,
        jdoubleArray jMatrix2, jint rows2, jint cols2);

JNIEXPORT jdoubleArray JNICALL
Java_com_example_matrixcalculator_MatrixOperations_divideMatrices(
        JNIEnv *env, jobject obj,
        jdoubleArray jMatrix1, jint rows1, jint cols1,
        jdoubleArray jMatrix2, jint rows2, jint cols2);
}

#endif // MATRIX_OPERATIONS_H