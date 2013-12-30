#pragma once
#include <vector>
template<typename T>
class Stack
{
public:
	typedef T value_type;

public:
	void push(const T& val);
	T pop();
	T exchangeTop(const T& val);
	T& top();
	const T& top() const;

	typename std::vector<T>::iterator begin();
	typename std::vector<T>::iterator end();

	typename std::vector<T>::const_iterator begin() const;
	typename std::vector<T>::const_iterator end() const;

	bool empty();

	T& operator[](std::size_t index);
private:
	std::vector<value_type> m_content;
};

template<typename T>
void Stack<T>::push(const T& val)
{
	m_content.push_back(val);
}

template<typename T>
T Stack<T>::pop()
{
	T top = m_content.back();
	m_content.pop_back();
	return top;
}

template<typename T>
T Stack<T>::exchangeTop(const T& val)
{
	T top = m_content.back();
	m_content.pop_back();
	m_content.push_back(val);
	return top;
}

template<typename T>
T& Stack<T>::top()
{
	return m_content.back();
}

template<typename T>
const T& Stack<T>::top() const
{
	return m_content.back();
}

template<typename T>
typename std::vector<T>::iterator Stack<T>::begin()
{
	return m_content.begin();
}

template<typename T>
typename std::vector<T>::iterator Stack<T>::end()
{
	return m_content.end();
}

template<typename T>
typename std::vector<T>::const_iterator Stack<T>::begin() const
{
	return m_content.begin();
}

template<typename T>
typename std::vector<T>::const_iterator Stack<T>::end() const
{
	return m_content.end();
}

// 0 is top
template<typename T>
T& Stack<T>::operator[](std::size_t index)
{
	return m_content.at(m_content.size() - 1 - index);
}

template<typename T>
bool Stack<T>::empty()
{
	return m_content.empty();
}