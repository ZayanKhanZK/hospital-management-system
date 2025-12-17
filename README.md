# hospital-management-system

# 🏥 Hospital Management System (HMS)

A robust, modular Hospital Management System built in C. This console-based application streamlines hospital administration by managing patient admissions, doctor records, and room allocations with persistent data storage.

> **Project Type:** University Group Project
> **My Role:** Core Logic Implementation & Functional Programming

## 🚀 Overview

This project simulates a database management system using C structures and binary file I/O. It provides a Command Line Interface (CLI) for performing CRUD (Create, Read, Update, Delete) operations. The system is designed to be fault-tolerant, featuring robust input validation and specific business logic to prevent errors like room overbooking.

## 👨‍💻 Team & Contributions

This application was developed as a collaborative university project. 

**My Specific Contributions:**
I was responsible for **handling the coding of the core functions** and implementing the system logic. My work focused on:
* **Module Development:** Writing the source code for `patient.c` and `doctor.c`.
* **Business Logic:** Implementing the algorithms for room occupancy checks (Private vs. Public capacity) and unique ID generation.
* **Search Algorithms:** Coding the search filters to find records by substrings (Name, Disease) and integer ranges (Age, ID).
* **Data Persistence:** Implementing the binary file handling (`fwrite`/`fread`) to ensure data remains consistent across sessions.

## ✨ Key Features

### 👨‍⚕️ Doctor Management
* **Registration & Tracking:** maintain records of ID, Name, Specialization, and Availability.
* **Search Engine:** Filter doctors by ID, Name (partial match), or Specialization.
* **Soft Delete:** Mark doctors as inactive (Retirement/Transfer) without corrupting the historical data order.

### 😷 Patient Management
* **Admission Workflow:** Capture detailed info including age, gender, disease, and room assignment.
* **Intelligent Room Allocation:** * *Private Rooms:* Limited to 1 patient.
    * *Public Wards:* Limited to 4 patients.
    * The system automatically validates occupancy before assigning a bed.
* **Discharge System:** Safely remove patients from active lists while updating room availability.

### 💾 Data Persistence
* Uses **Binary File storage** (`patients.dat` and `doctors.dat`) for efficient, secure data saving and loading.
* Automated file creation if no database is found on startup.

## 🛠️ Technical Implementation

* **Language:** C (Standard C99/C11)
* **Architecture:** Modular design using separate Header (`.h`) and Source (`.c`) files.
* **Input Validation:** Custom helper functions (`read_string`, `clear_input_line`) to prevent buffer overflows and handle invalid data types.
* **Memory Management:** Efficient use of static arrays and structure pointers.

## 📂 Project Structure

```text
├── main.c              # Entry point and main menu orchestration
├── doctor.c / .h       # Doctor module (logic and data structures)
├── patient.c / .h      # Patient module (logic, room validation, data structures)
├── global_helpers.c/.h # Shared utilities (input validation, string manipulation)
└── data/               # .dat files (generated automatically)
