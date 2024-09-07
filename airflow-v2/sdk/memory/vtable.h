#pragma once

namespace vtable
{
    template <typename T = void*>
    inline T get(void* class_, unsigned int index) 
    {
        if (!class_)
            return T{};

        void** table = *reinterpret_cast<void***>(class_);
        if (!table)
            return T{};

        return reinterpret_cast<T>(table[index]);
    }

    template <typename T, typename... Args>
    inline T call(void* class_, unsigned int index, Args... args) 
    {
        auto func = get<T(__thiscall*)(void*, Args...)>(class_, index);
        return func(class_, args...);
    }
}