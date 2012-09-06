#ifndef _MUTATION_OPERATORS_H_
#define _MUTATION_OPERATORS_H_

#include <vector>
#include "Random.h"
#include "Genome.h"
#include "Gene.h"

namespace GAL
{
	namespace Operators
	{
		void DeferredMutation( Genome &Mutatee, double MutationRate )
		{
			std::vector< Gene* > Genes = Mutatee.GetGenes();

			for( std::vector< Gene* >::iterator iter = Genes.begin(); iter != Genes.end(); iter++ )
			{
				if( Random::RandomFloat() > MutationRate )
				{
					(*iter)->Mutate();
				}
			}

			Mutatee.SetGenes( Genes );
		}
	}
}

#endif