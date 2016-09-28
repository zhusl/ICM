// Name:	lightlist.h
// Date:	08/10/2016
// Version:	1.0.0.0

#ifndef _SYSTEM_LIGHTLIST_H_
#define _SYSTEM_LIGHTLIST_H_
#include "macro.h"
#include "memory.h"

SYSTEM BEGIN
template <typename T>
class lightlist
{
public:
	using iterator = T*;
public:
	lightlist() = default;

	lightlist(size_t capacity)
		: _capacity(capacity), data(Memory::create<T>(_capacity), Memory::free<T>) {}

	lightlist(T* begin, T* end)
		: _capacity(end - begin), data(Memory::copyOf(begin, _capacity), Memory::free<T>) {}

	template <typename Iter>
	lightlist(Iter begin, Iter end)
		: _capacity(end - begin), data(Memory::create<T>(_capacity), Memory::free<T>) {
		T* ptr = data.get();
		for (Iter p = begin; p != end; ++p)
			*ptr++ = *p;
	}

	template <typename Container>
	lightlist(const Container &con)
		: lightlist(con.begin(), con.end()) {}

	template <size_t N>
	lightlist(T(&arr)[N])
		: lightlist(std::begin(arr), std::end(arr)) {}

	lightlist(const std::initializer_list<T> &il)
		: lightlist(il.begin(), il.end()) {}

	lightlist(const T &t)
		: lightlist({ t }) {}

	~lightlist() {}

	T* begin() { return data.get(); }
	T* end() { return data.get() + _capacity; }
	const T* begin() const { return data.get(); }
	const T* end() const { return data.get() + _capacity; }
	const T* cbegin() const { return data.get(); }
	const T* cend() const { return data.get() + _capacity; }

	T& operator[](size_t id) { return data.get()[id]; }
	const T& operator[](size_t id) const { return data.get()[id]; }

	T& front() { return *begin(); }
	const T& front() const { return *begin(); }
	T& back() { return *(data.get() + _capacity - 1); }
	const T& back() const { return *(data.get() + _capacity - 1); }

	size_t size() const { return _capacity; }
	bool empty() const { return _capacity == 0; }

private:
	size_t _capacity = 0;
	std::shared_ptr<T> data = nullptr;
};

template <typename T>
class lightlist_creater
{
public:
	lightlist_creater(size_t n) : _count(0), _data(n) {}

	void push_back(const T &e) {
		_data[_count++] = e;
	}
	void clear() {
		for (size_t i : range(0, _data.size()))
			_data[i].~T();
		_count = 0;
	}
	lightlist<T> data() const {
		return _data;
	}
	size_t size() const {
		return _count;
	}
	size_t capacity() const {
		return _data.size();
	}

private:
	size_t _count;
	lightlist<T> _data;
};
END

#endif
