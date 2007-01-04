// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


// Copyright 2007, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#include <iostream>
#include <string>
#include <sstream>

#include "c2ga_parse.h"
#include "c2ga_mv_lexer.hpp"
#include "c2ga_mv_parser.hpp"

namespace c2ga {

c2ga::mv parseMVString(const std::string &str) {
 	try {
 		std::istringstream inputStream(str);
 		c2ga::c2ga_mv_lexer lex(inputStream);

 		c2ga::c2ga_mv_parser par(lex);
 		return par.multivector();
 	} catch (...) {
 		throw std::string("parseMVString(): could not parse: " + str);
 	}
}

} /* end of namespace c2ga */
