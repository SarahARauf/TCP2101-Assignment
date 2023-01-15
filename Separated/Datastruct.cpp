#include "Datastruct.h"
template class Datastruct<int>;
template class Datastruct<float>;
template class Datastruct<double>;
template bool Datastruct<double>::search<std::vector>(std::vector<double, std::allocator<double> > const&, double const&);
template void Datastruct<int>::print<std::vector>(std::vector<int, std::allocator<int> > const&);
template bool Datastruct<int>::search<std::vector>(std::vector<int, std::allocator<int> > const&, int const&);
template bool Datastruct<float>::search<std::vector>(std::vector<float, std::allocator<float> > const&, float const&);
template void Datastruct<float>::print<std::vector>(std::vector<float, std::allocator<float> > const&);
template void Datastruct<double>::print<std::vector>(std::vector<double, std::allocator<double> > const&);



template <typename T>
Datastruct<T>::Datastruct(const Datastruct<T> &copyFrom) : DeclObject(copyFrom)
{
    // any other properties specific to Datastruct
}


template <typename T>
template <template <typename, typename> class Container>
bool Datastruct<T>::search(const Container<T, std::allocator<T>> &container, const T &value) {
    //search for the value in the container
    return std::find(container.begin(), container.end(), value) != container.end();
}

template <typename T>
template <template <typename, typename> class Container>
void Datastruct<T>::print(const Container<T, std::allocator<T>> &container)
{
    for (const auto &x : container)
    {
        cout << x << ":";
    }
    cout << endl;
}