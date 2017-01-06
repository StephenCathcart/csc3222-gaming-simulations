#ifndef VECTOR3DSTACK_H
#define VECTOR3DSTACK_H

#include <iostream>

class Vec3 {

public:
	/** CONSTRUCTORS & DESTRUCTOR **/
	Vec3(void);
	Vec3(const float xyz);
	Vec3(const float x, const float y, const float z);
	Vec3(const Vec3& copy);
	~Vec3(void);

	/** MEMBER FUNCTIONS **/
	float magnitude() const;
	void addVector(const Vec3 &vector);
	void subtractVector(const Vec3 &vector);
	void multiplyByScalar(const float value);
	void divideByScalar(const float value);
	float dot(const Vec3 &vector) const;
	Vec3 cross(const Vec3 &vector) const;
	Vec3 normalise();
	Vec3 orthogonalVector(const Vec3 vector) const;

	static float distance(const Vec3 v0, const Vec3 v1);
	float x() const { return m_x; };
	float y() const { return m_y; };
	float z() const { return m_z; };
	void x(float x) { m_x = x; };
	void y(float y) { m_y = y; };
	void z(float z) { m_z = z; };

	/** OPERATOR OVERLOADS **/
	Vec3 operator+(const Vec3 &vector) const;							// Add vectors
	void operator+=(const Vec3 &vector);
	Vec3 operator-(const Vec3 &vector) const;							// Subtract vectors
	void operator-=(const Vec3 &vector);
	Vec3 operator*(const float scalar) const;							// Multiply by scalar
	void operator*=(const float scalar);
	Vec3 operator/(const float scalar) const;							// Divide by scalar
	void operator/=(const float scalar);
	float operator*(const Vec3 &vector) const; 							// Dot product
	Vec3 operator%(const Vec3 &vector) const;							// Cross product
	Vec3 operator=(const Vec3 vector);									// Assignment
	friend std::ostream& operator<<(std::ostream& o, const Vec3& v);	// To string
	bool operator==(const Vec3 &vector) const;							// Equals
	bool operator!=(const Vec3 &vector) const;							// Not equals

private:
	float m_x;
	float m_y;
	float m_z;
};


#endif 