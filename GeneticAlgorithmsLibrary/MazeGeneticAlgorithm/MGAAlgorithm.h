#ifndef _MGAALGORITHM_H_
#define _MGAALGORITHM_H_

#include "GeneticAlgorithm.h"
#include "GeneticOperators.h"
#include "Point.h"
#include "GlobalDefines.h"
#include "Maze.h"
#include "MGAGene.h"

namespace MGA
{
	GAL::Gene* MGAGeneConstructor()
	{
		return new MGAGene();
	}

	class MGAAlgorithm : public GAL::GeneticAlgorithm
	{
	public:
		explicit MGAAlgorithm()
			: GeneticAlgorithm( CROSSOVER_RATE,
								MUTATION_RATE,
								CHROMO_LENGTH,
								POP_SIZE,
								(GAL::GeneticAlgorithm::CrossoverOperator)GAL::Operators::SinglePointCrossover,
								(GAL::GeneticAlgorithm::SelectionOperator)GAL::Operators::RouletteWheelSelector,
								(GAL::GeneticAlgorithm::MutationOperator)GAL::Operators::DeferredMutation,
								(GAL::Genome::GeneConstructor)MGAGeneConstructor )
		{
		}

	private:
		Maze TestMaze;

		virtual void CalculateFitness( GAL::Genome& );
	};
}

#endif