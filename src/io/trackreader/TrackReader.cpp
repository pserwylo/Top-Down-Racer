#include "io/trackreader/TrackReader.h"

#ifdef WII
#include "io/trackreader/wii/WiiTrackReader.h"
#else
#include "io/trackreader/reg/RegTrackReader.h"
#endif

TrackReader* TrackReader::create( b2World* world, std::string trackName, double scale )
{

	TrackReader* reader;

#ifdef WII
	reader = new WiiTrackReader();
#else
	reader = new RegTrackReader();
#endif

	reader->readTrack( world, trackName, scale );
	return reader;

}
