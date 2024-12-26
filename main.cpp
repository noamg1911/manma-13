#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MIN_VAL (0)
#define MAX_VAL (15)

size_t num_comparisons = 0;
size_t num_copies = 0;

template<size_t HeapArraySize>
class HeapSorter
{
public:
    HeapSorter(size_t num_of_children, size_t unordered_heap_array[HeapArraySize]) : _num_of_children(num_of_children), _heap_array(unordered_heap_array)
    {
        update_max_parent_index();
    }

    void max_heapify(size_t index)
    {
        size_t largest_child_index = this->get_index_of_largest_child(index);

        if (this->_heap_array[largest_child_index] > this->_heap_array[index])
        {
            this->swap_values(index, largest_child_index);
            this->max_heapify(largest_child_index);
        }
    }

    void build_max_heap()
    {
        // int and not size_t so the loop can stop after 0, in size_t it will reach around to MAX_UINT and loop forever...
        for (int current_parent_index = this->_max_parent_index; current_parent_index >= 0; current_parent_index--)
        {
            max_heapify(current_parent_index);
        }

        if (this->verify_max_heap())
        {
            printf("yay!\n");
        }
    }

    void heap_sort()
    {
        printf("g");
    }

    void set_num_of_children(size_t new_num_of_children)
    {
        this->_num_of_children = new_num_of_children;
        this->update_max_parent_index();
    }

    void print_heap()
    {
        for (size_t index = 0; index < HeapArraySize; index++)
        {
            printf("%zu ", this->_heap_array[index]);
        }
        printf("\n");
    }

private:
    void swap_values(size_t first_index, size_t second_index)
    {
        if (first_index > HeapArraySize - 1 || second_index > HeapArraySize - 1)
        {
            printf("weird swap indexes %zu %zu\n", first_index, second_index);
            return;
        }

        size_t temp = this->_heap_array[first_index];
        this->_heap_array[first_index] = _heap_array[second_index];
        this->_heap_array[second_index] = temp;
    }

    size_t get_left_child_index(size_t parent_index)
    {
        if (parent_index > this->_max_parent_index)
        {
            return parent_index;
        }

        return parent_index * this->_num_of_children + 1;
    }

    size_t get_parent_index(size_t child_index)
    {
        if (child_index == 0)
        {
            printf("weird child index %zu\n", child_index);
            return 0;
        }

        return (child_index - 1) / this->_num_of_children;
    }

    size_t get_index_of_largest_child(size_t parent_index)
    {
        if (parent_index > this->_max_parent_index)
        {
            // printf("2weird parent index %zu\n", parent_index);
            return parent_index;
        }

        size_t left_child_index = this->get_left_child_index(parent_index);
        size_t right_child_index = left_child_index + this->_num_of_children - 1;
        if (right_child_index > HeapArraySize - 1)
        {
            right_child_index = HeapArraySize - 1;
        }

        size_t largest_child_index = left_child_index;

        for (size_t current_child_index = left_child_index + 1; current_child_index < right_child_index + 1; current_child_index++)
        {
            if (this->_heap_array[current_child_index] > this->_heap_array[largest_child_index])
            {
                largest_child_index = current_child_index;
            }
        }

        return largest_child_index;
    }

    void update_max_parent_index()
    {
        this->_max_parent_index = this->get_parent_index(HeapArraySize - 1);
    }

    bool verify_max_heap()
    {
        for (size_t index = 0; index < this->_max_parent_index; index++)
        {
            size_t left_child_index = this->get_left_child_index(index);
            size_t right_child_index = left_child_index + this->_num_of_children - 1;
            if (right_child_index > HeapArraySize - 1)
            {
                right_child_index = HeapArraySize - 1;
            }

            for (size_t current_child_index = left_child_index; current_child_index < right_child_index + 1; current_child_index++)
            {
                if (this->_heap_array[current_child_index] > this->_heap_array[index])
                {
                    printf("wow! error at %zu, %zu\n", index, current_child_index);
                    return false;
                }
            }
        }

        return true;
    }

    size_t (&_heap_array)[HeapArraySize];
    size_t _current_heap_size;
    size_t _num_of_children;
    size_t _max_parent_index;
};

template<unsigned int ArraySize>
void rand_num_array_generator(size_t (&empty_array)[ArraySize], int min_value, int max_value)
{   
    size_t i = 0;
    int range = max_value - min_value + 1;

    for (i = 0; i < ArraySize; i++)
    {
        empty_array[i] = size_t(min_value + (rand() % range));
    }
}


// Reset the counters for the assignment. Will be used after every heap sort check.
void reset_counts()
{
    num_comparisons = 0;
    num_copies = 0;
}


int main()
{
    srand(unsigned(time(0)));
    size_t series_A[50] = { 0 }; 
    size_t series_B[100] = { 0 }; 
    size_t series_C[200] = { 0 }; 

    rand_num_array_generator(series_A, MIN_VAL, MAX_VAL);
    rand_num_array_generator(series_B, MIN_VAL, MAX_VAL);
    rand_num_array_generator(series_C, MIN_VAL, MAX_VAL);

    HeapSorter<50> heapy = HeapSorter<50>(2, series_A);
    heapy.print_heap();
    heapy.build_max_heap();
    heapy.print_heap();
    printf("\n");
    printf("peniss\n");
}