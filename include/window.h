#ifndef WINDOW_H
#define WINDOW_H

template <typename T>
class Window
{
public:
    // Constructor
    Window(T min_x, T max_x, T min_y, T max_y) : _min_x(min_x), _max_x(max_x), _min_y(min_y), _max_y(max_y) {};

    // getters and setters
    T x_min() const { return _min_x; };
    void x_min(T x_min) { _min_x = x_min; };

    T x_max() const { return _max_x; };
    void x_max(T x_max) { _max_x = x_max; };

    T y_min() const { return _min_y; };
    void y_min(T y_min) { _min_y = y_min; };

    T y_max() const { return _max_y; };
    void y_max(T y_max) { _max_y = y_max; };

    // Public functions
    T height() { return _max_y - _min_y; };
    T width() { return _max_x - _min_y; };
    T size() { return width() * height(); };

private:
    T _min_x, _max_x, _min_y, _max_y;
};

#endif WINDOW_H