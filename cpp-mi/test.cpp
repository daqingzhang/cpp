#include <iostream>
#include <test.h>

using namespace std;
////////////////////////////////Class A///////////////////////////////////
A::A()
{
	value = 0;
	cout << "construct A" << endl;
}

A::~A()
{
	cout << "destruct A" << endl;
}

int A::get(void)
{
	cout << "get A" << endl;
	return value;
}

void A::set(int v)
{
	cout << "set A" << endl;
	value = v;
}

void A::inc(void)
{
	value++;
}

int A::getBaseValue(void)
{
	cout << "getBaseValue,"
		<< " value = " << value
		<< " addr  = " << &value
		<< endl;

	return value;
}

////////////////////////////////Class B///////////////////////////////////
B::B()
{
	value = 0;
	cout << "construct B" << endl;
}

B::~B()
{
	cout << "destruct B" << endl;
}

int B::get(void)
{
	cout << "get B" << endl;
	return value;
}

void B::set(int v)
{
	cout << "set B" << endl;
	value = v;
}

int B::getParentBaseValueB(void)
{
	cout << "B: getParentBaseValue" << endl;
	return getBaseValue();
}

////////////////////////////////Class C///////////////////////////////////
C::C()
{
	value = 0;
	cout << "construct C" << endl;
}

C::~C()
{
	cout << "destruct C" << endl;
}

int C::get(void)
{
	cout << "get C" << endl;
	return value;
}

void C::set(int v)
{
	cout << "set C" << endl;
	value = v;
}

int C::getParentBaseValueC(void)
{
	cout << "C: getParentBaseValue" << endl;
	return getBaseValue();
}

////////////////////////////////Class D///////////////////////////////////
D::D()
{
	value = 0;
	cout << "construct D" << endl;
}

D::~D()
{
	cout << "destruct D" << endl;
}

int D::get(void)
{
	cout << "get D" << endl;
	return value;
}

void D::set(int v)
{
	cout << "set D" << endl;
	value = v;
}

void test_multiple_inherit(void)
{
	A obja;
	B objb;
	C objc;
	D objd;

	int a, b, c;

	obja.set(1);
	objb.set(2);
	objc.set(3);
	objd.set(4);

	cout << "obja.value = " << obja.get() << endl;
	cout << "objb.value = " << objb.get() << endl;
	cout << "objc.value = " << objc.get() << endl;
	cout << "objd.value = " << objd.get() << endl;

	cout << "\nbefore inc:" << endl;
	cout << "objb base value = " << objb.getBaseValue() << endl;
	cout << "objc base value = " << objc.getBaseValue() << endl;
	cout << "objd base value = " << objd.getBaseValue() << endl;

	cout << "\nafter inc:" << endl;
	objb.inc();
	cout << "objb base value = " << objb.getBaseValue() << endl;

	objc.inc();
	objc.inc();
	cout << "objc base value = " << objc.getBaseValue() << endl;

	/*
	 * D inchrited from B and C, The A is the base class of B and C.
	 * if a = b = c, then the B, C and D has the save base A.
	 */

	objd.inc();
	objd.inc();
	objd.inc();

	a = objd.getBaseValue();
	b = objd.getParentBaseValueB();
	c = objd.getParentBaseValueC();

	cout << "objd base value = " << a << endl;//same value
	cout << "objd parent base value = " << b << endl;//same value
	cout << "objd parent base value = " << c << endl;//same value
}
