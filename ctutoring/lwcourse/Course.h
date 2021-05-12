#ifndef COURSE_DESCRIPTION_H
#define COURSE_DESCRIPTION_H

#include <string>

/**
 * Represents course by its ID and title. 
 */
class Course {
    /**
     * Course ID.
     */
    std::string id = "";

    /**
     * Course title.
     */
    std::string title = "";

public:
    /**
     * Default constructor.
     */
    Course() {}

    /**
     * Full constructor. 
     */
    Course(std::string id, std::string title)
    : id(id), title(title) {}

    /**
     * Getter function for course ID.
     */
    std::string getId() const { return id; }

    /**
     * Getter function for course title.
     */
    std::string getTitle() const {return title; }
};

#endif