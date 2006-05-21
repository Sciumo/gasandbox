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

// Daniel Fontijne -- fontijne@science.uva.nl

#include <stdio.h>
#include <stdlib.h>

#include "readcalibrationdata.h"
#include <libgasandbox/e3ga_util.h>
#include <libgasandbox/e3ga_parse.h>

// Ancient code; reads calibration text file  (did not want to use XML->creates another library dependency. . .)

using namespace extCalibRefine;
using namespace e3ga;

namespace {
// string compare without case
inline int strcmpnc(const char *s1, const char *s2) {
#ifdef WIN32
	return stricmp(s1, s2);
#else // the rest of the world:
	return strcasecmp(s1, s2);
#endif
}

/*
reads line up to and including newline character
returns line _excluding_ newline character in 'buf'
return length of line, or negative on failure
removes crap from end of line
returns number of tabs a start of line
removes crap from start of line
'n' is the maximum length of this line
*/
int read_line(FILE *F, char *buf, int n, int *ntabs) {
	int i;
	if (fgets(buf, n-1, F) == 0) {
		buf[0] = 0;
		return -1;
	}
	n = (int)strlen(buf);
	while ((n>0) && (buf[n-1] <= 32)) n--;
	buf[n] = 0;

	*ntabs = i = 0;
	while ((buf[i] <= 32) && (i < n)) {
		if (buf[i] == '\t') (*ntabs)++;
		i++;
	}

	memmove(buf, buf + i, n - i + 1);

	return (n) ? (n-1) : 0;
}

/*
Returns true if 'line' is an empty line
*/
bool empty_line(const char *line) {
	return ((line[0] == '#') || (line[0] == '\0'));
}


} /* end of anon. namespace */

State readCalibrationData(const std::string &filename) {
	const int maxLineLength = 1024;
	char line[maxLineLength];
	int lineNumber = 0, nTabs, l;
	int err = 0;
	FILE *F;
	char entryname[256];
	int nbCams = 0;
	int camIdx = 0;
	std::vector<Camera> cameras;

	if ( (F = fopen(filename.c_str(), "rb")) == NULL) {
		throw "readCalibrationData(): can not open '" + filename + "'";
	}

	while (!feof(F)) {
		if ( (l = read_line(F, line, maxLineLength, &nTabs)) < 0) {
			break;
		}
		lineNumber++;
		if (empty_line(line)) continue;

		if (sscanf(line, "%s ", entryname) != 1) continue;

//		printf("Entry: %s\n", entryname);

		if (!strcmpnc(entryname, "nbCams")) {		// nbCams
			if ((sscanf(line, "%s %d", entryname, &nbCams) != 2)) {err = -1;break;	}
			cameras.resize(nbCams);
			printf("%d cameras\n", nbCams);
		}
		else if (!strcmpnc(entryname, "cam")) {		// cam
			if ((sscanf(line, "%s %d", entryname, &camIdx) != 2)) {err = -1;break;	}
			if (camIdx >= (int)cameras.size()) {err = -1;break;	}
			printf("camera %d\n", camIdx);
		}
		else if (!strcmpnc(entryname, "orientation")) {		// orientation
			size_t skipNb = strlen("orientation") + 1;
			if (strlen(line) <= skipNb) {err = -1;break;	}
			char *rotorStr = line + strlen("orientation") + 1;
			printf("rotor: %s\n", rotorStr);

			try {
				rotor R = _rotor(parseMVString(rotorStr));
				cameras[camIdx].setR(R);
			} catch (const std::string &str) {
				printf("%s\n", str.c_str());
				err = -1;break;
			}


		}
		else {
			//printf("warning: readCalibrationData(): Unknown entry '%s' at line '%d'\n", entryname, lineNumber);
		}

	}
	fclose(F);

	if (err) {
		// error detected:
		char buf[1024];
		sprintf(buf, "readCalibrationData(): Invalid entry '%s' at line %d\n", entryname, lineNumber);
		throw std::string(buf);
	}


	return State();
}
