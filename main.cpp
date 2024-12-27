#include <time.h>
#include "heap_sorter/heap_sorter.hpp"

#define MIN_VAL (0)
#define MAX_VAL (1023)
#define A_SIZE (50)
#define B_SIZE (100)
#define C_SIZE (200)
#define MIN_NUM_CHILDREN (2)
#define MAX_NUM_CHILDREN (5)

/*
Puts random positive (ranged) integers in a given array.

@template param ArraySize: The size of the array of numbers.
@param o_empty_array: A (so-called) empty array that will be filled with random integers.
@param min_value: The lower bound of the range of random integers.
@param max_value: The upper bound of the range of random integers.
*/
template<size_t ArraySize>
void random_number_array_generator(size_t (&o_empty_array)[ArraySize], int min_value, int max_value)
{   
    size_t i = 0;
    int range = max_value - min_value + 1;

    for (i = 0; i < ArraySize; i++)
    {
        o_empty_array[i] = size_t(min_value + (rand() % range));
    }
}

/*
Prints out the number of comparisons and swaps made on a given array using the heap_sort algorithm with different
numbers of heap children per parent.

@template param HeapSize: The size of the array/heap.
@param heap_sorter: The HeapSorter objet that implements the heap_sort algorithm.
@param unordered_array: The array to be sorted using heap_sort.
@param array_char: A character that represents the array (according to maman instructions).
*/
template<size_t HeapSize>
void output_results_for_heapsort(HeapSorter<HeapSize> heap_sorter, size_t (&unordered_array)[HeapSize], char array_char)
{
    size_t num_of_children = MIN_NUM_CHILDREN;

    printf("For Series %c:\n==============\n", array_char);

    for (num_of_children = MIN_NUM_CHILDREN; num_of_children < MAX_NUM_CHILDREN + 1; num_of_children++)
    {
        heap_sorter.heap_sort(num_of_children, unordered_array);
        printf("for d = %zu:\n", num_of_children);
        printf("comparisons: %zu, copies: %zu\n", heap_sorter.get_comparisons(), heap_sorter.get_copies());
    }

    printf("===============\n");
    printf("\n");
}


int main()
{
    size_t series_A[A_SIZE] = { 0 }; 
    size_t series_B[B_SIZE] = { 0 }; 
    size_t series_C[C_SIZE] = { 0 }; 

    srand(unsigned(time(0)));
    random_number_array_generator(series_A, MIN_VAL, MAX_VAL);
    random_number_array_generator(series_B, MIN_VAL, MAX_VAL);
    random_number_array_generator(series_C, MIN_VAL, MAX_VAL);

    HeapSorter<A_SIZE> heap_sorter_A = HeapSorter<A_SIZE>(MIN_NUM_CHILDREN);
    HeapSorter<B_SIZE> heap_sorter_B = HeapSorter<B_SIZE>(MIN_NUM_CHILDREN);
    HeapSorter<C_SIZE> heap_sorter_C = HeapSorter<C_SIZE>(MIN_NUM_CHILDREN);

    output_results_for_heapsort(heap_sorter_A, series_A, 'A');
    output_results_for_heapsort(heap_sorter_B, series_B, 'B');
    output_results_for_heapsort(heap_sorter_C, series_C, 'C');
}