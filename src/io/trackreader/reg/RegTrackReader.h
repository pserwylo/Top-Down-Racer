#ifndef REGTRACKREADER_H_
#define REGTRACKREADER_H_

#include "io/trackreader/TrackReader.h"

class RegTrackReader : public TrackReader
{
public:
	RegTrackReader() {};
	virtual ~RegTrackReader() {};

protected:
	virtual void readTrack( b2World* world, std::string trackName, double scale );

};

#endif /* REGTRACKREADER_H_ */
