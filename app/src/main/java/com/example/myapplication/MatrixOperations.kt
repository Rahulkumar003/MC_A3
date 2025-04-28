package com.example.myapplication


class MatrixOperations {
    // Load native library
    companion object {
        init {
            System.loadLibrary("matrix_operations")
        }
    }

    // Native methods
    external fun addMatrices(
        matrix1: DoubleArray, rows1: Int, cols1: Int,
        matrix2: DoubleArray, rows2: Int, cols2: Int
    ): DoubleArray?

    external fun subtractMatrices(
        matrix1: DoubleArray, rows1: Int, cols1: Int,
        matrix2: DoubleArray, rows2: Int, cols2: Int
    ): DoubleArray?

    external fun multiplyMatrices(
        matrix1: DoubleArray, rows1: Int, cols1: Int,
        matrix2: DoubleArray, rows2: Int, cols2: Int
    ): DoubleArray?

    external fun divideMatrices(
        matrix1: DoubleArray, rows1: Int, cols1: Int,
        matrix2: DoubleArray, rows2: Int, cols2: Int
    ): DoubleArray?

    // Helper method to convert matrix to string for display
    fun matrixToString(matrix: DoubleArray?, rows: Int, cols: Int): String {
        if (matrix == null) return "Invalid operation"

        val sb = StringBuilder()
        for (i in 0 until rows) {
            sb.append("| ")
            for (j in 0 until cols) {
                val value = matrix[i * cols + j]
                sb.append(String.format("%.2f ", value))
            }
            sb.append("|\n")
        }
        return sb.toString()
    }
}