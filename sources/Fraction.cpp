#include <iostream>
#include "Fraction.hpp"

namespace ariel
{
    // const
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
        // numerator = round(num * 1000);
        // denominator = 1000;
        // reduce();
    }

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
    // setters
    void Fraction::setNumerator(int num)
    {
        numerator = num;
    }

    void Fraction::setDenominator(int den)
    {
        denominator = den;
    }

    // getters
    int Fraction::getNumerator()
    {
        return this->numerator;
    }

    int Fraction::getDenominator()
    {
        return this->denominator;
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
                numerator *= -1;
                denominator *= -1;
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

    void Fraction::convertFloatToFraction(float n)
    {
        int num = int(n * 1000);
        int den = 1000;
        this->numerator = num;
        this->denominator = den;
    }

    float Fraction::convertFractionToFloat() const
    {
        int num = this->numerator;
        int den = this->denominator;
        float res = (float)num / (float)den;
        return res;
    }

    // Overloaded operators
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

    Fraction operator+(const float &n, const Fraction &f)
    {
        float num = (float)f.numerator / (float)f.denominator;
        float res = set3DigitsBeyondThePoints(num);
        float ans = res + n;
        return Fraction(ans);
        // Fraction ot(n);
        // return ot + f;
    }
    Fraction operator-(const float &n, const Fraction &f)
    {
        float num = (float)f.numerator / (float)f.denominator;
        float res = set3DigitsBeyondThePoints(num);
        float ans = n - res;
        return Fraction(ans);
        // Fraction ot(n);
        // return ot - f;
    }
    Fraction operator*(const float &n, const Fraction &f)
    {
        Fraction ot(n);
        return ot * f;
    }
    Fraction operator/(const float &n, const Fraction &f)
    {
        Fraction ot(n);
        return ot / f;
    }

    Fraction operator+(const Fraction &f, const float &n)
    {
        float num = (float)f.numerator / (float)f.denominator;
        float res = set3DigitsBeyondThePoints(num);
        float ans = res + n;
        return Fraction(ans);
        // Fraction ot(n);
        // return f + ot;
    }

    Fraction operator-(const Fraction &f, const float &n)
    {
        Fraction ot(n);
        return f - ot;
    }

    Fraction operator*(const Fraction &f, const float &n)
    {
        Fraction ot(n);
        return f * ot;
    }

    Fraction operator/(const Fraction &f, const float &n)
    {
        Fraction ot(n);
        return f / ot;
    }

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

}

// #include "Fraction.hpp"
// #include <sstream>
// #include <vector>
// #include <stdexcept>
// #include <string>
// #include <cstdlib>
// #include <climits>

// /*

// */

// namespace ariel{

//     // ======================= Constructors =======================

//     Fraction::Fraction(): numerator(0), denominator(1){}

//     Fraction::Fraction(int num1, int num2): numerator(num1), denominator(num2){
//         if(this->denominator == 0 ){
//             // throw ("Error: Divide by 0");
//             throw std::invalid_argument("Error: Denominator is 0");
//         }
//         if(this->denominator < 0){
//             this->numerator = -this->numerator;
//             this->denominator = -this->denominator;
//         }
//         reduce();
//     }

//     Fraction::Fraction(float num) {
//         float res = convert3Digit(num);
//         this->convertFloatToFraction(res);
//     }

//     // ======================= Setters =======================

//     void Fraction::setNumerator(int num){
//         this->numerator = num;
//     }

//     void Fraction::setDenominator(int num){
//         this->denominator = num;
//     }

//     // ======================= Getters =======================

//     int Fraction::getNumerator(){
//         return this->numerator;
//     }

//     int Fraction::getDenominator(){
//         return this->denominator;
//     }

//     // ======================= Helper Functions =======================

//     // bool Fraction::isOverflow(const Fraction& fraction) {
//     //     // Check for overflow when multiplying numerator by any integer value
//     //     if (fraction.numerator != 0 && isOverflow((fraction.numerator, 1))) {
//     //         return true;
//     //     }
//     //     // Check for overflow when multiplying denominator by any integer value
//     //     if (fraction.denominator != 0 && isOverflow((fraction.denominator, 1))) {
//     //         return true;
//     //     }
//     //     return false;
//     // }

//     bool isOverflow(int num1, int num2, char op) {
//         switch (op) {
//             case '+':
//                 return (num2 > 0 && num1 > INT_MAX - num2) || (num2 < 0 && num1 < INT_MIN - num2);
//             case '-':
//                 return (num2 > 0 && num1 < INT_MIN + num2) || (num2 < 0 && num1 > INT_MAX + num2);
//             case '*':
//                 return (num2 > 0 && num1 > INT_MAX / num2) || (num2 < 0 && num1 < INT_MIN / num2) ||
//                        (num1 > 0 && num2 > INT_MAX / num1) || (num1 < 0 && num2 < INT_MIN / num1);
//             case '/':
//                 return num2 == 0 || (num2 == -1 && num1 == INT_MIN);
//             default:
//                 return false;
//         }
//     }



