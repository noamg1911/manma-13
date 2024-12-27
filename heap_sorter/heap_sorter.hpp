#pragma once

#include <stdio.h>
#include <stdlib.h>

#define ROOT_INDEX (0)

template<size_t MaxHeapArraySize>
class HeapSorter
{
public:
    HeapSorter(size_t num_of_children) : _num_of_children(num_of_children)
    {
        for (size_t index = 0; index < MaxHeapArraySize; index++)
        {
            this->_heap_array[index] = 0;
        }
        this->initialize_non_array_members();
    }

    void heap_sort(size_t num_of_children, size_t (&unordered_array)[MaxHeapArraySize])
    {
        this->initialize_non_array_members();
        this->set_num_of_children(num_of_children);   
        for (size_t index = 0; index < MaxHeapArraySize; index++)
        {
            this->_heap_array[index] = unordered_array[index];
        }

        this->build_max_heap();

        for (int index = MaxHeapArraySize - 1; index > 0; index--)
        {
            this->swap_values(ROOT_INDEX, index);
            this->_current_heap_size--;
            this->update_max_parent_index();
            this->max_heapify(ROOT_INDEX);
        }
    }

    void max_heapify(size_t index)
    {
        size_t largest_child_index = this->get_index_of_largest_child(index);

        if (this->_heap_array[largest_child_index] > this->_heap_array[index])
        {
            this->swap_values(index, largest_child_index);
            this->max_heapify(largest_child_index);
        }
        this->_num_comparisons++;
    }

    void build_max_heap()
    {
        for (int current_parent_index = this->_max_parent_index; current_parent_index >= 0; current_parent_index--)
        {
            max_heapify(current_parent_index);
        }
    }

    void set_num_of_children(size_t new_num_of_children)
    {
        this->_num_of_children = new_num_of_children;
        this->update_max_parent_index();
    }

    void print_heap()
    {
        for (size_t index = 0; index < MaxHeapArraySize; index++)
        {
            printf("%zu ", this->_heap_array[index]);
        }
        printf("\n");
    }

    size_t get_comparisons()
    {
        return this->_num_comparisons;
    }

    size_t get_copies()
    {
        return this->_num_copies;
    }

private:
    void swap_values(size_t first_index, size_t second_index)
    {
        if (first_index > this->_current_heap_size - 1 || second_index > this->_current_heap_size - 1)
        {
            printf("weird swap indexes %zu %zu, bigger than %zu\n", first_index, second_index, this->_current_heap_size);
            return;
        }

        size_t temp = this->_heap_array[first_index];
        this->_heap_array[first_index] = _heap_array[second_index];
        this->_heap_array[second_index] = temp;
        this->_num_copies += 2;
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
        if (child_index == ROOT_INDEX)
        {
            return ROOT_INDEX;
        }

        return (child_index - 1) / this->_num_of_children;
    }

    size_t get_index_of_largest_child(size_t parent_index)
    {
        if (parent_index > this->_max_parent_index || this->_current_heap_size <= 1)
        {
            return parent_index;
        }

        size_t left_child_index = this->get_left_child_index(parent_index);
        size_t largest_child_index = left_child_index;

        for (size_t current_child_index = left_child_index + 1; current_child_index < left_child_index + this->_num_of_children && current_child_index < this->_current_heap_size; current_child_index++)
        {
            if (this->_heap_array[current_child_index] > this->_heap_array[largest_child_index])
            {
                largest_child_index = current_child_index;
            }
            this->_num_comparisons++;
        }

        return largest_child_index;
    }

    void update_max_parent_index()
    {
        this->_max_parent_index = this->get_parent_index(this->_current_heap_size - 1);
    }

    void initialize_non_array_members()
    {
        this->_num_comparisons = 0;
        this->_num_copies = 0;
        this->_current_heap_size = MaxHeapArraySize;
        this->update_max_parent_index();
    }

    size_t _heap_array[MaxHeapArraySize];
    size_t _current_heap_size;
    size_t _num_of_children;
    size_t _max_parent_index;
    size_t _num_comparisons;
    size_t _num_copies;
};