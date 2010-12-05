#include "io/TrackReader.h"
#include "core/Track.h"
#include "lib/rapidxml.hpp"

#include <fstream>
#include <cstring>
#include <iostream>

using namespace rapidxml;
using namespace std;

TrackReader::TrackReader( std::string filename )
{
	string line;
	string xml;

	ifstream stream;
	stream.open( filename.c_str() );
	while ( !stream.eof() )
	{
		getline( stream, line );
		xml += line;
	}
	stream.close();

	xml_document<> doc;
	doc.parse<0>( &xml[0] );

	xml_node<>* svgNode = doc.first_node();
	for ( xml_node<>* svgChild = svgNode->first_node(); svgChild; svgChild = svgChild->next_sibling() )
	{
		if ( strcmp( svgChild->name(), "g" ) == 0 )
		{
			std::cout << "Found 'g' Node!" << std::endl;
			for ( xml_node<>* pathNode = svgChild->first_node(); pathNode; pathNode = pathNode->next_sibling() )
			{
				for ( xml_attribute<>* pathAttribute = pathNode->first_attribute(); pathAttribute; pathAttribute = pathAttribute->next_attribute() )
				{
					if ( strcmp( pathAttribute->name(), "d" ) == 0 )
					{
						string path = pathAttribute->value();
						path = path.substr( 2, path.length() - 4 );
						std::cout << pathNode->name() << ": '" << path << "'" << std::endl;
						break;
					}
				}
			}
			break;
		}
	}

}

TrackReader::~TrackReader()
{

}

Track* TrackReader::getTrack()
{
	return this->track;
}
