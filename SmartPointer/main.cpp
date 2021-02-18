#include <iostream>
#include "SmartPointer.h"
#include <string>

class A {
public:
    A(int number): data(number) {
        
    }
    int data;
    
    ~A() {
        std::cout << "Destructor from A" << "\n";
    }
    
};

void func(shared_memory::SmartPointer<A> a) {
    std::cout << a->data << "\n";
}

void func1(const A* ptrA) {
    std::cout << ptrA->data << "\n";
}

int main(int argc, const char * argv[]) {
//    shared_memory::SmartPointer<A> ptr = shared_memory::make_shared<A>(10);
//    {
//        std::cout << "Количество ссылок ptr: " << ptr.getCount() << "\n";
//        std::cout << "Данные ptr: " << ptr->data << "\n";
//        auto ptr1 = shared_memory::make_shared<A>(7);
//        std::cout << "Количество ссылок ptr1: " << ptr1.getCount() << "\n";
//        std::cout << "Данные ptr1: " << ptr1->data << "\n";
//        auto ptr2 = shared_memory::make_shared<A>(5);
//        std::cout << "Количество ссылок ptr2: " << ptr2.getCount() << "\n";
//        std::cout << "Данные ptr2: " << ptr2->data << "\n";
//        ptr1 = ptr2;
//        std::cout << "Количество ссылок ptr1: " << ptr1.getCount() << "\n";
//        std::cout << "Данные ptr1: " << ptr1->data << "\n";
//    }
//
//    std::cout << ptr.getCount() << "\n";
//    std::cout << ptr->data << "\n";
    
    
//    shared_memory::SmartPointer<int> ptr = std::move(shared_memory::SmartPointer<int>(new int(5)));
    
    shared_memory::SmartPointer<A> ptr = shared_memory::make_shared<A>(10);
//    shared_memory::SmartPointer<A> ptr1;
    
    const shared_memory::SmartPointer<A> ptr1 = std::move(ptr);
    
//    func(ptr1);
    
    func1(ptr1.getData());
    
    
    std::cout << "Hello, World!\n";
    return 0;
}
//
//shared_memory::SmartPointer<int> ptr;
//shared_memory::SmartPointer<int> ptr1;
//shared_memory::SmartPointer<int> ptr2;
//
//ptr = ptr1;
//
//ptr1 = shared_memory::make_shared<int>(5);
//
//ptr2 = ptr1;
