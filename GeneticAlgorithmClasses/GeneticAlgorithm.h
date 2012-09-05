#ifndef _GENETIC_ALGORITHM_H_
#define _GENETIC_ALGORITHM_H_

#include "Assertion.h"

#include <vector>
#include "Genome.h"
#include "Gene.h"

namespace GAL
{
	class GeneticAlgorithm
	{
	public:

		typedef void (*CrossoverOperator)( Genome, Genome, Genome&, Genome& );
		typedef Genome (*SelectionOperator)();
		typedef void (*MutationOperator)( Genome& );

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

	void GAL::GeneticAlgorithm::Epoch()
	{
		PreEpoch();
		CreateNewGeneration();
		PostEpoch();
	}

	void GAL::GeneticAlgorithm::CreateNewGeneration()
	{
		std::vector< Genome > NewGeneration;

		PerformElitism( NewGeneration );

		while( NewGeneration.size() < PopulationSize )
		{
			Genome Mum = (*SelectGenome)();
			Genome Dad = (*SelectGenome)();

			Genome Daughter, Son;

			(*Crossover)( Mum, Dad, Daughter, Son );

			(*Mutate)( Daughter );
			(*Mutate)( Son );

			NewGeneration.push_back( Daughter );
			NewGeneration.push_back( Son );

		}

		Population = NewGeneration;

		++Generation;
	}

	void GAL::GeneticAlgorithm::Reset()
	{
		Population.clear();

		for( unsigned int Iter = 0; Iter < PopulationSize; Iter++ )
		{
			Population.push_back( Genome( ChromosomeLength, CreateGene ) );
		}

		Generation = 0;
	}

	void GAL::GeneticAlgorithm::UpdateFitnessScores()
	{
		for( unsigned int Iter = 0; Iter < Population.size(); Iter++ )
		{
			CalculateFitness( Population[ Iter ] );
		}
	}

}

#endif