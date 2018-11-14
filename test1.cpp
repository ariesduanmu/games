#include <iostream>
using namespace std;
void foo2(int a, int b)
{
	cout<<a<<" "<<b<<endl;
}

extern "C"
{
	void cfoo2(int a, int b)
	{
		foo2(a, b);
	}
}
