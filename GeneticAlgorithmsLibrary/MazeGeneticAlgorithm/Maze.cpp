#include "Maze.h"
#include "Point.h"
#include "Genome.h"
#include "MGAGene.h"
#include "Assertion.h"

#include <iostream>

namespace MGA
{
#define MAP_HEIGHT 10
#define MAP_WIDTH 15

	const int Maze::Map[MAP_HEIGHT][MAP_WIDTH] = 
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
			 8, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
			 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1,
			 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
			 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
			 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1,
			 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5,
			 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
			 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	const Math::Point<int> Maze::StartPoint = Math::Point<int>( 14, 7 );
	const Math::Point<int> Maze::EndPoint = Math::Point<int>( 0, 2 );

	bool Maze::TestCell( Math::Point<int> Cell )
	{
		ASSERT( 0 <= Cell.X && Cell.X < MapHeight );
		ASSERT( 0 <= Cell.Y && Cell.Y < MapWidth );

		switch( Map[ Cell.X ][ Cell.Y ] )
		{
		//Empty spot
		case 0:
		//Exit
		case 8:
			return true;

		//Obstacle
		case 1:
		//Entry
		case 5:
			return false;

		default:
			std::cout << "Unknown tile type " << Map[ Cell.X ][ Cell.Y ] << " at point[" << Cell.X << ", " << Cell.Y << "]" << std::endl;
		}

		return false;
	}

	double Maze::TestRoute( const GAL::Genome& Route )
	{
		Math::Point< int > CurrentPosition = StartPoint;

		for( unsigned int iter = 0; iter < Route.Size(); iter++ )
		{
			const MGAGene* NextGene = dynamic_cast< const MGAGene* >( Route[ iter ] );
			Math::Point< int > NewCell;

			if( NextGene != NULL )
			{
				switch( NextGene->Direction )
				{
				case 0:
					NewCell = CurrentPosition + Math::Point< int >( 0, 1 );
					break;

				case 1:
					NewCell = CurrentPosition - Math::Point< int >( 0, 1 );
					break;

				case 2:
					NewCell = CurrentPosition + Math::Point< int >( 1, 0 );
					break;

				case 3:
					NewCell = CurrentPosition - Math::Point< int >( 1, 0 );
					break;

				default:
					std::cout << "Unknown direction " << NextGene->Direction << " in gene " << iter << std::endl;
				}
			}

			if( TestCell( NewCell ) )
			{
				CurrentPosition = NewCell;
				if( Map[ CurrentPosition.X ][ CurrentPosition.Y ] == 8 )
				{
					return 1.0;
				}
			}
		}

		Math::Point< int > DistanceToExit = CurrentPosition - EndPoint;


		return ( 1 / (double)( DistanceToExit.X + DistanceToExit.Y + 1 ) );
	}
}