#ifndef __CMATRIX4
#define __CMATRIX4
#include <stdio.h>

namespace base
{
	namespace math
	{
		template <class T>
		class CMatrix4 
		{
			public:
				CMatrix4<T> ();
				CMatrix4<T> (T k); //k is a constant / scalar value
				~CMatrix4<T> () {};
				
				CMatrix4<T> operator * (const CMatrix4<T> &other) const;
				CMatrix4<T> operator * (const T k) const; 
				CMatrix4<T> operator + (const CMatrix4<T> &other) const;
				CMatrix4<T> operator - (const CMatrix4<T> &other) const;
				CMatrix4<T> operator = (const CMatrix4<T> &other) const;
				T& CMatrix4<T>::operator[] (const int i);
				bool operator == (const CMatrix4<T> &other) ;
				bool operator != (const CMatrix4<T> &other);
				

				
				static CMatrix4<T> makeIdentity();
				bool isIdentity();
				CMatrix4<T> transpose();
				const T * asPointer() {return m;};
			//private:
				T m[16]; //this holds a 16 element array corresponnding to a 4x4 matrix. opengl prefers a single line of floats
		};


		//DEFINITIONS

		template <class T>
		base::math::CMatrix4<T>::CMatrix4()
		{
			m[0] = 1;
			m[1] = 1;
			m[2] = 1;
			m[3] = 1;

			m[4] = 1;
			m[5] = 1;
			m[6] = 1;
			m[7] = 1;
			
			m[8] = 1;
			m[9] = 1;
			m[10] = 1;
			m[11] = 1;
			
			m[12] = 1;
			m[13] = 1;
			m[14] = 1;
			m[15] = 1;
		}
		
		template <class T>
		base::math::CMatrix4<T>::CMatrix4 (T k)
		{
			m[0] = k;
			m[1] = k;
			m[2] = k;
			m[3] = k;

			m[4] = k;
			m[5] = k;
			m[6] = k;
			m[7] = k;
			
			m[8] = k;
			m[9] = k;
			m[10] = k;
			m[11] = k;
			
			m[12] = k;
			m[13] = k;
			m[14] = k;
			m[15] = k;

		}

		template <class T>
		inline CMatrix4<T> CMatrix4<T>::makeIdentity()
		{
			CMatrix4<T> newM;
						
			newM.m[0] = (T)1;
			newM.m[1] = (T)0;
			newM.m[2] = (T)0;
			newM.m[3] = (T)0;

			newM.m[4] = (T)0;
			newM.m[5] = (T)1;
			newM.m[6] = (T)0;
			newM.m[7] = (T)0;
			
			newM.m[8] = (T)0;
			newM.m[9] = (T)0;
			newM.m[10] = (T)1;
			newM.m[11] = (T)0;
			
			newM.m[12] = (T)0;
			newM.m[13] = (T)0;
			newM.m[14] = (T)0;
			newM.m[15] = (T)1;
			
			return newM;
		}

		template <class T>
		inline bool CMatrix4<T>::isIdentity()
		{
			//return (m[0] == 1 && m[5]== 1 && m[10] && m[15]== 1); not correct
			//CMatrix4 newM = this->makeIdentity();
			//return (newM == this );
			return false;
		}

