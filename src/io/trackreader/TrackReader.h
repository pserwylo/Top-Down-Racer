#ifndef TRACKREADER_H_
#define TRACKREADER_H_

#include <string>

class Track;
class b2World;

class TrackReader
{
public:
	TrackReader() {};
	virtual ~TrackReader() {};

	static TrackReader* create( b2World* world, std::string trackName, double scale = 1 );
	Track* getTrack() { return this->track; };

protected:
	virtual void readTrack( b2World* world, std::string trackName, double scale ) = 0;

protected:
	Track* track;
};

#endif /* TRACKREADER_H_ */
