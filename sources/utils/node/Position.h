#ifndef PROJET_RESEAU_CPP_POSITION_H
#define PROJET_RESEAU_CPP_POSITION_H

/**
 * class defining a position with a point x and y.
 *
 * @author COUTAND Bastien
 * @version 1.1
 * @date 20.04.2022
 */
class Position {
    private:
        /**
         * The x and y coordinates.
         */
        int _x, _y;

    public:
        Position(int x, int y);

        /**
         * Function that returns the coordinates x.
         * @return int
         */
        int getX() const;

        /**
         * Function that returns the coordinates y.
         * @return int
         */
        int getY() const;

        /**
         * Function that compares two positions and checks if they are equal.
         * @param otherPosition : the otherPosition to be compared with the instance.
         * @return true if equals, otherwise false.
         */
        bool operator==(Position otherPosition) const;
};


#endif //PROJET_RESEAU_CPP_POSITION_H
