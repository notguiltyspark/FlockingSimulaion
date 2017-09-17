#include "Vector2_ext.h"

float mag(const sf::Vector2f& v) {
	return sqrt(v.x*v.x + v.y*v.y);
}

float dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

float angleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	float dotProduct = dot(v1, v2);
	float phi = acos(dotProduct / mag(v1) / mag(v2));
	return phi;
}

sf::Vector2f norm(const sf::Vector2f& v) {  // ref&?
	return sf::Vector2f(v.x / mag(v), v.y / mag(v));
}


sf::Vector2f operator*(sf::Vector2f v, double d) {
	v.x *= d;
	v.y *= d;
	return v;
}


sf::Vector2f operator/(sf::Vector2f v, double d) {
	v.x /= d;
	v.y /= d;
	return v;
}


sf::Vector2f operator/(sf::Vector2f v, int d) {
	v.x /= d;
	v.y /= d;
	return v;
}

sf::Vector2f getNormalPoint(const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b) {
	auto v_ap = p - a;
	auto v_ab = b - a;
	v_ab = norm(v_ab);
	auto dot_product = dot(v_ab, v_ap);
	v_ab *= dot_product;
	auto normalPoint = a + v_ab;
	return normalPoint;

}

int randint(int min, int max)
{
	static std::default_random_engine ran;
	return std::uniform_int_distribution<>{min, max}(ran);
}


int randint(int max)
{
	return randint(0, max);
}
