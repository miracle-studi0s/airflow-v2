#pragma once

template <typename T>
class c_utl_vector
{
public:
    c_utl_vector()
    {
        size = 0;
        elements = nullptr;
    }

    inline T& element(int i)
    {
        return elements[i];
    }

    inline const T& element(int i) const
    {
        return elements[i];
    }

    T& operator[](int i)
    {
        return elements[i];
    }

    int count() const
    {
        return size;
    }

    int size;
    T* elements;

    int add_to_head();
    int add_to_tail();
    int insert_before(int elem);
    int insert_after(int elem);
    int add_to_head(const T& src);
    int add_to_tail(const T& src);
    int insert_before(int elem, const T& src);
    int insert_after(int elem, const T& src);
    void grow_vector(int num = 1);
    void shift_elements_right(int elem, int num = 1);
    void shift_elements_left(int elem, int num = 1);
    void fast_remove(int elem);
    void remove(int elem);
    bool find_and_remove(const T& src);
    bool find_and_fast_remove(const T& src);
    int get_offset(const T& src) const;
};

template <typename T>
class c_network_utl_vector
{
public:
    unsigned int size;
    T* elements;
};