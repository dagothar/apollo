#include "vectors.h"

const double PIOVER180 = M_PI / 180.0;

//pzelicza stopnie na radiany
double deg_to_rad(double angle)
{
    return angle * PIOVER180;
}

//przelicza radiany na stopnie
double rad_to_deg(double angle)
{
    return angle / PIOVER180;
}

//konstruktor; tworzy wektor zerowy
Vector::Vector() : x(0.0), y(0.0), z(0.0)
{
}

//konstruktor kopiujacy
Vector::Vector(const Vector &v) : x(v.x), y(v.y), z(v.z)
{
}

//konstruktor; przeksztalca kwaternion na wektor, skladowa w jest pomijana
Vector::Vector(const Quaternion &q) : x(q.x), y(q.y), z(q.z)
{
}

//konstruktor; tworzy wektor na podstawie 3 podanych wspolrzednych
Vector::Vector(const double _x, const double _y,  const double _z) : x(_x), y(_y), z(_z)
{
}

//operator =
Vector &Vector::operator=(const Vector &v)
{
    if(this == &v) return *this;
    
    x = v.x;
    y = v.y;
    z = v.z;
    
    return *this;
}

//operator = dla przypisania kwaternionu, pomija sie wspolrzedna w
Vector &Vector::operator=(const Quaternion &q)
{
    x = q.x;
    y = q.y;
    z = q.z;
}

//operator += dla dodawania wektorow
Vector &Vector::operator+=(const Vector &v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    
    return *this;
}

//operator -= dla odejmowania wektorow
Vector &Vector::operator-=(const Vector &v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    
    return *this;
}

//operator *= dla skalowania wektora
Vector &Vector::operator*=(const double &f)
{
    x *= f;
    y *= f;
    z *= f;
}

//operator /= dla skalowania wektora
Vector &Vector::operator/=(const double &f)
{
    x /= f;
    y /= f;
    z /= f;
}

//operator == dla porownywania wektora
bool Vector::operator==(const Vector &v) const
{
    return (x == v.x && y == v.y && z == v.z);
}

//operator != dla porownywania wektora
bool Vector::operator!=(const Vector &v) const
{
    return !(*this == v);
}

//operator * dla skalowania wektora
Vector Vector::operator*(const double f) const
{
    return Vector(f * x, f * y, f * z);
}

