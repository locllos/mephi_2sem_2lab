//Dynamic Array

#include <stdexcept>

constexpr auto IndexOutOfRangeException = "Index out of range";
constexpr auto NegativeSizeOfArrayException = "Negative size of array";
constexpr auto StartBiggerThanEndException = "Start index bigger than end index";


//My first and virgin class
template <class T>
class DynamicArray
{

private:

    int size = 0;
    T* data = nullptr;
    bool isEmpty = true;

public:

    //Creation constructors
    DynamicArray(const int size)
    {

        this->size = size;
        this->data = new T[size];
        this->isEmpty = false;

    }

    DynamicArray(const T* data, const int size)
    {

        this->size = size;
        this->data = new T[size];

        for (int i = 0; i < size; ++i) this->data[i] = data[i];
    }

    //Copy construstors
    DynamicArray(const DynamicArray<T>& dynamic_array)
    {

        if (!this->isEmpty) delete[] this->data;

        this->size = dynamic_array.size;
        this->data = new T[dynamic_array.size];
        this->isEmpty = false;

        for (int i = 0; i < dynamic_array.size; ++i) this->data[i] = dynamic_array.data[i];

    }

    DynamicArray<T>& operator = (const DynamicArray<T>& dynamic_array)
    {

        T* new_data = new T[dynamic_array.get_size()];
        for (int i = 0; i < dynamic_array.size; ++i) new_data[i] = dynamic_array.data[i];

        delete[] this->data;

        this->size = dynamic_array.size;
        this->data = new_data;
        this->isEmpty = false;

        return (*this);

    }

    //Destructor
    ~DynamicArray()
    {

        this->size = 0;
        delete[] this->data;

    }

    //Methods of class
    T get(const int index) const
    {

        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        return this->data[index];

    }

    T& operator [] (const int index) const
    {

        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        return this->data[index];

    }

    int get_size() const
    {

        return this->size;

    }

    void set(const int index, const T value)
    {

        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        this->data[index] = value;

    }

    void del(const int index)
    {
        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        const int new_size = this->size - 1;
        T* data_c = new T[new_size];
        int index_shift = 0;

        for (int i = 0; i < this->size; ++i)
        {
            if (i != index)
            {
                data_c[i - index_shift] = this->data[i];
            }
            else
            {
                index_shift = 1;
            }
        }

        delete[] this->data;

        this->data = data_c;
        this->size = new_size;
    }

    void resize(const int new_size)
    {

        if (new_size < 0) throw std::length_error(NegativeSizeOfArrayException);

        int const min_size = new_size < this->size ? new_size : this->size;;
        T* new_data = new T[new_size];


        this->size = new_size;
        for (int i = 0; i < min_size; ++i) new_data[i] = this->data[i];
        delete[] this->data;
        this->data = new_data;

    }

};
