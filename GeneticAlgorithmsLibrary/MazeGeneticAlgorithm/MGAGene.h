#ifndef _MGAGENE_H_
#define _MGAGENE_H_

#include "Gene.h"
#include "Random.h"

namespace MGA
{
	class MGAGene : public GAL::Gene
	{
	public:
		//North=0
		//South=1
		//East=2
		//West=3
		int Direction;

		explicit MGAGene() : Direction( Random::RandomInt( 0, 3 ) )
		{}

		virtual void Mutate()
		{
			Direction = Random::RandomInt( 0, 3 );
		}
	};
}

#endif