#ifndef _GENOME_H_
#define _GENOME_H_

#include <vector>
#include "Gene.h"

namespace GAL
{
	class Genome
	{
	private:
		double Fitness;
		std::vector< Gene* > Genes;

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

		~Genome();

		bool operator==( const Genome& ) const;

		inline double GetFitness() { return Fitness; }
		inline void SetFitness( double NewFitness ) { Fitness = NewFitness; }

		inline const std::vector< Gene* > GetGenes() const { return Genes; }
		inline void SetGenes( std::vector< Gene* > NewGenes ) { Genes = NewGenes; }

	};

	Genome::~Genome()
	{
		for( std::vector< Gene* >::iterator iter = Genes.begin(); iter != Genes.end(); iter++ )
		{
			delete (*iter);//TODO: Check that this isn't retarded
		}
	}

	bool Genome::operator==( const Genome &lhs ) const
	{
		std::vector< Gene* > LhsGenes = lhs.GetGenes();

		if( Genes.size() != LhsGenes.size() )
		{
			return false;
		}
		
		for( unsigned int iter = 0; iter < Genes.size(); iter++ )
		{
			if( Genes[iter] != LhsGenes[iter] )
			{
				return false;
			}
		}

		return true;
	}
}

#endif