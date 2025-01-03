#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
	// Public member
	double min, max;

	// Config function
	interval() :min(+infinity), max(-infinity) {}
	interval(double min, double max) :min{ min }, max{ max } {}
	
	// Public method
	double size() const {
		return max - min;
	}
	double contains(double x) const {
		return min <= x && x <= max;
	}
	bool surrounds(double x) const {
		return min < x && x < max;
	}
    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }
	static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif