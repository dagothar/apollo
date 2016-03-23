#ifndef _VEC_H
#define _VEC_H

#include <cmath>

#include "model.h"

struct Quaternion;

struct Vector {
    double x, y, z;
    
    Vector();
    Vector(const Vector &v);
    Vector(const Quaternion &q);
    Vector(const double _x, const double _y,  const double _z);
    
    Vector &operator=(const Vector &v);
    Vector &operator=(const Quaternion &q);
    Vector &operator+=(const Vector &v);
    Vector &operator-=(const Vector &v);
    Vector &operator*=(const double &f);
    Vector &operator/=(const double &f);
    bool operator==(const Vector &v) const;
    bool operator!=(const Vector &v) const;
    Vector operator+(const Vector &v) const;
    Vector operator-(const Vector &v) const;
    Vector operator*(const double f) const;
    Vector operator*(const Vector &v) const;
    Vector operator*(const Quaternion &q) const;
    
    Vertex to_vertex();
    
    Vector &normalise();
    double magnitude() const;
    
    //friend Vector operator-(const Vector &v);
};

//Vector operator-(const Vector &v);

typedef float Matrix[16];

struct Quaternion {
    double x, y, z, w;
    
    Quaternion();
    Quaternion(const Quaternion &q);
    Quaternion(const Vector &v);
    Quaternion(double _x, double _y, double _z, double _w);
    
    Quaternion &operator=(const Quaternion &q);
    Quaternion &operator=(const Vector &v);
    Quaternion &operator+=(const Quaternion &q);
    Quaternion &operator-=(const Quaternion &q);
    Quaternion &operator*=(const double &f);
    Quaternion &operator/=(const double &f);
    Quaternion operator+(const Quaternion &q) const;
    Quaternion operator-(const Quaternion &q) const;
    Quaternion operator*(const Quaternion &q) const;
    Vector operator*(const Vector &v) const;
    Quaternion operator*(const double f) const;
    
    Quaternion &from_axis(const Vector &axis, double angle);
    Quaternion &from_euler(double pitch, double yaw, double roll);
    
    Vector to_euler() const;
    void to_matrix(Matrix m) const;
    
    Quaternion &normalise();
    Quaternion get_conjugate() const;
};

// przelicz stopnie na radiany
double deg_to_rad(double angle);

// przelicz radiany na stopnie
double rad_to_deg(double angle);

#endif
