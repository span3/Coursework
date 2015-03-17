#include<exception>
#include<stdexcept>
#include<iostream>
using namespace std;


class myexception: public exception
{
  virtual const char* what() const throw()
  {
    return "My exception happened";
  }
} myex;

int main () {
   
 try
  {
	char data[100] = "Dr. Who" ;
	cout << "Print my Name" << endl;
	cerr << "my name is " << data << endl;
	throw myex;
	throw 7;
	throw "I want water?";
  }
  catch(bad_alloc e){ cout<< e.what() << " bad allocation " << endl;}
  catch(exception& e){ cout << e.what() << endl;}
  catch(int){ cout << "int exception" << endl;}
  catch(...){ cout << "all else failed" << endl;}
  return 0;
}


