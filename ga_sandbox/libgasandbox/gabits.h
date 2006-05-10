// This program is fee software; you can redistribute it and/or
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


#ifndef _GA_BITS_H_
#define _GA_BITS_H_

/**
    * returns the number of 1 bits in 'i'
    */
inline int bitCount32(int i) {
	// Note that unsigned shifting (>>>) is not required.
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	i = (i + (i >> 4)) & 0x0F0F0F0F;
	i = i + (i >> 8);
	i = i + (i >> 16);
	return i & 0x0000003F;
}

/**
    * returns the number of 1 bits in 'i'
    */
inline int bitCount16(int i) {
	// Note that unsigned shifting (>>>) is not required.
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	i = (i + (i >> 4)) & 0x0F0F0F0F;
	i = i + (i >> 8);
	return i & 0x0000001F;
}


#endif /* _GA_BITS_H_ */
