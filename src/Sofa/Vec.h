/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, version 1.0 beta 4      *
*                (c) 2006-2009 MGH, INRIA, USTL, UJF, CNRS                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                              SOFA :: Framework                              *
*                                                                             *
* Authors: M. Adam, J. Allard, B. Andre, P-J. Bensoussan, S. Cotin, C. Duriez,*
* H. Delingette, F. Falipou, F. Faure, S. Fonteneau, L. Heigeas, C. Mendoza,  *
* M. Nesme, P. Neumann, J-P. de la Plata Alcade, F. Poyer and F. Roy          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#ifndef SOFA_DEFAULTTYPE_VEC_H
#define SOFA_DEFAULTTYPE_VEC_H

#include <functional>
#include <Sofa/fixed_array.h>

#define EQUALITY_THRESHOLD 1e-6

namespace sofa
{

namespace defaulttype
{

enum NoInit { NOINIT }; ///< use when calling Vec or Mat constructor to skip initialization of values to 0

template <int N, typename real=double>
class Vec : public helper::fixed_array<real,N>
{
public:
        typedef real Real;

        /// Compile-time constant specifying the number of scalars within this vector (equivalent to static_size and size() method)
        enum { total_size = N };
        /// Compile-time constant specifying the number of dimensions of space (equivalent to total_size here)
        enum { spatial_dimensions = N };

        /// Default constructor: sets all values to 0.
        Vec()
        {
            this->clear();
        }

        /// Fast constructor: no initialization
        explicit Vec(NoInit)
        {
        }

        /// Specific constructor for 1-element vectors.
        explicit Vec(real r1)
        {
            this->elems[0]=r1;
        }

        /// Specific constructor for 1-element vectors.
        void operator=(real r1)
        {
            this->elems[0]=r1;
        }

        /// Specific constructor for 2-elements vectors.
        Vec(real r1, real r2)
        {
                this->elems[0]=r1;
                this->elems[1]=r2;
        }

        /// Specific constructor for 3-elements vectors.
        Vec(real r1, real r2, real r3)
        {
                this->elems[0]=r1;
                this->elems[1]=r2;
                this->elems[2]=r3;
        }

        /// Specific constructor for 4-elements vectors.
        Vec(real r1, real r2, real r3, real r4)
        {
                this->elems[0]=r1;
                this->elems[1]=r2;
                this->elems[2]=r3;
                this->elems[3]=r4;
        }

        /// Specific constructor for 6-elements vectors.
        Vec(real r1, real r2, real r3, real r4, real r5, real r6)
        {
            this->elems[0]=r1;
            this->elems[1]=r2;
            this->elems[2]=r3;
            this->elems[3]=r4;
            this->elems[4]=r5;
            this->elems[5]=r6;
        }

        /// Specific constructor for 8-elements vectors.
        Vec(real r1, real r2, real r3, real r4, real r5, real r6, real r7, real r8)
        {
                this->elems[0]=r1;
                this->elems[1]=r2;
                this->elems[2]=r3;
                this->elems[3]=r4;
                this->elems[4]=r5;
                this->elems[5]=r6;
                this->elems[6]=r7;
                this->elems[7]=r8;
        }

        /// Specific constructor for 9-elements vectors.
        Vec(real r1, real r2, real r3, real r4, real r5, real r6, real r7, real r8, real r9)
        {
            this->elems[0]=r1;
            this->elems[1]=r2;
            this->elems[2]=r3;
            this->elems[3]=r4;
            this->elems[4]=r5;
            this->elems[5]=r6;
            this->elems[6]=r7;
            this->elems[7]=r8;
            this->elems[8]=r9;
        }

        /// Specific constructor for 10-elements vectors.
        Vec(real r1, real r2, real r3, real r4, real r5, real r6, real r7, real r8, real r9, real r10)
        {
            this->elems[0]=r1;
            this->elems[1]=r2;
            this->elems[2]=r3;
            this->elems[3]=r4;
            this->elems[4]=r5;
            this->elems[5]=r6;
            this->elems[6]=r7;
            this->elems[7]=r8;
            this->elems[8]=r9;
            this->elems[9]=r10;
        }

