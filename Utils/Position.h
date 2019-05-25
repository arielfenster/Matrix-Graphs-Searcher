//
// Created by ariel on 1/11/19.
//

#ifndef EX4_POSITION_H
#define EX4_POSITION_H


class Position {
    int m_x;
    int m_y;

public:
    Position(int rowNum, int colNum) : m_x(rowNum), m_y(colNum) {}

    ~Position() {}

    bool operator==(const Position *p) const {
        return (this->m_x == p->m_x) && (this->m_y == p->m_y);
    }

    Position &operator=(const Position *p) {
        m_x = p->getX();
        m_y = p->getY();
        return *this;
    }

    int getX() const { return m_x; }

    int getY() const { return m_y; }
};


#endif //EX4_POSITION_H
