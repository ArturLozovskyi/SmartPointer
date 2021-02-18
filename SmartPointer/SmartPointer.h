#ifndef Header_h
#define Header_h
#include <iostream>

namespace shared_memory {
namespace {
class MemoryHandler {
public:
    MemoryHandler(): count(0) {
        
    }
    size_t getCount() {
        return count;
    }
    void incrementCount() {
        count++;
    }
    void decrementCount() {
        count--;
    }
    
private:
    size_t count;
};
}
template<class T>
class SmartPointer {
public:
    SmartPointer(): data(nullptr), memoryHandler(new MemoryHandler()) {
        memoryHandler->incrementCount(); // нужно ли увеличивать счетчик ссылок
    }
    explicit SmartPointer(T* ptr): data(ptr), memoryHandler(new MemoryHandler()) { // initialize можно сделать
        memoryHandler->incrementCount();
    }
    
    SmartPointer (const SmartPointer &ptr): data(ptr.data) { // Сам себе не нужно присваивать //Почему const T&
        if (*this != ptr) {
            updateDataAndRefs(ptr);
        }
    }
    
    SmartPointer(SmartPointer &&ptr) { // нужно переприсваивать счетчик ссылок, создать метод
        std::cout << "Move constructor" << "\n";
        if (*this != ptr) {
            if (memoryHandler != nullptr) {
                memoryHandler->decrementCount();
                if (memoryHandler->getCount() == 0) {
                    delete data;
                    delete memoryHandler;
                }
            }
            data = ptr.data;
            memoryHandler = ptr.memoryHandler;
            ptr.data = nullptr;
            ptr.memoryHandler = nullptr;
        }
    }
    
    SmartPointer& operator= (const SmartPointer &ptr) {
        if (*this != ptr) {
            updateDataAndRefs(ptr);
        }
        return *this;
    }
    
    SmartPointer& operator= (SmartPointer &&ptr) { // нужно переприсваивать счетчик ссылок, создать метод
        std::cout << "Move operator =" << "\n";
        if (*this != ptr) {
            if (memoryHandler != nullptr) {
                memoryHandler->decrementCount();
                if (memoryHandler->getCount() == 0) {
                    delete data;
                    delete memoryHandler;
                }
            }
            data = ptr.data;
            memoryHandler = ptr.memoryHandler;
            ptr.data = nullptr;
            ptr.memoryHandler = nullptr;
        }
        return *this;
    }
    
    T* getData () {
        return data;
    }
    
    const T* getData () const {
            return data;
    }
    
    T& operator* () { // добавить проверку
        return *data;
    }
    
    const T& operator* () const { // добавить проверку
           return *data;
    }
    
    T* operator -> () {
        return data;
    }
    
    const T* operator -> () const {
        return data;
    }
    
    bool operator == (const SmartPointer& ptr) const {
        return (this == &ptr);
    }
    
    bool operator != (const SmartPointer& ptr) const {
        return !(*this == ptr);
    }
    
    size_t getCount () const { // почему можно обратиться к полю, если оно не статик
        return memoryHandler->getCount();
    }
    ~SmartPointer () {
        if (memoryHandler == nullptr && data == nullptr) {
            return;
        }
        memoryHandler->decrementCount();
        if (memoryHandler->getCount() == 0) {
            delete data;
            delete memoryHandler;
        }
    }
    
private:
    T* data = nullptr; // Вынести count в другую структуру, и в конструкторе создавать её
//    size_t* count = nullptr; // Вынести count в другую структуру, и в конструкторе создавать её
    // И хранить здесь только указатель на структуру
    MemoryHandler* memoryHandler = nullptr;
    
    void updateDataAndRefs (const SmartPointer& ptr) {
        
        if (memoryHandler != nullptr) {
            memoryHandler->decrementCount();
            if (memoryHandler->getCount() == 0) {
                delete data;
                delete memoryHandler;
            }
        }
        data = ptr.data;
        memoryHandler = ptr.memoryHandler;
        memoryHandler->incrementCount();
    }
};

template <typename T, typename ...Args>
SmartPointer<T> make_shared (Args&&...args) {
    return SmartPointer<T>(new T (std::forward<Args>(args)...));
};
}
#endif /* Header_h */
