#ifndef VEC2_HPP_GUARD
#define VEC2_HPP_GUARD

struct Vec2 {
public:
    float x;
    float y;

    Vec2(float x,float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &other) {
        return Vec2(this->x + other.x, this->y + other.y);
    }

    Vec2 operator-(const Vec2 &other) {
        return Vec2(this->x - other.x, this->y - other.y);
    }

    Vec2 operator*(const float &other) {
        return Vec2(this->x * other, this->y * other);
    }

    Vec2 operator/(const float &other) {
        return Vec2(this->x / other, this->y / other);
    }

    float lenght_squared() {
        return this->x*this->x + this->y*this->y;
    }

    float lenght() {
        return sqrt(this->lenght_squared());
    }

    Vec2 normalize() {
        return *this / this->lenght();
    }

    float dot(const Vec2 &other) {
        return this->x * other.x + this->y * other.y;
    }
};

#endif // VEC2_HPP_GUARD