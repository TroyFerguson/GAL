#ifndef _CROSSOVER_OPERATORS_H_
#define _CROSSOVER_OPERATORS_H_

#include "Genome.h"
#include "Random.h"

namespace GAL
{
	namespace Operators
	{
		void SinglePointCrossover( const Genome &Mum, const Genome &Dad, Genome &Daughter, Genome &Son, double CrossoverRate )
		{
			if( ( Random::RandomFloat() < CrossoverRate ) || ( Mum == Dad ) )
			{
				Daughter = Mum;
				Son = Dad;

				return;
			}

			std::vector< Gene* > MumGenes = Mum.GetGenes(), DadGenes = Dad.GetGenes();
			std::vector< Gene* > DaughterGenes, SonGenes;

			unsigned int CrossoverPoint = Random::RandomInt( 0, MumGenes.size() - 1 );

			for( unsigned int iter = 0; iter < CrossoverPoint; iter++ )
			{
				DaughterGenes.push_back( MumGenes[iter] );
				SonGenes.push_back( DadGenes[iter] );
			}

			for( unsigned int iter = CrossoverPoint; iter < MumGenes.size(); iter++ )
			{
				DaughterGenes.push_back( MumGenes[iter] );
				SonGenes.push_back( DadGenes[iter] );
			}

		}
	}
}

#endif