# Lab Practice 2: Structures and Pointers in C

## Summary

In this lab, we explored how to work with structures, pointers, and arrays in C to create and manipulate complex data types. We specifically worked on summing the elements of rows of data stored in structures and utilized pointers to pass and manipulate those structures in functions.

## Key Concepts
- Defining and using `struct` in C to organize related data (arrays and summation results).
- Using pointers to pass and modify structures within functions.
- Resetting values within structures to avoid accumulating incorrect data.
- Basic memory management and the need to initialize variables properly in C.
- Implementing row-based summation operations on 2D-like data structures.

## Code Implementation Breakdown

### Struct Definition
We defined a structure `ROW` to hold an array of floats (`data[]`) and a single float to store the summation result (`addition`).

```c
struct ROW {
    float data[SIZE_ROW];
    float addition;
};
```

### Row Initialization (`init_row`)
We implemented the `init_row()` function to initialize each row’s `data[]` array with values based on the row index `i` and column index `j`.

```c
void init_row(struct ROW *row, int i) {
    for (int j = 0; j < SIZE_ROW; j++) {
        row -> data[j] = (float)i * j;
    }
}
```

### Summing the Rows (`sum_row`)
The `sum_row()` function was responsible for summing the elements of `data[]` in each `ROW` structure. We made sure to reset the `addition` field to `0.0f` at the start to prevent incorrect accumulation of values.

```c
void sum_row(struct ROW *pf) {
    pf -> addition = 0.0f;  // Reset the summation before calculating
    for(int j = 0; j < SIZE_ROW; j++) {
        pf -> addition += pf -> data[j];
    }
}
```

### Main Loop and Output
In the `main()` function, we defined an array of `struct ROW` and initialized each row, calculated the sum, and printed the results.

```c
int main() { 
    int i;
    float total_sum = 0;
    
    struct ROW rows[NUM_ROWS];
    
    for (i = 0; i < NUM_ROWS; i++) {
        init_row(&rows[i], i);
        sum_row(&rows[i]);
        printf("Row %d addition result is %f\n", i, rows[i].addition);
        total_sum += rows[i].addition;
    }

    printf("Final addition result is %f\n", total_sum);
    return 0;
}
```

### Key Insights:
- **Uninitialized values in C**: Variables, including struct fields, must be initialized properly. Without explicit initialization, fields like `addition` may contain garbage values, which could lead to incorrect results.
- **Passing structs by reference**: Using pointers (`&`) to pass structures to functions allows us to modify the original structure instead of working with a copy, which is crucial for efficiency in memory management.
- **Avoiding cumulative errors**: Resetting values such as `addition` before each summation avoids errors due to accumulating old values from previous calculations.

## Expected Output:
The program calculates and prints the sum of each row and the final sum of all rows, which should look like this:
```
Row 0 addition result is 0.000000
Row 1 addition result is 4950.000000
Row 2 addition result is 9900.000000
Row 3 addition result is 14850.000000
Row 4 addition result is 19800.000000
Row 5 addition result is 24750.000000
Row 6 addition result is 29700.000000
Row 7 addition result is 34650.000000
Row 8 addition result is 39600.000000
Row 9 addition result is 44550.000000
Final addition result is 247500.000000
```

## Conclusion
This lab practice helped solidify the understanding of how structs and pointers work in C, and how they can be used to manage and operate on complex data structures efficiently. Proper initialization and memory management techniques were emphasized to avoid common pitfalls in C programming.

