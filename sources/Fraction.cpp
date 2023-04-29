#include <iostream>
#include "Fraction.hpp"

namespace ariel
{
    // ===================== Constructors =====================
    Fraction::Fraction() : numerator(0), denominator(1) {}
    Fraction::Fraction(int num, int den) : numerator(num), denominator(den)
    {
        if (denominator == 0)
        {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    Fraction::Fraction(float n)
    {
        // round num to 3 digits beyond the decimal point for accuarcy
        float round3Digits = set3DigitsBeyondThePoint(n);

        // represent the float without decimal point and cast it to int,
        //  then represent it as numerator and denominator
        int num = static_cast<int>(round3Digits * 1000);
        int den = 1000;

        // set the data members
        this->numerator = num;
        this->denominator = den;

        // reduce the fraction
        reduce();
    }
    // ===================== End Constructors =====================

    // ===================== Setters =====================
    void Fraction::setNumerator(int num)
    {
        numerator = num;
    }

    void Fraction::setDenominator(int den)
    {
        denominator = den;
    }
    // ===================== End Setters =====================

    // ===================== Getters =====================
    int Fraction::getNumerator()
    {
        return this->numerator;
    }

    int Fraction::getDenominator()
    {
        return this->denominator;
    }
    // ===================== End Getters =====================

    // ===================== Helper Functions =====================
    float Fraction::set3DigitsBeyondThePoint(float num)
    {
        // multiply num by 1000 and round the
        // number without decimal point
        float round = roundf(num * 1000);

        // return the number into float
        float ret = round / 1000;

        return ret;
    }

    float set3DigitsBeyondThePoints(float num)
    {
        // multiply num by 1000 and round the
        // number without decimal point
        float round = roundf(num * 1000);

        // return the number into float
        float ret = round / 1000;

        return ret;
    }
    void Fraction::reduce()
    {
        if (numerator == 0)
        {
            denominator = 1;
        }
        else
        {
            int gcd = GCD(abs(numerator), abs(denominator));
            numerator /= gcd;
            denominator /= gcd;
            if (denominator < 0)
            {
                numerator = -numerator;
                denominator = -denominator;
            }
        }
    }

    int Fraction::GCD(int a, int b) const
    {
        if (b == 0)
        {
            return a;
        }
        return GCD(b, a % b);
    }
    // ===================== End Helper Functions =====================

    // ===================== Overloaded Arithmetic Operators =====================

    // Addittion Functions
    Fraction Fraction::operator+(const Fraction &other) const
    {
        if (other.denominator == 0 || this->denominator == 0)
        {
            throw std::runtime_error("Dennominator is 0");
        }
        if ((this->numerator == std::numeric_limits<int>::max() && this->denominator != std::numeric_limits<int>::max()) 
            || (other.denominator == std::numeric_limits<int>::max() && other.denominator != std::numeric_limits<int>::max()) 
            || (this->numerator <= std::numeric_limits<int>::min() + 100) && (other.numerator <= std::numeric_limits<int>::min() + 100))
        {
            throw std::overflow_error("Error: Overflow during addition.");
        }
        return Fraction(this->numerator * other.denominator + this->denominator * other.numerator, this->denominator * other.denominator);
    }

    Fraction operator+(const float &number, const Fraction &fraction)
    {
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float temp = set3DigitsBeyondThePoints(num);
        float ans = temp + number;
        return Fraction(ans);
    }

    Fraction operator+(const Fraction &fraction, const float &number)
    {
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float temp = set3DigitsBeyondThePoints(num);
        float ans = temp + number;
        return Fraction(ans);
    }

    // Subtraction Functions
    Fraction Fraction::operator-(const Fraction &other) const
    {
        if (other.denominator == 0 || this->denominator == 0)
        {
            throw std::runtime_error("Dennominator is 0");
        }
        if ((this->numerator <= std::numeric_limits<int>::min() + 100 && other.numerator <= std::numeric_limits<int>::min() + 100) 
        || (this->numerator >= std::numeric_limits<int>::max() - 100 && other.numerator <= std::numeric_limits<int>::min() + 100))
        {
            throw std::overflow_error("Error: Overflow during subtraction.");
        }
        return Fraction(this->numerator * other.denominator - this->denominator * other.numerator, this->denominator * other.denominator);
    }

    Fraction operator-(const float &number, const Fraction &fraction)
    {
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float temp = set3DigitsBeyondThePoints(num);
        float ans = number - temp;
        return Fraction(ans);
    }

    Fraction operator-(const Fraction &fraction, const float &number)
    {
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float temp = set3DigitsBeyondThePoints(num);
        float ans = temp - number;
        return Fraction(ans);
        // Fraction ot(n);
        // return f - ot;
    }

    // Multiplication Functions
    Fraction Fraction::operator*(const Fraction &other) const
    {
        if (other.denominator == 0 || this->denominator == 0)
        {
            throw std::runtime_error("Dennominator is 0");
        }
        if ((this->numerator == std::numeric_limits<int>::max() && this->denominator != std::numeric_limits<int>::max()) 
            || (this->denominator == std::numeric_limits<int>::max() && this->numerator != std::numeric_limits<int>::max()) 
            || (other.numerator == std::numeric_limits<int>::max() && other.denominator != std::numeric_limits<int>::max()) 
            || (other.denominator == std::numeric_limits<int>::max() && other.denominator != std::numeric_limits<int>::max()))
        {
            throw std::overflow_error("Error: Overflow during multiplication.");
        }
        return Fraction(this->numerator * other.numerator, this->denominator * other.denominator);
    }

    Fraction operator*(const float &number, const Fraction &fraction)
    {
        Fraction temp(number);
        return temp * fraction;
    }

    Fraction operator*(const Fraction &fraction, const float &number)
    {
        Fraction temp(number);
        return fraction * temp;
    }


    // Division Functions
    Fraction Fraction::operator/(const Fraction &other) const
    {
        if (other.denominator == 0 || this->denominator == 0 || other.numerator == 0)
        {
            throw std::runtime_error("Dennominator is 0");
        }
        if ((this->numerator == std::numeric_limits<int>::max() && this->denominator != std::numeric_limits<int>::max()) 
        || (this->denominator == std::numeric_limits<int>::max() && this->numerator < std::numeric_limits<int>::max() - 100))
        {
            throw std::overflow_error("Error: Overflow during division.");
        }
        return Fraction(this->numerator * other.denominator, this->denominator * other.numerator);
    }

    Fraction operator/(const float &number, const Fraction &fraction)
    {
        Fraction temp(number);
        return temp / fraction;
    }

    Fraction operator/(const Fraction &fraction, const float &number)
    {
        Fraction temp(number);
        return fraction / temp;
    }
    // ===================== End Overloaded Arithmetic Operators =====================

    // ===================== Overloaded Compromise Operators =====================
    bool Fraction::operator==(const Fraction &other) const
    {
        // check by 2 fractions or by 2 floats
        float f1 = set3DigitsBeyondThePoints((float)this->numerator/(float)this->denominator);
        float f2 = set3DigitsBeyondThePoints((float)other.numerator/(float)other.denominator);
        return this->numerator == other.numerator && this->denominator == other.denominator || f1 == f2;
    }

    bool Fraction::operator<(const Fraction &other) const
    {
        return this->numerator * other.denominator < this->denominator * other.numerator;
    }

    bool Fraction::operator<=(const Fraction &other) const
    {
        return this->numerator * other.denominator <= this->denominator * other.numerator;
    }

    bool Fraction::operator>(const Fraction &other) const
    {
        return this->numerator * other.denominator > this->denominator * other.numerator;
    }

    bool Fraction::operator>=(const Fraction &other) const
    {
        return this->numerator * other.denominator >= this->denominator * other.numerator;
    }

    bool operator==(const Fraction &ot, const float &n)
    {
        float num = (float)ot.numerator / (float)ot.denominator;
        float res = set3DigitsBeyondThePoints(num);
        Fraction f(n);
        return ot == f || res == n;
    }

    bool operator>=(const Fraction &ot, const float &n)
    {
        return (float)ot.numerator / (float)ot.denominator >= n;
        // Fraction f(n);
        // return ot>= f;
    }

    bool operator>(const Fraction &ot, const float &n)
    {
        float res = (float)ot.numerator / (float)ot.denominator;
        Fraction f(n);
        return ot > f || res > n;
    }

    bool operator<=(const Fraction &ot, const float &n)
    {
        return (float)ot.numerator / (float)ot.denominator <= n;
        // Fraction f(n);
        // return ot <= f;
    }

    bool operator<(const Fraction &ot, const float &n)
    {
        return (float)ot.numerator / (float)ot.denominator < n;
        // Fraction f(n);
        // return ot < f;
    }

    bool operator==(const float &n, const Fraction &f)
    {
        float num = (float)f.numerator / (float)f.denominator;
        float res = set3DigitsBeyondThePoints(num);
        // float res = (float)f.numerator/(float)f.denominator;
        Fraction ot(n);
        return f == ot || n == res;
    }

    bool operator<(const float &n, const Fraction &f)
    {
        return n < (float)f.numerator / (float)f.denominator;
        // Fraction ot(n);
        // return f > ot;
    }

    bool operator<=(const float &n, const Fraction &f)
    {
        return n <= (float)f.numerator / (float)f.denominator;
        // Fraction ot(n);
        // return f >= ot;
    }

    bool operator>(const float &n, const Fraction &f)
    {
        return n > (float)f.numerator / (float)f.denominator;
        // Fraction ot(n);
        // return f < ot;
    }

    bool operator>=(const float &n, const Fraction &f)
    {
        return n >= (float)f.numerator / (float)f.denominator;
        // Fraction ot(n);
        // return f <= ot;
    }
    // ===================== End Overloaded Compromise Operators =====================

    // ===================== Increasment & Decreasment =====================
    Fraction &Fraction::operator++()
    {
        numerator += denominator;
        return *this;
    }

    Fraction Fraction::operator++(int)
    {
        Fraction temp(*this);
        numerator += denominator;
        return temp;
    }

    Fraction &Fraction::operator--()
    {
        numerator -= denominator;
        return *this;
    }

    Fraction Fraction::operator--(int)
    {
        Fraction temp(*this);
        numerator -= denominator;
        return temp;
    }
    // ===================== End Increasment & Decreasment =====================

    // ===================== Overload Input & output =====================
    ostream &operator<<(ostream &output, const Fraction &f)
    {
        output << f.numerator << "/" << f.denominator;
        return output;
    }

    istream &operator>>(istream &input, Fraction &f)
    {
        int num, den;
        if (input.fail() || input.peek() == EOF)
        {
            input.setstate(std::ios_base::failbit);
        }
        input >> num;
        if (input.peek() == EOF)
        {
            throw runtime_error("Error: There is one number");
        }
        input >> den;
        if (den == 0)
        {
            throw runtime_error("Error: Denominator can't be 0");
        }
        f = Fraction(num, den);
        return input;
    }
    // ===================== End Overload Input & output =====================

}
