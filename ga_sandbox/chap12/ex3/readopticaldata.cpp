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

#include "readopticaldata.h"
#include <libgasandbox/c3ga_parse.h>
#include "opticaldata.h"

// Ancient code; reads optical capture data text file  (did not want to use XML->creates another library dependency. . .)


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

OpticalCaptureData readOpticalData(const std::string &filename) {
	const int maxLineLength = 1024;
	char line[maxLineLength];
	int lineNumber = 0, nTabs, l;
	int err = 0;
	FILE *F;
	char entryname[256];
	int nbCams = 0;
	int camIdx = 0;
	OpticalCaptureData OCD;
	OpticalCaptureCameraData *cam = NULL;
	int nbFrames = 0;


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
			OCD.m_cameraData.resize(nbCams);
		}
		else if (!strcmpnc(entryname, "nbFrames")) {		// nbFrames
			if ((sscanf(line, "%s %d", entryname, &nbFrames) != 2)) {err = -1;break;	}
		}
		else if (!strcmpnc(entryname, "cam")) {		// cam
			if ((sscanf(line, "%s %d", entryname, &camIdx) != 2)) {err = -1;break;	}
			if (camIdx >= nbCams) {err = -1;break;	}
			cam = &(OCD.m_cameraData[camIdx]);
			cam->m_2Dmarkers.resize(nbFrames); // set # frames
			printf("Reading data for camera %d/%d\n", camIdx+1, nbCams);
		}
		else if (!strcmpnc(entryname, "xf")) {		// xf
			size_t skipNb = strlen("xf") + 1;
			if (strlen(line) <= skipNb) {err = -1;break;	}
			char *versorStr = line + skipNb;

			try {
				cam->m_XF = c3ga::_TRversor(c3ga::parseMVString(versorStr));
				cam->m_XFi = c3ga::_TRversor(inverse(cam->m_XF));
			} catch (const std::string &str) {
				printf("%s\n", str.c_str());
				err = -1;break;
			}
		}
		else if (!strcmpnc(entryname, "frame")) {		// frame
			// frame idx image_plane_pt
			// e.g.: frame 2 1.000000*no + 0.297491*e1 - 0.045351*e2 + 0.045279*ni
			int frameIdx;

			// get frameidx
			if ((sscanf(line, "%s %d", entryname, &frameIdx) != 2)) {
				err = -1;break;
			}

			// find start of image point:
			const char *ptStr = NULL;
			{
				int idx = 0;
				for (int i = 0; i < 2; i++) {
					while (line[idx] > ' ') idx++;
					while (line[idx] <= ' ') idx++;
				}
				ptStr = line + idx;

				try {
					c3ga::normalizedPoint _pt = c3ga::_normalizedPoint(c3ga::parseMVString(ptStr));
					if ((frameIdx < 0) || (frameIdx >= (int)cam->m_2Dmarkers.size())) {
						err = -1;break;
					}

					// translate over -e3 (hack) + convert to world frame
					c3ga::dualSphere pt = c3ga::_dualSphere(cam->m_XF * (_pt-c3ga::e3) * cam->m_XFi);

					// set marker in array:
					cam->m_2Dmarkers[frameIdx].push_back(
						h3ga::normalizedPoint(h3ga::normalizedPoint_e1_e2_e3_e0f1_0, pt.e1(), pt.e2(), pt.e3())); // e3 = -1.0f
				} catch (const std::string &str) {
					printf("%s\n", str.c_str());
					err = -1;break;
				}
			}

		}
		else {
			//printf("warning: readOpticalData(): Unknown entry '%s' at line '%d'\n", entryname, lineNumber);
		}

	}
	fclose(F);

	if (err) {
		// error detected:
		char buf[1024];
		sprintf(buf, "readOpticalData(): Invalid entry '%s' at line %d\n", entryname, lineNumber);
		throw std::string(buf);
	}

	// post process all cameras:
	for (unsigned int c = 0; c < OCD.m_cameraData.size(); c++) {
		OpticalCaptureCameraData &C = OCD.m_cameraData[c];

		// factor XF intro translation, rotation, convert to h3ga
		const c3ga::TRversor &V = C.m_XF;
		c3ga::rotor R = c3ga::_rotor(-c3ga::no << (V * c3ga::ni));
		c3ga::vectorE3GA t = c3ga::_vectorE3GA(-2.0f * (c3ga::no << V) * c3ga::inverse(R));
		C.m_position = h3ga::normalizedPoint(h3ga::normalizedPoint_e1_e2_e3_e0f1_0, t.getC(c3ga::vectorE3GA_e1_e2_e3));
		C.m_orientation = h3ga::rotor(h3ga::rotor_scalar_e1e2_e2e3_e3e1, R.getC(c3ga::rotor_scalar_e1e2_e2e3_e3e1));

		// compute image plane, convert to h3ga
		c3ga::plane P = c3ga::_plane(c3ga::unit_r(C.m_XF * (c3ga::e3 - c3ga::ni) * C.m_XFi));
		C.m_imagePlane = h3ga::plane(h3ga::plane_e1e2e3_e1e2e0_e2e3e0_e3e1e0,
			P.e1e2e3ni(), P.e1e2noni(), P.e2e3noni(), -P.e1e3noni());
	}


	return OCD;
}
