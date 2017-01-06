#include "Vec3.h"
#include <math.h>

/** CONSTRUCTORS & DESTRUCTOR **/

/**
 *	Default constructor
 */
Vec3::Vec3(void) 
	: m_x(0.0f), m_y(0.0f), m_z(0.0f){
}

/**
 *	Constructor with explict x, y, z values
 */
Vec3::Vec3(const float xyz) 
	: m_x(xyz), m_y(xyz), m_z(xyz){
}

/**
 *	Constructor with explict x, y and z values
 */
Vec3::Vec3(const float x, const float y, const float z) 
	: m_x(x), m_y(y), m_z(z) {
}

/**
 *	Copy constructor
 */
Vec3::Vec3(const Vec3& copy) 
	: m_x(copy.m_x), m_y(copy.m_y), m_z(copy.m_z){
}

/**
 *	Destructor
 */
Vec3::~Vec3(void) {
}

/** MEMBER FUNCTIONS **/

/**
 *	Returns the magnitude of the vector as a float
 */
float Vec3::magnitude() const {
	/** COURSEWORK NOTE: Square roots should be avoided to improve performance, 
	a look up table could be used instead */
	return sqrt((m_x*m_x)+(m_y*m_y)+(m_z*m_z));
}

/**
 *	Adds a vector to the current vector
 */
void Vec3::addVector(const Vec3 &vector) {
	m_x += vector.m_x;
	m_y += vector.m_y;
	m_z += vector.m_z;
}

/**
 *	Subtracts a vector from the current vector
 */
void Vec3::subtractVector(const Vec3 &vector) {
	m_x -= vector.m_x;
	m_y -= vector.m_y;
	m_z -= vector.m_z;
}

/**
 *	Multiplies the current vector by a scalar value
 */
void Vec3::multiplyByScalar(const float scalar) {
	m_x *= scalar;
	m_y *= scalar;
	m_z *= scalar;
}

/**
 *	Divides the current vector by a scalar value
 */
void Vec3::divideByScalar(const float scalar) {
	if (scalar == 0.0f){
		throw std::overflow_error("Divide by zero exception");
	}
	m_x /= scalar;
	m_y /= scalar;
	m_z /= scalar;
}

/**
 *	Returns the dot product of this vector and the vector
 *	passed in as a float
 */
float Vec3::dot(const Vec3 &vector) const {
	return (m_x*vector.m_x) + (m_y*vector.m_y) + (m_z*vector.m_z);
}

/**
 *	Returns the cross product of this vector and the vector
 *	passed in as a float
 */
Vec3 Vec3::cross(const Vec3 &vector) const {
	return Vec3((m_y*vector.m_z) - (m_z*vector.m_y) , 
				(m_z*vector.m_x) - (m_x*vector.m_z) ,
				(m_x*vector.m_y) - (m_y*vector.m_x));	
}

/**
 *	Normalises the current vector (vector will have magnitude of 1)
 */
Vec3 Vec3::normalise() {
	float x, y, z;
	x = y = z = 0;

	float mag = magnitude();
	if(mag != 0.0f) {
		mag = 1.0f / mag;
		x = m_x * mag;
		y = m_y * mag;
		z = m_z * mag;
	}
	Vec3 normalVec(x, y, z);
	return normalVec;
}

/**
 *	Cross product both vectors then normalise the result
 */
Vec3 Vec3::orthogonalVector(const Vec3 vector) const {
	Vec3 oVec = cross(vector);
	return oVec.normalise();
}

float Vec3::distance(const Vec3 v0, const Vec3 v1) {
	return sqrt( pow((v1.x() - v0.x()), 2) + pow((v1.y() - v0.y()),2) + pow((v1.z() - v0.z()),2) );
}

/** OPERATOR OVERLOADS **/

/**
 *	Returns the addition of another vector3D as a new vector3D
 */
Vec3 Vec3::operator+(const Vec3 &vector) const {
	return Vec3(m_x + vector.m_x, m_y + vector.m_y, m_z + vector.m_z);
}

/**
 *	Adds another vector3D to the current vector3D
 */
void Vec3::operator+=(const Vec3 &vector) {
	addVector(vector);
}

/**
 *	Returns the subtraction of another vector3D as a new Vector3D
 */
Vec3 Vec3::operator-(const Vec3 &vector) const {
	return Vec3(m_x - vector.m_x, m_y - vector.m_y, m_z - vector.m_z);
}

/**
 *	Subtracts another vector3D from the current vector3D
 */
void Vec3::operator-=(const Vec3 &vector) {
	subtractVector(vector);
}

/**
 *	Returns the multiplication of a vector and a scalar value as 
 *	a new vector3D
 */
Vec3 Vec3::operator*(const float scalar) const {
	return Vec3(m_x * scalar, m_y * scalar, m_z * scalar);
}

/**
 *	Multiplies the current vector by a scalar value
 */
void Vec3::operator*=(const float scalar) {
	multiplyByScalar(scalar);
}

/**
 *	Returns the division of the current vector by a scalar value as
 *	a new vector3D
 */
Vec3 Vec3::operator/(const float scalar) const {
	if (scalar == 0.0f){
		throw std::overflow_error("Divide by zero exception");
	}
	return Vec3(m_x / scalar, m_y / scalar, m_z / scalar);
}

/**
 *	Divides the current vector by a scalar value
 */
void Vec3::operator/=(const float scalar) {
	divideByScalar(scalar);
}

/**
 *	Returns the dot product of the vector and the vector given as
 *	a float
 */
float Vec3::operator*(const Vec3 &vector) const {
	return dot(vector);
}

/**
 *	Returns the cross product of the vector and the vector given as
 *	a float
 */
Vec3 Vec3::operator%(const Vec3 &vector) const {
	return cross(vector);
}

/**
 *	Overloads assignment operator
 */
Vec3 Vec3::operator=(const Vec3 vector) {
	if(this == &vector){
		return *this;
	}
	m_x = vector.m_x;
	m_y = vector.m_y;
	m_z = vector.m_z;
	return *this;
}

/**
 *	Overloads ostream operator
 */
std::ostream& operator<<(std::ostream& o, const Vec3& v) {
	o << "Vec3(" << v.m_x << "," << v.m_y << "," << v.m_z <<")" << std::endl;
	return o;
}

/**
 *	Overloads equal operator
 */
bool Vec3::operator==(const Vec3 &vector) const {
	return (vector.m_x == m_x && vector.m_y == m_y && vector.m_z == m_z) ? true : false;
}

/**
 *	Overloads not equal operator
 */
bool Vec3::operator!=(const Vec3 &vector) const {
	return (vector.m_x == m_x && vector.m_y == m_y && vector.m_z == m_z) ? false : true;
}
