#pragma once
class vector2
{
public:
    float x = 0, y = 0;
    vector2();
    vector2(float x, float y);
    ~vector2();
public:
    vector2 operator+(const vector2& other) const;
    vector2 operator-(const vector2& other) const;
    vector2 operator*(float scalar) const;
    vector2 operator/(float scalar) const;
    
    void operator+=(const vector2& other);
    void operator-=(const vector2& other);
    void operator*=(float scalar);
    void operator/=(float scalar);
    
    float operator*(const vector2& other) const;

    float length() const;
    vector2 normalize() const;
};

