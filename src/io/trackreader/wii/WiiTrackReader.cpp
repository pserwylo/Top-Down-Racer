#include "io/trackreader/wii/WiiTrackReader.h"
#include "core/Track.h"
#include "Box2D/Box2D.h"

#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <fat.h>

using namespace rapidxml;
using namespace std;

void WiiTrackReader::readTrack( b2World* world, std::string trackName, double scale )
{

	this->track = new Track( world );

	string line;
	string xml;

	ifstream stream;
	string trackPath = "/apps/TDR/data/tracks/" + trackName + "/track.svg";
	stream.open( trackPath.c_str() );
	if ( !stream.is_open() )
	{
		exit( 0 );
	}

	while ( !stream.eof() )
	{
		getline( stream, line );
		xml += line;
	}
	stream.close();

	this->parseXML( world, xml, scale );

}
