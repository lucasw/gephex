#ifndef SEQUENCESERIAL_H
#define SEQUENCESERIAL_H

#include <iosfwd>

namespace sequencer
{
	class Sequence;

	std::ostream& operator<< (std::ostream& s, const Sequence& sequ);
	std::istream& operator>> (std::istream& s, Sequence& sequ);

}
#endif
