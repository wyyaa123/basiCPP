#include <iostream>

#include <package_1/simple.h>

int main ()
{
  std::cout << "Hello world!" << std::endl;

  some_namespace::SomeClass some_class;
  some_class.memberFunction();

  return 0;
}
