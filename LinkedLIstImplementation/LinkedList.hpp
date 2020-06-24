#include <iostream>
#include <stdexcept>
#include <cassert>

template <class T>
class LList
{
	struct Node
	{
		Node(Node * next = nullptr);
		Node(const T& val, Node * next = nullptr);
		T data;
		Node * p_next;
	};

public:

	// Конструктори
	LList();
	LList(const LList& other);
	LList& operator=(const LList &rhs);
	~LList();

	// Четене на елементи в списъка
	//  Само const версии за краткост
	// Би било добре да има и итератори,
	//  но отново са пропуснати за по-кратко
	const T& front() const;
	const T& end() const;
	const T& at(size_t pos) const;

	// Информативни методи
	bool is_empty() const;
	size_t size() const;

	// Добавяне на елементи
	void push_front(const T& val);
	void push_end(const T& val);
	void push_atPos(size_t pos, const T& val);

	// Премахване на елементи.
	//  Не връщат стойността на премахнатия елемент
	void pop_front();
	void pop_end();
	void pop_atPos(size_t pos);

	// Алгоритми
	void reverse();
	void toSet();
	void sort(bool stable = true);
	bool isSorted() const;
private:
	// Пазим връзка само към началото.
	//По-бавен достъп до последния елемент,
	//но по-проста реализация
	Node * head;
	size_t sz;

	void copy(const LList& other);
	void freeHeap();

	void split(Node* list, Node*& left, Node*& right);
	void split(Node* list, Node*& left, Node*& right, size_t sz);
	Node * merge(Node * left, Node * right);
	Node * mergeSort(Node * list);
	Node * mergeSort(Node * list, size_t sz);
};

template<class T>
inline LList<T>::Node::Node(const T& val, Node * next)
	:data(val), p_next(next)
{}

template<class T>
inline LList<T>::Node::Node(Node * next)
	: p_next(next)
{}

template<class T>
inline void LList<T>::copy(const LList<T>& other)
{
	Node dummy;
	Node * p_iter = &dummy;
	Node * curr = other.head;
	while (curr) {
		p_iter->p_next = new Node(curr->data);
		p_iter = p_iter->p_next;
		curr = curr->p_next;
	}

	head = dummy.p_next;
	sz = other.sz;
}

template<class T>
inline void LList<T>::freeHeap()
{
	Node * p_iter = head;
	Node * p_detach = head;

	for (size_t i = 0; i < sz; ++i) {
		p_detach = p_iter;
		p_iter = p_iter->p_next;
		delete p_detach;
	}

	head = nullptr;
	sz = 0;
}

template<class T>
inline LList<T>::LList()
	:head(nullptr), sz(0) {}

template<class T>
inline LList<T>::LList(const LList& other)
	: LList()
{
	copy(other);
}

template<class T>
inline LList<T>& LList<T>::operator=(const LList<T>& rhs)
{
	if (this != &rhs) {
		freeHeap();
		copy(rhs);
	}

	return *this;
}

template<class T>
inline LList<T>::~LList()
{
	freeHeap();
}

template<class T>
inline const T& LList<T>::at(size_t pos) const
{
	if (is_empty() || pos >= sz) {
		throw std::invalid_argument("Index out of bounds\n");
	}

	const Node * p_iter = head;
	for (size_t i = 0; i < pos; ++i, p_iter = p_iter->p_next)
		;
	return p_iter->data;
}

template<class T>
inline const T& LList<T>::front() const
{
	return at(0);
}

template< class T>
inline const T& LList<T>::end() const
{
	return at(sz - 1);
}

template<class T>
inline size_t LList<T>::size() const
{
	return sz;
}

template<class T>
inline void LList<T>::push_atPos(size_t pos, const T & val)
{
	if (pos > sz) {
		throw std::invalid_argument("Index out of bounds\n");
	}

	if (pos == 0) {
		head = new Node(val, head);
	}

	else {
		Node * p_iter = head;
		for (size_t i = 0; i < pos - 1; ++i, p_iter = p_iter->p_next)
			;

		p_iter->p_next = new Node(val, p_iter->p_next);
	}

	++sz;
}

template<class T>
inline void LList<T>::push_front(const T & val)
{
	push_atPos(0, val);
}

template<class T>
inline void LList<T>::push_end(const T & val)
{
	push_atPos(sz, val);
}

template<class T>
inline void LList<T>::pop_atPos(size_t pos)
{
	if (is_empty() || pos > sz - 1) {
		throw std::invalid_argument("Index out of bounds\n");
	}

	Node * p_detach = head;

	if (pos == 0) {
		head = head->p_next;
	}
	else {
		Node * p_iter = head;
		for (size_t i = 0; i < pos - 1; ++i, p_iter = p_iter->p_next)
			;

		p_detach = p_iter->p_next;
		p_iter->p_next = p_detach->p_next;
	}

	--sz;
	delete p_detach;
}

