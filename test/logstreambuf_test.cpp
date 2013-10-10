/*
*  logstreamxx - C++ logging library based on standard stream classes
*  Copyright (C) 2013 Uditha Atukorala
*
*  This software library is free software; you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.
*
*  This software library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public License
*  along with this software library. If not, see <http://www.gnu.org/licenses/>.
*
*/

#include "logstreambuf_test.h"

#include <logstreamxx/logstreambuf.h>
#include <unistd.h>


// register the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( logstreambuf_test );

// use namespace logstreamxx
using namespace logstreamxx;


void logstreambuf_test::test_constructor() {

	// log stream buffer
	logstreambuf sb;

	// assert - read buffer will be empty always
	CPPUNIT_ASSERT( 0 == sb.in_avail() );

}


void logstreambuf_test::test_overloaded_constructor() {

	// instance with STDERR as the destination
	CPPUNIT_ASSERT_NO_THROW( logstreambuf sb( STDERR_FILENO ) );

}


void logstreambuf_test::test_overloaded_constructor_fail() {

	// this will throw an invalid file descriptor exception
	CPPUNIT_ASSERT_THROW( logstreambuf sb( -1 ), logexception );

}


void logstreambuf_test::test_lpriority() {

	// log stream buffer
	logstreambuf sb;

	// set priority to info and assert that default priority is debug
	CPPUNIT_ASSERT( priority::debug == sb.lpriority( priority::info ) );

	// set priority to error and assert that last priority is info
	CPPUNIT_ASSERT( priority::info == sb.lpriority( priority::err ) );

}


void logstreambuf_test::test_setlogmask() {

	// log stream buffer
	logstreambuf sb;

	// set 'debug' mask and assert that default mast if 'emerg'
	CPPUNIT_ASSERT( priority::mask::emerg == sb.setlogmask( priority::mask::debug ) );

	// set the mask to 0 and assert that last mask is 'debug'
	CPPUNIT_ASSERT( priority::mask::debug == sb.setlogmask( 0 ) );

	// set the mask to 0 and assert that it is still 'debug'
	CPPUNIT_ASSERT( priority::mask::debug == sb.setlogmask( 0 ) );

}


void logstreambuf_test::test_setlogmask_complex() {

	// log stream buffer
	logstreambuf sb;

	// set mask
	sb.setlogmask( priority::mask::emerg | priority::mask::crit );

	// assert
	CPPUNIT_ASSERT( ( priority::mask::emerg | priority::mask::crit ) == sb.setlogmask( 0 ));

}

