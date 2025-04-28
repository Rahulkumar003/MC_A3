The **Matrix Calculator** is an Android application designed to perform basic matrix operations such as addition, subtraction, multiplication, and division. It provides a simple and intuitive interface for users to input matrix dimensions and elements, select operations, and view the results.

## Features

- Input dimensions and elements for two matrices.
- Perform the following operations:
  - Matrix Addition
  - Matrix Subtraction
  - Matrix Multiplication
  - Matrix Division
- Display results in a formatted matrix view.
- Error handling for invalid inputs and incompatible matrix operations.

## Technologies Used

- **Languages**: Kotlin (Android), C++ (Native operations via JNI)
- **Frameworks**: Android SDK
- **Build System**: Gradle
- **UI Components**: Android Views (EditText, TextView, RadioGroup, Button, etc.)

## Project Structure

- **`app/src/main/java/com/example/myapplication/MainActivity.kt`**: Contains the main activity logic, including UI initialization and matrix operation handling.
- **`app/src/main/res/layout/activity_main.xml`**: Defines the user interface for the main activity.
- **`app/src/main/cpp/`**: Contains native C++ code for matrix operations.
- **`app/build.gradle.kts`**: Gradle build script for configuring dependencies and build settings.
- **`app/src/main/AndroidManifest.xml`**: Configures the application metadata and entry point.

## How to Use

1. **Input Matrix Dimensions**:
   - Enter the number of rows and columns for both matrices.

2. **Input Matrix Elements**:
   - Provide the matrix elements separated by spaces.

3. **Select an Operation**:
   - Choose an operation (Add, Subtract, Multiply, Divide) using the radio buttons.

4. **Calculate**:
   - Press the "Calculate" button to perform the operation.

5. **View Results**:
   - The result will be displayed in the "Result" section.

## Prerequisites

- Android Studio installed on your system.
- Minimum SDK version: 24
- Target SDK version: 35

## Build and Run

1. Clone the repository to your local machine.
2. Open the project in Android Studio.
3. Sync the Gradle files.
4. Build the project using `Build > Make Project`.
5. Run the app on an emulator or a physical device.

## Troubleshooting

- **Unresolved reference: `R`**: Ensure there are no errors in your XML files and rebuild the project.
- **JNI Errors**: Verify that the native C++ code is correctly compiled and linked using the `CMakeLists.txt` file.

