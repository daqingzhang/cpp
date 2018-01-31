#ifndef __TEST_H__
#define __TEST_H__

class A
{
private:
	int value;
public:
	A();
	~A();

	virtual int get(void);
	virtual void set(int v);
	void inc(void);
	int getBaseValue(void);
//	virtual void dec(void);
};

//class B: public A
class B: virtual public A
{
private:
	int value;
public:
	B();
	~B();

	virtual int get(void);
	virtual void set(int v);
	virtual int getParentBaseValueB(void);
};

//class C: public A
class C: virtual public A
{
private:
	int value;
public:
	C();
	~C();

	virtual int get(void);
	virtual void set(int v);
	virtual int getParentBaseValueC(void);
};

//class D: public B, public C
class D: virtual public B, virtual public C
{
private:
	int value;
public:
	D();
	~D();

	virtual int get(void);
	virtual void set(int v);
};

#endif
