#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int age;
    char city[20];
    char gender[10];
} Row;

typedef struct {
    Row* rows;
    int num_rows;
} DataFrame;

DataFrame* createDataFrame(int num_rows) {
    // Allocate memory for DataFrame structure
    DataFrame* df = (DataFrame*)malloc(sizeof(DataFrame));
    // Allocate memory for the rows array
    df->rows = (Row*)malloc(num_rows * sizeof(Row));
    // Initialize each row with default values
    // (empty strings and age 0)
    for (int i = 0; i < num_rows; i++) {
        Row* row = &(df->rows[i]);
        row->name[0] = '\0';
        row->age = 0;
        row->city[0] = '\0';
        row->gender[0] = '\0';
    }
    // Set the number of rows in the DataFrame
    df->num_rows = num_rows;
    // Return the created DataFrame
    return df;
}

void freeDataFrame(DataFrame* df) {
    // Free the memory allocated for the rows array
    free(df->rows);
    // Free the memory allocated for the DataFrame structure
    free(df);
}

void addRow(DataFrame* df, const char* name, int age, const char* city, const char* gender) {
    // Check if the number of rows is non-negative
    if (df->num_rows >= 0) {
        // Allocate memory for the new row
        if (df->num_rows == 0) {
            df->rows = (Row*)malloc(sizeof(Row));
        } else {
            df->rows = (Row*)realloc(df->rows, (df->num_rows + 1) * sizeof(Row));
        }
        // Get a pointer to the new row
        Row* row = &(df->rows[df->num_rows]);
        // Copy the values to the new row
        strcpy(row->name, name);
        row->age = age;
        strcpy(row->city, city);
        strcpy(row->gender, gender);
        // Increment the number of rows
        df->num_rows++;
    }
}


void printDataFrame(DataFrame* df) {
    // Iterate over each row and print the values
    for (int i = 0; i < df->num_rows; i++) {
        Row row = df->rows[i];
        printf("Name: %s, Age: %d, City: %s, Gender: %s\n", row.name, row.age, row.city, row.gender);
    }
}


void calculateSummaryStatistics(DataFrame* df) {
    // Initialize variables for sum, min, and max age
    int sum_age = 0;
    int min_age = df->rows[0].age;
    int max_age = df->rows[0].age;

    // Calculate sum, minimum, and maximum age
    for (int i = 0; i < df->num_rows; i++) {
        Row row = df->rows[i];
        sum_age += row.age;

        if (row.age < min_age) {
            min_age = row.age;
        }

        if (row.age > max_age) {
            max_age = row.age;
        }
    }

    // Calculate average age
    float avg_age = (float)sum_age / df->num_rows;

    // Print summary statistics
    printf("Summary Statistics:\n");
    printf("Total rows: %d\n", df->num_rows);
    printf("Minimum age: %d\n", min_age);
    printf("Maximum age: %d\n", max_age);
    printf("Average age: %.2f\n", avg_age);
}


void performAggregation(DataFrame* df, const char* column) {
    printf("Aggregation by %s:\n", column);

    if (strcmp(column, "gender") == 0) {
        // Initialize variables for counting males and females
        int num_males = 0;
        int num_females = 0;

        // Count number of males and females
        for (int i = 0; i < df->num_rows; i++) {
            Row row = df->rows[i];
            if (strcmp(row.gender, "Male") == 0) {
                num_males++;
            } else if (strcmp(row.gender, "Female") == 0) {
                num_females++;
            }
        }

        // Print aggregation results
        printf("Number of Males: %d\n", num_males);
        printf("Number of Females: %d\n", num_females);
    } else if (strcmp(column, "city") == 0) {
        // Count unique cities
        int count = 0;
        for (int i = 0; i < df->num_rows; i++) {
            Row row = df->rows[i];
            int unique = 1;

            for (int j = 0; j < i; j++) {
                Row prev_row = df->rows[j];
                if (strcmp(row.city, prev_row.city) == 0) {
                    unique = 0;
                    break;
                }
            }

            if (unique) {
                count++;
            }
        }

        // Print aggregation result
        printf("Number of Unique Cities: %d\n", count);
    } else {
        printf("Invalid column for aggregation\n");
    }
}

int main() {
    DataFrame* df = createDataFrame(3);

    // Add rows to the DataFrame
    addRow(df, "John", 25, "New York", "Male");
    addRow(df, "Alice", 30, "London", "Female");
    addRow(df, "Bob", 35, "Paris", "Male");

    // Print the DataFrame
    printDataFrame(df);
    printf("\n");

    // Calculate and print summary statistics
    calculateSummaryStatistics(df);
    printf("\n");

    // Perform aggregation on gender and city columns
    performAggregation(df, "gender");
    printf("\n");

    performAggregation(df, "city");
    printf("\n");

    // Free memory
    freeDataFrame(df);

    return 0;
}

