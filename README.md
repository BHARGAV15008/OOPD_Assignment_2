# Complaint Management System

## Overview
This project is a Complaint Management System that allows users to submit complaints, track their status, and escalate them based on predefined levels of hierarchy. The system reads complaint data from a CSV file and enables user interaction through a command-line interface.

## Build Instructions

To compile the code, follow these steps:

1. **Open a Terminal/Command Prompt**.
2. **Navigate to the directory** containing the source file (e.g., `complaint_management.cpp`).
3. **Compile the program** using the following command:
   ```bash
   g++ complaint_management.cpp -o complaint_management -std=c++11
   ```
4. **Run the compiled program:**
    ```bash
    ./complaint_management
    ```
5. **Input File Format**

> - The program requires a CSV file named Level.csv with the following format:

> > -  *Complaint,Level1,Level2,Level3,Level4*

> > -  *Complaint about course issues,Level1,Level2,-,- *

> > -  *Complaint about registration issues,Level1,Level2,Level3,- *

- Each line represents a complaint with its associated escalation levels.
- The first column is the description of the complaint.
- The subsequent columns (Level1, Level2, Level3, Level4) represent the hierarchy of escalation levels.
- Use - to indicate that a level does not exist (e.g., no Level3 or Level4).