#ifndef _GENE_H_
#define _GENE_H_

namespace GAL
{
	class Gene
	{
	public:
		virtual ~Gene();
		virtual void Mutate() = 0;
	};
}

#endif