//     // bool Fraction::checkOverflow(const Fraction& f) {
//     //     if (f.denominator == 0) {
//     //         // Undefined value
//     //         return false;
//     //     }
//     //     if ((f.numerator > 0 && f.denominator > 0) || (f.numerator < 0 && f.denominator < 0)) {
//     //         if (abs(f.numerator) > numeric_limits<int>::max() / abs(f.denominator)) {
//     //             return true;
//     //         }
//     //     } 
//     //     // No overflow
//     //     return false;
//     // }



//     bool Fraction::checkOverflowAndUnderflow(const Fraction& f)const {
//         if (f.denominator == 0) {
//             // Undefined value
//             return false;
//         }
//         if ((f.numerator > 0 && f.denominator > 0) || (f.numerator < 0 && f.denominator < 0)) {
//             // Positive value
//             if (abs(f.numerator) > numeric_limits<int>::max()) {
//                 return true;
//             }
//             if (abs(f.denominator) > numeric_limits<int>::max()) {
//                 return true;
//             }
//         } else {
//             // Negative value
//             if (abs(f.numerator) > numeric_limits<int>::max()) {
//                 return true;
//             }
//             if (abs(f.denominator) > numeric_limits<int>::max()) {
//                 return true;
//             }
//         }
//         // No overflow or underflow
//         return false;
//     }
    
//     bool Fraction::isOverflow(const Fraction& f) const {
//         // Check for overflow when multiplying numerator by any integer value
//         if (abs(f.numerator) != 0 && abs(f.numerator) / abs(f.denominator)> INT_MAX ) {
//             return true;
//         }
//         // Check for overflow when multiplying denominator by any integer value
//         if (abs(f.denominator) != 0 && abs(f.denominator) / abs(f.numerator)> INT_MAX ) {
//             return true;
//         }
//         return false;
//     }
//     // bool Fraction::isOverflow() {
//     //     // Check for overflow when multiplying numerator by any integer value
//     //     if (this->numerator != 0 && this->numerator > INT_MAX / this->denominator) {
//     //         return true;
//     //     }
//     //     // Check for overflow when multiplying denominator by any integer value
//     //     if (this->denominator != 0 && this->denominator > INT_MAX / this->numerator) {
//     //         return true;
//     //     }
//     //     return false;
//     // }

//     string Fraction::toString(){
//         std::stringstream output;
//         output << this->getNumerator() << "/" << this->getDenominator();
//         return output.str();
//     }

//     int Fraction::GCD(){ // find the gcd between the numerator & the denominator
//         int gcd = 1;
//         for(int i = 1; i <= this->numerator || i <= this->denominator; i++) {
//             if(this->numerator % i == 0 && this->denominator % i == 0)
//             gcd = i;
//         }
//         return gcd;
//     }

//     int Fraction::Gcd(int num1, int num2) const {
//         if (num2 == 0) {
//             return num1;
//         }
//         return Gcd(num2, num1 % num2);
//     }

        
//     void Fraction::reduce(){ // to reduce the fraction to his reduced form
//     int gcd = Gcd(abs(this->numerator),abs(this->denominator));
//         // int gcd = this->GCD();
//         this->numerator = this->numerator / gcd;
//         this->denominator = this->denominator / gcd; 
//     }

//     // Count pre-decimal points, multiply the float number with 10 to move the floating point and also the denominator
//     // void Fraction::convertFloatToFraction(float num){ // convert from float to fraction
//     //     this->denominator = 1;

//     //     while(((float)(int)num) != num) {
//     //         num = num * 10;
//     //         this->denominator = this->denominator * 10;
//     //     }
//     //     this->numerator = (int)num;
//     //     this->reduce();
//     // }

//     float Fraction::convert3Digit(float num){
//         float round = roundf( num * 1000 );
//         // return the number into float
//         float ret = round / 1000;
//         return ret;
//     }

//     void Fraction::convertFloatToFraction(float num){
//         this->denominator = 1000;
//         this->numerator = (int)roundf(num * 1000);
//         reduce();
//     }

    

// 	float Fraction::convertFractionToFloat()const{ // convert from fraction to float
//         return (float)this->numerator / (float)this->denominator;
//     }

//     // ======================= Operators =======================

