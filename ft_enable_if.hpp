template<bool, class T>    //i give it two parameters, up to you to give more or less
struct enable_if
{};

template <class T>
struct enable_if<true, T>
{
    typedef T value;     //if true define the T type value
};