template<class T>
inline void LList<T>::pop_front()
{
	pop_atPos(0);
}

template<class T>
inline void LList<T>::pop_end()
{
	pop_atPos(sz - 1);
}

template<class T>
inline bool LList<T>::is_empty() const
{
	return sz == 0;
}

template<class T>
inline void LList<T>::reverse()
{
	Node * curr = head;
	Node * prev = nullptr;
	Node * next = nullptr;

	while (curr != nullptr) {
		next = curr->p_next;
		curr->p_next = prev;
		prev = curr;
		curr = next;
	}

	head = prev;

	
	//1->2->3->4 -------- 1<-2<-3<-4
	
}

template<class T>
inline void LList<T>::toSet()
{
	Node * i, *j, *tmp;
	i = head;
	while (i && i->p_next) {
		j = i;
		while (j->p_next != nullptr) {
			if (i->data == j->p_next->data) {
				tmp = j->p_next;
				j->p_next = j->p_next->p_next;
				--sz;
				delete tmp;
			}
			else {
				j = j->p_next;
			}
		}
		i = i->p_next;
	}
}

template<class T>
inline void LList<T>::sort(bool stable)
{
	head = stable ? mergeSort(head, sz) : mergeSort(head);
}

template<class T>
inline bool LList<T>::isSorted() const
{
	if (sz < 3) return true;

	Node* p_it = head;
	while (p_it->p_next && p_it->data == p_it->p_next->data)
		p_it = p_it->p_next;
	if (!p_it->p_next) return true;

	bool asc = p_it->data < p_it->p_next->data;
	while (p_it->p_next) {
		if (p_it->data != p_it->p_next->data &&
			asc != p_it->data < p_it->p_next->data)
			return false;
		p_it = p_it->p_next;
	}
	return true;
}

template<class T>
inline void LList<T>::split(Node* list, Node *& left, Node*& right)
{
	Node dummyLeft;
	Node dummyRight;
	Node* p_it = list;
	Node* p_end_left = &dummyLeft;
	Node* p_end_right = &dummyRight;

	bool swithToLeft = true;
	while (p_it) {
		if (swithToLeft) {
			p_end_left->p_next = p_it;
			p_end_left = p_end_left->p_next;
			swithToLeft = false;
		}
		else {
			p_end_right->p_next = p_it;
			p_end_right = p_end_right->p_next;
			swithToLeft = true;
		}
		p_it = p_it->p_next;
	}

	p_end_left->p_next = nullptr;
	p_end_right->p_next = nullptr;

	left = dummyLeft.p_next;
	right = dummyRight.p_next;
}

template<class T>
inline void LList<T>::split(Node* head, Node *& left, Node*& right, size_t listSz)
{
	Node* p_it = head;
	left = p_it;
	size_t mid = listSz / 2 + listSz % 2;
	for (size_t i = 0; i < mid - 1; i++) {
		p_it = p_it->p_next;
	}

	right = p_it->p_next;
	p_it->p_next = nullptr;
}

template<class T>
inline typename LList<T>::Node * LList<T>::merge(Node * left, Node * right)
{
	Node merged(0);
	Node * p_curr = &merged;
	while (left && right) {
		if (left->data < right->data) {
			p_curr->p_next = left;
			left = left->p_next;
		}
		else {
			p_curr->p_next = right;
			right = right->p_next;
		}
		p_curr = p_curr->p_next;
	}
	p_curr->p_next = left ? left : right;
	return merged.p_next;
}

template<class T>
inline typename LList<T>::Node * LList<T>::mergeSort(Node * list, size_t size)
{
	if (list->p_next == nullptr) {
		return list;
	}
	Node *left = nullptr, *right = nullptr;
	split(list, left, right, size);
	return merge(mergeSort(left, size / 2 + size % 2), mergeSort(right, size / 2));
}

template<class T>
inline typename LList<T>::Node * LList<T>::mergeSort(Node * list)
{
	if (list->p_next == nullptr) {
		return list;
	}
	Node *left = nullptr, *right = nullptr;
	split(list, left, right);
	return merge(mergeSort(left), mergeSort(right));
}


/////////////////////////////////////////////////
// Прости unit test методи за тестване на списъка
// директна имплементация

void testPush()
{
	LList<int> test;
	test.push_front(2);
	test.push_front(1);
	test.push_end(5);
	test.push_atPos(2, 3);
	test.push_atPos(3, 4);
	for (int i = 1; i <= 5; i++) {
		assert(test.at(unsigned(i - 1)) == i);
	}

	bool flag = false;
	try {
		test.push_atPos(unsigned(-1), 0);
	}
	catch (const std::invalid_argument&) {
		flag = true;
	}

	assert(flag);
}

