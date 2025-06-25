@echo off
echo ========================================
echo Order Management System - Test Runner
echo ========================================

:: Check if build directory exists
if not exist "build" (
    echo Creating build directory...
    mkdir build
)

cd build

:: Configure CMake (adjust vcpkg path as needed)
echo Configuring CMake...
if defined VCPKG_ROOT (
    cmake .. -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
) else (
    echo Warning: VCPKG_ROOT not set. Attempting standard configuration...
    cmake ..
)

if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

:: Build the project
echo Building project...
cmake --build . --config Release

if %ERRORLEVEL% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

:: Check if test executable exists
if exist "Release\OrderManagementTests.exe" (
    set TEST_EXE=Release\OrderManagementTests.exe
) else if exist "OrderManagementTests.exe" (
    set TEST_EXE=OrderManagementTests.exe
) else (
    echo Test executable not found! Google Test may not be installed.
    echo Building main application instead...
    cmake --build . --target OrderManagement
    
    if exist "Release\OrderManagement.exe" (
        echo Main application built successfully: Release\OrderManagement.exe
    ) else if exist "OrderManagement.exe" (
        echo Main application built successfully: OrderManagement.exe
    )
    pause
    exit /b 0
)

:: Run tests
echo Running tests...
echo ========================================
%TEST_EXE% --gtest_output=verbose

if %ERRORLEVEL% equ 0 (
    echo ========================================
    echo All tests passed successfully!
) else (
    echo ========================================
    echo Some tests failed. Check output above.
)

echo.
echo Test execution completed.
pause 