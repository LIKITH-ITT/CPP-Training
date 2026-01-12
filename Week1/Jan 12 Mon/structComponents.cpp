#include <iostream>
using namespace std;

struct test
{
  private:
    int x, y;

  public:
      test(int a, int b)
    {
        x = a;
        y = b;
    }

    void show()
    {
        cout << x << " " << y << endl;
    }

    ~test()
    {
        cout << "Destroyed Point Variable" << endl;
    }
};

int main()
{

    test s1(32, 56);
    test s2(979, 657);

    s1.show();
    s2.show();
    return 0;
}