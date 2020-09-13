#ifndef DYNTABLE_IMPLH
#define DYNTABLE_IMPLH

// Initialize a dynamic table.
// the argument specifies the initial number of elements the dynamic table should be able to hold without being resized
void* make_new_dynamic_table(int);

// Inserts element at the end of dynamic table
// Increase factor should be 1.5
void push_back(void**, int);

// Pops element from the end of dynamic table.
// Decrease factor should be 0.25
void pop_back(void**);

#endif