//operator * dla mnozenia wektorowego
Vector Vector::operator*(const Vector &v) const
{
    return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

//operator * dla mnozenia wektorowego z kwaternionem
Vector Vector::operator*(const Quaternion &q) const
{
    return Vector(Quaternion(*this) * q);
}

//operator - dla odwracania wektora
Vector operator-(const Vector &v)
{
    return Vector(-v.x, -v.y, -v.z);
}

//operator + dla dodawania wektorow
Vector Vector::operator+(const Vector &v) const
{
    Vector result = *this;
    
    result += v;
    
    return result;
}

//operator - dla odejmowania wektorow
Vector Vector::operator-(const Vector &v) const
{
    Vector result = *this;
    
    result -= v;
    
    return result;
}

//zamiana na vertex
Vertex Vector::to_vertex()
{
       return Vertex(x, y, z);
}
    
//normalizacja wektora; zachowuje kierunek, ustawia dlugosc na 1
Vector &Vector::normalise()
{
    double mag = magnitude();
    x /= mag;
    y /= mag;
    z /= mag;
    
    return *this;
}

//zwraca dlugosc wektora
double Vector::magnitude() const
{
    return sqrt(x*x + y*y + z*z);
}

Quaternion::Quaternion() : x(0.0), y(0.0), z(0.0), w(0.0)
{
}

Quaternion::Quaternion(const Quaternion &q) : x(q.x), y(q.y), z(q.z), w(q.w)
{
}

Quaternion::Quaternion(const Vector &v) : x(v.x), y(v.y), z(v.z), w(0.0)
{
}

Quaternion::Quaternion(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w)
{
}

Quaternion &Quaternion::operator=(const Quaternion &q)
{
    if(this == &q) return *this;
    
    x = q.x;
    y = q.y;
    z = q.z;
    w = q.w;
    
    return *this;
}

Quaternion &Quaternion::operator=(const Vector &v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = 0.0;
    
    return *this;
}

Quaternion &Quaternion::operator+=(const Quaternion &q)
{
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;
    
    return *this;
}

Quaternion &Quaternion::operator-=(const Quaternion &q)
{
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;
    
    return *this;
}

Quaternion &Quaternion::operator*=(const double &f)
{
    x *= f;
    y *= f;
    z *= f;
    w *= f;
}

Quaternion &Quaternion::operator/=(const double &f)
{
    x /= f;
    y /= f;
    z /= f;
    w /= f;
}

Quaternion Quaternion::operator+(const Quaternion &q) const
{
    Quaternion result = *this;
    
    result += q;
    
    return result;
}

Quaternion Quaternion::operator-(const Quaternion &q) const
{
    Quaternion result = *this;
    
    result -= q;
    
    return result;
}

Quaternion Quaternion::operator*(const Quaternion &q) const
{
    return Quaternion(  w * q.x + x * q.w + y * q.z - z * q.y,
                        w * q.y + y * q.w + z * q.x - x * q.z,
                        w * q.z + z * q.w + x * q.y - y * q.x,
                        w * q.w - x * q.x - y * q.y - z * q.z);
}

Vector Quaternion::operator*(const Vector &v) const
{
    Vector vn(v);
    
    Quaternion vq(vn.x, vn.y, vn.z, 0.0), rq;
    rq = vq * get_conjugate();
    rq = *this * rq;
    
    return Vector(rq.x, rq.y, rq.z);
}

Quaternion Quaternion::operator*(const double f) const
{
    return Quaternion(f * x, f * y, f * z, f * w);
}

Quaternion &Quaternion::from_axis(const Vector &axis, double angle)
{
    angle = deg_to_rad(angle);
    double sinangle = sin(angle);
    Vector tv(axis);
    tv.normalise();
    
    x = tv.x * sinangle;
    y = tv.y * sinangle;
    z = tv.z * sinangle;
    w = cos(angle);
    
    return *this;
}

Quaternion &Quaternion::from_euler(double pitch, double yaw, double roll)
{
    pitch = deg_to_rad(pitch / 2.0);
    yaw = deg_to_rad(yaw / 2.0);
    roll = deg_to_rad(roll / 2.0);
    
    double sinp = sin(pitch), cosp = cos(pitch);
    double siny = sin(yaw), cosy = cos(yaw);
    double sinr = sin(roll), cosr = cos(roll);
    
    x = sinr * cosp * cosy - cosr * sinp * siny;
    y = cosr * sinp * cosy + sinr * cosp * siny;
    z = cosr * cosp * siny - sinr * sinp * cosy;
    w = cosr * cosp * cosy + sinr * sinp * siny;

    normalise();
    
    return *this;
}

Vector Quaternion::to_euler() const
{
       //Vector i(1, 0, 0);
       //i = get_conjugate() * i;

       /*double yw = y * w;
       double xz = x * z;
       double xy = x * y;
       double zw = z * w;
       double xw = x * w;
       double yz = y * z;
    
       double x2 = x * x;
       double y2 = y * y;
       double z2 = z * z;
    
       Vector result( rad_to_deg(atan2(2.0 * (yw - xz), 1.0 - 2.0 * (y2 + z2))),
                      rad_to_deg(asin(2.0 * (xy + zw))),
                      -rad_to_deg(atan2(2.0 * (xw - yz), 1.0 - 2.0 * (x2 + z2))));
                      
       if(i.x < 0.0) if(i.y <= 0.0) result.y = 180.0 - result.y; else result.y = -180.0 - result.y;*/
       /*if(result.y > 90.0) result.x += 180.0, result.z += 180.0;
       if(result.x > 180.0) result.x = 180.0 - result.x;
       if(result.y > 180.0) result.y = 180.0 - result.y;
       if(result.z > 180.0) result.z = 180.0 - result.z;
       if(result.x < -180.0) result.x = 180.0 - result.x;
       if(result.y < -180.0) result.y = 180.0 - result.y;
       if(result.z < -180.0) result.z = 180.0 - result.z;*/
       Vector i(1, 0, 0);
       i = get_conjugate() * i;
       Vector j(0, 1, 0);
       j = get_conjugate() * j;
       Vector k(0, 0, 1);
       k = get_conjugate() * k;
       
       Vector result;
       result.x = 180.0*asin(i.z)/M_PI;
       result.y = -180.0*asin(i.y)/M_PI;
       result.z = 180.0*asin(j.z)/M_PI;
       
       //poprawki
       if(i.x < 0.0) if(i.y <= 0.0) result.y = 180.0 - result.y; else result.y = -180.0 - result.y;

       //poprawka na roll>90
       if(k.z < 0.0) if(k.y <= 0.0) result.z = 180.0 - result.z; else result.z = -180.0 - result.z;
       
       //poprawka na pitch>90
       //if((result.y < 90.0) && (result.y > -90.0)) {
       //            if(i.x < 0.0) if(i.z >= 0.0) result.x = 180.0 - result.x; else result.x = -180.0 - result.x;
       //}
       //else {
       //            if(i.x > 0.0) if(i.z < 0.0) result.x = 180.0 - result.x; else result.x = -180.0 - result.x;
       //}
       
       //ogranicz do +/- pi
       if(result.z > 180.0) result.z = result.z - 360.0;
       if(result.z < -180.0) result.z = result.z + 360.0;
      
       return result;
}

void Quaternion::to_matrix(Matrix m) const
{
    double x2 = x * x;
    double y2 = y * y;
    double z2 = z * z;
    double xy = x * y;
    double xz = x * z;
    double yz = y * z;
    double wx = w * x;
    double wy = w * y;
    double wz = w * z;
    
    m[0]  = 1.0 - 2.0 * (y2 + z2); m[1]  = 2.0 * (xy - wz);       m[2]  = 2.0 * (xz + wy);       m[3]  = 0.0;
    m[4]  = 2.0 * (xy + wz);       m[5]  = 1.0 - 2.0 * (x2 + z2); m[6]  = 2.0 * (yz - wx);       m[7]  = 0.0;
    m[8]  = 2.0 * (xz - wy);       m[9]  = 2.0 * (yz + wx);       m[10] = 1.0 - 2.0 * (x2 + y2); m[11] = 0.0;
    m[12] = 0.0;                   m[13] = 0.0;                   m[14] = 0.0;                   m[15] = 1.0;
}

Quaternion &Quaternion::normalise()
{
    double magnitude = sqrt(x*x + y*y + z*z + w*w);
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
    w /= magnitude;
    
    return *this;
}

Quaternion Quaternion::get_conjugate() const
{
    return Quaternion(-x, -y, -z, w);
}
