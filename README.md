# C++ Console Library Management System 📚🖥️

This project is a console-based Library Management System developed entirely in C++ during my first year of Software Engineering. It demonstrates my foundational understanding of memory handling, data structures, and file operations before transitioning to modern web and backend frameworks.

## 🛠️ Technical Highlights & Core Mechanics

* **Persistent Data via File I/O:** The system reads from and writes to `kitaplar.csv` (CSV file) using `<fstream>` and `<sstream>`, ensuring that the library's inventory state is saved across sessions.
* **Struct-Based OOP:** Utilizes C++ `struct` paradigms to model `kitap` (Book) and `kutuphane` (Library) objects, encapsulating properties (ISBN, Author, Status) and behaviors (Borrow, Return).
* **Dynamic Time Management:** Integrates the `<ctime>` library to dynamically calculate borrow dates and return deadlines (e.g., 31-day borrow limits).
* **Memory & Collections:** Implements `std::vector` for dynamic list management and memory-efficient iterations over the library inventory.
* **Data Parsing:** Demonstrates string manipulation and type conversion (e.g., `stoi`) to safely parse CSV data into usable application objects.

> **Note:** This is a legacy academic project showcasing my core C++ and algorithmic foundations. For my current enterprise-level full-stack development skills, please review my **.NET 8 / MySQL Library System** repository.
