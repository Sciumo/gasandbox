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
		}
		else if (!strcmpnc(entryname, "cam")) {		// cam
			if ((sscanf(line, "%s %d", entryname, &camIdx) != 2)) {err = -1;break;	}
			if (camIdx >= (int)cameras.size()) {err = -1;break;	}
		}
		else if (!strcmpnc(entryname, "orientation")) {		// orientation
			size_t skipNb = strlen("orientation") + 1;
			if (strlen(line) <= skipNb) {err = -1;break;	}
			char *rotorStr = line + skipNb;

			try {
				rotor R = _rotor(e3ga::parseMVString(rotorStr));
				cameras[camIdx].setR(R);
			} catch (const std::string &str) {
				printf("%s\n", str.c_str());
				err = -1;break;
			}
		}
		else if (!strcmpnc(entryname, "translation")) {		// translation
			size_t skipNb = strlen("translation") + 1;
			if (strlen(line) <= skipNb) {err = -1;break;	}
			char *vectorStr = line + skipNb;

			try {
				vector t = _vector(e3ga::parseMVString(vectorStr));
				cameras[camIdx].m_t = t;
			} catch (const std::string &str) {
				printf("%s\n", str.c_str());
				err = -1;break;
			}
		}
		else if (!strcmpnc(entryname, "frame")) {		// frame
			// frame idx visible X3 vector
			// e.g.: frame 0 1 1.489079 0.3517250121*e1 - 0.2088123262*e2 - 1.0000000000*e3
			unsigned int frameIdx, frameVisible;
			double X3;
			e3ga::vector t;

			// get frameidx, frameVisible, X3
			if ((sscanf(line, "%s %d %d %f", entryname, &frameIdx, &frameVisible, &X3) != 4)) {
				err = -1;break;
			}

			// find start of 't':
			const char *tStr = NULL;
			{
				int idx = 0;
				for (int i = 0; i < 4; i++) {
					while (line[idx] > ' ') idx++;
					while (line[idx] <= ' ') idx++;
				}
				tStr = line + idx;
				try {
					t = _vector(e3ga::parseMVString(tStr));
				} catch (const std::string &str) {
					printf("%s\n", str.c_str());
					err = -1;break;
				}
			}

			// resize nb frames, if required:
			if (frameIdx >= cameras[camIdx].getNbFrames()) {
				cameras[camIdx].setNbFrames(frameIdx + 1);
			}

			cameras[camIdx].m_visible[frameIdx] = (frameVisible != 0);
			cameras[camIdx].m_X3[frameIdx] = (mv::Float)X3;
			cameras[camIdx].m_pt[frameIdx] = t;

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


	return State(cameras);
}
