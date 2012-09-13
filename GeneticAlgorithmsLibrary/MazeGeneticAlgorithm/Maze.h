#ifndef _MAZE_H_
#define _MAZE_H_

#include "Point.h"
#include "Genome.h"

namespace MGA
{
#define MAP_HEIGHT 10
#define MAP_WIDTH 15

	class Maze
	{
	private:
		int MapHeight, MapWidth;
		static const Math::Point< int > StartPoint, EndPoint;

		static const int Map[ MAP_HEIGHT ][ MAP_WIDTH ];

		bool TestCell( Math::Point< int > Cell );

	public:
		explicit Maze()	:	MapHeight( MAP_HEIGHT ), MapWidth( MAP_WIDTH )
		{
		}

		double TestRoute( const GAL::Genome& );

		void Render();
	};
}

#endif