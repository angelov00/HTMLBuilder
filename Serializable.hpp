#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include <fstream>

class Serializable {
protected:
	virtual void serialize(std::ostream& os) const = 0;
};

#endif // !SERIALIZABLE_HPP
