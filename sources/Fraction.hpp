#include <iostream>
#include <stdexcept>
#include <cmath>
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
        float set3DigitsBeyondThePoint(float );
        friend float set3DigitsAfterThePoint(float );
        void reduce();
        int GCD(int , int ) const;
        friend bool checkOverflow(const Fraction &, const Fraction &, char );

        // Overloaded operators 
        Fraction operator+(const Fraction&) const;
        Fraction operator-(const Fraction&) const;
        Fraction operator*(const Fraction&) const;
        Fraction operator/(const Fraction&) const;

        friend Fraction operator+(const float& ,const Fraction &) ;
        friend Fraction operator-(const float& ,const Fraction &) ;
        friend Fraction operator*(const float& ,const Fraction &) ;
        friend Fraction operator/(const float& ,const Fraction &) ;

        friend Fraction operator+(const Fraction &, const float&) ;
        friend Fraction operator-(const Fraction &, const float&) ;
        friend Fraction operator*(const Fraction &, const float&) ;
        friend Fraction operator/(const Fraction &, const float&) ;
        
        bool operator==(const Fraction&) const;
        bool operator<(const Fraction&) const;
        bool operator<=(const Fraction&) const;
        bool operator>(const Fraction&) const;
        bool operator>=(const Fraction&) const;

        friend bool operator==(const Fraction &, const float&) ;
        friend bool operator<(const Fraction &, const float&) ;
        friend bool operator<=(const Fraction &, const float&) ;
        friend bool operator>(const Fraction &, const float&) ;
        friend bool operator>=(const Fraction &, const float&) ;

        friend bool operator==(const float& ,const Fraction &);
        friend bool operator<(const float& ,const Fraction &);
        friend bool operator<=(const float& ,const Fraction &);
        friend bool operator>(const float& ,const Fraction &);
        friend bool operator>=(const float& ,const Fraction &);


        
        Fraction& operator++();
        Fraction operator++( int );
        Fraction& operator--();
        Fraction operator--( int );

        friend ostream & operator<<(ostream&, const Fraction&);
        friend istream& operator>> (istream&, Fraction& );

    };    
    
}
