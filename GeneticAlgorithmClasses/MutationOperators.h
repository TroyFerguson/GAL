#ifndef _MUTATION_OPERATORS_H_
#define _MUTATION_OPERATORS_H_

#include <vector>
#include "Genome.h"
#include "Gene.h"

namespace GAL
{
	namespace Operators
	{
		void DeferredMutation( Genome &Mutatee )
		{
			std::vector< Gene* > Genes = Mutatee.GetGenes();

			for( std::vector< Gene* >::iterator iter = Genes.begin(); iter != Genes.end(); iter++ )
			{
				(*iter)->Mutate();
			}

			Mutatee.SetGenes( Genes );
		}
	}
}

#endif