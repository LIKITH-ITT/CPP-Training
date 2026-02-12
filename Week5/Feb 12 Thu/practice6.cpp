#include<iostream>
using namespace std;
class BaseClass{
    public:
        int var_base;
        void display(){
            cout<<"Dispalying Base class variable var_base "<<var_base<<endl;
        }
        virtual ~BaseClass(){
            std::cout << "Base Destructor\n";
        }
};

class DerivedClass : public BaseClass{
    public:
            int var_derived;
            void display(){
                cout<<"Dispalying Base class variable var_base "<<var_base<<endl;
                cout<<"Dispalying Derived class variable var_derived "<<var_derived<<endl;
            }
            ~DerivedClass(){
                std::cout << "Derived destructor\n";
            }
};
int main(){
    BaseClass* base_class_pointer = new DerivedClass();
    std::cout << base_class_pointer;
    delete base_class_pointer;

    return 0;
}
