#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <typeinfo>
#include <vector>
#include <string.h>
#include <random>
#include <algorithm>
#include <initializer_list>
#include <cassert>
using namespace std;

template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;
private:
    T* const data;
    size_type const y_size, x_size;

public:
    Grid(T* data, size_type y_size, size_type x_size) :
        data(data), y_size(y_size), x_size(x_size) { }

    //copy constructor
    Grid(Grid<T> const& other) {
        data = other.data;
        y_size = other.y_size;
        x_size = other.x_size;
    };

    //move constructor
    Grid(Grid<T>&& other) {
        swap(data, other.data);
        swap(x_size, other.x_size);
        swap(y_size, other.y_size);
        other.data = nullptr;
        other.x_size = 0;
        other.y_size = 0;

    };

    //copy operator
    Grid<T>& operator=(Grid<T>& other) {
        delete[] data;
        data = other.data;
        y_size = other.y_size;
        x_size = other.x_size;
        return *this;
    };

    //move operator
    Grid<T>& operator=(Grid<T>&& other) {
        swap(data, other.data);
        swap(x_size, other.x_size);
        swap(y_size, other.y_size);
        other.data = nullptr;
        other.x_size = 0;
        other.y_size = 0;
        return *this;
    };

    //destructor
    ~Grid() {
        delete[] data;
    }

    //create new grid 1x1
    Grid(T const& t) : x_size(1), y_size(1), data(new T[1]) { data[0] = t; }

    //read
    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    //write
    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    //assignment operator
    Grid<T>& operator=(T const& t) {
        for (
            auto it = data, end = data + x_size * y_size;
            it != end; it++
            ) * it = t;
        return *this;
    }

    //create new grid y by x
    Grid(size_type y, size_type x) : x_size(x), y_size(y), data(new T[x * y]) {
        for (auto it = data, end = data + x * y; it != end; ++it) {
            *it = T();
        }
    }

    //create new grid y by x filled with t
    Grid(size_type y, size_type x, T const& t) : x_size(x), y_size(y), data(new T[x * y]) {
        for (auto it = data, end = data + x * y; it != end; ++it) {
            *it = t;
        }
    }

    //accessor functions
    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }

    //index operator
    T* operator[] (size_type index) {
        return &data[index * x_size];
    }
};


int main() {
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using size_type = size_t;

    for (size_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (size_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for (size_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (size_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (size_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (size_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g[y_idx][x_idx]);
    return 0;
}