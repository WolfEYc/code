
 
#ifndef EARTHQUAKE
#define EARTHQUAKE



class QuakeDataSegment
{
	private:
		// members
		double waveAmplitude;
		double latitude;
		double longitude;
		double depth;

	public:
		// constructors
		QuakeDataSegment();
		QuakeDataSegment(double wa, double lat, double longi, double dep);

		// setters
		void setWaveAmplitude(double wa) { waveAmplitude = wa; }
		void setLatitude(double lat) { latitude = lat; }
		void setLongitude(double longi) { longitude = longi; }
		void setDepth(double dep) { depth = dep; }

		// getters
		double getWaveAmplitude() const { return waveAmplitude; }
		double getLatitude() const { return latitude; }
		double getLongitude() const { return longitude; }
		double getDepth() const { return depth; }

};

// overloaded output operator for QuakeDataSegment
std::ostream &operator<< (std::ostream &os, const QuakeDataSegment &x);


class EarthQuake
{

	private:
		unsigned int lengthOfQuake;

		double maxAmplitude;
		double minAmplitude;
		unsigned int sWaveIndex;
		
		// local coordinates to measure distance to quake
		// automatically set to College Station by default constructor
		double localGpsLatitude;
		double localGpsLongitude;

		// earthquake coordinates
		double earthquakeGpsLatitude;
		double earthquakeGpsLongitude;

		unsigned int distanceFromQuake;

		bool movedLatLong;
		bool movedDepth;


	public:
		// default constructor
		EarthQuake();

		// getters
		int getLengthOfQuake() const;
		double getMaxAmplitude() const;
		double getMinAmplitude() const;
		unsigned int getSWaveIndex() const; 
		std::string getEarthquakeLocation() const;
		bool getChangeInLatLong() const;
		bool getChangeInDepth() const;

		unsigned int getDistanceFromQuake() const;
		void setDistanceFromQuake();
	
		// display output helper
		void displayDataSegment(QuakeDataSegment*) const;

		// functions for setting and loading data
		void loadEarthquakeData(QuakeDataSegment* &dS, std::string file);
		void resizeArray(QuakeDataSegment*&);

		void setMaxAmplitude(QuakeDataSegment*);
		void setMinAmplitude(QuakeDataSegment*);
		void setSWaveIndex(QuakeDataSegment*);

		void setEarthquakeLocation(QuakeDataSegment*);
		void setChangeInLatLong(QuakeDataSegment*);
		void setChangeInDepth(QuakeDataSegment*);

};

std::ostream &operator << (std::ostream &os, const EarthQuake &x);



#endif