void testPop(unsigned seed = 1)
{
	LList<int> test;
	bool flag = false;
	try {
		test.pop_atPos(0);
	}
	catch (const std::invalid_argument&) {
		flag = true;
	}

	assert(flag);

	flag = false;
	try {
		test.pop_atPos(1);
	}
	catch (const std::invalid_argument&) {
		flag = true;
	}

	assert(flag);

	srand(seed);
	const size_t testSz = 100;

	for (size_t i = 0; i < testSz; i++) {
		test.push_atPos(i, i);
	}

	flag = false;
	try {
		for (size_t i = 0; i < testSz; i++) {
			test.pop_atPos(rand() % (testSz - i));
		}
	}
	catch (const std::invalid_argument&) {
		flag = true;
	}

	assert(flag || test.is_empty());
}

void testPos(unsigned seed = 1)
{
	LList<int> test;

	srand(seed);
	const size_t testSz = 100;

	for (size_t i = 0; i < testSz; i++) {
		test.push_atPos(i, rand() % testSz);
	}

	srand(seed);
	for (size_t i = 0; i < testSz; i++) {
		assert(rand() % testSz == test.at(i));
	}

	bool flag = false;
	try {
		test.at(unsigned(-1));
	}
	catch (const std::invalid_argument&) {
		flag = true;
	}

	assert(flag);
}

void testCpy(unsigned seed = 1)
{
	LList<int> test;

	srand(seed);
	const size_t testSz = 100;

	for (size_t i = 0; i < testSz; i++) {
		test.push_atPos(i, rand() % testSz);
	}

	LList<int> testCpy(test);
	for (size_t i = 0; i < testSz; i++) {
		assert(testCpy.at(i) == test.at(i));
	}

	assert(testCpy.size() == test.size());

	LList<int> testOp = test;
	for (size_t i = 0; i < testSz; i++) {
		assert(testCpy.at(i) == test.at(i));
	}

	assert(testOp.size() == testOp.size());
}

void testReverse()
{
	LList<int> test;
	const size_t testSz = 100;
	for (size_t i = 0; i < testSz; i++) {
		test.push_front(i);
	}

	test.reverse();
	for (size_t i = 0; i < testSz; i++) {
		assert(test.at(i) == i);
	}
}

void testSet(unsigned seed = 1)
{
	LList<int> test;
	const size_t testSz = 100;
	const size_t set_sz = 5;
	srand(seed);

	for (size_t i = 0; i < testSz; i++) {
		test.push_front(rand() % set_sz);
	}

	test.toSet();
	assert(test.size() <= 5);
}

void testIsSorted(unsigned seed = 1)
{
	const size_t testSz = 100;
	const size_t set_sz = 5;
	srand(seed);

	{
		LList<int> test1;
		for (size_t i = 0; i < testSz; ++i)
			test1.push_front(i);
		assert(test1.isSorted());
	}

	{
		LList<int> test2;
		for (size_t i = testSz; i > 0; --i)
			test2.push_front(i);
		assert(test2.isSorted());
	}

	{
		LList<int> test3;
		for (size_t i = set_sz; i > 0; --i)
			test3.push_front(0);

		for (size_t i = 0; i < testSz; ++i)
			test3.push_front(i);
		assert(test3.isSorted());
	}

	{
		LList<int> test4;
		for (size_t i = set_sz; i > 0; --i)
			test4.push_front(0);

		for (size_t i = testSz; i > 0; --i)
			test4.push_front(i);
		assert(!test4.isSorted());
	}

	{
		LList<int> test5;
		for (size_t i = 0; i < testSz; ++i)
			test5.push_front(i / 4);
		assert(test5.isSorted());
	}

	{
		LList<int> test6;
		for (size_t i = 0; i < testSz; i++) {
			test6.push_front(rand() % set_sz);
		}
		assert(!test6.isSorted());
	}
}

void testSort(unsigned seed = 1)
{
	LList<int> test;
	const size_t testSz = 100000;
	const size_t moduleSz = 2000;
	srand(seed);

	for (size_t i = 0; i < testSz; i++) {
		test.push_front(rand() % moduleSz);
	}

	test.sort(true);
	assert(test.isSorted());

	test.reverse();
	test.sort(false);
	assert(test.isSorted());
}

void makeTests()
{
	testPush();
	testPos();
	testPop();
	testCpy();
	testReverse();
	testSet();
	testIsSorted();
	testSort();
}

int main()
{
	makeTests();
	return 0;
}