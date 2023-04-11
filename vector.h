#pragma once

#include <iostream>
#include <type_traits>
#include <random>
#include <initializer_list>
#include <memory>

static const int BASE_CAPACITY = 8;

template <typename T> class Vector {
public:
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = ptrdiff_t;
	using reference = value_type&;

	// 默认构造函数
	Vector() {
		std::cout << "Vector 默认构造的调用\n";
		_capacity = 128;
		_elem = (T*)malloc(sizeof(T) * _capacity);
		_size = 0;
	}


	// initilizer_list 构造函数
	Vector(std::initializer_list<T> init_list) : Vector(init_list.size()) {
		std::cout << "Vector initilizer_list 构造的调用\n";
		std::uninitialized_move(init_list.begin(), init_list.end(), _elem);
	}

	// 拷贝构造
	Vector(const Vector& vec) {
		std::cout << "Vector 拷贝构造的调用\n";
		_capacity = vec._size;
		_size = vec._size;
		// 深拷贝
		_elem = (T*)malloc(sizeof(T) * _size);
		// 将vec中的数据都拷贝过来
		std::uninitialized_copy_n(vec.begin(), _size, _elem);
	}


	//移动构造函数
	Vector(Vector&& vec) {
		std::cout << "Vectory 移动构造的调用\n";
		_elem = vec._elem;
		vec._elem = nullptr;
		vec.~Vector();
	}

	// 参数构造函数
	Vector(std::size_t capacity) {
		std::cout << "Vector 参数构造的调用\n";
		_capacity = _size = capacity;
		_elem = (T*)malloc(sizeof(T) * _capacity);
		std::uninitialized_default_construct_n(_elem, _size);
	}

	// 析构函数
	~Vector() {
		if (_elem != nullptr) {
			std::cout << "Vector 析构的调用\n";
			std::destroy_n(_elem, _size);
			free(_elem);
			_elem = nullptr;
			_size = _capacity = 0;
		}
	}


	// operator= 防止浅拷贝问题
	Vector& operator=(const Vector& vec) {
		if (&vec == this) return *this;

		std::cout << "Vector operator=调用\n";
		// 先判断原来堆区是否有数据，如果有先释放
		if (_elem != nullptr) {
			free(_elem);
			_elem = nullptr;
			_capacity = 0;
			_size = 0;
		}

		_capacity = vec->_capacity;
		_size = vec->_size;

		// 深拷贝
		_elem = (T*)malloc(sizeof(T) * _capacity);

		// 将vec中的数据都拷贝过来
		for (int i = 0; i < _size; i++)
			_elem[i] = vec->_elem[i];
		return *this;
	}


	const T& operator[](size_t index) const;      // 访问指定元素
	T& operator[](size_t index);                  // 访问指定元素
	const T& front() const;                       // 访问第一个元素
	T& front();                                   // 访问第一个元素
	const T& back() const;                        // 访问最后一个元素
	T& back();                                    // 访问最后一个元素
	bool empty() const { return !_size; }         // 判空
	size_t size() const { return _size; }         // 容纳元素数
	size_t max_size() const { return _capacity; } // 容纳最大的元素数
	size_t capacity() const {
		return _capacity;
	}                         // 返回当前存储空间能够容纳的元素数
	void reserve(size_t val); // 预留存储空间
	void shrink_to_fit(); // 通过释放未使用的内存减少内存的使用
	void clear();
	void insert(size_t index, const T& val);
	T erase(size_t index);
	void push_back(const T& val);
	void push_back(T&& val);

	template <class... Args> void emplace_back(Args &&...args);

	void pop_back();
	void resize(size_t count, const value_type& value = T{});
	void swap(Vector& other);
	bool operator==(const Vector<T>& other);

	friend bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) { return lhs.operator==(rhs); }


protected:
	void expend(); // 扩容

private:
	size_type _size;
	size_type _capacity = BASE_CAPACITY;
	T* _elem;
};

