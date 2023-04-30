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

        this->numerator = num;
        this->denominator = den;
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

    // return float number whith 3 digits after the point
    float Fraction::set3DigitsBeyondThePoint(float num)
    {
        float round = roundf(num * 1000);        // multiply num by 1000 and round the number without decimal point
        float ret = round / 1000;        // return the number into float
        return ret;
    }

    // return float number whith 3 digits after the point
    float set3DigitsAfterThePoint(float num)
    {
        float round = roundf(num * 1000);        // multiply num by 1000 and round the number without decimal point
        float ret = round / 1000;        // return the number into float
        return ret;
    }

    // return the fraction in reduced form
    void Fraction::reduce()
    {
        if (numerator == 0)
        {
            denominator = 1;
        }
        else
        {
            int gcd = GCD(abs(numerator), abs(denominator)); // find the gcd
            numerator /= gcd;
            denominator /= gcd;
            if (denominator < 0)
            {
                numerator = -numerator;
                denominator = -denominator;
            }
        }
    }

    // return the gcd between 2 numbers
    int Fraction::GCD(int a, int b) const
    {
        if (b == 0)
        {
            return a;
        }
        return GCD(b, a % b);
    }

    // return true if there is overflow and return false else
    bool checkOverflow(const Fraction &frac1, const Fraction &frac2, char op){
        switch (op) {
            case '+':
                return ((frac1.numerator == std::numeric_limits<int>::max() && frac1.denominator != std::numeric_limits<int>::max()) 
                        || (frac2.denominator == std::numeric_limits<int>::max() && frac2.denominator != std::numeric_limits<int>::max()) 
                        || (frac1.numerator <= std::numeric_limits<int>::min() + 100) && (frac2.numerator <= std::numeric_limits<int>::min() + 100));

            case '-':
                return ((frac1.numerator <= std::numeric_limits<int>::min() + 100 && frac2.numerator <= std::numeric_limits<int>::min() + 100) 
                        || (frac1.numerator >= std::numeric_limits<int>::max() - 100 && frac2.numerator <= std::numeric_limits<int>::min() + 100));

            case '*':
                return ((frac1.numerator == std::numeric_limits<int>::max() && frac1.denominator != std::numeric_limits<int>::max()) 
                        || (frac1.denominator == std::numeric_limits<int>::max() && frac1.numerator != std::numeric_limits<int>::max()) 
                        || (frac2.numerator == std::numeric_limits<int>::max() && frac2.denominator != std::numeric_limits<int>::max()) 
                        || (frac2.denominator == std::numeric_limits<int>::max() && frac2.denominator != std::numeric_limits<int>::max()));

            case '/':
                return ((frac1.numerator == std::numeric_limits<int>::max() && frac1.denominator != std::numeric_limits<int>::max()) 
                        || (frac1.denominator == std::numeric_limits<int>::max() && frac1.numerator < std::numeric_limits<int>::max() - 100));

            default:
                return false;
        }
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
        if (checkOverflow(*this,other,'+'))
        {
            throw std::overflow_error("Error: Overflow during addition.");
        }
        return Fraction(this->numerator * other.denominator + this->denominator * other.numerator, this->denominator * other.denominator);
    }

    Fraction operator+(const float &number, const Fraction &fraction)
    {
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float temp = set3DigitsAfterThePoint(num);
        float ans = temp + number;
        return Fraction(ans);
    }

    Fraction operator+(const Fraction &fraction, const float &number)
    {
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float temp = set3DigitsAfterThePoint(num);
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
        if (checkOverflow(*this,other,'-'))
        {
            throw std::overflow_error("Error: Overflow during subtraction.");
        }
        return Fraction(this->numerator * other.denominator - this->denominator * other.numerator, this->denominator * other.denominator);
    }

    Fraction operator-(const float &number, const Fraction &fraction)
    {
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float temp = set3DigitsAfterThePoint(num);
        float ans = number - temp;
        return Fraction(ans);
    }

    Fraction operator-(const Fraction &fraction, const float &number)
    {
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float temp = set3DigitsAfterThePoint(num);
        float ans = temp - number;
        return Fraction(ans);
    }

    // Multiplication Functions
    Fraction Fraction::operator*(const Fraction &other) const
    {
        if (other.denominator == 0 || this->denominator == 0)
        {
            throw std::runtime_error("Dennominator is 0");
        }
        if (checkOverflow(*this,other,'*'))
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
            throw std::runtime_error("Error: Dennominator is 0");
        }
        if (checkOverflow(*this,other,'/'))
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

    // Operator ==
    bool Fraction::operator==(const Fraction &other) const
    {
        // check in fraction form or float form
        float f1 = set3DigitsAfterThePoint((float)this->numerator/(float)this->denominator);
        float f2 = set3DigitsAfterThePoint((float)other.numerator/(float)other.denominator);
        return this->numerator == other.numerator && this->denominator == other.denominator || f1 == f2;
    }

    bool operator==(const Fraction &fraction, const float &number)
    {
        // check in fraction form or float form
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float res = set3DigitsAfterThePoint(num);
        Fraction other(number);
        return fraction == other || res == number;
    }

    bool operator==(const float &number, const Fraction &fraction)
    {
        // check in fraction form or float form
        float num = (float)fraction.numerator / (float)fraction.denominator;
        float res = set3DigitsAfterThePoint(num);
        Fraction other(number);
        return fraction == other || number == res;
    }

    // Operator <
    bool Fraction::operator<(const Fraction &other) const
    {
        // check in fraction form or float form
        float f1 = set3DigitsAfterThePoint((float)this->numerator/(float)this->denominator);
        float f2 = set3DigitsAfterThePoint((float)other.numerator/(float)other.denominator);
        return this->numerator * other.denominator < this->denominator * other.numerator || f1 < f2;
    }

    bool operator<(const Fraction &fraction, const float &number)
    {
        // check in fraction form or float form
        Fraction other(number);
        return (float)fraction.numerator / (float)fraction.denominator < number || fraction < other;
    }

    bool operator<(const float &number, const Fraction &fraction)
    {
        // check in fraction form or float form
        Fraction other(number);
        return number < (float)fraction.numerator / (float)fraction.denominator || other < fraction;
    }

    // Operator <=
    bool Fraction::operator<=(const Fraction &other) const
    {
        // check in fraction form or float form
        float f1 = set3DigitsAfterThePoint((float)this->numerator/(float)this->denominator);
        float f2 = set3DigitsAfterThePoint((float)other.numerator/(float)other.denominator);
        return this->numerator * other.denominator <= this->denominator * other.numerator || f1 <= f2;
    }

    bool operator<=(const Fraction &fraction, const float &number)
    {
        // check in fraction form or float form
        Fraction other(number);
        return (float)fraction.numerator / (float)fraction.denominator <= number || fraction <= other;
    }

    bool operator<=(const float &number, const Fraction &fraction)
    {
        // check in fraction form or float form
        Fraction other(number);
        return number <= (float)fraction.numerator / (float)fraction.denominator || other <= fraction;
    }



    // Operator >
    bool Fraction::operator>(const Fraction &other) const
    {
        // check in fraction form or float form
        float f1 = set3DigitsAfterThePoint((float)this->numerator/(float)this->denominator);
        float f2 = set3DigitsAfterThePoint((float)other.numerator/(float)other.denominator);
        return this->numerator * other.denominator > this->denominator * other.numerator || f1 > f2;
    }

    bool operator>(const Fraction &fraction, const float &number)
    {
        // check in fraction form or float form
        float res = (float)fraction.numerator / (float)fraction.denominator;
        Fraction other(number);
        return fraction > other || res > number;
    }

    bool operator>(const float &number, const Fraction &fraction)
    {
        // check in fraction form or float form
        Fraction other(number);
        return number > (float)fraction.numerator / (float)fraction.denominator || other > fraction;
    }

    //Operator >=
    bool Fraction::operator>=(const Fraction &other) const
    {
        // check in fraction form or float form
        float f1 = set3DigitsAfterThePoint((float)this->numerator/(float)this->denominator);
        float f2 = set3DigitsAfterThePoint((float)other.numerator/(float)other.denominator);
        return this->numerator * other.denominator >= this->denominator * other.numerator || f1 >= f2;
    }

    bool operator>=(const Fraction &fraction, const float &number)
    {
        // check in fraction form or float form
        Fraction other(number);
        return (float)fraction.numerator / (float)fraction.denominator >= number || fraction >= other;
    }

    bool operator>=(const float &number, const Fraction &fraction)
    {
        // check in fraction form or float form
        Fraction other(number);
        return number >= (float)fraction.numerator / (float)fraction.denominator || other >= fraction;
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
    ostream &operator<<(ostream &output, const Fraction &fraction)
    {
        output << fraction.numerator << "/" << fraction.denominator;
        return output;
    }

    istream &operator>>(istream &input, Fraction &fraction)
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
        fraction = Fraction(num, den);
        return input;
    }
    // ===================== End Overload Input & output =====================

}
