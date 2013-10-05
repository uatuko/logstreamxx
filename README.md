logstreamxx
===========

C++ logging library based on standard stream classes

logstreamxx is a small and simple log library which provides a STL stream output
operator (`<<`) interface for logging. This library is not thread-safe and not
intended to provide advanced features similar to other C++ logging libraries that
are closer to log4j (log4cxx, log4cpp etc.).


##### Example usage:
```cpp
// log stream
logstreamxx::logstream logger;

logger << "default is to log at debug level" << std::endl;
logger << "24 in hex: " << std::hex << 24 << std::endl;
logger << "24 in oct: " << std::oct << 24 << std::endl;

logger << logstreamxx::priority::info << "this is logged at info level" << std::endl;
logger << "this will also be in info level" << std::endl;
```

Above code block would output the following to `STDOUT`;
```
Oct  3 20:31:22.190010 [DEBG] default is to log at debug level
Oct  3 20:31:22.190611 [DEBG] 24 in hex: 18
Oct  3 20:31:22.190624 [DEBG] 24 in oct: 30
Oct  3 20:31:22.190634 [INFO] this is logged at info level
Oct  3 20:31:22.190643 [INFO] this will also be in info level
```


### Dependencies

* CppUnit >= 1.12.1 (for unit tests)
* Doxygen (for doxygen documentation, of course)


### Bugs and Feature Requests

Please report all bugs and feature requests in [bugzilla](http://bugs.geniusse.com/) under the
[logstreamxx](http://bugs.geniusse.com/enter_bug.cgi?product=logstreamxx) project.
Known issues can be found [here](http://bugs.geniusse.com/buglist.cgi?query_format=specific&order=relevance%20desc&bug_status=__open__&product=logstreamxx).


### Version history

__0.0.1__ - _05th October 2013_
*   Initial release


### Copyright and License

Copyright (C) 2013 Uditha Atukorala.

This software library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This software library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
[GNU Lesser General Public License](http://www.gnu.org/licenses/lgpl.html)
for more details.

