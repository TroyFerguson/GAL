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

	Genome::~Genome()
	{
		Clear();
	}

	Genome& Genome::operator=( const Genome &Other )
	{
		if( this != &Other )
		{
			Clear();

			Fitness = Other.GetFitness();
			Genes = Other.GetGenes();
		}

		return *this;
	}

	bool Genome::operator==( const Genome &lhs ) const
	{
		if( Genes.size() != lhs.GetGenes().size() )
		{
			return false;
		}
		
		for( unsigned int iter = 0; iter < Genes.size(); iter++ )
		{
			if( Genes[iter] != lhs[iter] )
			{
				return false;
			}
		}

		return true;
	}

	const Gene* Genome::operator[]( int Index ) const
	{
		return Genes[ Index ];
	}

	void Genome::Clear()
	{
		for( std::vector< Gene* >::iterator iter = Genes.begin(); iter != Genes.end(); iter++ )
		{
			delete (*iter);
		}
	}
}

#endif