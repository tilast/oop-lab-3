#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <string>

/**
* @class ShallSort
* @desc class implements singleton, so we can use one instance to sort much lists
*/
class ShallSort
{
	static ShallSort* _self;

	/**
	* goTo - method turns us on the required position and returns required pointer
	* @param std::list< int >::iterator start
	* @param int Distance
	* @return pointer on required item of the list
	*/
	std::list< int >::iterator goTo(std::list< int >::iterator start, int Distance) {
		if(Distance > 0) {
			for(int i = 0; i < Distance; i++) {
				start++;
			}
		} else {
			for(int i = 0; i < -Distance; i++) {
				start--;
			}
		}

		return start;
	}    

	/**
	* findDistance - method calculates distance between two items of the list
	* @param std::list< int >::iterator first - pointer on the first item of the list
	* @param std::list< int >::iterator start - pointer on the start position
	* @param std::list< int >::iterator end - pointer on the end position
	* @return int - distance
	*/
	int findDistance(std::list< int >::iterator first, std::list< int >::iterator start, std::list< int >::iterator end) {
		int startPos = 0, endPos = 0;

		std::list<int>::iterator helper = first;

		for(; helper != start; helper++, startPos++);
		helper = first;
		for(; helper != end; helper++, endPos++);

		int result = endPos - startPos;

		return (result > 0) ? result : -result;
	}
protected:
	ShallSort(){}
public:
	/**
	* @return instance of the ShallSort class
	*/
	static ShallSort* Instance() {
		if(!_self) _self = new ShallSort();
		return _self;
	}

	/**
	* simpleSort - method changes input list sorting it by Shell asc and shows time of sorting
	* @param std::list< int >::iterator first - pointer on the first item of the list
	* @param int size - size of the list
	*/
    void simpleSort(std::list< int >::iterator first, int size) {
    	clock_t executeTime = clock();

    	std::list< int >::iterator al = goTo(first, 3);
		for(int d = size / 2; d != 0; d /= 2 ) {
	    	for( std::list< int >::iterator i = goTo(first, d); i != goTo(first, size); ++i ) {
	    		for(std::list< int >::iterator j = i; findDistance(first, first, j)  >= d && (*j < *(goTo(j, -d))); j = goTo(j, -d) ) {
	    			std::swap(*j, *(goTo(j, -d)));
	    		}

	    	}
	    }

	    executeTime = clock() - executeTime;

	    int ms = (double) executeTime / CLOCKS_PER_SEC * 1000;
	    std::cout << "Executing time: " << ms << " ms" << std::endl;
    }
};

ShallSort* ShallSort ::_self=NULL;

/**
* class Menu - singleton class, provides the I\O Interface
*/

class Menu {
	static Menu *_self;

	int getInt() {
        int tmp;
        std::cin >> tmp;

        while(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(100000, '\n');
            std::cin >> tmp;
        }
        
        std::cin.ignore();

        return tmp;
    }

    std::list< int >::iterator goTo(std::list< int >::iterator start, int Distance) {
		if(Distance > 0) {
			for(int i = 0; i < Distance; i++) {
				start++;
			}
		} else {
			for(int i = 0; i < -Distance; i++) {
				start--;
			}
		}

		return start;
	}

	std::list<int> myList;
	std::list<int>::iterator myIt;

	protected:
		Menu() {
			myIt = myList.begin();
			std::cout << "Hello! Write the command" << std::endl;
			bool exit = false;

			while(!exit) {
				std::cout << "user@user: ";
			    // string for command
		        std::string command;
		        //console->outInputCommand();
		        // take command
				std::getline(std::cin, command);

		        // split string by white-space
				std::stringstream tmp(command);
		        std::string tmpStr;
		        std::vector<std::string> commands;

		        while(!tmp.eof()) {
		            getline(tmp, tmpStr, ' ');
		            commands.push_back(tmpStr);
		        }
		        
		        if(commands.size() < 4) {
	                for(int i = commands.size() -1; i < 4; i++) {
	                    commands.push_back("");
	                }
		        }

		        if(!commands[0].compare("add")) {
		     		if(!commands[1].compare("item")) {
		     			std::cout << "input item" << std::endl;
			     		int number = getInt();
			     		std::cout << "input position" << std::endl;  	
			     		int position = getInt();
			     		if(position > myList.size()) {
			     			position = myList.size();
			     		} 

			     		myIt = goTo(myList.begin(), position);
			     		myList.insert(myIt, number);
		     		}
		        } else if(!commands[0].compare("remove")) {
		        	if(!commands[1].compare("item")) {
		        		if(myList.empty()) {
			     			std::cout << "list is empty" << std::endl;  	
			     		} else {
			     			std::cout << "input position" << std::endl;  	
				     		
				     		int position = getInt();
				     		if(position > myList.size()) {
				     			position = myList.size();
				     		} 

				     		myIt = goTo(myList.begin(), position);
				     		myList.erase(myIt);
			     		}
		        	} else if(!commands[1].compare("all")) {
		        		myList.clear();
		        		std::cout << "All items of list were removed" << std::endl;
		        	}
		        } else if(!commands[0].compare("size")) {
		        	std::cout << myList.size() << std::endl;
		        } else if(!commands[0].compare("view")) {
		        	if(myList.empty()) {
		        		std::cout << "List is empty" << std::endl;
		        	} else {
			        		for(myIt = myList.begin(); myIt != myList.end(); myIt++) {
			        		std::cout << *myIt << std::endl;
			        	}
		        	}
		        } else if(!commands[0].compare("shellsort")) {
		        	ShallSort::Instance()->simpleSort(myList.begin(), myList.size());
		        } else if(!commands[0].compare("exit")) {
		        	std::cout << "Byu!" << std::endl;
		        	exit = true;
		        } else {
		        	std::cout << "Wrong command '" << command << "'" << std::endl;
		        }

		        if(exit) {
		        	break;
		        }
		    }
		}
	public:
		static Menu* Instance() {
			if(!_self) {
				_self = new Menu();
			}

			return _self;
		}
};
Menu* Menu ::_self=NULL;

int main(int argc, char ** argv) {
	srand(time(NULL));

	Menu::Instance();

	return 0;
}