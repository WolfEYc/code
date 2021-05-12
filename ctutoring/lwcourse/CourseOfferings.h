#ifndef COURSE_OFFERINGS_H
#define COURSE_OFFERINGS_H

#include <string>
#include "Course.h"
#include "Section.h"

/**
 * Represents course offerings as course, year, semester, number of sections,
 * capacity, and list of sections.
 */
class CourseOfferings {
    /**
     * Offered course.
     */
    Course course;

    /**
     * Offered course's academic year.
     */
    unsigned int year;

    /**
     * Offered course's academic semester.
     */
    char semester;

    /**
     * Number of offered course sections.
     */
    size_t nbSections;

    /**
     * Offered course's capacity.
     */
    size_t capacity;

    /**
     * List of offered course sections.
     */
    Section* sectionList;

    /**
     * Increases array capacity for storing list of sections.
     */
    void increaseSectionListCapacity();

  public:
    /* TODO: Declare copy constructor here. */
    CourseOfferings(const CourseOfferings& other);
    /* TODO: Declare copy assignment operator function here. */
    void operator=(const CourseOfferings& other);
    /* TODO: Declare destructor here. */
    ~CourseOfferings();
    /**
     * Default constructor
     */
    CourseOfferings()
        : course(), year(0), semester('X'), nbSections(0), capacity(0), sectionList(nullptr) {}

    /**
     * Full construtor
     * @param
     */
    CourseOfferings(Course course, unsigned int year, char semester);

    /**
     * Constructor for course in different semester year.
     * @param   year        Academic year of course.
     * @param   semester    Academic semester of course.
     * @param   other       Other course.
     */
    CourseOfferings(unsigned int year, char semester, const CourseOfferings& other);

    /**
     * Adds section to list of offered course sections.
     * @param   section     Section.
     */
    void addSection(const Section& section);

    /**
     * Getter function for offered course year.
     */
    unsigned int getYear() const { return year; }

    /**
     * Getter function for offered course semester.
     */
    char getSemester() const { return semester; }

    /**
     * Getter function for offered course.
     */
    Course getCourse() const { return course; }

    /**
     * Getter function for number of offered course sections.
     */
    size_t getNumberSections() const { return nbSections; }

    /**
     * Getter function for list of offered course sections.
     */
    Section* getSectionList() const { return sectionList; }

    /**
     * Getter function for array capacity of offered course sections.
     */
    size_t getSectionListCapacity() const { return capacity;}
};

/* TODO: Declare CourseOfferings extraction overload operator function here. */
std::ostream& operator<<(std::ostream& os, CourseOfferings& other);

/**
 * Equality operator overload function for CourseOfferings class.
 */
bool operator==(const CourseOfferings& lhs, const CourseOfferings& rhs);

#endif