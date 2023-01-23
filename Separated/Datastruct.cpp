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
template void Datastruct<double>::bubbleASC<std::vector>(std::vector<double, std::allocator<double> >&);
template void Datastruct<float>::bubbleASC<std::vector>(std::vector<float, std::allocator<float> >&);
template void Datastruct<int>::bubbleASC<std::vector>(std::vector<int, std::allocator<int> >&);
template void Datastruct<double>::bubbleDESC<std::vector>(std::vector<double, std::allocator<double> >&);
template void Datastruct<float>::bubbleDESC<std::vector>(std::vector<float, std::allocator<float> >&);
template void Datastruct<int>::bubbleDESC<std::vector>(std::vector<int, std::allocator<int> >&);





template <typename T>
Datastruct<T>::Datastruct(const Datastruct<T> &copyFrom) : DeclObject(copyFrom)
{
    // any other properties specific to Datastruct
}

template <typename T>
template <template <typename, typename> class Container>
void Datastruct<T>::bubbleASC(Container<T, std::allocator<T>> &container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        for (auto it2 = container.begin(); it2 != container.end() - 1; ++it2) {
            if (*it2 > *(it2 + 1)) {
                std::iter_swap(it2, it2 + 1);
            }
        }
    }
}

template <typename T>
template <template <typename, typename> class Container>
void Datastruct<T>::bubbleDESC(Container<T, std::allocator<T>> &container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        for (auto it2 = container.begin(); it2 != container.end() - 1; ++it2) {
            if (*it2 < *(it2 + 1)) {
                std::iter_swap(it2, it2 + 1);
            }
        }
    }
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