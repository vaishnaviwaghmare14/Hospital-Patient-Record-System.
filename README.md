# Hospital-Patient-Record-System.

This project presents a Hospital Patient Record Management System developed in C, utilizing the Queue (FIFO – First In, First Out) data structure to efficiently manage patient flow across multiple departments.

The system is designed to simulate real-world hospital operations, where patients are registered, categorized, and served systematically based on their arrival and assigned department.

#  Hospital Patient Record System (C | Queue-Based)

This project implements a **Hospital Patient Record Management System** in C using the **Queue (FIFO - First In First Out)** data structure.  
It simulates how patients are managed across different hospital departments in an organized and systematic way.



**Functionality**

- **Add Patient**  
  Register a patient with ID, name, age, disease, and priority.

- **Assign Department**  
  Patients are directed to one of four departments:  
  Orthopedic, Dermatology, Cardiology, or General.

- **Doctor Information**  
  Displays assigned doctor details including room number and availability.

- **Serve Patient**  
  Processes the next patient in the queue (FIFO order).

- **View Patients**  
  Shows all patients department-wise with their details.

- **Search Patient**  
  Find a patient quickly using their unique ID.

- **Discharge Patient**  
  Remove a patient record from the system.

- **Statistics**  
  Displays total patients and available capacity.


 Technical Overview

- Circular Queue implementation using arrays  
- Use of structures (`struct`) for data organization  
- Menu-driven program design  
- Basic input validation and data handling

Author****
Vaishnavi Waghmare



 How to Run

```bash
gcc hospital.c -o hospital
./hospital
```
