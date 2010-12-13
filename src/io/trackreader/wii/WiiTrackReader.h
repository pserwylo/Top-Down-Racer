#ifndef WIITRACKREADER_H_
#define WIITRACKREADER_H_

#include "io/trackreader/TrackReader.h"

class WiiTrackReader : public TrackReader
{
public:
	WiiTrackReader() {};
	virtual ~WiiTrackReader() {};

protected:
	virtual void readTrack( b2World* world, std::string trackName, double scale );

};

#endif /* WIITRACKREADER_H_ */
