#include "memory.h"

#include "../sdk/sdk.h"

template <class T, class I>
c_utl_memory<T, I>::c_utl_memory(int grow_size, int init_allocation_count) : memory(0), allocation_count(init_allocation_count), grow_size(grow_size)
{
    validate_grow_size();
    assert(grow_size >= 0);
    if (allocation_count)
    {
        memory = (T*)sdk::mem_alloc->alloc(allocation_count * sizeof(T));
    }
}

template <class T, class I>
c_utl_memory<T, I>::c_utl_memory(T* memory, int number_of_elements) : memory(memory), allocation_count(number_of_elements)
{
    grow_size = EXTERNAL_BUFFER_MARKER;
}

template <class T, class I>
c_utl_memory<T, I>::c_utl_memory(const T* memory, int number_of_elements) : memory((T*)memory), allocation_count(number_of_elements)
{
    grow_size = EXTERNAL_CONST_BUFFER_MARKER;
}

template <class T, class I>
c_utl_memory<T, I>::~c_utl_memory()
{
    purge();
}

template <class T, class I>
void c_utl_memory<T, I>::init(int gor_size, int init_size)
{
    purge();

    grow_size = gor_size;
    allocation_count = init_size;
    validate_grow_size();
    assert(gor_size >= 0);
    if (allocation_count) {
        memory = (T*)sdk::mem_alloc->alloc(allocation_count * sizeof(T));
    }
}

template <class T>
__forceinline void V_swap(T& x, T& y)
{
    T temp = x;
    x = y;
    y = temp;
}

template <class T, class I>
void c_utl_memory<T, I>::swap(c_utl_memory<T, I>& mem)
{
    V_swap(grow_size, mem.grow_size);
    V_swap(memory, mem.memory);
    V_swap(allocation_count, mem.allocation_count);
}

template <class T, class I>
void c_utl_memory<T, I>::convert_to_growable_memory(int grow_size)
{
    if (!is_externally_allocated())
        return;

    grow_size = grow_size;
    if (allocation_count)
    {
        int nNumBytes = allocation_count * sizeof(T);
        T* memory = (T*)sdk::mem_alloc->alloc(nNumBytes);
        memcpy(memory, memory, nNumBytes);
        memory = memory;
    }
    else
    {
        memory = NULL;
    }
}

template <class T, class I>
void c_utl_memory<T, I>::set_external_buffer(T* memory, int number_of_elements)
{
    purge();

    memory = memory;
    allocation_count = number_of_elements;
    grow_size = EXTERNAL_BUFFER_MARKER;
}

template <class T, class I>
void c_utl_memory<T, I>::set_external_buffer(const T* memory, int number_of_elements)
{
    purge();

    memory = const_cast<T*>(memory);
    allocation_count = number_of_elements;

    grow_size = EXTERNAL_CONST_BUFFER_MARKER;
}

template <class T, class I>
void c_utl_memory<T, I>::assume_memory(T* memory, int number_of_elements)
{
    purge();
    memory = memory;
    allocation_count = number_of_elements;
}

template <class T, class I>
void* c_utl_memory<T, I>::detach_memory()
{
    if (is_externally_allocated())
        return NULL;

    void* memory = memory;
    memory = 0;
    allocation_count = 0;
    return memory;
}

template <class T, class I>
inline T* c_utl_memory<T, I>::detach()
{
    return (T*)detach_memory();
}

template <class T, class I>
inline T& c_utl_memory<T, I>::operator[](I i)
{
    assert(!is_read_only());
    assert(is_idx_valid(i));
    return memory[i];
}

template <class T, class I>
inline const T& c_utl_memory<T, I>::operator[](I i) const
{
    assert(is_idx_valid(i));
    return memory[i];
}

template <class T, class I>
inline T& c_utl_memory<T, I>::element(I i)
{
    assert(!is_read_only());
    assert(is_idx_valid(i));
    return memory[i];
}

template <class T, class I>
inline const T& c_utl_memory<T, I>::element(I i) const
{
    assert(is_idx_valid(i));
    return memory[i];
}

template <class T, class I>
bool c_utl_memory<T, I>::is_externally_allocated() const
{
    return (grow_size < 0);
}

