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

#include <logstreamxx/logstream.h>
#include <logstreamxx/priority.h>


int main() {

	// log stream
	logstreamxx::logstream logger;

	// set log output level
	logger.loglevel( logstreamxx::priority::debug );

	logger << "default is to log at debug level" << std::endl;
	logger << "24 in hex: " << std::hex << 24 << std::endl;
	logger << "24 in oct: " << std::oct << 24 << std::endl;

	logger << logstreamxx::priority::info << "this is logged at info level" << std::endl;
	logger << "this will also be in info level" << std::endl;

	return 0;

}

