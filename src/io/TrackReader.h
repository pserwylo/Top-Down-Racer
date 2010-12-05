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

class TrackReader {
public:
	TrackReader( std::string filename );
	virtual ~TrackReader();

	Track* getTrack();

private:
	Track* track;
};

#endif /* TRACKREADER_H_ */
