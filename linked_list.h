//Linked list 
#include <stdexcept>

constexpr auto IndexOutOfRangeException = "Index out of range";
constexpr auto NegativeSizeOfArrayException = "Negative size of array";
constexpr auto StartBiggerThanEndException = "Start index bigger than end index";


template <class T>
class LinkedList
{

private:

    struct node
    {
        T data = T(0);
        node* next = nullptr;
    };

    int size = 0;
    node* head = nullptr;

public:

    //Creation constructors
    LinkedList() : size(0), head(nullptr) {};

    LinkedList(const T* data, const int size) : LinkedList()
    {

        if (size < 0) throw std::length_error(NegativeSizeOfArrayException);

        this->size = size;
        node** node_dptr = &(this->head);

        for (int i = 0; i < size; ++i)
        {
            (*node_dptr) = new node;
            (*node_dptr)->data = data[i];
            node_dptr = &((*node_dptr)->next);
        }

    }

    //Copy constructor
    LinkedList(const LinkedList <T>& list)
    {

        this->size = list.size;
        node** node_dptr = &this->head;
        node* node_ptr_c = list.head;

        for (int i = 0; i < list.size; ++i)
        {
            *node_dptr = new node;
            (*node_dptr)->data = node_ptr_c->data;
            node_dptr = &((*node_dptr)->next);
            node_ptr_c = node_ptr_c->next;
        }

    }

    LinkedList<T>& operator = (const LinkedList<T>& list)
    {

        if (this == &list) return *this;

        this->size = list.size;
        node** node_dptr = &this->head;
        node* node_ptr_c = list.head;

        for (int i = 0; i < list.size; ++i)
        {
            *node_dptr = new node;
            (*node_dptr)->data = node_ptr_c->data;
            node_dptr = &((*node_dptr)->next);
            node_ptr_c = node_ptr_c->next;
        }

        return *this;

    }

    //Destructor
    ~LinkedList()
    {
        node* node_temp_ptr;
        node* node_ptr = this->head;


        for (int i = 0; i < this->size; ++i)
        {
            node_temp_ptr = node_ptr->next;
            delete node_ptr;
            node_ptr = node_temp_ptr;
        }

        this->head = nullptr;
        this->size = 0;

    }

    //Methods of class
    T get_first() const
    {

        if (this->head == nullptr) throw std::out_of_range(IndexOutOfRangeException);

        return this->head->data;

    }

    T get_last() const
    {

        if (this->head == nullptr) throw std::out_of_range(IndexOutOfRangeException);

        node* node_temp_ptr = this->head;

        while (node_temp_ptr->next != nullptr) node_temp_ptr = node_temp_ptr->next;

        return node_temp_ptr->data;

    }

    T get(const int index) const
    {
        if (this->head == nullptr || index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        node* node_temp_ptr = this->head;

        for (int i = 0; i < index; ++i) node_temp_ptr = node_temp_ptr->next;

        return node_temp_ptr->data;
    }

    T& operator [] (const int index) const
    {

        if (this->head == nullptr || index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        node* node_temp_ptr = this->head;

        for (int i = 0; i < index; ++i) node_temp_ptr = node_temp_ptr->next;

        return node_temp_ptr->data;

    }

    LinkedList<T>* get_sublist(const int start_index, const int end_index) const
    {
        if (start_index > end_index) throw std::logic_error(StartBiggerThanEndException);
        if (start_index < 0 || start_index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        int sublist_size = end_index - start_index;
        node* node_temp_ptr = this->head;
        T* data_c = new T[sublist_size];

        for (int i = 0; i < end_index; ++i)
        {
            if (i >= start_index) data_c[i - start_index] = node_temp_ptr->data;

            node_temp_ptr = node_temp_ptr->next;
        }

        LinkedList<T>* sublist_ptr = new LinkedList<T>(data_c, sublist_size);
        delete[] data_c;

        return  sublist_ptr;

    }

    int get_size() const
    {

        return  this->size;

    }

    void del(const int index)
    {
        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        const int new_size = this->size - 1;
        node* del_node_ptr = this->head;
        node* node_temp_ptr = this->head;

        if (index == 0)
        {
            this->head = this->head->next;
            delete del_node_ptr;
        }
        else
        {
            for (int i = 0; i < index - 1; ++i) node_temp_ptr = node_temp_ptr->next;

            del_node_ptr = node_temp_ptr->next;
            node_temp_ptr->next = del_node_ptr->next;

            delete del_node_ptr;
        }

        this->size = new_size;
    }

    void append(const T data)
    {

        node* new_node_ptr = this->head;

        while (new_node_ptr->next != nullptr) new_node_ptr = new_node_ptr->next;

        new_node_ptr->next = new node;
        new_node_ptr = new_node_ptr->next;
        new_node_ptr->data = data;

        ++this->size;

    };

    void prepend(const T data)
    {

        node* new_node_ptr = new node{ data,this->head };
        this->head = new_node_ptr;

        ++this->size;

    }

    void insert(const T data, const int index)
    {
        if (index < 0 || index >= this->size) throw std::out_of_range(IndexOutOfRangeException);

        if (index == 0)
        {
            this->prepend(data);
        }
        else
        {
            node* new_node_ptr = new node{ data,nullptr };
            node* node_temp_ptr = this->head;
            ++this->size;

            for (int i = 0; i < index - 1; ++i) node_temp_ptr = node_temp_ptr->next;

            new_node_ptr->next = node_temp_ptr->next;
            node_temp_ptr->next = new_node_ptr;
        }
    }

    LinkedList<T>* concat(const LinkedList<T>* list)
    {
        const int sum_size = this->size + list->size;
        T* data_c = new T[sum_size];
        node* node_temp_ptr = this->head;

        for (int i = 0; i < this->size; ++i, node_temp_ptr = node_temp_ptr->next) data_c[i] = node_temp_ptr->data;

        node_temp_ptr = list->head;

        for (int i = this->size; i < sum_size; ++i, node_temp_ptr = node_temp_ptr->next) data_c[i] = node_temp_ptr->data;

        LinkedList<T>* concated_list_ptr = new LinkedList<T>(data_c, sum_size);
        delete[] data_c;

        return  concated_list_ptr;
    }

};
