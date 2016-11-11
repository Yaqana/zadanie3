#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <utility>
#include <vector>


class Vector {
private:
    int xx, yy;
public:
    Vector(int x_coord, int y_coord);
    Vector(const Vector& vec);
    Vector(Vector&& vec);
    bool operator==(const Vector &vec) const;
    int x() const;
    int y() const;
    Vector reflection() const;
    Vector operator+=(const Vector &v) const;
    ~Vector();
};

class Position {
private:
    int xx, yy;
public:
    Position(int x_coord, int y_coord);
    Position(const Position& pos);
    Position(Position&& pos);
    Position& operator=(const Position& pos);
    bool operator==(const Position &pos) const;
    int x() const;
    int y() const;
    Position reflection() const;
    Position operator+=(const Vector &v) const;
    static Position& origin();
    ~Position();
};

class Rectangle {
private:
    Position left_bottom;
    int ht, wth;
public:
    Rectangle(int w, int h);
    Rectangle(int w, int h, const Position& pos);
    Rectangle(int w, int h, Position&& pos);
    Rectangle(const Rectangle& rec);
    Rectangle(Rectangle&& rec);
    Rectangle& operator=(const Rectangle& rec);
    Rectangle& operator=(Rectangle&& rec);
    bool operator==(const Rectangle &rec) const;
    int height() const;
    int width() const;
    Position pos() const;
    Rectangle operator+=(const Vector &v) const;
    int area() const;
    std::pair<Rectangle, Rectangle> split_horizontally(int place) const;
    std::pair<Rectangle, Rectangle> split_vertically(int place) const;
    ~Rectangle();
};

class Rectangles {
private:
    std::vector<Rectangle> rects;
    enum class Type {HORIZONTALLY, VERTICALLY};
    Rectangles split(Type type, const unsigned long idx, const int place) const;
public:
    Rectangles (const std::vector<Rectangle>& rec);
    Rectangles (std:: vector<Rectangle>&& rec);
    Rectangles();
    Rectangles(const Rectangles& recs);
    Rectangles(Rectangles&& recs);
    Rectangles& operator=(const Rectangles& recs);
    Rectangles& operator=(Rectangles&& recs);
    Rectangle operator[](const unsigned& i) const;
    unsigned long size() const;
    bool operator==(const Rectangles rs) const;
    Rectangles operator+=(const Vector& v) const;
    Rectangles split_horizontally(const unsigned long idx, const int place) const;
    Rectangles split_vertically(const unsigned long idx, const int place) const;
    ~Rectangles();
};

#endif //GEOMETRY_H
