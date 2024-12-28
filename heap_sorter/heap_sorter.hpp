#pragma once

#include <stdio.h>
#include <stdlib.h>

#define ROOT_INDEX (0)


/*
A class that represents an implementation of the heap_sort algorithm. 

@template param MaxHeapArraySize: The maximal size of the heap array (maximal because in heap sort you decrement
the size of the heap).
@member heap_array: an Array that holds the values given in the heap sort function.
@member current_heap_size: The current size of the heap (not the array, because in heap sort the heap size is decremented).
@member num_of_children: The number of children for each parent in the heap.
@member max_parent_index: The index in the array of the last parent in the heap (parent -> has children).
@member num_comparisons: The number of comparisons that were made on heap_array during the function runs.
@member num_copies: The number of copies that were made on heap_array during the function runs.
*/
template<size_t MaxHeapArraySize>
class HeapSorter
{
public:
    /*
    Constructor. Sets the relevant members to their initial values, and zeroes out the heap_array member.
    */
    HeapSorter(size_t num_of_children) : _num_of_children(num_of_children)
    {
        for (size_t index = 0; index < MaxHeapArraySize; index++)
        {
            this->_heap_array[index] = 0;
        }
        this->initialize_non_array_members();
    }

    /*
    Central function of the class. Implements the heap sort algorithm by taking an array, reorganizing it to make a
    heap, and then sorts that heap.

    @param num_of_children: The number of children each parent in the created heap will have
    @param unordered_array: The array to be sorted (the values of the array are copied here so the array itself isn't sorted).
    */
    void heap_sort(size_t num_of_children, size_t (&unordered_array)[MaxHeapArraySize])
    {
        this->initialize_data_for_heap_sort(num_of_children, unordered_array);
        this->build_max_heap();

        for (int index = MaxHeapArraySize - 1; index > 0; index--)
        {
            this->swap_values(ROOT_INDEX, index);
            this->_current_heap_size--;
            this->update_max_parent_index();
            this->max_heapify(ROOT_INDEX);
        }
    }

    /*
    Implementation of the max heapify function. "Sifts" down a given index in a heap array, recursively calling the 
    function until the index's heap subtree is "legal".
    
    @param index: The index to be "sifted" down to make the index's heap subtree legal.
    */
    void max_heapify(size_t index)
    {
        size_t largest_child_index = this->get_index_of_largest_child(index);

        if (largest_child_index == index)
        {
            return;
        }

        this->_num_comparisons++;
        if (this->_heap_array[largest_child_index] > this->_heap_array[index])
        {
            this->swap_values(index, largest_child_index);
            this->max_heapify(largest_child_index);
        }
    }

    /*
    Turns the class's array into a legal max heap. Uses max heapify calls on the array's parent indexes.
    */
    void build_max_heap()
    {
        for (int current_parent_index = this->_max_parent_index; current_parent_index >= 0; current_parent_index--)
        {
            this->max_heapify(current_parent_index);
        }
    }

    /*
    Prints the values of the elements in the class's array. Used mainly for debugging.
    */
    void print_heap()
    {
        for (size_t index = 0; index < MaxHeapArraySize; index++)
        {
            printf("%zu ", this->_heap_array[index]);
        }
        printf("\n");
    }

    /*
    Returns the number of comparisons that were currently made on the objects of the class's array.
    */
    size_t get_comparisons()
    {
        return this->_num_comparisons;
    }

    /*
    Returns the number of value copies that were currently made on the objects of the class's array.
    */
    size_t get_copies()
    {
        return this->_num_copies;
    }

private:
    /*
    Swaps the values of two elements in the class's heap array

    @param first_index, second_index: The indexes of the elements to swap.
    */
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

    /*
    Sets the number of children each parent in the heap will have, and calculates the maximal index of a 
    parent element in the array (all indexes after it are just children).

    @param new_num_of_children: The new number of children each parent will have.
    */
    void set_num_of_children(size_t new_num_of_children)
    {
        this->_num_of_children = new_num_of_children;
        this->update_max_parent_index();
    }

    /*
    Gets the array index of the leftmost child of a given heap parent element

    @param parent_index: The array index of the parent element.
    
    @return The index of the leftmost child.
    */
    size_t get_left_child_index(size_t parent_index)
    {
        if (parent_index > this->_max_parent_index)
        {
            return parent_index;
        }

        return parent_index * this->_num_of_children + 1;
    }

    /*
    Gets the array index of the parent of a given heap child element

    @param child_index: The array index of the child element.
    
    @return The index of the parent.
    */
    size_t get_parent_index(size_t child_index)
    {
        if (child_index == ROOT_INDEX)
        {
            return ROOT_INDEX;
        }

        return (child_index - 1) / this->_num_of_children;
    }

    /*
    Calculates and gets the index of a given parent element's heap child element with the largest value.

    @param parent_index: The array index of the parent element.
    
    @return The index of the child with the largest value (not index value, array value).
    */
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
            this->_num_comparisons++;
            if (this->_heap_array[current_child_index] > this->_heap_array[largest_child_index])
            {
                largest_child_index = current_child_index;
            }
        }

        return largest_child_index;
    }

    /*
    Calculates the biggest array index of a parent element in the heap array (all other elements after are non-parent elements)
    */
    void update_max_parent_index()
    {
        this->_max_parent_index = this->get_parent_index(this->_current_heap_size - 1);
    }

    /*
    Initializes member data for the heap_sort function.
    */
    void initialize_data_for_heap_sort(size_t num_of_children, size_t (&unordered_array)[MaxHeapArraySize])
    {
        this->initialize_non_array_members();
        this->set_num_of_children(num_of_children);   
        for (size_t index = 0; index < MaxHeapArraySize; index++)
        {
            this->_heap_array[index] = unordered_array[index];
        }
    }

    /*
    Initializes some of the members to their default value (used in constructor and before running heap sort).
    */
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