#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

/*
class ShallSort
{
public:
        static const ShallSort& Instance()
        {
                static ShallSort theSingleInstance;
                return theSingleInstance;
        }
private:        
        ShallSort(){};
        ShallSort(const ShallSort& root);
        ShallSort& operator=(const ShallSort&);
};*/

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

	std::list< int > simpleSort(std::list< int > myList) {
		
	}

	std::list< int > sedgwickSort(std::list< int > myList) {
		incrementsArray(myList.size());
	}

	void incrementsArray(int size) {
		increments.resize(size);

		for(int i = 0; i < size; i++) {
			increments[i] = (i % 2) ? odd(i) : even(i);
		}
	}

	int even(int i) {
		return 9 * pow(2.0, i) - 9 * pow(2.0, i / 2) + 1;
	}

	int odd(int i) {
		return 8 * pow(2.0, i) - 6 * pow(2.0, (i + 1) / 2) + 1;
	}
};

ShallSort* ShallSort ::_self=NULL;

int main(int argc, char ** argv) {
	srand(time(NULL));
	std::list<int> a(1000);
	std::list<int>::iterator it = a.begin;
/*	a.push_back(3);
	a.push_back(17);
	a.push_back(5);
	a.push_back(16);
	a.push_back(11);
	a.push_back(-9);
	std::list<int>::iterator it = a.begin();
	it++;
	it++;
	it++;
	std::cout << *it << std::endl;
	std::cout << "sksjh" << std::endl;
*/
	// Sedgewick sort
		/*for(int i = 0; i < 40000; i++) {
			a.push_back(rand() % 75);
		}*/

	ShallSort::Instance()->sedgwickSort(a);
	return 0;
}