//     Fraction Fraction::operator+(const float& value) const {
//         return *this + Fraction(value);
//     }

//     Fraction Fraction::operator-(const float& value) const {
//         return *this - Fraction(value);
//     }

//     Fraction Fraction::operator*(const float& value) const {
//         return *this * Fraction(value);
//     }

//     Fraction Fraction::operator/(const float& value) const {
//         return *this / Fraction(value);
//     }


//     Fraction Fraction::operator+(const Fraction &other)const{ // Fraction + Fraction
//         if(this->denominator == 0 || other.denominator == 0){
//             throw ("Error: Divide by 0");
//         }
//         else{
//             Fraction result;
//             int num,den;
//             num = this->numerator * other.denominator + this->denominator * other.numerator;
//             den = this->denominator * other.denominator;
//             // if (isOverflow(this->numerator, other.denominator, '+') || isOverflow(other.numerator, this->denominator, '+') || isOverflow(num, den, '/')) {
//             //     throw std::overflow_error("Error: Overflow during addition.");
//             // }
//             result = Fraction(num, den);
//             if(isOverflow(result)/*checkOverflowAndUnderflow(result)*/){
//                 throw std::overflow_error("Error: Overflow during addition.");
//             }
//             result.reduce();
//             return result;
//         }
//     }

//     Fraction Fraction::operator-(const Fraction &other) const{ // Fraction - Fraction
//         if(this->denominator == 0 || other.denominator == 0){
//             throw ("Error: Divide by 0");
//         }
//         else{
//             Fraction result;
//             int num,den;
//             num = this->numerator * other.denominator - this->denominator * other.numerator;
//             den = this->denominator * other.denominator;
//             // if (isOverflow(this->numerator, other.denominator, '-') || isOverflow(other.numerator, this->denominator, '-') || isOverflow(num, den, '/')) {
//             //     throw std::overflow_error("Error: Overflow during subtraction.");
//             // }
//             result = Fraction(num, den);
//             if(checkOverflowAndUnderflow(result)){
//                 throw std::overflow_error("Error: Overflow during subtraction.");
//             }
//             result.reduce();
//             return result;  
//         }
//     }

//     Fraction Fraction::operator*(const Fraction &other)const{ // Fraction * Fraction
//         if(this->denominator == 0 || other.denominator == 0){
//             throw ("Error: Divide by 0");
//         }
//         else{
//             Fraction result;
//             int num,den;
//             num = this->numerator * other.numerator;
//             den = this->denominator * other.denominator;
//             // if (isOverflow(this->numerator, other.numerator, '*') || isOverflow(this->denominator, other.denominator, '*') || isOverflow(num, den, '/')) {
//             //     throw std::overflow_error("Error: Overflow during multiplication.");
//             // }
//             result = Fraction(num, den);
//             if(checkOverflowAndUnderflow(result)){
//                 throw std::overflow_error("Error: Overflow during multiplication.");
//             }
//             result.reduce();
//             return result;
//         }
//     }

//     Fraction Fraction::operator/(const Fraction &other)const{ // Fraction / Fraction
//         if(this->denominator == 0 || other.denominator == 0 || other.numerator == 0){
//             // throw ("Error: Divide by 0");
//             throw std::runtime_error("Error: Divide by 0");
//         }
//         else{
//             Fraction result;
//             int num,den;
//             num = this->numerator * other.denominator;
//             den = this->denominator * other.numerator;
//             // if (isOverflow(this->numerator, other.denominator, '*') || isOverflow(this->denominator, other.numerator, '*') ||isOverflow(num, den, '/')) {
//             //     throw std::overflow_error("Error: Overflow during division.");
//             // }
//             result = Fraction(num,den);
//             if(checkOverflowAndUnderflow(result)){
//                 throw std::overflow_error("Error: Overflow during division.");
//             }
//             result.reduce();
//             return result;
//         }
//     }

//     Fraction operator+(float num,const Fraction & fraction){
//         Fraction other(num);
//         // other.convertFloatToFraction(num);
//         Fraction result(other + fraction);
//         return result;
//         // return other + fraction;

//     }

//     Fraction operator-(float num,const Fraction & fraction){
//         Fraction other(num);
//         // other.convertFloatToFraction(num);
//         Fraction result(other - fraction);
//         return result;
//         // return other - fraction;

//     }

//     Fraction operator*(float num,const Fraction & fraction){
//         Fraction other(num);
//         Fraction result(other * fraction);
//         return result;
//         // other.convertFloatToFraction(num);
//         // return other * fraction;

//     }

//     Fraction operator/(float num,const Fraction & fraction){
//         Fraction other(num);
//         // other.convertFloatToFraction(num);
//         Fraction result(other / fraction);
//         return result;
//         // return other / fraction;
//     }



