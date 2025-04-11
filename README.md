Project Title: Query Execution Engine

Author: Gabe M.

Date: November 20th, 2024 

Description:
    This project is a simple query processing engine built using relational algebra operators.
    It supports query evaluation using materialization, with operators such as Select, 
    Project, and Join, and processes records from flat files in a paginated manner.

    How to Run:
    # Compile (if not already)
        g++ driver.cpp -o a.out

    # Run the executable
        ./a.out
    
    Output example:
    -----------------Page-----------------
    <record 1>
    <record 2>
    ...
    [Finished]
        pages  received: 3
        records received: 5

Features:
    Relational Algebra Operators:
        Select (σ)
        Project (π)
        Join (⨝ )
    Materialization Support:
        Intermediate results are written to temporary files and used as inputs to 
        subsequent operations.
    Custom File Reader and Writer:
        Handles large datasets (bigData, smallData) using block-based pagination.
    Record-Based Storage:
        Each record is structured and processed with custom Record and Page abstractions. 

File Structure & Purposes:
    .
    ├── FileReader.h     *Reads data from input files (page-wise)*
    ├── FileWriter.h     *Writes output and intermediate results*
    ├── Join.h           *Implements the join operator*
    ├── Select.h         *Implements the select operator*
    ├── Project.h        *Implements the project operator*
    ├── Operator.h       *Base class for all operators*
    ├── Record.h         *Record structure and utilities*
    ├── driver.cpp       *Main driver for executing the query*
    ├── bigData/         *Large dataset files*
    ├── smallData/       *Sample small dataset files*
