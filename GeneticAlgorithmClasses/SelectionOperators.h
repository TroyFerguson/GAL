#ifndef _SELECTION_OPERATORS_H_
#define _SELECTION_OPERATORS_H_

#include <vector>
#include "Genome.h"
#include "Random\Random.h"

namespace GAL
{
	namespace Operators
	{

		Genome RouletteWheelSelector( const std::vector< Genome > Population )
		{
			double TotalFitnessScore = 0.0;

			for( auto iter = Population.begin(); iter != Population.end(); iter++ )
			{
				TotalFitnessScore += (*iter).GetFitness();
			}

			double Slice = Random::RandomDouble() * TotalFitnessScore;
			double FitnessAccumulator = 0.0;
			int SelectedGenome = 0;

			for( unsigned int iter = 0; iter < Population.size(); iter++ )
			{
				FitnessAccumulator += Population[ iter ].GetFitness();

				if( FitnessAccumulator > Slice )
				{
					SelectedGenome = iter;
					break;
				}
			}

			return Population[ SelectedGenome ];
		}

	}
}

#endif