        /// Specific constructor for 11-elements vectors.
        Vec(real r1, real r2, real r3, real r4, real r5, real r6, real r7, real r8, real r9, real r10, real r11)
        {
            this->elems[0]=r1;
            this->elems[1]=r2;
            this->elems[2]=r3;
            this->elems[3]=r4;
            this->elems[4]=r5;
            this->elems[5]=r6;
            this->elems[6]=r7;
            this->elems[7]=r8;
            this->elems[8]=r9;
            this->elems[9]=r10;
            this->elems[10]=r11;
        }

        /// Specific constructor for 11-elements vectors.
        Vec(real r1, real r2, real r3, real r4, real r5, real r6, real r7, real r8, real r9, real r10, real r11, real r12)
        {
            this->elems[0]=r1;
            this->elems[1]=r2;
            this->elems[2]=r3;
            this->elems[3]=r4;
            this->elems[4]=r5;
            this->elems[5]=r6;
            this->elems[6]=r7;
            this->elems[7]=r8;
            this->elems[8]=r9;
            this->elems[9]=r10;
            this->elems[10]=r11;
            this->elems[11]=r12;
        }

        /// Constructor from an N-1 elements vector and an additional value (added at the end).
        Vec(const Vec<N-1,real>& v, real r1)
        {
                for(int i=0;i<N-1;i++)
                        this->elems[i] = v[i];
                this->elems[N-1]=r1;
        }

        template<typename real2>
        Vec(const Vec<N, real2>& p)
        {
                //std::copy(p.begin(), p.end(), this->begin());
                for(int i=0;i<N;i++)
                        this->elems[i] = (real)p(i);
        }

        /// Constructor from an array of values.
        template<typename real2>
        explicit Vec(const real2* p)
        {
                //std::copy(p, p+N, this->begin());
                for(int i=0;i<N;i++)
                        this->elems[i] = (real)p[i];
        }

        /// Special access to first element.
        real& x()
        {
                return this->elems[0];
        }
        /// Special access to second element.
        real& y()
        {
                return this->elems[1];
        }
        /// Special access to third element.
        real& z()
        {
                return this->elems[2];
        }
        /// Special access to fourth element.
        real& w()
        {
                return this->elems[3];
        }

        /// Special const access to first element.
        const real& x() const
        {
                return this->elems[0];
        }
        /// Special const access to second element.
        const real& y() const
        {
                return this->elems[1];
        }
        /// Special const access to third element.
        const real& z() const
        {
                return this->elems[2];
        }
        /// Special const access to fourth element.
        const real& w() const
        {
                return this->elems[3];
        }

        /// Assignment operator from an array of values.
        template<typename real2>
        void operator=(const real2* p)
        {
                //std::copy(p, p+N, this->begin());
                for(int i=0;i<N;i++)
                        this->elems[i] = (real)p[i];
        }

        /// Assignment from a vector with different dimensions.
        template<int M, typename real2>
        void operator=(const Vec<M,real2>& v)
        {
                //std::copy(v.begin(), v.begin()+(N>M?M:N), this->begin());
                for(int i=0;i<(N>M?M:N);i++)
                        this->elems[i] = (real)v(i);
        }


//        ///// Cross product for 3-elements vectors.
//        template<typename real>
//        Vec<3,real> cross(const Vec<3,real>& b)
//        {
//                return Vec<3,real>(a.y()*b.z() - a.z()*b.y(),
//                                   a.z()*b.x() - a.x()*b.z(),
//                                   a.x()*b.y() - a.y()*b.x());
//        }

        /// Dot product (alias for operator*)
        real dot(const Vec<N,real>& b)
        {
                return *this*b;
        }

    /// Sets every element to 0.
    void clear()
    {
    this->assign(real());
    }

