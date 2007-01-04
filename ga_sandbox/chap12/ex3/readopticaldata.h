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

#ifndef _READ_OPTICAL_DATA_H_
#define _READ_OPTICAL_DATA_H_

#include <string>
#include "opticaldata.h"

// Ancient code; reads calibration text file  (did not want to use XML->creates another library dependency. . .)

/** reads calibration text file, throws std::string on error, otherwise returns optical capture data */
OpticalCaptureData readOpticalData(const std::string &filename);


#endif /* _READ_OPTICAL_DATA_H_ */
