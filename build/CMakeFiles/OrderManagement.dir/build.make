# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\FCAI\GP\TESTREPOS\OrdersManagment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\FCAI\GP\TESTREPOS\OrdersManagment\build

# Include any dependencies generated for this target.
include CMakeFiles/OrderManagement.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OrderManagement.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OrderManagement.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OrderManagement.dir/flags.make

CMakeFiles/OrderManagement.dir/codegen:
.PHONY : CMakeFiles/OrderManagement.dir/codegen

CMakeFiles/OrderManagement.dir/src/main.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/main.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/main.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/main.cpp
CMakeFiles/OrderManagement.dir/src/main.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OrderManagement.dir/src/main.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/main.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\main.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\main.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\main.cpp

CMakeFiles/OrderManagement.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/main.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\main.cpp > CMakeFiles\OrderManagement.dir\src\main.cpp.i

CMakeFiles/OrderManagement.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/main.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\main.cpp -o CMakeFiles\OrderManagement.dir\src\main.cpp.s

CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/models/Customer.cpp
CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\models\Customer.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\models\Customer.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\Customer.cpp

CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\Customer.cpp > CMakeFiles\OrderManagement.dir\src\models\Customer.cpp.i

CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\Customer.cpp -o CMakeFiles\OrderManagement.dir\src\models\Customer.cpp.s

CMakeFiles/OrderManagement.dir/src/models/Product.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/models/Product.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/models/Product.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/models/Product.cpp
CMakeFiles/OrderManagement.dir/src/models/Product.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/OrderManagement.dir/src/models/Product.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/models/Product.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\models\Product.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\models\Product.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\Product.cpp

CMakeFiles/OrderManagement.dir/src/models/Product.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/models/Product.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\Product.cpp > CMakeFiles\OrderManagement.dir\src\models\Product.cpp.i

CMakeFiles/OrderManagement.dir/src/models/Product.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/models/Product.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\Product.cpp -o CMakeFiles\OrderManagement.dir\src\models\Product.cpp.s

CMakeFiles/OrderManagement.dir/src/models/Order.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/models/Order.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/models/Order.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/models/Order.cpp
CMakeFiles/OrderManagement.dir/src/models/Order.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/OrderManagement.dir/src/models/Order.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/models/Order.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\models\Order.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\models\Order.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\Order.cpp

CMakeFiles/OrderManagement.dir/src/models/Order.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/models/Order.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\Order.cpp > CMakeFiles\OrderManagement.dir\src\models\Order.cpp.i

CMakeFiles/OrderManagement.dir/src/models/Order.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/models/Order.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\Order.cpp -o CMakeFiles\OrderManagement.dir\src\models\Order.cpp.s

CMakeFiles/OrderManagement.dir/src/models/User.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/models/User.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/models/User.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/models/User.cpp
CMakeFiles/OrderManagement.dir/src/models/User.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/OrderManagement.dir/src/models/User.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/models/User.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\models\User.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\models\User.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\User.cpp

CMakeFiles/OrderManagement.dir/src/models/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/models/User.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\User.cpp > CMakeFiles\OrderManagement.dir\src\models\User.cpp.i

CMakeFiles/OrderManagement.dir/src/models/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/models/User.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\models\User.cpp -o CMakeFiles\OrderManagement.dir\src\models\User.cpp.s

CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/managers/CustomerManager.cpp
CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\managers\CustomerManager.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\managers\CustomerManager.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\CustomerManager.cpp

CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\CustomerManager.cpp > CMakeFiles\OrderManagement.dir\src\managers\CustomerManager.cpp.i

CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\CustomerManager.cpp -o CMakeFiles\OrderManagement.dir\src\managers\CustomerManager.cpp.s

CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/managers/ProductManager.cpp
CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\managers\ProductManager.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\managers\ProductManager.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\ProductManager.cpp

CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\ProductManager.cpp > CMakeFiles\OrderManagement.dir\src\managers\ProductManager.cpp.i

CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\ProductManager.cpp -o CMakeFiles\OrderManagement.dir\src\managers\ProductManager.cpp.s

CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/managers/OrderManager.cpp
CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\managers\OrderManager.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\managers\OrderManager.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\OrderManager.cpp

CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\OrderManager.cpp > CMakeFiles\OrderManagement.dir\src\managers\OrderManager.cpp.i

CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\OrderManager.cpp -o CMakeFiles\OrderManagement.dir\src\managers\OrderManager.cpp.s

CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/managers/UserManager.cpp
CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\managers\UserManager.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\managers\UserManager.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\UserManager.cpp

CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\UserManager.cpp > CMakeFiles\OrderManagement.dir\src\managers\UserManager.cpp.i

CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\managers\UserManager.cpp -o CMakeFiles\OrderManagement.dir\src\managers\UserManager.cpp.s

CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/utils/Database.cpp
CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\utils\Database.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\utils\Database.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\utils\Database.cpp

CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\utils\Database.cpp > CMakeFiles\OrderManagement.dir\src\utils\Database.cpp.i

CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\utils\Database.cpp -o CMakeFiles\OrderManagement.dir\src\utils\Database.cpp.s

CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/utils/Logger.cpp
CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\utils\Logger.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\utils\Logger.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\utils\Logger.cpp

CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\utils\Logger.cpp > CMakeFiles\OrderManagement.dir\src\utils\Logger.cpp.i

CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\utils\Logger.cpp -o CMakeFiles\OrderManagement.dir\src\utils\Logger.cpp.s

CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/utils/Utils.cpp
CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\utils\Utils.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\utils\Utils.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\utils\Utils.cpp

CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\utils\Utils.cpp > CMakeFiles\OrderManagement.dir\src\utils\Utils.cpp.i

CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\utils\Utils.cpp -o CMakeFiles\OrderManagement.dir\src\utils\Utils.cpp.s

CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.obj: CMakeFiles/OrderManagement.dir/flags.make
CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.obj: CMakeFiles/OrderManagement.dir/includes_CXX.rsp
CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.obj: F:/FCAI/GP/TESTREPOS/OrdersManagment/src/ui/ConsoleUI.cpp
CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.obj: CMakeFiles/OrderManagement.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.obj -MF CMakeFiles\OrderManagement.dir\src\ui\ConsoleUI.cpp.obj.d -o CMakeFiles\OrderManagement.dir\src\ui\ConsoleUI.cpp.obj -c F:\FCAI\GP\TESTREPOS\OrdersManagment\src\ui\ConsoleUI.cpp

CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\FCAI\GP\TESTREPOS\OrdersManagment\src\ui\ConsoleUI.cpp > CMakeFiles\OrderManagement.dir\src\ui\ConsoleUI.cpp.i

CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\FCAI\GP\TESTREPOS\OrdersManagment\src\ui\ConsoleUI.cpp -o CMakeFiles\OrderManagement.dir\src\ui\ConsoleUI.cpp.s

# Object files for target OrderManagement
OrderManagement_OBJECTS = \
"CMakeFiles/OrderManagement.dir/src/main.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/models/Product.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/models/Order.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/models/User.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.obj" \
"CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.obj"

# External object files for target OrderManagement
OrderManagement_EXTERNAL_OBJECTS =

OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/main.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/models/Customer.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/models/Product.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/models/Order.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/models/User.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/managers/CustomerManager.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/managers/ProductManager.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/managers/OrderManager.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/managers/UserManager.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/utils/Database.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/utils/Logger.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/utils/Utils.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/src/ui/ConsoleUI.cpp.obj
OrderManagement.exe: CMakeFiles/OrderManagement.dir/build.make
OrderManagement.exe: CMakeFiles/OrderManagement.dir/linkLibs.rsp
OrderManagement.exe: CMakeFiles/OrderManagement.dir/objects1.rsp
OrderManagement.exe: CMakeFiles/OrderManagement.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking CXX executable OrderManagement.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\OrderManagement.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OrderManagement.dir/build: OrderManagement.exe
.PHONY : CMakeFiles/OrderManagement.dir/build

CMakeFiles/OrderManagement.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\OrderManagement.dir\cmake_clean.cmake
.PHONY : CMakeFiles/OrderManagement.dir/clean

CMakeFiles/OrderManagement.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\FCAI\GP\TESTREPOS\OrdersManagment F:\FCAI\GP\TESTREPOS\OrdersManagment F:\FCAI\GP\TESTREPOS\OrdersManagment\build F:\FCAI\GP\TESTREPOS\OrdersManagment\build F:\FCAI\GP\TESTREPOS\OrdersManagment\build\CMakeFiles\OrderManagement.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/OrderManagement.dir/depend

