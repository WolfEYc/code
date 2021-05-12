	

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>       /* fabs */
#include <limits>

#include "EarthQuake.h"

using namespace std;

// QuakeDataSegment constructors
/* TODO */
QuakeDataSegment::QuakeDataSegment() {
	waveAmplitude = 0;
	latitude = 0;
	longitude = 0;
	depth = 0;
}

/* TODO */
QuakeDataSegment::QuakeDataSegment(double wa, double lat, double longi, double dep) {
	waveAmplitude = wa;
	latitude = lat;
	longitude = longi;
	depth = dep;
}

// overloaded output operator for QuakeDataSegment
ostream &operator<< (ostream &os, const QuakeDataSegment &x) //remember x is an alias
{
	os << "waveAmplitude: " <<  x.getWaveAmplitude() << endl;
	os << "latitude: " <<  x.getLatitude() << endl;
	os << "longitude: " <<  x.getLongitude() << endl;
	os << "depth: " <<  x.getDepth() << endl;
	return os;
}

// EarthQuake constructor
EarthQuake::EarthQuake() :
	lengthOfQuake(0), 
	// this is used so you don't have to pass the size
	maxAmplitude(numeric_limits<double>::max()),
	minAmplitude(numeric_limits<double>::min()),

	sWaveIndex(0),

	localGpsLatitude(30.6), localGpsLongitude(-96.3),
	// College Station TX coordinates

	earthquakeGpsLatitude(0.0),  // - if South 
	earthquakeGpsLongitude(0.0), // - if West
	  
	distanceFromQuake(0),
		
	movedLatLong(false),
	movedDepth(false)
{}

// getters
int EarthQuake::getLengthOfQuake() const { return lengthOfQuake;	}
double EarthQuake::getMaxAmplitude() const { return maxAmplitude; }
double EarthQuake::getMinAmplitude() const { return minAmplitude; }
unsigned int EarthQuake::getSWaveIndex() const { return sWaveIndex; }
string EarthQuake::getEarthquakeLocation() const
{ return to_string(earthquakeGpsLongitude) + " " + to_string(earthquakeGpsLatitude); }
bool EarthQuake::getChangeInLatLong() const { return movedLatLong; }
bool EarthQuake::getChangeInDepth() const { return movedDepth; }
unsigned int EarthQuake::getDistanceFromQuake() const { return distanceFromQuake; }

void EarthQuake::setDistanceFromQuake()
{
	int R = 6371; // radius = 6371 kilometers
	double x = earthquakeGpsLatitude * M_PI/180; // in radians
	double y = localGpsLatitude * M_PI/180;
	double deltaX = (localGpsLongitude -earthquakeGpsLongitude) * M_PI/180;
	double deltaY = (localGpsLatitude -earthquakeGpsLatitude) * M_PI/180;

	double a = sin(deltaY/2) * sin(deltaY/2) +
			  cos(x) * cos(y) *
			  sin(deltaX/2) * sin(deltaX/2);
	distanceFromQuake = (2 * R * atan2(sqrt(a), sqrt(1-a))); // in meters
}

void EarthQuake::displayDataSegment(QuakeDataSegment * dS) const
{
	for (unsigned int i = 0; i < lengthOfQuake; i++)
	{
		// using overloaded QuakeDataSegment
		cout << "******************" << endl;
		cout << "at second " << (i + 1) << endl;
		cout << dS[i] << endl;
	}
}

// functions for setting and loading data
void EarthQuake::loadEarthquakeData(QuakeDataSegment* &dataSegment, string file)
{

	dataSegment = new QuakeDataSegment[1];
	
	ifstream in(file);
	double wa, lat, longi, depth;
	
	while(in >> wa >> lat >> longi >> depth){
		
		resizeArray(dataSegment); // resize for new row
		
		dataSegment[lengthOfQuake-1].setWaveAmplitude(wa);
		dataSegment[lengthOfQuake-1].setLatitude(lat);
		dataSegment[lengthOfQuake-1].setLongitude(longi);
		dataSegment[lengthOfQuake-1].setDepth(depth);		
		
	}
	
	
}

void EarthQuake::resizeArray(QuakeDataSegment* &segarr)
{
	// TODO
	lengthOfQuake++;
	
	QuakeDataSegment temp[lengthOfQuake+1];
	
	for(unsigned int i = 0;i<lengthOfQuake;i++)
		temp[i] = segarr[i];
	
	segarr = new QuakeDataSegment[lengthOfQuake+1];

	for(unsigned int i = 0;i<lengthOfQuake;i++)
		segarr[i] = temp[i];

	//cout << lengthOfQuake << endl;	
	
}


void EarthQuake::setMaxAmplitude(QuakeDataSegment* segarr)
{
	// TODO
	double max = numeric_limits<double>::min();
	for(unsigned int i = 0; i<lengthOfQuake;i++)
		if(segarr[i].getWaveAmplitude()>max)
			max = segarr[i].getWaveAmplitude();

	maxAmplitude = max;

}

void EarthQuake::setMinAmplitude(QuakeDataSegment* segarr)
{
	// TODO
	double min = numeric_limits<double>::max();
	for(unsigned int i = 0; i<lengthOfQuake;i++)
		if(segarr[i].getWaveAmplitude()<min)
			min = segarr[i].getWaveAmplitude();

	minAmplitude = min;
}

void EarthQuake::setSWaveIndex(QuakeDataSegment* segarr)
{
	// TODO
	for(unsigned int i = 1; i<lengthOfQuake;i++)
		if(segarr[i-1].getWaveAmplitude()<segarr[i].getWaveAmplitude())
			sWaveIndex = i;
}

void EarthQuake::setEarthquakeLocation(QuakeDataSegment* segarr) 
{
	// TODO
	earthquakeGpsLatitude = segarr[0].getLatitude();
	earthquakeGpsLongitude = segarr[0].getLongitude();
}

void EarthQuake::setChangeInLatLong(QuakeDataSegment* segarr)
{
	// set default from [0] for lat and long, see if it changes
	for(unsigned int i = 0;i<lengthOfQuake;i++)
		if(earthquakeGpsLatitude != segarr[i].getLatitude()
		 || earthquakeGpsLongitude != segarr[i].getLongitude())
			movedLatLong = 1;
}

void EarthQuake::setChangeInDepth(QuakeDataSegment* segarr)
{
	// set default from [0] for depth, see if it changes
		double def = segarr[0].getDepth();
		for(unsigned int i = 0;i<lengthOfQuake;i++)
			if(segarr[i].getDepth()!=def)
				movedDepth = 1;
}

ostream &operator << (ostream &os, const EarthQuake &x)
{
	os << "Max amp: " << x.getMaxAmplitude() << endl;
	os << "Min amp: " << x.getMinAmplitude() << endl;
	os << "Length of Quake: " << x.getLengthOfQuake() << endl;
	os << "S wave arrival (in seconds): " << x.getSWaveIndex() << endl;
	os << "Location of Quake: " << x.getEarthquakeLocation() << endl;
	os << "Distance from Quake: " << x.getDistanceFromQuake() << "km " << endl;
	os << "Did quake lat/long move? (0/1): " << x.getChangeInLatLong() << endl;
	os << "Did quake depth move? (0/1): " << x.getChangeInDepth() << endl;
	return os;
}