		template <class T>
		inline CMatrix4<T> CMatrix4<T>::operator*(const CMatrix4<T> &other) const
		{
			CMatrix4<T> a = other;
		
			CMatrix4<T> Y;
			if(a.isIdentity()) //TODO: check both matrices for identity
				memcpy(Y.m, m, sizeof(T) *16 );
			else
			{
				CMatrix4<T> n = other;
					Y[0]  = m[0]*n.m[0] + m[4]*n.m[1] + m[8]*n.m[2]     + m[12]*n.m[3] ;
					Y[1]  = m[1]*n.m[0] + m[5]*n.m[1] + m[9]*n.m[2]     + m[13]*n.m[3] ; 
					Y[2]  = m[2]*n.m[0] + m[6]*n.m[1] + m[10]*n.m[2]    + m[14]*n.m[3] ;
					Y[3]  = m[3]*n.m[0] + m[7]*n.m[1] + m[11]*n.m[2]    + m[15]*n.m[3] ;
					
					Y[4]  = m[0]*n.m[4] + m[4]*n.m[5] + m[8]*n.m[6]     + m[12]*n.m[7] ;
					Y[5]  = m[1]*n.m[4] + m[5]*n.m[5] + m[8]*n.m[6]     + m[13]*n.m[7] ;
					Y[6]  = m[2]*n.m[4] + m[6]*n.m[5] + m[10]*n.m[6]    + m[14]*n.m[7] ;
					Y[7]  = m[3]*n.m[4] + m[7]*n.m[5] + m[11]*n.m[6]    + m[15]*n.m[7] ;
					
					Y[8]  = m[0]*n.m[8] + m[4]*n.m[9] + m[8]*n.m[10]    + m[12]*n.m[11] ;
					Y[9]  = m[1]*n.m[8] + m[5]*n.m[9] + m[9]*n.m[10]    + m[13]*n.m[11] ;
					Y[10] = m[2]*n.m[8] + m[6]*n.m[9] + m[10]*n.m[10]   + m[14]*n.m[11] ;
					Y[11] = m[3]*n.m[8] + m[7]*n.m[9] + m[11]*n.m[10]   + m[15]*n.m[11] ;
					
					Y[12] = m[0]*n.m[12] + m[4]*n.m[13] + m[8]*n.m[14]  + m[12]*n.m[15] ;
					Y[13] = m[1]*n.m[12] + m[5]*n.m[13] + m[9]*n.m[14]  + m[13]*n.m[15] ;
					Y[14] = m[2]*n.m[12] + m[6]*n.m[13] + m[10]*n.m[14] + m[14]*n.m[15] ;
					Y[15] = m[3]*n.m[12] + m[7]*n.m[13] + m[11]*n.m[14] + m[15]*n.m[15] ;
			}

			return Y;
		}

		template <class T>
		inline CMatrix4<T> CMatrix4<T>::operator*(const T k) const
		{
			CMatrix4<T> newM;
			for(int i=0; i < 16; i++)
				newM[i] = m[i]  * k; 

			return newM;
		}

		template <class T>
		inline CMatrix4<T> CMatrix4<T>::operator + (const CMatrix4<T> & other) const 
		{
			CMatrix4 newM;
			for (int i = 0 ; i < 16; i++)
				newM[i] = m[i]  + other.m[i];
			
			return newM;
		}

		template <class T>
		inline CMatrix4<T> CMatrix4<T>::operator- (const CMatrix4<T> & other) const 
		{
			CMatrix4 newM;
			for (int i = 0 ; i < 16; i++)
				newM[i] = m[i]  - other.m[i];
			
			return newM;
		}

		template <class T>
		inline CMatrix4<T> CMatrix4<T>::transpose()
		{
			CMatrix4<T newM;

			newM[0] = m[0];
			newM[1] = m[4];
			newM[2] = m[8];
			newM[3] = m[12];

			newM[4] = m[1];
			newM[5] = m[5];
			newM[6] = m[9];
			newM[7] = m[13];

			newM[8] = m[2];
			newM[9] = m[6];
			newM[10] = m[10];
			newM[11] = m[14];

			newM[12] = m[3];
			newM[13] = m[7];
			newM[14] = m[11];
			newM[15] = m[15];
			return newM;
		}

		template <class T>
		inline bool CMatrix4<T>::operator== (const CMatrix4<T> &other)
		{
			bool result = true;
			for(int i=0; i < 16; i++)
			{
				if(m[i]!= other.m[i] )
				{
					result = false;
					break;
				}
			}
			return result;
		}

		template <class T>
		inline bool CMatrix4<T>::operator!= (const CMatrix4<T> &other)
		{
			//TODO
			bool result = true;
			for(int i=0; i < 16; i++)
			{
				if(m[i] == other.m[i] )
				{
					result = false;
					break;
				}
			}
			return result;
		}
		
		template <class T>
		inline T& CMatrix4<T>::operator[] (const int i)
		{
			return m[i];
		}

		template <class T>
		inline CMatrix4<T> CMatrix4<T>::operator= (const CMatrix4<T> &other) const
		{
			if(this==&other)
				return *this;
			memcpy(other.m, this->m,sizeof(T)*16);
			return *this;
		}
 		//TYPE DEFS
		typedef CMatrix4<float> Matrix4f;
	}

}
#endif;