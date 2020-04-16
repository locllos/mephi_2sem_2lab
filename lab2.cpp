#include <iostream>
#include <stdexcept>

#define IndexOutOfRangeException "IndexOutOfRange"
#define NegativeSizeOfArrayException "NegativeSizeOfArray"


//Testers
template <typename ClassType, typename ConstType>
void inputer(ClassType& MyClass, const ConstType random) {
    int size = MyClass.GetSize();
    for (int i = 0; i < size; ++i) MyClass[i] = ((ConstType)(i + random)) % size;
}

template <typename ClassType> 
void outputer(ClassType &MyClass) {
    std::cout << "\n";
    int size = MyClass.GetSize();
    for (int i = 0; i < size; ++i) std::cout << MyClass[i] << " ";
    std::cout << "\n";

}


//My first and virgin class
template <class T>
class DynamicArray {
private:

    int size = 0;
    T* data = nullptr;
    bool isEmpty = true;

public:

    //Creation constructors
    DynamicArray(int size) {

        this->size = size;
        this->data = new T[size];
        this->isEmpty = false;

    }

    DynamicArray(T* data, int size) {

        this->size = size;
        this->data = data;
        this->isEmpty = false;
    }

    //Copy construstors
    DynamicArray(const DynamicArray<T>& dynamicArray) {

        if (!this->isEmpty) delete[] this->data;

        this->size = dynamicArray.size;
        this->data = new T[dynamicArray.size];
        this->isEmpty = false;

        for (int i = 0; i < dynamicArray.size; ++i) this->data[i] = dynamicArray.data[i];

    }

    DynamicArray& operator = (const DynamicArray<T>& dynamicArray) {

        if (!this->isEmpty) delete[] this->data;

        this->size = dynamicArray.size;
        this->data = new T[dynamicArray.size];
        this->isEmpty = false;

        for (int i = 0; i < dynamicArray.size; ++i) this->data[i] = dynamicArray.data[i];

        return (*this);

    }

    //Destructor
    ~DynamicArray() {

        this->size = 0;
        delete[] this->data;

    }

    //Methods of class
    T Get(const int index) {

       if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);
       
        return this->data[index];

    }

    T& operator [] (const int index) {

        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);
        
        return this->data[index];

    }

    int GetSize()
    {

        return this->size;

    }

    void Set(const int index, const T value) {

        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        this->data[index] = value;

    }

    void resize(const int newSize) {

        if (newSize < 0) throw std::length_error(NegativeSizeOfArrayException);

        int minSize;
        T* newData = new T[newSize];
        minSize = newSize < this->size ? newSize : this->size;

        this->size = newSize;
        for (int i = 0; i < minSize; ++i) newData[i] = this->data[i];
        delete[] this->data;
        this->data = newData;

    }

};

int main()
{
    
    return 0;

 }

