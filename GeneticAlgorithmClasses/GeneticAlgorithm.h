#ifndef _GENETIC_ALGORITHM_H_
#define _GENETIC_ALGORITHM_H_

#include "Assert\Assertion.h"

#include <vector>
#include "Genome.h"
#include "Gene.h"

namespace GAL
{
	class GeneticAlgorithm
	{
	public:

		typedef void (*CrossoverOperator)( const Genome&, const Genome&, Genome&, Genome&, double );
		typedef Genome (*SelectionOperator)( const std::vector< Genome >& );
		typedef void (*MutationOperator)( Genome&, double );

		explicit GeneticAlgorithm	(	double CrossoverRate,
										double MutationRate,
										int ChromosomeLength,
										int PopulationSize,
										CrossoverOperator Crossover = NULL,
										SelectionOperator SelectGenome = NULL,
										MutationOperator Mutate = NULL,
										Genome::GeneConstructor CreateGene = NULL
									) : CrossoverRate( CrossoverRate ),
										MutationRate( MutationRate ),
										ChromosomeLength( ChromosomeLength ),
										bEvolving( false ),
										PopulationSize( PopulationSize ),
										Generation( 0 ),
										Crossover( Crossover ),
										Mutate( Mutate ),
										SelectGenome( SelectGenome ),
										CreateGene( CreateGene )
		{
			ASSERT( Crossover != NULL );
			ASSERT( Mutate != NULL );
			ASSERT( SelectGenome != NULL );
			ASSERT( CreateGene != NULL );
			Reset();
		}

		void Epoch();
		void Reset();

	private:
		int Generation;
		unsigned int PopulationSize;
		std::vector< Genome > Population;

		int ChromosomeLength;
		
		double CrossoverRate;
		double MutationRate;
		
		/** Whether the genetic algorithm is running or not */
		bool bEvolving;

		void UpdateFitnessScores();

		virtual void CalculateFitness( Genome& ) = 0;

		virtual void PreEpoch(){};
		virtual void PerformElitism( std::vector< Genome >& ){};
		virtual void PostEpoch(){};

		void CreateNewGeneration();

		//Member function pointers
		CrossoverOperator Crossover;
		MutationOperator Mutate;
		SelectionOperator SelectGenome;
		Genome::GeneConstructor CreateGene;
	};

}

#endif