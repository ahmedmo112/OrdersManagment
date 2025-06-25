# Order Management System

A comprehensive C++ application for managing orders, customers, products, and users with role-based access control.

## Features

### Core Functionality
- **User Management**: Authentication and role-based access control (Admin, Manager, Employee, Guest)
- **Customer Management**: Complete CRUD operations for customer data
- **Product Management**: Inventory management with stock tracking and low-stock alerts
- **Order Management**: Create, track, and manage orders through different statuses
- **Reporting**: Sales reports, inventory reports, and analytics
- **Logging**: Comprehensive logging system for audit trails
- **Data Persistence**: File-based storage system

### Advanced Features
- Role-based access control with different permission levels
- Order status workflow (Pending → Confirmed → Processing → Shipped → Delivered)
- Stock management with automatic low-stock warnings
- Discount application and order calculations
- Search and filter functionality across all entities
- Data validation and error handling
- Backup and restore capabilities

## System Requirements

- **Compiler**: C++17 compatible compiler (GCC 8+, Clang 7+, MSVC 2019+)
- **Build System**: CMake 3.16 or higher
- **Operating System**: Windows, Linux, or macOS

## Project Structure

```
OrdersManagement/
├── src/                    # Source files
│   ├── main.cpp           # Application entry point
│   ├── models/            # Data models
│   │   ├── Customer.cpp
│   │   ├── Product.cpp
│   │   ├── Order.cpp
│   │   └── User.cpp
│   ├── managers/          # Business logic managers
│   │   ├── CustomerManager.cpp
│   │   ├── ProductManager.cpp
│   │   ├── OrderManager.cpp
│   │   └── UserManager.cpp
│   ├── utils/             # Utility classes
│   │   ├── Database.cpp
│   │   ├── Logger.cpp
│   │   └── Utils.cpp
│   └── ui/                # User interface
│       └── ConsoleUI.cpp
├── include/               # Header files
├── data/                  # Data files
├── logs/                  # Log files (generated)
├── CMakeLists.txt        # CMake configuration
└── README.md             # This file
```

## Building the Application

### Using CMake

1. **Create build directory:**
   ```bash
   mkdir build
   cd build
   ```

2. **Configure the project:**
   ```bash
   cmake ..
   ```

3. **Build the application:**
   ```bash
   cmake --build .
   ```

### Using Visual Studio (Windows)

1. Open the project folder in Visual Studio
2. Configure CMake settings if needed
3. Build → Build Solution

## Running the Application

After building, run the executable:

```bash
# On Windows
./OrderManagement.exe

# On Linux/macOS
./OrderManagement
```

## Default Login Credentials

- **Username**: `admin`
- **Password**: `admin`
- **Role**: Administrator

## User Roles and Permissions

### Administrator
- Full access to all system features
- User management (create, update, delete users)
- System settings and configuration
- All reporting capabilities

### Manager
- Product management (CRUD operations)
- Order management and status updates
- Customer management
- Sales and inventory reports

### Employee
- Order processing and status updates
- Customer service operations
- Basic reporting access

### Guest
- Read-only access to basic information

## Usage Guide

### First Time Setup

1. **Login** with default admin credentials
2. **Change default password** (recommended)
3. **Add users** with appropriate roles
4. **Set up customers** and products
5. **Start processing orders**

### Managing Customers

1. Navigate to Customer Management menu
2. Add new customers with complete contact information
3. Search and filter customers by various criteria
4. Update customer information as needed

### Managing Products

1. Access Product Management menu
2. Add products with categories, pricing, and stock levels
3. Set minimum stock levels for automatic alerts
4. Monitor inventory and update stock quantities

### Processing Orders

1. Create new orders for existing customers
2. Add products to orders with quantities
3. Apply discounts if applicable
4. Update order status through the workflow
5. Track order progress and generate reports

### Generating Reports

1. Access Reports menu
2. Choose from various report types:
   - Sales reports (daily, monthly)
   - Inventory reports
   - Customer analytics
   - Order status reports

## Data Storage

The application uses file-based storage in the `data/` directory:

- `users.txt` - User accounts and authentication data
- `customers.txt` - Customer information
- `products.txt` - Product catalog and inventory
- `orders.txt` - Order records and history

## Logging

Application logs are stored in the `logs/` directory:

- `application.log` - Main application log
- Logs include user actions, system events, and error information

## Best Practices

### Security
- Change default passwords immediately
- Use strong passwords for user accounts
- Regular backup of data files
- Monitor access logs for unusual activity

### Data Management
- Regular data backups
- Monitor disk space usage
- Clean up old log files periodically
- Validate data integrity regularly

### Performance
- Monitor system performance with large datasets
- Optimize search operations for better response times
- Consider data archiving for old records

## Troubleshooting

### Common Issues

1. **Application won't start**
   - Check file permissions in data/ and logs/ directories
   - Verify all required directories exist
   - Check system logs for error messages

2. **Login issues**
   - Verify username/password combination
   - Check if user account is active
   - Reset password using admin account

3. **Data not saving**
   - Check file permissions
   - Verify disk space availability
   - Check application logs for error messages

4. **Performance issues**
   - Monitor system resources
   - Check data file sizes
   - Consider data cleanup/archiving

## Development

### Adding New Features

1. Follow the existing project structure
2. Add appropriate header files in `include/`
3. Implement source files in `src/`
4. Update CMakeLists.txt if needed
5. Add appropriate logging and error handling

### Coding Standards

- Use meaningful variable and function names
- Follow C++ best practices (RAII, const correctness)
- Add appropriate comments and documentation
- Handle errors gracefully
- Use logging for important operations

## Future Enhancements

- Database integration (MySQL, PostgreSQL)
- Web interface
- RESTful API
- Email notifications
- Advanced reporting with charts
- Multi-currency support
- Integration with payment systems

## License

This project is for educational purposes. Feel free to modify and use as needed.

## Support

For issues, feature requests, or questions, please refer to the project documentation or contact the development team. 