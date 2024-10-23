#include <stdio.h> 
#define SIZE_ROW 100
#define NUM_ROWS 10

struct ROW {
    float data[SIZE_ROW];
    float addition;
};

void sum_row (struct ROW *pf) {
// B) Implement sum_row
    pf -> addition = 0;
    for(int j = 0; j < SIZE_ROW; j++){
        pf -> addition += pf -> data[j];
    }
}

// Initilize rows with value i * j
void init_row(struct ROW *row, int i) {
    for (int j = 0; j < SIZE_ROW; j++) {
        row -> data[j] = (float)i*j;
    }
}

int main() { 
    int i;
    float total_sum;
    
    struct ROW rows[NUM_ROWS];
    
    // C) Complete the loop
    total_sum = 0;
    for (i = 0; i < NUM_ROWS; i++) {
        init_row(&rows[i], i);
        sum_row(&(rows[i]));
        printf("Row %d addition result is %f\n", i, rows[i].addition);
        // update total_sum with the actual row
        
        total_sum += rows[i].addition;
    }

    printf("Final addition result is %f\n", total_sum); 
    
    return 0;
}
