#include "geometry.h"
#include <cassert>
#include <iostream>


Position::Position(int x_coord, int y_coord) : xx{x_coord}, yy{y_coord} { std::cout << "Position constructor\n"; };

Position::Position(const Position &pos) : xx{pos.xx}, yy{pos.yy} { std::cout << "Postion copy constructor\n"; }

Position::Position(Position &&pos) : xx{std::move(pos.xx)}, yy{std::move(pos.yy)} {
    std::cout << "Position move constructor\n";
}

Position &Position::operator=(const Position &pos) {
    std::cout << "Position copy assignment\n";
    xx = pos.xx;
    yy = pos.yy;
    return *this;
}

bool Position::operator==(const Position &pos) const {
    return (xx == pos.xx && yy == pos.yy);
}

int Position::x() const { return xx; }

int Position::y() const { return yy; }

Position Position::reflection() const {
    std::cout << "Creating Position reflection\n";;
    return Position {yy, xx};
}

Position Position::operator+=(const Vector &v) const {
    std::cout << "Adding vector to Position\n";
    return Position {xx + v.x(), yy + v.y()};
}

Position &Position::origin() {
    static Position v = Position{0, 0};
    return v;
}

Position::~Position() { std::cout << "Position destructor\n"; }

Vector::Vector(int x_coord, int y_coord) : xx{x_coord}, yy{y_coord} { std::cout << "Vector constructor\n"; };

Vector::Vector(const Vector &vec) : xx{vec.xx}, yy{vec.yy} { std::cout << "Vector copy constructor\n"; }

Vector::Vector(Vector &&vec) : xx{std::move(vec.xx)}, yy{std::move(vec.yy)} { std::cout << "Vector move costructor"; }

bool Vector::operator==(const Vector &vec) const {
    return (xx == vec.xx && yy == vec.yy);
}

int Vector::x() const { return xx; }

int Vector::y() const { return yy; }

Vector Vector::reflection() const {
    std::cout << "Vector.reflection()\n";
    return Vector{yy, xx};
}

Vector Vector::operator+=(const Vector &vec) const {
    return Vector{xx + vec.xx, yy + vec.yy};
}

Vector::~Vector() { std::cout << "Vector destructor\n"; }

Rectangle::Rectangle(int w, int h) :
        left_bottom(Position::origin()),
        wth(w),
        ht(h) {
    std::cout << "Rectangle constructor without position\n";
}

Rectangle::Rectangle(int w, int h, const Position &pos) :
        left_bottom(pos),
        wth(w),
        ht(h) {
    std::cout << "Rectangle constructor with lvalue position\n";
}

Rectangle::Rectangle(int w, int h, Position &&pos) :
        left_bottom(std::move(pos)),
        wth(w),
        ht(h) {
    std::cout << "Rectangle constructor with rvalue position\n";
}

Rectangle::Rectangle(const Rectangle &rec) : wth(rec.wth), ht(rec.ht), left_bottom(rec.left_bottom) {
    std::cout << "Rectangle copy constructor\n";
};

Rectangle::Rectangle(Rectangle &&rec) : wth(rec.wth), ht(rec.ht), left_bottom(std::move(rec.left_bottom)) {
    std::cout << "Rectangle move constructor\n";
};

Rectangle &Rectangle::operator=(Rectangle &&rec) {
    std::cout << "Rectangle move assignment operator\n";
    ht = rec.ht;
    wth = rec.wth;
    left_bottom = std::move(rec.left_bottom);
    return *this;
}


Rectangle &Rectangle::operator=(const Rectangle &rec) {
    std::cout << "Rectangle copy assignment operator\n";
    ht = rec.ht;
    wth = rec.wth;
    left_bottom = rec.left_bottom;
    return *this;
}

bool Rectangle::operator==(const Rectangle &rec) const {
    return (ht == rec.ht
            && wth == rec.wth
            && left_bottom == rec.left_bottom);
}

int Rectangle::height() const { return ht; }

int Rectangle::width() const { return wth; }

Position Rectangle::pos() const { return left_bottom; }

Rectangle Rectangle::operator+=(const Vector &v) const {
    return Rectangle {ht, wth, left_bottom += v};
}

int Rectangle::area() const { return ht * wth; }

