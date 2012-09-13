#pragma once

namespace Math
{
	template< class T >
	class Point
	{
	public:
		T X, Y;

		explicit Point() : X( 0 ), Y( 0 )
		{}

		explicit Point( T X, T Y ) : X( X ), Y( Y )
		{}

		Point operator+( const Point rhs )
		{
			return Point( X + rhs.X, Y + rhs.Y );
		}

		Point operator-( const Point rhs )
		{
			return Point( X - rhs.X, Y - rhs.Y );
		}

		Point operator*( const Point rhs )
		{
			return Point( X * rhs.X, Y * rhs.Y );
		}

		Point operator/( const Point rhs )
		{
			return Point( X / rhs.X, Y / rhs.Y );
		}
	};
}