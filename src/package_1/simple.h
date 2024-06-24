#pragma once

namespace some_namespace
{

class SomeClass
{
public:
  SomeClass();

  // Always make functions const if they don't modify *this
  void memberFunction() const;
private:

  // Underscore members starting with m_
  int m_member_var;

};

}