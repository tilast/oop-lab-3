#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

class ShallSort
{
	static ShallSort* _self;
	std::vector<int> increments;
protected:
	ShallSort(){}
public:
	static ShallSort* Instance() {
		if(!_self) _self = new ShallSort();
		return _self;
	}

    void simpleSort(std::list< int >::iterator first, int size) {
    	std::list< int >::iterator al = goTo(first, 3);
		for(int d = size / 2; d != 0; d /= 2 ) {
			std::cout << "deep 1" << std::endl;
	    	for( std::list< int >::iterator i = goTo(first, d); i != goTo(first, size - 1); ++i ) {
	    		std::cout << "deep 2" << std::endl;
	    		std::list< int >::iterator j = i;
	    		for(; findOffset(first, first, j)  >= d && (*j < *(goTo(j, -d))); j = goTo(j, -d) ) {
	    			std::cout << "deep 3" << std::endl;
	    			int a = *j;
	    			*j = *(goTo(j, -d));
	    			*(goTo(j, -d)) = a;
	    			std::cout << "swap" << std::endl;
	    		}
	    	}
	    }
    }

	std::list< int >::iterator goTo(std::list< int >::iterator start, int offset) {
		
		std::cout << "goto:" << std::endl;
		clock_t progTime = clock();
		if(offset > 0) {
			for(int i = 0; i < offset; i++) {
				start++;
			}
		} else {
			for(int i = 0; i < -offset; i--) {
				start--;
			}
		}

		progTime = clock() - progTime;
		std::cout << "Time: " <<(double)progTime / CLOCKS_PER_SEC << " seconds" << std::endl;

		return start;
	}    

	int findOffset(std::list< int >::iterator first, std::list< int >::iterator start, std::list< int >::iterator end) {
		std::cout << "findoffset:" << std::endl;
		clock_t progTime = clock();
		int startPos = 0, endPos = 0;

		std::list<int>::iterator helper = first;

		for(; helper != start; helper++, startPos++);
		helper = first;
		for(; helper != end; helper++, endPos++);

		int result = endPos - startPos;
		progTime = clock() - progTime;
		std::cout << "Time: " <<(double)progTime / CLOCKS_PER_SEC << " seconds" << std::endl;

		return (result > 0) ? result : -result;
	}
};

ShallSort* ShallSort ::_self=NULL;

int main(int argc, char ** argv) {
	srand(time(NULL));
	std::list<int> a;
	a.push_back(5);
	a.push_back(15);
	a.push_back(-56);
	a.push_back(54);
	a.push_back(12);
	a.push_back(34);
	a.push_back(47);
	a.push_back(0);

	ShallSort::Instance()->simpleSort(a.begin(), a.size());

	for(std::list<int>::iterator it = a.begin(); it != a.end(); it++) {
		std::cout << *it << std::endl;
	}
	return 0;
}