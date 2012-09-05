#ifndef _GENOME_H_
#define _GENOME_H_

#include <vector>

namespace GAL
{
	template < class T >
	class Genome
	{
	private:
		double Fitness;
		std::vector< T > Genes;

	public:
		explicit Genome( int GenomeLength ) : Fitness( 0.0f )
		{
			for( int Iter = 0; Iter < GenomeLength; Iter++ )
			{
				Genes.push_back( T() );
			}
		}

		Genome( std::vector< T > Genes )	:	Fitness( 0.0f ),
												Genes( Genes )
		{}

		inline double GetFitness() { return Fitness; }
		inline void SetFitness( double NewFitness ) { Fitness = NewFitness; }

		inline const std::vector< T > GetGenes() const { return Genes; }
		inline void SetGenes( std::vector< T > NewGenes ) { Genes = NewGenes; }

	};
}

#endif