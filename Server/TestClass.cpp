#include "TestClass.h"

TestClass::TestClass(int a, int b): a(a), b(b)
{
}

int TestClass::getA()
{
	return a;
}

int TestClass::getB()
{
	return b;
}
