#pragma once

#include <cassert>

template <class T, class I = int>
class c_utl_memory
{
public:
    c_utl_memory(int nGrowSize = 0, int nInitSize = 0);
    c_utl_memory(T* memory, int numElements);
    c_utl_memory(const T* memory, int numElements);
    ~c_utl_memory();

    void init(int nGrowSize = 0, int nInitSize = 0);

    class iterator_t
    {
    public:
        iterator_t(I i) : index(i) { }

        I index;

        bool operator==(const iterator_t& it) const
        {
            return index == it.index;
        }
        bool operator!=(const iterator_t& it) const
        {
            return index != it.index;
        }
    };

    iterator_t first() const
    {
        return iterator_t(is_idx_valid(0) ? 0 : invalid_index());
    }

    iterator_t next(const iterator_t& it) const
    {
        return iterator_t(is_idx_valid(it.index + 1) ? it.index + 1 : invalid_index());
    }

    I get_index(const iterator_t& it) const
    {
        return it.index;
    }
    bool is_idx_after(I i, const iterator_t& it) const
    {
        return i > it.index;
    }
    bool is_valid_iterator(const iterator_t& it) const
    {
        return is_idx_valid(it.index);
    }
    iterator_t invalid_iterator() const
    {
        return iterator_t(invalid_index());
    }

    T& operator[](I i);
    const T& operator[](I i) const;
    T& element(I i);
    const T& element(I i) const;

    bool is_idx_valid(I i) const;

    static const I INVALID_INDEX = (I)-1;
    static I invalid_index() {
        return INVALID_INDEX;
    }

    T* base();
    const T* base() const;

    void set_external_buffer(T* memory, int numElements);
    void set_external_buffer(const T* memory, int numElements);
    void assume_memory(T* memory, int nSize);
    T* detach();
    void* detach_memory();

    void swap(c_utl_memory<T, I>& mem);
    void convert_to_growable_memory(int nGrowSize);
    int num_allocated() const;
    int count() const;
    void grow(int num = 1);
    void ensure_capacity(int num);
    void purge();
    void purge(int numElements);
    bool is_externally_allocated() const;
    bool is_read_only() const;
    void set_grow_size(int size);
protected:
    void validate_grow_size() const { }

    enum {
        EXTERNAL_BUFFER_MARKER = -1,
        EXTERNAL_CONST_BUFFER_MARKER = -2,
    };
public:
    T* memory;
    int allocation_count;
    int grow_size;
};