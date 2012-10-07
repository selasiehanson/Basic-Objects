#ifndef __CVEC2
#define __CVEC2

namespace base
{
	namespace math
	{
		template<class T>
		class CVec2
		{
			public :
				CVec2<T>(){}
				CVec2<T>(T _x, T _y):x(_x), y(_y){}
				T x;
				T y;
		};

		typedef CVec2<int> Vec2i;
		typedef CVec2<float> Vec2f;
	}
}

#endif