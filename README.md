<p align="center">
  <img src="https://pics.craiyon.com/2023-06-13/0205f5e24c4b4aefb0f47706fb3122de.webp" alt="Image Alt Text" width="400" height="400">
</p>

# DataFrame Operations in C

This C program demonstrates basic operations on a DataFrame. The program creates a DataFrame structure, adds rows to it, and performs operations such as printing the DataFrame, calculating summary statistics, and performing aggregation.

## Code Explanation

The code consists of the following components:

1. Includes the necessary libraries for input/output and string handling.
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

2. Defines the `Row` structure to represent a single row of data in the DataFrame.
```c
typedef struct {
    char name[20];
    int age;
    char city[20];
    char gender[10];
} Row;
```

3. Defines the `DataFrame` structure to store rows and the number of rows.
```c
typedef struct {
    Row* rows;
    int num_rows;
} DataFrame;
```

4. Implements the `createDataFrame` function that creates a DataFrame with a given number of rows and initializes each row with default values.
```c
DataFrame* createDataFrame(int num_rows) {
    // Implementation details
    return df;
}
```

5. Implements the `freeDataFrame` function that frees the memory allocated for the DataFrame and its rows.
```c
void freeDataFrame(DataFrame* df) {
    // Implementation details
}
```

6. Implements the `addRow` function that adds a new row to the DataFrame.
```c
void addRow(DataFrame* df, const char* name, int age, const char* city, const char* gender) {
    // Implementation details
}
```

7. Implements the `printDataFrame` function that prints the contents of the DataFrame.
```c
void printDataFrame(DataFrame* df) {
    // Implementation details
}
```

8. Implements the `calculateSummaryStatistics` function that calculates and prints summary statistics of the DataFrame.
```c
void calculateSummaryStatistics(DataFrame* df) {
    // Implementation details
}
```

9. Implements the `performAggregation` function that performs aggregation on a specified column of the DataFrame.
```c
void performAggregation(DataFrame* df, const char* column) {
    // Implementation details
}
```

10. The `main` function demonstrates the usage of DataFrame operations. It creates a DataFrame, adds rows, and performs operations like printing the DataFrame, calculating summary statistics, and performing aggregation.
```c
int main() {
    // Implementation details

    return 0;
}
```

## Usage

1. Compile the program using a C compiler.
```
gcc dataframe_operations.c -o dataframe_operations
```

2. Run the executable.
```
./dataframe_operations
```

## Output

The program generates the following output:

```
Name: John, Age: 25, City: New York, Gender: Male
Name: Alice, Age: 30, City: London, Gender: Female
Name: Bob, Age: 35, City: Paris, Gender: Male

Summary Statistics:
Total rows: 3
Minimum age: 25
Maximum age: 35
Average age: 30.00

Aggregation by gender:
Number of Males: 2
Number of Females: 1

Aggregation by city:
Number of Unique Cities: 3
```

## Cleanup

The program frees the memory allocated for the DataFrame and its rows to avoid memory leaks.

## License

This project is licensed under the [MIT License](LICENSE).

Feel free to modify and use the code according to your needs.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any changes or improvements you would like to make.

## Acknowledgements

This program was developed by Soumya Chakraborty as a demonstration of basic DataFrame operations in C.
