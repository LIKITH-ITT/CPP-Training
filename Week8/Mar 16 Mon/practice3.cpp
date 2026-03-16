#include <iostream>
using namespace std;

template <class T>
class mycontainer {
    T element;
  public:
    mycontainer (T arg) {element=arg;}
    T increase () {return ++element;}
};

template<>
char mycontainer<char>::increase()
{
    if ((element>='a')&&(element<='z'))
      element+='A'-'a';
      return element;
}

// template <>
// class mycontainer <char> {
//     char element;
//   public:
//     mycontainer (char arg) {element=arg;}
//     char uppercase ()
//     {
//       if ((element>='a')&&(element<='z'))
//       element+='A'-'a';
//       return element;
//     }
// };

int main () {
  mycontainer myint (7);
  mycontainer mychar ('j');
  cout << myint.increase() << endl;
  cout << mychar.increase() << endl;
  return 0;
}