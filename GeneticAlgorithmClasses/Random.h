#ifndef _RANDOM_UTIL_H
#define _RANDOM_UTIL_H

#include <time.h>

namespace Random
{
	struct RandomNumberGenerator
	{
		RandomNumberGenerator() { srand((unsigned)time(0)); }
	};

	template< typename T >
	T RandomNumber( T Min, T Max )
	{
		return ( Min + (T)rand() / ( (T)RAND_MAX / ( Max-Min ) ) );
	}

	double RandomDouble( double Min = 0.0, double Max = 1.0 )
	{
		return RandomNumber< double >( Min, Max );
	}

	float RandomFloat( float Min = 0.0, float Max = 1.0 )
	{
		return RandomNumber< float >( Min, Max );
	}

	int RandomInt( int Min = 0.0, int Max = 1.0 )
	{
		return RandomNumber< int >( Min, Max );
	}

	static RandomNumberGenerator RNG;
}

#endif