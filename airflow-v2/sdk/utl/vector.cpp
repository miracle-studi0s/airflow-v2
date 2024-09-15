#include "vector.h"

#include "../sdk/sdk.h"

template <typename T>
void c_utl_vector<T>::grow_vector(int num)
{
    size += num;
    if (elements)
        elements = (T*)sdk::mem_alloc->realloc(elements, size * sizeof(T));
    else
        elements = (T*)sdk::mem_alloc->alloc(size * sizeof(T));
}

template <typename T>
inline int c_utl_vector<T>::add_to_head()
{
    return insert_before(0);
}

template <typename T>
inline int c_utl_vector<T>::add_to_tail()
{
    return insert_before(size);
}

template <typename T>
inline int c_utl_vector<T>::insert_after(int elem)
{
    return insert_before(elem + 1);
}

template <typename T>
int c_utl_vector<T>::insert_before(int elem)
{
    grow_vector();
    shift_elements_right(elem);
    Construct(&element(elem));
    return elem;
}

template <typename T>
inline int c_utl_vector<T>::add_to_head(const T& src)
{
    return insert_before(0, src);
}

template <typename T>
inline int c_utl_vector<T>::add_to_tail(const T& src)
{
    return insert_before(size, src);
}

template <typename T>
inline int c_utl_vector<T>::insert_after(int elem, const T& src)
{
    return insert_before(elem + 1, src);
}

template <typename T>
int c_utl_vector<T>::insert_before(int elem, const T& src)
{
    grow_vector();
    shift_elements_right(elem);
    CopyConstruct(&element(elem), src);
    return elem;
}

template <typename T>
void c_utl_vector<T>::shift_elements_right(int elem, int num)
{
    int num_to_move = size - elem - num;
    if ((num_to_move > 0) && (num > 0))
        memmove(&element(elem + num), &element(elem), num_to_move * sizeof(T));
}

template <typename T>
void c_utl_vector<T>::shift_elements_left(int elem, int num)
{
    int numToMove = size - elem - num;
    if ((numToMove > 0) && (num > 0))
    {
        memmove(&element(elem), &element(elem + num), numToMove * sizeof(T));

#ifdef _DEBUG
        memset(&element(size - num), 0xDD, num * sizeof(T));
#endif
    }
}

template <typename T>
void c_utl_vector<T>::fast_remove(int elem)
{
    Destruct(&element(elem));
    if (size > 0)
    {
        if (elem != size - 1)
            memcpy(&element(elem), &element(size - 1), sizeof(T));
        --size;
    }
}

template <typename T>
void c_utl_vector<T>::remove(int elem)
{
    Destruct(&element(elem));
    shift_elements_left(elem);
    --size;
}

template <typename T>
bool c_utl_vector<T>::find_and_remove(const T& src)
{
    int elem = get_offset(src);
    if (elem != -1)
    {
        remove(elem);
        return true;
    }
    return false;
}

template <typename T>
bool c_utl_vector<T>::find_and_fast_remove(const T& src)
{
    int elem = get_offset(src);
    if (elem != -1) {
        fast_remove(elem);
        return true;
    }
    return false;
}

template <typename T>
int c_utl_vector<T>::get_offset(const T& src) const
{
    for (auto i = 0; i < count(); ++i)
    {
        if (element(i) == src)
            return i;
    }
    return -1;
}