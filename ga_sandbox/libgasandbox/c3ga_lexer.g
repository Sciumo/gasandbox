
// Generated on 2007-08-08 10:16:05 by G2 0.1 from 'E:\gasandbox\ga_sandbox\libgasandbox\c3ga.gs2'

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



header "pre_include_cpp" {
	#include <iostream>
		#include <antlr/SemanticException.hpp>
		#include <antlr/String.hpp>
		#include "c3ga.h"
		using namespace std;
}


options {
	mangleLiteralPrefix = "TK_";
	language="Cpp";
	namespace = "c3ga";
}

class c3ga_mv_lexer extends Lexer;
options {
	k=4;
	exportVocab=c3ga_mv_lexer;
	charVocabulary = '\3'..'\377';
	interactive = false;
	genHashLines=false;
	testLiterals = true;
}

WS_	: (' ' |	'\t' | '\n'	{newline();} | '\r') { _ttype = antlr::Token::SKIP; };

MINUS : "-";

PLUS : "+";

GP : "*";

OP : "^";


BASIS_VECTOR options {paraphrase = "a basis vector";}: ("no" | "e1" | "e2" | "e3" | "ni");

/*
Todo: if you could supply this small piece of lexer code for
their custom types (as long as it doesn't cause ambiguity with the 
other rules), then GA strings over any type could be parsed....
*/
protected
	INT : ('0'..'9')+ ;
NUMBER options {paraphrase = "a scalar";} : (INT ('.' INT)? | '.' INT) (('e' | 'E') ('+' | '-')? INT)?;

