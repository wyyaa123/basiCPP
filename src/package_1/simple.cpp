#include <package_1/simple.h>

#include <iostream>

using namespace some_namespace;

SomeClass::SomeClass()
 : m_member_var(0)
{

}

void SomeClass::memberFunction() const
{
  std::cout << "Some member func" << std::endl;
}