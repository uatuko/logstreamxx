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

#ifndef LOGSTREAMXX_PRIORITY_H
#define LOGSTREAMXX_PRIORITY_H


namespace logstreamxx {

	/**
	*   @brief Log priorities helper class
	*
	*   This class defines the types, structures and helper methods
	*   related to log priorities.
	*
	*/
	class priority {
	public:

		/**
		*   @brief log priorities type
		*
		*   These directly correlates to syslog(3) priorities.
		*
		*/
		enum log_priority_t {
			emerg    = 0,    //!< system is unusable
			alert    = 1,    //!< action must be taken immediately
			crit     = 2,    //!< critical conditions
			err      = 3,    //!< error conditions
			warning  = 4,    //!< warning conditions
			notice   = 5,    //!< normal, but significant, condition
			info     = 6,    //!< informational message
			debug    = 7     //!< debug-level message
		};

		/**
		*   @brief convert log priority value into readable text
		*   @return text value of the log priority
		*
		*   This helper method maps priority::log_priority_t values into
		*   readable text and returns a C style char pointer.
		*
		*/
		static const char * text( const log_priority_t &p ) {

			// priority value to text mapping
			static char priority_name[8][5] = {
				"EMRG",
				"ALRT",
				"CRIT",
				"EROR",
				"WARN",
				"NTCE",
				"INFO",
				"DEBG"
			};

			return priority_name[p];

		}

	};

} /* end of namespace logstreamxx */

#endif /* !LOGSTREAMXX_PRIORITY_H */

