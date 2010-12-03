/*
 * Track.h
 *
 *  Created on: 18/10/2010
 *      Author: pete
 */

#ifndef TRACK_H_
#define TRACK_H_

class Track
{
public:
	Track();
	virtual ~Track();

public:
	b2PolygonShape** getObstacles();
	b2PolygonShape** getBorders();
	b2PolygonShape** getWaypoints();

};

#endif /* TRACK_H_ */