//     // ======================= Equalations =======================

//     bool Fraction::operator==(const Fraction&fraction)const{
//         return (this->numerator * fraction.denominator) == (fraction.numerator * this->denominator);
//     }

//     bool Fraction::operator>(const Fraction &fraction)const{
//         return (this->numerator * fraction.denominator) > (fraction.numerator * this->denominator);
//     }

//     bool Fraction::operator>=(const Fraction &fraction)const{
//         return (this->numerator * fraction.denominator) >= (fraction.numerator * this->denominator);
//     }

//     bool Fraction::operator<(const Fraction &fraction)const{
//         return (this->numerator * fraction.denominator) < (fraction.numerator * this->denominator);
//     }

//     bool Fraction::operator<=(const Fraction &fraction)const{
//         return (this->numerator * fraction.denominator) <= (fraction.numerator * this->denominator);
//     }

//     bool operator==(const float& num,const Fraction &fraction){
//         return fraction == num;
//         // Fraction other;
//         // other.convertFloatToFraction(num);
//         // return other == fraction;  
//     }

//     bool operator<(const float& num,const Fraction &fraction){
//         // return fraction > num;
//         // return fraction.numerator < num * fraction.denominator;
//         // return num < fraction;
//         Fraction other(num);
//         // other.convertFloatToFraction(num);
//         return other < fraction;    
//     }

//     bool operator<=(const float& num,const Fraction &fraction){
//         // return fraction >= num;
//         // return fraction.numerator <= num * fraction.denominator;
//         // return num <= fraction;
//         Fraction other(num);
//         // other.convertFloatToFraction(num);
//         return other <= fraction;  
//     }

//     bool operator>(const float& num,const Fraction &fraction){
//         // return fraction < num;
//         // return fraction.numerator > num * fraction.denominator;
//         // return num > fraction;
//         Fraction other(num);
//         // other.convertFloatToFraction(num);
//         return other > fraction;   
//     }

//     bool operator>=(const float& num,const Fraction &fraction){
//         // return fraction <= num;
//         // return fraction.numerator >= num * fraction.denominator;
//         // return num >= fraction;
//         Fraction other(num);
//         // other.convertFloatToFraction(num);
//         return other >= fraction;  
//     }

//     bool Fraction::operator==(const float& num) const{
//         return numerator == num * denominator;
//     }

//     bool Fraction::operator>(const float& num) const{
//         return numerator > num * denominator;
//     }

//     bool Fraction::operator>=(const float& num) const{
//         return numerator >= num * denominator;
//     }

//     bool Fraction::operator<(const float& num) const{
//         return numerator < num * denominator;
//     }

//     bool Fraction::operator<=(const float& num) const{
//         return numerator <= num * denominator;
//     }

//     // ======================= Increasement & Decreasment =======================

//     Fraction& Fraction::operator++(){ // pre-Increasement
//         if(this->denominator == 0 ){
//             throw ("Error: Divide by 0");
//         }
//         else{
//             this->numerator += this->denominator;
//             return *this;
//         }
//     }
    
//     Fraction Fraction::operator++(int num){ // post-Increasement
//         if(this->denominator == 0 ){
//             throw ("Error: Divide by 0");
//         }
//         else{
//             Fraction temp(*this);
//             ++*this;     // call the prefix operator
//             return temp;
//         }
//     }

//     Fraction& Fraction::operator--(){ // pre-Decreasment
//         if(this->denominator == 0 ){
//             throw ("Error: Divide by 0");
//         }
//         else{
//             this->numerator -= this->denominator;
//             return *this;
//         }
//     }

//     Fraction Fraction::operator--(int num){ // post-Decreasment
//         if(this->denominator == 0 ){
//             throw ("Error: Divide by 0");
//         }
//         else{

//             Fraction temp(*this);
//             --*this;        // call the prefix operator
//             return temp;
//         }
//     }

//     // ======================= input & output =======================

//     istream& operator>> (istream &input , Fraction& fraction){

//         int num, den;
//         if(input.fail() || input.peek() == EOF){
//             input.setstate(std::ios_base::failbit);
//         }
//         input >> num;
//         if(input.peek() == EOF){
//             throw runtime_error("Error: There is one number");
//         }
//         input >> den;
//         if(den == 0){
//             throw runtime_error("Error: Denominator can't be 0");
//         }
//         fraction = Fraction(num,den);
//         return input;

//     }

//     ostream& operator<<(ostream &out ,const Fraction &fraction){
//         Fraction result(fraction);
//         result.reduce();
//         out << result.numerator << "/" << result.denominator;
//         return out;
//     }


// }