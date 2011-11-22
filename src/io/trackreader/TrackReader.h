#ifndef TRACKREADER_H_
#define TRACKREADER_H_

#include <string>
#include <lib/rapidxml.hpp>

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
	void parseXML( b2World* world, std::string& xmlContents, double scale );

private:
	void handleGElement( rapidxml::xml_node<>* gNode );

protected:
	Track* track;
	b2World* world;
	double scale;
};

#endif /* TRACKREADER_H_ */
