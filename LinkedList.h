#pragma once


#pragma once

#include <iostream>



template <typename T>
class LinkedList
{
protected:
	template <typename T>
	struct Node
	{
		T value;
		Node<T>* next;
		Node<T>* last;
	};

	Node<T>* head;
	Node<T>* back;
	size_t lenght;
public:
	LinkedList() : head(nullptr), back(nullptr), lenght(0) {};
	LinkedList(const std::initializer_list<T>& lst);
	~LinkedList();

	size_t size() const { return lenght; }
	bool empty() const { return !head; }

	T& getFront() { if (head) return head->value; else throw std::out_of_range("overload"); }
	const T& getFront() const { if (head) return head->value; else throw std::out_of_range("overload"); }
	T& getBack() { if (back) return back->value; else throw std::out_of_range("overload"); }
	const T& getBack() const { if (back) return back->value; else throw std::out_of_range("overload"); }

	T& get(int index);
	const T& get(int index) const;

	T& operator[](int index) { return get(index); };
	const T& operator[](int index) const { return get(index); };

	void push_front(const T& pValue);
	void push_back(const T& pValue);
	void pop_front();
	void pop_back();

	void insert(int index, const T& pValue);
	void pop(int index);

	void clear();

	std::ostream& print(std::ostream& out) const;
	friend std::ostream& operator<<(std::ostream& out, const LinkedList<T>& linkedList) { return linkedList.print(out); }
};

template<typename T>
inline LinkedList<T>::LinkedList(const std::initializer_list<T>& lst) : LinkedList()
{
	for (const T* item = lst.begin(); item != lst.end(); item++)
		push_back(*item);
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	Node<T>* tmp = head;
	while (tmp)
	{
		Node<T>* toDelete = tmp;
		tmp = tmp->next;
		delete toDelete;
	}
}

template<typename T>
inline T& LinkedList<T>::get(int index)
{
	if (index < 0 || index >= lenght)
		throw std::out_of_range("overload");

	Node<T>* tmp = head;
	while (index-- > 0)
		tmp = tmp->next;
	return tmp->value;
}


template<typename T>
inline const T& LinkedList<T>::get(int index) const
{
	if (index < 0 || index >= lenght)
		throw std::out_of_range("overload");

	Node<T>* tmp = head;
	while (index-- > 0)
		tmp = tmp->next;
	return tmp->value;
}

template <typename T>
inline void LinkedList<T>::push_front(const T& pValue)
{
	Node<T>* tmp = new Node<T>{ pValue, head, nullptr };
	head = tmp;
	if (lenght++ == 0)
		back = tmp;
}

template<typename T>
inline void LinkedList<T>::push_back(const T& pValue)
{
	Node<T>* tmp = new Node<T>{ pValue, nullptr, back };
	if (back)
		back->next = tmp;

	back = tmp;
	if (lenght++ == 0)
		head = tmp;
}

template<typename T>
inline void LinkedList<T>::pop_front()
{
	if (lenght == 0)
		throw std::out_of_range("overload");

	Node<T>* tmp = head;
	head = tmp->next;
	delete tmp;

	if (--lenght == 0)
		back = nullptr;
}

template<typename T>
inline void LinkedList<T>::pop_back()
{
	if (lenght == 0)
		throw std::out_of_range("overload");

	Node<T>* tmp = back;
	back = tmp->last;

	if (back)
		back->next = nullptr;
	delete tmp;

	if (--lenght == 0)
		head = nullptr;
}

template<typename T>
inline void LinkedList<T>::insert(int index, const T& pValue)
{
	if (index < 0 || index > lenght)
		throw std::out_of_range("overload");
	if (index == 0)
	{
		push_front(pValue);
		return;
	}
	if (index == lenght)
	{
		push_back(pValue);
		return;
	}

	Node<T>* tmp = head;
	while (index--)
		tmp = tmp->next;

	Node<T>* newElement = new Node<T>{ pValue, tmp, tmp->last };
	tmp->last->next = newElement;
	tmp->last = newElement;
	lenght++;
}

template<typename T>
inline void LinkedList<T>::pop(int index)
{
	if (index < 0 || index >= lenght)
		throw std::out_of_range("overload");

	Node<T>* tmp = head;
	while (index--)
		tmp = tmp->next;

	if (tmp->last)
		tmp->last->next = tmp->next;
	else
		head = tmp->next;

	if (tmp->next)
		tmp->next->last = tmp->last;
	else
		back = tmp->last;

	delete tmp;
	lenght--;
}

template<typename T>
inline void LinkedList<T>::clear()
{
	Node<T>* tmp = head;
	while (tmp)
	{
		Node<T>* toDelete = tmp;
		tmp = tmp->next;
		delete toDelete;
	}

	head = nullptr;
	back = nullptr;
	lenght = 0;
}

template<typename T>
inline std::ostream& LinkedList<T>::print(std::ostream& out) const
{
	Node<T>* tmp = head;
	out << "[ ";
	for (int i = 0; i < lenght; i++)
	{
		out << tmp->value;
		if (i != lenght - 1)
			out << ", ";
		tmp = tmp->next;
	}
	out << " ]";
	return out;
}
