#include "io/trackreader/reg/RegTrackReader.h"
#include "core/Track.h"
#include "lib/rapidxml.hpp"
#include "Box2D.h"

#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace rapidxml;
using namespace std;

void RegTrackReader::readTrack( b2World* world, std::string trackName, double scale )
{
	this->track = new Track( world );

	string line;
	string xml;

	ifstream stream;
	string trackPath = "data/tracks/" + trackName + "/track.svg";
	stream.open( trackPath.c_str() );
	while ( !stream.eof() )
	{
		getline( stream, line );
		xml += line;
	}
	stream.close();

	this->parseXML( world, xml, scale );

}
