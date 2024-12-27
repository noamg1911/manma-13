#include <time.h>
#include <math.h>
#include <array>
#include <tuple>
#include "heap_sorter/heap_sorter.hpp"

#define MIN_VAL (0)
#define MAX_VAL (1023)
#define A_SIZE (50)
#define B_SIZE (100)
#define C_SIZE (200)
#define MIN_NUM_CHILDREN (2)
#define MAX_NUM_CHILDREN (5)



template<unsigned int ArraySize>
void random_number_array_generator(size_t (&empty_array)[ArraySize], int min_value, int max_value)
{   
    size_t i = 0;
    int range = max_value - min_value + 1;

    for (i = 0; i < ArraySize; i++)
    {
        empty_array[i] = size_t(min_value + (rand() % range));
    }
}


int main()
{
    srand(unsigned(time(0)));
    size_t series_A[A_SIZE] = { 0 }; 
    size_t series_B[B_SIZE] = { 0 }; 
    size_t series_C[C_SIZE] = { 0 }; 

    random_number_array_generator(series_A, MIN_VAL, MAX_VAL);
    random_number_array_generator(series_B, MIN_VAL, MAX_VAL);
    random_number_array_generator(series_C, MIN_VAL, MAX_VAL);

    HeapSorter<A_SIZE> heap_sorter_A = HeapSorter<A_SIZE>(2);
    HeapSorter<B_SIZE> heap_sorter_B = HeapSorter<B_SIZE>(2);
    HeapSorter<C_SIZE> heap_sorter_C = HeapSorter<C_SIZE>(2);


    // const auto matching_heap_sorters_series_letters = std::array{std::make_tuple(std::ref(heap_sorter_A), series_A, 'A'), std::make_tuple(std::ref(heap_sorter_B), series_B, 'B'), std::make_tuple(std::ref(heap_sorter_C), series_C, 'C'),};
    size_t num_of_children;
    char series_char = 'A';

    printf("For Series %c\n", series_char);
    printf("===============\n");
    for (num_of_children = MIN_NUM_CHILDREN; num_of_children < MAX_NUM_CHILDREN + 1; num_of_children++)
    {
        heap_sorter_C.heap_sort(num_of_children, series_C);
        printf("for d = %zu:\n", num_of_children);
        printf("comparisons: %zu, copies: %zu\n", heap_sorter_C.get_comparisons(), heap_sorter_C.get_copies());
    }
    printf("===============\n");


    // for (const auto& [heap_sorter, series, letter] : matching_heap_sorters_series_letters)
    // {
    //     printf("For Series %c\n", letter);
    //     printf("===============\n");
    //     for (num_of_children = MIN_NUM_CHILDREN; num_of_children < MAX_NUM_CHILDREN; num_of_children++)
    //     {
    //         heap_sorter.heap_sort(num_of_children, series);
    //         printf("for d = %zu:\n", num_of_children);
    //         printf("comparisons: %zu, copies: %zu\n", heap_sorter.get_comparisons(), heap_sorter.get_copies());
    //     }
    //     printf("===============\n");
    // }
    printf("\n");
}