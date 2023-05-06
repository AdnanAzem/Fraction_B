#include <iostream>
#include "Fraction.hpp"


namespace ariel
{
    // ===================== Constructors =====================
    // Default Constructor
    Fraction::Fraction() : numerator(0), denominator(1) {}

    // Constructor with 2 integers inputs
    Fraction::Fraction(int num, int den) : numerator(num), denominator(den)
    {
        // throw error if the denominator is 0.
        if (denominator == 0)
        {
            throw std::invalid_argument("Denominator cannot be zero.");
        }
        reduce();
    }

    // Constructor whith float input
    Fraction::Fraction(float n)
    {
        // round the number to 3 digits after the decimal point.
        float round3Digits = setFloatWith3Digits(n);

        // represent the float number without decimal point and cast it to int
        int num = static_cast<int>(round3Digits * 1000);
        int den = 1000;

        // represent it as numerator and denominator
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

    // check overflow between 2 fractions
    bool Fraction::checkFractionOverflow(const Fraction& f1, const Fraction& f2, char op) const{
        // Calculate the result of the arithmetic operation using long longs to avoid overflow
        long long result = 0;
        long long result2 = 0;
        if (op == '+') {
            result = (long long)f1.numerator * f2.denominator + (long long)f2.numerator * f1.denominator;
        }
        else if (op == '-') {
            result = (long long)f1.numerator * f2.denominator - (long long)f2.numerator * f1.denominator;
        }
        else if (op == '*') {
            result = (long long)f1.numerator * f2.numerator ; 
            result2 = (long long)f1.denominator * f2.denominator;
        }
        else if (op == '/') {
            result = (long long)f1.numerator * f2.denominator;
            result2 = (long long)f2.numerator * f1.denominator;
        }

        // Check if the result overflows the integer limits
        if (result > MAX || result < MIN || result2 > MAX || result2 < MIN) { 
            return true; // overflow detected
        }

        // No overflow detected
        return false;
    }


    // return float number whith 3 digits after the point
    float Fraction::setFloatWith3Digits(float num)
    {
        //roundf() - Return The value of x rounded to the nearest integral (as a floating-point value).
        float round = roundf(num * 1000);        // multiply num by 1000 and round the number without decimal point
        float ret = round / 1000;        // return the number into float
        return ret;
    }



    // return the fraction in reduced form
    void Fraction::reduce()
    {
        // if the numerator is 0 then the reduced form is 0/1
        if (numerator == 0)
        {
            denominator = 1;
        }
        else
        {
            // abs() - returns the absolute value (positive value) of an integer number
            int gcd = GCD(abs(numerator), abs(denominator)); // send 2 positive number to find the gcd
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
    // ===================== End Helper Functions =====================

    // ===================== Overloaded Arithmetic Operators =====================

    // Addittion Functions
    Fraction Fraction::operator+(const Fraction &other) const
    {
        // throw error if there is overflow in addition
        if(checkFractionOverflow(*this,other,'+'))
        {
            throw std::overflow_error("Error: Overflow during addition.");
        }
        return Fraction(this->numerator * other.denominator + this->denominator * other.numerator, this->denominator * other.denominator);
    }

    Fraction operator+(const float &number, const Fraction &fraction) 
    {
        // send to function +(fraction, fraction)
        return Fraction(number) + fraction;
    }

    Fraction operator+(const Fraction &fraction, const float &number)
    {
        // send to function +(fraction, fraction)
        return fraction + Fraction(number);
    }

    // Subtraction Functions
    Fraction Fraction::operator-(const Fraction &other) const
    {
        // throw error if there is overflow in subtraction
        if(checkFractionOverflow(*this,other,'-'))
        {
            throw std::overflow_error("Error: Overflow during subtraction.");
        }
        return Fraction(this->numerator * other.denominator - this->denominator * other.numerator, this->denominator * other.denominator);
    }

    Fraction operator-(const float &number, const Fraction &fraction)
    {
        // send to function -(fraction, fraction)
        return Fraction(number) - fraction;
    }

    Fraction operator-(const Fraction &fraction, const float &number)
    {
        // send to function -(fraction, fraction)
        return fraction - Fraction(number);
    }

    // Multiplication Functions
    Fraction Fraction::operator*(const Fraction &other) const
    {
        // throw error if there is overflow in multiplication
        if(checkFractionOverflow(*this,other,'*'))
        {
            throw std::overflow_error("Error: Overflow during multiplication.");
        }
        return Fraction(this->numerator * other.numerator, this->denominator * other.denominator);
    }

    Fraction operator*(const float &number, const Fraction &fraction)
    {
        // send to function *(fraction, fraction)
        return Fraction(number) * fraction;
    }

    Fraction operator*(const Fraction &fraction, const float &number)
    {
        // send to function *(fraction, fraction)
        return fraction * Fraction(number);
    }

    // Division Functions
    Fraction Fraction::operator/(const Fraction &other) const
    {
        // throw error if the numenator of the second fraction is 0
        if (other.numerator == 0)
        {
            throw std::runtime_error("Error: Divided by 0");
        }
        // throw error if there is overflow in division
        if(checkFractionOverflow(*this,other,'/'))
        {
            throw std::overflow_error("Error: Overflow during division.");
        }
        return Fraction(this->numerator * other.denominator, this->denominator * other.numerator);
    }

    Fraction operator/(const float &number, const Fraction &fraction)
    {
        // send to function /(fraction, fraction)
        return Fraction(number) / fraction;
    }

    Fraction operator/(const Fraction &fraction, const float &number)
    {
        // send to function /(fraction, fraction)
        return fraction / Fraction(number);
    }
    // ===================== End Overloaded Arithmetic Operators =====================

    // ===================== Overloaded Compromise Operators =====================

    // Operator ==
    bool Fraction::operator==(const Fraction &other) const
    {
        // check the comprise between 2 fractions
        return this->numerator == other.numerator && this->denominator == other.denominator;
    }

    bool operator==(const Fraction &fraction, const float &number)
    {
        // send to function ==(fraction,fraction)
        return fraction == Fraction(number);
    }

    bool operator==(const float &number, const Fraction &fraction)
    {
        // send to function ==(fraction,float)
        return fraction == number;
    }

    // Operator <
    bool Fraction::operator<(const Fraction &other) const
    {
        // check the comprise between 2 fractions
        return this->numerator * other.denominator < this->denominator * other.numerator ;
    }

    bool operator<(const Fraction &fraction, const float &number)
    {
        // send to function <(fraction,fraction)
        return fraction < Fraction(number);
    }

    bool operator<(const float &number, const Fraction &fraction)
    {
        // send to function <(fraction,float)
        return fraction > number;
    }

    // Operator <=
    bool Fraction::operator<=(const Fraction &other) const
    {
        // check the comprise between 2 fractions
        return this->numerator * other.denominator <= this->denominator * other.numerator;
    }

    bool operator<=(const Fraction &fraction, const float &number)
    {
        // send to function <=(fraction,fraction)
        return fraction <= Fraction(number);
    }

    bool operator<=(const float &number, const Fraction &fraction)
    {
        // send to function <=(fraction,float)
        return fraction >= number;
    }



    // Operator >
    bool Fraction::operator>(const Fraction &other) const
    {
        // check the comprise between 2 fractions
        return this->numerator * other.denominator > this->denominator * other.numerator;
    }

    bool operator>(const Fraction &fraction, const float &number)
    {
        // send to function >(fraction,fraction)
        return fraction > Fraction(number);
    }

    bool operator>(const float &number, const Fraction &fraction)
    {
        // send to function >(fraction,float)
        return fraction < number;
    }

    //Operator >=
    bool Fraction::operator>=(const Fraction &other) const
    {
        // check the comprise between 2 fractions
        return this->numerator * other.denominator >= this->denominator * other.numerator ;
    }

    bool operator>=(const Fraction &fraction, const float &number)
    {
        // send to function >=(fraction,fraction)
        return fraction >= Fraction(number);
    }

    bool operator>=(const float &number, const Fraction &fraction)
    {
        // send to function >=(fraction,float)
        return fraction <= number;
    }
    // ===================== End Overloaded Compromise Operators =====================

    // ===================== Increasment & Decreasment =====================
    // Prefix Increasment
    Fraction &Fraction::operator++()
    {
        numerator += denominator;
        return *this;
    }

    // Postfix Increasment
    Fraction Fraction::operator++(int)
    {
        Fraction temp(*this);
        numerator += denominator;
        return temp;
    }

    // Prefix Decreasment
    Fraction &Fraction::operator--()
    {
        numerator -= denominator;
        return *this;
    }

    // Postfix Decreasment
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
        //fail() - Returns true if either (or both) the failbit or the badbit error state flags is set for the stream.
        //peek() - Returns the next character in the input sequence, without extracting it: The character is left as the next character to be extracted from the stream.
        if (input.fail() || input.peek() == EOF) // if there is no input
        {
            //setstate() - Modifies the current internal error state flags by combining the current flags with those in argument state
            //failbit - The last input operation failed because of an error related to the internal logic of the operation itself.
            input.setstate(std::ios_base::failbit);
        }
        input >> num;
        if (input.peek() == EOF) // if there is one input throw error
        {
            throw runtime_error("Error: There is one number");
        }
        input >> den;
        if (den == 0) // if the denominator in input is 0
        {
            throw runtime_error("Error: Denominator can't be 0");
        }
        fraction = Fraction(num, den);
        return input;
    }
    // ===================== End Overload Input & output =====================

}
