#pragma once

template <class T>
class c_utl_vector
{
public:
    auto begin() const { return data; }
    auto end() const { return data + size; }

    auto at(int i) const { return data[i]; }
    auto at_ptr(int i) const { return data + i; }

    bool exists(T val) const {
        for (const auto& it : *this)
            if (it == val) return true;
        return false;
    }
    bool is_empty() const { return size == 0; }

    int size;
    char pad0[0x4];
    T* data;
    char pad1[0x8];
};

template <typename T>
class c_network_utl_vector 
{
public:
    unsigned int size;
    T* elements;
};