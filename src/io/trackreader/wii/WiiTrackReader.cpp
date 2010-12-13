#include "io/trackreader/wii/WiiTrackReader.h"
#include "core/Track.h"
#include "lib/rapidxml.hpp"
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

	xml_document<> doc;
	doc.parse<0>( &xml[0] );

	// Search all of the children of the root 'svg' node and use those which are a 'g' node...
	xml_node<>* svgNode = doc.first_node();
	for ( xml_node<>* svgChild = svgNode->first_node(); svgChild; svgChild = svgChild->next_sibling() )
	{
		if ( strcmp( svgChild->name(), "g" ) == 0 )
		{

			// Identify each path node inside the 'g' node, and extract the 'd' attribute from each...
			for ( xml_node<>* pathNode = svgChild->first_node(); pathNode; pathNode = pathNode->next_sibling() )
			{
				for ( xml_attribute<>* pathAttribute = pathNode->first_attribute(); pathAttribute; pathAttribute = pathAttribute->next_attribute() )
				{
					if ( strcmp( pathAttribute->name(), "d" ) == 0 )
					{

						// Strip off the leading 'M ' and trailing ' z' from the path...
						string path = pathAttribute->value();
						path = path.substr( 2, path.length() - 4 );
						std::cout << pathNode->name() << ": '" << path << "'" << std::endl;

						// Tokenize the path, so that we can extract all of the coordinates from it...
						stringstream pathStream( path );
						string token;

						vector<b2Vec2> points;

						// Extract the x, y pairs and convert to numbers...
						while ( getline( pathStream, token, ' ' ) )
						{
							int commaIndex = token.find( ',' );
							double x = atof( token.substr( 0, commaIndex ).c_str() );
							double y = atof( token.substr( commaIndex + 1 ).c_str() );
							points.push_back( b2Vec2( x / scale, y / scale ) );
						}

						// Stuff them into an appropriate data structure and give them to the Track object...
						b2BodyDef obstacleDef;
						obstacleDef.type = b2_staticBody;
						obstacleDef.userData = this->track;
						b2Body* obstacleBody = world->CreateBody( &obstacleDef );

						b2Vec2* borderPoints = new b2Vec2[ points.size() ];
						for ( unsigned int i = 0; i < points.size(); i ++ )
						{
							borderPoints[ i ] = points[ i ];
						}
						b2LoopShape* border = new b2LoopShape();

						border->Create( borderPoints, points.size() );


						this->track->getBorders().push_back( border );

						obstacleBody->CreateFixture( border, points.size() );
						break;
					}
				}
			}
			break;
		}
	}

}
