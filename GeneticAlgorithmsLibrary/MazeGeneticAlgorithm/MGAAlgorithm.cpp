#include "MGAAlgorithm.h"
#include "Genome.h"
#include "MGAGene.h"

namespace MGA
{
	void MGAAlgorithm::CalculateFitness( GAL::Genome& Candidate )
	{
		double Fitness = TestMaze.TestRoute( Candidate );
		Candidate.SetFitness( Fitness );
	}
}