        /// Sets every element to r.
        void fill(real r)
        {
                this->assign(r);
        }

        // Access to i-th element.
        // Already in fixed_array
        //real& operator[](int i)
        //{
        //    return this->elems[i];
        //}

        // Access to i-th element.
        // Already in fixed_array
        /// Const access to i-th element.
        //const real& operator[](int i) const
        //{
        //    return this->elems[i];
        //}

        /// Access to i-th element.
        real& operator()(int i)
        {
                return this->elems[i];
        }

        /// Const access to i-th element.
        const real& operator()(int i) const
        {
                return this->elems[i];
        }

        /// Cast into a const array of values.
        /// CHANGE(Jeremie A.): removed it as it confuses some compilers. Use ptr() or data() instead
        //operator const real*() const
        //{
        //    return this->elems;
        //}

        /// Cast into an array of values.
        /// CHANGE(Jeremie A.): removed it as it confuses some compilers. Use ptr() or data() instead
        //operator real*()
        //{
        //    return this->elems;
        //}

        /// Cast into a const array of values.
        const real* data() const
        {
                return this->elems;
        }

        /// Cast into an array of values.
        real* data()
        {
                return this->elems;
        }

        // LINEAR ALGEBRA

    /// Multiplication by a scalar f.
    template<class real2>
    Vec<N,real> operator*(real2 f) const
    {
    Vec<N,real> r(NOINIT);
    for (int i=0;i<N;i++)
        r[i] = this->elems[i]*(real)f;
    return r;
    }

        /// On-place multiplication by a scalar f.
        template<class real2>
        void operator*=(real2 f)
        {
                for (int i=0;i<N;i++)
                        this->elems[i]*=(real)f;
        }


    /// Division by a scalar f.
    template<class real2>
    Vec<N,real> operator/(real2 f) const
    {
    Vec<N,real> r(NOINIT);
    for (int i=0;i<N;i++)
        r[i] = this->elems[i]/(real)f;
    return r;
    }

        /// On-place division by a scalar f.
        template<class real2>
        void operator/=(real2 f)
        {
                for (int i=0;i<N;i++)
                        this->elems[i]/=(real)f;
        }

        /// Dot product.
        template<class real2>
        real operator*(const Vec<N,real2>& v) const
        {
                real r = (real)(this->elems[0]*v[0]);
                for (int i=1;i<N;i++)
                        r += (real)(this->elems[i]*v[i]);
                return r;
        }

    /// linear product.
    template<class real2>
    Vec<N,real> linearProduct(const Vec<N,real2>& v) const
    {
    Vec<N,real> r(NOINIT);
    for (int i=0;i<N;i++)
        r[i]=this->elems[i]*(real)v[i];
    return r;
    }
    
    
    /// linear division.
    template<class real2>
    Vec<N,real> linearDivision(const Vec<N,real2>& v) const
    {
      Vec<N,real> r(NOINIT);
      for (int i=0;i<N;i++)
    r[i]=this->elems[i]/(real)v[i];
      return r;
    }

    /// Vector addition.
    template<class real2>
    Vec<N,real> operator+(const Vec<N,real2>& v) const
    {
    Vec<N,real> r(NOINIT);
    for (int i=0;i<N;i++)
        r[i]=this->elems[i]+(real)v[i];
    return r;
    }

        /// On-place vector addition.
        template<class real2>
        void operator+=(const Vec<N,real2>& v)
        {
                for (int i=0;i<N;i++)
                        this->elems[i]+=(real)v[i];
        }

    /// Vector subtraction.
    template<class real2>
    Vec<N,real> operator-(const Vec<N,real2>& v) const
    {
    Vec<N,real> r(NOINIT);
    for (int i=0;i<N;i++)
        r[i]=this->elems[i]-(real)v[i];
    return r;
    }

        /// On-place vector subtraction.
        template<class real2>
        void operator-=(const Vec<N,real2>& v)
        {
                for (int i=0;i<N;i++)
                        this->elems[i]-=(real)v[i];
        }

