#ifndef _GENETIC_ALGORITHM_H_
#define _GENETIC_ALGORITHM_H_

#include <vector>
#include "Genome.h"

namespace GAL
{
	template< class T, class Y >
	class GeneticAlgorithm
	{
	public:

		typedef void (*CrossoverOperator)( Genome< T >, Genome< T >, Genome< T >&, Genome< T >& );
		typedef Genome< T > (*SelectionOperator)();
		typedef void (*MutationOperator)( Genome< T >& );

		explicit GeneticAlgorithm	(	double CrossoverRate,
										double MutationRate,
										int ChromosomeLength,
										int PopulationSize,
										CrossoverOperator Crossover = NULL,
										SelectionOperator SelectGenome = NULL,
										MutationOperator Mutate = NULL
									) : CrossoverRate( CrossoverRate ),
										MutationRate( MutationRate ),
										ChromosomeLength( ChromosomeLength ),
										bEvolving( false ),
										PopulationSize( PopulationSize ),
										Generation( 0 ),
										Crossover( Crossover ),
										Mutate( Mutate ),
										SelectGenome( SelectGenome )
		{
			Reset();
		}

		void Epoch();
		void Reset();

	private:
		int Generation;
		int PopulationSize;
		std::vector< Genome< T > > Population;

		int ChromosomeLength;
		
		double CrossoverRate;
		double MutationRate;
		
		/** Whether the genetic algorithm is running or not */
		bool bEvolving;

		void UpdateFitnessScores();

		virtual Y Decode( Genome< T > ) = 0;
		virtual void CalculateFitness( Genome< T >& ) = 0;

		virtual void PreEpoch(){};
		virtual void PerformElitism( std::vector< Genome< T > >& ){};
		virtual void PostEpoch(){};

		void CreateNewGeneration();

		//Member function pointers
		CrossoverOperator Crossover;
		MutationOperator Mutate;
		SelectionOperator SelectGenome;
	};

	template< class T, class Y >
	void GAL::GeneticAlgorithm< T, Y >::Epoch()
	{
		PreEpoch();
		CreateNewGeneration();
		PostEpoch();
	}

	template< class T, class Y >
	void GAL::GeneticAlgorithm< T, Y >::CreateNewGeneration()
	{
		std::vector< Genome< T > > NewGeneration;

		PerformElitism( &NewGeneration );

		while( NewGeneration.size() < PopulationSize )
		{
			Genome< T > Mum = (*SelectGenome)();
			Genome< T > Dad = (*SelectGenome)();

			Genome< T > Daughter, Son;

			(*Crossover)( Mum, Dad, Daughter, Son );

			(*Mutate)( &Daughter );
			(*Mutate)( &Son );

			NewGeneration.push_back( Daughter );
			NewGeneration.push_back( Son );

		}

		Population = NewGeneration;

		++Generation;
	}

	template< class T, class Y >
	void GAL::GeneticAlgorithm< T, Y >::Reset()
	{
		Population.clear();

		for( int Iter = 0; Iter < PopulationSize; Iter++ )
		{
			Population.push_back( Genome< T >( ChromosomeLength ) );
		}

		Generation = 0;
	}

	template< class T, class Y >
	void GAL::GeneticAlgorithm< T, Y >::UpdateFitnessScores()
	{
		for( int Iter = 0; Iter < Population.Size(); Iter++ )
		{
			CalculateFitness( &Population[ Iter ] );
		}
	}

}

#endif