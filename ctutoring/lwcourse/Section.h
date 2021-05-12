	#ifndef SECTION_H
	#define SECTION_H

	#include <string>

/**
 * Represents section by ID, time, location, and instructor.
 */
class Section {
	const std::string NA = "n/a";

	/**
	 * Section ID.
	 */
	std::string id;

	/**
	 * Section time.
	 */
	std::string time;

	/**
	 * Section location.
	 */
	std::string location;

	/**
	 * Section instructor.
	 */
	std::string instructor;
	
  public:
	/**
	 * Default constructor.
	 */
	Section() : id(NA), time(NA), location(NA), instructor(NA) { }

	/**
	 * Copy constructor.
	 */
	Section(const Section& other)
		: id(other.id), time(other.time), location(other.location), instructor(other.instructor) {}

	/**
	 * Full constructor.
	 * @param	id			Section ID.
	 * @param	time		Section time.
	 * @param	location	Section location.
	 * @param	instructor	Section instructor.
	 */
	Section(std::string id, std::string time, std::string location, std::string instructor) 
		: id(id), time(time), location(location), instructor(instructor) { }

	/**
	 * Copy assignment operator.
	 */
	Section& operator=(const Section& other) {
		this->id         = other.id;
		this->time 	     = other.time;
		this->location 	 = other.location;
		this->instructor = other.instructor;
		return *this;
	}

	/**
	 * Getter function for section ID.
	 * @return	Section ID.
	 */
	std::string getId() const { return id; }

	/**
	 * Getter function for section location.
	 * @return	Section location.
	 */
	std::string getLocation() const { return location; }

	/**
	 * Getter function for section time.
	 * @return	Section time.
	 */
	std::string getTime() const { return time; }

	/**
	 * Getter function for section instructor.
	 * @return	Section instructor.
	 */
	std::string getInstructor() const { return instructor; }

	/**
	 * Setter function for section ID.
	 * @param	id		Section ID.
	 */
	void setId(std::string id) {this->id = id; }

	/**
	 * Setter function for section time.
	 * @param	time	Section time.
	 */
	void setTime(std::string time)  { this->time = time; }

	/**
	 * Setter function for section location.
	 * @param	location	Section location.
	 */
	void setLocation(std::string location) { this->location = location; }

	/**
	 * Setter function for section instructor.
	 * @param	instructor	Section instructor.
	 */
	void setInstructor(std::string instructor) { this->instructor = instructor; }
};

#endif