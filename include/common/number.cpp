#include "number.h"

SYSTEM BEGIN
namespace Number
{
	//--------------------
	// * Class Rational
	//--------------------
	void Rational::initialize(Rational::Type n, Rational::Type d) {
		if (d == 0) {
			num = 1;
			den = 0;
			return;
		}
		else if (n == 0) {
			num = 0;
			den = 1;
			return;
		}
		num = std::abs(n);
		den = std::abs(d);
		auto r = gcd(num, den);
		if (r) {
			num /= r;
			den /= r;
		}
		bool cond = (n > 0 && d < 0) || (n < 0 && d > 0);
		num *= cond ? -1 : 1;
	}
	Rational& Rational::operator+=(const Rational &r) {
		initialize(num * r.den + r.num * den, den * r.den);
		return *this;
	}
	Rational& Rational::operator-=(const Rational &r) {
		initialize(num * r.den - r.num * den, den * r.den);
		return *this;
	}
	Rational& Rational::operator*=(const Rational &r) {
		initialize(num * r.num, den * r.den);
		return *this;
	}
	Rational& Rational::operator/=(const Rational &r) {
		initialize(num * r.den, den * r.num);
		return *this;
	}
	//--------------------
	// * Basic
	//--------------------
	const Rational operator-(const Rational &sr) {
		return Rational(-sr.num, sr.den);
	}
	const Rational operator~(const Rational &sr) {
		return Rational(sr.den, sr.num);
	}
	const Rational operator+(const Rational &sr, const Rational &r) {
		return Rational(sr.num * r.den + r.num * sr.den, sr.den * r.den);
	}
	const Rational operator-(const Rational &sr, const Rational &r) {
		return Rational(sr.num * r.den - r.num * sr.den, sr.den * r.den);
	}
	const Rational operator*(const Rational &sr, const Rational &r) {
		return Rational(sr.num * r.num, sr.den * r.den);
	}
	const Rational operator/(const Rational &sr, const Rational &r) {
		return Rational(sr.num * r.den, sr.den * r.num);
	}
	Rational::Type ceil(const Rational &sr) {
		return (Rational::Type)std::ceil((long double)(sr.num) / sr.den);
	}
	Rational::Type floor(const Rational &sr) {
		return (Rational::Type)std::floor((long double)(sr.num) / sr.den);
	}
	Rational::Type fix(const Rational &sr) {
		return (sr.num > 0) ? floor(sr) : ceil(sr);
	}
	const Rational abs(const Rational &sr) {
		return Rational(std::abs(sr.num), sr.den);
	}
	const Rational mod(const Rational &sr, const Rational &r) {
		return sr - r * floor(sr / r);
	}
	const Rational rem(const Rational &sr, const Rational &r) {
		return sr - r * fix(sr / r);
	}
	//--------------------
	// * Compare
	//--------------------
	Rational::Type compare(const Rational &sr, const Rational &r) {
		return sr.num * r.den - r.num * sr.den;
	}
	bool operator>(const Rational &sr, const Rational &r) {
		return compare(sr, r) > 0;
	}
	bool operator>=(const Rational &sr, const Rational &r) {
		return compare(sr, r) >= 0;
	}
	bool operator==(const Rational &sr, const Rational &r) {
		return sr.num == r.num && sr.den == r.den;
	}
	bool operator!=(const Rational &sr, const Rational &r) {
		return !(sr == r);
	}
	bool operator<(const Rational &sr, const Rational &r) {
		return compare(sr, r) < 0;
	}
	bool operator<=(const Rational &sr, const Rational &r) {
		return compare(sr, r) <= 0;
	}
	//--------------------
	// * Convert
	//--------------------
	std::string to_string(const Rational &rat)
	{
		if (rat.den == 0)
			return "NaN";
		std::string result(std::to_string(rat.num));
		if (rat.den != 1)
			result += std::string("/") + std::to_string(rat.den);
		return result;
	}
	Rational get_num(const std::string &str);
	Rational to_rational(const std::string &str)
	{
		size_t i1 = str.find('/');
		size_t i2 = str.find('.');

		if (i1 != std::string::npos) {
			if (i1 == str.rfind('/') && i2 == std::string::npos)
				return Rational(std::stoi(str.substr(0, i1)), std::stoi(str.substr(i1 + 1, std::string::npos)));
		}
		else {
			if (i2 != std::string::npos) {
				if (i2 == str.rfind('.')) {
					Rational n = get_num(str.substr(0, i2));
					std::string substr(str.substr(i2 + 1, std::string::npos));
					Rational r = get_num(substr);
					Rational::Type m = (Rational::Type)std::powl(10, substr.size());
					return r / m + n;
				}
			}
			else {
				return get_num(str);
			}
		}
		return Rational(0, 0);
	}
	Rational get_num(const std::string &str)
	{
		if (str.size() > 18)
			return Rational(0, 0);
		else
			return Rational(std::stoll(str));
	}
}
END