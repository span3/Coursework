#include <iostream>

using namespace std;

class language {
public:
	virtual void say_hello(void) = 0;
};

class japanese : public language {
public:
	void say_hello(void) {
		cout << "Konichiwa!" << endl;
	}
};

class english : public language {
public:
	void say_hello(void) {
		cout << "Hello!" << endl;
	}
};

class british_english : public english {
public:
	void say_hello(void) {
		cout << "Hello chap!" << endl;
	}
};

int main()
{
	language *l;
        language *k;

	l = new japanese();
	l->say_hello();
	k = new british_english();
	k->say_hello();
	english eng_lan = *dynamic_cast<british_english*>(l);
	eng_lan.say_hello();
	
	return 0;
}
