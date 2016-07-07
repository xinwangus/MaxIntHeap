#include "MaxIntHeap.h"
#include <random>

using namespace std;

MaxIntHeap::
MaxIntHeap(int s):
_size(s),_tail_marker(0),_data(0)
{
}

MaxIntHeap::
~MaxIntHeap()
{
	if (_data) {
		delete[] _data;
	}
}

void
MaxIntHeap::
_swap (unsigned int a, unsigned int b)
{
	// todo check a, b are valid or not.
	int tmp = _data[a];
	_data[a] = _data[b];
	_data[b] = tmp;
}

void
MaxIntHeap::
_heapUp (unsigned int child)
{
	unsigned int p, l, r;
	if (child == 0) { return; }
	if (child % 2) {
		l = child;
		r = l + 1;
		p = (l - 1)/2;
	} else {
		r = child;
		l = r - 1;
		p = (l - 1)/2;
	}
		
	if ((_data[l] >= _data[r]) &&
	    (_data[l] > _data[p])) {
		_swap(l, p);
		_heapUp(p);
	} 

	if ((r <= _tail_marker) && // valid
	    (_data[r] >= _data[l]) &&
	    (_data[r] > _data[p])) {
		_swap(r, p);
		_heapUp(p);
	} 
	// stop, heap condition is good.
}

void
MaxIntHeap::
_heapDown (unsigned int parent)
{
	unsigned int p, l, r;
	p = parent;
	l = 2*p + 1;
	r = 2*p + 2;

	// both children not valid, we are done.
	if (l > _tail_marker) { return; }

	if (r > _tail_marker) { // only l valid.
		if (_data[p] < _data[l]) {
			_swap(p, l);
			// we are done.
			return;
		}
	}

	// both children valid;
	if ((_data[l] >= _data[r]) &&
	    (_data[l] > _data[p])) {
		_swap(l, p);
		_heapDown(l);
	} 

	if ((_data[r] >= _data[l]) &&
	    (_data[r] > _data[p])) {
		_swap(r, p);
		_heapDown(r);
	}
	// stop.
}


// Add from the tail, then swap up.
bool
MaxIntHeap::
addInt (int a)
{
	if ((_data == 0) && (_size > 0)) {
		_data = new int[_size + 1];
	}
	if (_data == 0) { return false; }

	_data[_tail_marker] = a;
	_heapUp(_tail_marker);
	_tail_marker++;

	return true;
}

// Pop from the head, then swap down.
bool
MaxIntHeap::
popMax (int& out)
{
	if (_tail_marker == 0) { return false; }
	out = _data[0];
	_data[0] = _data[_tail_marker - 1];
	_tail_marker--;
	_heapDown(0);
	return true;
}


int
main()
{
	int array[] = {7, 5, 89, 4, 3, -34};
	int tmp;
	unsigned int s = sizeof(array)/sizeof(int);
	MaxIntHeap myHeap(s);

	for(int i = 0; i < s; i++) {
		if (myHeap.addInt(array[i])) {
			std::cout << " " << array[i];
		}
	}
	std::cout << std::endl;

	for(int i = 0; i < s; i++) {
		if(myHeap.popMax(tmp)) {
			std::cout << " " << tmp;
		}
	}
	std::cout << std::endl;

	// a bigger test.
	MaxIntHeap myHeap2(100);
	default_random_engine dre;
	uniform_int_distribution<int> di(1,1000); 


	for (int i = 0; i < 100; i++) {
		int val = di(dre);
		if (myHeap2.addInt(val)) {
			std::cout << " " << val;
		}
	}
	std::cout << std::endl;
	for(int i = 0; i < 100; i++) {
		if(myHeap2.popMax(tmp)) {
			std::cout << " " << tmp;
		}
	}
	std::cout << std::endl;
}

