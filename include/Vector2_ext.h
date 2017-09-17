#pragma once
#ifndef VECTOR2_EXT_H
#define VECTOR2_EXT_H

#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

constexpr double PI = 3.14159265359;

float mag(const sf::Vector2f& v);
float dot(const sf::Vector2f& v1, const sf::Vector2f& v2);
float angleBetween(const sf::Vector2f& v1, const sf::Vector2f& v2);

sf::Vector2f norm(const sf::Vector2f& v);
sf::Vector2f getNormalPoint(const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b);
sf::Vector2f operator*(sf::Vector2f v, double d);
sf::Vector2f operator/(sf::Vector2f v, double d);
sf::Vector2f operator/(sf::Vector2f v, int d);

int randint(int min, int max);
int randint(int max);

//inlining maybe?

#endif
