//Array sequence

#include "dynamic_array.h"

template <class T>
class ArraySequence : public Sequence<T>
{
private:

    DynamicArray<T>dynamic_array = DynamicArray<T>(0);

public:

    ArraySequence() : Sequence<T>() {};

    ArraySequence(const int new_size) : Sequence<T>()
    {

        this->dynamic_array = DynamicArray<T>(new_size);
    }

    ArraySequence(const T* data, const int size) : Sequence<T>()
    {

        DynamicArray<T>dynamic_array_c(data, size);
        
        this->dynamic_array = dynamic_array_c;
    }

    ArraySequence(const Sequence<T>* sequence) : Sequence<T>()
    {
        const int new_size = sequence->get_size();
        this->dynamic_array = DynamicArray<T>(new_size);

        for (int i = 0; i < new_size; ++i) this->dynamic_array[i] = (*sequence)[i];
    }

    ArraySequence<T>* operator = (const Sequence<T>* sequence) override
    {

        const int new_size = sequence->get_size();
        this->dynamic_array = DynamicArray<T>(new_size);

        for (int i = 0; i < new_size; ++i) this->dynamic_array[i] = (*sequence)[i];

        return  this;
    }

    ~ArraySequence() override = default;

    T get_first() const override
    {
        return  this->dynamic_array[0];
    }

    T get_last() const override
    {
        const int size = this->dynamic_array.get_size();
        return  this->dynamic_array[size - 1];
    }

    T get(const int index) const override
    {
        return this->dynamic_array[index];
    }

    T& operator [] (const int index) const override
    {
        return this->dynamic_array[index];
    }

    ArraySequence<T>* get_subsequence(const int start_index, const int end_index) const override
    {
        if (start_index > end_index) throw std::logic_error(StartBiggerThanEndException);
        if (start_index < 0 || start_index > this->get_size()) throw std::out_of_range(IndexOutOfRangeException);

        const int sub_size = end_index - start_index;
        ArraySequence<T>* subsequence = new ArraySequence<T>(sub_size);

        for (int i = 0; i < sub_size; ++i) subsequence->dynamic_array[i] = this->dynamic_array[i];

        return subsequence;
    }

    ArraySequence<T>* concat(const Sequence<T>* sequence) override
    {
        const int sum_size = this->get_size() + sequence->get_size();
        ArraySequence<T>* concated_array_sequence = new ArraySequence<T>(sum_size);

        for (int i = 0; i < this->get_size(); ++i) concated_array_sequence->dynamic_array[i] = this->dynamic_array[i];
        for (int i = this->get_size(); i < sum_size; ++i) concated_array_sequence->dynamic_array[i] = (*sequence)[i - this->get_size()];

        return  concated_array_sequence;
    }

    int get_size() const override
    {
        return this->dynamic_array.get_size();
    }

    void del(const int index) override
    {
        this->dynamic_array.del(index);
    }

    void append(const T value) override
    {
        const int old_size = this->dynamic_array.get_size();
        this->dynamic_array.resize(old_size + 1);
        this->dynamic_array[old_size] = value;
    }
    void prepend(const T value) override
    {
        const int size = this->dynamic_array.get_size();
        DynamicArray<T> dynamic_array_c(this->dynamic_array);

        this->dynamic_array.resize(size + 1);

        for (int i = 0; i < size; ++i) this->dynamic_array[i + 1] = dynamic_array_c[i];

        this->dynamic_array[0] = value;
    }

    void insert(const T value, const int index) override
    {
        const int old_size = this->dynamic_array.get_size();
        const int new_size = old_size + 1;

        if (index < 0 || index > old_size) throw std::out_of_range(IndexOutOfRangeException);

        int index_shift = 0;
        DynamicArray<T> dynamic_array_c(this->dynamic_array);

        this->dynamic_array.resize(new_size);

        for (int i = 0; i < new_size; ++i)
        {
            if (i != index) {
                this->dynamic_array[i] = dynamic_array_c[i - index_shift];
            }
            else
            {
                this->dynamic_array[i] = value;
                index_shift = 1;
            }
        }
    }
};