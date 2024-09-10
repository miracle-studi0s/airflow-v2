#pragma once

template <class T>
struct resource_binding
{
	T* data;
	unsigned long long unk;
	unsigned long long unk2;
	volatile unsigned int* references_count;
};

template <class T>
class c_strong_handle
{
public:
	operator T* ()
	{

		if (!binding)
			return nullptr;

		return binding->data;
	}

	T* operator->()
	{

		if (!binding)
			return nullptr;

		return binding->data;
	}
public:
	const resource_binding<T>* binding;
};