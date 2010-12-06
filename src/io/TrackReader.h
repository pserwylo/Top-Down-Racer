/*
 * TrackReader.h
 *
 *  Created on: 05/12/2010
 *      Author: pete
 */

#ifndef TRACKREADER_H_
#define TRACKREADER_H_

#include <string>
class Track;
class b2World;

class TrackReader {
public:
	TrackReader( b2World* world, std::string filename, double scale = 1 );
	virtual ~TrackReader();

	Track* getTrack();

private:
	Track* track;
};

#endif /* TRACKREADER_H_ */
