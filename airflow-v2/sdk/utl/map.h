#pragma once

#include <cstdint>
#include <cstddef>
#include <optional>

template <typename K, typename V>
class c_utl_map
{
public:
    struct node_t 
    {
        int left;
        int right;
        int parent;
        int tag;
        K key;
        V value;
    };

    char pad_0[0x8];
    node_t* data;
    char pad_1[0x8];
    int root;
    int size;
    char pad_2[0x8];

    auto begin() const { return data; }
    auto end() const { return data + size; }

    std::optional<V> find_by_key(K key) const
    {
        int current = root;
        while (current != -1) 
        {
            const node_t& element = data[current];
            if (element.key < key)
                current = element.right;
            else if (element.key > key)
                current = element.left;
            else
                return element.value;
        }
        return std::nullopt;
    }
};