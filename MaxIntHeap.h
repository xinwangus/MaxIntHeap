/*
 * A simple experimenatl implementation of Max Heap of Int
 * using an array.
 *
 * We could also just use C++ standard lib of priority Queue.
 */
#include <iostream>

class
MaxIntHeap
{
public:
	MaxIntHeap(int s);
	~MaxIntHeap();

	bool addInt (int a);
	bool popMax (int& out);

private:
	void _heapUp (unsigned int child);
	void _heapDown (unsigned int parent);

	void _swap (unsigned int a, unsigned int b);

	int* _data;
	unsigned int _size;
	unsigned int _tail_marker;	
};

