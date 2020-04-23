//Sequence

template <class T>
class Sequence
{
public:
    const int size = 0;
public:

    Sequence() = default;

    virtual Sequence<T>* operator = (const Sequence<T>* sequence) = 0;

    virtual T get_first() const = 0;
    virtual T get_last() const = 0;
    virtual T get(const int index) const = 0;
    virtual T& operator [] (const int index) const = 0;
    virtual int get_size() const = 0;

    virtual Sequence<T>* get_subsequence(const int start_index, const int end_index) const = 0;
    virtual Sequence<T>* concat(const Sequence<T>* sequence) = 0;

    virtual void del(const int index) = 0;
    virtual void append(const T value) = 0;
    virtual void prepend(const T value) = 0;
    virtual void insert(const T value, const int index) = 0;

    virtual ~Sequence() = default;

};
