#include <iostream>

using namespace std;

class aCls
{
private:
	int a;
public:
	// constructor & destructor
	aCls();
	~aCls();

	// copy-constructor
	aCls(aCls &);

	// interface
	int get(void);
	void set(int v);
	aCls operator+(aCls &pa);
	aCls operator*(int n);
	aCls operator*(aCls &pa);

	// static function member
	static int show(void);

	// friend function
	friend void func(aCls *pa, int v);
	friend aCls func2(aCls pa);
};

aCls::aCls()
{
	a = 0;
	cout << "construct this = " << this << endl;
}

aCls::~aCls()
{
	cout << "destruct this = " << this << endl;
}

aCls::aCls(aCls &)
{
	cout << "copy-constructor" << endl;
}

int count = 0;
int aCls::show(void)
{
	count++;
	cout << "show, count = " << count << endl;
}

int aCls::get(void)
{
	cout << "this = " << this
		<< " get a = " << a
		<< endl;
	return a;
}

void aCls::set(int v)
{
	a = v;
	cout << "this = " << this
		<< " set a = " << a
		<< endl;
}

aCls aCls::operator+(aCls &pa)
{
	aCls d;

	d.a = a + pa.a;
	cout << "operator+" << endl;
	return d;
}

aCls aCls::operator*(int n)
{
	aCls d;

	d.a = a * n;
	cout << "operator*" << endl;
	return d;
}

aCls aCls::operator*(aCls &pa)
{
	aCls d;

	d.a = a * pa.a;
	cout << "operator*" << endl;
	return d;
}

void func(aCls *pa, int v)
{
	pa->a = v;
}

aCls func2(aCls pa)
{
	aCls t;

	t = pa;
	return t;
}

int test_cls(void)
{
	int t;
	aCls a, b;
	aCls c = a;

	cout << "a=" << a.get() << endl;
	cout << "b=" << b.get() << endl;
	cout << "c=" << c.get() << endl;

	a.set(10);
	b.set(20);

	c = a;
	cout << "c = a, a" << c.get() << endl;

	c = a + b;
	cout << "a + b=" << c.get() << endl;

	c = a * 12;
	cout << "a * 12=" << c.get() << endl;

	c = a * a;
	cout << "a * a=" << c.get() << endl;

	cout << "before func(a) =" << a.get() << endl;
	func(&a, 22);
	cout << "after func(a) =" << a.get() << endl;

	cout << "func2 start" << endl;
	c = func2(a);
	cout << "func2 end" << endl;

	a.show();
	cout << "hello world\n";
}

void test_multiple_inherit(void);

int main(void)
{
//	test_cls();
	test_multiple_inherit();
}