template <class T, class I>
bool c_utl_memory<T, I>::is_read_only() const
{
    return (grow_size == EXTERNAL_CONST_BUFFER_MARKER);
}

template <class T, class I>
void c_utl_memory<T, I>::set_grow_size(int size)
{
    assert(!is_externally_allocated());
    assert(size >= 0);
    grow_size = size;
    validate_grow_size();
}

template <class T, class I>
inline T* c_utl_memory<T, I>::base()
{
    assert(!is_read_only());
    return memory;
}

template <class T, class I>
inline const T* c_utl_memory<T, I>::base() const
{
    return memory;
}

template <class T, class I>
inline int c_utl_memory<T, I>::num_allocated() const
{
    return allocation_count;
}

template <class T, class I>
inline int c_utl_memory<T, I>::count() const
{
    return allocation_count;
}

template <class T, class I>
inline bool c_utl_memory<T, I>::is_idx_valid(I i) const
{
    long x = i;
    return (x >= 0) && (x < allocation_count);
}

inline int utl_memory_calculate_new_allocation_count(int allocation_count, int grow_size, int new_size, int item_bytes)
{
    if (grow_size)
    {
        allocation_count = ((1 + ((new_size - 1) / grow_size)) * grow_size);
    }
    else
    {
        if (!allocation_count)
        {
            allocation_count = (31 + item_bytes) / item_bytes;
        }

        while (allocation_count < new_size) {
            allocation_count *= 2;
        }
    }

    return allocation_count;
}

template <class T, class I>
void c_utl_memory<T, I>::grow(int num) {
    assert(num > 0);

    if (is_externally_allocated())
    {
        assert(0);
        return;
    }

    auto old_allocation_count = allocation_count;
    int allocation_requested = allocation_count + num;

    int new_allocation_count = utl_memory_calculate_new_allocation_count(allocation_count, grow_size, allocation_requested, sizeof(T));

    if ((int)(I)new_allocation_count < allocation_requested)
    {
        if ((int)(I)new_allocation_count == 0 && (int)(I)(new_allocation_count - 1) >= allocation_requested)
        {
            --new_allocation_count;
        }
        else
        {
            if ((int)(I)allocation_requested != allocation_requested)
            {
                assert(0);
                return;
            }
            while ((int)(I)new_allocation_count < allocation_requested)
            {
                new_allocation_count = (new_allocation_count + allocation_requested) / 2;
            }
        }
    }

    allocation_count = new_allocation_count;

    if (memory) {
        auto ptr = sdk::mem_alloc->alloc(allocation_count * sizeof(T));

        memcpy(ptr, memory, old_allocation_count * sizeof(T));
        memory = (T*)ptr;
    }
    else {
        memory = (T*)sdk::mem_alloc->alloc(allocation_count * sizeof(T));
    }
}

template <class T, class I>
inline void c_utl_memory<T, I>::ensure_capacity(int num)
{
    if (allocation_count >= num)
        return;

    if (is_externally_allocated())
    {
        assert(0);
        return;
    }
    allocation_count = num;

    if (memory)
    {
        memory = (T*)sdk::mem_alloc->realloc(memory, allocation_count * sizeof(T));
    }
    else {
        memory = (T*)sdk::mem_alloc->alloc(allocation_count * sizeof(T));
    }
}

template <class T, class I>
void c_utl_memory<T, I>::purge()
{
    if (!is_externally_allocated())
    {
        if (memory)
        {
            sdk::mem_alloc->free((void*)memory);
            memory = 0;
        }
        allocation_count = 0;
    }
}

template <class T, class I>
void c_utl_memory<T, I>::purge(int number_of_elements)
{
    assert(number_of_elements >= 0);

    if (number_of_elements > allocation_count)
    {
        assert(number_of_elements <= allocation_count);
        return;
    }

    if (number_of_elements == 0)
    {
        purge();
        return;
    }

    if (is_externally_allocated())
    {
        return;
    }

    if (number_of_elements == allocation_count)
    {
        return;
    }

    if (!memory)
    {
        assert(memory);
        return;
    }
    allocation_count = number_of_elements;
    memory = (T*)sdk::mem_alloc->realloc(memory, allocation_count * sizeof(T));
}