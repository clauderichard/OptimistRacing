/*	Copyright (C) 2012  Claude Richard
 *
 *	Optimist Racing is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Optimist Racing is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Optimist Racing.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Event.hpp"


EventPublisher::EventPublisher()
{
}

EventPublisher::~EventPublisher()
{
}
	
void EventPublisher::subscribeEvent( std::string eventName, void(*method)(void) )
{
	EventList::iterator it = mEvents.find( eventName );
	if ( it==mEvents.end() ) {
		mEvents[ eventName ] = FunctionList();
	}
	mEvents[ eventName ].push_back( method );
}

void EventPublisher::unsubscribeEvent( std::string eventName, void(*method)(void) )
{
	FunctionList::iterator it=mEvents.at(eventName).begin();
	while ( it!=mEvents.at(eventName).end() ) {
		if ( *it == method ) {
			FunctionList::iterator toErase = it;
			it++;
			mEvents.at(eventName).erase(toErase);
		} else {
			it++;
		}
	}
}

void EventPublisher::unsubscribeEventAll( std::string eventName )
{
	EventList::iterator it = mEvents.find( eventName );
	if ( it != mEvents.end() ) {
		mEvents.erase( it );
	}
}

void EventPublisher::publishEvent( std::string eventName )
{
	EventList::iterator it = mEvents.find( eventName );
	if ( it != mEvents.end() ) {
		for (FunctionList::iterator it2=it->second.begin(); it2!=it->second.end(); it2++) {
			(*it2)();
		}
	}
}