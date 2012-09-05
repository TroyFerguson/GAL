#ifndef _MUTATION_OPERATORS_H_
#define _MUTATION_OPERATORS_H_

#include <vector>
#include "Genome.h"
#include "Gene.h"

namespace GAL
{
	namespace Operators
	{
		template< class T >
		struct DefferedMutator
		{
			void operator() ( Genome< T > &Mutatee )
			{
				const std::vector< T > Genes = Mutatee.GetGenes();

				for( std::vector< T >::iterator iter = Genes.begin(); iter != Genes.end(); iter++ )
				{
					(Gene)(*iter).Mutate();
				}

				Mutatee.SetGenes( Genes );
			}
		};
	}
}

#endif