    /// Vector negation.
    Vec<N,real> operator-() const
    {
    Vec<N,real> r(NOINIT);
    for (int i=0;i<N;i++)
        r[i]=-this->elems[i];
    return r;
    }

        /// Squared norm.
        real norm2() const
        {
                real r = this->elems[0]*this->elems[0];
                for (int i=1;i<N;i++)
                        r += this->elems[i]*this->elems[i];
                return r;
        }

    /// Euclidean norm.
    real norm() const
    {
        return sqrt(norm2());
    }

        /// Normalize the vector.
        void normalize(real threshold=(real)1e-20)
        {
                const real r = norm();
                if (r>threshold)
                for (int i=0;i<N;i++)
                  this->elems[i]/=r;
        }

        Vec cross( const Vec& b ) const
        {
                return Vec(
                               (*this)[1]*b[2] - (*this)[2]*b[1],
                               (*this)[2]*b[0] - (*this)[0]*b[2],
                               (*this)[0]*b[1] - (*this)[1]*b[0]
                       );
        }

		
    /// sum of all elements of the vector
    real sum() const
    {
        real sum = 0.0;
        for (int i=0;i<N;i++)
            sum += this->elems[i];
        return sum;
    }
		
		
    /// @name Tests operators
    /// @{

    bool operator==(const Vec& b) const
    {
        for (int i=0;i<N;i++)
            if ( fabs( (double)(this->elems[i] - b[i]) ) > EQUALITY_THRESHOLD ) return false;
        return true;
    }

    bool operator!=(const Vec& b) const
    {
        for (int i=0;i<N;i++)
            if ( fabs( (double)(this->elems[i] - b[i]) ) > EQUALITY_THRESHOLD ) return true;
        return false;
    }

    /// @}
};

/// Same as Vec except the values are not initialized by default
template <int N, typename real=double>
class VecNoInit : public Vec<N,real>
{
public:
    VecNoInit()
    : Vec<N,real>(NOINIT)
    {
    }

    /// Assignment operator from an array of values.
    template<typename real2>
    void operator=(const real2* p)
    {
    this->Vec<N,real>::operator=(p);
    }

    /// Assignment from a vector with different dimensions.
    template<int M, typename real2>
    void operator=(const Vec<M,real2>& v)
    {
    this->Vec<N,real>::operator=(v);
    }

    /// Scalar vector multiplication operator.
    friend Vec<N,real> operator*(real r, const Vec<N,real>& v)
    {
        return v*r;
    }
};

/// Read from an input stream
template<int N,typename Real>
std::istream& operator >> ( std::istream& in, Vec<N,Real>& v )
{
        for( int i=0; i<N; ++i )
                in>>v[i];
        return in;
}

/// Write to an output stream
template<int N,typename Real>
std::ostream& operator << ( std::ostream& out, const Vec<N,Real>& v )
{
        for( int i=0; i<N-1; ++i )
                out<<v[i]<<" ";
        out<<v[N-1];
        return out;
}

///// Cross product for 3-elements vectors.
//template<typename real>
//inline Vec<3,real> cross(const Vec<3,real>& a, const Vec<3,real>& b)
//{
//        return Vec<3,real>(a.y()*b.z() - a.z()*b.y(),
//                           a.z()*b.x() - a.x()*b.z(),
//                           a.x()*b.y() - a.y()*b.x());
//}

///// Cross product for 2-elements vectors.
//template <typename real>
//real cross(const defaulttype::Vec<2,real>& a, const defaulttype::Vec<2,real>& b )
//{
//    return a[0]*b[1] - a[1]*b[0];
//}

///// Dot product (alias for operator*)
//template<int N,typename real>
//inline real dot(const Vec<N,real>& a, const Vec<N,real>& b)
//{
//        return a*b;
//}

} // namespace defaulttype

} // namespace sofa

#endif

