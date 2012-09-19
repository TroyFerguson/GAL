#ifndef _GENOME_H_
#define _GENOME_H_

#include <vector>
#include <algorithm>
#include "Gene.h"

namespace GAL
{
	class Genome
	{
	private:
		double Fitness;
		std::vector< Gene* > Genes;

		void Clear();

	public:
		typedef Gene* (*GeneConstructor)();

		explicit Genome() : Fitness( 0.0f ) {}

		explicit Genome( int ChromosomeLength, GeneConstructor CreateGene )	:	Fitness( 0.0f )
		{
			for( int iter = 0; iter < ChromosomeLength; iter++ )
			{
				Genes.push_back( CreateGene() );
			}
		}

		explicit Genome( std::vector< Gene* > Genes )	:	Fitness( 0.0f ),
															Genes( Genes )
		{}

		Genome( const Genome& Other )	:	Fitness( Other.GetFitness() ),
													Genes( Other.GetGenes() )
		{}

		~Genome();

		Genome& operator=( const Genome& );
		bool operator==( const Genome& ) const;
		const Gene* operator[]( int Index ) const;

		double GetFitness() const { return Fitness; }
		void SetFitness( double NewFitness ) { Fitness = NewFitness; }

		const std::vector< Gene* > GetGenes() const { return Genes; }
		void SetGenes( std::vector< Gene* > NewGenes ) { Genes = NewGenes; }

		unsigned int Size() const { return Genes.size(); }

	};

}

#endif