std::pair<Rectangle, Rectangle> Rectangle::split_horizontally(int place) const {
    int lb_x = left_bottom.x(), lb_y = left_bottom.y();
    assert(place >= lb_y && place <= lb_y + ht);
    return std::pair<Rectangle, Rectangle>
            {Rectangle {wth, place - lb_y, left_bottom},
             Rectangle {wth, lb_y + ht - place, Position{lb_x, place}}};
};

std::pair<Rectangle, Rectangle> Rectangle::split_vertically(int place) const {
    std::cout << "Rectangle.split_vertically()\n";
    int lb_x = left_bottom.x(), lb_y = left_bottom.y();
    assert(place >= lb_x && place <= lb_x + wth);;
    std::cout << "split_vertically() return\n";
    return std::pair<Rectangle, Rectangle>
            {Rectangle {place - lb_x, ht, left_bottom},
             Rectangle {lb_x + wth - place, ht, Position{place, lb_y}}};
};

Rectangle::~Rectangle() { std::cout << "Rectangle destructor\n"; }


Rectangles::Rectangles(const std::vector<Rectangle> &rec) : rects(rec) {
    std::cout << "Rectangles constructor with lvalue vector\n";
};

Rectangles::Rectangles(std::vector<Rectangle> &&rec) : rects(std::move(rec)) {
    std::cout << "Rectangles constructor with rvalue vector\n";
};

Rectangles::Rectangles() : rects({}) { std::cout << "Rectangles default constructor\n"; };

Rectangles::Rectangles(const Rectangles &recs) : rects(recs.rects) { std::cout << "Rectangles copy constructor\n"; }

Rectangles::Rectangles(Rectangles &&recs) : rects(std::move(recs.rects)) {
    std::cout << "Rectangles move constructor\n";
}

Rectangles &Rectangles::operator=(const Rectangles &recs) {
    std::cout << "Rectangles copy assignment\n";
    rects = recs.rects;
}

Rectangles &Rectangles::operator=(Rectangles &&recs) {
    std::cout << "Rectangles move assignment\n";
    rects = std::move(recs.rects);
    return *this;
}

Rectangle Rectangles::operator[](const unsigned &i) const { return rects[i]; };

unsigned long Rectangles::size() const { return rects.size(); };

bool Rectangles::operator==(const Rectangles rs) const {
    if (rects.size() != rs.size())
        return false;
    unsigned long s = rects.size(), i = 0;
    for (; i < s; ++i) {
        if (rects[i] == rs.rects[i]) {}
        else
            return false;
    }
    return true;
}

Rectangles Rectangles::operator+=(const Vector &v) const {
    std::vector<Rectangle> new_rects;
    unsigned long s = rects.size(), i = 0;
    new_rects.reserve(s + 1);
    for (; i < s; ++i) {
        new_rects.push_back(rects[i] += v);
    }
    return Rectangles{new_rects};
}

Rectangles Rectangles::split(Type type, const unsigned long idx, const int place) const {
    std::vector<Rectangle> new_rects;
    unsigned long i = 0, s = rects.size();
    new_rects.reserve(s + 1);
    for (; i < s; ++i) {
        if (i == idx) {
            std::cout << "Splitting " << idx << " Rectangle\n";
            if (type == Type::HORIZONTALLY) {
                std::pair<Rectangle, Rectangle> r = std::move(rects[i].split_horizontally(place));
                new_rects.push_back(std::move(r.first));
                new_rects.push_back(std::move(r.second));
            } else {
                std::pair<Rectangle, Rectangle> r = std::move(rects[i].split_vertically(place));
                std::cout << "Adding first splitted\n";
                new_rects.push_back(std::move(r.first));
                std::cout << "Adding second splitted\n";
                new_rects.push_back(std::move(r.second));
            }
        } else {
            std::cout << "Adding non-splitted\n";
            new_rects.push_back(std::move(rects[i]));
        }
    }
    std::cout << "Rectangles.split_vertically return\n";
    return Rectangles(std::move(new_rects));
}

Rectangles Rectangles::split_horizontally(const unsigned long idx, const int place) const {
    return split(Type::HORIZONTALLY, idx, place);
}

Rectangles Rectangles::split_vertically(const unsigned long idx, const int place) const {
    return split(Type::VERTICALLY, idx, place);
}

Rectangles::~Rectangles() { std::cout << "Rectangles destructor\n"; }


