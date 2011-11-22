#include "io/trackreader/TrackReader.h"
#include "lib/rapidxml.hpp"
#include "core/Track.h"
#include "core/Waypoint.h"
#include "Box2D.h"

#include <fstream>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

#ifdef WII
#include "io/trackreader/wii/WiiTrackReader.h"
#else
#include "io/trackreader/reg/RegTrackReader.h"
#endif

using namespace rapidxml;
using namespace std;

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

void TrackReader::parseXML( b2World* world, std::string& xmlContents, double scale )
{
	this->world = world;
	this->scale = scale;

	xml_document<> doc;
	doc.parse<0>( &xmlContents[0] );

	// Search all of the children of the root 'svg' node and use those which are a 'g' node...
	xml_node<>* svgNode = doc.first_node();
	for ( xml_node<>* svgChild = svgNode->first_node(); svgChild; svgChild = svgChild->next_sibling() )
	{
		if ( strcmp( svgChild->name(), "g" ) == 0 )
		{
			// cout << "Found g element..." << endl;
			this->handleGElement( svgChild );
		}
	}
}

void TrackReader::handleGElement( xml_node<>* gNode )
{
	// Identify each path node inside the 'g' node, and extract the 'd' attribute from each...
	for ( xml_node<>* pathNode = gNode->first_node(); pathNode; pathNode = pathNode->next_sibling() )
	{
		vector<b2Vec2> points;
		string id;

		for ( xml_attribute<>* pathAttribute = pathNode->first_attribute(); pathAttribute; pathAttribute = pathAttribute->next_attribute() )
		{
			if ( strcmp( pathAttribute->name(), "id" ) == 0 )
			{
				id = pathAttribute->value();
			}
			else if ( strcmp( pathAttribute->name(), "d" ) == 0 )
			{
				// Strip off the leading 'M ' and trailing ' z' from the path...
				string path = pathAttribute->value();
				path = path.substr( 2, path.length() - 4 );
				// std::cout << pathNode->name() << ": '" << path << "'" << std::endl;

				// Tokenize the path, so that we can extract all of the coordinates from it...
				stringstream pathStream( path );
				string token;

				// Extract the x, y pairs and convert to numbers...
				while ( getline( pathStream, token, ' ' ) )
				{
					int commaIndex = token.find( ',' );
					double x = atof( token.substr( 0, commaIndex ).c_str() );
					double y = atof( token.substr( commaIndex + 1 ).c_str() );
					points.push_back( b2Vec2( x / this->scale, y / this->scale ) );
				}
			}
		}

		if ( points.size() > 0 )
		{
			// Stuff them into an appropriate data structure and give them to the Track object...
			b2BodyDef obstacleDef;
			obstacleDef.type = b2_staticBody;
			obstacleDef.userData = this->track;
			b2Body* obstacleBody = this->world->CreateBody( &obstacleDef );

			// Transfer from the std::vector to an array for box2D...
			b2Vec2* borderPoints = new b2Vec2[ points.size() ];
			for ( unsigned int i = 0; i < points.size(); i ++ )
			{
				borderPoints[ i ] = points[ i ];
			}

			b2LoopShape* border = new b2LoopShape();
			border->Create( borderPoints, points.size() );
			b2Fixture* fixture = obstacleBody->CreateFixture( border, points.size() );

			// If its a checkpoint, don't allow collisions, instead we just want to know when the car drives over it...
			bool isCheckpoint = ( strncmp( id.c_str(), "checkpoint_", 11 ) == 0 );
			bool isHazard = ( strncmp( id.c_str(), "hazard_", 7 ) == 0 );
			if ( isCheckpoint )
			{
				// Extract waypoint index from xml id...
				std::string waypointNumber = id.substr( 11 );
				int waypointIndex = atoi( waypointNumber.c_str() );

				Waypoint* waypoint = new Waypoint( obstacleBody, waypointIndex );

				fixture->SetSensor( true );
				obstacleBody->SetUserData( waypoint );

				this->track->getWaypoints().push_back( waypoint );
			}
			else if ( isHazard )
			{
				fixture->SetSensor( true );
				obstacleBody->SetUserData( this->track );
				this->track->getHazards().push_back( fixture->GetShape() );
			}
			else
			{
				obstacleBody->SetUserData( this->track );
				this->track->getBorders().push_back( fixture->GetShape() );
			}
		}
	}
}
