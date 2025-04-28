package com.example.myapplication


import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.RadioGroup
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
class MainActivity : AppCompatActivity() {
    private lateinit var matrixOperations: MatrixOperations

    // UI Elements
    private lateinit var etRows1: EditText
    private lateinit var etCols1: EditText
    private lateinit var etRows2: EditText
    private lateinit var etCols2: EditText
    private lateinit var etMatrix1: EditText
    private lateinit var etMatrix2: EditText
    private lateinit var rgOperation: RadioGroup
    private lateinit var btnCalculate: Button
    private lateinit var tvResult: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Initialize native operations
        matrixOperations = MatrixOperations()

        // Initialize UI elements
        etRows1 = findViewById(R.id.etRows1)
        etCols1 = findViewById(R.id.etCols1)
        etRows2 = findViewById(R.id.etRows2)
        etCols2 = findViewById(R.id.etCols2)
        etMatrix1 = findViewById(R.id.etMatrix1)
        etMatrix2 = findViewById(R.id.etMatrix2)
        rgOperation = findViewById(R.id.rgOperation)
        btnCalculate = findViewById(R.id.btnCalculate)
        tvResult = findViewById(R.id.tvResult)

        // Set dimension update listeners
        val dimensionListener = { updateMatrixInputHint() }
        etRows1.setOnFocusChangeListener { _, hasFocus -> if (!hasFocus) dimensionListener() }
        etCols1.setOnFocusChangeListener { _, hasFocus -> if (!hasFocus) dimensionListener() }
        etRows2.setOnFocusChangeListener { _, hasFocus -> if (!hasFocus) dimensionListener() }
        etCols2.setOnFocusChangeListener { _, hasFocus -> if (!hasFocus) dimensionListener() }

        // Set calculate button listener
        btnCalculate.setOnClickListener {
            calculateResult()
        }
    }

    private fun updateMatrixInputHint() {
        try {
            val rows1 = etRows1.text.toString().toIntOrNull() ?: 0
            val cols1 = etCols1.text.toString().toIntOrNull() ?: 0
            val rows2 = etRows2.text.toString().toIntOrNull() ?: 0
            val cols2 = etCols2.text.toString().toIntOrNull() ?: 0

            if (rows1 > 0 && cols1 > 0) {
                etMatrix1.hint = "Enter ${rows1}x${cols1} matrix elements separated by spaces"
            }

            if (rows2 > 0 && cols2 > 0) {
                etMatrix2.hint = "Enter ${rows2}x${cols2} matrix elements separated by spaces"
            }
        } catch (e: Exception) {
            Toast.makeText(this, "Invalid dimensions", Toast.LENGTH_SHORT).show()
        }
    }

    private fun calculateResult() {
        try {
            // Parse dimensions
            val rows1 = etRows1.text.toString().toInt()
            val cols1 = etCols1.text.toString().toInt()
            val rows2 = etRows2.text.toString().toInt()
            val cols2 = etCols2.text.toString().toInt()

            // Validate dimensions
            if (rows1 <= 0 || cols1 <= 0 || rows2 <= 0 || cols2 <= 0) {
                Toast.makeText(this, "Dimensions must be positive", Toast.LENGTH_SHORT).show()
                return
            }

            // Parse matrix elements
            val matrix1 = parseMatrixInput(etMatrix1.text.toString(), rows1, cols1)
            val matrix2 = parseMatrixInput(etMatrix2.text.toString(), rows2, cols2)

            if (matrix1 == null || matrix2 == null) {
                Toast.makeText(this, "Invalid matrix input", Toast.LENGTH_SHORT).show()
                return
            }

            // Perform selected operation
            val resultArray = when (rgOperation.checkedRadioButtonId) {
                R.id.rbAdd -> matrixOperations.addMatrices(matrix1, rows1, cols1, matrix2, rows2, cols2)
                R.id.rbSubtract -> matrixOperations.subtractMatrices(matrix1, rows1, cols1, matrix2, rows2, cols2)
                R.id.rbMultiply -> matrixOperations.multiplyMatrices(matrix1, rows1, cols1, matrix2, rows2, cols2)
                R.id.rbDivide -> matrixOperations.divideMatrices(matrix1, rows1, cols1, matrix2, rows2, cols2)
                else -> null
            }

            // Display result
            if (resultArray != null) {
                // Determine result dimensions
                val resultRows = when (rgOperation.checkedRadioButtonId) {
                    R.id.rbMultiply, R.id.rbDivide -> rows1
                    else -> rows1 // For add and subtract, dimensions should be the same
                }

                val resultCols = when (rgOperation.checkedRadioButtonId) {
                    R.id.rbMultiply, R.id.rbDivide -> cols2
                    else -> cols1 // For add and subtract, dimensions should be the same
                }

                val resultStr = matrixOperations.matrixToString(resultArray, resultRows, resultCols)
                tvResult.text = "Result:\n$resultStr"
            } else {
                tvResult.text = "Error: Invalid operation for these matrices"
            }
        } catch (e: Exception) {
            Toast.makeText(this, "Error: ${e.message}", Toast.LENGTH_SHORT).show()
            tvResult.text = "Error: ${e.message}"
        }
    }

    private fun parseMatrixInput(input: String, rows: Int, cols: Int): DoubleArray? {
        try {
            val elements = input.trim().split(Regex("\\s+")).map { it.toDouble() }

            if (elements.size != rows * cols) {
                Toast.makeText(
                    this,
                    "Matrix input must have exactly ${rows * cols} elements",
                    Toast.LENGTH_SHORT
                ).show()
                return null
            }

            return elements.toDoubleArray()
        } catch (e: Exception) {
            return null
        }
    }
}