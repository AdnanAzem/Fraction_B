#include <iostream>
#include <stdexcept>
#include <cmath>
#define MAX std::numeric_limits<int>::max()
#define MIN std::numeric_limits<int>::min()
using namespace std;

namespace ariel{

    class Fraction
    {
    private:
        int numerator;
        int denominator;
        
    public:

        // const
        Fraction();
        Fraction(int , int);
        Fraction(float);
        
        //setters
        void setNumerator(int);
        void setDenominator(int);

        //getters
        int getNumerator();
        int getDenominator();

        //helper functions
        bool checkFractionOverflow(const Fraction& , const Fraction& , char ) const; // check overflow between 2 fractions
        float setFloatWith3Digits(float ); // set 3 digits after point
        void reduce(); // reduced form of fraction
        int GCD(int , int ) const; // find gcd between 2 numbers

        // Overloaded operators 
        // (Fraction,Fraction)
        Fraction operator+(const Fraction&) const;
        Fraction operator-(const Fraction&) const;
        Fraction operator*(const Fraction&) const;
        Fraction operator/(const Fraction&) const;

        // (float,Fraction)
        friend Fraction operator+(const float& ,const Fraction &) ;
        friend Fraction operator-(const float& ,const Fraction &) ;
        friend Fraction operator*(const float& ,const Fraction &) ;
        friend Fraction operator/(const float& ,const Fraction &) ;

        // (Fraction,float)
        friend Fraction operator+(const Fraction &, const float&) ;
        friend Fraction operator-(const Fraction &, const float&) ;
        friend Fraction operator*(const Fraction &, const float&) ;
        friend Fraction operator/(const Fraction &, const float&) ;
        
        // (Fraction,Fraction)
        bool operator==(const Fraction&) const;
        bool operator<(const Fraction&) const;
        bool operator<=(const Fraction&) const;
        bool operator>(const Fraction&) const;
        bool operator>=(const Fraction&) const;


        // (Fraction,float)
        friend bool operator==(const Fraction &, const float&) ;
        friend bool operator<(const Fraction &, const float&) ;
        friend bool operator<=(const Fraction &, const float&) ;
        friend bool operator>(const Fraction &, const float&) ;
        friend bool operator>=(const Fraction &, const float&) ;

        // (float,Fraction)
        friend bool operator==(const float& ,const Fraction &);
        friend bool operator<(const float& ,const Fraction &);
        friend bool operator<=(const float& ,const Fraction &);
        friend bool operator>(const float& ,const Fraction &);
        friend bool operator>=(const float& ,const Fraction &);

        Fraction& operator++(); // Prefix
        Fraction operator++( int ); // Postfix
        Fraction& operator--(); // Prefix
        Fraction operator--( int ); // Postfix

        friend ostream & operator<<(ostream&, const Fraction&);
        friend istream& operator>> (istream&, Fraction& );

    };    
    
}
