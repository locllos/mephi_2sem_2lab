//List sequence 

#include "linked_list.h"

template <class T>
class ListSequence : public Sequence<T>
{
private:

    LinkedList<T>linked_list = LinkedList<T>();

public:

    ListSequence() {};

    ListSequence(const T* data, const int size) : Sequence<T>()
    {
        this->linked_list = LinkedList<T>(data, size);
    }

    ListSequence(const Sequence<T>* sequence) : Sequence<T>()
    {
        const int new_size = sequence->get_size();
        T* new_data = new T[new_size];

        for (int i = 0; i < new_size; ++i) new_data[i] = (*sequence)[i];

        this->linked_list = LinkedList<T>(new_data, new_size);
        delete[] new_data;
    }

    ListSequence<T>* operator =(const Sequence<T>* sequence) override
    {
        const int new_size = sequence->get_size();
        T* new_data = new T[new_size];

        for (int i = 0; i < new_size; ++i) new_data[i] = (*sequence)[i];

        this->linked_list = LinkedList<T>(new_data, new_size);
        delete[] new_data;

        return this;
    }

    ~ListSequence() override = default;

    T get_first() const override
    {
        return  this->linked_list.get_first();
    }

    T get_last() const override
    {
        return this->linked_list.get_last();
    }

    T get(const int index) const override
    {
        return this->linked_list.get(index);
    }

    T& operator [] (const int index) const override
    {
        return this->linked_list[index];
    }

    int get_size() const override
    {
        return  this->linked_list.get_size();
    }

    ListSequence<T>* get_subsequence(const int start_index, const int end_index) const override
    {
        LinkedList<T> sublist = *(this->linked_list.get_sublist(start_index, end_index));
        ListSequence<T>* subsequence = new ListSequence<T>;
        subsequence->linked_list = sublist;

        return subsequence;
    }

    ListSequence<T>* concat(const Sequence<T>* sequence) override
    {
        const int size_c = sequence->get_size();
        T* data_c = new T[size_c];

        for (int i = 0; i < size_c; ++i) data_c[i] = (*sequence)[i];

        ListSequence<T>* concated_sequence = new ListSequence<T>(data_c, size_c);
        concated_sequence->linked_list = *(this->linked_list.concat(&(concated_sequence->linked_list)));

        delete[] data_c;

        return concated_sequence;
    }

    void del(const int index) override
    {
        this->linked_list.del(index);
    }

    void append(const T value) override
    {
        this->linked_list.append(value);
    }

    void prepend(const T value) override
    {
        this->linked_list.prepend(value);
    }

    void insert(const T value, const int index) override
    {
        this->linked_list.insert(value, index);
    }
};