template <typename T> void Vector<T>::expend() {
	if (_size < _capacity)
		return;
	if (_capacity < BASE_CAPACITY)
		_capacity = BASE_CAPACITY;
	T* _origin_elem = _elem;
	_elem = (T*)malloc(sizeof(T) * (_capacity <<= 1));  // new int[_capacity <<= 1];
	std::uninitialized_move_n(_origin_elem, _capacity, _elem);
	free(_origin_elem);
	_origin_elem = nullptr;
}

template <typename T> const T& Vector<T>::operator[](size_t index) const {
	return _elem[index];
}

template <typename T> T& Vector<T>::operator[](size_t index) {
	return const_cast<T&>(static_cast<const Vector&>(*this)[index]);
}

template <typename T> const T& Vector<T>::front() const { return _elem[0]; }

template <typename T> T& Vector<T>::front() {
	return const_cast<T&>(static_cast<const Vector*>(this)->front());
}

template <typename T> const T& Vector<T>::back() const {
	return _elem[_size - 1];
}

template <typename T> T& Vector<T>::back() {
	return const_cast<T&>(static_cast<const Vector*>(this)->back());
}

template <typename T> void Vector<T>::reserve(size_t new_cap) {
	while (size() < new_cap) {
		expend();
	}
}

template <typename T> void Vector<T>::shrink_to_fit() {
	_capacity = _size;
	auto new_space = (T*)malloc(sizeof(T) * _capacity);
	std::uninitialized_move_n(_elem, _size, new_space);
	std::swap(new_space, _elem);
	free(new_space);
	new_space = nullptr;
}

template <typename T> void Vector<T>::clear() {
	std::destroy_n(_elem, _size);
	_size = 0;
}

template <typename T> void Vector<T>::insert(size_t index, const T& val) {
	if (_size + 1 > _capacity) {
		expend();
	}
	if (index == _size) {
		std::construct_at(_elem + _size, val);
	}
	else {
		std::construct_at(_elem + _size, back());
		for (int i = _size-1; i > index; i--) {
			_elem[i] = std::move(_elem[i - 1]);
		}
		_elem[index] = val;
		++_size;
	}
}

template <typename T> T Vector<T>::erase(size_t index) {
	auto temp = std::move(_elem[index]);
	for (size_t i = index; i < size() - 1; i++) {
		_elem[i] = std::move(_elem[i + 1]);
	}
	--_size;
	return temp; // NRVO
}

template <typename T> void Vector<T>::push_back(const T& val) {
	if (_size + 1 > _capacity) {
		expend();
	}
	std::construct_at(_elem + _size, val);
	++_size;
}

template <typename T> void Vector<T>::push_back(T&& val) {
	if (_size + 1 > _capacity) {
		expend();
	}
	std::construct_at(_elem + _size, std::move(val));
	++_size;
}

template <typename T> void Vector<T>::pop_back() { std::destroy_at(_elem + (--_size)); }

template <typename T>
void Vector<T>::resize(size_t count, const Vector<T>::value_type& value) {
	if (_size > count) {
		for (int i = count; i < _size; ++i) {
			_elem[i].~T();
		}
	}
	else if (_size < count) {
		while (capacity() < count) {
			expend();
		}
		for (std::size_t i = size(); i < count; ++i) {
			_elem[i] = value;
		}
	}

	_size = count;
}

template <typename T> void Vector<T>::swap(Vector& other) {
	std::swap(_elem, other._elem);
	std::swap(_size, other._size);
	std::swap(_capacity, other._capacity);
}

template <typename T> bool Vector<T>::operator==(const Vector<T>& other) {
	if (size() == other.size()) {
		for (std::size_t i = 0; i < size(); i++) {
			if (_elem[i] != other[i])
				return false;
		}
		return true;
	}
	else {
		return false;
	}
}

template <typename T>
template <class... Args>
inline void Vector<T>::emplace_back(Args &&...args) {
	static_assert(!std::is_invocable_v<T, Args...>);

	if (_size + 1 > _capacity) {
		expend();
	}
	_elem[_size++] = T(std::forward<Args>(args)...);
}


template< class T >
void swap(Vector<T>& lhs, Vector<T>& rhs) {
	lhs.swap(rhs);
}
