
// Generated on 2007-01-08 11:07:19 by G2 0.1 from 'E:\ga\ga_sandbox\ga_sandbox\libgasandbox\c3ga.gs2'

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


#include <stdio.h> /* required to save profile */
#include <stdlib.h> /* required to save profile */
	#include <time.h> /* required to save profile */

	#ifdef WIN32
	#include <winsock2.h>
	#else /* UNIX */
	#include <errno.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <sys/time.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <fcntl.h>
	#endif // WIN32 / UNIX?


	#include <string.h>
	#include "c3ga.h"

	// pre_cpp_include


	namespace c3ga {

	// The dimension of the space:
	const int mv_spaceDim = 5;

	// Is the metric of the space Euclidean?
	const bool mv_metricEuclidean = false;


	// This array can be used to lookup the number of coordinates for a grade part of a general multivector
	const int mv_gradeSize[6] = {
		1, 5, 10, 10, 5, 1 
	};

	// This array can be used to lookup the number of coordinates based on a grade usage bitmap
	const int mv_size[64] = {
		0, 1, 5, 6, 10, 11, 15, 16, 10, 11, 15, 16, 20, 21, 25, 26, 5, 6, 10, 11, 15, 16, 20, 21, 15, 16, 20, 21, 25, 26, 30, 31, 1, 2, 6, 7, 11, 12, 16, 17, 11, 12, 16, 17, 21, 22, 26, 27, 6, 7, 11, 12, 16, 17, 21, 22, 16, 17, 21, 22, 26, 27, 31, 32 
	};

	// This array of ASCIIZ strings contains the names of the basis vectors
	const char *mv_basisVectorNames[5] = {
		"no", "e1", "e2", "e3", "ni" 
	};

	// This array of integers contains the order of basis elements in the general multivector
	const int mv_basisElements[32][6] = {
		{-1}
		, {0, -1}
		, {1, -1}
		, {2, -1}
		, {3, -1}
		, {4, -1}
		, {0, 1, -1}
		, {0, 2, -1}
		, {0, 3, -1}
		, {1, 2, -1}
		, {2, 3, -1}
		, {1, 3, -1}
		, {1, 4, -1}
		, {2, 4, -1}
		, {3, 4, -1}
		, {0, 4, -1}
		, {2, 3, 4, -1}
		, {1, 3, 4, -1}
		, {1, 2, 4, -1}
		, {0, 3, 4, -1}
		, {0, 1, 4, -1}
		, {0, 2, 4, -1}
		, {0, 2, 3, -1}
		, {0, 1, 3, -1}
		, {0, 1, 2, -1}
		, {1, 2, 3, -1}
		, {1, 2, 3, 4, -1}
		, {0, 2, 3, 4, -1}
		, {0, 1, 3, 4, -1}
		, {0, 1, 2, 4, -1}
		, {0, 1, 2, 3, -1}
		, {0, 1, 2, 3, 4, -1}
	};

	// This array of integers contains the 'sign' (even/odd permutation of the canonical order) of basis elements in the general multivector
	const double mv_basisElementSign[32] = {
		1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0, 1.0, 1.0, 1.0 
	};

	// This array of integers contains the order of basis elements in the general multivector
	// Use it to answer: 'at what index do I find basis element [x] (x = basis vector bitmap)?
	const int mv_basisElementIndexByBitmap[32] = {
		0, 1, 2, 6, 3, 7, 9, 24, 4, 8, 11, 23, 10, 22, 25, 30, 5, 15, 12, 20, 13, 21, 18, 29, 14, 19, 17, 28, 16, 27, 26, 31 
	};

	// This array of integers contains the indices of basis elements in the general multivector
	// Use it to answer: 'what basis element do I find at index [x]'?
	const int mv_basisElementBitmapByIndex[32] = {
		0, 1, 2, 4, 8, 16, 3, 5, 9, 6, 12, 10, 18, 20, 24, 17, 28, 26, 22, 25, 19, 21, 13, 11, 7, 14, 30, 29, 27, 23, 15, 31 
	};




	// These strings determine how the output of string() is formatted.
	// You can alter them at runtime using mv_setStringFormat().

	const char *mv_string_fp = "%2.2f"; 
	const char *mv_string_start = ""; 
	const char *mv_string_end = ""; 
	const char *mv_string_mul = "*"; 
	const char *mv_string_wedge = "^"; 
	const char *mv_string_plus = " + "; 
	const char *mv_string_minus = " - "; 

	void mv_setStringFormat(const char *what, const char *format) {

		if (!strcmp(what, "fp")) 
			mv_string_fp = (format) ? format : "%2.2f"; 
		else if (!strcmp(what, "start")) 
			mv_string_start = (format) ? format : ""; 
		else if (!strcmp(what, "end")) 
			mv_string_end = (format) ? format : ""; 
		else if (!strcmp(what, "mul")) 
			mv_string_mul = (format) ? format : "*"; 
		else if (!strcmp(what, "wedge")) 
			mv_string_wedge = (format) ? format : "^"; 
		else if (!strcmp(what, "plus")) 
			mv_string_plus = (format) ? format : " + "; 
		else if (!strcmp(what, "minus")) 
			mv_string_minus = (format) ? format : " - ";	else {
			char msg[1024];
			sprintf(msg, "invalid argument to mv_setStringFormat(): %s", what);
			mv_throw_exception(msg, MV_EXCEPTION_WARNING);
		}

	}


	namespace g2Net {
		void closeSocket(int *sock) {
			if (*sock == -1) return;
			#ifdef WIN32
				closesocket(*sock);
			#else
				close(*sock);
			#endif
				*sock = -1;
		}

		void  setSocketNonBlocking(int sock) {
			#ifdef WIN32
				u_long arg = 1;
			ioctlsocket(sock, FIONBIO, &arg);
			#else
				int currentValue;
			currentValue = fcntl(sock, F_GETFL, 0);
			fcntl(sock, F_SETFL, currentValue | O_NONBLOCK);
			#endif
		}

		bool wouldBlock() {
			#ifdef WIN32
				return ((WSAGetLastError() == WSAEWOULDBLOCK) ? true : false);
			#else
				return ((errno == EWOULDBLOCK) ? true : false);
			#endif
		}

		// this function disables the Nagle algorithm for the given port
		void disableNagle(int sock) {
			int nodelay = 1;
			setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&nodelay, sizeof(int));
		}

		// this function sets the TCP send/receive buffer to some size
		void setRecvBuffer(int sock, int size) {
			setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&size, sizeof(int));
		}
		// this function sets the TCP send/receive buffer to some size
		void setSendBuffer(int sock, int size) {
			setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&size, sizeof(int));
		}

		int recvN(int sock, const unsigned char *buf, int n) {
			int idx = 0;
			while (idx < n) {
				int nbRecv = (int)recv(sock, (char*)buf + idx, n-idx, 0);
				if (nbRecv < 0) return nbRecv;
				else idx += nbRecv;
			}
			return n;
		}

		int sendN(int sock, const unsigned char *buf, int n) {
			int idx = 0;
			while (idx < n) {
				int nbSent = (int)send(sock, (char*)buf + idx, n-idx, 0);
				if (nbSent < 0) return nbSent;
				else idx += nbSent;
			}
			return n;
		}

		int serialize_uint(int forReal, unsigned char *dest, unsigned int idx, unsigned int value) {
			int i;
			if (forReal) {
				int wordSize = sizeof(unsigned int);
				for (i = 0; i < wordSize; i++)
				dest[idx + i] = (value >> ((wordSize - i - 1) << 3)) & 0xff;
			}
			return sizeof(unsigned int);
		}

		int serialize_ushort(int forReal, unsigned char *dest, unsigned int idx, unsigned short value) {
			int i;
			if (forReal) {
				int wordSize = sizeof(unsigned short);
				for (i = 0; i < wordSize; i++)
				dest[idx + i] = (value >> ((wordSize - i - 1) << 3)) & 0xff;
			}
			return sizeof(unsigned short);
		}

		int deserialize_uint(const unsigned char *source, unsigned int idx, unsigned int *value) {
			int i;
			int wordSize = sizeof(unsigned int);
			*value = 0;
			for (i = 0; i < wordSize; i++)
			*value |= (source[idx + i] << ((wordSize - i - 1) << 3));
			return sizeof(unsigned int);
		}

		int deserialize_ushort(const unsigned char *source, unsigned int idx, unsigned short *value) {
			int i;
			int wordSize = sizeof(unsigned short);
			*value = 0;
			for (i = 0; i < wordSize; i++)
			*value |= (unsigned short)(source[idx + i] << ((wordSize - i - 1) << 3));
			return sizeof(unsigned short);
		}


		void init() {
			#ifdef WIN32
				WORD wVersionRequested;
			WSADATA wsaData;
			int WSAerr; 

			static bool initDone = false;
			if (initDone) return;
			initDone = true;
			#endif /* WIN32 */

				#ifdef WIN32
				wVersionRequested = MAKEWORD( 2, 0 ); 
			WSAerr = WSAStartup( wVersionRequested, &wsaData );
			if ( WSAerr != 0 )
				throw std::string("init(): an error occured during WSAStartup() (%d)", WSAerr);
			#endif /* WIN32 */
		}

	} // end of namespace g2Net


	namespace g2Profiling {
		namespace { // anonymous namespace for profiling code:

			// todo: multithreading (mutex, etc)


			const char *g_functionNames[] = {
				// function names of G2 functions:
				"", // 0 
					"mv lcont(mv x, mv y)", // 1 
					"mv scp(mv x, mv y)", // 2 
					"mv gp(mv x, mv y)", // 3 
					"mv gpEM(mv x, mv y)", // 4 
					"mv scpEM(mv x, mv y)", // 5 
					"mv lcontEM(mv x, mv y)", // 6 
					"mv op(mv x, mv y)", // 7 
					"mv add(mv x, mv y)", // 8 
					"mv subtract(mv x, mv y)", // 9 
					"scalar norm_e2(mv x)", // 10 
					"scalar norm_e(mv x)", // 11 
					"mv unit_e(mv x)", // 12 
					"scalar norm_r2(mv x)", // 13 
					"scalar norm_r(mv x)", // 14 
					"mv unit_r(mv x)", // 15 
					"mv reverse(mv x)", // 16 
					"mv negate(mv x)", // 17 
					"mv dual(mv x)", // 18 
					"mv undual(mv x)", // 19 
					"mv inverse(mv x)", // 20 
					"mv inverseEM(mv x)", // 21 
					"mv apply_om(om x, mv y)", // 22 
					"mv gradeInvolution(mv x)", // 23 
					"void set(om __x__, point __image_of_no__, point __image_of_e1__, point __image_of_e2__, point __image_of_e3__, point __image_of_ni__)", // 24 
					"void set(om __x__, omFlatPoint __y__)", // 25 
					"void set(omFlatPoint __x__, point __image_of_e1__, point __image_of_ni__, point __image_of_e2__, point __image_of_e3__, point __image_of_no__)", // 26 
					"void set(omFlatPoint __x__, flatPoint image_ofe1ni, flatPoint image_ofe2ni, flatPoint image_ofe3ni, flatPoint image_ofnoni)", // 27 
					"void set(omFlatPoint __x__, om __y__)", // 28 
					// function names for underscore constructors for specialized types
					"__NON_G2__ _no_t(mv arg1)", // 29 
					"__NON_G2__ _e1_t(mv arg1)", // 30 
					"__NON_G2__ _e2_t(mv arg1)", // 31 
					"__NON_G2__ _e3_t(mv arg1)", // 32 
					"__NON_G2__ _ni_t(mv arg1)", // 33 
					"__NON_G2__ _scalar(mv arg1)", // 34 
					"__NON_G2__ _noni_t(mv arg1)", // 35 
					"__NON_G2__ _point(mv arg1)", // 36 
					"__NON_G2__ _normalizedPoint(mv arg1)", // 37 
					"__NON_G2__ _flatPoint(mv arg1)", // 38 
					"__NON_G2__ _normalizedFlatPoint(mv arg1)", // 39 
					"__NON_G2__ _pointPair(mv arg1)", // 40 
					"__NON_G2__ _line(mv arg1)", // 41 
					"__NON_G2__ _dualLine(mv arg1)", // 42 
					"__NON_G2__ _plane(mv arg1)", // 43 
					"__NON_G2__ _dualPlane(mv arg1)", // 44 
					"__NON_G2__ _circle(mv arg1)", // 45 
					"__NON_G2__ _sphere(mv arg1)", // 46 
					"__NON_G2__ _dualSphere(mv arg1)", // 47 
					"__NON_G2__ _normalizedSphere(mv arg1)", // 48 
					"__NON_G2__ _normalizedDualSphere(mv arg1)", // 49 
					"__NON_G2__ _freeVector(mv arg1)", // 50 
					"__NON_G2__ _freeBivector(mv arg1)", // 51 
					"__NON_G2__ _freeTrivector(mv arg1)", // 52 
					"__NON_G2__ _tangentVector(mv arg1)", // 53 
					"__NON_G2__ _tangentBivector(mv arg1)", // 54 
					"__NON_G2__ _vectorE2GA(mv arg1)", // 55 
					"__NON_G2__ _vectorE3GA(mv arg1)", // 56 
					"__NON_G2__ _bivectorE3GA(mv arg1)", // 57 
					"__NON_G2__ _TRversorLog(mv arg1)", // 58 
					"__NON_G2__ _TRSversorLog(mv arg1)", // 59 
					"__NON_G2__ _TRversor(mv arg1)", // 60 
					"__NON_G2__ _TRSversor(mv arg1)", // 61 
					"__NON_G2__ _evenVersor(mv arg1)", // 62 
					"__NON_G2__ _translator(mv arg1)", // 63 
					"__NON_G2__ _normalizedTranslator(mv arg1)", // 64 
					"__NON_G2__ _rotor(mv arg1)", // 65 
					"__NON_G2__ _scalor(mv arg1)", // 66 
					"__NON_G2__ ___no_ct__(mv arg1)", // 67 
					"__NON_G2__ ___e1_ct__(mv arg1)", // 68 
					"__NON_G2__ ___e2_ct__(mv arg1)", // 69 
					"__NON_G2__ ___e3_ct__(mv arg1)", // 70 
					"__NON_G2__ ___ni_ct__(mv arg1)", // 71 
					"__NON_G2__ ___noni_ct__(mv arg1)", // 72 
					"__NON_G2__ ___e3ni_ct__(mv arg1)", // 73 
					"__NON_G2__ ___e2ni_ct__(mv arg1)", // 74 
					"__NON_G2__ ___I3_ct__(mv arg1)", // 75 
					"__NON_G2__ ___e1ni_ct__(mv arg1)", // 76 
					"__NON_G2__ ___I5_ct__(mv arg1)", // 77 
					"__NON_G2__ ___I5i_ct__(mv arg1)", // 78 
					// function names for underscore constructors for floats
					"__NON_G2__ _float(mv arg1)", // 79 
					"__NON_G2__ _double(mv arg1)", // 80 
					"__NON_G2__ _Float(mv arg1)", // 81 
					""
			};

			const char *g_typeNames[] = {
				"", // 0 
					"void", // 1 
					"bool", // 2 
					"char", // 3 
					"short", // 4 
					"int", // 5 
					"float", // 6 
					"double", // 7 
					"mv", // 8 
					"om", // 9 
					"no_t", // 10 
					"e1_t", // 11 
					"e2_t", // 12 
					"e3_t", // 13 
					"ni_t", // 14 
					"scalar", // 15 
					"noni_t", // 16 
					"point", // 17 
					"normalizedPoint", // 18 
					"flatPoint", // 19 
					"normalizedFlatPoint", // 20 
					"pointPair", // 21 
					"line", // 22 
					"dualLine", // 23 
					"plane", // 24 
					"dualPlane", // 25 
					"circle", // 26 
					"sphere", // 27 
					"dualSphere", // 28 
					"normalizedSphere", // 29 
					"normalizedDualSphere", // 30 
					"freeVector", // 31 
					"freeBivector", // 32 
					"freeTrivector", // 33 
					"tangentVector", // 34 
					"tangentBivector", // 35 
					"vectorE2GA", // 36 
					"vectorE3GA", // 37 
					"bivectorE3GA", // 38 
					"TRversorLog", // 39 
					"TRSversorLog", // 40 
					"TRversor", // 41 
					"TRSversor", // 42 
					"evenVersor", // 43 
					"translator", // 44 
					"normalizedTranslator", // 45 
					"rotor", // 46 
					"scalor", // 47 
					"__no_ct__", // 48 
					"__e1_ct__", // 49 
					"__e2_ct__", // 50 
					"__e3_ct__", // 51 
					"__ni_ct__", // 52 
					"__noni_ct__", // 53 
					"__e3ni_ct__", // 54 
					"__e2ni_ct__", // 55 
					"__I3_ct__", // 56 
					"__e1ni_ct__", // 57 
					"__I5_ct__", // 58 
					"__I5i_ct__", // 59 
					"omFlatPoint", // 60 
					""
			};

			const char *g_storageTypeNames[] = {
				"float"
			};

			// each entry records the use of a specific G2 type (profile() sets them to true)
			bool g_usedTypes[] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

			// when the profile is saved, we also save all synthetic types that we used
			// these strings describe what to save:
			const char *g_synMVTypeGS2Strings[] = {
				NULL, // 0 
					NULL, // 1 
					NULL, // 2 
					NULL, // 3 
					NULL, // 4 
					NULL, // 5 
					NULL, // 6 
					NULL, // 7 
					NULL, // 8 
					NULL, // 9 
					NULL, // 10 
					NULL, // 11 
					NULL, // 12 
					NULL, // 13 
					NULL, // 14 
					NULL, // 15 
					NULL, // 16 
					NULL, // 17 
					NULL, // 18 
					NULL, // 19 
					NULL, // 20 
					NULL, // 21 
					NULL, // 22 
					NULL, // 23 
					NULL, // 24 
					NULL, // 25 
					NULL, // 26 
					NULL, // 27 
					NULL, // 28 
					NULL, // 29 
					NULL, // 30 
					NULL, // 31 
					NULL, // 32 
					NULL, // 33 
					NULL, // 34 
					NULL, // 35 
					NULL, // 36 
					NULL, // 37 
					NULL, // 38 
					NULL, // 39 
					NULL, // 40 
					NULL, // 41 
					NULL, // 42 
					NULL, // 43 
					NULL, // 44 
					NULL, // 45 
					NULL, // 46 
					NULL, // 47 
					NULL, // 48 
					NULL, // 49 
					NULL, // 50 
					NULL, // 51 
					NULL, // 52 
					NULL, // 53 
					NULL, // 54 
					NULL, // 55 
					NULL, // 56 
					NULL, // 57 
					NULL, // 58 
					NULL, // 59 
					NULL, // 60 
					NULL
			};	


			class entry {
				friend bool operator==(const entry &E1, const entry &E2);
				public:
					inline entry(unsigned int funcIdx, unsigned short storageTypeIdx, unsigned short nbArg, unsigned short argType[]) : // custom init constructor
					m_count(1), m_funcIdx(funcIdx), m_storageTypeIdx(storageTypeIdx), m_nbArg(nbArg), m_argType(argType), m_deleteArgType(false),
					m_returnType(NULL), m_nbReturnTypes(0) {
				}
				inline entry(unsigned int funcIdx, unsigned short storageTypeIdx, unsigned short nbArg, unsigned short argType[], 
				unsigned short nbReturnType, unsigned short returnType[]) : // custom init constructor
					m_count(1), m_funcIdx(funcIdx), m_storageTypeIdx(storageTypeIdx), m_nbArg(nbArg), m_argType(argType), m_deleteArgType(false),
					m_returnType(NULL), m_nbReturnTypes(nbReturnType) {
					if (nbReturnType != NULL) {
						m_returnType = new unsigned short[m_nbReturnTypes];
						memcpy(m_returnType, returnType, m_nbReturnTypes * sizeof(unsigned short));			
					}
				}

				inline entry(const entry &E) : // copy constructor
				m_count(E.m_count), m_funcIdx(E.m_funcIdx), m_storageTypeIdx(E.m_storageTypeIdx), m_nbArg(E.m_nbArg), m_deleteArgType(true), m_nbReturnTypes(E.m_nbReturnTypes) {
					m_argType = new unsigned short[m_nbArg];
					memcpy(m_argType, E.m_argType, m_nbArg * sizeof(unsigned short));

					if (m_nbReturnTypes) {
						m_returnType = new unsigned short[m_nbReturnTypes];
						memcpy(m_returnType, E.m_returnType, m_nbReturnTypes * sizeof(unsigned short));
					}
					else m_returnType = NULL;
				}

				inline ~entry() {
					if (m_argType && m_deleteArgType) delete[] m_argType;
					if (m_returnType) delete[] m_returnType;
				}

				inline unsigned int hashIndex() const {
					// m_returnType does not contribute to hashIndex!
					unsigned int idx = m_funcIdx ^ ((unsigned int)m_storageTypeIdx << 12) ^ ((unsigned int)m_nbArg << 14);
					for (unsigned int i = 0; i < m_nbArg; i++)
					idx ^= m_argType[i] << (((i+2) & 3) * 8);
					return idx;
				}

				inline unsigned int count() const {
					return m_count;
				}

				inline void addCount(unsigned int count) {
					if ((m_count + count) < count) return; // prevent overflow
					m_count += count;
				}


				inline unsigned int funcIdx() const {return m_funcIdx;}
				inline unsigned short storageTypeIdx() const {return m_storageTypeIdx;}
				inline unsigned short nbArg() const {return m_nbArg;}
				inline unsigned short argType(unsigned int idx) const {
					if (idx >= nbArg()) {
						mv_throw_exception("g2Profiling::entry::argType(): Index out of range", MV_EXCEPTION_ERROR);
						return 0;
					}
					else return m_argType[idx];
				}

				inline void deleteArgType(bool d) {
					m_deleteArgType = d;
				}

				inline unsigned short *returnType() {
					return m_returnType;
				}
				inline unsigned short returnType(int idx) {
					return m_returnType[idx];
				}
				inline unsigned short nbReturnTypes() const {return m_nbReturnTypes;}

				private:
					unsigned int m_funcIdx;
				unsigned short m_storageTypeIdx;
				unsigned short m_nbArg;
				bool m_deleteArgType; // the copy constructor allocates mem for m_argType, the 'custom init' constructor doesn't
				unsigned short *m_argType; // memory allocated with new[], or from stack/caller (in that case, m_deleteArgType is false!) (todo: allocator)
				unsigned int m_count;

				unsigned short m_nbReturnTypes;
				unsigned short *m_returnType; // memory allocated with new[] (or NULL)
			};

			inline bool operator==(const entry &E1, const entry &E2) {
				if (E1.m_nbArg != E2.m_nbArg) return false;
				for (unsigned int i = 0; i < E1.m_nbArg; i++)
				if (E1.m_argType[i] != E2.m_argType[i])
					return false;

				return ((E1.m_funcIdx == E2.m_funcIdx) &&
					(E1.m_storageTypeIdx == E2.m_storageTypeIdx));
			}

			unsigned int g_hashCount = 0; // number of entries in hash table (hash table size is ~doubled when hash table is 'half full')

			class hashBucket {
				public:
					hashBucket() : m_nbEntries(0), m_maxEntries(4) {
					m_entry = new entry*[m_maxEntries];
				}

				~hashBucket() {
					for (unsigned int i = 0; i < m_nbEntries; i++)
					if (m_entry[i]) delete m_entry[i];
					delete[] m_entry;
				}

				entry *findEntry(const entry &E) {
					for (unsigned int i = 0; i < m_nbEntries; i++) {
						if (*(m_entry[i]) == E) {
							return m_entry[i];
						}
					}
					return NULL;
				}


				entry *addEntry(const entry &E) {
					// check if already present:
					{
						entry *X = findEntry(E);
						if (X != NULL) {
							X->addCount(E.count());
							return X;
						}
					}

					// not found: add a new entry:
					{
						// if bucket if full: resize
						if (m_maxEntries == m_nbEntries) {
							m_maxEntries = (m_maxEntries) ? m_maxEntries * 2 : 4;
							entry **oldEntry = m_entry;
							m_entry = new entry*[m_maxEntries];
							memcpy(m_entry, oldEntry, m_nbEntries * sizeof(entry*));
							if (m_entry) {
								delete[] m_entry;
							}
						}

						// add entry to bucket, increment hash count
						entry *X = m_entry[m_nbEntries] = new entry(E);
						m_nbEntries++;
						g_hashCount++;
						return X;
					}
				}

				unsigned int nbEntries() const {return m_nbEntries;}
				inline const entry&operator[](unsigned int idx) {
					if (idx >= m_nbEntries) {
						mv_throw_exception("g2Profiling::hashBucket::operator[](): Index out of range", MV_EXCEPTION_ERROR);
						static entry tmp(0, 0, 0, NULL);
						return tmp;
					}
					else return *(m_entry[idx]);
				}

				private:
				unsigned int m_maxEntries;
				unsigned int m_nbEntries;
				entry **m_entry; // the entries that life in this bucket
			};

			// table of primes, ~*2 each entry ('0' marks the start of the table, '1' marks the end of the table)
			unsigned int g_primes[] = {0, 101, 211, 401, 809, 1601, 3203, 6421, 12809, 25601, 51203, 102407, 204803,  409609,  819229,  1638431,  3276803,  6553621, 1};
			unsigned int g_hashTableSize = 0; // number of buckets in hash table
			hashBucket *g_hashTable = NULL; // memory allocated with new[] (todo: allocator)

			void increaseHashTableSize();
			void reinsertHashTableEntries(unsigned int hashTableSize, hashBucket *hashTable);

			entry *addEntry(const entry &E) {

				if ((g_hashCount+1) * 2 > g_hashTableSize) {
					increaseHashTableSize();
				}

				unsigned int idx = E.hashIndex() % g_hashTableSize;	
				return g_hashTable[idx].addEntry(E);
			}

			entry *findEntry(const entry &E) {
				if (g_hashTableSize == 0) return NULL;
				unsigned int idx = E.hashIndex() % g_hashTableSize;	
				return g_hashTable[idx].findEntry(E);
			}

			void increaseHashTableSize() {
				// find the current idx in the table:
				unsigned int i = 0;
				while ((g_primes[i] != g_hashTableSize) && (g_primes[i] != 1)) i++;

				// get new size (or double capacity when out of primes (unlikely to happen)
				unsigned int newSize = (g_primes[i] == 1) ? g_hashTableSize * 2 : g_primes[i+1];

				// remember old hash talbe:
				unsigned int hashTableSize = g_hashTableSize;
				hashBucket *hashTable = g_hashTable;

				// resize:
				g_hashTableSize = newSize;
				g_hashTable = new hashBucket[g_hashTableSize];

				// reinsert:
				g_hashCount = 0;
				reinsertHashTableEntries(hashTableSize, hashTable); 

				// delete old
				if (hashTable) delete[] hashTable;
			}

			void reinsertHashTableEntries(unsigned int hashTableSize,  hashBucket *hashTable) {
				for (unsigned int i = 0; i < hashTableSize; i++)
				for (unsigned int j = 0; j < hashTable[i].nbEntries(); j++)
				addEntry(hashTable[i][j]);
			}

		} // end of anonymous namespace for profiling code

		int getReturnTypesFromServer(const entry &E, unsigned short returnType[4]);
		// external entry point:
		void profile(unsigned int funcIdx, unsigned short storageTypeIdx, unsigned short nbArg, 
			unsigned short argType[], int nbReturnType, unsigned short returnType[]) {
			// todo: multithreading (lock mutex, etc)
			// mark types as used:
			bool usedGMV = false;
			unsigned short usedGMVtype = 0;
			for (int i = 0; i < nbArg; i++) {
				if (argType[i] < 61)
					g_usedTypes[argType[i]] = true;

				if (argType[i] == MVT_NONE) usedGMV = true; // is this line required?
				if (argType[i] == MVT_MV) {
					usedGMV = true;
					usedGMVtype = argType[i];
				}
			}
			if (usedGMV) { //  a DSL function that is invoked with GMV argument can never be specialized / optimized
				for (int i = 0; i < nbReturnType; i++) {
					returnType[i] = usedGMVtype;
				}
				return;
			}

			entry *E; // E gets set either by findEntry() or by addEntry()
			entry tempEntry(funcIdx, storageTypeIdx, nbArg, argType);
			if ( (E = findEntry(tempEntry)) == NULL) {
				unsigned short nbReturnTypeServer = 0;
				unsigned short returnTypeServer[4] = {(unsigned short)MVT_NONE, (unsigned short)MVT_NONE, (unsigned short)MVT_NONE, (unsigned short)MVT_NONE};
				nbReturnTypeServer = getReturnTypesFromServer(tempEntry, returnTypeServer);


				// ask server for return types
				// add entry
				E = addEntry(entry(funcIdx, storageTypeIdx, nbArg, argType, nbReturnTypeServer, returnTypeServer));
			}

			if (returnType == NULL) return;
			else {
				int maxNbR = (E == NULL) ? 0 : E->nbReturnTypes();
				for (int i = 0; i < nbReturnType; i++) {
					if (i < maxNbR)
						returnType[i] = E->returnType(i);
					else returnType[i] = (unsigned short)MVT_NONE;
				}
			}
			// todo: multithreading (release mutex, etc)
		}

		// external entry point:
		void reset() {
			// todo: multithreading (lock mutex, etc)	
			g_hashCount = 0;
			g_hashTableSize = 0;
			if (g_hashTable) {
				delete[] g_hashTable;
				g_hashTable = NULL;
			}
			// todo: multithreading (release mutex, etc)
		}

		int g_profileNetSocket = -1;
		/** must be called in order for network profiling to work */
		void init(const char *gp2Filename /*= "E:\\ga\\ga_sandbox\\ga_sandbox\\libgasandbox\\c3ga.gp2"*/,
			const char *hostName /* = "localhost" */, int port /* = 7693 */) {
			// todo: multithreading (lock mutex, etc)
			// also todo: IPv6

			if (g_profileNetSocket >= 0) return; // already initialized
			g2Net::init();	

			{ // initialize socket	
				struct hostent *HostEnt;
				struct sockaddr_in ServerAddress;
				struct in_addr InAddr;
				struct in_addr **List;

				if ( (InAddr.s_addr = inet_addr(hostName)) == INADDR_NONE) {
					/* getting address with 'inet_addr()' failed; try a normal 'gethostbyname()' */
					if ( (HostEnt = gethostbyname(hostName)) == NULL)
						throw std::string("Could not gethostbyname() ") + hostName;
					List = (struct in_addr **)HostEnt->h_addr_list;
					InAddr.s_addr = List[0]->s_addr;
				}

				g_profileNetSocket = (int)socket(AF_INET, SOCK_STREAM, 0);
				if (g_profileNetSocket == -1)
					throw std::string("Could not create socket");

				/* setup server address struct; connect to server */
				memset((void*)&ServerAddress, 0, sizeof(ServerAddress));
				ServerAddress.sin_family = AF_INET;
				ServerAddress.sin_addr.s_addr = InAddr.s_addr;
				ServerAddress.sin_port = htons((short)port);
				if (connect(g_profileNetSocket, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress)) == -1) {
					g2Net::closeSocket(&g_profileNetSocket);
					throw std::string("could not connect to server ") + hostName;
				}

				/* disable nagle algorithm */
				g2Net::disableNagle(g_profileNetSocket);
			}

			{ // send opening message:
				const char *gs2Filename = "E:\\ga\\ga_sandbox\\ga_sandbox\\libgasandbox\\c3ga.gs2";
				int n = g2Net::sendN(g_profileNetSocket, (const unsigned char*)gs2Filename, (int)strlen(gs2Filename) + 1);
				n = g2Net::sendN(g_profileNetSocket, (const unsigned char*)gp2Filename, (int)strlen(gp2Filename) + 1);

				unsigned char buf[256];
				bool forReal = true;

				// send number of profile function ids:
				{
					int bufIdx = 0;
					unsigned short nbFunctionsIds = 29;
					bufIdx += g2Net::serialize_ushort(forReal, buf, bufIdx, nbFunctionsIds);
					n = g2Net::sendN(g_profileNetSocket, buf, bufIdx);
				}


				// sen number of specialized types:
				{
					int bufIdx = 0;
					unsigned short nbFunctionsIds = 50;
					bufIdx += g2Net::serialize_ushort(forReal, buf, bufIdx, nbFunctionsIds);
					n = g2Net::sendN(g_profileNetSocket, buf, bufIdx);
				}


				// send know types / ids
				// message format:
				// unsigned int ID
				// char name[], 0
				int nbTypes = 61;
				for (int i = 0; i < nbTypes; i++) {
					// send id;
					int bufIdx = 0;
					bufIdx += g2Net::serialize_uint(forReal, buf, bufIdx, (unsigned int)i);
					n = g2Net::sendN(g_profileNetSocket, buf, bufIdx);

					// send type:
					if (g_typeNames[i]) {
						n = g2Net::sendN(g_profileNetSocket, (const unsigned char*)g_typeNames[i], (int)strlen(g_typeNames[i]) + 1);
					}
					else {
						unsigned char tmp[1] = {0};
						n = g2Net::sendN(g_profileNetSocket, tmp, 1);
					}
				}

				// send 'end of ids' (0xFFFFFFFF)
				{
					int bufIdx = 0;
					bufIdx += g2Net::serialize_uint(forReal, buf, bufIdx, (unsigned int)0xFFFFFFFF);
					n = (int)g2Net::sendN(g_profileNetSocket, buf, bufIdx);
				}

				// wait for one byte ('specification & profile loaded')
				{
					n = g2Net::recvN(g_profileNetSocket, buf, 1);
					if (n < 0) {
						g_profileNetSocket = -1;
						return;
					}
				}
			}
			printf("Connected to profiling server %s:%d\n", hostName, port);
			// todo: multithreading (release mutex, etc)	
		}

		/** gets return type(s) from server, returns nb args */
		int getReturnTypesFromServer(const entry &E, unsigned short returnType[4]) {
			if (g_profileNetSocket < 0) return 0;

			unsigned short nbReturnTypes = 0; // set at the end of the function (read from recv-ed message)

			unsigned char messageBuf[1024];
			unsigned short messageLength = 0;

			// compose message
			{
				// message format:
				// unsigned short messageID = 1
				// unsigned short messageLength
				// unsigned int m_funcIdx
				// unsigned short storageTypeIdx
				// unsigned short nbArg
				// unsigned short argTypes[nbArg]
				int idx = 0;

				{
					bool forReal = true;

					// 'header':
					unsigned short messageID = 1;
					messageLength = 0; // set again later on, when message length is known
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, messageID);
					int mlIdx = idx; // remember index used for message length so we can overwrite it later on:
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, messageLength);

					// content:
					idx += g2Net::serialize_uint(forReal, messageBuf, idx, E.funcIdx());
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, E.storageTypeIdx());
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, E.nbArg());
					for (unsigned short i = 0; i < E.nbArg(); i++)
					idx += g2Net::serialize_ushort(forReal, messageBuf, idx, E.argType(i));

					// overwrite message length
					messageLength = (unsigned short)idx;
					g2Net::serialize_ushort(forReal, messageBuf, mlIdx, messageLength);

					messageLength = idx;
				}

				// send message	
				{
					int n = g2Net::sendN(g_profileNetSocket, messageBuf, messageLength);
					if (n < 0) throw std::string("getReturnTypesFromServer(): could not send data to net profiling server");
					//			printf("Sent %d\n", n);
				}

				// recv answer:
				{	
					// message format:
					// unsigned short messageID = 2
					// unsigned short messageLength
					// unsigned short nbReturnTypes
					// unsigned short returnType[nbReturnTypes]

					int idx = 0;

					// first 'header' (get ID + length)
					int n = g2Net::recvN(g_profileNetSocket, messageBuf, 4);
					if (n < 0) throw std::string("getReturnTypesFromServer(): could not recv data from profiling server");

					// parse 'header':
					unsigned short messageID, messageLength;
					idx += g2Net::deserialize_ushort(messageBuf, idx, &messageID);
					idx += g2Net::deserialize_ushort(messageBuf, idx, &messageLength);

					if (messageLength < (4 + 2)) throw std::string("getReturnTypesFromServer(): bad message profiling server");

					// get nb return types
					n = g2Net::recvN(g_profileNetSocket, messageBuf + idx, 2);
					if (n < 0) throw std::string("getReturnTypesFromServer(): could not recv data from profiling server");
					idx += g2Net::deserialize_ushort(messageBuf, idx, &nbReturnTypes);

					if (messageLength != (4 + 2 + nbReturnTypes * 2)) 
						throw std::string("getReturnTypesFromServer(): bad message profiling server");
					if (nbReturnTypes > 4)
						throw std::string("getReturnTypesFromServer(): bad message profiling server");

					// get return types
					n = g2Net::recvN(g_profileNetSocket, messageBuf + idx, nbReturnTypes * 2);
					if (n < 0) throw std::string("getReturnTypesFromServer(): could not recv data from profiling server");

					for (int i = 0; i < nbReturnTypes; i++) {
						idx += g2Net::deserialize_ushort(messageBuf, idx, returnType + i);
					}
				}
			}



			return nbReturnTypes;
		}

		void save(const char *filename /*= "E:\\ga\\ga_sandbox\\ga_sandbox\\libgasandbox\\c3ga.gp2"*/, bool append /*= false*/) {
			// when 'net profiling' is enabled, no need to save profile
			return;
		}




	} // end of namespace g2Profiling







	// todo: for all storage formats, generate constants






	// set to 0
	void mv::set() {
		// set grade usage
		gu(0);
		// set type (used for profiling)
		type(MVT_MV);

	}

	// set to copy 
	void mv::set(const mv &arg1) {
		// copy grade usage
		gu(arg1.gu());
		// copy type (used for profiling)
		type(arg1.type());
		// copy coordinates
		mv_memcpy(m_c, arg1.m_c, mv_size[gu()]);

	}

	// set to scalar
	void mv::set(Float scalarVal) {
		// set grade usage
		gu(1);
		// set type (if profile)
		// set type (used for profiling)
		type(MVT_SCALAR);
		// set coordinate
		m_c[0] = scalarVal;

	}


	// set to coordinates 
	void mv::set(unsigned int gradeUsage, const Float *coordinates, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// set coordinates
		mv_memcpy(m_c, coordinates, mv_size[gu()]);

	}


	// set to 1 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 1)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;

	}

	// set to 2 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 2)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;

	}

	// set to 3 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 3)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;

	}

	// set to 4 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 4)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;

	}

	// set to 5 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 5)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;

	}

	// set to 6 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 6)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;

	}

	// set to 7 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 7)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;

	}

	// set to 8 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 8)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;

	}

	// set to 9 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 9)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;

	}

	// set to 10 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 10)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;

	}

	// set to 11 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 11)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;

	}

	// set to 12 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 12)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;

	}

	// set to 13 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 13)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;

	}

	// set to 14 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 14)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;

	}

	// set to 15 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 15)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;

	}

	// set to 16 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 16)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;

	}

	// set to 17 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 17)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;

	}

	// set to 18 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 18)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;

	}

	// set to 19 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 19)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;

	}

	// set to 20 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 20)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;

	}

	// set to 21 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 21)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;

	}

	// set to 22 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 22)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;

	}

	// set to 23 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 23)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;

	}

	// set to 24 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 24)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;

	}

	// set to 25 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 25)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;

	}

	// set to 26 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 26)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;

	}

	// set to 27 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 27)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;

	}

	// set to 28 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 28)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;

	}

	// set to 29 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 29)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;
		m_c[28] = c28;

	}

	// set to 30 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 30)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;
		m_c[28] = c28;
		m_c[29] = c29;

	}

	// set to 31 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29, Float c30	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 31)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;
		m_c[28] = c28;
		m_c[29] = c29;
		m_c[30] = c30;

	}

	// set to 32 coordinates 
	void mv::set(unsigned int gradeUsage, Float c0, Float c1, Float c2, Float c3, Float c4, Float c5, Float c6, Float c7, Float c8, Float c9, Float c10, Float c11, Float c12, Float c13, Float c14, Float c15, Float c16, Float c17, Float c18, Float c19, Float c20, Float c21, Float c22, Float c23, Float c24, Float c25, Float c26, Float c27, Float c28, Float c29, Float c30, Float c31	, g2Type t /*= MVT_MV*/) {
		// set grade usage
		gu(gradeUsage);
		// set type (used for profiling)
		type(t);
		// check the number of coordinates
		if (mv_size[gu()] != 32)
			throw (-1); // todo: more sensible exception
		// set coordinates
		m_c[0] = c0;
		m_c[1] = c1;
		m_c[2] = c2;
		m_c[3] = c3;
		m_c[4] = c4;
		m_c[5] = c5;
		m_c[6] = c6;
		m_c[7] = c7;
		m_c[8] = c8;
		m_c[9] = c9;
		m_c[10] = c10;
		m_c[11] = c11;
		m_c[12] = c12;
		m_c[13] = c13;
		m_c[14] = c14;
		m_c[15] = c15;
		m_c[16] = c16;
		m_c[17] = c17;
		m_c[18] = c18;
		m_c[19] = c19;
		m_c[20] = c20;
		m_c[21] = c21;
		m_c[22] = c22;
		m_c[23] = c23;
		m_c[24] = c24;
		m_c[25] = c25;
		m_c[26] = c26;
		m_c[27] = c27;
		m_c[28] = c28;
		m_c[29] = c29;
		m_c[30] = c30;
		m_c[31] = c31;

	}



	// set to no_t 
	void mv::set(const no_t & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_NO_T);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to e1_t 
	void mv::set(const e1_t & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_E1_T);

		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to e2_t 
	void mv::set(const e2_t & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_E2_T);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = arg1.m_c[0] ;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to e3_t 
	void mv::set(const e3_t & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_E3_T);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = (Float)0;


	}
	// set to ni_t 
	void mv::set(const ni_t & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_NI_T);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = arg1.m_c[0] ;


	}
	// set to scalar 
	void mv::set(const scalar & arg1) {

		// set grade usage 
		gu(1);

		// set type (used for profiling)
		type(MVT_SCALAR);

		m_c[0] = arg1.m_c[0] ;


	}
	// set to noni_t 
	void mv::set(const noni_t & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_NONI_T);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = arg1.m_c[0] ;


	}
	// set to point 
	void mv::set(const point & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_POINT);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;


	}
	// set to normalizedPoint 
	void mv::set(const normalizedPoint & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_NORMALIZEDPOINT);

		m_c[0] = (Float)1.0f; 
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;
		m_c[4] = arg1.m_c[3] ;


	}
	// set to flatPoint 
	void mv::set(const flatPoint & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_FLATPOINT);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = arg1.m_c[0] ;
		m_c[7] = arg1.m_c[1] ;
		m_c[8] = arg1.m_c[2] ;
		m_c[9] = arg1.m_c[3] ;


	}
	// set to normalizedFlatPoint 
	void mv::set(const normalizedFlatPoint & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_NORMALIZEDFLATPOINT);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = arg1.m_c[0] ;
		m_c[7] = arg1.m_c[1] ;
		m_c[8] = arg1.m_c[2] ;
		m_c[9] = (Float)1.0f; 


	}
	// set to pointPair 
	void mv::set(const pointPair & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_POINTPAIR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;
		m_c[5] = arg1.m_c[5] ;
		m_c[6] = arg1.m_c[6] ;
		m_c[7] = arg1.m_c[7] ;
		m_c[8] = arg1.m_c[8] ;
		m_c[9] = arg1.m_c[9] ;


	}
	// set to line 
	void mv::set(const line & arg1) {

		// set grade usage 
		gu(8);

		// set type (used for profiling)
		type(MVT_LINE);

		m_c[0] = arg1.m_c[2] ;
		m_c[1] = arg1.m_c[1] * (Float)-1.0;
		m_c[2] = arg1.m_c[0] ;
		m_c[3] = arg1.m_c[5] * (Float)-1.0;
		m_c[4] = arg1.m_c[3] * (Float)-1.0;
		m_c[5] = arg1.m_c[4] * (Float)-1.0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;


	}
	// set to dualLine 
	void mv::set(const dualLine & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_DUALLINE);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = arg1.m_c[2] ;
		m_c[5] = arg1.m_c[1] * (Float)-1.0;
		m_c[6] = arg1.m_c[3] ;
		m_c[7] = arg1.m_c[4] ;
		m_c[8] = arg1.m_c[5] ;
		m_c[9] = (Float)0;


	}
	// set to plane 
	void mv::set(const plane & arg1) {

		// set grade usage 
		gu(16);

		// set type (used for profiling)
		type(MVT_PLANE);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[3] ;
		m_c[2] = arg1.m_c[2] * (Float)-1.0;
		m_c[3] = arg1.m_c[1] ;
		m_c[4] = (Float)0;


	}
	// set to dualPlane 
	void mv::set(const dualPlane & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_DUALPLANE);

		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;
		m_c[4] = arg1.m_c[3] ;


	}
	// set to circle 
	void mv::set(const circle & arg1) {

		// set grade usage 
		gu(8);

		// set type (used for profiling)
		type(MVT_CIRCLE);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;
		m_c[5] = arg1.m_c[5] ;
		m_c[6] = arg1.m_c[6] ;
		m_c[7] = arg1.m_c[7] ;
		m_c[8] = arg1.m_c[8] ;
		m_c[9] = arg1.m_c[9] ;


	}
	// set to sphere 
	void mv::set(const sphere & arg1) {

		// set grade usage 
		gu(16);

		// set type (used for profiling)
		type(MVT_SPHERE);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[3] ;
		m_c[2] = arg1.m_c[2] * (Float)-1.0;
		m_c[3] = arg1.m_c[1] ;
		m_c[4] = arg1.m_c[4] * (Float)-1.0;


	}
	// set to dualSphere 
	void mv::set(const dualSphere & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_DUALSPHERE);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;


	}
	// set to normalizedSphere 
	void mv::set(const normalizedSphere & arg1) {

		// set grade usage 
		gu(16);

		// set type (used for profiling)
		type(MVT_NORMALIZEDSPHERE);

		m_c[0] = (Float)1.0f; 
		m_c[1] = arg1.m_c[2] ;
		m_c[2] = arg1.m_c[1] * (Float)-1.0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = arg1.m_c[3] * (Float)-1.0;


	}
	// set to normalizedDualSphere 
	void mv::set(const normalizedDualSphere & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_NORMALIZEDDUALSPHERE);

		m_c[0] = (Float)1.0f; 
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;
		m_c[4] = arg1.m_c[3] ;


	}
	// set to freeVector 
	void mv::set(const freeVector & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_FREEVECTOR);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = arg1.m_c[0] ;
		m_c[7] = arg1.m_c[1] ;
		m_c[8] = arg1.m_c[2] ;
		m_c[9] = (Float)0;


	}
	// set to freeBivector 
	void mv::set(const freeBivector & arg1) {

		// set grade usage 
		gu(8);

		// set type (used for profiling)
		type(MVT_FREEBIVECTOR);

		m_c[0] = arg1.m_c[1] ;
		m_c[1] = arg1.m_c[2] ;
		m_c[2] = arg1.m_c[0] ;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;


	}
	// set to freeTrivector 
	void mv::set(const freeTrivector & arg1) {

		// set grade usage 
		gu(16);

		// set type (used for profiling)
		type(MVT_FREETRIVECTOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to tangentVector 
	void mv::set(const tangentVector & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_TANGENTVECTOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;
		m_c[5] = arg1.m_c[5] ;
		m_c[6] = arg1.m_c[6] ;
		m_c[7] = arg1.m_c[7] ;
		m_c[8] = arg1.m_c[8] ;
		m_c[9] = arg1.m_c[9] ;


	}
	// set to tangentBivector 
	void mv::set(const tangentBivector & arg1) {

		// set grade usage 
		gu(8);

		// set type (used for profiling)
		type(MVT_TANGENTBIVECTOR);

		m_c[0] = arg1.m_c[1] ;
		m_c[1] = arg1.m_c[2] ;
		m_c[2] = arg1.m_c[3] ;
		m_c[3] = arg1.m_c[4] ;
		m_c[4] = arg1.m_c[5] ;
		m_c[5] = arg1.m_c[6] ;
		m_c[6] = arg1.m_c[7] ;
		m_c[7] = arg1.m_c[8] ;
		m_c[8] = arg1.m_c[9] ;
		m_c[9] = arg1.m_c[0] ;


	}
	// set to vectorE2GA 
	void mv::set(const vectorE2GA & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_VECTORE2GA);

		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to vectorE3GA 
	void mv::set(const vectorE3GA & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT_VECTORE3GA);

		m_c[0] = (Float)0;
		m_c[1] = arg1.m_c[0] ;
		m_c[2] = arg1.m_c[1] ;
		m_c[3] = arg1.m_c[2] ;
		m_c[4] = (Float)0;


	}
	// set to bivectorE3GA 
	void mv::set(const bivectorE3GA & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_BIVECTORE3GA);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = arg1.m_c[1] ;
		m_c[5] = arg1.m_c[2] ;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;


	}
	// set to TRversorLog 
	void mv::set(const TRversorLog & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_TRVERSORLOG);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = arg1.m_c[1] ;
		m_c[5] = arg1.m_c[2] ;
		m_c[6] = arg1.m_c[3] ;
		m_c[7] = arg1.m_c[4] ;
		m_c[8] = arg1.m_c[5] ;
		m_c[9] = (Float)0;


	}
	// set to TRSversorLog 
	void mv::set(const TRSversorLog & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT_TRSVERSORLOG);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = arg1.m_c[0] ;
		m_c[4] = arg1.m_c[2] ;
		m_c[5] = arg1.m_c[1] * (Float)-1.0;
		m_c[6] = arg1.m_c[3] ;
		m_c[7] = arg1.m_c[4] ;
		m_c[8] = arg1.m_c[5] ;
		m_c[9] = arg1.m_c[6] ;


	}
	// set to TRversor 
	void mv::set(const TRversor & arg1) {

		// set grade usage 
		gu(21);

		// set type (used for profiling)
		type(MVT_TRVERSOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = arg1.m_c[1] ;
		m_c[5] = arg1.m_c[3] ;
		m_c[6] = arg1.m_c[2] * (Float)-1.0;
		m_c[7] = arg1.m_c[4] ;
		m_c[8] = arg1.m_c[5] ;
		m_c[9] = arg1.m_c[6] ;
		m_c[10] = (Float)0;
		m_c[11] = arg1.m_c[7] ;
		m_c[12] = (Float)0;
		m_c[13] = (Float)0;
		m_c[14] = (Float)0;
		m_c[15] = (Float)0;


	}
	// set to TRSversor 
	void mv::set(const TRSversor & arg1) {

		// set grade usage 
		gu(21);

		// set type (used for profiling)
		type(MVT_TRSVERSOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = arg1.m_c[1] ;
		m_c[5] = arg1.m_c[3] ;
		m_c[6] = arg1.m_c[2] * (Float)-1.0;
		m_c[7] = arg1.m_c[4] ;
		m_c[8] = arg1.m_c[5] ;
		m_c[9] = arg1.m_c[6] ;
		m_c[10] = arg1.m_c[7] ;
		m_c[11] = arg1.m_c[11] ;
		m_c[12] = arg1.m_c[10] ;
		m_c[13] = arg1.m_c[9] * (Float)-1.0;
		m_c[14] = arg1.m_c[8] ;
		m_c[15] = (Float)0;


	}
	// set to evenVersor 
	void mv::set(const evenVersor & arg1) {

		// set grade usage 
		gu(21);

		// set type (used for profiling)
		type(MVT_EVENVERSOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = arg1.m_c[1] ;
		m_c[2] = arg1.m_c[2] ;
		m_c[3] = arg1.m_c[3] ;
		m_c[4] = arg1.m_c[4] ;
		m_c[5] = arg1.m_c[5] ;
		m_c[6] = arg1.m_c[6] ;
		m_c[7] = arg1.m_c[7] ;
		m_c[8] = arg1.m_c[8] ;
		m_c[9] = arg1.m_c[9] ;
		m_c[10] = arg1.m_c[10] ;
		m_c[11] = arg1.m_c[11] ;
		m_c[12] = arg1.m_c[14] ;
		m_c[13] = arg1.m_c[13] * (Float)-1.0;
		m_c[14] = arg1.m_c[12] ;
		m_c[15] = arg1.m_c[15] * (Float)-1.0;


	}
	// set to translator 
	void mv::set(const translator & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT_TRANSLATOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = arg1.m_c[1] ;
		m_c[8] = arg1.m_c[2] ;
		m_c[9] = arg1.m_c[3] ;
		m_c[10] = (Float)0;


	}
	// set to normalizedTranslator 
	void mv::set(const normalizedTranslator & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT_NORMALIZEDTRANSLATOR);

		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = arg1.m_c[0] ;
		m_c[8] = arg1.m_c[1] ;
		m_c[9] = arg1.m_c[2] ;
		m_c[10] = (Float)0;


	}
	// set to rotor 
	void mv::set(const rotor & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT_ROTOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = arg1.m_c[1] ;
		m_c[5] = arg1.m_c[2] ;
		m_c[6] = arg1.m_c[3] ;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;
		m_c[10] = (Float)0;


	}
	// set to scalor 
	void mv::set(const scalor & arg1) {

		// set grade usage 
		gu(5);

		// set type (used for profiling)
		type(MVT_SCALOR);

		m_c[0] = arg1.m_c[0] ;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;
		m_c[10] = arg1.m_c[1] ;


	}
	// set to __no_ct__ 
	void mv::set(const __no_ct__ & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___NO_CT__);

		m_c[0] = (Float)1.0f; 
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to __e1_ct__ 
	void mv::set(const __e1_ct__ & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___E1_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)1.0f; 
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to __e2_ct__ 
	void mv::set(const __e2_ct__ & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___E2_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)1.0f; 
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;


	}
	// set to __e3_ct__ 
	void mv::set(const __e3_ct__ & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___E3_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)1.0f; 
		m_c[4] = (Float)0;


	}
	// set to __ni_ct__ 
	void mv::set(const __ni_ct__ & arg1) {

		// set grade usage 
		gu(2);

		// set type (used for profiling)
		type(MVT___NI_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)1.0f; 


	}
	// set to __noni_ct__ 
	void mv::set(const __noni_ct__ & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___NONI_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)1.0f; 


	}
	// set to __e3ni_ct__ 
	void mv::set(const __e3ni_ct__ & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___E3NI_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)1.0f; 
		m_c[9] = (Float)0;


	}
	// set to __e2ni_ct__ 
	void mv::set(const __e2ni_ct__ & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___E2NI_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)1.0f; 
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;


	}
	// set to __I3_ct__ 
	void mv::set(const __I3_ct__ & arg1) {

		// set grade usage 
		gu(8);

		// set type (used for profiling)
		type(MVT___I3_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)0;
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)1.0f; 


	}
	// set to __e1ni_ct__ 
	void mv::set(const __e1ni_ct__ & arg1) {

		// set grade usage 
		gu(4);

		// set type (used for profiling)
		type(MVT___E1NI_CT__);

		m_c[0] = (Float)0;
		m_c[1] = (Float)0;
		m_c[2] = (Float)0;
		m_c[3] = (Float)0;
		m_c[4] = (Float)0;
		m_c[5] = (Float)0;
		m_c[6] = (Float)1.0f; 
		m_c[7] = (Float)0;
		m_c[8] = (Float)0;
		m_c[9] = (Float)0;


	}
	// set to __I5_ct__ 
	void mv::set(const __I5_ct__ & arg1) {

		// set grade usage 
		gu(32);

		// set type (used for profiling)
		type(MVT___I5_CT__);

		m_c[0] = (Float)1.0f; 


	}
	// set to __I5i_ct__ 
	void mv::set(const __I5i_ct__ & arg1) {

		// set grade usage 
		gu(32);

		// set type (used for profiling)
		type(MVT___I5I_CT__);

		m_c[0] = (Float)-1.0f; 


	}






	// assign copy
	mv& mv::operator=(const mv &arg1) {
		set(arg1);
		return *this;
	}


	// assign scalar
	mv& mv::operator=(Float s) {
		set(s);
		return *this;
	}

	// assign no_t 
	mv& mv::operator=(const no_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign e1_t 
	mv& mv::operator=(const e1_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign e2_t 
	mv& mv::operator=(const e2_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign e3_t 
	mv& mv::operator=(const e3_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign ni_t 
	mv& mv::operator=(const ni_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign scalar 
	mv& mv::operator=(const scalar& arg1) {
		set(arg1);
		return *this;
	}
	// assign noni_t 
	mv& mv::operator=(const noni_t& arg1) {
		set(arg1);
		return *this;
	}
	// assign point 
	mv& mv::operator=(const point& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedPoint 
	mv& mv::operator=(const normalizedPoint& arg1) {
		set(arg1);
		return *this;
	}
	// assign flatPoint 
	mv& mv::operator=(const flatPoint& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedFlatPoint 
	mv& mv::operator=(const normalizedFlatPoint& arg1) {
		set(arg1);
		return *this;
	}
	// assign pointPair 
	mv& mv::operator=(const pointPair& arg1) {
		set(arg1);
		return *this;
	}
	// assign line 
	mv& mv::operator=(const line& arg1) {
		set(arg1);
		return *this;
	}
	// assign dualLine 
	mv& mv::operator=(const dualLine& arg1) {
		set(arg1);
		return *this;
	}
	// assign plane 
	mv& mv::operator=(const plane& arg1) {
		set(arg1);
		return *this;
	}
	// assign dualPlane 
	mv& mv::operator=(const dualPlane& arg1) {
		set(arg1);
		return *this;
	}
	// assign circle 
	mv& mv::operator=(const circle& arg1) {
		set(arg1);
		return *this;
	}
	// assign sphere 
	mv& mv::operator=(const sphere& arg1) {
		set(arg1);
		return *this;
	}
	// assign dualSphere 
	mv& mv::operator=(const dualSphere& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedSphere 
	mv& mv::operator=(const normalizedSphere& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedDualSphere 
	mv& mv::operator=(const normalizedDualSphere& arg1) {
		set(arg1);
		return *this;
	}
	// assign freeVector 
	mv& mv::operator=(const freeVector& arg1) {
		set(arg1);
		return *this;
	}
	// assign freeBivector 
	mv& mv::operator=(const freeBivector& arg1) {
		set(arg1);
		return *this;
	}
	// assign freeTrivector 
	mv& mv::operator=(const freeTrivector& arg1) {
		set(arg1);
		return *this;
	}
	// assign tangentVector 
	mv& mv::operator=(const tangentVector& arg1) {
		set(arg1);
		return *this;
	}
	// assign tangentBivector 
	mv& mv::operator=(const tangentBivector& arg1) {
		set(arg1);
		return *this;
	}
	// assign vectorE2GA 
	mv& mv::operator=(const vectorE2GA& arg1) {
		set(arg1);
		return *this;
	}
	// assign vectorE3GA 
	mv& mv::operator=(const vectorE3GA& arg1) {
		set(arg1);
		return *this;
	}
	// assign bivectorE3GA 
	mv& mv::operator=(const bivectorE3GA& arg1) {
		set(arg1);
		return *this;
	}
	// assign TRversorLog 
	mv& mv::operator=(const TRversorLog& arg1) {
		set(arg1);
		return *this;
	}
	// assign TRSversorLog 
	mv& mv::operator=(const TRSversorLog& arg1) {
		set(arg1);
		return *this;
	}
	// assign TRversor 
	mv& mv::operator=(const TRversor& arg1) {
		set(arg1);
		return *this;
	}
	// assign TRSversor 
	mv& mv::operator=(const TRSversor& arg1) {
		set(arg1);
		return *this;
	}
	// assign evenVersor 
	mv& mv::operator=(const evenVersor& arg1) {
		set(arg1);
		return *this;
	}
	// assign translator 
	mv& mv::operator=(const translator& arg1) {
		set(arg1);
		return *this;
	}
	// assign normalizedTranslator 
	mv& mv::operator=(const normalizedTranslator& arg1) {
		set(arg1);
		return *this;
	}
	// assign rotor 
	mv& mv::operator=(const rotor& arg1) {
		set(arg1);
		return *this;
	}
	// assign scalor 
	mv& mv::operator=(const scalor& arg1) {
		set(arg1);
		return *this;
	}
	// assign __no_ct__ 
	mv& mv::operator=(const __no_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e1_ct__ 
	mv& mv::operator=(const __e1_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e2_ct__ 
	mv& mv::operator=(const __e2_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e3_ct__ 
	mv& mv::operator=(const __e3_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __ni_ct__ 
	mv& mv::operator=(const __ni_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __noni_ct__ 
	mv& mv::operator=(const __noni_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e3ni_ct__ 
	mv& mv::operator=(const __e3ni_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e2ni_ct__ 
	mv& mv::operator=(const __e2ni_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __I3_ct__ 
	mv& mv::operator=(const __I3_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __e1ni_ct__ 
	mv& mv::operator=(const __e1ni_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __I5_ct__ 
	mv& mv::operator=(const __I5_ct__& arg1) {
		set(arg1);
		return *this;
	}
	// assign __I5i_ct__ 
	mv& mv::operator=(const __I5i_ct__& arg1) {
		set(arg1);
		return *this;
	}




	float mv::largestCoordinate() const {
		int nc = mv_size[gu()], i;
		Float maxC = -1.0, C;

		for (i = 0; i < nc; i++) {
			C = (m_c[i] < (Float)0.0) ? -m_c[i] : m_c[i];
			if (C > maxC) maxC = C;
		}

		return maxC;
	}

	float mv::largestBasisBlade(unsigned int &bm) const {
		int nc = mv_size[gu()];
		Float maxC = -1.0, C;

		int idx = 0;
		int grade = 0;
		int i = 0;

		while (i < nc) {
			if (gu() & (1 << grade)) {
				for (int j = 0; j < mv_gradeSize[grade]; j++) {
					C = (m_c[i] < (Float)0.0) ? -m_c[i] : m_c[i];
					if (C > maxC) {
						maxC = C;
						bm = mv_basisElementBitmapByIndex[idx];
					}
					idx++;
					i++;
				}
			}
			else idx += mv_gradeSize[grade];
			grade++;
		}

		return maxC;
	}








	// set to mv 
	void no_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float no_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float no_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 1;

		return maxC;
	}




	// set to mv 
	void e1_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float e1_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e1_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 2;

		return maxC;
	}




	// set to mv 
	void e2_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float e2_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e2_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 4;

		return maxC;
	}




	// set to mv 
	void e3_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 3];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float e3_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float e3_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 8;

		return maxC;
	}




	// set to mv 
	void ni_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float ni_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float ni_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 16;

		return maxC;
	}




	// set to mv 
	void scalar::set(const mv & arg1) {


		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float scalar::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float scalar::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 0;

		return maxC;
	}




	// set to mv 
	void noni_t::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float noni_t::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float noni_t::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 17;

		return maxC;
	}




	// set to mv 
	void point::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
		}


	}




	float point::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float point::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}




	// set to mv 
	void normalizedPoint::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
			m_c[2] = arg1.m_c[gidx + 3];
			m_c[3] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}




	float normalizedPoint::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedPoint::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 1;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}




	// set to mv 
	void flatPoint::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 6];
			m_c[1] = arg1.m_c[gidx + 7];
			m_c[2] = arg1.m_c[gidx + 8];
			m_c[3] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}




	float flatPoint::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float flatPoint::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 18;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		return maxC;
	}




	// set to mv 
	void normalizedFlatPoint::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 6];
			m_c[1] = arg1.m_c[gidx + 7];
			m_c[2] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float normalizedFlatPoint::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedFlatPoint::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 17;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}




	// set to mv 
	void pointPair::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
			m_c[5] = arg1.m_c[gidx + 5];
			m_c[6] = arg1.m_c[gidx + 6];
			m_c[7] = arg1.m_c[gidx + 7];
			m_c[8] = arg1.m_c[gidx + 8];
			m_c[9] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
		}


	}




	float pointPair::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float pointPair::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 3;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 9;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		return maxC;
	}




	// set to mv 
	void line::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 2];
			m_c[1] = arg1.m_c[gidx + 1]* (Float)-1.0;
			m_c[2] = arg1.m_c[gidx + 0];
			m_c[3] = arg1.m_c[gidx + 4]* (Float)-1.0;
			m_c[4] = arg1.m_c[gidx + 5]* (Float)-1.0;
			m_c[5] = arg1.m_c[gidx + 3]* (Float)-1.0;
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
		}


	}




	float line::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float line::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 22;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 26;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 28;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 19;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 21;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 25;
		}
		return maxC;
	}




	// set to mv 
	void dualLine::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 3];
			m_c[1] = arg1.m_c[gidx + 5]* (Float)-1.0;
			m_c[2] = arg1.m_c[gidx + 4];
			m_c[3] = arg1.m_c[gidx + 6];
			m_c[4] = arg1.m_c[gidx + 7];
			m_c[5] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
		}


	}




	float dualLine::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float dualLine::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 6;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}




	// set to mv 
	void plane::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[3] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}




	float plane::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float plane::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 30;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		return maxC;
	}




	// set to mv 
	void dualPlane::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
			m_c[2] = arg1.m_c[gidx + 3];
			m_c[3] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}




	float dualPlane::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float dualPlane::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 2;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}




	// set to mv 
	void circle::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
			m_c[5] = arg1.m_c[gidx + 5];
			m_c[6] = arg1.m_c[gidx + 6];
			m_c[7] = arg1.m_c[gidx + 7];
			m_c[8] = arg1.m_c[gidx + 8];
			m_c[9] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
		}


	}




	float circle::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float circle::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 28;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 26;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 22;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 25;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 19;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 21;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 13;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 11;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 7;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 14;
		}
		return maxC;
	}




	// set to mv 
	void sphere::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[3] = arg1.m_c[gidx + 1];
			m_c[4] = arg1.m_c[gidx + 4]* (Float)-1.0;
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
		}


	}




	float sphere::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float sphere::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 30;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 15;
		}
		return maxC;
	}




	// set to mv 
	void dualSphere::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
		}


	}




	float dualSphere::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float dualSphere::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 1;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}




	// set to mv 
	void normalizedSphere::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[0] = arg1.m_c[gidx + 3];
			m_c[1] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[2] = arg1.m_c[gidx + 1];
			m_c[3] = arg1.m_c[gidx + 4]* (Float)-1.0;
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}




	float normalizedSphere::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedSphere::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 30;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 15;
		}
		return maxC;
	}




	// set to mv 
	void normalizedDualSphere::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
			m_c[2] = arg1.m_c[gidx + 3];
			m_c[3] = arg1.m_c[gidx + 4];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}




	float normalizedDualSphere::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedDualSphere::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 1;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 2;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 16;
		}
		return maxC;
	}




	// set to mv 
	void freeVector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 6];
			m_c[1] = arg1.m_c[gidx + 7];
			m_c[2] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float freeVector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float freeVector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 18;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}




	// set to mv 
	void freeBivector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 2];
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 1];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float freeBivector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float freeBivector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 22;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 28;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 26;
		}
		return maxC;
	}




	// set to mv 
	void freeTrivector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[0] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[0] = (Float)0.0;
		}


	}




	float freeTrivector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];

		return maxC;
	}

	float freeTrivector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		bm = 30;

		return maxC;
	}




	// set to mv 
	void tangentVector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 0];
			m_c[1] = arg1.m_c[gidx + 1];
			m_c[2] = arg1.m_c[gidx + 2];
			m_c[3] = arg1.m_c[gidx + 3];
			m_c[4] = arg1.m_c[gidx + 4];
			m_c[5] = arg1.m_c[gidx + 5];
			m_c[6] = arg1.m_c[gidx + 6];
			m_c[7] = arg1.m_c[gidx + 7];
			m_c[8] = arg1.m_c[gidx + 8];
			m_c[9] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
		}


	}




	float tangentVector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float tangentVector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 3;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 9;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		return maxC;
	}




	// set to mv 
	void tangentBivector::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 8) {
			m_c[0] = arg1.m_c[gidx + 9];
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 1];
			m_c[3] = arg1.m_c[gidx + 2];
			m_c[4] = arg1.m_c[gidx + 3];
			m_c[5] = arg1.m_c[gidx + 4];
			m_c[6] = arg1.m_c[gidx + 5];
			m_c[7] = arg1.m_c[gidx + 6];
			m_c[8] = arg1.m_c[gidx + 7];
			m_c[9] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
		}


	}




	float tangentBivector::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float tangentBivector::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 14;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 28;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 26;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 22;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 25;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 19;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 21;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 13;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 11;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 7;
		}
		return maxC;
	}




	// set to mv 
	void vectorE2GA::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
		}


	}




	float vectorE2GA::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float vectorE2GA::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 2;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		return maxC;
	}




	// set to mv 
	void vectorE3GA::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			m_c[0] = arg1.m_c[gidx + 1];
			m_c[1] = arg1.m_c[gidx + 2];
			m_c[2] = arg1.m_c[gidx + 3];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float vectorE3GA::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float vectorE3GA::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 2;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 4;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 8;
		}
		return maxC;
	}




	// set to mv 
	void bivectorE3GA::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 3];
			m_c[1] = arg1.m_c[gidx + 4];
			m_c[2] = arg1.m_c[gidx + 5];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float bivectorE3GA::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float bivectorE3GA::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 6;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		return maxC;
	}




	// set to mv 
	void TRversorLog::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 3];
			m_c[1] = arg1.m_c[gidx + 4];
			m_c[2] = arg1.m_c[gidx + 5];
			m_c[3] = arg1.m_c[gidx + 6];
			m_c[4] = arg1.m_c[gidx + 7];
			m_c[5] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
		}


	}




	float TRversorLog::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float TRversorLog::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 6;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}




	// set to mv 
	void TRSversorLog::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 3];
			m_c[1] = arg1.m_c[gidx + 5]* (Float)-1.0;
			m_c[2] = arg1.m_c[gidx + 4];
			m_c[3] = arg1.m_c[gidx + 6];
			m_c[4] = arg1.m_c[gidx + 7];
			m_c[5] = arg1.m_c[gidx + 8];
			m_c[6] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
		}


	}




	float TRSversorLog::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float TRSversorLog::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 6;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		return maxC;
	}




	// set to mv 
	void TRversor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 5]* (Float)-1.0;
			m_c[3] = arg1.m_c[gidx + 4];
			m_c[4] = arg1.m_c[gidx + 6];
			m_c[5] = arg1.m_c[gidx + 7];
			m_c[6] = arg1.m_c[gidx + 8];
			gidx += 10;		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[7] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[7] = (Float)0.0;
		}


	}




	float TRversor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float TRversor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 30;
		}
		return maxC;
	}




	// set to mv 
	void TRSversor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 5]* (Float)-1.0;
			m_c[3] = arg1.m_c[gidx + 4];
			m_c[4] = arg1.m_c[gidx + 6];
			m_c[5] = arg1.m_c[gidx + 7];
			m_c[6] = arg1.m_c[gidx + 8];
			m_c[7] = arg1.m_c[gidx + 9];
			gidx += 10;		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[8] = arg1.m_c[gidx + 3];
			m_c[9] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[10] = arg1.m_c[gidx + 1];
			m_c[11] = arg1.m_c[gidx + 0];
		}
		else {
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
			m_c[10] = (Float)0.0;
			m_c[11] = (Float)0.0;
		}


	}




	float TRSversor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		C = (m_c[10] < (Float)0.0) ? -m_c[10] : m_c[10];
		if (C > maxC) maxC = C;
		C = (m_c[11] < (Float)0.0) ? -m_c[11] : m_c[11];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float TRSversor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[10] < (Float)0.0) ? -m_c[10] : m_c[10];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		C = (m_c[11] < (Float)0.0) ? -m_c[11] : m_c[11];
		if (C > maxC) {
			maxC = C;
			bm = 30;
		}
		return maxC;
	}




	// set to mv 
	void evenVersor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 0];
			m_c[2] = arg1.m_c[gidx + 1];
			m_c[3] = arg1.m_c[gidx + 2];
			m_c[4] = arg1.m_c[gidx + 3];
			m_c[5] = arg1.m_c[gidx + 4];
			m_c[6] = arg1.m_c[gidx + 5];
			m_c[7] = arg1.m_c[gidx + 6];
			m_c[8] = arg1.m_c[gidx + 7];
			m_c[9] = arg1.m_c[gidx + 8];
			m_c[10] = arg1.m_c[gidx + 9];
			gidx += 10;		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
			m_c[4] = (Float)0.0;
			m_c[5] = (Float)0.0;
			m_c[6] = (Float)0.0;
			m_c[7] = (Float)0.0;
			m_c[8] = (Float)0.0;
			m_c[9] = (Float)0.0;
			m_c[10] = (Float)0.0;
		}

		if (arg1.gu() & 8) {
			gidx += 10;		}
		else {
		}

		if (arg1.gu() & 16) {
			m_c[11] = arg1.m_c[gidx + 0];
			m_c[12] = arg1.m_c[gidx + 3];
			m_c[13] = arg1.m_c[gidx + 2]* (Float)-1.0;
			m_c[14] = arg1.m_c[gidx + 1];
			m_c[15] = arg1.m_c[gidx + 4]* (Float)-1.0;
		}
		else {
			m_c[11] = (Float)0.0;
			m_c[12] = (Float)0.0;
			m_c[13] = (Float)0.0;
			m_c[14] = (Float)0.0;
			m_c[15] = (Float)0.0;
		}


	}




	float evenVersor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) maxC = C;
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) maxC = C;
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) maxC = C;
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) maxC = C;
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) maxC = C;
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) maxC = C;
		C = (m_c[10] < (Float)0.0) ? -m_c[10] : m_c[10];
		if (C > maxC) maxC = C;
		C = (m_c[11] < (Float)0.0) ? -m_c[11] : m_c[11];
		if (C > maxC) maxC = C;
		C = (m_c[12] < (Float)0.0) ? -m_c[12] : m_c[12];
		if (C > maxC) maxC = C;
		C = (m_c[13] < (Float)0.0) ? -m_c[13] : m_c[13];
		if (C > maxC) maxC = C;
		C = (m_c[14] < (Float)0.0) ? -m_c[14] : m_c[14];
		if (C > maxC) maxC = C;
		C = (m_c[15] < (Float)0.0) ? -m_c[15] : m_c[15];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float evenVersor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 3;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 5;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 9;
		}
		C = (m_c[4] < (Float)0.0) ? -m_c[4] : m_c[4];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[5] < (Float)0.0) ? -m_c[5] : m_c[5];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[6] < (Float)0.0) ? -m_c[6] : m_c[6];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		C = (m_c[7] < (Float)0.0) ? -m_c[7] : m_c[7];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[8] < (Float)0.0) ? -m_c[8] : m_c[8];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[9] < (Float)0.0) ? -m_c[9] : m_c[9];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		C = (m_c[10] < (Float)0.0) ? -m_c[10] : m_c[10];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		C = (m_c[11] < (Float)0.0) ? -m_c[11] : m_c[11];
		if (C > maxC) {
			maxC = C;
			bm = 30;
		}
		C = (m_c[12] < (Float)0.0) ? -m_c[12] : m_c[12];
		if (C > maxC) {
			maxC = C;
			bm = 23;
		}
		C = (m_c[13] < (Float)0.0) ? -m_c[13] : m_c[13];
		if (C > maxC) {
			maxC = C;
			bm = 27;
		}
		C = (m_c[14] < (Float)0.0) ? -m_c[14] : m_c[14];
		if (C > maxC) {
			maxC = C;
			bm = 29;
		}
		C = (m_c[15] < (Float)0.0) ? -m_c[15] : m_c[15];
		if (C > maxC) {
			maxC = C;
			bm = 15;
		}
		return maxC;
	}




	// set to mv 
	void translator::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 6];
			m_c[2] = arg1.m_c[gidx + 7];
			m_c[3] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}




	float translator::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float translator::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}




	// set to mv 
	void normalizedTranslator::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			gidx += 1;		}
		else {
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[0] = arg1.m_c[gidx + 6];
			m_c[1] = arg1.m_c[gidx + 7];
			m_c[2] = arg1.m_c[gidx + 8];
		}
		else {
			m_c[0] = (Float)0.0;
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
		}


	}




	float normalizedTranslator::largestCoordinate() const {

		Float maxC = (Float)1.0f, C;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) maxC = C;
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float normalizedTranslator::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f, C;
		bm = 0;

		C = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0];
		if (C > maxC) {
			maxC = C;
			bm = 18;
		}
		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 20;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 24;
		}
		return maxC;
	}




	// set to mv 
	void rotor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 3];
			m_c[2] = arg1.m_c[gidx + 4];
			m_c[3] = arg1.m_c[gidx + 5];
		}
		else {
			m_c[1] = (Float)0.0;
			m_c[2] = (Float)0.0;
			m_c[3] = (Float)0.0;
		}


	}




	float rotor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) maxC = C;
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float rotor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 6;
		}
		C = (m_c[2] < (Float)0.0) ? -m_c[2] : m_c[2];
		if (C > maxC) {
			maxC = C;
			bm = 12;
		}
		C = (m_c[3] < (Float)0.0) ? -m_c[3] : m_c[3];
		if (C > maxC) {
			maxC = C;
			bm = 10;
		}
		return maxC;
	}




	// set to mv 
	void scalor::set(const mv & arg1) {

		int gidx = 0;

		if (arg1.gu() & 1) {
			m_c[0] = arg1.m_c[gidx + 0];
			gidx += 1;		}
		else {
			m_c[0] = (Float)0.0;
		}

		if (arg1.gu() & 2) {
			gidx += 5;		}
		else {
		}

		if (arg1.gu() & 4) {
			m_c[1] = arg1.m_c[gidx + 9];
		}
		else {
			m_c[1] = (Float)0.0;
		}


	}




	float scalor::largestCoordinate() const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) maxC = C;
		return maxC;
	}

	float scalor::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (m_c[0] < (Float)0.0) ? -m_c[0] : m_c[0], C;
		bm = 0;

		C = (m_c[1] < (Float)0.0) ? -m_c[1] : m_c[1];
		if (C > maxC) {
			maxC = C;
			bm = 17;
		}
		return maxC;
	}




	// set to mv 
	void __no_ct__::set(const mv & arg1) {



	}




	float __no_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __no_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 1;

		return maxC;
	}




	// set to mv 
	void __e1_ct__::set(const mv & arg1) {



	}




	float __e1_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e1_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 2;

		return maxC;
	}




	// set to mv 
	void __e2_ct__::set(const mv & arg1) {



	}




	float __e2_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e2_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 4;

		return maxC;
	}




	// set to mv 
	void __e3_ct__::set(const mv & arg1) {



	}




	float __e3_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e3_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 8;

		return maxC;
	}




	// set to mv 
	void __ni_ct__::set(const mv & arg1) {



	}




	float __ni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __ni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 16;

		return maxC;
	}




	// set to mv 
	void __noni_ct__::set(const mv & arg1) {



	}




	float __noni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __noni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 17;

		return maxC;
	}




	// set to mv 
	void __e3ni_ct__::set(const mv & arg1) {



	}




	float __e3ni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e3ni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 24;

		return maxC;
	}




	// set to mv 
	void __e2ni_ct__::set(const mv & arg1) {



	}




	float __e2ni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e2ni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 20;

		return maxC;
	}




	// set to mv 
	void __I3_ct__::set(const mv & arg1) {



	}




	float __I3_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I3_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 14;

		return maxC;
	}




	// set to mv 
	void __e1ni_ct__::set(const mv & arg1) {



	}




	float __e1ni_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __e1ni_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 18;

		return maxC;
	}




	// set to mv 
	void __I5_ct__::set(const mv & arg1) {



	}




	float __I5_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I5_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 31;

		return maxC;
	}




	// set to mv 
	void __I5i_ct__::set(const mv & arg1) {



	}




	float __I5i_ct__::largestCoordinate() const {

		Float maxC = (Float)1.0f;

		return maxC;
	}

	float __I5i_ct__::largestBasisBlade(unsigned int &bm) const {

		Float maxC = (Float)1.0f;
		bm = 31;

		return maxC;
	}






	// set to identity 'I'
	void om::set() {
		// simplify forward call to set(scalar)
		set(1.0);
	}

	// set to copy
	void om::set(const om &arg1) {
		mv_memcpy(m_c, arg1.m_c, 251);
		// set type (used for profiling)
		type(OMT_OM);
	}

	// set to scalar
	void om::set(Float scalarVal) {
		c3ga::__G2_GENERATED__::set(*this, point(point_no_e1_e2_e3_ni, scalarVal, (Float)0, (Float)0, (Float)0, (Float)0), point(point_no_e1_e2_e3_ni, (Float)0, scalarVal, (Float)0, (Float)0, (Float)0), point(point_no_e1_e2_e3_ni, (Float)0, (Float)0, scalarVal, (Float)0, (Float)0), point(point_no_e1_e2_e3_ni, (Float)0, (Float)0, (Float)0, scalarVal, (Float)0), point(point_no_e1_e2_e3_ni, (Float)0, (Float)0, (Float)0, (Float)0, scalarVal));
		// set type (used for profiling)
		type(OMT_OM);
	}

	// set to coordinates 
	void om::set(const Float *coordinates) {
		mv_memcpy(m_c, coordinates, 251);
		// set type (used for profiling)
		type(OMT_OM);
	}

	// set from basis vectors array
	void om::set(const point *vectors) {
		c3ga::__G2_GENERATED__::set(*this, vectors[0], vectors[1], vectors[2], vectors[3], vectors[4]);
		// set type (used for profiling)
		type(OMT_OM);
	}


	// set from basis vectors 
	void om::set(const point & image_of_no, const point & image_of_e1, const point & image_of_e2, const point & image_of_e3, const point & image_of_ni) {
		c3ga::__G2_GENERATED__::set(*this, image_of_no, image_of_e1, image_of_e2, image_of_e3, image_of_ni);
		// set type (used for profiling)
		type(OMT_OM);
	}

	// set to specialization
	void om::set(const omFlatPoint &arg1) {
		c3ga::__G2_GENERATED__::set(*this, arg1);
		// set type (used for profiling)
		type(OMT_OMFLATPOINT);
	}

	// set by coordinates, transpose
	void om::set(const Float *coordinates, bool transpose) {
		if (transpose) {
			m_c[0] = coordinates[0];
			m_c[5] = coordinates[1];
			m_c[10] = coordinates[2];
			m_c[15] = coordinates[3];
			m_c[20] = coordinates[4];
			m_c[1] = coordinates[5];
			m_c[6] = coordinates[6];
			m_c[11] = coordinates[7];
			m_c[16] = coordinates[8];
			m_c[21] = coordinates[9];
			m_c[2] = coordinates[10];
			m_c[7] = coordinates[11];
			m_c[12] = coordinates[12];
			m_c[17] = coordinates[13];
			m_c[22] = coordinates[14];
			m_c[3] = coordinates[15];
			m_c[8] = coordinates[16];
			m_c[13] = coordinates[17];
			m_c[18] = coordinates[18];
			m_c[23] = coordinates[19];
			m_c[4] = coordinates[20];
			m_c[9] = coordinates[21];
			m_c[14] = coordinates[22];
			m_c[19] = coordinates[23];
			m_c[24] = coordinates[24];
			m_c[25] = coordinates[25];
			m_c[35] = coordinates[26];
			m_c[45] = coordinates[27];
			m_c[55] = coordinates[28];
			m_c[65] = coordinates[29];
			m_c[75] = coordinates[30];
			m_c[85] = coordinates[31];
			m_c[95] = coordinates[32];
			m_c[105] = coordinates[33];
			m_c[115] = coordinates[34];
			m_c[26] = coordinates[35];
			m_c[36] = coordinates[36];
			m_c[46] = coordinates[37];
			m_c[56] = coordinates[38];
			m_c[66] = coordinates[39];
			m_c[76] = coordinates[40];
			m_c[86] = coordinates[41];
			m_c[96] = coordinates[42];
			m_c[106] = coordinates[43];
			m_c[116] = coordinates[44];
			m_c[27] = coordinates[45];
			m_c[37] = coordinates[46];
			m_c[47] = coordinates[47];
			m_c[57] = coordinates[48];
			m_c[67] = coordinates[49];
			m_c[77] = coordinates[50];
			m_c[87] = coordinates[51];
			m_c[97] = coordinates[52];
			m_c[107] = coordinates[53];
			m_c[117] = coordinates[54];
			m_c[28] = coordinates[55];
			m_c[38] = coordinates[56];
			m_c[48] = coordinates[57];
			m_c[58] = coordinates[58];
			m_c[68] = coordinates[59];
			m_c[78] = coordinates[60];
			m_c[88] = coordinates[61];
			m_c[98] = coordinates[62];
			m_c[108] = coordinates[63];
			m_c[118] = coordinates[64];
			m_c[29] = coordinates[65];
			m_c[39] = coordinates[66];
			m_c[49] = coordinates[67];
			m_c[59] = coordinates[68];
			m_c[69] = coordinates[69];
			m_c[79] = coordinates[70];
			m_c[89] = coordinates[71];
			m_c[99] = coordinates[72];
			m_c[109] = coordinates[73];
			m_c[119] = coordinates[74];
			m_c[30] = coordinates[75];
			m_c[40] = coordinates[76];
			m_c[50] = coordinates[77];
			m_c[60] = coordinates[78];
			m_c[70] = coordinates[79];
			m_c[80] = coordinates[80];
			m_c[90] = coordinates[81];
			m_c[100] = coordinates[82];
			m_c[110] = coordinates[83];
			m_c[120] = coordinates[84];
			m_c[31] = coordinates[85];
			m_c[41] = coordinates[86];
			m_c[51] = coordinates[87];
			m_c[61] = coordinates[88];
			m_c[71] = coordinates[89];
			m_c[81] = coordinates[90];
			m_c[91] = coordinates[91];
			m_c[101] = coordinates[92];
			m_c[111] = coordinates[93];
			m_c[121] = coordinates[94];
			m_c[32] = coordinates[95];
			m_c[42] = coordinates[96];
			m_c[52] = coordinates[97];
			m_c[62] = coordinates[98];
			m_c[72] = coordinates[99];
			m_c[82] = coordinates[100];
			m_c[92] = coordinates[101];
			m_c[102] = coordinates[102];
			m_c[112] = coordinates[103];
			m_c[122] = coordinates[104];
			m_c[33] = coordinates[105];
			m_c[43] = coordinates[106];
			m_c[53] = coordinates[107];
			m_c[63] = coordinates[108];
			m_c[73] = coordinates[109];
			m_c[83] = coordinates[110];
			m_c[93] = coordinates[111];
			m_c[103] = coordinates[112];
			m_c[113] = coordinates[113];
			m_c[123] = coordinates[114];
			m_c[34] = coordinates[115];
			m_c[44] = coordinates[116];
			m_c[54] = coordinates[117];
			m_c[64] = coordinates[118];
			m_c[74] = coordinates[119];
			m_c[84] = coordinates[120];
			m_c[94] = coordinates[121];
			m_c[104] = coordinates[122];
			m_c[114] = coordinates[123];
			m_c[124] = coordinates[124];
			m_c[125] = coordinates[125];
			m_c[135] = coordinates[126];
			m_c[145] = coordinates[127];
			m_c[155] = coordinates[128];
			m_c[165] = coordinates[129];
			m_c[175] = coordinates[130];
			m_c[185] = coordinates[131];
			m_c[195] = coordinates[132];
			m_c[205] = coordinates[133];
			m_c[215] = coordinates[134];
			m_c[126] = coordinates[135];
			m_c[136] = coordinates[136];
			m_c[146] = coordinates[137];
			m_c[156] = coordinates[138];
			m_c[166] = coordinates[139];
			m_c[176] = coordinates[140];
			m_c[186] = coordinates[141];
			m_c[196] = coordinates[142];
			m_c[206] = coordinates[143];
			m_c[216] = coordinates[144];
			m_c[127] = coordinates[145];
			m_c[137] = coordinates[146];
			m_c[147] = coordinates[147];
			m_c[157] = coordinates[148];
			m_c[167] = coordinates[149];
			m_c[177] = coordinates[150];
			m_c[187] = coordinates[151];
			m_c[197] = coordinates[152];
			m_c[207] = coordinates[153];
			m_c[217] = coordinates[154];
			m_c[128] = coordinates[155];
			m_c[138] = coordinates[156];
			m_c[148] = coordinates[157];
			m_c[158] = coordinates[158];
			m_c[168] = coordinates[159];
			m_c[178] = coordinates[160];
			m_c[188] = coordinates[161];
			m_c[198] = coordinates[162];
			m_c[208] = coordinates[163];
			m_c[218] = coordinates[164];
			m_c[129] = coordinates[165];
			m_c[139] = coordinates[166];
			m_c[149] = coordinates[167];
			m_c[159] = coordinates[168];
			m_c[169] = coordinates[169];
			m_c[179] = coordinates[170];
			m_c[189] = coordinates[171];
			m_c[199] = coordinates[172];
			m_c[209] = coordinates[173];
			m_c[219] = coordinates[174];
			m_c[130] = coordinates[175];
			m_c[140] = coordinates[176];
			m_c[150] = coordinates[177];
			m_c[160] = coordinates[178];
			m_c[170] = coordinates[179];
			m_c[180] = coordinates[180];
			m_c[190] = coordinates[181];
			m_c[200] = coordinates[182];
			m_c[210] = coordinates[183];
			m_c[220] = coordinates[184];
			m_c[131] = coordinates[185];
			m_c[141] = coordinates[186];
			m_c[151] = coordinates[187];
			m_c[161] = coordinates[188];
			m_c[171] = coordinates[189];
			m_c[181] = coordinates[190];
			m_c[191] = coordinates[191];
			m_c[201] = coordinates[192];
			m_c[211] = coordinates[193];
			m_c[221] = coordinates[194];
			m_c[132] = coordinates[195];
			m_c[142] = coordinates[196];
			m_c[152] = coordinates[197];
			m_c[162] = coordinates[198];
			m_c[172] = coordinates[199];
			m_c[182] = coordinates[200];
			m_c[192] = coordinates[201];
			m_c[202] = coordinates[202];
			m_c[212] = coordinates[203];
			m_c[222] = coordinates[204];
			m_c[133] = coordinates[205];
			m_c[143] = coordinates[206];
			m_c[153] = coordinates[207];
			m_c[163] = coordinates[208];
			m_c[173] = coordinates[209];
			m_c[183] = coordinates[210];
			m_c[193] = coordinates[211];
			m_c[203] = coordinates[212];
			m_c[213] = coordinates[213];
			m_c[223] = coordinates[214];
			m_c[134] = coordinates[215];
			m_c[144] = coordinates[216];
			m_c[154] = coordinates[217];
			m_c[164] = coordinates[218];
			m_c[174] = coordinates[219];
			m_c[184] = coordinates[220];
			m_c[194] = coordinates[221];
			m_c[204] = coordinates[222];
			m_c[214] = coordinates[223];
			m_c[224] = coordinates[224];
			m_c[225] = coordinates[225];
			m_c[230] = coordinates[226];
			m_c[235] = coordinates[227];
			m_c[240] = coordinates[228];
			m_c[245] = coordinates[229];
			m_c[226] = coordinates[230];
			m_c[231] = coordinates[231];
			m_c[236] = coordinates[232];
			m_c[241] = coordinates[233];
			m_c[246] = coordinates[234];
			m_c[227] = coordinates[235];
			m_c[232] = coordinates[236];
			m_c[237] = coordinates[237];
			m_c[242] = coordinates[238];
			m_c[247] = coordinates[239];
			m_c[228] = coordinates[240];
			m_c[233] = coordinates[241];
			m_c[238] = coordinates[242];
			m_c[243] = coordinates[243];
			m_c[248] = coordinates[244];
			m_c[229] = coordinates[245];
			m_c[234] = coordinates[246];
			m_c[239] = coordinates[247];
			m_c[244] = coordinates[248];
			m_c[249] = coordinates[249];
			m_c[250] = coordinates[250];
			// set type (used for profiling)
			type(OMT_OM);
		}
		else set(coordinates);
	}




	// assign copy
	om &om::operator=(const om &arg1) {
		set(arg1);
		return *this;
	}

	// assign scalar (creates scalar * 'I' outermorphism)
	om &om::operator=(Float scalarVal) {
		set(scalarVal);
		return *this;
	}

	/// assign specialization:
	om &om::operator=(const omFlatPoint &arg1) {
		set(arg1);
		return *this;
	}









	// G2 functions:
	mv lcont(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)1), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_1__[32] ;
		mv_zero(__tmp_coord_array_1__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[1] += (__y_xpd__[1][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[2] += (__y_xpd__[1][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[3] += (__y_xpd__[1][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[4] += (__y_xpd__[1][3] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[5] += (__y_xpd__[1][4] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[0] += ((__x_xpd__[1][2] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[1][4]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[6] += (__y_xpd__[2][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[7] += (__y_xpd__[2][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[8] += (__y_xpd__[2][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[9] += (__y_xpd__[2][3] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[10] += (__y_xpd__[2][4] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[11] += (__y_xpd__[2][5] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[12] += (__y_xpd__[2][6] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[13] += (__y_xpd__[2][7] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[14] += (__y_xpd__[2][8] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[15] += (__y_xpd__[2][9] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[1] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]));
				__tmp_coord_array_1__[2] += ((__x_xpd__[1][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][3]) + (__x_xpd__[1][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][0]));
				__tmp_coord_array_1__[3] += ((__x_xpd__[1][0] * __y_xpd__[2][7]) + (__x_xpd__[1][1] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][1]));
				__tmp_coord_array_1__[4] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][5]) + (__x_xpd__[1][0] * __y_xpd__[2][8]) + (__x_xpd__[1][2] * __y_xpd__[2][4]));
				__tmp_coord_array_1__[5] += ((__x_xpd__[1][1] * __y_xpd__[2][6]) + (__x_xpd__[1][2] * __y_xpd__[2][7]) + (__x_xpd__[1][3] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][9]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[0] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]) + (__x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][8]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[16] += (__y_xpd__[3][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[17] += (__y_xpd__[3][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[18] += (__y_xpd__[3][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[19] += (__y_xpd__[3][3] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[20] += (__y_xpd__[3][4] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[21] += (__y_xpd__[3][5] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[22] += (__y_xpd__[3][6] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[23] += (__y_xpd__[3][7] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[24] += (__y_xpd__[3][8] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[25] += (__y_xpd__[3][9] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[6] += ((__x_xpd__[1][3] * __y_xpd__[3][7]) + (__x_xpd__[1][2] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][4]));
				__tmp_coord_array_1__[7] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][5]) + (__x_xpd__[1][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][8]));
				__tmp_coord_array_1__[8] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][7]));
				__tmp_coord_array_1__[9] += ((__x_xpd__[1][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][2]));
				__tmp_coord_array_1__[10] += ((__x_xpd__[1][1] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]));
				__tmp_coord_array_1__[11] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][1]) + (__x_xpd__[1][2] * __y_xpd__[3][9]) + (__x_xpd__[1][4] * __y_xpd__[3][7]));
				__tmp_coord_array_1__[12] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][4]) + (__x_xpd__[1][3] * __y_xpd__[3][1]));
				__tmp_coord_array_1__[13] += ((__x_xpd__[1][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]));
				__tmp_coord_array_1__[14] += ((__x_xpd__[1][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]));
				__tmp_coord_array_1__[15] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][3]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[1] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][5]) + (__x_xpd__[2][5] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][8]));
				__tmp_coord_array_1__[2] += ((__x_xpd__[2][8] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][9]) + (__x_xpd__[2][2] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]) + (__x_xpd__[2][7] * __y_xpd__[3][8]));
				__tmp_coord_array_1__[3] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][9]) + (__x_xpd__[2][0] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][8]) + (__x_xpd__[2][8] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][5]));
				__tmp_coord_array_1__[4] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][9]) + (__x_xpd__[2][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][7]));
				__tmp_coord_array_1__[5] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][2]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_1__[0] += ((__x_xpd__[3][8] * __y_xpd__[3][2]) + (__x_xpd__[3][6] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (__x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][1]) + (__x_xpd__[3][4] * __y_xpd__[3][4]) + (__x_xpd__[3][2] * __y_xpd__[3][8]) + (__x_xpd__[3][5] * __y_xpd__[3][5]) + (__x_xpd__[3][0] * __y_xpd__[3][6]));

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[26] += (__y_xpd__[4][0] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[27] += (__y_xpd__[4][1] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[28] += (__y_xpd__[4][2] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[29] += (__y_xpd__[4][3] * __x_xpd__[0][0]);
				__tmp_coord_array_1__[30] += (__y_xpd__[4][4] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[16] += ((__x_xpd__[1][1] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[17] += ((__x_xpd__[1][2] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][2]));
				__tmp_coord_array_1__[18] += ((__x_xpd__[1][3] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[19] += ((__x_xpd__[1][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[20] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[4][2]) + (__x_xpd__[1][2] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[21] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[4][3]) + (__x_xpd__[1][3] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[22] += ((__x_xpd__[1][0] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[23] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[4][2]) + (__x_xpd__[1][2] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[24] += ((__x_xpd__[1][0] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[25] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][4]) + (__x_xpd__[1][0] * __y_xpd__[4][0]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[6] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[4][4]) + (__x_xpd__[2][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[7] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][4]) + (__x_xpd__[2][0] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[8] += ((__x_xpd__[2][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[9] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[4][0]) + (__x_xpd__[2][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][4]));
				__tmp_coord_array_1__[10] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][4]) + (__x_xpd__[2][9] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[11] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][0]) + (__x_xpd__[2][9] * __y_xpd__[4][2]));
				__tmp_coord_array_1__[12] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]) + (__x_xpd__[2][7] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[13] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]) + (__x_xpd__[2][8] * __y_xpd__[4][1]));
				__tmp_coord_array_1__[14] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]) + (__x_xpd__[2][6] * __y_xpd__[4][2]));
				__tmp_coord_array_1__[15] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][2]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_1__[1] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[4][1]) + (__x_xpd__[3][9] * __y_xpd__[4][4]) + (__x_xpd__[3][7] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[2] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][0]) + (__x_xpd__[3][0] * __y_xpd__[4][4]) + (__x_xpd__[3][5] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[3] += ((__x_xpd__[3][7] * __y_xpd__[4][0]) + (__x_xpd__[3][3] * __y_xpd__[4][1]) + (__x_xpd__[3][1] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][3]));
				__tmp_coord_array_1__[4] += ((__x_xpd__[3][4] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[4][1]) + (__x_xpd__[3][2] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][0]));
				__tmp_coord_array_1__[5] += ((__x_xpd__[3][2] * __y_xpd__[4][3]) + (__x_xpd__[3][0] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[4][0]) + (__x_xpd__[3][1] * __y_xpd__[4][2]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_1__[0] += ((__x_xpd__[4][4] * __y_xpd__[4][0]) + (__x_xpd__[4][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[4][1]));

			}

		}
		if (((y.m_gu & 32) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_1__[31] += (__y_xpd__[5][0] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_1__[26] += (-1.0f * __x_xpd__[1][4] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[27] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[28] += (-1.0f * __x_xpd__[1][2] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[29] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[30] += (-1.0f * __x_xpd__[1][0] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_1__[16] += (-1.0f * __x_xpd__[2][6] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[17] += (-1.0f * __x_xpd__[2][7] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[18] += (-1.0f * __x_xpd__[2][8] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[19] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[20] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[21] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[22] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[23] += (__x_xpd__[2][1] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[24] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[25] += (-1.0f * __x_xpd__[2][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_1__[6] += (__x_xpd__[3][6] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[7] += (-1.0f * __x_xpd__[3][7] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[8] += (__x_xpd__[3][8] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[9] += (__x_xpd__[3][3] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[10] += (__x_xpd__[3][4] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[11] += (__x_xpd__[3][5] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[12] += (__x_xpd__[3][0] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[13] += (__x_xpd__[3][1] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[14] += (__x_xpd__[3][2] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[15] += (__x_xpd__[3][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_1__[1] += (__x_xpd__[4][4] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[2] += (__x_xpd__[4][1] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[3] += (__x_xpd__[4][2] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[4] += (__x_xpd__[4][3] * __y_xpd__[5][0]);
				__tmp_coord_array_1__[5] += (__x_xpd__[4][0] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_1__[0] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_1__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	scalar scp(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)2), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar __temp_var_1__;
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 2) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 4) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (__x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 8) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]) + (__x_xpd__[3][5] * __y_xpd__[3][5]) + (__x_xpd__[3][2] * __y_xpd__[3][8]) + (__x_xpd__[3][6] * __y_xpd__[3][0]) + (__x_xpd__[3][4] * __y_xpd__[3][4]) + (__x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (__x_xpd__[3][0] * __y_xpd__[3][6]) + (__x_xpd__[3][8] * __y_xpd__[3][2]));

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 16) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[4][3]) + (__x_xpd__[4][4] * __y_xpd__[4][0]) + (__x_xpd__[4][0] * __y_xpd__[4][4]));

			}

		}
		if (((y.m_gu & 32) != 0)) {
			if (((x.m_gu & 32) != 0)) {
				__temp_var_1__.m_c[0] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		return __temp_var_1__;
	}
	mv gp(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)3), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_2__[32] ;
		mv_zero(__tmp_coord_array_2__, 32);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[4] += (__x_xpd__[1][3] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[5] += (__x_xpd__[1][4] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[6] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[7] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[8] += (__x_xpd__[2][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[9] += (__x_xpd__[2][3] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[10] += (__x_xpd__[2][4] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[11] += (__x_xpd__[2][5] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[12] += (__x_xpd__[2][6] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[13] += (__x_xpd__[2][7] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[14] += (__x_xpd__[2][8] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[15] += (__x_xpd__[2][9] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[16] += (__x_xpd__[3][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[17] += (__x_xpd__[3][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[18] += (__x_xpd__[3][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[19] += (__x_xpd__[3][3] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[20] += (__x_xpd__[3][4] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[21] += (__x_xpd__[3][5] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[22] += (__x_xpd__[3][6] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[23] += (__x_xpd__[3][7] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[24] += (__x_xpd__[3][8] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[25] += (__x_xpd__[3][9] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[26] += (__x_xpd__[4][0] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[27] += (__x_xpd__[4][1] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[28] += (__x_xpd__[4][2] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[29] += (__x_xpd__[4][3] * __y_xpd__[0][0]);
				__tmp_coord_array_2__[30] += (__x_xpd__[4][4] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[31] += (__x_xpd__[5][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_2__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);
				__tmp_coord_array_2__[4] += (__x_xpd__[0][0] * __y_xpd__[1][3]);
				__tmp_coord_array_2__[5] += (__x_xpd__[0][0] * __y_xpd__[1][4]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[0] += ((__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[1][4]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[10] += ((__x_xpd__[1][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[11] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[1][3]) + (__x_xpd__[1][3] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[12] += ((__x_xpd__[1][1] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][2]) + (__x_xpd__[1][2] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][3]) + (__x_xpd__[1][3] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][4]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[1][0]) + (__x_xpd__[2][0] * __y_xpd__[1][1]) + (__x_xpd__[2][2] * __y_xpd__[1][3]) + (__x_xpd__[2][1] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[2] += ((__x_xpd__[2][3] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[1][0]) + (__x_xpd__[2][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[1][1]) + (__x_xpd__[2][4] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[1][0]) + (__x_xpd__[2][1] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[4] += ((__x_xpd__[2][2] * __y_xpd__[1][4]) + (__x_xpd__[2][5] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[1][3]) + (__x_xpd__[2][9] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[16] += ((__x_xpd__[2][8] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[1][3]) + (__x_xpd__[2][4] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[17] += ((__x_xpd__[2][6] * __y_xpd__[1][3]) + (__x_xpd__[2][5] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[1][2]) + (__x_xpd__[2][7] * __y_xpd__[1][1]) + (__x_xpd__[2][3] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[2][8] * __y_xpd__[1][0]) + (__x_xpd__[2][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[20] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[1][1]) + (__x_xpd__[2][0] * __y_xpd__[1][4]) + (__x_xpd__[2][6] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[2][7] * __y_xpd__[1][0]) + (__x_xpd__[2][1] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[22] += ((__x_xpd__[2][4] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][2]) + (__x_xpd__[2][1] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[1][0]) + (__x_xpd__[2][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[24] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[1][1]) + (__x_xpd__[2][0] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[25] += ((__x_xpd__[2][5] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][3]) + (__x_xpd__[2][4] * __y_xpd__[1][1]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[6] += ((__x_xpd__[3][8] * __y_xpd__[1][2]) + (__x_xpd__[3][7] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[1][1]) + (__x_xpd__[3][6] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]) + (__x_xpd__[3][9] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[10] += ((__x_xpd__[3][9] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[11] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[1][0]) + (__x_xpd__[3][7] * __y_xpd__[1][4]) + (__x_xpd__[3][9] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][2]) + (__x_xpd__[3][1] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[1][4]) + (__x_xpd__[3][2] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[1][4]) + (__x_xpd__[3][0] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[26] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][3]) + (__x_xpd__[3][9] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[27] += ((__x_xpd__[3][6] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][0]) + (__x_xpd__[3][3] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[28] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[1][0]) + (__x_xpd__[3][4] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[29] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]) + (__x_xpd__[3][5] * __y_xpd__[1][1]) + (__x_xpd__[3][8] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[30] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[1][0]) + (__x_xpd__[3][6] * __y_xpd__[1][1]) + (__x_xpd__[3][8] * __y_xpd__[1][3]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[16] += ((__x_xpd__[4][1] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[17] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[1][2]) + (__x_xpd__[4][2] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[1][3]) + (__x_xpd__[4][3] * __y_xpd__[1][4]));
				__tmp_coord_array_2__[19] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[1][1]) + (__x_xpd__[4][1] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[20] += ((__x_xpd__[4][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[1][2]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[4][3] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][3]));
				__tmp_coord_array_2__[22] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[1][0]) + (__x_xpd__[4][4] * __y_xpd__[1][1]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[1][2]) + (__x_xpd__[4][2] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[24] += ((__x_xpd__[4][4] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[25] += ((__x_xpd__[4][4] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][0]));
				__tmp_coord_array_2__[31] += ((__x_xpd__[4][4] * __y_xpd__[1][4]) + (__x_xpd__[4][0] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[1][3]));

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[26] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][4]);
				__tmp_coord_array_2__[27] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][1]);
				__tmp_coord_array_2__[28] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][2]);
				__tmp_coord_array_2__[29] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][3]);
				__tmp_coord_array_2__[30] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][0]);

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[6] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_2__[7] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_2__[8] += (__x_xpd__[0][0] * __y_xpd__[2][2]);
				__tmp_coord_array_2__[9] += (__x_xpd__[0][0] * __y_xpd__[2][3]);
				__tmp_coord_array_2__[10] += (__x_xpd__[0][0] * __y_xpd__[2][4]);
				__tmp_coord_array_2__[11] += (__x_xpd__[0][0] * __y_xpd__[2][5]);
				__tmp_coord_array_2__[12] += (__x_xpd__[0][0] * __y_xpd__[2][6]);
				__tmp_coord_array_2__[13] += (__x_xpd__[0][0] * __y_xpd__[2][7]);
				__tmp_coord_array_2__[14] += (__x_xpd__[0][0] * __y_xpd__[2][8]);
				__tmp_coord_array_2__[15] += (__x_xpd__[0][0] * __y_xpd__[2][9]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[2] += ((__x_xpd__[1][3] * __y_xpd__[2][5]) + (__x_xpd__[1][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][1]) + (__x_xpd__[1][1] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (__x_xpd__[1][0] * __y_xpd__[2][7]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][5]) + (__x_xpd__[1][0] * __y_xpd__[2][8]) + (__x_xpd__[1][2] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[5] += ((__x_xpd__[1][2] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][9]) + (__x_xpd__[1][3] * __y_xpd__[2][8]) + (__x_xpd__[1][1] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[16] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][4]) + (__x_xpd__[1][2] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[17] += ((__x_xpd__[1][3] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][8]) + (__x_xpd__[1][4] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[18] += ((__x_xpd__[1][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][6]) + (__x_xpd__[1][4] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[19] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][9]) + (__x_xpd__[1][4] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[20] += ((__x_xpd__[1][0] * __y_xpd__[2][6]) + (__x_xpd__[1][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[21] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][9]) + (__x_xpd__[1][0] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[22] += ((__x_xpd__[1][3] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[23] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][2]) + (__x_xpd__[1][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[24] += ((__x_xpd__[1][2] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[25] += ((__x_xpd__[1][1] * __y_xpd__[2][4]) + (__x_xpd__[1][3] * __y_xpd__[2][3]) + (__x_xpd__[1][2] * __y_xpd__[2][5]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[0] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][8]) + (__x_xpd__[2][9] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[2][3]) + (__x_xpd__[2][0] * __y_xpd__[2][9]) + (__x_xpd__[2][2] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][0]) + (__x_xpd__[2][3] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][2]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[2][0]) + (__x_xpd__[2][4] * __y_xpd__[2][2]) + (__x_xpd__[2][1] * __y_xpd__[2][9]) + (__x_xpd__[2][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[8] += ((__x_xpd__[2][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][5]) + (__x_xpd__[2][5] * __y_xpd__[2][0]) + (__x_xpd__[2][1] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][5]) + (__x_xpd__[2][1] * __y_xpd__[2][6]) + (__x_xpd__[2][5] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][1]) + (__x_xpd__[2][7] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[10] += ((__x_xpd__[2][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][3]) + (__x_xpd__[2][2] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][2]) + (__x_xpd__[2][8] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[2][0] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][6]) + (__x_xpd__[2][6] * __y_xpd__[2][2]) + (__x_xpd__[2][4] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[2][8]) + (__x_xpd__[2][3] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][9]) + (__x_xpd__[2][8] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][3]) + (__x_xpd__[2][9] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[13] += ((__x_xpd__[2][6] * __y_xpd__[2][3]) + (__x_xpd__[2][4] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][4]) + (__x_xpd__[2][9] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[14] += ((__x_xpd__[2][7] * __y_xpd__[2][4]) + (__x_xpd__[2][9] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][7]) + (__x_xpd__[2][5] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]) + (__x_xpd__[2][1] * __y_xpd__[2][7]) + (__x_xpd__[2][2] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (__x_xpd__[2][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[26] += ((__x_xpd__[2][3] * __y_xpd__[2][8]) + (__x_xpd__[2][8] * __y_xpd__[2][3]) + (__x_xpd__[2][5] * __y_xpd__[2][7]) + (__x_xpd__[2][6] * __y_xpd__[2][4]) + (__x_xpd__[2][7] * __y_xpd__[2][5]) + (__x_xpd__[2][4] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[27] += ((__x_xpd__[2][9] * __y_xpd__[2][4]) + (__x_xpd__[2][4] * __y_xpd__[2][9]) + (__x_xpd__[2][1] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][2]) + (__x_xpd__[2][8] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][7]));
				__tmp_coord_array_2__[28] += ((__x_xpd__[2][9] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][8]) + (__x_xpd__[2][6] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][0]) + (__x_xpd__[2][5] * __y_xpd__[2][9]) + (__x_xpd__[2][2] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[29] += ((__x_xpd__[2][3] * __y_xpd__[2][9]) + (__x_xpd__[2][0] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][1]) + (__x_xpd__[2][7] * __y_xpd__[2][0]) + (__x_xpd__[2][9] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[30] += ((__x_xpd__[2][3] * __y_xpd__[2][2]) + (__x_xpd__[2][5] * __y_xpd__[2][1]) + (__x_xpd__[2][0] * __y_xpd__[2][4]) + (__x_xpd__[2][2] * __y_xpd__[2][3]) + (__x_xpd__[2][1] * __y_xpd__[2][5]) + (__x_xpd__[2][4] * __y_xpd__[2][0]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][3]) + (__x_xpd__[3][7] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[2] += ((__x_xpd__[3][7] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][1]) + (__x_xpd__[3][8] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][4]) + (__x_xpd__[3][1] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][5]) + (__x_xpd__[3][6] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][2]) + (__x_xpd__[3][2] * __y_xpd__[2][0]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][6]) + (__x_xpd__[3][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[16] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[2][9]) + (__x_xpd__[3][3] * __y_xpd__[2][7]) + (__x_xpd__[3][2] * __y_xpd__[2][5]) + (__x_xpd__[3][9] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[17] += ((__x_xpd__[3][9] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][6]) + (__x_xpd__[3][4] * __y_xpd__[2][8]) + (__x_xpd__[3][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][5]) + (__x_xpd__[3][5] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][7]) + (__x_xpd__[3][1] * __y_xpd__[2][4]) + (__x_xpd__[3][9] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[3][1] * __y_xpd__[2][0]) + (__x_xpd__[3][5] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][5]));
				__tmp_coord_array_2__[20] += ((__x_xpd__[3][7] * __y_xpd__[2][8]) + (__x_xpd__[3][8] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][3]) + (__x_xpd__[3][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][2]) + (__x_xpd__[3][2] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[21] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][0]) + (__x_xpd__[3][6] * __y_xpd__[2][8]) + (__x_xpd__[3][4] * __y_xpd__[2][3]) + (__x_xpd__[3][0] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[22] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][0]) + (__x_xpd__[3][8] * __y_xpd__[2][5]) + (__x_xpd__[3][3] * __y_xpd__[2][1]) + (__x_xpd__[3][6] * __y_xpd__[2][9]) + (__x_xpd__[3][7] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[23] += ((__x_xpd__[3][3] * __y_xpd__[2][0]) + (__x_xpd__[3][8] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][2]) + (__x_xpd__[3][9] * __y_xpd__[2][1]) + (__x_xpd__[3][7] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[24] += ((__x_xpd__[3][8] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][4]) + (__x_xpd__[3][5] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][2]));
				__tmp_coord_array_2__[25] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][0]) + (__x_xpd__[3][6] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][1]) + (__x_xpd__[3][8] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[31] += ((__x_xpd__[3][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][7]) + (__x_xpd__[3][1] * __y_xpd__[2][1]) + (__x_xpd__[3][6] * __y_xpd__[2][6]) + (__x_xpd__[3][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][9]) + (__x_xpd__[3][5] * __y_xpd__[2][5]) + (__x_xpd__[3][2] * __y_xpd__[2][2]) + (__x_xpd__[3][0] * __y_xpd__[2][0]) + (__x_xpd__[3][8] * __y_xpd__[2][8]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[2][1]) + (__x_xpd__[4][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[4][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][2]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][0]) + (__x_xpd__[4][1] * __y_xpd__[2][1]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][8]) + (__x_xpd__[4][3] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][2]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][0]) + (__x_xpd__[4][1] * __y_xpd__[2][9]));
				__tmp_coord_array_2__[11] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[2][1]) + (__x_xpd__[4][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][7]));
				__tmp_coord_array_2__[12] += ((__x_xpd__[4][3] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][5]) + (__x_xpd__[4][1] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][7]) + (__x_xpd__[4][2] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][4]));
				__tmp_coord_array_2__[26] += ((__x_xpd__[4][1] * __y_xpd__[2][6]) + (__x_xpd__[4][2] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][9]) + (__x_xpd__[4][3] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[27] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][3]) + (__x_xpd__[4][3] * __y_xpd__[2][5]) + (__x_xpd__[4][4] * __y_xpd__[2][6]));
				__tmp_coord_array_2__[28] += ((__x_xpd__[4][4] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][4]) + (__x_xpd__[4][1] * __y_xpd__[2][3]));
				__tmp_coord_array_2__[29] += ((__x_xpd__[4][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][5]) + (__x_xpd__[4][4] * __y_xpd__[2][8]));
				__tmp_coord_array_2__[30] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][2]) + (__x_xpd__[4][4] * __y_xpd__[2][9]));

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[16] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][6]);
				__tmp_coord_array_2__[17] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][7]);
				__tmp_coord_array_2__[18] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][8]);
				__tmp_coord_array_2__[19] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][3]);
				__tmp_coord_array_2__[20] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][4]);
				__tmp_coord_array_2__[21] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][5]);
				__tmp_coord_array_2__[22] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][0]);
				__tmp_coord_array_2__[23] += (__x_xpd__[5][0] * __y_xpd__[2][1]);
				__tmp_coord_array_2__[24] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][2]);
				__tmp_coord_array_2__[25] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][9]);

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[16] += (__x_xpd__[0][0] * __y_xpd__[3][0]);
				__tmp_coord_array_2__[17] += (__x_xpd__[0][0] * __y_xpd__[3][1]);
				__tmp_coord_array_2__[18] += (__x_xpd__[0][0] * __y_xpd__[3][2]);
				__tmp_coord_array_2__[19] += (__x_xpd__[0][0] * __y_xpd__[3][3]);
				__tmp_coord_array_2__[20] += (__x_xpd__[0][0] * __y_xpd__[3][4]);
				__tmp_coord_array_2__[21] += (__x_xpd__[0][0] * __y_xpd__[3][5]);
				__tmp_coord_array_2__[22] += (__x_xpd__[0][0] * __y_xpd__[3][6]);
				__tmp_coord_array_2__[23] += (__x_xpd__[0][0] * __y_xpd__[3][7]);
				__tmp_coord_array_2__[24] += (__x_xpd__[0][0] * __y_xpd__[3][8]);
				__tmp_coord_array_2__[25] += (__x_xpd__[0][0] * __y_xpd__[3][9]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[6] += ((__x_xpd__[1][2] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][4]) + (__x_xpd__[1][3] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[1][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][2]) + (__x_xpd__[1][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][0]) + (__x_xpd__[1][1] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[11] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][1]) + (__x_xpd__[1][2] * __y_xpd__[3][9]) + (__x_xpd__[1][4] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]) + (__x_xpd__[1][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]) + (__x_xpd__[1][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][3]) + (__x_xpd__[1][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[26] += ((__x_xpd__[1][1] * __y_xpd__[3][0]) + (__x_xpd__[1][2] * __y_xpd__[3][1]) + (__x_xpd__[1][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[27] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]) + (__x_xpd__[1][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][3]) + (__x_xpd__[1][3] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[28] += ((__x_xpd__[1][0] * __y_xpd__[3][1]) + (__x_xpd__[1][1] * __y_xpd__[3][3]) + (__x_xpd__[1][4] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[29] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]) + (__x_xpd__[1][0] * __y_xpd__[3][2]) + (__x_xpd__[1][2] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[30] += ((__x_xpd__[1][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][8]) + (__x_xpd__[1][2] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][6]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][6]) + (__x_xpd__[2][5] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]) + (__x_xpd__[2][7] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][4]) + (__x_xpd__[2][8] * __y_xpd__[3][7]) + (__x_xpd__[2][2] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[3] += ((__x_xpd__[2][0] * __y_xpd__[3][2]) + (__x_xpd__[2][8] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][6]) + (__x_xpd__[2][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[16] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[3][3]) + (__x_xpd__[2][8] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][2]) + (__x_xpd__[2][3] * __y_xpd__[3][1]) + (__x_xpd__[2][9] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[17] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[3][4]) + (__x_xpd__[2][9] * __y_xpd__[3][1]) + (__x_xpd__[2][4] * __y_xpd__[3][2]) + (__x_xpd__[2][6] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[3][9]) + (__x_xpd__[2][7] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][5]) + (__x_xpd__[2][9] * __y_xpd__[3][2]) + (__x_xpd__[2][5] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[2][6] * __y_xpd__[3][7]) + (__x_xpd__[2][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]) + (__x_xpd__[2][7] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][5]) + (__x_xpd__[2][5] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[20] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][8]) + (__x_xpd__[2][2] * __y_xpd__[3][1]) + (__x_xpd__[2][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[2][0] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][6]) + (__x_xpd__[2][6] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][4]) + (__x_xpd__[2][4] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[22] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][8]) + (__x_xpd__[2][2] * __y_xpd__[3][5]) + (__x_xpd__[2][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[23] += ((__x_xpd__[2][2] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][9]) + (__x_xpd__[2][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[24] += ((__x_xpd__[2][2] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][8]) + (__x_xpd__[2][4] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][5]) + (__x_xpd__[2][1] * __y_xpd__[3][4]) + (__x_xpd__[2][5] * __y_xpd__[3][6]));
				__tmp_coord_array_2__[25] += ((__x_xpd__[2][2] * __y_xpd__[3][2]) + (__x_xpd__[2][7] * __y_xpd__[3][7]) + (__x_xpd__[2][0] * __y_xpd__[3][0]) + (__x_xpd__[2][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[31] += ((__x_xpd__[2][2] * __y_xpd__[3][2]) + (__x_xpd__[2][0] * __y_xpd__[3][0]) + (__x_xpd__[2][8] * __y_xpd__[3][8]) + (__x_xpd__[2][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][9]) + (__x_xpd__[2][6] * __y_xpd__[3][6]) + (__x_xpd__[2][3] * __y_xpd__[3][3]) + (__x_xpd__[2][5] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][7]) + (__x_xpd__[2][4] * __y_xpd__[3][4]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[0] += ((__x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][1]) + (__x_xpd__[3][4] * __y_xpd__[3][4]) + (__x_xpd__[3][8] * __y_xpd__[3][2]) + (__x_xpd__[3][6] * __y_xpd__[3][0]) + (__x_xpd__[3][2] * __y_xpd__[3][8]) + (__x_xpd__[3][0] * __y_xpd__[3][6]) + (__x_xpd__[3][5] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[3][3]) + (__x_xpd__[3][9] * __y_xpd__[3][6]) + (__x_xpd__[3][5] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][9]) + (__x_xpd__[3][3] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[7] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[3][3]) + (__x_xpd__[3][8] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][8]) + (__x_xpd__[3][3] * __y_xpd__[3][6]) + (__x_xpd__[3][7] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[8] += ((__x_xpd__[3][6] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][9]) + (__x_xpd__[3][9] * __y_xpd__[3][8]) + (__x_xpd__[3][7] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][6]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[3][6]) + (__x_xpd__[3][6] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][4]) + (__x_xpd__[3][4] * __y_xpd__[3][5]) + (__x_xpd__[3][7] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[10] += ((__x_xpd__[3][1] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][1]) + (__x_xpd__[3][5] * __y_xpd__[3][3]) + (__x_xpd__[3][2] * __y_xpd__[3][7]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[3][3] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][2]) + (__x_xpd__[3][2] * __y_xpd__[3][6]) + (__x_xpd__[3][8] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[3][1]) + (__x_xpd__[3][5] * __y_xpd__[3][2]) + (__x_xpd__[3][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][5]) + (__x_xpd__[3][1] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][2]) + (__x_xpd__[3][2] * __y_xpd__[3][4]) + (__x_xpd__[3][3] * __y_xpd__[3][0]) + (__x_xpd__[3][1] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[3][0]) + (__x_xpd__[3][4] * __y_xpd__[3][1]) + (__x_xpd__[3][0] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][4]) + (__x_xpd__[3][2] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]) + (__x_xpd__[3][2] * __y_xpd__[3][8]) + (__x_xpd__[3][0] * __y_xpd__[3][6]) + (__x_xpd__[3][7] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[26] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[27] += ((__x_xpd__[3][1] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][4]) + (__x_xpd__[3][8] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][9]) + (__x_xpd__[3][2] * __y_xpd__[3][7]) + (__x_xpd__[3][7] * __y_xpd__[3][2]));
				__tmp_coord_array_2__[28] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][5]) + (__x_xpd__[3][6] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][0]) + (__x_xpd__[3][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[29] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[30] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[3][6]) + (__x_xpd__[3][5] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][4]) + (__x_xpd__[3][7] * __y_xpd__[3][5]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][7]) + (__x_xpd__[4][1] * __y_xpd__[3][6]) + (__x_xpd__[4][3] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][0]) + (__x_xpd__[4][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[3][5]) + (__x_xpd__[4][0] * __y_xpd__[3][6]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[3][3]) + (__x_xpd__[4][3] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[4] += ((__x_xpd__[4][0] * __y_xpd__[3][8]) + (__x_xpd__[4][1] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[3][1]) + (__x_xpd__[4][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][0]));
				__tmp_coord_array_2__[16] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[3][2]) + (__x_xpd__[4][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[17] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[3][0]) + (__x_xpd__[4][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][5]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[3][1]) + (__x_xpd__[4][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[19] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][2]) + (__x_xpd__[4][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[20] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][6]) + (__x_xpd__[4][1] * __y_xpd__[3][9]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[4][2] * __y_xpd__[3][9]) + (__x_xpd__[4][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][1]));
				__tmp_coord_array_2__[22] += ((__x_xpd__[4][2] * __y_xpd__[3][8]) + (__x_xpd__[4][3] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][4]));
				__tmp_coord_array_2__[23] += ((__x_xpd__[4][4] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[3][6]) + (__x_xpd__[4][1] * __y_xpd__[3][8]));
				__tmp_coord_array_2__[24] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][3]));
				__tmp_coord_array_2__[25] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][4]));

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[6] += (__x_xpd__[5][0] * __y_xpd__[3][6]);
				__tmp_coord_array_2__[7] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][7]);
				__tmp_coord_array_2__[8] += (__x_xpd__[5][0] * __y_xpd__[3][8]);
				__tmp_coord_array_2__[9] += (__x_xpd__[5][0] * __y_xpd__[3][3]);
				__tmp_coord_array_2__[10] += (__x_xpd__[5][0] * __y_xpd__[3][4]);
				__tmp_coord_array_2__[11] += (__x_xpd__[5][0] * __y_xpd__[3][5]);
				__tmp_coord_array_2__[12] += (__x_xpd__[5][0] * __y_xpd__[3][0]);
				__tmp_coord_array_2__[13] += (__x_xpd__[5][0] * __y_xpd__[3][1]);
				__tmp_coord_array_2__[14] += (__x_xpd__[5][0] * __y_xpd__[3][2]);
				__tmp_coord_array_2__[15] += (__x_xpd__[5][0] * __y_xpd__[3][9]);

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[26] += (__x_xpd__[0][0] * __y_xpd__[4][0]);
				__tmp_coord_array_2__[27] += (__x_xpd__[0][0] * __y_xpd__[4][1]);
				__tmp_coord_array_2__[28] += (__x_xpd__[0][0] * __y_xpd__[4][2]);
				__tmp_coord_array_2__[29] += (__x_xpd__[0][0] * __y_xpd__[4][3]);
				__tmp_coord_array_2__[30] += (__x_xpd__[0][0] * __y_xpd__[4][4]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[16] += ((__x_xpd__[1][1] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[17] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][2]) + (__x_xpd__[1][2] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[18] += ((__x_xpd__[1][3] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[19] += ((__x_xpd__[1][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[20] += ((__x_xpd__[1][2] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[21] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[4][3]) + (__x_xpd__[1][3] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[22] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[4][4]) + (__x_xpd__[1][0] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[23] += ((__x_xpd__[1][2] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[24] += ((__x_xpd__[1][0] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[25] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][4]) + (__x_xpd__[1][0] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[31] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][1]) + (__x_xpd__[1][0] * __y_xpd__[4][0]) + (__x_xpd__[1][4] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][3]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][4]) + (__x_xpd__[2][2] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[2][0] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[2][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][4]) + (__x_xpd__[2][1] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[9] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[4][0]) + (__x_xpd__[2][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[10] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][0]) + (__x_xpd__[2][9] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[2][9] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]) + (__x_xpd__[2][7] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[13] += ((__x_xpd__[2][8] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][1]) + (__x_xpd__[2][6] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[15] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[26] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][2]) + (__x_xpd__[2][9] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[27] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][4]) + (__x_xpd__[2][3] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][3]) + (__x_xpd__[2][0] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[28] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][4]) + (__x_xpd__[2][4] * __y_xpd__[4][3]) + (__x_xpd__[2][1] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[29] += ((__x_xpd__[2][5] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][4]) + (__x_xpd__[2][2] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[30] += ((__x_xpd__[2][1] * __y_xpd__[4][2]) + (__x_xpd__[2][0] * __y_xpd__[4][1]) + (__x_xpd__[2][2] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][4]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[1] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][3]) + (__x_xpd__[3][9] * __y_xpd__[4][4]) + (__x_xpd__[3][7] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[2] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][0]) + (__x_xpd__[3][5] * __y_xpd__[4][3]) + (__x_xpd__[3][0] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[3] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[4][3]) + (__x_xpd__[3][3] * __y_xpd__[4][1]) + (__x_xpd__[3][1] * __y_xpd__[4][4]) + (__x_xpd__[3][7] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[4] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[4][1]) + (__x_xpd__[3][2] * __y_xpd__[4][4]) + (__x_xpd__[3][4] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[5] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[4][0]) + (__x_xpd__[3][1] * __y_xpd__[4][2]) + (__x_xpd__[3][0] * __y_xpd__[4][1]) + (__x_xpd__[3][2] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[16] += ((__x_xpd__[3][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[17] += ((__x_xpd__[3][2] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[4][0]));
				__tmp_coord_array_2__[18] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][0]) + (__x_xpd__[3][0] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[19] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[4][0]) + (__x_xpd__[3][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[20] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][0]) + (__x_xpd__[3][9] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[21] += ((__x_xpd__[3][9] * __y_xpd__[4][2]) + (__x_xpd__[3][7] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[22] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[4][4]) + (__x_xpd__[3][8] * __y_xpd__[4][2]) + (__x_xpd__[3][7] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[23] += ((__x_xpd__[3][5] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][3]) + (__x_xpd__[3][8] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[24] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[25] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][1]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[0] += ((__x_xpd__[4][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][2]) + (__x_xpd__[4][4] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[6] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[4][1]) + (__x_xpd__[4][1] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[7] += ((__x_xpd__[4][2] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[8] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[4][3]) + (__x_xpd__[4][3] * __y_xpd__[4][4]));
				__tmp_coord_array_2__[9] += ((__x_xpd__[4][2] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[10] += ((__x_xpd__[4][3] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[11] += ((__x_xpd__[4][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[12] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[4][0]) + (__x_xpd__[4][0] * __y_xpd__[4][1]));
				__tmp_coord_array_2__[13] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[4][0]) + (__x_xpd__[4][0] * __y_xpd__[4][2]));
				__tmp_coord_array_2__[14] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[4][0]) + (__x_xpd__[4][0] * __y_xpd__[4][3]));
				__tmp_coord_array_2__[15] += ((__x_xpd__[4][0] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[4][0]));

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[5][0] * __y_xpd__[4][4]);
				__tmp_coord_array_2__[2] += (__x_xpd__[5][0] * __y_xpd__[4][1]);
				__tmp_coord_array_2__[3] += (__x_xpd__[5][0] * __y_xpd__[4][2]);
				__tmp_coord_array_2__[4] += (__x_xpd__[5][0] * __y_xpd__[4][3]);
				__tmp_coord_array_2__[5] += (__x_xpd__[5][0] * __y_xpd__[4][0]);

			}

		}
		if (((y.m_gu & 32) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_2__[31] += (__x_xpd__[0][0] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_2__[26] += (-1.0f * __x_xpd__[1][4] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[27] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[28] += (-1.0f * __x_xpd__[1][2] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[29] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[30] += (-1.0f * __x_xpd__[1][0] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_2__[16] += (-1.0f * __x_xpd__[2][6] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[17] += (-1.0f * __x_xpd__[2][7] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[18] += (-1.0f * __x_xpd__[2][8] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[19] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[20] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[21] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[22] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[23] += (__x_xpd__[2][1] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[24] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[25] += (-1.0f * __x_xpd__[2][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_2__[6] += (__x_xpd__[3][6] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[7] += (-1.0f * __x_xpd__[3][7] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[8] += (__x_xpd__[3][8] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[9] += (__x_xpd__[3][3] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[10] += (__x_xpd__[3][4] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[11] += (__x_xpd__[3][5] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[12] += (__x_xpd__[3][0] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[13] += (__x_xpd__[3][1] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[14] += (__x_xpd__[3][2] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[15] += (__x_xpd__[3][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_2__[1] += (__x_xpd__[4][4] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[2] += (__x_xpd__[4][1] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[3] += (__x_xpd__[4][2] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[4] += (__x_xpd__[4][3] * __y_xpd__[5][0]);
				__tmp_coord_array_2__[5] += (__x_xpd__[4][0] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_2__[0] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_2__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv gpEM(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)4), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_3__[32] ;
		mv_zero(__tmp_coord_array_3__, 32);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[4] += (__x_xpd__[1][3] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[5] += (__x_xpd__[1][4] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[6] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[7] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[8] += (__x_xpd__[2][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[9] += (__x_xpd__[2][3] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[10] += (__x_xpd__[2][4] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[11] += (__x_xpd__[2][5] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[12] += (__x_xpd__[2][6] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[13] += (__x_xpd__[2][7] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[14] += (__x_xpd__[2][8] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[15] += (__x_xpd__[2][9] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[16] += (__x_xpd__[3][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[17] += (__x_xpd__[3][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[18] += (__x_xpd__[3][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[19] += (__x_xpd__[3][3] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[20] += (__x_xpd__[3][4] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[21] += (__x_xpd__[3][5] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[22] += (__x_xpd__[3][6] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[23] += (__x_xpd__[3][7] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[24] += (__x_xpd__[3][8] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[25] += (__x_xpd__[3][9] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[26] += (__x_xpd__[4][0] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[27] += (__x_xpd__[4][1] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[28] += (__x_xpd__[4][2] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[29] += (__x_xpd__[4][3] * __y_xpd__[0][0]);
				__tmp_coord_array_3__[30] += (__x_xpd__[4][4] * __y_xpd__[0][0]);

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[31] += (__x_xpd__[5][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_3__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_3__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);
				__tmp_coord_array_3__[4] += (__x_xpd__[0][0] * __y_xpd__[1][3]);
				__tmp_coord_array_3__[5] += (__x_xpd__[0][0] * __y_xpd__[1][4]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[0] += ((__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][0] * __y_xpd__[1][0]) + (__x_xpd__[1][4] * __y_xpd__[1][4]) + (__x_xpd__[1][3] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[6] += ((__x_xpd__[1][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[8] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[9] += ((__x_xpd__[1][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[10] += ((__x_xpd__[1][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[11] += ((__x_xpd__[1][3] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[12] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[1][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[14] += ((__x_xpd__[1][3] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][4]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[1] += ((__x_xpd__[2][1] * __y_xpd__[1][2]) + (__x_xpd__[2][0] * __y_xpd__[1][1]) + (__x_xpd__[2][2] * __y_xpd__[1][3]) + (__x_xpd__[2][9] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[2] += ((__x_xpd__[2][6] * __y_xpd__[1][4]) + (__x_xpd__[2][3] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[3] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[1][1]) + (__x_xpd__[2][4] * __y_xpd__[1][3]) + (__x_xpd__[2][7] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[4] += ((__x_xpd__[2][8] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][0]) + (__x_xpd__[2][5] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[5] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[16] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[1][3]) + (__x_xpd__[2][8] * __y_xpd__[1][2]) + (__x_xpd__[2][4] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[1][1]) + (__x_xpd__[2][5] * __y_xpd__[1][4]) + (__x_xpd__[2][6] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[18] += ((__x_xpd__[2][7] * __y_xpd__[1][1]) + (__x_xpd__[2][3] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[19] += ((__x_xpd__[2][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][3]) + (__x_xpd__[2][8] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[20] += ((__x_xpd__[2][6] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][1]) + (__x_xpd__[2][0] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[21] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[1][2]) + (__x_xpd__[2][1] * __y_xpd__[1][4]) + (__x_xpd__[2][7] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[22] += ((__x_xpd__[2][1] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][2]) + (__x_xpd__[2][4] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[2][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[24] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[1][1]) + (__x_xpd__[2][3] * __y_xpd__[1][0]) + (__x_xpd__[2][0] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[2][5] * __y_xpd__[1][2]) + (__x_xpd__[2][4] * __y_xpd__[1][1]) + (__x_xpd__[2][3] * __y_xpd__[1][3]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[6] += ((__x_xpd__[3][8] * __y_xpd__[1][2]) + (__x_xpd__[3][7] * __y_xpd__[1][3]) + (__x_xpd__[3][4] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[1][1]) + (__x_xpd__[3][6] * __y_xpd__[1][3]) + (__x_xpd__[3][5] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[8] += ((__x_xpd__[3][3] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[9] += ((__x_xpd__[3][9] * __y_xpd__[1][3]) + (__x_xpd__[3][2] * __y_xpd__[1][4]) + (__x_xpd__[3][8] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[10] += ((__x_xpd__[3][0] * __y_xpd__[1][4]) + (__x_xpd__[3][9] * __y_xpd__[1][1]) + (__x_xpd__[3][6] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[11] += ((__x_xpd__[3][1] * __y_xpd__[1][4]) + (__x_xpd__[3][9] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[12] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[1][2]) + (__x_xpd__[3][4] * __y_xpd__[1][0]) + (__x_xpd__[3][1] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[13] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[1][3]) + (__x_xpd__[3][5] * __y_xpd__[1][0]) + (__x_xpd__[3][2] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[14] += ((__x_xpd__[3][0] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][1]) + (__x_xpd__[3][3] * __y_xpd__[1][0]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[26] += ((__x_xpd__[3][9] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[27] += ((__x_xpd__[3][3] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][0]) + (__x_xpd__[3][6] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[28] += ((__x_xpd__[3][4] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[29] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]) + (__x_xpd__[3][5] * __y_xpd__[1][1]) + (__x_xpd__[3][8] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[30] += ((__x_xpd__[3][6] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][2]) + (__x_xpd__[3][8] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[1][0]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[16] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][1]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[19] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[1][1]) + (__x_xpd__[4][1] * __y_xpd__[1][2]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[1][2]) + (__x_xpd__[4][2] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[4][3] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][3]));
				__tmp_coord_array_3__[22] += ((__x_xpd__[4][4] * __y_xpd__[1][1]) + (__x_xpd__[4][1] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[23] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[4][4] * __y_xpd__[1][3]) + (__x_xpd__[4][3] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[25] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[1][0]) + (__x_xpd__[4][0] * __y_xpd__[1][4]));
				__tmp_coord_array_3__[31] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[1][3]) + (__x_xpd__[4][4] * __y_xpd__[1][4]) + (__x_xpd__[4][0] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[1][1]));

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[26] += (__x_xpd__[5][0] * __y_xpd__[1][0]);
				__tmp_coord_array_3__[27] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][1]);
				__tmp_coord_array_3__[28] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][2]);
				__tmp_coord_array_3__[29] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[1][3]);
				__tmp_coord_array_3__[30] += (__x_xpd__[5][0] * __y_xpd__[1][4]);

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[6] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_3__[7] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_3__[8] += (__x_xpd__[0][0] * __y_xpd__[2][2]);
				__tmp_coord_array_3__[9] += (__x_xpd__[0][0] * __y_xpd__[2][3]);
				__tmp_coord_array_3__[10] += (__x_xpd__[0][0] * __y_xpd__[2][4]);
				__tmp_coord_array_3__[11] += (__x_xpd__[0][0] * __y_xpd__[2][5]);
				__tmp_coord_array_3__[12] += (__x_xpd__[0][0] * __y_xpd__[2][6]);
				__tmp_coord_array_3__[13] += (__x_xpd__[0][0] * __y_xpd__[2][7]);
				__tmp_coord_array_3__[14] += (__x_xpd__[0][0] * __y_xpd__[2][8]);
				__tmp_coord_array_3__[15] += (__x_xpd__[0][0] * __y_xpd__[2][9]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[1] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[2] += ((__x_xpd__[1][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][3]) + (__x_xpd__[1][0] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[3] += ((__x_xpd__[1][1] * __y_xpd__[2][3]) + (__x_xpd__[1][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][7]));
				__tmp_coord_array_3__[4] += ((__x_xpd__[1][0] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][5]) + (__x_xpd__[1][2] * __y_xpd__[2][4]));
				__tmp_coord_array_3__[5] += ((__x_xpd__[1][0] * __y_xpd__[2][9]) + (__x_xpd__[1][1] * __y_xpd__[2][6]) + (__x_xpd__[1][3] * __y_xpd__[2][8]) + (__x_xpd__[1][2] * __y_xpd__[2][7]));
				__tmp_coord_array_3__[16] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][4]) + (__x_xpd__[1][2] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[17] += ((__x_xpd__[1][4] * __y_xpd__[2][5]) + (__x_xpd__[1][3] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][6]) + (__x_xpd__[1][1] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[19] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][9]) + (__x_xpd__[1][4] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][9]) + (__x_xpd__[1][4] * __y_xpd__[2][0]) + (__x_xpd__[1][0] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[21] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][9]) + (__x_xpd__[1][0] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][1]));
				__tmp_coord_array_3__[22] += ((__x_xpd__[1][3] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[23] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[2][5]) + (__x_xpd__[1][3] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[1][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][1]) + (__x_xpd__[1][2] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[1][2] * __y_xpd__[2][5]) + (__x_xpd__[1][3] * __y_xpd__[2][3]) + (__x_xpd__[1][1] * __y_xpd__[2][4]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[0] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[6] += ((__x_xpd__[2][3] * __y_xpd__[2][1]) + (__x_xpd__[2][6] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][2]) + (__x_xpd__[2][2] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][4]) + (__x_xpd__[2][4] * __y_xpd__[2][2]) + (__x_xpd__[2][7] * __y_xpd__[2][9]) + (__x_xpd__[2][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[8] += ((__x_xpd__[2][5] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][8]) + (__x_xpd__[2][8] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][1]) + (__x_xpd__[2][1] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[9] += ((__x_xpd__[2][7] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][7]) + (__x_xpd__[2][5] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][5]) + (__x_xpd__[2][1] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[10] += ((__x_xpd__[2][8] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][8]) + (__x_xpd__[2][2] * __y_xpd__[2][1]) + (__x_xpd__[2][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][6]) + (__x_xpd__[2][0] * __y_xpd__[2][2]) + (__x_xpd__[2][4] * __y_xpd__[2][3]) + (__x_xpd__[2][6] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[2][9] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][9]) + (__x_xpd__[2][3] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][3]) + (__x_xpd__[2][8] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[2][6] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][4]) + (__x_xpd__[2][9] * __y_xpd__[2][1]) + (__x_xpd__[2][4] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][9]));
				__tmp_coord_array_3__[14] += ((__x_xpd__[2][7] * __y_xpd__[2][4]) + (__x_xpd__[2][5] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][9]) + (__x_xpd__[2][9] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[2][0]) + (__x_xpd__[2][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][2]) + (__x_xpd__[2][0] * __y_xpd__[2][6]) + (__x_xpd__[2][2] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[26] += ((__x_xpd__[2][7] * __y_xpd__[2][5]) + (__x_xpd__[2][6] * __y_xpd__[2][4]) + (__x_xpd__[2][4] * __y_xpd__[2][6]) + (__x_xpd__[2][8] * __y_xpd__[2][3]) + (__x_xpd__[2][5] * __y_xpd__[2][7]) + (__x_xpd__[2][3] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[27] += ((__x_xpd__[2][1] * __y_xpd__[2][8]) + (__x_xpd__[2][9] * __y_xpd__[2][4]) + (__x_xpd__[2][8] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][7]) + (__x_xpd__[2][4] * __y_xpd__[2][9]));
				__tmp_coord_array_3__[28] += ((__x_xpd__[2][6] * __y_xpd__[2][2]) + (__x_xpd__[2][9] * __y_xpd__[2][5]) + (__x_xpd__[2][5] * __y_xpd__[2][9]) + (__x_xpd__[2][2] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[29] += ((__x_xpd__[2][0] * __y_xpd__[2][7]) + (__x_xpd__[2][7] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][1]) + (__x_xpd__[2][3] * __y_xpd__[2][9]) + (__x_xpd__[2][9] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[30] += ((__x_xpd__[2][4] * __y_xpd__[2][0]) + (__x_xpd__[2][0] * __y_xpd__[2][4]) + (__x_xpd__[2][5] * __y_xpd__[2][1]) + (__x_xpd__[2][1] * __y_xpd__[2][5]) + (__x_xpd__[2][2] * __y_xpd__[2][3]) + (__x_xpd__[2][3] * __y_xpd__[2][2]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[1] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[2][8]) + (__x_xpd__[3][7] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][4]));
				__tmp_coord_array_3__[2] += ((__x_xpd__[3][1] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][7]) + (__x_xpd__[3][8] * __y_xpd__[2][1]) + (__x_xpd__[3][4] * __y_xpd__[2][9]) + (__x_xpd__[3][7] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][4]));
				__tmp_coord_array_3__[3] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][0]) + (__x_xpd__[3][2] * __y_xpd__[2][6]) + (__x_xpd__[3][5] * __y_xpd__[2][9]) + (__x_xpd__[3][6] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[4] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[2][1]) + (__x_xpd__[3][0] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][0]) + (__x_xpd__[3][3] * __y_xpd__[2][9]));
				__tmp_coord_array_3__[5] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[16] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[2][2]) + (__x_xpd__[3][3] * __y_xpd__[2][1]) + (__x_xpd__[3][6] * __y_xpd__[2][9]) + (__x_xpd__[3][2] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][3]) + (__x_xpd__[3][9] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[2][0]) + (__x_xpd__[3][4] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][4]) + (__x_xpd__[3][0] * __y_xpd__[2][3]) + (__x_xpd__[3][9] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][9]));
				__tmp_coord_array_3__[18] += ((__x_xpd__[3][9] * __y_xpd__[2][8]) + (__x_xpd__[3][5] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][5]) + (__x_xpd__[3][8] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][1]) + (__x_xpd__[3][1] * __y_xpd__[2][4]));
				__tmp_coord_array_3__[19] += ((__x_xpd__[3][1] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][1]) + (__x_xpd__[3][5] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][7]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[2][2]) + (__x_xpd__[3][7] * __y_xpd__[2][8]) + (__x_xpd__[3][3] * __y_xpd__[2][5]) + (__x_xpd__[3][2] * __y_xpd__[2][1]) + (__x_xpd__[3][8] * __y_xpd__[2][7]));
				__tmp_coord_array_3__[21] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][0]) + (__x_xpd__[3][6] * __y_xpd__[2][8]) + (__x_xpd__[3][0] * __y_xpd__[2][2]) + (__x_xpd__[3][4] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[22] += ((-1.0f * __x_xpd__[3][0] * __y_xpd__[2][9]) + (__x_xpd__[3][8] * __y_xpd__[2][5]) + (__x_xpd__[3][3] * __y_xpd__[2][7]) + (__x_xpd__[3][7] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[3][8] * __y_xpd__[2][4]) + (__x_xpd__[3][1] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[2][8]) + (__x_xpd__[3][3] * __y_xpd__[2][6]) + (__x_xpd__[3][9] * __y_xpd__[2][1]));
				__tmp_coord_array_3__[24] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][2]) + (__x_xpd__[3][5] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[25] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[2][7]) + (__x_xpd__[3][8] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][1]) + (__x_xpd__[3][6] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[31] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[2][9]) + (__x_xpd__[3][2] * __y_xpd__[2][2]) + (__x_xpd__[3][5] * __y_xpd__[2][5]) + (__x_xpd__[3][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][7]) + (__x_xpd__[3][4] * __y_xpd__[2][4]) + (__x_xpd__[3][8] * __y_xpd__[2][8]) + (__x_xpd__[3][3] * __y_xpd__[2][3]) + (__x_xpd__[3][0] * __y_xpd__[2][0]) + (__x_xpd__[3][6] * __y_xpd__[2][6]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[6] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][7]) + (__x_xpd__[4][2] * __y_xpd__[2][8]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][8]) + (__x_xpd__[4][3] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[8] += ((__x_xpd__[4][1] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[9] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[10] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][6]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[2][1]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[4][3] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[4][1] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[2][1]) + (__x_xpd__[4][2] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][3]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[26] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[2][9]) + (__x_xpd__[4][3] * __y_xpd__[2][2]) + (__x_xpd__[4][2] * __y_xpd__[2][1]) + (__x_xpd__[4][1] * __y_xpd__[2][0]));
				__tmp_coord_array_3__[27] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][0]) + (__x_xpd__[4][4] * __y_xpd__[2][6]) + (__x_xpd__[4][3] * __y_xpd__[2][5]));
				__tmp_coord_array_3__[28] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[2][4]) + (__x_xpd__[4][1] * __y_xpd__[2][3]) + (__x_xpd__[4][4] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][1]));
				__tmp_coord_array_3__[29] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[2][5]) + (__x_xpd__[4][4] * __y_xpd__[2][8]) + (__x_xpd__[4][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[2][2]));
				__tmp_coord_array_3__[30] += ((__x_xpd__[4][0] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[2][8]));

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[16] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][0]);
				__tmp_coord_array_3__[17] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][1]);
				__tmp_coord_array_3__[18] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][2]);
				__tmp_coord_array_3__[19] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][3]);
				__tmp_coord_array_3__[20] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][4]);
				__tmp_coord_array_3__[21] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][5]);
				__tmp_coord_array_3__[22] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][6]);
				__tmp_coord_array_3__[23] += (__x_xpd__[5][0] * __y_xpd__[2][7]);
				__tmp_coord_array_3__[24] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[2][8]);
				__tmp_coord_array_3__[25] += (__x_xpd__[5][0] * __y_xpd__[2][9]);

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[16] += (__x_xpd__[0][0] * __y_xpd__[3][0]);
				__tmp_coord_array_3__[17] += (__x_xpd__[0][0] * __y_xpd__[3][1]);
				__tmp_coord_array_3__[18] += (__x_xpd__[0][0] * __y_xpd__[3][2]);
				__tmp_coord_array_3__[19] += (__x_xpd__[0][0] * __y_xpd__[3][3]);
				__tmp_coord_array_3__[20] += (__x_xpd__[0][0] * __y_xpd__[3][4]);
				__tmp_coord_array_3__[21] += (__x_xpd__[0][0] * __y_xpd__[3][5]);
				__tmp_coord_array_3__[22] += (__x_xpd__[0][0] * __y_xpd__[3][6]);
				__tmp_coord_array_3__[23] += (__x_xpd__[0][0] * __y_xpd__[3][7]);
				__tmp_coord_array_3__[24] += (__x_xpd__[0][0] * __y_xpd__[3][8]);
				__tmp_coord_array_3__[25] += (__x_xpd__[0][0] * __y_xpd__[3][9]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[6] += ((__x_xpd__[1][3] * __y_xpd__[3][7]) + (__x_xpd__[1][2] * __y_xpd__[3][8]) + (__x_xpd__[1][4] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[7] += ((__x_xpd__[1][4] * __y_xpd__[3][5]) + (__x_xpd__[1][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[8] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][6]) + (__x_xpd__[1][4] * __y_xpd__[3][3]));
				__tmp_coord_array_3__[9] += ((__x_xpd__[1][4] * __y_xpd__[3][2]) + (__x_xpd__[1][3] * __y_xpd__[3][9]) + (__x_xpd__[1][0] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[10] += ((__x_xpd__[1][4] * __y_xpd__[3][0]) + (__x_xpd__[1][0] * __y_xpd__[3][6]) + (__x_xpd__[1][1] * __y_xpd__[3][9]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[3][7]) + (__x_xpd__[1][2] * __y_xpd__[3][9]) + (__x_xpd__[1][4] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[1][3] * __y_xpd__[3][1]) + (__x_xpd__[1][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[1][0] * __y_xpd__[3][5]) + (__x_xpd__[1][1] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[14] += ((__x_xpd__[1][2] * __y_xpd__[3][0]) + (__x_xpd__[1][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[26] += ((__x_xpd__[1][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][9]) + (__x_xpd__[1][2] * __y_xpd__[3][1]) + (__x_xpd__[1][3] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[27] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[3][3]) + (__x_xpd__[1][3] * __y_xpd__[3][5]) + (__x_xpd__[1][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[28] += ((__x_xpd__[1][4] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][4]) + (__x_xpd__[1][1] * __y_xpd__[3][3]) + (__x_xpd__[1][0] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[29] += ((__x_xpd__[1][2] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][5]) + (__x_xpd__[1][0] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[30] += ((__x_xpd__[1][2] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][8]) + (__x_xpd__[1][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][6]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[1] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][5]) + (__x_xpd__[2][5] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[2] += ((__x_xpd__[2][2] * __y_xpd__[3][7]) + (__x_xpd__[2][9] * __y_xpd__[3][4]) + (__x_xpd__[2][1] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][9]) + (__x_xpd__[2][8] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[3] += ((__x_xpd__[2][9] * __y_xpd__[3][5]) + (__x_xpd__[2][6] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][0]) + (__x_xpd__[2][2] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[4] += ((__x_xpd__[2][7] * __y_xpd__[3][0]) + (__x_xpd__[2][9] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[5] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[16] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[3][9]) + (__x_xpd__[2][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][3]) + (__x_xpd__[2][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[17] += ((__x_xpd__[2][0] * __y_xpd__[3][3]) + (__x_xpd__[2][9] * __y_xpd__[3][7]) + (__x_xpd__[2][4] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[2][4] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][9]) + (__x_xpd__[2][5] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][5]) + (__x_xpd__[2][1] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[19] += ((__x_xpd__[2][5] * __y_xpd__[3][4]) + (__x_xpd__[2][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][1]) + (__x_xpd__[2][7] * __y_xpd__[3][6]) + (__x_xpd__[2][6] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[20] += ((__x_xpd__[2][2] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][2]) + (__x_xpd__[2][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[2][0] * __y_xpd__[3][2]) + (__x_xpd__[2][4] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][4]) + (__x_xpd__[2][6] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[22] += ((__x_xpd__[2][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][7]) + (__x_xpd__[2][8] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][8]) + (__x_xpd__[2][9] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][3]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[2][3] * __y_xpd__[3][6]) + (__x_xpd__[2][8] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[2][5] * __y_xpd__[3][6]) + (__x_xpd__[2][2] * __y_xpd__[3][9]) + (__x_xpd__[2][9] * __y_xpd__[3][2]) + (__x_xpd__[2][7] * __y_xpd__[3][4]) + (__x_xpd__[2][4] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[2][8] * __y_xpd__[3][2]) + (__x_xpd__[2][6] * __y_xpd__[3][0]) + (__x_xpd__[2][1] * __y_xpd__[3][7]) + (__x_xpd__[2][7] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[31] += ((__x_xpd__[2][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][9]) + (__x_xpd__[2][1] * __y_xpd__[3][1]) + (__x_xpd__[2][3] * __y_xpd__[3][3]) + (__x_xpd__[2][8] * __y_xpd__[3][8]) + (__x_xpd__[2][0] * __y_xpd__[3][0]) + (__x_xpd__[2][5] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][7]) + (__x_xpd__[2][4] * __y_xpd__[3][4]) + (__x_xpd__[2][6] * __y_xpd__[3][6]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[0] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]));
				__tmp_coord_array_3__[6] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][3]) + (__x_xpd__[3][9] * __y_xpd__[3][6]) + (__x_xpd__[3][3] * __y_xpd__[3][1]) + (__x_xpd__[3][2] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][9]));
				__tmp_coord_array_3__[7] += ((__x_xpd__[3][4] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][7]) + (__x_xpd__[3][7] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][0]) + (__x_xpd__[3][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[8] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[3][1]) + (__x_xpd__[3][5] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][9]) + (__x_xpd__[3][1] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][5]) + (__x_xpd__[3][9] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[9] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][1]) + (__x_xpd__[3][5] * __y_xpd__[3][4]) + (__x_xpd__[3][1] * __y_xpd__[3][0]) + (__x_xpd__[3][6] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[10] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[3][3]) + (__x_xpd__[3][7] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][2]) + (__x_xpd__[3][2] * __y_xpd__[3][1]) + (__x_xpd__[3][3] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[3][6]) + (__x_xpd__[3][0] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][4]) + (__x_xpd__[3][6] * __y_xpd__[3][8]) + (__x_xpd__[3][4] * __y_xpd__[3][3]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[3][0] * __y_xpd__[3][9]) + (__x_xpd__[3][7] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][0]) + (__x_xpd__[3][8] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[3][6] * __y_xpd__[3][3]) + (__x_xpd__[3][4] * __y_xpd__[3][8]) + (__x_xpd__[3][1] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][4]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[3][4]) + (__x_xpd__[3][4] * __y_xpd__[3][7]) + (__x_xpd__[3][2] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][5]) + (__x_xpd__[3][5] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[15] += ((__x_xpd__[3][2] * __y_xpd__[3][8]) + (__x_xpd__[3][0] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][0]) + (__x_xpd__[3][7] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[26] += ((__x_xpd__[3][3] * __y_xpd__[3][8]) + (__x_xpd__[3][8] * __y_xpd__[3][3]) + (__x_xpd__[3][6] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][5]) + (__x_xpd__[3][4] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[27] += ((__x_xpd__[3][7] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][4]) + (__x_xpd__[3][8] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][9]) + (__x_xpd__[3][1] * __y_xpd__[3][8]) + (__x_xpd__[3][2] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[28] += ((-1.0f * __x_xpd__[3][8] * __y_xpd__[3][0]) + (__x_xpd__[3][2] * __y_xpd__[3][6]) + (__x_xpd__[3][6] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[29] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[30] += ((__x_xpd__[3][2] * __y_xpd__[3][3]) + (__x_xpd__[3][5] * __y_xpd__[3][1]) + (__x_xpd__[3][0] * __y_xpd__[3][4]) + (__x_xpd__[3][1] * __y_xpd__[3][5]) + (__x_xpd__[3][4] * __y_xpd__[3][0]) + (__x_xpd__[3][3] * __y_xpd__[3][2]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[1] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][1]));
				__tmp_coord_array_3__[2] += ((__x_xpd__[4][4] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][0]) + (__x_xpd__[4][3] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[3] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[3][4]) + (__x_xpd__[4][1] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[4] += ((__x_xpd__[4][2] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][2]) + (__x_xpd__[4][4] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[5] += ((__x_xpd__[4][0] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][7]) + (__x_xpd__[4][3] * __y_xpd__[3][8]) + (__x_xpd__[4][1] * __y_xpd__[3][6]));
				__tmp_coord_array_3__[16] += ((__x_xpd__[4][3] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][4]) + (__x_xpd__[4][2] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[17] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][5]) + (__x_xpd__[4][3] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][3]));
				__tmp_coord_array_3__[19] += ((__x_xpd__[4][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][8]));
				__tmp_coord_array_3__[20] += ((__x_xpd__[4][1] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[4][4] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[21] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[3][1]) + (__x_xpd__[4][2] * __y_xpd__[3][9]) + (__x_xpd__[4][0] * __y_xpd__[3][7]));
				__tmp_coord_array_3__[22] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[3][4]) + (__x_xpd__[4][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[3][2]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[4][3] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][2]) + (__x_xpd__[4][0] * __y_xpd__[3][5]));
				__tmp_coord_array_3__[24] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[4][1] * __y_xpd__[3][1]) + (__x_xpd__[4][2] * __y_xpd__[3][0]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[4][2] * __y_xpd__[3][5]) + (__x_xpd__[4][1] * __y_xpd__[3][4]) + (__x_xpd__[4][3] * __y_xpd__[3][3]));

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[6] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][0]);
				__tmp_coord_array_3__[7] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][1]);
				__tmp_coord_array_3__[8] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][2]);
				__tmp_coord_array_3__[9] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][3]);
				__tmp_coord_array_3__[10] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][4]);
				__tmp_coord_array_3__[11] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][5]);
				__tmp_coord_array_3__[12] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][6]);
				__tmp_coord_array_3__[13] += (__x_xpd__[5][0] * __y_xpd__[3][7]);
				__tmp_coord_array_3__[14] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[3][8]);
				__tmp_coord_array_3__[15] += (__x_xpd__[5][0] * __y_xpd__[3][9]);

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[26] += (__x_xpd__[0][0] * __y_xpd__[4][0]);
				__tmp_coord_array_3__[27] += (__x_xpd__[0][0] * __y_xpd__[4][1]);
				__tmp_coord_array_3__[28] += (__x_xpd__[0][0] * __y_xpd__[4][2]);
				__tmp_coord_array_3__[29] += (__x_xpd__[0][0] * __y_xpd__[4][3]);
				__tmp_coord_array_3__[30] += (__x_xpd__[0][0] * __y_xpd__[4][4]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[16] += ((__x_xpd__[1][1] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[17] += ((__x_xpd__[1][0] * __y_xpd__[4][2]) + (__x_xpd__[1][2] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[18] += ((__x_xpd__[1][0] * __y_xpd__[4][3]) + (__x_xpd__[1][3] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[19] += ((__x_xpd__[1][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[20] += ((__x_xpd__[1][2] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[21] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[4][3]) + (__x_xpd__[1][3] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[22] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[1][4] * __y_xpd__[4][2]) + (__x_xpd__[1][2] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[24] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[25] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[31] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[4][2]) + (__x_xpd__[1][0] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][3]) + (__x_xpd__[1][4] * __y_xpd__[4][4]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[6] += ((__x_xpd__[2][8] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[7] += ((__x_xpd__[2][6] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[8] += ((__x_xpd__[2][7] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[9] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[10] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[12] += ((__x_xpd__[2][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[13] += ((__x_xpd__[2][2] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[4][1]) + (__x_xpd__[2][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[26] += ((__x_xpd__[2][9] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[27] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][4]) + (__x_xpd__[2][0] * __y_xpd__[4][0]) + (__x_xpd__[2][3] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[28] += ((__x_xpd__[2][4] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][4]) + (__x_xpd__[2][1] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[29] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][2]) + (__x_xpd__[2][2] * __y_xpd__[4][0]) + (__x_xpd__[2][5] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[30] += ((__x_xpd__[2][8] * __y_xpd__[4][3]) + (__x_xpd__[2][6] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][0]) + (__x_xpd__[2][7] * __y_xpd__[4][2]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[1] += ((__x_xpd__[3][9] * __y_xpd__[4][4]) + (__x_xpd__[3][2] * __y_xpd__[4][3]) + (__x_xpd__[3][1] * __y_xpd__[4][2]) + (__x_xpd__[3][0] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[2] += ((-1.0f * __x_xpd__[3][5] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][4]) + (__x_xpd__[3][3] * __y_xpd__[4][2]) + (__x_xpd__[3][0] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[3] += ((__x_xpd__[3][1] * __y_xpd__[4][0]) + (__x_xpd__[3][7] * __y_xpd__[4][4]) + (__x_xpd__[3][4] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[4] += ((__x_xpd__[3][5] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][4]) + (__x_xpd__[3][2] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[5] += ((__x_xpd__[3][7] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[16] += ((__x_xpd__[3][7] * __y_xpd__[4][3]) + (__x_xpd__[3][8] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[17] += ((__x_xpd__[3][6] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[18] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[19] += ((-1.0f * __x_xpd__[3][2] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][0]) + (__x_xpd__[3][9] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[20] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[4][0]) + (__x_xpd__[3][9] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[21] += ((__x_xpd__[3][7] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[4][4]) + (__x_xpd__[3][9] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[22] += ((__x_xpd__[3][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[23] += ((__x_xpd__[3][0] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[4][1]) + (__x_xpd__[3][5] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[24] += ((__x_xpd__[3][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[25] += ((__x_xpd__[3][3] * __y_xpd__[4][3]) + (__x_xpd__[3][4] * __y_xpd__[4][1]) + (__x_xpd__[3][5] * __y_xpd__[4][2]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[0] += ((__x_xpd__[4][2] * __y_xpd__[4][2]) + (__x_xpd__[4][0] * __y_xpd__[4][0]) + (__x_xpd__[4][1] * __y_xpd__[4][1]) + (__x_xpd__[4][3] * __y_xpd__[4][3]) + (__x_xpd__[4][4] * __y_xpd__[4][4]));
				__tmp_coord_array_3__[6] += ((__x_xpd__[4][1] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[4][0] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[7] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[4][2]) + (__x_xpd__[4][2] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[8] += ((-1.0f * __x_xpd__[4][0] * __y_xpd__[4][3]) + (__x_xpd__[4][3] * __y_xpd__[4][0]));
				__tmp_coord_array_3__[9] += ((__x_xpd__[4][1] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[10] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[4][2]) + (__x_xpd__[4][2] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[11] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[4][3]) + (__x_xpd__[4][3] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[12] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[4][4]) + (__x_xpd__[4][4] * __y_xpd__[4][1]));
				__tmp_coord_array_3__[13] += ((-1.0f * __x_xpd__[4][2] * __y_xpd__[4][4]) + (__x_xpd__[4][4] * __y_xpd__[4][2]));
				__tmp_coord_array_3__[14] += ((-1.0f * __x_xpd__[4][3] * __y_xpd__[4][4]) + (__x_xpd__[4][4] * __y_xpd__[4][3]));
				__tmp_coord_array_3__[15] += ((-1.0f * __x_xpd__[4][4] * __y_xpd__[4][0]) + (__x_xpd__[4][0] * __y_xpd__[4][4]));

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[5][0] * __y_xpd__[4][0]);
				__tmp_coord_array_3__[2] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[4][1]);
				__tmp_coord_array_3__[3] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[4][2]);
				__tmp_coord_array_3__[4] += (-1.0f * __x_xpd__[5][0] * __y_xpd__[4][3]);
				__tmp_coord_array_3__[5] += (__x_xpd__[5][0] * __y_xpd__[4][4]);

			}

		}
		if (((y.m_gu & 32) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_3__[31] += (__x_xpd__[0][0] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_3__[26] += (__x_xpd__[1][0] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[27] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[28] += (-1.0f * __x_xpd__[1][2] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[29] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[30] += (__x_xpd__[1][4] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_3__[16] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[17] += (-1.0f * __x_xpd__[2][1] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[18] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[19] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[20] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[21] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[22] += (-1.0f * __x_xpd__[2][6] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[23] += (__x_xpd__[2][7] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[24] += (-1.0f * __x_xpd__[2][8] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[25] += (__x_xpd__[2][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_3__[6] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[7] += (-1.0f * __x_xpd__[3][1] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[8] += (-1.0f * __x_xpd__[3][2] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[9] += (-1.0f * __x_xpd__[3][3] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[10] += (-1.0f * __x_xpd__[3][4] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[11] += (-1.0f * __x_xpd__[3][5] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[12] += (-1.0f * __x_xpd__[3][6] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[13] += (__x_xpd__[3][7] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[14] += (-1.0f * __x_xpd__[3][8] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[15] += (__x_xpd__[3][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_3__[1] += (__x_xpd__[4][0] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[2] += (-1.0f * __x_xpd__[4][1] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[3] += (-1.0f * __x_xpd__[4][2] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[4] += (-1.0f * __x_xpd__[4][3] * __y_xpd__[5][0]);
				__tmp_coord_array_3__[5] += (__x_xpd__[4][4] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_3__[0] += (__x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_3__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	scalar scpEM(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)5), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar __temp_var_1__;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 2) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[1][3] * __y_xpd__[1][3]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][4] * __y_xpd__[1][4]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][0] * __y_xpd__[1][0]));

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 4) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]));

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 8) != 0)) {
				__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][6]));

			}

		}
		if (((x.m_gu & 16) != 0)) {
			if (((y.m_gu & 16) != 0)) {
				__temp_var_1__.m_c[0] += ((__x_xpd__[4][2] * __y_xpd__[4][2]) + (__x_xpd__[4][3] * __y_xpd__[4][3]) + (__x_xpd__[4][0] * __y_xpd__[4][0]) + (__x_xpd__[4][1] * __y_xpd__[4][1]) + (__x_xpd__[4][4] * __y_xpd__[4][4]));

			}

		}
		if (((x.m_gu & 32) != 0)) {
			if (((y.m_gu & 32) != 0)) {
				__temp_var_1__.m_c[0] += (__x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		return __temp_var_1__;
	}
	mv lcontEM(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)6), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_4__[32] ;
		mv_zero(__tmp_coord_array_4__, 32);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}

		}
		if (((y.m_gu & 2) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[1] += (__y_xpd__[1][0] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[2] += (__y_xpd__[1][1] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[3] += (__y_xpd__[1][2] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[4] += (__y_xpd__[1][3] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[5] += (__y_xpd__[1][4] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[0] += ((__x_xpd__[1][3] * __y_xpd__[1][3]) + (__x_xpd__[1][2] * __y_xpd__[1][2]) + (__x_xpd__[1][1] * __y_xpd__[1][1]) + (__x_xpd__[1][4] * __y_xpd__[1][4]) + (__x_xpd__[1][0] * __y_xpd__[1][0]));

			}

		}
		if (((y.m_gu & 4) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[6] += (__y_xpd__[2][0] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[7] += (__y_xpd__[2][1] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[8] += (__y_xpd__[2][2] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[9] += (__y_xpd__[2][3] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[10] += (__y_xpd__[2][4] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[11] += (__y_xpd__[2][5] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[12] += (__y_xpd__[2][6] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[13] += (__y_xpd__[2][7] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[14] += (__y_xpd__[2][8] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[15] += (__y_xpd__[2][9] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[1] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][0]));
				__tmp_coord_array_4__[2] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][6]) + (__x_xpd__[1][3] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[2][3]) + (__x_xpd__[1][0] * __y_xpd__[2][0]));
				__tmp_coord_array_4__[3] += ((__x_xpd__[1][0] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[2][7]) + (__x_xpd__[1][1] * __y_xpd__[2][3]));
				__tmp_coord_array_4__[4] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[2][8]) + (__x_xpd__[1][0] * __y_xpd__[2][2]) + (__x_xpd__[1][2] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][5]));
				__tmp_coord_array_4__[5] += ((__x_xpd__[1][0] * __y_xpd__[2][9]) + (__x_xpd__[1][1] * __y_xpd__[2][6]) + (__x_xpd__[1][2] * __y_xpd__[2][7]) + (__x_xpd__[1][3] * __y_xpd__[2][8]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_4__[0] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][7]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][0]));

			}

		}
		if (((y.m_gu & 8) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[16] += (__y_xpd__[3][0] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[17] += (__y_xpd__[3][1] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[18] += (__y_xpd__[3][2] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[19] += (__y_xpd__[3][3] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[20] += (__y_xpd__[3][4] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[21] += (__y_xpd__[3][5] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[22] += (__y_xpd__[3][6] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[23] += (__y_xpd__[3][7] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[24] += (__y_xpd__[3][8] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[25] += (__y_xpd__[3][9] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[6] += ((__x_xpd__[1][3] * __y_xpd__[3][7]) + (__x_xpd__[1][2] * __y_xpd__[3][8]) + (__x_xpd__[1][4] * __y_xpd__[3][4]));
				__tmp_coord_array_4__[7] += ((__x_xpd__[1][3] * __y_xpd__[3][6]) + (__x_xpd__[1][4] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][8]));
				__tmp_coord_array_4__[8] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][6]) + (__x_xpd__[1][4] * __y_xpd__[3][3]));
				__tmp_coord_array_4__[9] += ((__x_xpd__[1][0] * __y_xpd__[3][8]) + (__x_xpd__[1][4] * __y_xpd__[3][2]) + (__x_xpd__[1][3] * __y_xpd__[3][9]));
				__tmp_coord_array_4__[10] += ((__x_xpd__[1][4] * __y_xpd__[3][0]) + (__x_xpd__[1][1] * __y_xpd__[3][9]) + (__x_xpd__[1][0] * __y_xpd__[3][6]));
				__tmp_coord_array_4__[11] += ((__x_xpd__[1][4] * __y_xpd__[3][1]) + (__x_xpd__[1][2] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[1][0] * __y_xpd__[3][7]));
				__tmp_coord_array_4__[12] += ((__x_xpd__[1][0] * __y_xpd__[3][4]) + (__x_xpd__[1][3] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][2]));
				__tmp_coord_array_4__[13] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][0]) + (__x_xpd__[1][0] * __y_xpd__[3][5]) + (__x_xpd__[1][1] * __y_xpd__[3][2]));
				__tmp_coord_array_4__[14] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[3][1]) + (__x_xpd__[1][0] * __y_xpd__[3][3]) + (__x_xpd__[1][2] * __y_xpd__[3][0]));
				__tmp_coord_array_4__[15] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[3][5]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_4__[1] += ((__x_xpd__[2][5] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][4]));
				__tmp_coord_array_4__[2] += ((__x_xpd__[2][8] * __y_xpd__[3][1]) + (__x_xpd__[2][2] * __y_xpd__[3][7]) + (__x_xpd__[2][9] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][9]) + (__x_xpd__[2][1] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][2]));
				__tmp_coord_array_4__[3] += ((__x_xpd__[2][2] * __y_xpd__[3][6]) + (__x_xpd__[2][9] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[3][0]) + (__x_xpd__[2][6] * __y_xpd__[3][2]));
				__tmp_coord_array_4__[4] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[3][6]) + (__x_xpd__[2][7] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][7]) + (__x_xpd__[2][9] * __y_xpd__[3][3]));
				__tmp_coord_array_4__[5] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[3][5]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_4__[0] += ((-1.0f * __x_xpd__[3][9] * __y_xpd__[3][9]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[3][7]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[3][0]) + (-1.0f * __x_xpd__[3][1] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[3][6]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[3][4]));

			}

		}
		if (((y.m_gu & 16) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[26] += (__y_xpd__[4][0] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[27] += (__y_xpd__[4][1] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[28] += (__y_xpd__[4][2] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[29] += (__y_xpd__[4][3] * __x_xpd__[0][0]);
				__tmp_coord_array_4__[30] += (__y_xpd__[4][4] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[16] += ((__x_xpd__[1][1] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[17] += ((__x_xpd__[1][2] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][2]));
				__tmp_coord_array_4__[18] += ((__x_xpd__[1][3] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][3]));
				__tmp_coord_array_4__[19] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[4][1]) + (__x_xpd__[1][1] * __y_xpd__[4][2]));
				__tmp_coord_array_4__[20] += ((__x_xpd__[1][2] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][2]));
				__tmp_coord_array_4__[21] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[4][3]) + (__x_xpd__[1][3] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[22] += ((-1.0f * __x_xpd__[1][1] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[23] += ((__x_xpd__[1][2] * __y_xpd__[4][4]) + (__x_xpd__[1][4] * __y_xpd__[4][2]));
				__tmp_coord_array_4__[24] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[25] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[4][0]) + (__x_xpd__[1][0] * __y_xpd__[4][4]));

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_4__[6] += ((__x_xpd__[2][8] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[7] += ((__x_xpd__[2][6] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[8] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[4][2]) + (__x_xpd__[2][7] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[9] += ((-1.0f * __x_xpd__[2][9] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[4][0]));
				__tmp_coord_array_4__[10] += ((-1.0f * __x_xpd__[2][6] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[11] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[4][2]));
				__tmp_coord_array_4__[12] += ((-1.0f * __x_xpd__[2][2] * __y_xpd__[4][2]) + (__x_xpd__[2][1] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][0]));
				__tmp_coord_array_4__[13] += ((-1.0f * __x_xpd__[2][5] * __y_xpd__[4][0]) + (__x_xpd__[2][2] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[4][3]));
				__tmp_coord_array_4__[14] += ((-1.0f * __x_xpd__[2][1] * __y_xpd__[4][1]) + (__x_xpd__[2][0] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][3] * __y_xpd__[4][0]));
				__tmp_coord_array_4__[15] += ((-1.0f * __x_xpd__[2][3] * __y_xpd__[4][3]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[2][4] * __y_xpd__[4][1]));

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_4__[1] += ((__x_xpd__[3][9] * __y_xpd__[4][4]) + (__x_xpd__[3][2] * __y_xpd__[4][3]) + (__x_xpd__[3][1] * __y_xpd__[4][2]) + (__x_xpd__[3][0] * __y_xpd__[4][1]));
				__tmp_coord_array_4__[2] += ((-1.0f * __x_xpd__[3][6] * __y_xpd__[4][4]) + (__x_xpd__[3][0] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[4][3]) + (__x_xpd__[3][3] * __y_xpd__[4][2]));
				__tmp_coord_array_4__[3] += ((-1.0f * __x_xpd__[3][3] * __y_xpd__[4][1]) + (__x_xpd__[3][1] * __y_xpd__[4][0]) + (__x_xpd__[3][7] * __y_xpd__[4][4]) + (__x_xpd__[3][4] * __y_xpd__[4][3]));
				__tmp_coord_array_4__[4] += ((__x_xpd__[3][5] * __y_xpd__[4][1]) + (__x_xpd__[3][2] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][4] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][4]));
				__tmp_coord_array_4__[5] += ((__x_xpd__[3][7] * __y_xpd__[4][2]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[3][6] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[3][8] * __y_xpd__[4][3]));

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_4__[0] += ((__x_xpd__[4][3] * __y_xpd__[4][3]) + (__x_xpd__[4][2] * __y_xpd__[4][2]) + (__x_xpd__[4][4] * __y_xpd__[4][4]) + (__x_xpd__[4][1] * __y_xpd__[4][1]) + (__x_xpd__[4][0] * __y_xpd__[4][0]));

			}

		}
		if (((y.m_gu & 32) != 0)) {
			if (((x.m_gu & 1) != 0)) {
				__tmp_coord_array_4__[31] += (__y_xpd__[5][0] * __x_xpd__[0][0]);

			}
			if (((x.m_gu & 2) != 0)) {
				__tmp_coord_array_4__[26] += (__x_xpd__[1][0] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[27] += (-1.0f * __x_xpd__[1][1] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[28] += (-1.0f * __x_xpd__[1][2] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[29] += (-1.0f * __x_xpd__[1][3] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[30] += (__x_xpd__[1][4] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 4) != 0)) {
				__tmp_coord_array_4__[16] += (-1.0f * __x_xpd__[2][0] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[17] += (-1.0f * __x_xpd__[2][1] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[18] += (-1.0f * __x_xpd__[2][2] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[19] += (-1.0f * __x_xpd__[2][3] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[20] += (-1.0f * __x_xpd__[2][4] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[21] += (-1.0f * __x_xpd__[2][5] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[22] += (-1.0f * __x_xpd__[2][6] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[23] += (__x_xpd__[2][7] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[24] += (-1.0f * __x_xpd__[2][8] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[25] += (__x_xpd__[2][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 8) != 0)) {
				__tmp_coord_array_4__[6] += (-1.0f * __x_xpd__[3][0] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[7] += (-1.0f * __x_xpd__[3][1] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[8] += (-1.0f * __x_xpd__[3][2] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[9] += (-1.0f * __x_xpd__[3][3] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[10] += (-1.0f * __x_xpd__[3][4] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[11] += (-1.0f * __x_xpd__[3][5] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[12] += (-1.0f * __x_xpd__[3][6] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[13] += (__x_xpd__[3][7] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[14] += (-1.0f * __x_xpd__[3][8] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[15] += (__x_xpd__[3][9] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 16) != 0)) {
				__tmp_coord_array_4__[1] += (__x_xpd__[4][0] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[2] += (-1.0f * __x_xpd__[4][1] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[3] += (-1.0f * __x_xpd__[4][2] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[4] += (-1.0f * __x_xpd__[4][3] * __y_xpd__[5][0]);
				__tmp_coord_array_4__[5] += (__x_xpd__[4][4] * __y_xpd__[5][0]);

			}
			if (((x.m_gu & 32) != 0)) {
				__tmp_coord_array_4__[0] += (__x_xpd__[5][0] * __y_xpd__[5][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_4__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv op(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)7), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_5__[32] ;
		mv_zero(__tmp_coord_array_5__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[0] += (__x_xpd__[0][0] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[1] += (__x_xpd__[0][0] * __y_xpd__[1][0]);
				__tmp_coord_array_5__[2] += (__x_xpd__[0][0] * __y_xpd__[1][1]);
				__tmp_coord_array_5__[3] += (__x_xpd__[0][0] * __y_xpd__[1][2]);
				__tmp_coord_array_5__[4] += (__x_xpd__[0][0] * __y_xpd__[1][3]);
				__tmp_coord_array_5__[5] += (__x_xpd__[0][0] * __y_xpd__[1][4]);

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_5__[6] += (__x_xpd__[0][0] * __y_xpd__[2][0]);
				__tmp_coord_array_5__[7] += (__x_xpd__[0][0] * __y_xpd__[2][1]);
				__tmp_coord_array_5__[8] += (__x_xpd__[0][0] * __y_xpd__[2][2]);
				__tmp_coord_array_5__[9] += (__x_xpd__[0][0] * __y_xpd__[2][3]);
				__tmp_coord_array_5__[10] += (__x_xpd__[0][0] * __y_xpd__[2][4]);
				__tmp_coord_array_5__[11] += (__x_xpd__[0][0] * __y_xpd__[2][5]);
				__tmp_coord_array_5__[12] += (__x_xpd__[0][0] * __y_xpd__[2][6]);
				__tmp_coord_array_5__[13] += (__x_xpd__[0][0] * __y_xpd__[2][7]);
				__tmp_coord_array_5__[14] += (__x_xpd__[0][0] * __y_xpd__[2][8]);
				__tmp_coord_array_5__[15] += (__x_xpd__[0][0] * __y_xpd__[2][9]);

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_5__[16] += (__x_xpd__[0][0] * __y_xpd__[3][0]);
				__tmp_coord_array_5__[17] += (__x_xpd__[0][0] * __y_xpd__[3][1]);
				__tmp_coord_array_5__[18] += (__x_xpd__[0][0] * __y_xpd__[3][2]);
				__tmp_coord_array_5__[19] += (__x_xpd__[0][0] * __y_xpd__[3][3]);
				__tmp_coord_array_5__[20] += (__x_xpd__[0][0] * __y_xpd__[3][4]);
				__tmp_coord_array_5__[21] += (__x_xpd__[0][0] * __y_xpd__[3][5]);
				__tmp_coord_array_5__[22] += (__x_xpd__[0][0] * __y_xpd__[3][6]);
				__tmp_coord_array_5__[23] += (__x_xpd__[0][0] * __y_xpd__[3][7]);
				__tmp_coord_array_5__[24] += (__x_xpd__[0][0] * __y_xpd__[3][8]);
				__tmp_coord_array_5__[25] += (__x_xpd__[0][0] * __y_xpd__[3][9]);

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_5__[26] += (__x_xpd__[0][0] * __y_xpd__[4][0]);
				__tmp_coord_array_5__[27] += (__x_xpd__[0][0] * __y_xpd__[4][1]);
				__tmp_coord_array_5__[28] += (__x_xpd__[0][0] * __y_xpd__[4][2]);
				__tmp_coord_array_5__[29] += (__x_xpd__[0][0] * __y_xpd__[4][3]);
				__tmp_coord_array_5__[30] += (__x_xpd__[0][0] * __y_xpd__[4][4]);

			}
			if (((y.m_gu & 32) != 0)) {
				__tmp_coord_array_5__[31] += (__x_xpd__[0][0] * __y_xpd__[5][0]);

			}

		}
		if (((x.m_gu & 2) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[1] += (__x_xpd__[1][0] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[2] += (__x_xpd__[1][1] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[3] += (__x_xpd__[1][2] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[4] += (__x_xpd__[1][3] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[5] += (__x_xpd__[1][4] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[6] += ((__x_xpd__[1][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][0]));
				__tmp_coord_array_5__[7] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[1][0]) + (__x_xpd__[1][0] * __y_xpd__[1][2]));
				__tmp_coord_array_5__[8] += ((__x_xpd__[1][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][0]));
				__tmp_coord_array_5__[9] += ((__x_xpd__[1][1] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[1][1]));
				__tmp_coord_array_5__[10] += ((__x_xpd__[1][2] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[1][2]));
				__tmp_coord_array_5__[11] += ((__x_xpd__[1][3] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[1][3]));
				__tmp_coord_array_5__[12] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][1]) + (__x_xpd__[1][1] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[13] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[1][2]) + (__x_xpd__[1][2] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[14] += ((__x_xpd__[1][3] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][3]));
				__tmp_coord_array_5__[15] += ((__x_xpd__[1][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[1][0]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_5__[16] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][7]) + (__x_xpd__[1][2] * __y_xpd__[2][8]) + (__x_xpd__[1][4] * __y_xpd__[2][4]));
				__tmp_coord_array_5__[17] += ((__x_xpd__[1][3] * __y_xpd__[2][6]) + (__x_xpd__[1][4] * __y_xpd__[2][5]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][8]));
				__tmp_coord_array_5__[18] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][6]) + (__x_xpd__[1][4] * __y_xpd__[2][3]) + (__x_xpd__[1][1] * __y_xpd__[2][7]));
				__tmp_coord_array_5__[19] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[2][9]) + (__x_xpd__[1][4] * __y_xpd__[2][2]) + (__x_xpd__[1][0] * __y_xpd__[2][8]));
				__tmp_coord_array_5__[20] += ((__x_xpd__[1][0] * __y_xpd__[2][6]) + (__x_xpd__[1][4] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][9]));
				__tmp_coord_array_5__[21] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][9]) + (__x_xpd__[1][0] * __y_xpd__[2][7]) + (__x_xpd__[1][4] * __y_xpd__[2][1]));
				__tmp_coord_array_5__[22] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[2][2]) + (__x_xpd__[1][3] * __y_xpd__[2][1]) + (__x_xpd__[1][0] * __y_xpd__[2][4]));
				__tmp_coord_array_5__[23] += ((-1.0f * __x_xpd__[1][0] * __y_xpd__[2][5]) + (__x_xpd__[1][3] * __y_xpd__[2][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][2]));
				__tmp_coord_array_5__[24] += ((__x_xpd__[1][0] * __y_xpd__[2][3]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[2][1]) + (__x_xpd__[1][2] * __y_xpd__[2][0]));
				__tmp_coord_array_5__[25] += ((__x_xpd__[1][3] * __y_xpd__[2][3]) + (__x_xpd__[1][1] * __y_xpd__[2][4]) + (__x_xpd__[1][2] * __y_xpd__[2][5]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_5__[26] += ((__x_xpd__[1][3] * __y_xpd__[3][2]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][9]) + (__x_xpd__[1][1] * __y_xpd__[3][0]) + (__x_xpd__[1][2] * __y_xpd__[3][1]));
				__tmp_coord_array_5__[27] += ((-1.0f * __x_xpd__[1][2] * __y_xpd__[3][3]) + (-1.0f * __x_xpd__[1][4] * __y_xpd__[3][6]) + (__x_xpd__[1][3] * __y_xpd__[3][5]) + (__x_xpd__[1][0] * __y_xpd__[3][0]));
				__tmp_coord_array_5__[28] += ((__x_xpd__[1][1] * __y_xpd__[3][3]) + (__x_xpd__[1][4] * __y_xpd__[3][7]) + (__x_xpd__[1][0] * __y_xpd__[3][1]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[3][4]));
				__tmp_coord_array_5__[29] += ((-1.0f * __x_xpd__[1][4] * __y_xpd__[3][8]) + (__x_xpd__[1][2] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][5]) + (__x_xpd__[1][0] * __y_xpd__[3][2]));
				__tmp_coord_array_5__[30] += ((-1.0f * __x_xpd__[1][3] * __y_xpd__[3][8]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[3][6]) + (__x_xpd__[1][0] * __y_xpd__[3][9]) + (__x_xpd__[1][2] * __y_xpd__[3][7]));

			}
			if (((y.m_gu & 16) != 0)) {
				__tmp_coord_array_5__[31] += ((__x_xpd__[1][0] * __y_xpd__[4][0]) + (-1.0f * __x_xpd__[1][1] * __y_xpd__[4][1]) + (-1.0f * __x_xpd__[1][2] * __y_xpd__[4][2]) + (__x_xpd__[1][4] * __y_xpd__[4][4]) + (-1.0f * __x_xpd__[1][3] * __y_xpd__[4][3]));

			}

		}
		if (((x.m_gu & 4) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[6] += (__x_xpd__[2][0] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[7] += (__x_xpd__[2][1] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[8] += (__x_xpd__[2][2] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[9] += (__x_xpd__[2][3] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[10] += (__x_xpd__[2][4] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[11] += (__x_xpd__[2][5] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[12] += (__x_xpd__[2][6] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[13] += (__x_xpd__[2][7] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[14] += (__x_xpd__[2][8] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[15] += (__x_xpd__[2][9] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[16] += ((-1.0f * __x_xpd__[2][7] * __y_xpd__[1][3]) + (__x_xpd__[2][4] * __y_xpd__[1][4]) + (__x_xpd__[2][8] * __y_xpd__[1][2]));
				__tmp_coord_array_5__[17] += ((-1.0f * __x_xpd__[2][8] * __y_xpd__[1][1]) + (__x_xpd__[2][5] * __y_xpd__[1][4]) + (__x_xpd__[2][6] * __y_xpd__[1][3]));
				__tmp_coord_array_5__[18] += ((__x_xpd__[2][7] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[19] += ((__x_xpd__[2][2] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][3]) + (__x_xpd__[2][8] * __y_xpd__[1][0]));
				__tmp_coord_array_5__[20] += ((__x_xpd__[2][0] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][1]) + (__x_xpd__[2][6] * __y_xpd__[1][0]));
				__tmp_coord_array_5__[21] += ((__x_xpd__[2][7] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[1][2]) + (__x_xpd__[2][1] * __y_xpd__[1][4]));
				__tmp_coord_array_5__[22] += ((__x_xpd__[2][4] * __y_xpd__[1][0]) + (__x_xpd__[2][1] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][2]));
				__tmp_coord_array_5__[23] += ((__x_xpd__[2][0] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[2][5] * __y_xpd__[1][0]));
				__tmp_coord_array_5__[24] += ((__x_xpd__[2][0] * __y_xpd__[1][2]) + (__x_xpd__[2][3] * __y_xpd__[1][0]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[1][1]));
				__tmp_coord_array_5__[25] += ((__x_xpd__[2][4] * __y_xpd__[1][1]) + (__x_xpd__[2][3] * __y_xpd__[1][3]) + (__x_xpd__[2][5] * __y_xpd__[1][2]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_5__[26] += ((__x_xpd__[2][5] * __y_xpd__[2][7]) + (__x_xpd__[2][3] * __y_xpd__[2][8]) + (__x_xpd__[2][8] * __y_xpd__[2][3]) + (__x_xpd__[2][4] * __y_xpd__[2][6]) + (__x_xpd__[2][6] * __y_xpd__[2][4]) + (__x_xpd__[2][7] * __y_xpd__[2][5]));
				__tmp_coord_array_5__[27] += ((__x_xpd__[2][9] * __y_xpd__[2][4]) + (__x_xpd__[2][1] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[2][2]) + (__x_xpd__[2][8] * __y_xpd__[2][1]) + (-1.0f * __x_xpd__[2][2] * __y_xpd__[2][7]) + (__x_xpd__[2][4] * __y_xpd__[2][9]));
				__tmp_coord_array_5__[28] += ((__x_xpd__[2][2] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][0] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[2][8] * __y_xpd__[2][0]) + (__x_xpd__[2][5] * __y_xpd__[2][9]) + (__x_xpd__[2][6] * __y_xpd__[2][2]) + (__x_xpd__[2][9] * __y_xpd__[2][5]));
				__tmp_coord_array_5__[29] += ((__x_xpd__[2][9] * __y_xpd__[2][3]) + (__x_xpd__[2][3] * __y_xpd__[2][9]) + (-1.0f * __x_xpd__[2][1] * __y_xpd__[2][6]) + (-1.0f * __x_xpd__[2][6] * __y_xpd__[2][1]) + (__x_xpd__[2][7] * __y_xpd__[2][0]) + (__x_xpd__[2][0] * __y_xpd__[2][7]));
				__tmp_coord_array_5__[30] += ((__x_xpd__[2][3] * __y_xpd__[2][2]) + (__x_xpd__[2][1] * __y_xpd__[2][5]) + (__x_xpd__[2][4] * __y_xpd__[2][0]) + (__x_xpd__[2][2] * __y_xpd__[2][3]) + (__x_xpd__[2][5] * __y_xpd__[2][1]) + (__x_xpd__[2][0] * __y_xpd__[2][4]));

			}
			if (((y.m_gu & 8) != 0)) {
				__tmp_coord_array_5__[31] += ((__x_xpd__[2][4] * __y_xpd__[3][4]) + (-1.0f * __x_xpd__[2][9] * __y_xpd__[3][9]) + (__x_xpd__[2][5] * __y_xpd__[3][5]) + (-1.0f * __x_xpd__[2][7] * __y_xpd__[3][7]) + (__x_xpd__[2][1] * __y_xpd__[3][1]) + (__x_xpd__[2][2] * __y_xpd__[3][2]) + (__x_xpd__[2][3] * __y_xpd__[3][3]) + (__x_xpd__[2][0] * __y_xpd__[3][0]) + (__x_xpd__[2][6] * __y_xpd__[3][6]) + (__x_xpd__[2][8] * __y_xpd__[3][8]));

			}

		}
		if (((x.m_gu & 8) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[16] += (__x_xpd__[3][0] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[17] += (__x_xpd__[3][1] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[18] += (__x_xpd__[3][2] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[19] += (__x_xpd__[3][3] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[20] += (__x_xpd__[3][4] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[21] += (__x_xpd__[3][5] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[22] += (__x_xpd__[3][6] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[23] += (__x_xpd__[3][7] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[24] += (__x_xpd__[3][8] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[25] += (__x_xpd__[3][9] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[26] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[1][2]) + (__x_xpd__[3][9] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][3]));
				__tmp_coord_array_5__[27] += ((__x_xpd__[3][6] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][5] * __y_xpd__[1][3]) + (__x_xpd__[3][3] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[3][0] * __y_xpd__[1][0]));
				__tmp_coord_array_5__[28] += ((-1.0f * __x_xpd__[3][1] * __y_xpd__[1][0]) + (__x_xpd__[3][4] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][3] * __y_xpd__[1][1]));
				__tmp_coord_array_5__[29] += ((-1.0f * __x_xpd__[3][4] * __y_xpd__[1][2]) + (__x_xpd__[3][5] * __y_xpd__[1][1]) + (__x_xpd__[3][8] * __y_xpd__[1][4]) + (-1.0f * __x_xpd__[3][2] * __y_xpd__[1][0]));
				__tmp_coord_array_5__[30] += ((-1.0f * __x_xpd__[3][7] * __y_xpd__[1][2]) + (__x_xpd__[3][6] * __y_xpd__[1][1]) + (__x_xpd__[3][8] * __y_xpd__[1][3]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[1][0]));

			}
			if (((y.m_gu & 4) != 0)) {
				__tmp_coord_array_5__[31] += ((__x_xpd__[3][3] * __y_xpd__[2][3]) + (__x_xpd__[3][5] * __y_xpd__[2][5]) + (__x_xpd__[3][1] * __y_xpd__[2][1]) + (__x_xpd__[3][8] * __y_xpd__[2][8]) + (-1.0f * __x_xpd__[3][7] * __y_xpd__[2][7]) + (__x_xpd__[3][0] * __y_xpd__[2][0]) + (__x_xpd__[3][4] * __y_xpd__[2][4]) + (-1.0f * __x_xpd__[3][9] * __y_xpd__[2][9]) + (__x_xpd__[3][6] * __y_xpd__[2][6]) + (__x_xpd__[3][2] * __y_xpd__[2][2]));

			}

		}
		if (((x.m_gu & 16) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[26] += (__x_xpd__[4][0] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[27] += (__x_xpd__[4][1] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[28] += (__x_xpd__[4][2] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[29] += (__x_xpd__[4][3] * __y_xpd__[0][0]);
				__tmp_coord_array_5__[30] += (__x_xpd__[4][4] * __y_xpd__[0][0]);

			}
			if (((y.m_gu & 2) != 0)) {
				__tmp_coord_array_5__[31] += ((-1.0f * __x_xpd__[4][1] * __y_xpd__[1][1]) + (-1.0f * __x_xpd__[4][2] * __y_xpd__[1][2]) + (-1.0f * __x_xpd__[4][3] * __y_xpd__[1][3]) + (__x_xpd__[4][4] * __y_xpd__[1][4]) + (__x_xpd__[4][0] * __y_xpd__[1][0]));

			}

		}
		if (((x.m_gu & 32) != 0)) {
			if (((y.m_gu & 1) != 0)) {
				__tmp_coord_array_5__[31] += (__x_xpd__[5][0] * __y_xpd__[0][0]);

			}

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_5__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv add(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)8), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_6__[32] ;
		mv_zero(__tmp_coord_array_6__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_6__[0] += __y_xpd__[0][0];

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_6__[1] += __y_xpd__[1][0];
			__tmp_coord_array_6__[2] += __y_xpd__[1][1];
			__tmp_coord_array_6__[3] += __y_xpd__[1][2];
			__tmp_coord_array_6__[4] += __y_xpd__[1][3];
			__tmp_coord_array_6__[5] += __y_xpd__[1][4];

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_6__[6] += __y_xpd__[2][0];
			__tmp_coord_array_6__[7] += __y_xpd__[2][1];
			__tmp_coord_array_6__[8] += __y_xpd__[2][2];
			__tmp_coord_array_6__[9] += __y_xpd__[2][3];
			__tmp_coord_array_6__[10] += __y_xpd__[2][4];
			__tmp_coord_array_6__[11] += __y_xpd__[2][5];
			__tmp_coord_array_6__[12] += __y_xpd__[2][6];
			__tmp_coord_array_6__[13] += __y_xpd__[2][7];
			__tmp_coord_array_6__[14] += __y_xpd__[2][8];
			__tmp_coord_array_6__[15] += __y_xpd__[2][9];

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_6__[16] += __y_xpd__[3][0];
			__tmp_coord_array_6__[17] += __y_xpd__[3][1];
			__tmp_coord_array_6__[18] += __y_xpd__[3][2];
			__tmp_coord_array_6__[19] += __y_xpd__[3][3];
			__tmp_coord_array_6__[20] += __y_xpd__[3][4];
			__tmp_coord_array_6__[21] += __y_xpd__[3][5];
			__tmp_coord_array_6__[22] += __y_xpd__[3][6];
			__tmp_coord_array_6__[23] += __y_xpd__[3][7];
			__tmp_coord_array_6__[24] += __y_xpd__[3][8];
			__tmp_coord_array_6__[25] += __y_xpd__[3][9];

		}
		if (((y.m_gu & 16) != 0)) {
			__tmp_coord_array_6__[26] += __y_xpd__[4][0];
			__tmp_coord_array_6__[27] += __y_xpd__[4][1];
			__tmp_coord_array_6__[28] += __y_xpd__[4][2];
			__tmp_coord_array_6__[29] += __y_xpd__[4][3];
			__tmp_coord_array_6__[30] += __y_xpd__[4][4];

		}
		if (((y.m_gu & 32) != 0)) {
			__tmp_coord_array_6__[31] += __y_xpd__[5][0];

		}
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_6__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_6__[1] += __x_xpd__[1][0];
			__tmp_coord_array_6__[2] += __x_xpd__[1][1];
			__tmp_coord_array_6__[3] += __x_xpd__[1][2];
			__tmp_coord_array_6__[4] += __x_xpd__[1][3];
			__tmp_coord_array_6__[5] += __x_xpd__[1][4];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_6__[6] += __x_xpd__[2][0];
			__tmp_coord_array_6__[7] += __x_xpd__[2][1];
			__tmp_coord_array_6__[8] += __x_xpd__[2][2];
			__tmp_coord_array_6__[9] += __x_xpd__[2][3];
			__tmp_coord_array_6__[10] += __x_xpd__[2][4];
			__tmp_coord_array_6__[11] += __x_xpd__[2][5];
			__tmp_coord_array_6__[12] += __x_xpd__[2][6];
			__tmp_coord_array_6__[13] += __x_xpd__[2][7];
			__tmp_coord_array_6__[14] += __x_xpd__[2][8];
			__tmp_coord_array_6__[15] += __x_xpd__[2][9];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_6__[16] += __x_xpd__[3][0];
			__tmp_coord_array_6__[17] += __x_xpd__[3][1];
			__tmp_coord_array_6__[18] += __x_xpd__[3][2];
			__tmp_coord_array_6__[19] += __x_xpd__[3][3];
			__tmp_coord_array_6__[20] += __x_xpd__[3][4];
			__tmp_coord_array_6__[21] += __x_xpd__[3][5];
			__tmp_coord_array_6__[22] += __x_xpd__[3][6];
			__tmp_coord_array_6__[23] += __x_xpd__[3][7];
			__tmp_coord_array_6__[24] += __x_xpd__[3][8];
			__tmp_coord_array_6__[25] += __x_xpd__[3][9];

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_6__[26] += __x_xpd__[4][0];
			__tmp_coord_array_6__[27] += __x_xpd__[4][1];
			__tmp_coord_array_6__[28] += __x_xpd__[4][2];
			__tmp_coord_array_6__[29] += __x_xpd__[4][3];
			__tmp_coord_array_6__[30] += __x_xpd__[4][4];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_6__[31] += __x_xpd__[5][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_6__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv subtract(const mv& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)9), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_7__[32] ;
		mv_zero(__tmp_coord_array_7__, 32);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_7__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_7__[1] += __x_xpd__[1][0];
			__tmp_coord_array_7__[2] += __x_xpd__[1][1];
			__tmp_coord_array_7__[3] += __x_xpd__[1][2];
			__tmp_coord_array_7__[4] += __x_xpd__[1][3];
			__tmp_coord_array_7__[5] += __x_xpd__[1][4];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_7__[6] += __x_xpd__[2][0];
			__tmp_coord_array_7__[7] += __x_xpd__[2][1];
			__tmp_coord_array_7__[8] += __x_xpd__[2][2];
			__tmp_coord_array_7__[9] += __x_xpd__[2][3];
			__tmp_coord_array_7__[10] += __x_xpd__[2][4];
			__tmp_coord_array_7__[11] += __x_xpd__[2][5];
			__tmp_coord_array_7__[12] += __x_xpd__[2][6];
			__tmp_coord_array_7__[13] += __x_xpd__[2][7];
			__tmp_coord_array_7__[14] += __x_xpd__[2][8];
			__tmp_coord_array_7__[15] += __x_xpd__[2][9];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_7__[16] += __x_xpd__[3][0];
			__tmp_coord_array_7__[17] += __x_xpd__[3][1];
			__tmp_coord_array_7__[18] += __x_xpd__[3][2];
			__tmp_coord_array_7__[19] += __x_xpd__[3][3];
			__tmp_coord_array_7__[20] += __x_xpd__[3][4];
			__tmp_coord_array_7__[21] += __x_xpd__[3][5];
			__tmp_coord_array_7__[22] += __x_xpd__[3][6];
			__tmp_coord_array_7__[23] += __x_xpd__[3][7];
			__tmp_coord_array_7__[24] += __x_xpd__[3][8];
			__tmp_coord_array_7__[25] += __x_xpd__[3][9];

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_7__[26] += __x_xpd__[4][0];
			__tmp_coord_array_7__[27] += __x_xpd__[4][1];
			__tmp_coord_array_7__[28] += __x_xpd__[4][2];
			__tmp_coord_array_7__[29] += __x_xpd__[4][3];
			__tmp_coord_array_7__[30] += __x_xpd__[4][4];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_7__[31] += __x_xpd__[5][0];

		}
		if (((y.m_gu & 1) != 0)) {
			__tmp_coord_array_7__[0] += (-1.0f * __y_xpd__[0][0]);

		}
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_7__[1] += (-1.0f * __y_xpd__[1][0]);
			__tmp_coord_array_7__[2] += (-1.0f * __y_xpd__[1][1]);
			__tmp_coord_array_7__[3] += (-1.0f * __y_xpd__[1][2]);
			__tmp_coord_array_7__[4] += (-1.0f * __y_xpd__[1][3]);
			__tmp_coord_array_7__[5] += (-1.0f * __y_xpd__[1][4]);

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_7__[6] += (-1.0f * __y_xpd__[2][0]);
			__tmp_coord_array_7__[7] += (-1.0f * __y_xpd__[2][1]);
			__tmp_coord_array_7__[8] += (-1.0f * __y_xpd__[2][2]);
			__tmp_coord_array_7__[9] += (-1.0f * __y_xpd__[2][3]);
			__tmp_coord_array_7__[10] += (-1.0f * __y_xpd__[2][4]);
			__tmp_coord_array_7__[11] += (-1.0f * __y_xpd__[2][5]);
			__tmp_coord_array_7__[12] += (-1.0f * __y_xpd__[2][6]);
			__tmp_coord_array_7__[13] += (-1.0f * __y_xpd__[2][7]);
			__tmp_coord_array_7__[14] += (-1.0f * __y_xpd__[2][8]);
			__tmp_coord_array_7__[15] += (-1.0f * __y_xpd__[2][9]);

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_7__[16] += (-1.0f * __y_xpd__[3][0]);
			__tmp_coord_array_7__[17] += (-1.0f * __y_xpd__[3][1]);
			__tmp_coord_array_7__[18] += (-1.0f * __y_xpd__[3][2]);
			__tmp_coord_array_7__[19] += (-1.0f * __y_xpd__[3][3]);
			__tmp_coord_array_7__[20] += (-1.0f * __y_xpd__[3][4]);
			__tmp_coord_array_7__[21] += (-1.0f * __y_xpd__[3][5]);
			__tmp_coord_array_7__[22] += (-1.0f * __y_xpd__[3][6]);
			__tmp_coord_array_7__[23] += (-1.0f * __y_xpd__[3][7]);
			__tmp_coord_array_7__[24] += (-1.0f * __y_xpd__[3][8]);
			__tmp_coord_array_7__[25] += (-1.0f * __y_xpd__[3][9]);

		}
		if (((y.m_gu & 16) != 0)) {
			__tmp_coord_array_7__[26] += (-1.0f * __y_xpd__[4][0]);
			__tmp_coord_array_7__[27] += (-1.0f * __y_xpd__[4][1]);
			__tmp_coord_array_7__[28] += (-1.0f * __y_xpd__[4][2]);
			__tmp_coord_array_7__[29] += (-1.0f * __y_xpd__[4][3]);
			__tmp_coord_array_7__[30] += (-1.0f * __y_xpd__[4][4]);

		}
		if (((y.m_gu & 32) != 0)) {
			__tmp_coord_array_7__[31] += (-1.0f * __y_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_7__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	scalar norm_e2(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)10), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar __temp_var_1__;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][4] * __x_xpd__[1][4]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][6] * __x_xpd__[2][6]) + (__x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][8] * __x_xpd__[2][8]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][7] * __x_xpd__[2][7]));

		}
		if (((x.m_gu & 8) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[3][3] * __x_xpd__[3][3]) + (__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][8] * __x_xpd__[3][8]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (__x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][6] * __x_xpd__[3][6]) + (__x_xpd__[3][7] * __x_xpd__[3][7]) + (__x_xpd__[3][5] * __x_xpd__[3][5]));

		}
		if (((x.m_gu & 16) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[4][3] * __x_xpd__[4][3]) + (__x_xpd__[4][0] * __x_xpd__[4][0]) + (__x_xpd__[4][1] * __x_xpd__[4][1]) + (__x_xpd__[4][4] * __x_xpd__[4][4]) + (__x_xpd__[4][2] * __x_xpd__[4][2]));

		}
		if (((x.m_gu & 32) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		return __temp_var_1__;
	}
	scalar norm_e(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)11), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar e2;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][4] * __x_xpd__[1][4]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += ((__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][6] * __x_xpd__[2][6]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][7] * __x_xpd__[2][7]) + (__x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][8] * __x_xpd__[2][8]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][3] * __x_xpd__[2][3]));

		}
		if (((x.m_gu & 8) != 0)) {
			e2.m_c[0] += ((__x_xpd__[3][6] * __x_xpd__[3][6]) + (__x_xpd__[3][7] * __x_xpd__[3][7]) + (__x_xpd__[3][3] * __x_xpd__[3][3]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][5] * __x_xpd__[3][5]) + (__x_xpd__[3][0] * __x_xpd__[3][0]) + (__x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][8] * __x_xpd__[3][8]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][9] * __x_xpd__[3][9]));

		}
		if (((x.m_gu & 16) != 0)) {
			e2.m_c[0] += ((__x_xpd__[4][0] * __x_xpd__[4][0]) + (__x_xpd__[4][3] * __x_xpd__[4][3]) + (__x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][1] * __x_xpd__[4][1]) + (__x_xpd__[4][4] * __x_xpd__[4][4]));

		}
		if (((x.m_gu & 32) != 0)) {
			e2.m_c[0] += (__x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		return scalar(scalar_scalar, sqrt(e2.m_c[0]));
	}
	mv unit_e(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)12), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar e2;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			e2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			e2.m_c[0] += ((__x_xpd__[1][4] * __x_xpd__[1][4]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][0] * __x_xpd__[1][0]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][1] * __x_xpd__[1][1]));

		}
		if (((x.m_gu & 4) != 0)) {
			e2.m_c[0] += ((__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][6] * __x_xpd__[2][6]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][8] * __x_xpd__[2][8]) + (__x_xpd__[2][7] * __x_xpd__[2][7]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][2] * __x_xpd__[2][2]));

		}
		if (((x.m_gu & 8) != 0)) {
			e2.m_c[0] += ((__x_xpd__[3][5] * __x_xpd__[3][5]) + (__x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][7] * __x_xpd__[3][7]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][8] * __x_xpd__[3][8]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (__x_xpd__[3][6] * __x_xpd__[3][6]) + (__x_xpd__[3][3] * __x_xpd__[3][3]) + (__x_xpd__[3][0] * __x_xpd__[3][0]));

		}
		if (((x.m_gu & 16) != 0)) {
			e2.m_c[0] += ((__x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][0] * __x_xpd__[4][0]) + (__x_xpd__[4][4] * __x_xpd__[4][4]) + (__x_xpd__[4][1] * __x_xpd__[4][1]) + (__x_xpd__[4][3] * __x_xpd__[4][3]));

		}
		if (((x.m_gu & 32) != 0)) {
			e2.m_c[0] += (__x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		scalar ie;
		ie.m_c[0] = ((char)1 / sqrt(e2.m_c[0]));
		mv __temp_var_1__;
		float __tmp_coord_array_8__[32] ;
		mv_zero(__tmp_coord_array_8__, 32);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_8__[0] += (__x_xpd__[0][0] * ie.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_8__[1] += (__x_xpd__[1][0] * ie.m_c[0]);
			__tmp_coord_array_8__[2] += (__x_xpd__[1][1] * ie.m_c[0]);
			__tmp_coord_array_8__[3] += (__x_xpd__[1][2] * ie.m_c[0]);
			__tmp_coord_array_8__[4] += (__x_xpd__[1][3] * ie.m_c[0]);
			__tmp_coord_array_8__[5] += (__x_xpd__[1][4] * ie.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_8__[6] += (__x_xpd__[2][0] * ie.m_c[0]);
			__tmp_coord_array_8__[7] += (__x_xpd__[2][1] * ie.m_c[0]);
			__tmp_coord_array_8__[8] += (__x_xpd__[2][2] * ie.m_c[0]);
			__tmp_coord_array_8__[9] += (__x_xpd__[2][3] * ie.m_c[0]);
			__tmp_coord_array_8__[10] += (__x_xpd__[2][4] * ie.m_c[0]);
			__tmp_coord_array_8__[11] += (__x_xpd__[2][5] * ie.m_c[0]);
			__tmp_coord_array_8__[12] += (__x_xpd__[2][6] * ie.m_c[0]);
			__tmp_coord_array_8__[13] += (__x_xpd__[2][7] * ie.m_c[0]);
			__tmp_coord_array_8__[14] += (__x_xpd__[2][8] * ie.m_c[0]);
			__tmp_coord_array_8__[15] += (__x_xpd__[2][9] * ie.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_8__[16] += (__x_xpd__[3][0] * ie.m_c[0]);
			__tmp_coord_array_8__[17] += (__x_xpd__[3][1] * ie.m_c[0]);
			__tmp_coord_array_8__[18] += (__x_xpd__[3][2] * ie.m_c[0]);
			__tmp_coord_array_8__[19] += (__x_xpd__[3][3] * ie.m_c[0]);
			__tmp_coord_array_8__[20] += (__x_xpd__[3][4] * ie.m_c[0]);
			__tmp_coord_array_8__[21] += (__x_xpd__[3][5] * ie.m_c[0]);
			__tmp_coord_array_8__[22] += (__x_xpd__[3][6] * ie.m_c[0]);
			__tmp_coord_array_8__[23] += (__x_xpd__[3][7] * ie.m_c[0]);
			__tmp_coord_array_8__[24] += (__x_xpd__[3][8] * ie.m_c[0]);
			__tmp_coord_array_8__[25] += (__x_xpd__[3][9] * ie.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_8__[26] += (__x_xpd__[4][0] * ie.m_c[0]);
			__tmp_coord_array_8__[27] += (__x_xpd__[4][1] * ie.m_c[0]);
			__tmp_coord_array_8__[28] += (__x_xpd__[4][2] * ie.m_c[0]);
			__tmp_coord_array_8__[29] += (__x_xpd__[4][3] * ie.m_c[0]);
			__tmp_coord_array_8__[30] += (__x_xpd__[4][4] * ie.m_c[0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_8__[31] += (__x_xpd__[5][0] * ie.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_8__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	scalar norm_r2(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)13), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar __temp_var_1__;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__temp_var_1__.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__temp_var_1__.m_c[0] += ((-1.0f * __x_xpd__[1][0] * __x_xpd__[1][4]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][3] * __x_xpd__[1][3]) + (-1.0f * __x_xpd__[1][4] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[2][0] * __x_xpd__[2][6]) + (-1.0f * __x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][8] * __x_xpd__[2][2]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][1] * __x_xpd__[2][7]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][6] * __x_xpd__[2][0]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][2] * __x_xpd__[2][8]) + (__x_xpd__[2][7] * __x_xpd__[2][1]));

		}
		if (((x.m_gu & 8) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[3][7] * __x_xpd__[3][1]) + (-1.0f * __x_xpd__[3][6] * __x_xpd__[3][0]) + (__x_xpd__[3][1] * __x_xpd__[3][7]) + (-1.0f * __x_xpd__[3][3] * __x_xpd__[3][3]) + (-1.0f * __x_xpd__[3][5] * __x_xpd__[3][5]) + (-1.0f * __x_xpd__[3][2] * __x_xpd__[3][8]) + (-1.0f * __x_xpd__[3][8] * __x_xpd__[3][2]) + (-1.0f * __x_xpd__[3][0] * __x_xpd__[3][6]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (-1.0f * __x_xpd__[3][4] * __x_xpd__[3][4]));

		}
		if (((x.m_gu & 16) != 0)) {
			__temp_var_1__.m_c[0] += ((__x_xpd__[4][4] * __x_xpd__[4][0]) + (-1.0f * __x_xpd__[4][3] * __x_xpd__[4][3]) + (-1.0f * __x_xpd__[4][1] * __x_xpd__[4][1]) + (__x_xpd__[4][0] * __x_xpd__[4][4]) + (-1.0f * __x_xpd__[4][2] * __x_xpd__[4][2]));

		}
		if (((x.m_gu & 32) != 0)) {
			__temp_var_1__.m_c[0] += (-1.0f * __x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		return __temp_var_1__;
	}
	scalar norm_r(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)14), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar r2;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][2] * __x_xpd__[1][2]) + (-1.0f * __x_xpd__[1][4] * __x_xpd__[1][0]) + (-1.0f * __x_xpd__[1][0] * __x_xpd__[1][4]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][3] * __x_xpd__[1][3]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += ((__x_xpd__[2][6] * __x_xpd__[2][0]) + (__x_xpd__[2][1] * __x_xpd__[2][7]) + (__x_xpd__[2][2] * __x_xpd__[2][8]) + (-1.0f * __x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][0] * __x_xpd__[2][6]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][8] * __x_xpd__[2][2]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][7] * __x_xpd__[2][1]) + (__x_xpd__[2][5] * __x_xpd__[2][5]));

		}
		if (((x.m_gu & 8) != 0)) {
			r2.m_c[0] += ((-1.0f * __x_xpd__[3][6] * __x_xpd__[3][0]) + (-1.0f * __x_xpd__[3][3] * __x_xpd__[3][3]) + (-1.0f * __x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (__x_xpd__[3][1] * __x_xpd__[3][7]) + (-1.0f * __x_xpd__[3][2] * __x_xpd__[3][8]) + (-1.0f * __x_xpd__[3][0] * __x_xpd__[3][6]) + (-1.0f * __x_xpd__[3][5] * __x_xpd__[3][5]) + (-1.0f * __x_xpd__[3][8] * __x_xpd__[3][2]) + (__x_xpd__[3][7] * __x_xpd__[3][1]));

		}
		if (((x.m_gu & 16) != 0)) {
			r2.m_c[0] += ((-1.0f * __x_xpd__[4][1] * __x_xpd__[4][1]) + (-1.0f * __x_xpd__[4][3] * __x_xpd__[4][3]) + (-1.0f * __x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][4] * __x_xpd__[4][0]) + (__x_xpd__[4][0] * __x_xpd__[4][4]));

		}
		if (((x.m_gu & 32) != 0)) {
			r2.m_c[0] += (-1.0f * __x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		return scalar(scalar_scalar, ((((r2.m_c[0] < (char)0)) ? (char)-1 : ((((r2.m_c[0] > (char)0)) ? (char)1 : (char)0))) * sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0])))));
	}
	mv unit_r(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)15), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar r2;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			r2.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			r2.m_c[0] += ((__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (-1.0f * __x_xpd__[1][4] * __x_xpd__[1][0]) + (-1.0f * __x_xpd__[1][0] * __x_xpd__[1][4]));

		}
		if (((x.m_gu & 4) != 0)) {
			r2.m_c[0] += ((__x_xpd__[2][8] * __x_xpd__[2][2]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][1] * __x_xpd__[2][7]) + (__x_xpd__[2][0] * __x_xpd__[2][6]) + (__x_xpd__[2][7] * __x_xpd__[2][1]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (-1.0f * __x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][2] * __x_xpd__[2][8]) + (__x_xpd__[2][6] * __x_xpd__[2][0]));

		}
		if (((x.m_gu & 8) != 0)) {
			r2.m_c[0] += ((__x_xpd__[3][7] * __x_xpd__[3][1]) + (-1.0f * __x_xpd__[3][8] * __x_xpd__[3][2]) + (__x_xpd__[3][1] * __x_xpd__[3][7]) + (-1.0f * __x_xpd__[3][5] * __x_xpd__[3][5]) + (-1.0f * __x_xpd__[3][6] * __x_xpd__[3][0]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (-1.0f * __x_xpd__[3][3] * __x_xpd__[3][3]) + (-1.0f * __x_xpd__[3][2] * __x_xpd__[3][8]) + (-1.0f * __x_xpd__[3][4] * __x_xpd__[3][4]) + (-1.0f * __x_xpd__[3][0] * __x_xpd__[3][6]));

		}
		if (((x.m_gu & 16) != 0)) {
			r2.m_c[0] += ((__x_xpd__[4][4] * __x_xpd__[4][0]) + (-1.0f * __x_xpd__[4][3] * __x_xpd__[4][3]) + (-1.0f * __x_xpd__[4][2] * __x_xpd__[4][2]) + (-1.0f * __x_xpd__[4][1] * __x_xpd__[4][1]) + (__x_xpd__[4][0] * __x_xpd__[4][4]));

		}
		if (((x.m_gu & 32) != 0)) {
			r2.m_c[0] += (-1.0f * __x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		scalar ir;
		ir.m_c[0] = ((char)1 / sqrt((((r2.m_c[0] < (char)0)) ? ((-r2.m_c[0])) : (r2.m_c[0]))));
		mv __temp_var_1__;
		float __tmp_coord_array_9__[32] ;
		mv_zero(__tmp_coord_array_9__, 32);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_9__[0] += (__x_xpd__[0][0] * ir.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_9__[1] += (__x_xpd__[1][0] * ir.m_c[0]);
			__tmp_coord_array_9__[2] += (__x_xpd__[1][1] * ir.m_c[0]);
			__tmp_coord_array_9__[3] += (__x_xpd__[1][2] * ir.m_c[0]);
			__tmp_coord_array_9__[4] += (__x_xpd__[1][3] * ir.m_c[0]);
			__tmp_coord_array_9__[5] += (__x_xpd__[1][4] * ir.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_9__[6] += (__x_xpd__[2][0] * ir.m_c[0]);
			__tmp_coord_array_9__[7] += (__x_xpd__[2][1] * ir.m_c[0]);
			__tmp_coord_array_9__[8] += (__x_xpd__[2][2] * ir.m_c[0]);
			__tmp_coord_array_9__[9] += (__x_xpd__[2][3] * ir.m_c[0]);
			__tmp_coord_array_9__[10] += (__x_xpd__[2][4] * ir.m_c[0]);
			__tmp_coord_array_9__[11] += (__x_xpd__[2][5] * ir.m_c[0]);
			__tmp_coord_array_9__[12] += (__x_xpd__[2][6] * ir.m_c[0]);
			__tmp_coord_array_9__[13] += (__x_xpd__[2][7] * ir.m_c[0]);
			__tmp_coord_array_9__[14] += (__x_xpd__[2][8] * ir.m_c[0]);
			__tmp_coord_array_9__[15] += (__x_xpd__[2][9] * ir.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_9__[16] += (__x_xpd__[3][0] * ir.m_c[0]);
			__tmp_coord_array_9__[17] += (__x_xpd__[3][1] * ir.m_c[0]);
			__tmp_coord_array_9__[18] += (__x_xpd__[3][2] * ir.m_c[0]);
			__tmp_coord_array_9__[19] += (__x_xpd__[3][3] * ir.m_c[0]);
			__tmp_coord_array_9__[20] += (__x_xpd__[3][4] * ir.m_c[0]);
			__tmp_coord_array_9__[21] += (__x_xpd__[3][5] * ir.m_c[0]);
			__tmp_coord_array_9__[22] += (__x_xpd__[3][6] * ir.m_c[0]);
			__tmp_coord_array_9__[23] += (__x_xpd__[3][7] * ir.m_c[0]);
			__tmp_coord_array_9__[24] += (__x_xpd__[3][8] * ir.m_c[0]);
			__tmp_coord_array_9__[25] += (__x_xpd__[3][9] * ir.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_9__[26] += (__x_xpd__[4][0] * ir.m_c[0]);
			__tmp_coord_array_9__[27] += (__x_xpd__[4][1] * ir.m_c[0]);
			__tmp_coord_array_9__[28] += (__x_xpd__[4][2] * ir.m_c[0]);
			__tmp_coord_array_9__[29] += (__x_xpd__[4][3] * ir.m_c[0]);
			__tmp_coord_array_9__[30] += (__x_xpd__[4][4] * ir.m_c[0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_9__[31] += (__x_xpd__[5][0] * ir.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_9__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv reverse(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)16), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_10__[32] ;
		mv_zero(__tmp_coord_array_10__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_10__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_10__[1] += __x_xpd__[1][0];
			__tmp_coord_array_10__[2] += __x_xpd__[1][1];
			__tmp_coord_array_10__[3] += __x_xpd__[1][2];
			__tmp_coord_array_10__[4] += __x_xpd__[1][3];
			__tmp_coord_array_10__[5] += __x_xpd__[1][4];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_10__[6] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_10__[7] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_10__[8] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_10__[9] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_10__[10] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_10__[11] += (-1.0f * __x_xpd__[2][5]);
			__tmp_coord_array_10__[12] += (-1.0f * __x_xpd__[2][6]);
			__tmp_coord_array_10__[13] += (-1.0f * __x_xpd__[2][7]);
			__tmp_coord_array_10__[14] += (-1.0f * __x_xpd__[2][8]);
			__tmp_coord_array_10__[15] += (-1.0f * __x_xpd__[2][9]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_10__[16] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_10__[17] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_10__[18] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_10__[19] += (-1.0f * __x_xpd__[3][3]);
			__tmp_coord_array_10__[20] += (-1.0f * __x_xpd__[3][4]);
			__tmp_coord_array_10__[21] += (-1.0f * __x_xpd__[3][5]);
			__tmp_coord_array_10__[22] += (-1.0f * __x_xpd__[3][6]);
			__tmp_coord_array_10__[23] += (-1.0f * __x_xpd__[3][7]);
			__tmp_coord_array_10__[24] += (-1.0f * __x_xpd__[3][8]);
			__tmp_coord_array_10__[25] += (-1.0f * __x_xpd__[3][9]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_10__[26] += __x_xpd__[4][0];
			__tmp_coord_array_10__[27] += __x_xpd__[4][1];
			__tmp_coord_array_10__[28] += __x_xpd__[4][2];
			__tmp_coord_array_10__[29] += __x_xpd__[4][3];
			__tmp_coord_array_10__[30] += __x_xpd__[4][4];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_10__[31] += __x_xpd__[5][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_10__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv negate(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)17), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_11__[32] ;
		mv_zero(__tmp_coord_array_11__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_11__[0] += (-1.0f * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_11__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_11__[2] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_11__[3] += (-1.0f * __x_xpd__[1][2]);
			__tmp_coord_array_11__[4] += (-1.0f * __x_xpd__[1][3]);
			__tmp_coord_array_11__[5] += (-1.0f * __x_xpd__[1][4]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_11__[6] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_11__[7] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_11__[8] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_11__[9] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_11__[10] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_11__[11] += (-1.0f * __x_xpd__[2][5]);
			__tmp_coord_array_11__[12] += (-1.0f * __x_xpd__[2][6]);
			__tmp_coord_array_11__[13] += (-1.0f * __x_xpd__[2][7]);
			__tmp_coord_array_11__[14] += (-1.0f * __x_xpd__[2][8]);
			__tmp_coord_array_11__[15] += (-1.0f * __x_xpd__[2][9]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_11__[16] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_11__[17] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_11__[18] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_11__[19] += (-1.0f * __x_xpd__[3][3]);
			__tmp_coord_array_11__[20] += (-1.0f * __x_xpd__[3][4]);
			__tmp_coord_array_11__[21] += (-1.0f * __x_xpd__[3][5]);
			__tmp_coord_array_11__[22] += (-1.0f * __x_xpd__[3][6]);
			__tmp_coord_array_11__[23] += (-1.0f * __x_xpd__[3][7]);
			__tmp_coord_array_11__[24] += (-1.0f * __x_xpd__[3][8]);
			__tmp_coord_array_11__[25] += (-1.0f * __x_xpd__[3][9]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_11__[26] += (-1.0f * __x_xpd__[4][0]);
			__tmp_coord_array_11__[27] += (-1.0f * __x_xpd__[4][1]);
			__tmp_coord_array_11__[28] += (-1.0f * __x_xpd__[4][2]);
			__tmp_coord_array_11__[29] += (-1.0f * __x_xpd__[4][3]);
			__tmp_coord_array_11__[30] += (-1.0f * __x_xpd__[4][4]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_11__[31] += (-1.0f * __x_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_11__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv dual(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)18), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_12__[32] ;
		mv_zero(__tmp_coord_array_12__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_12__[31] += (-1.0f * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_12__[26] += __x_xpd__[1][4];
			__tmp_coord_array_12__[27] += __x_xpd__[1][1];
			__tmp_coord_array_12__[28] += __x_xpd__[1][2];
			__tmp_coord_array_12__[29] += __x_xpd__[1][3];
			__tmp_coord_array_12__[30] += __x_xpd__[1][0];

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_12__[16] += __x_xpd__[2][6];
			__tmp_coord_array_12__[17] += __x_xpd__[2][7];
			__tmp_coord_array_12__[18] += __x_xpd__[2][8];
			__tmp_coord_array_12__[19] += __x_xpd__[2][3];
			__tmp_coord_array_12__[20] += __x_xpd__[2][4];
			__tmp_coord_array_12__[21] += __x_xpd__[2][5];
			__tmp_coord_array_12__[22] += __x_xpd__[2][0];
			__tmp_coord_array_12__[23] += (-1.0f * __x_xpd__[2][1]);
			__tmp_coord_array_12__[24] += __x_xpd__[2][2];
			__tmp_coord_array_12__[25] += __x_xpd__[2][9];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_12__[6] += (-1.0f * __x_xpd__[3][6]);
			__tmp_coord_array_12__[7] += __x_xpd__[3][7];
			__tmp_coord_array_12__[8] += (-1.0f * __x_xpd__[3][8]);
			__tmp_coord_array_12__[9] += (-1.0f * __x_xpd__[3][3]);
			__tmp_coord_array_12__[10] += (-1.0f * __x_xpd__[3][4]);
			__tmp_coord_array_12__[11] += (-1.0f * __x_xpd__[3][5]);
			__tmp_coord_array_12__[12] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_12__[13] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_12__[14] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_12__[15] += (-1.0f * __x_xpd__[3][9]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_12__[1] += (-1.0f * __x_xpd__[4][4]);
			__tmp_coord_array_12__[2] += (-1.0f * __x_xpd__[4][1]);
			__tmp_coord_array_12__[3] += (-1.0f * __x_xpd__[4][2]);
			__tmp_coord_array_12__[4] += (-1.0f * __x_xpd__[4][3]);
			__tmp_coord_array_12__[5] += (-1.0f * __x_xpd__[4][0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_12__[0] += __x_xpd__[5][0];

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_12__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv undual(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)19), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_13__[32] ;
		mv_zero(__tmp_coord_array_13__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_13__[31] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_13__[26] += (-1.0f * __x_xpd__[1][4]);
			__tmp_coord_array_13__[27] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_13__[28] += (-1.0f * __x_xpd__[1][2]);
			__tmp_coord_array_13__[29] += (-1.0f * __x_xpd__[1][3]);
			__tmp_coord_array_13__[30] += (-1.0f * __x_xpd__[1][0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_13__[16] += (-1.0f * __x_xpd__[2][6]);
			__tmp_coord_array_13__[17] += (-1.0f * __x_xpd__[2][7]);
			__tmp_coord_array_13__[18] += (-1.0f * __x_xpd__[2][8]);
			__tmp_coord_array_13__[19] += (-1.0f * __x_xpd__[2][3]);
			__tmp_coord_array_13__[20] += (-1.0f * __x_xpd__[2][4]);
			__tmp_coord_array_13__[21] += (-1.0f * __x_xpd__[2][5]);
			__tmp_coord_array_13__[22] += (-1.0f * __x_xpd__[2][0]);
			__tmp_coord_array_13__[23] += __x_xpd__[2][1];
			__tmp_coord_array_13__[24] += (-1.0f * __x_xpd__[2][2]);
			__tmp_coord_array_13__[25] += (-1.0f * __x_xpd__[2][9]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_13__[6] += __x_xpd__[3][6];
			__tmp_coord_array_13__[7] += (-1.0f * __x_xpd__[3][7]);
			__tmp_coord_array_13__[8] += __x_xpd__[3][8];
			__tmp_coord_array_13__[9] += __x_xpd__[3][3];
			__tmp_coord_array_13__[10] += __x_xpd__[3][4];
			__tmp_coord_array_13__[11] += __x_xpd__[3][5];
			__tmp_coord_array_13__[12] += __x_xpd__[3][0];
			__tmp_coord_array_13__[13] += __x_xpd__[3][1];
			__tmp_coord_array_13__[14] += __x_xpd__[3][2];
			__tmp_coord_array_13__[15] += __x_xpd__[3][9];

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_13__[1] += __x_xpd__[4][4];
			__tmp_coord_array_13__[2] += __x_xpd__[4][1];
			__tmp_coord_array_13__[3] += __x_xpd__[4][2];
			__tmp_coord_array_13__[4] += __x_xpd__[4][3];
			__tmp_coord_array_13__[5] += __x_xpd__[4][0];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_13__[0] += (-1.0f * __x_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_13__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv inverse(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)20), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar n;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			n.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			n.m_c[0] += ((-1.0f * __x_xpd__[1][4] * __x_xpd__[1][0]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (-1.0f * __x_xpd__[1][0] * __x_xpd__[1][4]) + (__x_xpd__[1][3] * __x_xpd__[1][3]));

		}
		if (((x.m_gu & 4) != 0)) {
			n.m_c[0] += ((__x_xpd__[2][2] * __x_xpd__[2][8]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][0] * __x_xpd__[2][6]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][7] * __x_xpd__[2][1]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (-1.0f * __x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][6] * __x_xpd__[2][0]) + (__x_xpd__[2][1] * __x_xpd__[2][7]) + (__x_xpd__[2][8] * __x_xpd__[2][2]));

		}
		if (((x.m_gu & 8) != 0)) {
			n.m_c[0] += ((-1.0f * __x_xpd__[3][3] * __x_xpd__[3][3]) + (-1.0f * __x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (-1.0f * __x_xpd__[3][5] * __x_xpd__[3][5]) + (-1.0f * __x_xpd__[3][0] * __x_xpd__[3][6]) + (__x_xpd__[3][7] * __x_xpd__[3][1]) + (-1.0f * __x_xpd__[3][8] * __x_xpd__[3][2]) + (__x_xpd__[3][1] * __x_xpd__[3][7]) + (-1.0f * __x_xpd__[3][6] * __x_xpd__[3][0]) + (-1.0f * __x_xpd__[3][2] * __x_xpd__[3][8]));

		}
		if (((x.m_gu & 16) != 0)) {
			n.m_c[0] += ((-1.0f * __x_xpd__[4][3] * __x_xpd__[4][3]) + (__x_xpd__[4][4] * __x_xpd__[4][0]) + (-1.0f * __x_xpd__[4][1] * __x_xpd__[4][1]) + (__x_xpd__[4][0] * __x_xpd__[4][4]) + (-1.0f * __x_xpd__[4][2] * __x_xpd__[4][2]));

		}
		if (((x.m_gu & 32) != 0)) {
			n.m_c[0] += (-1.0f * __x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		scalar in;
		in.m_c[0] = ((char)1 / n.m_c[0]);
		mv __temp_var_1__;
		float __tmp_coord_array_14__[32] ;
		mv_zero(__tmp_coord_array_14__, 32);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_14__[0] += (__x_xpd__[0][0] * in.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_14__[1] += (__x_xpd__[1][0] * in.m_c[0]);
			__tmp_coord_array_14__[2] += (__x_xpd__[1][1] * in.m_c[0]);
			__tmp_coord_array_14__[3] += (__x_xpd__[1][2] * in.m_c[0]);
			__tmp_coord_array_14__[4] += (__x_xpd__[1][3] * in.m_c[0]);
			__tmp_coord_array_14__[5] += (__x_xpd__[1][4] * in.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_14__[6] += (-1.0f * __x_xpd__[2][0] * in.m_c[0]);
			__tmp_coord_array_14__[7] += (-1.0f * __x_xpd__[2][1] * in.m_c[0]);
			__tmp_coord_array_14__[8] += (-1.0f * __x_xpd__[2][2] * in.m_c[0]);
			__tmp_coord_array_14__[9] += (-1.0f * __x_xpd__[2][3] * in.m_c[0]);
			__tmp_coord_array_14__[10] += (-1.0f * __x_xpd__[2][4] * in.m_c[0]);
			__tmp_coord_array_14__[11] += (-1.0f * __x_xpd__[2][5] * in.m_c[0]);
			__tmp_coord_array_14__[12] += (-1.0f * __x_xpd__[2][6] * in.m_c[0]);
			__tmp_coord_array_14__[13] += (-1.0f * __x_xpd__[2][7] * in.m_c[0]);
			__tmp_coord_array_14__[14] += (-1.0f * __x_xpd__[2][8] * in.m_c[0]);
			__tmp_coord_array_14__[15] += (-1.0f * __x_xpd__[2][9] * in.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_14__[16] += (-1.0f * __x_xpd__[3][0] * in.m_c[0]);
			__tmp_coord_array_14__[17] += (-1.0f * __x_xpd__[3][1] * in.m_c[0]);
			__tmp_coord_array_14__[18] += (-1.0f * __x_xpd__[3][2] * in.m_c[0]);
			__tmp_coord_array_14__[19] += (-1.0f * __x_xpd__[3][3] * in.m_c[0]);
			__tmp_coord_array_14__[20] += (-1.0f * __x_xpd__[3][4] * in.m_c[0]);
			__tmp_coord_array_14__[21] += (-1.0f * __x_xpd__[3][5] * in.m_c[0]);
			__tmp_coord_array_14__[22] += (-1.0f * __x_xpd__[3][6] * in.m_c[0]);
			__tmp_coord_array_14__[23] += (-1.0f * __x_xpd__[3][7] * in.m_c[0]);
			__tmp_coord_array_14__[24] += (-1.0f * __x_xpd__[3][8] * in.m_c[0]);
			__tmp_coord_array_14__[25] += (-1.0f * __x_xpd__[3][9] * in.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_14__[26] += (__x_xpd__[4][0] * in.m_c[0]);
			__tmp_coord_array_14__[27] += (__x_xpd__[4][1] * in.m_c[0]);
			__tmp_coord_array_14__[28] += (__x_xpd__[4][2] * in.m_c[0]);
			__tmp_coord_array_14__[29] += (__x_xpd__[4][3] * in.m_c[0]);
			__tmp_coord_array_14__[30] += (__x_xpd__[4][4] * in.m_c[0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_14__[31] += (__x_xpd__[5][0] * in.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_14__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv inverseEM(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)21), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		scalar n;
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			n.m_c[0] += (__x_xpd__[0][0] * __x_xpd__[0][0]);

		}
		if (((x.m_gu & 2) != 0)) {
			n.m_c[0] += ((__x_xpd__[1][3] * __x_xpd__[1][3]) + (__x_xpd__[1][4] * __x_xpd__[1][4]) + (__x_xpd__[1][2] * __x_xpd__[1][2]) + (__x_xpd__[1][1] * __x_xpd__[1][1]) + (__x_xpd__[1][0] * __x_xpd__[1][0]));

		}
		if (((x.m_gu & 4) != 0)) {
			n.m_c[0] += ((__x_xpd__[2][9] * __x_xpd__[2][9]) + (__x_xpd__[2][3] * __x_xpd__[2][3]) + (__x_xpd__[2][2] * __x_xpd__[2][2]) + (__x_xpd__[2][4] * __x_xpd__[2][4]) + (__x_xpd__[2][0] * __x_xpd__[2][0]) + (__x_xpd__[2][1] * __x_xpd__[2][1]) + (__x_xpd__[2][5] * __x_xpd__[2][5]) + (__x_xpd__[2][7] * __x_xpd__[2][7]) + (__x_xpd__[2][6] * __x_xpd__[2][6]) + (__x_xpd__[2][8] * __x_xpd__[2][8]));

		}
		if (((x.m_gu & 8) != 0)) {
			n.m_c[0] += ((__x_xpd__[3][6] * __x_xpd__[3][6]) + (__x_xpd__[3][7] * __x_xpd__[3][7]) + (__x_xpd__[3][1] * __x_xpd__[3][1]) + (__x_xpd__[3][4] * __x_xpd__[3][4]) + (__x_xpd__[3][9] * __x_xpd__[3][9]) + (__x_xpd__[3][2] * __x_xpd__[3][2]) + (__x_xpd__[3][3] * __x_xpd__[3][3]) + (__x_xpd__[3][8] * __x_xpd__[3][8]) + (__x_xpd__[3][5] * __x_xpd__[3][5]) + (__x_xpd__[3][0] * __x_xpd__[3][0]));

		}
		if (((x.m_gu & 16) != 0)) {
			n.m_c[0] += ((__x_xpd__[4][1] * __x_xpd__[4][1]) + (__x_xpd__[4][0] * __x_xpd__[4][0]) + (__x_xpd__[4][4] * __x_xpd__[4][4]) + (__x_xpd__[4][2] * __x_xpd__[4][2]) + (__x_xpd__[4][3] * __x_xpd__[4][3]));

		}
		if (((x.m_gu & 32) != 0)) {
			n.m_c[0] += (__x_xpd__[5][0] * __x_xpd__[5][0]);

		}
		scalar in;
		in.m_c[0] = ((char)1 / n.m_c[0]);
		mv __temp_var_1__;
		float __tmp_coord_array_15__[32] ;
		mv_zero(__tmp_coord_array_15__, 32);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_15__[0] += (__x_xpd__[0][0] * in.m_c[0]);

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_15__[1] += (__x_xpd__[1][0] * in.m_c[0]);
			__tmp_coord_array_15__[2] += (__x_xpd__[1][1] * in.m_c[0]);
			__tmp_coord_array_15__[3] += (__x_xpd__[1][2] * in.m_c[0]);
			__tmp_coord_array_15__[4] += (__x_xpd__[1][3] * in.m_c[0]);
			__tmp_coord_array_15__[5] += (__x_xpd__[1][4] * in.m_c[0]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_15__[6] += (-1.0f * __x_xpd__[2][0] * in.m_c[0]);
			__tmp_coord_array_15__[7] += (-1.0f * __x_xpd__[2][1] * in.m_c[0]);
			__tmp_coord_array_15__[8] += (-1.0f * __x_xpd__[2][2] * in.m_c[0]);
			__tmp_coord_array_15__[9] += (-1.0f * __x_xpd__[2][3] * in.m_c[0]);
			__tmp_coord_array_15__[10] += (-1.0f * __x_xpd__[2][4] * in.m_c[0]);
			__tmp_coord_array_15__[11] += (-1.0f * __x_xpd__[2][5] * in.m_c[0]);
			__tmp_coord_array_15__[12] += (-1.0f * __x_xpd__[2][6] * in.m_c[0]);
			__tmp_coord_array_15__[13] += (-1.0f * __x_xpd__[2][7] * in.m_c[0]);
			__tmp_coord_array_15__[14] += (-1.0f * __x_xpd__[2][8] * in.m_c[0]);
			__tmp_coord_array_15__[15] += (-1.0f * __x_xpd__[2][9] * in.m_c[0]);

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_15__[16] += (-1.0f * __x_xpd__[3][0] * in.m_c[0]);
			__tmp_coord_array_15__[17] += (-1.0f * __x_xpd__[3][1] * in.m_c[0]);
			__tmp_coord_array_15__[18] += (-1.0f * __x_xpd__[3][2] * in.m_c[0]);
			__tmp_coord_array_15__[19] += (-1.0f * __x_xpd__[3][3] * in.m_c[0]);
			__tmp_coord_array_15__[20] += (-1.0f * __x_xpd__[3][4] * in.m_c[0]);
			__tmp_coord_array_15__[21] += (-1.0f * __x_xpd__[3][5] * in.m_c[0]);
			__tmp_coord_array_15__[22] += (-1.0f * __x_xpd__[3][6] * in.m_c[0]);
			__tmp_coord_array_15__[23] += (-1.0f * __x_xpd__[3][7] * in.m_c[0]);
			__tmp_coord_array_15__[24] += (-1.0f * __x_xpd__[3][8] * in.m_c[0]);
			__tmp_coord_array_15__[25] += (-1.0f * __x_xpd__[3][9] * in.m_c[0]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_15__[26] += (__x_xpd__[4][0] * in.m_c[0]);
			__tmp_coord_array_15__[27] += (__x_xpd__[4][1] * in.m_c[0]);
			__tmp_coord_array_15__[28] += (__x_xpd__[4][2] * in.m_c[0]);
			__tmp_coord_array_15__[29] += (__x_xpd__[4][3] * in.m_c[0]);
			__tmp_coord_array_15__[30] += (__x_xpd__[4][4] * in.m_c[0]);

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_15__[31] += (__x_xpd__[5][0] * in.m_c[0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_15__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	mv gradeInvolution(const mv& x) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)23), ((unsigned short)-1), ((unsigned short)1), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_16__[32] ;
		mv_zero(__tmp_coord_array_16__, 32);
		const float* __x_xpd__[6] ;
		x.expand(__x_xpd__, true);
		if (((x.m_gu & 1) != 0)) {
			__tmp_coord_array_16__[0] += __x_xpd__[0][0];

		}
		if (((x.m_gu & 2) != 0)) {
			__tmp_coord_array_16__[1] += (-1.0f * __x_xpd__[1][0]);
			__tmp_coord_array_16__[2] += (-1.0f * __x_xpd__[1][1]);
			__tmp_coord_array_16__[3] += (-1.0f * __x_xpd__[1][2]);
			__tmp_coord_array_16__[4] += (-1.0f * __x_xpd__[1][3]);
			__tmp_coord_array_16__[5] += (-1.0f * __x_xpd__[1][4]);

		}
		if (((x.m_gu & 4) != 0)) {
			__tmp_coord_array_16__[6] += __x_xpd__[2][0];
			__tmp_coord_array_16__[7] += __x_xpd__[2][1];
			__tmp_coord_array_16__[8] += __x_xpd__[2][2];
			__tmp_coord_array_16__[9] += __x_xpd__[2][3];
			__tmp_coord_array_16__[10] += __x_xpd__[2][4];
			__tmp_coord_array_16__[11] += __x_xpd__[2][5];
			__tmp_coord_array_16__[12] += __x_xpd__[2][6];
			__tmp_coord_array_16__[13] += __x_xpd__[2][7];
			__tmp_coord_array_16__[14] += __x_xpd__[2][8];
			__tmp_coord_array_16__[15] += __x_xpd__[2][9];

		}
		if (((x.m_gu & 8) != 0)) {
			__tmp_coord_array_16__[16] += (-1.0f * __x_xpd__[3][0]);
			__tmp_coord_array_16__[17] += (-1.0f * __x_xpd__[3][1]);
			__tmp_coord_array_16__[18] += (-1.0f * __x_xpd__[3][2]);
			__tmp_coord_array_16__[19] += (-1.0f * __x_xpd__[3][3]);
			__tmp_coord_array_16__[20] += (-1.0f * __x_xpd__[3][4]);
			__tmp_coord_array_16__[21] += (-1.0f * __x_xpd__[3][5]);
			__tmp_coord_array_16__[22] += (-1.0f * __x_xpd__[3][6]);
			__tmp_coord_array_16__[23] += (-1.0f * __x_xpd__[3][7]);
			__tmp_coord_array_16__[24] += (-1.0f * __x_xpd__[3][8]);
			__tmp_coord_array_16__[25] += (-1.0f * __x_xpd__[3][9]);

		}
		if (((x.m_gu & 16) != 0)) {
			__tmp_coord_array_16__[26] += __x_xpd__[4][0];
			__tmp_coord_array_16__[27] += __x_xpd__[4][1];
			__tmp_coord_array_16__[28] += __x_xpd__[4][2];
			__tmp_coord_array_16__[29] += __x_xpd__[4][3];
			__tmp_coord_array_16__[30] += __x_xpd__[4][4];

		}
		if (((x.m_gu & 32) != 0)) {
			__tmp_coord_array_16__[31] += (-1.0f * __x_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_16__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}

	// G2 functions:
	mv apply_om(const om& x, const mv& y) {
		/* start of profiling instrumentation code */;
		unsigned short __profileArgTypes__[]  = {x.type(), y.type()};
		unsigned short __returnTypes__[1] ;
		g2Profiling::profile(((unsigned int)22), ((unsigned short)-1), ((unsigned short)2), __profileArgTypes__, ((unsigned short)1), __returnTypes__);
		/* end of profiling instrumentation code */;
		mv __temp_var_1__;
		float __tmp_coord_array_17__[32] ;
		mv_zero(__tmp_coord_array_17__, 32);
		const float* __y_xpd__[6] ;
		y.expand(__y_xpd__, true);
		if (((y.m_gu & 2) != 0)) {
			__tmp_coord_array_17__[1] += ((x.m_c[2] * __y_xpd__[1][2]) + (x.m_c[1] * __y_xpd__[1][1]) + (x.m_c[4] * __y_xpd__[1][4]) + (x.m_c[3] * __y_xpd__[1][3]) + (x.m_c[0] * __y_xpd__[1][0]));
			__tmp_coord_array_17__[2] += ((x.m_c[8] * __y_xpd__[1][3]) + (x.m_c[5] * __y_xpd__[1][0]) + (x.m_c[6] * __y_xpd__[1][1]) + (x.m_c[9] * __y_xpd__[1][4]) + (x.m_c[7] * __y_xpd__[1][2]));
			__tmp_coord_array_17__[3] += ((x.m_c[10] * __y_xpd__[1][0]) + (x.m_c[13] * __y_xpd__[1][3]) + (x.m_c[14] * __y_xpd__[1][4]) + (x.m_c[12] * __y_xpd__[1][2]) + (x.m_c[11] * __y_xpd__[1][1]));
			__tmp_coord_array_17__[4] += ((x.m_c[17] * __y_xpd__[1][2]) + (x.m_c[19] * __y_xpd__[1][4]) + (x.m_c[18] * __y_xpd__[1][3]) + (x.m_c[16] * __y_xpd__[1][1]) + (x.m_c[15] * __y_xpd__[1][0]));
			__tmp_coord_array_17__[5] += ((x.m_c[22] * __y_xpd__[1][2]) + (x.m_c[20] * __y_xpd__[1][0]) + (x.m_c[24] * __y_xpd__[1][4]) + (x.m_c[21] * __y_xpd__[1][1]) + (x.m_c[23] * __y_xpd__[1][3]));

		}
		if (((y.m_gu & 4) != 0)) {
			__tmp_coord_array_17__[6] += ((x.m_c[26] * __y_xpd__[2][1]) + (x.m_c[31] * __y_xpd__[2][6]) + (x.m_c[33] * __y_xpd__[2][8]) + (x.m_c[30] * __y_xpd__[2][5]) + (x.m_c[25] * __y_xpd__[2][0]) + (x.m_c[29] * __y_xpd__[2][4]) + (x.m_c[28] * __y_xpd__[2][3]) + (x.m_c[32] * __y_xpd__[2][7]) + (x.m_c[34] * __y_xpd__[2][9]) + (x.m_c[27] * __y_xpd__[2][2]));
			__tmp_coord_array_17__[7] += ((x.m_c[44] * __y_xpd__[2][9]) + (x.m_c[42] * __y_xpd__[2][7]) + (x.m_c[40] * __y_xpd__[2][5]) + (x.m_c[38] * __y_xpd__[2][3]) + (x.m_c[39] * __y_xpd__[2][4]) + (x.m_c[37] * __y_xpd__[2][2]) + (x.m_c[43] * __y_xpd__[2][8]) + (x.m_c[41] * __y_xpd__[2][6]) + (x.m_c[36] * __y_xpd__[2][1]) + (x.m_c[35] * __y_xpd__[2][0]));
			__tmp_coord_array_17__[8] += ((x.m_c[45] * __y_xpd__[2][0]) + (x.m_c[51] * __y_xpd__[2][6]) + (x.m_c[53] * __y_xpd__[2][8]) + (x.m_c[54] * __y_xpd__[2][9]) + (x.m_c[49] * __y_xpd__[2][4]) + (x.m_c[46] * __y_xpd__[2][1]) + (x.m_c[47] * __y_xpd__[2][2]) + (x.m_c[48] * __y_xpd__[2][3]) + (x.m_c[50] * __y_xpd__[2][5]) + (x.m_c[52] * __y_xpd__[2][7]));
			__tmp_coord_array_17__[9] += ((x.m_c[60] * __y_xpd__[2][5]) + (x.m_c[57] * __y_xpd__[2][2]) + (x.m_c[58] * __y_xpd__[2][3]) + (x.m_c[55] * __y_xpd__[2][0]) + (x.m_c[56] * __y_xpd__[2][1]) + (x.m_c[61] * __y_xpd__[2][6]) + (x.m_c[62] * __y_xpd__[2][7]) + (x.m_c[64] * __y_xpd__[2][9]) + (x.m_c[59] * __y_xpd__[2][4]) + (x.m_c[63] * __y_xpd__[2][8]));
			__tmp_coord_array_17__[10] += ((x.m_c[65] * __y_xpd__[2][0]) + (x.m_c[69] * __y_xpd__[2][4]) + (x.m_c[70] * __y_xpd__[2][5]) + (x.m_c[66] * __y_xpd__[2][1]) + (x.m_c[68] * __y_xpd__[2][3]) + (x.m_c[73] * __y_xpd__[2][8]) + (x.m_c[67] * __y_xpd__[2][2]) + (x.m_c[71] * __y_xpd__[2][6]) + (x.m_c[74] * __y_xpd__[2][9]) + (x.m_c[72] * __y_xpd__[2][7]));
			__tmp_coord_array_17__[11] += ((x.m_c[83] * __y_xpd__[2][8]) + (x.m_c[76] * __y_xpd__[2][1]) + (x.m_c[82] * __y_xpd__[2][7]) + (x.m_c[77] * __y_xpd__[2][2]) + (x.m_c[75] * __y_xpd__[2][0]) + (x.m_c[80] * __y_xpd__[2][5]) + (x.m_c[81] * __y_xpd__[2][6]) + (x.m_c[79] * __y_xpd__[2][4]) + (x.m_c[78] * __y_xpd__[2][3]) + (x.m_c[84] * __y_xpd__[2][9]));
			__tmp_coord_array_17__[12] += ((x.m_c[87] * __y_xpd__[2][2]) + (x.m_c[93] * __y_xpd__[2][8]) + (x.m_c[91] * __y_xpd__[2][6]) + (x.m_c[89] * __y_xpd__[2][4]) + (x.m_c[94] * __y_xpd__[2][9]) + (x.m_c[88] * __y_xpd__[2][3]) + (x.m_c[90] * __y_xpd__[2][5]) + (x.m_c[85] * __y_xpd__[2][0]) + (x.m_c[92] * __y_xpd__[2][7]) + (x.m_c[86] * __y_xpd__[2][1]));
			__tmp_coord_array_17__[13] += ((x.m_c[99] * __y_xpd__[2][4]) + (x.m_c[95] * __y_xpd__[2][0]) + (x.m_c[96] * __y_xpd__[2][1]) + (x.m_c[102] * __y_xpd__[2][7]) + (x.m_c[100] * __y_xpd__[2][5]) + (x.m_c[104] * __y_xpd__[2][9]) + (x.m_c[97] * __y_xpd__[2][2]) + (x.m_c[98] * __y_xpd__[2][3]) + (x.m_c[101] * __y_xpd__[2][6]) + (x.m_c[103] * __y_xpd__[2][8]));
			__tmp_coord_array_17__[14] += ((x.m_c[111] * __y_xpd__[2][6]) + (x.m_c[109] * __y_xpd__[2][4]) + (x.m_c[107] * __y_xpd__[2][2]) + (x.m_c[106] * __y_xpd__[2][1]) + (x.m_c[114] * __y_xpd__[2][9]) + (x.m_c[113] * __y_xpd__[2][8]) + (x.m_c[105] * __y_xpd__[2][0]) + (x.m_c[110] * __y_xpd__[2][5]) + (x.m_c[112] * __y_xpd__[2][7]) + (x.m_c[108] * __y_xpd__[2][3]));
			__tmp_coord_array_17__[15] += ((x.m_c[115] * __y_xpd__[2][0]) + (x.m_c[120] * __y_xpd__[2][5]) + (x.m_c[119] * __y_xpd__[2][4]) + (x.m_c[118] * __y_xpd__[2][3]) + (x.m_c[117] * __y_xpd__[2][2]) + (x.m_c[124] * __y_xpd__[2][9]) + (x.m_c[122] * __y_xpd__[2][7]) + (x.m_c[116] * __y_xpd__[2][1]) + (x.m_c[123] * __y_xpd__[2][8]) + (x.m_c[121] * __y_xpd__[2][6]));

		}
		if (((y.m_gu & 8) != 0)) {
			__tmp_coord_array_17__[16] += ((x.m_c[128] * __y_xpd__[3][3]) + (x.m_c[125] * __y_xpd__[3][0]) + (x.m_c[126] * __y_xpd__[3][1]) + (x.m_c[131] * __y_xpd__[3][6]) + (x.m_c[129] * __y_xpd__[3][4]) + (x.m_c[134] * __y_xpd__[3][9]) + (x.m_c[130] * __y_xpd__[3][5]) + (x.m_c[127] * __y_xpd__[3][2]) + (x.m_c[132] * __y_xpd__[3][7]) + (x.m_c[133] * __y_xpd__[3][8]));
			__tmp_coord_array_17__[17] += ((x.m_c[144] * __y_xpd__[3][9]) + (x.m_c[137] * __y_xpd__[3][2]) + (x.m_c[142] * __y_xpd__[3][7]) + (x.m_c[140] * __y_xpd__[3][5]) + (x.m_c[138] * __y_xpd__[3][3]) + (x.m_c[139] * __y_xpd__[3][4]) + (x.m_c[136] * __y_xpd__[3][1]) + (x.m_c[143] * __y_xpd__[3][8]) + (x.m_c[141] * __y_xpd__[3][6]) + (x.m_c[135] * __y_xpd__[3][0]));
			__tmp_coord_array_17__[18] += ((x.m_c[145] * __y_xpd__[3][0]) + (x.m_c[146] * __y_xpd__[3][1]) + (x.m_c[148] * __y_xpd__[3][3]) + (x.m_c[150] * __y_xpd__[3][5]) + (x.m_c[154] * __y_xpd__[3][9]) + (x.m_c[147] * __y_xpd__[3][2]) + (x.m_c[153] * __y_xpd__[3][8]) + (x.m_c[149] * __y_xpd__[3][4]) + (x.m_c[151] * __y_xpd__[3][6]) + (x.m_c[152] * __y_xpd__[3][7]));
			__tmp_coord_array_17__[19] += ((x.m_c[164] * __y_xpd__[3][9]) + (x.m_c[156] * __y_xpd__[3][1]) + (x.m_c[160] * __y_xpd__[3][5]) + (x.m_c[157] * __y_xpd__[3][2]) + (x.m_c[162] * __y_xpd__[3][7]) + (x.m_c[163] * __y_xpd__[3][8]) + (x.m_c[161] * __y_xpd__[3][6]) + (x.m_c[155] * __y_xpd__[3][0]) + (x.m_c[158] * __y_xpd__[3][3]) + (x.m_c[159] * __y_xpd__[3][4]));
			__tmp_coord_array_17__[20] += ((x.m_c[171] * __y_xpd__[3][6]) + (x.m_c[170] * __y_xpd__[3][5]) + (x.m_c[166] * __y_xpd__[3][1]) + (x.m_c[172] * __y_xpd__[3][7]) + (x.m_c[167] * __y_xpd__[3][2]) + (x.m_c[168] * __y_xpd__[3][3]) + (x.m_c[165] * __y_xpd__[3][0]) + (x.m_c[174] * __y_xpd__[3][9]) + (x.m_c[169] * __y_xpd__[3][4]) + (x.m_c[173] * __y_xpd__[3][8]));
			__tmp_coord_array_17__[21] += ((x.m_c[177] * __y_xpd__[3][2]) + (x.m_c[178] * __y_xpd__[3][3]) + (x.m_c[182] * __y_xpd__[3][7]) + (x.m_c[175] * __y_xpd__[3][0]) + (x.m_c[176] * __y_xpd__[3][1]) + (x.m_c[183] * __y_xpd__[3][8]) + (x.m_c[179] * __y_xpd__[3][4]) + (x.m_c[180] * __y_xpd__[3][5]) + (x.m_c[181] * __y_xpd__[3][6]) + (x.m_c[184] * __y_xpd__[3][9]));
			__tmp_coord_array_17__[22] += ((x.m_c[193] * __y_xpd__[3][8]) + (x.m_c[192] * __y_xpd__[3][7]) + (x.m_c[185] * __y_xpd__[3][0]) + (x.m_c[194] * __y_xpd__[3][9]) + (x.m_c[190] * __y_xpd__[3][5]) + (x.m_c[189] * __y_xpd__[3][4]) + (x.m_c[187] * __y_xpd__[3][2]) + (x.m_c[188] * __y_xpd__[3][3]) + (x.m_c[186] * __y_xpd__[3][1]) + (x.m_c[191] * __y_xpd__[3][6]));
			__tmp_coord_array_17__[23] += ((x.m_c[197] * __y_xpd__[3][2]) + (x.m_c[195] * __y_xpd__[3][0]) + (x.m_c[201] * __y_xpd__[3][6]) + (x.m_c[204] * __y_xpd__[3][9]) + (x.m_c[198] * __y_xpd__[3][3]) + (x.m_c[203] * __y_xpd__[3][8]) + (x.m_c[200] * __y_xpd__[3][5]) + (x.m_c[199] * __y_xpd__[3][4]) + (x.m_c[196] * __y_xpd__[3][1]) + (x.m_c[202] * __y_xpd__[3][7]));
			__tmp_coord_array_17__[24] += ((x.m_c[214] * __y_xpd__[3][9]) + (x.m_c[211] * __y_xpd__[3][6]) + (x.m_c[206] * __y_xpd__[3][1]) + (x.m_c[207] * __y_xpd__[3][2]) + (x.m_c[212] * __y_xpd__[3][7]) + (x.m_c[208] * __y_xpd__[3][3]) + (x.m_c[205] * __y_xpd__[3][0]) + (x.m_c[210] * __y_xpd__[3][5]) + (x.m_c[213] * __y_xpd__[3][8]) + (x.m_c[209] * __y_xpd__[3][4]));
			__tmp_coord_array_17__[25] += ((x.m_c[221] * __y_xpd__[3][6]) + (x.m_c[217] * __y_xpd__[3][2]) + (x.m_c[223] * __y_xpd__[3][8]) + (x.m_c[220] * __y_xpd__[3][5]) + (x.m_c[218] * __y_xpd__[3][3]) + (x.m_c[224] * __y_xpd__[3][9]) + (x.m_c[222] * __y_xpd__[3][7]) + (x.m_c[219] * __y_xpd__[3][4]) + (x.m_c[216] * __y_xpd__[3][1]) + (x.m_c[215] * __y_xpd__[3][0]));

		}
		if (((y.m_gu & 16) != 0)) {
			__tmp_coord_array_17__[26] += ((x.m_c[226] * __y_xpd__[4][1]) + (x.m_c[225] * __y_xpd__[4][0]) + (-1.0f * x.m_c[227] * __y_xpd__[4][2]) + (x.m_c[229] * __y_xpd__[4][4]) + (x.m_c[228] * __y_xpd__[4][3]));
			__tmp_coord_array_17__[27] += ((-1.0f * x.m_c[232] * __y_xpd__[4][2]) + (x.m_c[230] * __y_xpd__[4][0]) + (x.m_c[233] * __y_xpd__[4][3]) + (x.m_c[234] * __y_xpd__[4][4]) + (x.m_c[231] * __y_xpd__[4][1]));
			__tmp_coord_array_17__[28] += ((-1.0f * x.m_c[235] * __y_xpd__[4][0]) + (-1.0f * x.m_c[236] * __y_xpd__[4][1]) + (-1.0f * x.m_c[239] * __y_xpd__[4][4]) + (x.m_c[237] * __y_xpd__[4][2]) + (-1.0f * x.m_c[238] * __y_xpd__[4][3]));
			__tmp_coord_array_17__[29] += ((x.m_c[243] * __y_xpd__[4][3]) + (x.m_c[241] * __y_xpd__[4][1]) + (x.m_c[240] * __y_xpd__[4][0]) + (x.m_c[244] * __y_xpd__[4][4]) + (-1.0f * x.m_c[242] * __y_xpd__[4][2]));
			__tmp_coord_array_17__[30] += ((x.m_c[249] * __y_xpd__[4][4]) + (x.m_c[248] * __y_xpd__[4][3]) + (x.m_c[246] * __y_xpd__[4][1]) + (-1.0f * x.m_c[247] * __y_xpd__[4][2]) + (x.m_c[245] * __y_xpd__[4][0]));

		}
		if (((y.m_gu & 32) != 0)) {
			__tmp_coord_array_17__[31] += (x.m_c[250] * __y_xpd__[5][0]);

		}
		__temp_var_1__ = mv_compress(__tmp_coord_array_17__);
		__temp_var_1__.type(((g2Type)((short)__returnTypes__[0])));
		return __temp_var_1__;
	}
	namespace __G2_GENERATED__ {
		void set(om& __x__, const point& __image_of_no__, const point& __image_of_e1__, const point& __image_of_e2__, const point& __image_of_e3__, const point& __image_of_ni__) {
			__x__.m_c[0] = __image_of_no__.m_c[0];
			__x__.m_c[5] = __image_of_no__.m_c[1];
			__x__.m_c[10] = __image_of_no__.m_c[2];
			__x__.m_c[15] = __image_of_no__.m_c[3];
			__x__.m_c[20] = __image_of_no__.m_c[4];
			__x__.m_c[1] = __image_of_e1__.m_c[0];
			__x__.m_c[6] = __image_of_e1__.m_c[1];
			__x__.m_c[11] = __image_of_e1__.m_c[2];
			__x__.m_c[16] = __image_of_e1__.m_c[3];
			__x__.m_c[21] = __image_of_e1__.m_c[4];
			__x__.m_c[2] = __image_of_e2__.m_c[0];
			__x__.m_c[7] = __image_of_e2__.m_c[1];
			__x__.m_c[12] = __image_of_e2__.m_c[2];
			__x__.m_c[17] = __image_of_e2__.m_c[3];
			__x__.m_c[22] = __image_of_e2__.m_c[4];
			__x__.m_c[3] = __image_of_e3__.m_c[0];
			__x__.m_c[8] = __image_of_e3__.m_c[1];
			__x__.m_c[13] = __image_of_e3__.m_c[2];
			__x__.m_c[18] = __image_of_e3__.m_c[3];
			__x__.m_c[23] = __image_of_e3__.m_c[4];
			__x__.m_c[4] = __image_of_ni__.m_c[0];
			__x__.m_c[9] = __image_of_ni__.m_c[1];
			__x__.m_c[14] = __image_of_ni__.m_c[2];
			__x__.m_c[19] = __image_of_ni__.m_c[3];
			__x__.m_c[24] = __image_of_ni__.m_c[4];
			__x__.m_c[25] = ((-1.0f * __x__.m_c[1] * __x__.m_c[5]) + (__x__.m_c[6] * __x__.m_c[0]));
			__x__.m_c[35] = ((__x__.m_c[11] * __x__.m_c[0]) + (-1.0f * __x__.m_c[1] * __x__.m_c[10]));
			__x__.m_c[45] = ((-1.0f * __x__.m_c[1] * __x__.m_c[15]) + (__x__.m_c[16] * __x__.m_c[0]));
			__x__.m_c[55] = ((-1.0f * __x__.m_c[6] * __x__.m_c[10]) + (__x__.m_c[11] * __x__.m_c[5]));
			__x__.m_c[65] = ((__x__.m_c[16] * __x__.m_c[10]) + (-1.0f * __x__.m_c[11] * __x__.m_c[15]));
			__x__.m_c[75] = ((__x__.m_c[6] * __x__.m_c[15]) + (-1.0f * __x__.m_c[16] * __x__.m_c[5]));
			__x__.m_c[85] = ((__x__.m_c[21] * __x__.m_c[5]) + (-1.0f * __x__.m_c[6] * __x__.m_c[20]));
			__x__.m_c[95] = ((-1.0f * __x__.m_c[11] * __x__.m_c[20]) + (__x__.m_c[21] * __x__.m_c[10]));
			__x__.m_c[105] = ((-1.0f * __x__.m_c[16] * __x__.m_c[20]) + (__x__.m_c[21] * __x__.m_c[15]));
			__x__.m_c[115] = ((-1.0f * __x__.m_c[1] * __x__.m_c[20]) + (__x__.m_c[21] * __x__.m_c[0]));
			__x__.m_c[26] = ((-1.0f * __x__.m_c[2] * __x__.m_c[5]) + (__x__.m_c[7] * __x__.m_c[0]));
			__x__.m_c[36] = ((__x__.m_c[12] * __x__.m_c[0]) + (-1.0f * __x__.m_c[2] * __x__.m_c[10]));
			__x__.m_c[46] = ((__x__.m_c[17] * __x__.m_c[0]) + (-1.0f * __x__.m_c[2] * __x__.m_c[15]));
			__x__.m_c[56] = ((__x__.m_c[12] * __x__.m_c[5]) + (-1.0f * __x__.m_c[7] * __x__.m_c[10]));
			__x__.m_c[66] = ((__x__.m_c[17] * __x__.m_c[10]) + (-1.0f * __x__.m_c[12] * __x__.m_c[15]));
			__x__.m_c[76] = ((-1.0f * __x__.m_c[17] * __x__.m_c[5]) + (__x__.m_c[7] * __x__.m_c[15]));
			__x__.m_c[86] = ((-1.0f * __x__.m_c[7] * __x__.m_c[20]) + (__x__.m_c[22] * __x__.m_c[5]));
			__x__.m_c[96] = ((-1.0f * __x__.m_c[12] * __x__.m_c[20]) + (__x__.m_c[22] * __x__.m_c[10]));
			__x__.m_c[106] = ((-1.0f * __x__.m_c[17] * __x__.m_c[20]) + (__x__.m_c[22] * __x__.m_c[15]));
			__x__.m_c[116] = ((-1.0f * __x__.m_c[2] * __x__.m_c[20]) + (__x__.m_c[22] * __x__.m_c[0]));
			__x__.m_c[27] = ((-1.0f * __x__.m_c[3] * __x__.m_c[5]) + (__x__.m_c[8] * __x__.m_c[0]));
			__x__.m_c[37] = ((-1.0f * __x__.m_c[3] * __x__.m_c[10]) + (__x__.m_c[13] * __x__.m_c[0]));
			__x__.m_c[47] = ((-1.0f * __x__.m_c[3] * __x__.m_c[15]) + (__x__.m_c[18] * __x__.m_c[0]));
			__x__.m_c[57] = ((__x__.m_c[13] * __x__.m_c[5]) + (-1.0f * __x__.m_c[8] * __x__.m_c[10]));
			__x__.m_c[67] = ((__x__.m_c[18] * __x__.m_c[10]) + (-1.0f * __x__.m_c[13] * __x__.m_c[15]));
			__x__.m_c[77] = ((__x__.m_c[8] * __x__.m_c[15]) + (-1.0f * __x__.m_c[18] * __x__.m_c[5]));
			__x__.m_c[87] = ((-1.0f * __x__.m_c[8] * __x__.m_c[20]) + (__x__.m_c[23] * __x__.m_c[5]));
			__x__.m_c[97] = ((__x__.m_c[23] * __x__.m_c[10]) + (-1.0f * __x__.m_c[13] * __x__.m_c[20]));
			__x__.m_c[107] = ((-1.0f * __x__.m_c[18] * __x__.m_c[20]) + (__x__.m_c[23] * __x__.m_c[15]));
			__x__.m_c[117] = ((__x__.m_c[23] * __x__.m_c[0]) + (-1.0f * __x__.m_c[3] * __x__.m_c[20]));
			__x__.m_c[28] = ((__x__.m_c[7] * __x__.m_c[1]) + (-1.0f * __x__.m_c[2] * __x__.m_c[6]));
			__x__.m_c[38] = ((__x__.m_c[12] * __x__.m_c[1]) + (-1.0f * __x__.m_c[2] * __x__.m_c[11]));
			__x__.m_c[48] = ((__x__.m_c[17] * __x__.m_c[1]) + (-1.0f * __x__.m_c[2] * __x__.m_c[16]));
			__x__.m_c[58] = ((__x__.m_c[12] * __x__.m_c[6]) + (-1.0f * __x__.m_c[7] * __x__.m_c[11]));
			__x__.m_c[68] = ((__x__.m_c[17] * __x__.m_c[11]) + (-1.0f * __x__.m_c[12] * __x__.m_c[16]));
			__x__.m_c[78] = ((__x__.m_c[7] * __x__.m_c[16]) + (-1.0f * __x__.m_c[17] * __x__.m_c[6]));
			__x__.m_c[88] = ((-1.0f * __x__.m_c[7] * __x__.m_c[21]) + (__x__.m_c[22] * __x__.m_c[6]));
			__x__.m_c[98] = ((__x__.m_c[22] * __x__.m_c[11]) + (-1.0f * __x__.m_c[12] * __x__.m_c[21]));
			__x__.m_c[108] = ((-1.0f * __x__.m_c[17] * __x__.m_c[21]) + (__x__.m_c[22] * __x__.m_c[16]));
			__x__.m_c[118] = ((__x__.m_c[22] * __x__.m_c[1]) + (-1.0f * __x__.m_c[2] * __x__.m_c[21]));
			__x__.m_c[29] = ((-1.0f * __x__.m_c[3] * __x__.m_c[7]) + (__x__.m_c[8] * __x__.m_c[2]));
			__x__.m_c[39] = ((__x__.m_c[13] * __x__.m_c[2]) + (-1.0f * __x__.m_c[3] * __x__.m_c[12]));
			__x__.m_c[49] = ((__x__.m_c[18] * __x__.m_c[2]) + (-1.0f * __x__.m_c[3] * __x__.m_c[17]));
			__x__.m_c[59] = ((__x__.m_c[13] * __x__.m_c[7]) + (-1.0f * __x__.m_c[8] * __x__.m_c[12]));
			__x__.m_c[69] = ((-1.0f * __x__.m_c[13] * __x__.m_c[17]) + (__x__.m_c[18] * __x__.m_c[12]));
			__x__.m_c[79] = ((-1.0f * __x__.m_c[18] * __x__.m_c[7]) + (__x__.m_c[8] * __x__.m_c[17]));
			__x__.m_c[89] = ((__x__.m_c[23] * __x__.m_c[7]) + (-1.0f * __x__.m_c[8] * __x__.m_c[22]));
			__x__.m_c[99] = ((-1.0f * __x__.m_c[13] * __x__.m_c[22]) + (__x__.m_c[23] * __x__.m_c[12]));
			__x__.m_c[109] = ((__x__.m_c[23] * __x__.m_c[17]) + (-1.0f * __x__.m_c[18] * __x__.m_c[22]));
			__x__.m_c[119] = ((-1.0f * __x__.m_c[3] * __x__.m_c[22]) + (__x__.m_c[23] * __x__.m_c[2]));
			__x__.m_c[30] = ((-1.0f * __x__.m_c[8] * __x__.m_c[1]) + (__x__.m_c[3] * __x__.m_c[6]));
			__x__.m_c[40] = ((__x__.m_c[3] * __x__.m_c[11]) + (-1.0f * __x__.m_c[13] * __x__.m_c[1]));
			__x__.m_c[50] = ((__x__.m_c[3] * __x__.m_c[16]) + (-1.0f * __x__.m_c[18] * __x__.m_c[1]));
			__x__.m_c[60] = ((-1.0f * __x__.m_c[13] * __x__.m_c[6]) + (__x__.m_c[8] * __x__.m_c[11]));
			__x__.m_c[70] = ((__x__.m_c[13] * __x__.m_c[16]) + (-1.0f * __x__.m_c[18] * __x__.m_c[11]));
			__x__.m_c[80] = ((__x__.m_c[18] * __x__.m_c[6]) + (-1.0f * __x__.m_c[8] * __x__.m_c[16]));
			__x__.m_c[90] = ((__x__.m_c[8] * __x__.m_c[21]) + (-1.0f * __x__.m_c[23] * __x__.m_c[6]));
			__x__.m_c[100] = ((-1.0f * __x__.m_c[23] * __x__.m_c[11]) + (__x__.m_c[13] * __x__.m_c[21]));
			__x__.m_c[110] = ((__x__.m_c[18] * __x__.m_c[21]) + (-1.0f * __x__.m_c[23] * __x__.m_c[16]));
			__x__.m_c[120] = ((-1.0f * __x__.m_c[23] * __x__.m_c[1]) + (__x__.m_c[3] * __x__.m_c[21]));
			__x__.m_c[31] = ((-1.0f * __x__.m_c[4] * __x__.m_c[6]) + (__x__.m_c[9] * __x__.m_c[1]));
			__x__.m_c[41] = ((-1.0f * __x__.m_c[4] * __x__.m_c[11]) + (__x__.m_c[14] * __x__.m_c[1]));
			__x__.m_c[51] = ((__x__.m_c[19] * __x__.m_c[1]) + (-1.0f * __x__.m_c[4] * __x__.m_c[16]));
			__x__.m_c[61] = ((-1.0f * __x__.m_c[9] * __x__.m_c[11]) + (__x__.m_c[14] * __x__.m_c[6]));
			__x__.m_c[71] = ((-1.0f * __x__.m_c[14] * __x__.m_c[16]) + (__x__.m_c[19] * __x__.m_c[11]));
			__x__.m_c[81] = ((-1.0f * __x__.m_c[19] * __x__.m_c[6]) + (__x__.m_c[9] * __x__.m_c[16]));
			__x__.m_c[91] = ((-1.0f * __x__.m_c[9] * __x__.m_c[21]) + (__x__.m_c[24] * __x__.m_c[6]));
			__x__.m_c[101] = ((-1.0f * __x__.m_c[14] * __x__.m_c[21]) + (__x__.m_c[24] * __x__.m_c[11]));
			__x__.m_c[111] = ((__x__.m_c[24] * __x__.m_c[16]) + (-1.0f * __x__.m_c[19] * __x__.m_c[21]));
			__x__.m_c[121] = ((__x__.m_c[24] * __x__.m_c[1]) + (-1.0f * __x__.m_c[4] * __x__.m_c[21]));
			__x__.m_c[32] = ((-1.0f * __x__.m_c[4] * __x__.m_c[7]) + (__x__.m_c[9] * __x__.m_c[2]));
			__x__.m_c[42] = ((-1.0f * __x__.m_c[4] * __x__.m_c[12]) + (__x__.m_c[14] * __x__.m_c[2]));
			__x__.m_c[52] = ((__x__.m_c[19] * __x__.m_c[2]) + (-1.0f * __x__.m_c[4] * __x__.m_c[17]));
			__x__.m_c[62] = ((__x__.m_c[14] * __x__.m_c[7]) + (-1.0f * __x__.m_c[9] * __x__.m_c[12]));
			__x__.m_c[72] = ((__x__.m_c[19] * __x__.m_c[12]) + (-1.0f * __x__.m_c[14] * __x__.m_c[17]));
			__x__.m_c[82] = ((__x__.m_c[9] * __x__.m_c[17]) + (-1.0f * __x__.m_c[19] * __x__.m_c[7]));
			__x__.m_c[92] = ((-1.0f * __x__.m_c[9] * __x__.m_c[22]) + (__x__.m_c[24] * __x__.m_c[7]));
			__x__.m_c[102] = ((__x__.m_c[24] * __x__.m_c[12]) + (-1.0f * __x__.m_c[14] * __x__.m_c[22]));
			__x__.m_c[112] = ((-1.0f * __x__.m_c[19] * __x__.m_c[22]) + (__x__.m_c[24] * __x__.m_c[17]));
			__x__.m_c[122] = ((__x__.m_c[24] * __x__.m_c[2]) + (-1.0f * __x__.m_c[4] * __x__.m_c[22]));
			__x__.m_c[33] = ((-1.0f * __x__.m_c[4] * __x__.m_c[8]) + (__x__.m_c[9] * __x__.m_c[3]));
			__x__.m_c[43] = ((__x__.m_c[14] * __x__.m_c[3]) + (-1.0f * __x__.m_c[4] * __x__.m_c[13]));
			__x__.m_c[53] = ((__x__.m_c[19] * __x__.m_c[3]) + (-1.0f * __x__.m_c[4] * __x__.m_c[18]));
			__x__.m_c[63] = ((__x__.m_c[14] * __x__.m_c[8]) + (-1.0f * __x__.m_c[9] * __x__.m_c[13]));
			__x__.m_c[73] = ((__x__.m_c[19] * __x__.m_c[13]) + (-1.0f * __x__.m_c[14] * __x__.m_c[18]));
			__x__.m_c[83] = ((-1.0f * __x__.m_c[19] * __x__.m_c[8]) + (__x__.m_c[9] * __x__.m_c[18]));
			__x__.m_c[93] = ((__x__.m_c[24] * __x__.m_c[8]) + (-1.0f * __x__.m_c[9] * __x__.m_c[23]));
			__x__.m_c[103] = ((__x__.m_c[24] * __x__.m_c[13]) + (-1.0f * __x__.m_c[14] * __x__.m_c[23]));
			__x__.m_c[113] = ((__x__.m_c[24] * __x__.m_c[18]) + (-1.0f * __x__.m_c[19] * __x__.m_c[23]));
			__x__.m_c[123] = ((-1.0f * __x__.m_c[4] * __x__.m_c[23]) + (__x__.m_c[24] * __x__.m_c[3]));
			__x__.m_c[34] = ((-1.0f * __x__.m_c[4] * __x__.m_c[5]) + (__x__.m_c[9] * __x__.m_c[0]));
			__x__.m_c[44] = ((__x__.m_c[14] * __x__.m_c[0]) + (-1.0f * __x__.m_c[4] * __x__.m_c[10]));
			__x__.m_c[54] = ((__x__.m_c[19] * __x__.m_c[0]) + (-1.0f * __x__.m_c[4] * __x__.m_c[15]));
			__x__.m_c[64] = ((-1.0f * __x__.m_c[9] * __x__.m_c[10]) + (__x__.m_c[14] * __x__.m_c[5]));
			__x__.m_c[74] = ((-1.0f * __x__.m_c[14] * __x__.m_c[15]) + (__x__.m_c[19] * __x__.m_c[10]));
			__x__.m_c[84] = ((__x__.m_c[9] * __x__.m_c[15]) + (-1.0f * __x__.m_c[19] * __x__.m_c[5]));
			__x__.m_c[94] = ((__x__.m_c[24] * __x__.m_c[5]) + (-1.0f * __x__.m_c[9] * __x__.m_c[20]));
			__x__.m_c[104] = ((-1.0f * __x__.m_c[14] * __x__.m_c[20]) + (__x__.m_c[24] * __x__.m_c[10]));
			__x__.m_c[114] = ((-1.0f * __x__.m_c[19] * __x__.m_c[20]) + (__x__.m_c[24] * __x__.m_c[15]));
			__x__.m_c[124] = ((-1.0f * __x__.m_c[4] * __x__.m_c[20]) + (__x__.m_c[24] * __x__.m_c[0]));
			__x__.m_c[125] = ((-1.0f * __x__.m_c[103] * __x__.m_c[17]) + (__x__.m_c[73] * __x__.m_c[22]) + (__x__.m_c[113] * __x__.m_c[12]));
			__x__.m_c[135] = ((__x__.m_c[83] * __x__.m_c[22]) + (__x__.m_c[93] * __x__.m_c[17]) + (-1.0f * __x__.m_c[113] * __x__.m_c[7]));
			__x__.m_c[145] = ((__x__.m_c[103] * __x__.m_c[7]) + (-1.0f * __x__.m_c[93] * __x__.m_c[12]) + (__x__.m_c[63] * __x__.m_c[22]));
			__x__.m_c[155] = ((__x__.m_c[113] * __x__.m_c[2]) + (-1.0f * __x__.m_c[123] * __x__.m_c[17]) + (__x__.m_c[53] * __x__.m_c[22]));
			__x__.m_c[165] = ((__x__.m_c[93] * __x__.m_c[2]) + (-1.0f * __x__.m_c[123] * __x__.m_c[7]) + (__x__.m_c[33] * __x__.m_c[22]));
			__x__.m_c[175] = ((-1.0f * __x__.m_c[123] * __x__.m_c[12]) + (__x__.m_c[43] * __x__.m_c[22]) + (__x__.m_c[103] * __x__.m_c[2]));
			__x__.m_c[185] = ((__x__.m_c[73] * __x__.m_c[2]) + (__x__.m_c[43] * __x__.m_c[17]) + (-1.0f * __x__.m_c[53] * __x__.m_c[12]));
			__x__.m_c[195] = ((-1.0f * __x__.m_c[53] * __x__.m_c[7]) + (__x__.m_c[33] * __x__.m_c[17]) + (-1.0f * __x__.m_c[83] * __x__.m_c[2]));
			__x__.m_c[205] = ((-1.0f * __x__.m_c[43] * __x__.m_c[7]) + (__x__.m_c[63] * __x__.m_c[2]) + (__x__.m_c[33] * __x__.m_c[12]));
			__x__.m_c[215] = ((__x__.m_c[83] * __x__.m_c[12]) + (__x__.m_c[63] * __x__.m_c[17]) + (__x__.m_c[73] * __x__.m_c[7]));
			__x__.m_c[126] = ((-1.0f * __x__.m_c[113] * __x__.m_c[11]) + (__x__.m_c[103] * __x__.m_c[16]) + (-1.0f * __x__.m_c[73] * __x__.m_c[21]));
			__x__.m_c[136] = ((__x__.m_c[113] * __x__.m_c[6]) + (-1.0f * __x__.m_c[93] * __x__.m_c[16]) + (-1.0f * __x__.m_c[83] * __x__.m_c[21]));
			__x__.m_c[146] = ((-1.0f * __x__.m_c[103] * __x__.m_c[6]) + (__x__.m_c[93] * __x__.m_c[11]) + (-1.0f * __x__.m_c[63] * __x__.m_c[21]));
			__x__.m_c[156] = ((-1.0f * __x__.m_c[53] * __x__.m_c[21]) + (__x__.m_c[123] * __x__.m_c[16]) + (-1.0f * __x__.m_c[113] * __x__.m_c[1]));
			__x__.m_c[166] = ((__x__.m_c[123] * __x__.m_c[6]) + (-1.0f * __x__.m_c[33] * __x__.m_c[21]) + (-1.0f * __x__.m_c[93] * __x__.m_c[1]));
			__x__.m_c[176] = ((-1.0f * __x__.m_c[43] * __x__.m_c[21]) + (-1.0f * __x__.m_c[103] * __x__.m_c[1]) + (__x__.m_c[123] * __x__.m_c[11]));
			__x__.m_c[186] = ((__x__.m_c[53] * __x__.m_c[11]) + (-1.0f * __x__.m_c[73] * __x__.m_c[1]) + (-1.0f * __x__.m_c[43] * __x__.m_c[16]));
			__x__.m_c[196] = ((__x__.m_c[83] * __x__.m_c[1]) + (-1.0f * __x__.m_c[33] * __x__.m_c[16]) + (__x__.m_c[53] * __x__.m_c[6]));
			__x__.m_c[206] = ((-1.0f * __x__.m_c[63] * __x__.m_c[1]) + (-1.0f * __x__.m_c[33] * __x__.m_c[11]) + (__x__.m_c[43] * __x__.m_c[6]));
			__x__.m_c[216] = ((-1.0f * __x__.m_c[83] * __x__.m_c[11]) + (-1.0f * __x__.m_c[63] * __x__.m_c[16]) + (-1.0f * __x__.m_c[73] * __x__.m_c[6]));
			__x__.m_c[127] = ((__x__.m_c[112] * __x__.m_c[11]) + (-1.0f * __x__.m_c[102] * __x__.m_c[16]) + (__x__.m_c[72] * __x__.m_c[21]));
			__x__.m_c[137] = ((-1.0f * __x__.m_c[112] * __x__.m_c[6]) + (__x__.m_c[82] * __x__.m_c[21]) + (__x__.m_c[92] * __x__.m_c[16]));
			__x__.m_c[147] = ((__x__.m_c[62] * __x__.m_c[21]) + (__x__.m_c[102] * __x__.m_c[6]) + (-1.0f * __x__.m_c[92] * __x__.m_c[11]));
			__x__.m_c[157] = ((__x__.m_c[52] * __x__.m_c[21]) + (-1.0f * __x__.m_c[122] * __x__.m_c[16]) + (__x__.m_c[112] * __x__.m_c[1]));
			__x__.m_c[167] = ((-1.0f * __x__.m_c[122] * __x__.m_c[6]) + (__x__.m_c[92] * __x__.m_c[1]) + (__x__.m_c[32] * __x__.m_c[21]));
			__x__.m_c[177] = ((__x__.m_c[102] * __x__.m_c[1]) + (-1.0f * __x__.m_c[122] * __x__.m_c[11]) + (__x__.m_c[42] * __x__.m_c[21]));
			__x__.m_c[187] = ((-1.0f * __x__.m_c[52] * __x__.m_c[11]) + (__x__.m_c[42] * __x__.m_c[16]) + (__x__.m_c[72] * __x__.m_c[1]));
			__x__.m_c[197] = ((__x__.m_c[32] * __x__.m_c[16]) + (-1.0f * __x__.m_c[82] * __x__.m_c[1]) + (-1.0f * __x__.m_c[52] * __x__.m_c[6]));
			__x__.m_c[207] = ((-1.0f * __x__.m_c[42] * __x__.m_c[6]) + (__x__.m_c[32] * __x__.m_c[11]) + (__x__.m_c[62] * __x__.m_c[1]));
			__x__.m_c[217] = ((__x__.m_c[82] * __x__.m_c[11]) + (__x__.m_c[62] * __x__.m_c[16]) + (__x__.m_c[72] * __x__.m_c[6]));
			__x__.m_c[128] = ((__x__.m_c[104] * __x__.m_c[18]) + (-1.0f * __x__.m_c[114] * __x__.m_c[13]) + (-1.0f * __x__.m_c[74] * __x__.m_c[23]));
			__x__.m_c[138] = ((-1.0f * __x__.m_c[84] * __x__.m_c[23]) + (-1.0f * __x__.m_c[94] * __x__.m_c[18]) + (__x__.m_c[114] * __x__.m_c[8]));
			__x__.m_c[148] = ((-1.0f * __x__.m_c[104] * __x__.m_c[8]) + (-1.0f * __x__.m_c[64] * __x__.m_c[23]) + (__x__.m_c[94] * __x__.m_c[13]));
			__x__.m_c[158] = ((-1.0f * __x__.m_c[54] * __x__.m_c[23]) + (__x__.m_c[124] * __x__.m_c[18]) + (-1.0f * __x__.m_c[114] * __x__.m_c[3]));
			__x__.m_c[168] = ((-1.0f * __x__.m_c[34] * __x__.m_c[23]) + (__x__.m_c[124] * __x__.m_c[8]) + (-1.0f * __x__.m_c[94] * __x__.m_c[3]));
			__x__.m_c[178] = ((-1.0f * __x__.m_c[104] * __x__.m_c[3]) + (-1.0f * __x__.m_c[44] * __x__.m_c[23]) + (__x__.m_c[124] * __x__.m_c[13]));
			__x__.m_c[188] = ((-1.0f * __x__.m_c[44] * __x__.m_c[18]) + (-1.0f * __x__.m_c[74] * __x__.m_c[3]) + (__x__.m_c[54] * __x__.m_c[13]));
			__x__.m_c[198] = ((-1.0f * __x__.m_c[34] * __x__.m_c[18]) + (__x__.m_c[84] * __x__.m_c[3]) + (__x__.m_c[54] * __x__.m_c[8]));
			__x__.m_c[208] = ((-1.0f * __x__.m_c[34] * __x__.m_c[13]) + (__x__.m_c[44] * __x__.m_c[8]) + (-1.0f * __x__.m_c[64] * __x__.m_c[3]));
			__x__.m_c[218] = ((-1.0f * __x__.m_c[84] * __x__.m_c[13]) + (-1.0f * __x__.m_c[74] * __x__.m_c[8]) + (-1.0f * __x__.m_c[64] * __x__.m_c[18]));
			__x__.m_c[129] = ((__x__.m_c[104] * __x__.m_c[16]) + (-1.0f * __x__.m_c[74] * __x__.m_c[21]) + (-1.0f * __x__.m_c[114] * __x__.m_c[11]));
			__x__.m_c[139] = ((__x__.m_c[114] * __x__.m_c[6]) + (-1.0f * __x__.m_c[94] * __x__.m_c[16]) + (-1.0f * __x__.m_c[84] * __x__.m_c[21]));
			__x__.m_c[149] = ((-1.0f * __x__.m_c[104] * __x__.m_c[6]) + (__x__.m_c[94] * __x__.m_c[11]) + (-1.0f * __x__.m_c[64] * __x__.m_c[21]));
			__x__.m_c[159] = ((-1.0f * __x__.m_c[114] * __x__.m_c[1]) + (-1.0f * __x__.m_c[54] * __x__.m_c[21]) + (__x__.m_c[124] * __x__.m_c[16]));
			__x__.m_c[169] = ((__x__.m_c[124] * __x__.m_c[6]) + (-1.0f * __x__.m_c[34] * __x__.m_c[21]) + (-1.0f * __x__.m_c[94] * __x__.m_c[1]));
			__x__.m_c[179] = ((-1.0f * __x__.m_c[44] * __x__.m_c[21]) + (-1.0f * __x__.m_c[104] * __x__.m_c[1]) + (__x__.m_c[124] * __x__.m_c[11]));
			__x__.m_c[189] = ((-1.0f * __x__.m_c[74] * __x__.m_c[1]) + (-1.0f * __x__.m_c[44] * __x__.m_c[16]) + (__x__.m_c[54] * __x__.m_c[11]));
			__x__.m_c[199] = ((-1.0f * __x__.m_c[34] * __x__.m_c[16]) + (__x__.m_c[84] * __x__.m_c[1]) + (__x__.m_c[54] * __x__.m_c[6]));
			__x__.m_c[209] = ((-1.0f * __x__.m_c[64] * __x__.m_c[1]) + (-1.0f * __x__.m_c[34] * __x__.m_c[11]) + (__x__.m_c[44] * __x__.m_c[6]));
			__x__.m_c[219] = ((-1.0f * __x__.m_c[74] * __x__.m_c[6]) + (-1.0f * __x__.m_c[84] * __x__.m_c[11]) + (-1.0f * __x__.m_c[64] * __x__.m_c[16]));
			__x__.m_c[130] = ((-1.0f * __x__.m_c[74] * __x__.m_c[22]) + (-1.0f * __x__.m_c[114] * __x__.m_c[12]) + (__x__.m_c[104] * __x__.m_c[17]));
			__x__.m_c[140] = ((__x__.m_c[114] * __x__.m_c[7]) + (-1.0f * __x__.m_c[84] * __x__.m_c[22]) + (-1.0f * __x__.m_c[94] * __x__.m_c[17]));
			__x__.m_c[150] = ((-1.0f * __x__.m_c[64] * __x__.m_c[22]) + (__x__.m_c[94] * __x__.m_c[12]) + (-1.0f * __x__.m_c[104] * __x__.m_c[7]));
			__x__.m_c[160] = ((-1.0f * __x__.m_c[114] * __x__.m_c[2]) + (-1.0f * __x__.m_c[54] * __x__.m_c[22]) + (__x__.m_c[124] * __x__.m_c[17]));
			__x__.m_c[170] = ((-1.0f * __x__.m_c[94] * __x__.m_c[2]) + (-1.0f * __x__.m_c[34] * __x__.m_c[22]) + (__x__.m_c[124] * __x__.m_c[7]));
			__x__.m_c[180] = ((-1.0f * __x__.m_c[44] * __x__.m_c[22]) + (-1.0f * __x__.m_c[104] * __x__.m_c[2]) + (__x__.m_c[124] * __x__.m_c[12]));
			__x__.m_c[190] = ((__x__.m_c[54] * __x__.m_c[12]) + (-1.0f * __x__.m_c[44] * __x__.m_c[17]) + (-1.0f * __x__.m_c[74] * __x__.m_c[2]));
			__x__.m_c[200] = ((-1.0f * __x__.m_c[34] * __x__.m_c[17]) + (__x__.m_c[84] * __x__.m_c[2]) + (__x__.m_c[54] * __x__.m_c[7]));
			__x__.m_c[210] = ((-1.0f * __x__.m_c[64] * __x__.m_c[2]) + (-1.0f * __x__.m_c[34] * __x__.m_c[12]) + (__x__.m_c[44] * __x__.m_c[7]));
			__x__.m_c[220] = ((-1.0f * __x__.m_c[84] * __x__.m_c[12]) + (-1.0f * __x__.m_c[64] * __x__.m_c[17]) + (-1.0f * __x__.m_c[74] * __x__.m_c[7]));
			__x__.m_c[131] = ((__x__.m_c[109] * __x__.m_c[10]) + (-1.0f * __x__.m_c[99] * __x__.m_c[15]) + (__x__.m_c[69] * __x__.m_c[20]));
			__x__.m_c[141] = ((__x__.m_c[89] * __x__.m_c[15]) + (-1.0f * __x__.m_c[109] * __x__.m_c[5]) + (__x__.m_c[79] * __x__.m_c[20]));
			__x__.m_c[151] = ((-1.0f * __x__.m_c[89] * __x__.m_c[10]) + (__x__.m_c[59] * __x__.m_c[20]) + (__x__.m_c[99] * __x__.m_c[5]));
			__x__.m_c[161] = ((-1.0f * __x__.m_c[119] * __x__.m_c[15]) + (__x__.m_c[109] * __x__.m_c[0]) + (__x__.m_c[49] * __x__.m_c[20]));
			__x__.m_c[171] = ((__x__.m_c[29] * __x__.m_c[20]) + (__x__.m_c[89] * __x__.m_c[0]) + (-1.0f * __x__.m_c[119] * __x__.m_c[5]));
			__x__.m_c[181] = ((__x__.m_c[99] * __x__.m_c[0]) + (-1.0f * __x__.m_c[119] * __x__.m_c[10]) + (__x__.m_c[39] * __x__.m_c[20]));
			__x__.m_c[191] = ((__x__.m_c[39] * __x__.m_c[15]) + (-1.0f * __x__.m_c[49] * __x__.m_c[10]) + (__x__.m_c[69] * __x__.m_c[0]));
			__x__.m_c[201] = ((-1.0f * __x__.m_c[49] * __x__.m_c[5]) + (-1.0f * __x__.m_c[79] * __x__.m_c[0]) + (__x__.m_c[29] * __x__.m_c[15]));
			__x__.m_c[211] = ((-1.0f * __x__.m_c[39] * __x__.m_c[5]) + (__x__.m_c[29] * __x__.m_c[10]) + (__x__.m_c[59] * __x__.m_c[0]));
			__x__.m_c[221] = ((__x__.m_c[79] * __x__.m_c[10]) + (__x__.m_c[59] * __x__.m_c[15]) + (__x__.m_c[69] * __x__.m_c[5]));
			__x__.m_c[132] = ((__x__.m_c[100] * __x__.m_c[15]) + (-1.0f * __x__.m_c[110] * __x__.m_c[10]) + (-1.0f * __x__.m_c[70] * __x__.m_c[20]));
			__x__.m_c[142] = ((-1.0f * __x__.m_c[90] * __x__.m_c[15]) + (__x__.m_c[110] * __x__.m_c[5]) + (-1.0f * __x__.m_c[80] * __x__.m_c[20]));
			__x__.m_c[152] = ((-1.0f * __x__.m_c[100] * __x__.m_c[5]) + (-1.0f * __x__.m_c[60] * __x__.m_c[20]) + (__x__.m_c[90] * __x__.m_c[10]));
			__x__.m_c[162] = ((-1.0f * __x__.m_c[50] * __x__.m_c[20]) + (__x__.m_c[120] * __x__.m_c[15]) + (-1.0f * __x__.m_c[110] * __x__.m_c[0]));
			__x__.m_c[172] = ((__x__.m_c[120] * __x__.m_c[5]) + (-1.0f * __x__.m_c[30] * __x__.m_c[20]) + (-1.0f * __x__.m_c[90] * __x__.m_c[0]));
			__x__.m_c[182] = ((__x__.m_c[120] * __x__.m_c[10]) + (-1.0f * __x__.m_c[40] * __x__.m_c[20]) + (-1.0f * __x__.m_c[100] * __x__.m_c[0]));
			__x__.m_c[192] = ((__x__.m_c[50] * __x__.m_c[10]) + (-1.0f * __x__.m_c[70] * __x__.m_c[0]) + (-1.0f * __x__.m_c[40] * __x__.m_c[15]));
			__x__.m_c[202] = ((-1.0f * __x__.m_c[30] * __x__.m_c[15]) + (__x__.m_c[80] * __x__.m_c[0]) + (__x__.m_c[50] * __x__.m_c[5]));
			__x__.m_c[212] = ((__x__.m_c[40] * __x__.m_c[5]) + (-1.0f * __x__.m_c[60] * __x__.m_c[0]) + (-1.0f * __x__.m_c[30] * __x__.m_c[10]));
			__x__.m_c[222] = ((-1.0f * __x__.m_c[70] * __x__.m_c[5]) + (-1.0f * __x__.m_c[80] * __x__.m_c[10]) + (-1.0f * __x__.m_c[60] * __x__.m_c[15]));
			__x__.m_c[133] = ((__x__.m_c[68] * __x__.m_c[20]) + (__x__.m_c[108] * __x__.m_c[10]) + (-1.0f * __x__.m_c[98] * __x__.m_c[15]));
			__x__.m_c[143] = ((-1.0f * __x__.m_c[108] * __x__.m_c[5]) + (__x__.m_c[88] * __x__.m_c[15]) + (__x__.m_c[78] * __x__.m_c[20]));
			__x__.m_c[153] = ((-1.0f * __x__.m_c[88] * __x__.m_c[10]) + (__x__.m_c[58] * __x__.m_c[20]) + (__x__.m_c[98] * __x__.m_c[5]));
			__x__.m_c[163] = ((__x__.m_c[48] * __x__.m_c[20]) + (-1.0f * __x__.m_c[118] * __x__.m_c[15]) + (__x__.m_c[108] * __x__.m_c[0]));
			__x__.m_c[173] = ((__x__.m_c[28] * __x__.m_c[20]) + (-1.0f * __x__.m_c[118] * __x__.m_c[5]) + (__x__.m_c[88] * __x__.m_c[0]));
			__x__.m_c[183] = ((-1.0f * __x__.m_c[118] * __x__.m_c[10]) + (__x__.m_c[38] * __x__.m_c[20]) + (__x__.m_c[98] * __x__.m_c[0]));
			__x__.m_c[193] = ((-1.0f * __x__.m_c[48] * __x__.m_c[10]) + (__x__.m_c[68] * __x__.m_c[0]) + (__x__.m_c[38] * __x__.m_c[15]));
			__x__.m_c[203] = ((__x__.m_c[28] * __x__.m_c[15]) + (-1.0f * __x__.m_c[48] * __x__.m_c[5]) + (-1.0f * __x__.m_c[78] * __x__.m_c[0]));
			__x__.m_c[213] = ((-1.0f * __x__.m_c[38] * __x__.m_c[5]) + (__x__.m_c[58] * __x__.m_c[0]) + (__x__.m_c[28] * __x__.m_c[10]));
			__x__.m_c[223] = ((__x__.m_c[78] * __x__.m_c[10]) + (__x__.m_c[58] * __x__.m_c[15]) + (__x__.m_c[68] * __x__.m_c[5]));
			__x__.m_c[134] = ((-1.0f * __x__.m_c[100] * __x__.m_c[17]) + (__x__.m_c[110] * __x__.m_c[12]) + (__x__.m_c[70] * __x__.m_c[22]));
			__x__.m_c[144] = ((__x__.m_c[80] * __x__.m_c[22]) + (-1.0f * __x__.m_c[110] * __x__.m_c[7]) + (__x__.m_c[90] * __x__.m_c[17]));
			__x__.m_c[154] = ((-1.0f * __x__.m_c[90] * __x__.m_c[12]) + (__x__.m_c[100] * __x__.m_c[7]) + (__x__.m_c[60] * __x__.m_c[22]));
			__x__.m_c[164] = ((-1.0f * __x__.m_c[120] * __x__.m_c[17]) + (__x__.m_c[50] * __x__.m_c[22]) + (__x__.m_c[110] * __x__.m_c[2]));
			__x__.m_c[174] = ((-1.0f * __x__.m_c[120] * __x__.m_c[7]) + (__x__.m_c[90] * __x__.m_c[2]) + (__x__.m_c[30] * __x__.m_c[22]));
			__x__.m_c[184] = ((__x__.m_c[40] * __x__.m_c[22]) + (-1.0f * __x__.m_c[120] * __x__.m_c[12]) + (__x__.m_c[100] * __x__.m_c[2]));
			__x__.m_c[194] = ((-1.0f * __x__.m_c[50] * __x__.m_c[12]) + (__x__.m_c[40] * __x__.m_c[17]) + (__x__.m_c[70] * __x__.m_c[2]));
			__x__.m_c[204] = ((__x__.m_c[30] * __x__.m_c[17]) + (-1.0f * __x__.m_c[50] * __x__.m_c[7]) + (-1.0f * __x__.m_c[80] * __x__.m_c[2]));
			__x__.m_c[214] = ((__x__.m_c[30] * __x__.m_c[12]) + (__x__.m_c[60] * __x__.m_c[2]) + (-1.0f * __x__.m_c[40] * __x__.m_c[7]));
			__x__.m_c[224] = ((__x__.m_c[80] * __x__.m_c[12]) + (__x__.m_c[70] * __x__.m_c[7]) + (__x__.m_c[60] * __x__.m_c[17]));
			__x__.m_c[225] = ((-1.0f * __x__.m_c[154] * __x__.m_c[19]) + (__x__.m_c[224] * __x__.m_c[24]) + (-1.0f * __x__.m_c[134] * __x__.m_c[9]) + (-1.0f * __x__.m_c[144] * __x__.m_c[14]));
			__x__.m_c[230] = ((-1.0f * __x__.m_c[184] * __x__.m_c[19]) + (-1.0f * __x__.m_c[134] * __x__.m_c[4]) + (__x__.m_c[164] * __x__.m_c[14]) + (__x__.m_c[194] * __x__.m_c[24]));
			__x__.m_c[235] = ((__x__.m_c[164] * __x__.m_c[9]) + (__x__.m_c[144] * __x__.m_c[4]) + (__x__.m_c[204] * __x__.m_c[24]) + (-1.0f * __x__.m_c[174] * __x__.m_c[19]));
			__x__.m_c[240] = ((__x__.m_c[184] * __x__.m_c[9]) + (__x__.m_c[214] * __x__.m_c[24]) + (-1.0f * __x__.m_c[154] * __x__.m_c[4]) + (-1.0f * __x__.m_c[174] * __x__.m_c[14]));
			__x__.m_c[245] = ((__x__.m_c[214] * __x__.m_c[19]) + (-1.0f * __x__.m_c[224] * __x__.m_c[4]) + (-1.0f * __x__.m_c[204] * __x__.m_c[14]) + (__x__.m_c[194] * __x__.m_c[9]));
			__x__.m_c[226] = ((-1.0f * __x__.m_c[131] * __x__.m_c[9]) + (__x__.m_c[221] * __x__.m_c[24]) + (-1.0f * __x__.m_c[141] * __x__.m_c[14]) + (-1.0f * __x__.m_c[151] * __x__.m_c[19]));
			__x__.m_c[231] = ((-1.0f * __x__.m_c[131] * __x__.m_c[4]) + (__x__.m_c[161] * __x__.m_c[14]) + (-1.0f * __x__.m_c[181] * __x__.m_c[19]) + (__x__.m_c[191] * __x__.m_c[24]));
			__x__.m_c[236] = ((__x__.m_c[141] * __x__.m_c[4]) + (__x__.m_c[201] * __x__.m_c[24]) + (-1.0f * __x__.m_c[171] * __x__.m_c[19]) + (__x__.m_c[161] * __x__.m_c[9]));
			__x__.m_c[241] = ((-1.0f * __x__.m_c[171] * __x__.m_c[14]) + (__x__.m_c[181] * __x__.m_c[9]) + (__x__.m_c[211] * __x__.m_c[24]) + (-1.0f * __x__.m_c[151] * __x__.m_c[4]));
			__x__.m_c[246] = ((-1.0f * __x__.m_c[221] * __x__.m_c[4]) + (-1.0f * __x__.m_c[201] * __x__.m_c[14]) + (__x__.m_c[191] * __x__.m_c[9]) + (__x__.m_c[211] * __x__.m_c[19]));
			__x__.m_c[227] = ((__x__.m_c[222] * __x__.m_c[24]) + (-1.0f * __x__.m_c[142] * __x__.m_c[14]) + (-1.0f * __x__.m_c[152] * __x__.m_c[19]) + (-1.0f * __x__.m_c[132] * __x__.m_c[9]));
			__x__.m_c[232] = ((__x__.m_c[162] * __x__.m_c[14]) + (-1.0f * __x__.m_c[132] * __x__.m_c[4]) + (-1.0f * __x__.m_c[182] * __x__.m_c[19]) + (__x__.m_c[192] * __x__.m_c[24]));
			__x__.m_c[237] = ((-1.0f * __x__.m_c[172] * __x__.m_c[19]) + (__x__.m_c[162] * __x__.m_c[9]) + (__x__.m_c[202] * __x__.m_c[24]) + (__x__.m_c[142] * __x__.m_c[4]));
			__x__.m_c[242] = ((-1.0f * __x__.m_c[172] * __x__.m_c[14]) + (__x__.m_c[212] * __x__.m_c[24]) + (-1.0f * __x__.m_c[152] * __x__.m_c[4]) + (__x__.m_c[182] * __x__.m_c[9]));
			__x__.m_c[247] = ((__x__.m_c[192] * __x__.m_c[9]) + (__x__.m_c[212] * __x__.m_c[19]) + (-1.0f * __x__.m_c[222] * __x__.m_c[4]) + (-1.0f * __x__.m_c[202] * __x__.m_c[14]));
			__x__.m_c[228] = ((__x__.m_c[223] * __x__.m_c[24]) + (-1.0f * __x__.m_c[153] * __x__.m_c[19]) + (-1.0f * __x__.m_c[143] * __x__.m_c[14]) + (-1.0f * __x__.m_c[133] * __x__.m_c[9]));
			__x__.m_c[233] = ((__x__.m_c[163] * __x__.m_c[14]) + (__x__.m_c[193] * __x__.m_c[24]) + (-1.0f * __x__.m_c[183] * __x__.m_c[19]) + (-1.0f * __x__.m_c[133] * __x__.m_c[4]));
			__x__.m_c[238] = ((__x__.m_c[143] * __x__.m_c[4]) + (-1.0f * __x__.m_c[173] * __x__.m_c[19]) + (__x__.m_c[163] * __x__.m_c[9]) + (__x__.m_c[203] * __x__.m_c[24]));
			__x__.m_c[243] = ((-1.0f * __x__.m_c[153] * __x__.m_c[4]) + (-1.0f * __x__.m_c[173] * __x__.m_c[14]) + (__x__.m_c[213] * __x__.m_c[24]) + (__x__.m_c[183] * __x__.m_c[9]));
			__x__.m_c[248] = ((-1.0f * __x__.m_c[203] * __x__.m_c[14]) + (-1.0f * __x__.m_c[223] * __x__.m_c[4]) + (__x__.m_c[213] * __x__.m_c[19]) + (__x__.m_c[193] * __x__.m_c[9]));
			__x__.m_c[229] = ((__x__.m_c[134] * __x__.m_c[5]) + (-1.0f * __x__.m_c[224] * __x__.m_c[20]) + (__x__.m_c[154] * __x__.m_c[15]) + (__x__.m_c[144] * __x__.m_c[10]));
			__x__.m_c[234] = ((-1.0f * __x__.m_c[164] * __x__.m_c[10]) + (__x__.m_c[184] * __x__.m_c[15]) + (-1.0f * __x__.m_c[194] * __x__.m_c[20]) + (__x__.m_c[134] * __x__.m_c[0]));
			__x__.m_c[239] = ((-1.0f * __x__.m_c[204] * __x__.m_c[20]) + (-1.0f * __x__.m_c[164] * __x__.m_c[5]) + (-1.0f * __x__.m_c[144] * __x__.m_c[0]) + (__x__.m_c[174] * __x__.m_c[15]));
			__x__.m_c[244] = ((__x__.m_c[174] * __x__.m_c[10]) + (-1.0f * __x__.m_c[184] * __x__.m_c[5]) + (__x__.m_c[154] * __x__.m_c[0]) + (-1.0f * __x__.m_c[214] * __x__.m_c[20]));
			__x__.m_c[249] = ((__x__.m_c[204] * __x__.m_c[10]) + (__x__.m_c[224] * __x__.m_c[0]) + (-1.0f * __x__.m_c[214] * __x__.m_c[15]) + (-1.0f * __x__.m_c[194] * __x__.m_c[5]));
			__x__.m_c[250] = ((-1.0f * __x__.m_c[244] * __x__.m_c[19]) + (-1.0f * __x__.m_c[234] * __x__.m_c[9]) + (__x__.m_c[249] * __x__.m_c[24]) + (__x__.m_c[229] * __x__.m_c[4]) + (__x__.m_c[239] * __x__.m_c[14]));
		}
		void set(om& __x__, const omFlatPoint& __y__) {
			__x__.m_c[0] = (char)0;
			__x__.m_c[5] = (char)0;
			__x__.m_c[10] = (char)0;
			__x__.m_c[15] = (char)0;
			__x__.m_c[20] = (char)0;
			__x__.m_c[1] = (char)0;
			__x__.m_c[6] = (char)0;
			__x__.m_c[11] = (char)0;
			__x__.m_c[16] = (char)0;
			__x__.m_c[21] = (char)0;
			__x__.m_c[2] = (char)0;
			__x__.m_c[7] = (char)0;
			__x__.m_c[12] = (char)0;
			__x__.m_c[17] = (char)0;
			__x__.m_c[22] = (char)0;
			__x__.m_c[3] = (char)0;
			__x__.m_c[8] = (char)0;
			__x__.m_c[13] = (char)0;
			__x__.m_c[18] = (char)0;
			__x__.m_c[23] = (char)0;
			__x__.m_c[4] = (char)0;
			__x__.m_c[9] = (char)0;
			__x__.m_c[14] = (char)0;
			__x__.m_c[19] = (char)0;
			__x__.m_c[24] = (char)0;
			__x__.m_c[25] = ((__x__.m_c[6] * __x__.m_c[0]) + (-1.0f * __x__.m_c[1] * __x__.m_c[5]));
			__x__.m_c[35] = ((-1.0f * __x__.m_c[1] * __x__.m_c[10]) + (__x__.m_c[11] * __x__.m_c[0]));
			__x__.m_c[45] = ((__x__.m_c[16] * __x__.m_c[0]) + (-1.0f * __x__.m_c[1] * __x__.m_c[15]));
			__x__.m_c[55] = ((__x__.m_c[11] * __x__.m_c[5]) + (-1.0f * __x__.m_c[6] * __x__.m_c[10]));
			__x__.m_c[65] = ((-1.0f * __x__.m_c[11] * __x__.m_c[15]) + (__x__.m_c[16] * __x__.m_c[10]));
			__x__.m_c[75] = ((__x__.m_c[6] * __x__.m_c[15]) + (-1.0f * __x__.m_c[16] * __x__.m_c[5]));
			__x__.m_c[85] = ((-1.0f * __x__.m_c[6] * __x__.m_c[20]) + (__x__.m_c[21] * __x__.m_c[5]));
			__x__.m_c[95] = ((__x__.m_c[21] * __x__.m_c[10]) + (-1.0f * __x__.m_c[11] * __x__.m_c[20]));
			__x__.m_c[105] = ((__x__.m_c[21] * __x__.m_c[15]) + (-1.0f * __x__.m_c[16] * __x__.m_c[20]));
			__x__.m_c[115] = ((-1.0f * __x__.m_c[1] * __x__.m_c[20]) + (__x__.m_c[21] * __x__.m_c[0]));
			__x__.m_c[26] = ((__x__.m_c[7] * __x__.m_c[0]) + (-1.0f * __x__.m_c[2] * __x__.m_c[5]));
			__x__.m_c[36] = ((-1.0f * __x__.m_c[2] * __x__.m_c[10]) + (__x__.m_c[12] * __x__.m_c[0]));
			__x__.m_c[46] = ((-1.0f * __x__.m_c[2] * __x__.m_c[15]) + (__x__.m_c[17] * __x__.m_c[0]));
			__x__.m_c[56] = ((__x__.m_c[12] * __x__.m_c[5]) + (-1.0f * __x__.m_c[7] * __x__.m_c[10]));
			__x__.m_c[66] = ((__x__.m_c[17] * __x__.m_c[10]) + (-1.0f * __x__.m_c[12] * __x__.m_c[15]));
			__x__.m_c[76] = ((__x__.m_c[7] * __x__.m_c[15]) + (-1.0f * __x__.m_c[17] * __x__.m_c[5]));
			__x__.m_c[86] = ((__x__.m_c[22] * __x__.m_c[5]) + (-1.0f * __x__.m_c[7] * __x__.m_c[20]));
			__x__.m_c[96] = ((__x__.m_c[22] * __x__.m_c[10]) + (-1.0f * __x__.m_c[12] * __x__.m_c[20]));
			__x__.m_c[106] = ((-1.0f * __x__.m_c[17] * __x__.m_c[20]) + (__x__.m_c[22] * __x__.m_c[15]));
			__x__.m_c[116] = ((__x__.m_c[22] * __x__.m_c[0]) + (-1.0f * __x__.m_c[2] * __x__.m_c[20]));
			__x__.m_c[27] = ((-1.0f * __x__.m_c[3] * __x__.m_c[5]) + (__x__.m_c[8] * __x__.m_c[0]));
			__x__.m_c[37] = ((__x__.m_c[13] * __x__.m_c[0]) + (-1.0f * __x__.m_c[3] * __x__.m_c[10]));
			__x__.m_c[47] = ((-1.0f * __x__.m_c[3] * __x__.m_c[15]) + (__x__.m_c[18] * __x__.m_c[0]));
			__x__.m_c[57] = ((-1.0f * __x__.m_c[8] * __x__.m_c[10]) + (__x__.m_c[13] * __x__.m_c[5]));
			__x__.m_c[67] = ((__x__.m_c[18] * __x__.m_c[10]) + (-1.0f * __x__.m_c[13] * __x__.m_c[15]));
			__x__.m_c[77] = ((-1.0f * __x__.m_c[18] * __x__.m_c[5]) + (__x__.m_c[8] * __x__.m_c[15]));
			__x__.m_c[87] = ((__x__.m_c[23] * __x__.m_c[5]) + (-1.0f * __x__.m_c[8] * __x__.m_c[20]));
			__x__.m_c[97] = ((__x__.m_c[23] * __x__.m_c[10]) + (-1.0f * __x__.m_c[13] * __x__.m_c[20]));
			__x__.m_c[107] = ((-1.0f * __x__.m_c[18] * __x__.m_c[20]) + (__x__.m_c[23] * __x__.m_c[15]));
			__x__.m_c[117] = ((-1.0f * __x__.m_c[3] * __x__.m_c[20]) + (__x__.m_c[23] * __x__.m_c[0]));
			__x__.m_c[28] = ((__x__.m_c[7] * __x__.m_c[1]) + (-1.0f * __x__.m_c[2] * __x__.m_c[6]));
			__x__.m_c[38] = ((-1.0f * __x__.m_c[2] * __x__.m_c[11]) + (__x__.m_c[12] * __x__.m_c[1]));
			__x__.m_c[48] = ((-1.0f * __x__.m_c[2] * __x__.m_c[16]) + (__x__.m_c[17] * __x__.m_c[1]));
			__x__.m_c[58] = ((__x__.m_c[12] * __x__.m_c[6]) + (-1.0f * __x__.m_c[7] * __x__.m_c[11]));
			__x__.m_c[68] = ((__x__.m_c[17] * __x__.m_c[11]) + (-1.0f * __x__.m_c[12] * __x__.m_c[16]));
			__x__.m_c[78] = ((__x__.m_c[7] * __x__.m_c[16]) + (-1.0f * __x__.m_c[17] * __x__.m_c[6]));
			__x__.m_c[88] = ((-1.0f * __x__.m_c[7] * __x__.m_c[21]) + (__x__.m_c[22] * __x__.m_c[6]));
			__x__.m_c[98] = ((-1.0f * __x__.m_c[12] * __x__.m_c[21]) + (__x__.m_c[22] * __x__.m_c[11]));
			__x__.m_c[108] = ((__x__.m_c[22] * __x__.m_c[16]) + (-1.0f * __x__.m_c[17] * __x__.m_c[21]));
			__x__.m_c[118] = ((-1.0f * __x__.m_c[2] * __x__.m_c[21]) + (__x__.m_c[22] * __x__.m_c[1]));
			__x__.m_c[29] = ((__x__.m_c[8] * __x__.m_c[2]) + (-1.0f * __x__.m_c[3] * __x__.m_c[7]));
			__x__.m_c[39] = ((-1.0f * __x__.m_c[3] * __x__.m_c[12]) + (__x__.m_c[13] * __x__.m_c[2]));
			__x__.m_c[49] = ((__x__.m_c[18] * __x__.m_c[2]) + (-1.0f * __x__.m_c[3] * __x__.m_c[17]));
			__x__.m_c[59] = ((-1.0f * __x__.m_c[8] * __x__.m_c[12]) + (__x__.m_c[13] * __x__.m_c[7]));
			__x__.m_c[69] = ((-1.0f * __x__.m_c[13] * __x__.m_c[17]) + (__x__.m_c[18] * __x__.m_c[12]));
			__x__.m_c[79] = ((-1.0f * __x__.m_c[18] * __x__.m_c[7]) + (__x__.m_c[8] * __x__.m_c[17]));
			__x__.m_c[89] = ((-1.0f * __x__.m_c[8] * __x__.m_c[22]) + (__x__.m_c[23] * __x__.m_c[7]));
			__x__.m_c[99] = ((-1.0f * __x__.m_c[13] * __x__.m_c[22]) + (__x__.m_c[23] * __x__.m_c[12]));
			__x__.m_c[109] = ((-1.0f * __x__.m_c[18] * __x__.m_c[22]) + (__x__.m_c[23] * __x__.m_c[17]));
			__x__.m_c[119] = ((-1.0f * __x__.m_c[3] * __x__.m_c[22]) + (__x__.m_c[23] * __x__.m_c[2]));
			__x__.m_c[30] = ((__x__.m_c[3] * __x__.m_c[6]) + (-1.0f * __x__.m_c[8] * __x__.m_c[1]));
			__x__.m_c[40] = ((__x__.m_c[3] * __x__.m_c[11]) + (-1.0f * __x__.m_c[13] * __x__.m_c[1]));
			__x__.m_c[50] = ((__x__.m_c[3] * __x__.m_c[16]) + (-1.0f * __x__.m_c[18] * __x__.m_c[1]));
			__x__.m_c[60] = ((-1.0f * __x__.m_c[13] * __x__.m_c[6]) + (__x__.m_c[8] * __x__.m_c[11]));
			__x__.m_c[70] = ((-1.0f * __x__.m_c[18] * __x__.m_c[11]) + (__x__.m_c[13] * __x__.m_c[16]));
			__x__.m_c[80] = ((__x__.m_c[18] * __x__.m_c[6]) + (-1.0f * __x__.m_c[8] * __x__.m_c[16]));
			__x__.m_c[90] = ((__x__.m_c[8] * __x__.m_c[21]) + (-1.0f * __x__.m_c[23] * __x__.m_c[6]));
			__x__.m_c[100] = ((-1.0f * __x__.m_c[23] * __x__.m_c[11]) + (__x__.m_c[13] * __x__.m_c[21]));
			__x__.m_c[110] = ((-1.0f * __x__.m_c[23] * __x__.m_c[16]) + (__x__.m_c[18] * __x__.m_c[21]));
			__x__.m_c[120] = ((__x__.m_c[3] * __x__.m_c[21]) + (-1.0f * __x__.m_c[23] * __x__.m_c[1]));
			__x__.m_c[31] = ((__x__.m_c[9] * __x__.m_c[1]) + (-1.0f * __x__.m_c[4] * __x__.m_c[6]));
			__x__.m_c[41] = ((__x__.m_c[14] * __x__.m_c[1]) + (-1.0f * __x__.m_c[4] * __x__.m_c[11]));
			__x__.m_c[51] = ((-1.0f * __x__.m_c[4] * __x__.m_c[16]) + (__x__.m_c[19] * __x__.m_c[1]));
			__x__.m_c[61] = ((__x__.m_c[14] * __x__.m_c[6]) + (-1.0f * __x__.m_c[9] * __x__.m_c[11]));
			__x__.m_c[71] = ((-1.0f * __x__.m_c[14] * __x__.m_c[16]) + (__x__.m_c[19] * __x__.m_c[11]));
			__x__.m_c[81] = ((__x__.m_c[9] * __x__.m_c[16]) + (-1.0f * __x__.m_c[19] * __x__.m_c[6]));
			__x__.m_c[91] = ((__x__.m_c[24] * __x__.m_c[6]) + (-1.0f * __x__.m_c[9] * __x__.m_c[21]));
			__x__.m_c[101] = ((__x__.m_c[24] * __x__.m_c[11]) + (-1.0f * __x__.m_c[14] * __x__.m_c[21]));
			__x__.m_c[111] = ((__x__.m_c[24] * __x__.m_c[16]) + (-1.0f * __x__.m_c[19] * __x__.m_c[21]));
			__x__.m_c[121] = ((__x__.m_c[24] * __x__.m_c[1]) + (-1.0f * __x__.m_c[4] * __x__.m_c[21]));
			__x__.m_c[32] = ((__x__.m_c[9] * __x__.m_c[2]) + (-1.0f * __x__.m_c[4] * __x__.m_c[7]));
			__x__.m_c[42] = ((-1.0f * __x__.m_c[4] * __x__.m_c[12]) + (__x__.m_c[14] * __x__.m_c[2]));
			__x__.m_c[52] = ((__x__.m_c[19] * __x__.m_c[2]) + (-1.0f * __x__.m_c[4] * __x__.m_c[17]));
			__x__.m_c[62] = ((-1.0f * __x__.m_c[9] * __x__.m_c[12]) + (__x__.m_c[14] * __x__.m_c[7]));
			__x__.m_c[72] = ((-1.0f * __x__.m_c[14] * __x__.m_c[17]) + (__x__.m_c[19] * __x__.m_c[12]));
			__x__.m_c[82] = ((__x__.m_c[9] * __x__.m_c[17]) + (-1.0f * __x__.m_c[19] * __x__.m_c[7]));
			__x__.m_c[92] = ((-1.0f * __x__.m_c[9] * __x__.m_c[22]) + (__x__.m_c[24] * __x__.m_c[7]));
			__x__.m_c[102] = ((-1.0f * __x__.m_c[14] * __x__.m_c[22]) + (__x__.m_c[24] * __x__.m_c[12]));
			__x__.m_c[112] = ((__x__.m_c[24] * __x__.m_c[17]) + (-1.0f * __x__.m_c[19] * __x__.m_c[22]));
			__x__.m_c[122] = ((__x__.m_c[24] * __x__.m_c[2]) + (-1.0f * __x__.m_c[4] * __x__.m_c[22]));
			__x__.m_c[33] = ((-1.0f * __x__.m_c[4] * __x__.m_c[8]) + (__x__.m_c[9] * __x__.m_c[3]));
			__x__.m_c[43] = ((-1.0f * __x__.m_c[4] * __x__.m_c[13]) + (__x__.m_c[14] * __x__.m_c[3]));
			__x__.m_c[53] = ((__x__.m_c[19] * __x__.m_c[3]) + (-1.0f * __x__.m_c[4] * __x__.m_c[18]));
			__x__.m_c[63] = ((__x__.m_c[14] * __x__.m_c[8]) + (-1.0f * __x__.m_c[9] * __x__.m_c[13]));
			__x__.m_c[73] = ((-1.0f * __x__.m_c[14] * __x__.m_c[18]) + (__x__.m_c[19] * __x__.m_c[13]));
			__x__.m_c[83] = ((-1.0f * __x__.m_c[19] * __x__.m_c[8]) + (__x__.m_c[9] * __x__.m_c[18]));
			__x__.m_c[93] = ((__x__.m_c[24] * __x__.m_c[8]) + (-1.0f * __x__.m_c[9] * __x__.m_c[23]));
			__x__.m_c[103] = ((-1.0f * __x__.m_c[14] * __x__.m_c[23]) + (__x__.m_c[24] * __x__.m_c[13]));
			__x__.m_c[113] = ((__x__.m_c[24] * __x__.m_c[18]) + (-1.0f * __x__.m_c[19] * __x__.m_c[23]));
			__x__.m_c[123] = ((-1.0f * __x__.m_c[4] * __x__.m_c[23]) + (__x__.m_c[24] * __x__.m_c[3]));
			__x__.m_c[34] = ((__x__.m_c[9] * __x__.m_c[0]) + (-1.0f * __x__.m_c[4] * __x__.m_c[5]));
			__x__.m_c[44] = ((-1.0f * __x__.m_c[4] * __x__.m_c[10]) + (__x__.m_c[14] * __x__.m_c[0]));
			__x__.m_c[54] = ((-1.0f * __x__.m_c[4] * __x__.m_c[15]) + (__x__.m_c[19] * __x__.m_c[0]));
			__x__.m_c[64] = ((__x__.m_c[14] * __x__.m_c[5]) + (-1.0f * __x__.m_c[9] * __x__.m_c[10]));
			__x__.m_c[74] = ((__x__.m_c[19] * __x__.m_c[10]) + (-1.0f * __x__.m_c[14] * __x__.m_c[15]));
			__x__.m_c[84] = ((__x__.m_c[9] * __x__.m_c[15]) + (-1.0f * __x__.m_c[19] * __x__.m_c[5]));
			__x__.m_c[94] = ((-1.0f * __x__.m_c[9] * __x__.m_c[20]) + (__x__.m_c[24] * __x__.m_c[5]));
			__x__.m_c[104] = ((__x__.m_c[24] * __x__.m_c[10]) + (-1.0f * __x__.m_c[14] * __x__.m_c[20]));
			__x__.m_c[114] = ((__x__.m_c[24] * __x__.m_c[15]) + (-1.0f * __x__.m_c[19] * __x__.m_c[20]));
			__x__.m_c[124] = ((-1.0f * __x__.m_c[4] * __x__.m_c[20]) + (__x__.m_c[24] * __x__.m_c[0]));
			__x__.m_c[125] = ((__x__.m_c[113] * __x__.m_c[12]) + (-1.0f * __x__.m_c[103] * __x__.m_c[17]) + (__x__.m_c[73] * __x__.m_c[22]));
			__x__.m_c[135] = ((__x__.m_c[83] * __x__.m_c[22]) + (__x__.m_c[93] * __x__.m_c[17]) + (-1.0f * __x__.m_c[113] * __x__.m_c[7]));
			__x__.m_c[145] = ((__x__.m_c[103] * __x__.m_c[7]) + (__x__.m_c[63] * __x__.m_c[22]) + (-1.0f * __x__.m_c[93] * __x__.m_c[12]));
			__x__.m_c[155] = ((__x__.m_c[113] * __x__.m_c[2]) + (__x__.m_c[53] * __x__.m_c[22]) + (-1.0f * __x__.m_c[123] * __x__.m_c[17]));
			__x__.m_c[165] = ((__x__.m_c[93] * __x__.m_c[2]) + (-1.0f * __x__.m_c[123] * __x__.m_c[7]) + (__x__.m_c[33] * __x__.m_c[22]));
			__x__.m_c[175] = ((__x__.m_c[103] * __x__.m_c[2]) + (-1.0f * __x__.m_c[123] * __x__.m_c[12]) + (__x__.m_c[43] * __x__.m_c[22]));
			__x__.m_c[185] = ((-1.0f * __x__.m_c[53] * __x__.m_c[12]) + (__x__.m_c[43] * __x__.m_c[17]) + (__x__.m_c[73] * __x__.m_c[2]));
			__x__.m_c[195] = ((-1.0f * __x__.m_c[83] * __x__.m_c[2]) + (__x__.m_c[33] * __x__.m_c[17]) + (-1.0f * __x__.m_c[53] * __x__.m_c[7]));
			__x__.m_c[205] = ((__x__.m_c[33] * __x__.m_c[12]) + (-1.0f * __x__.m_c[43] * __x__.m_c[7]) + (__x__.m_c[63] * __x__.m_c[2]));
			__x__.m_c[215] = ((__x__.m_c[63] * __x__.m_c[17]) + (__x__.m_c[73] * __x__.m_c[7]) + (__x__.m_c[83] * __x__.m_c[12]));
			__x__.m_c[126] = ((-1.0f * __x__.m_c[113] * __x__.m_c[11]) + (-1.0f * __x__.m_c[73] * __x__.m_c[21]) + (__x__.m_c[103] * __x__.m_c[16]));
			__x__.m_c[136] = ((-1.0f * __x__.m_c[83] * __x__.m_c[21]) + (__x__.m_c[113] * __x__.m_c[6]) + (-1.0f * __x__.m_c[93] * __x__.m_c[16]));
			__x__.m_c[146] = ((-1.0f * __x__.m_c[63] * __x__.m_c[21]) + (__x__.m_c[93] * __x__.m_c[11]) + (-1.0f * __x__.m_c[103] * __x__.m_c[6]));
			__x__.m_c[156] = ((__x__.m_c[123] * __x__.m_c[16]) + (-1.0f * __x__.m_c[53] * __x__.m_c[21]) + (-1.0f * __x__.m_c[113] * __x__.m_c[1]));
			__x__.m_c[166] = ((__x__.m_c[123] * __x__.m_c[6]) + (-1.0f * __x__.m_c[33] * __x__.m_c[21]) + (-1.0f * __x__.m_c[93] * __x__.m_c[1]));
			__x__.m_c[176] = ((-1.0f * __x__.m_c[43] * __x__.m_c[21]) + (__x__.m_c[123] * __x__.m_c[11]) + (-1.0f * __x__.m_c[103] * __x__.m_c[1]));
			__x__.m_c[186] = ((-1.0f * __x__.m_c[73] * __x__.m_c[1]) + (-1.0f * __x__.m_c[43] * __x__.m_c[16]) + (__x__.m_c[53] * __x__.m_c[11]));
			__x__.m_c[196] = ((-1.0f * __x__.m_c[33] * __x__.m_c[16]) + (__x__.m_c[53] * __x__.m_c[6]) + (__x__.m_c[83] * __x__.m_c[1]));
			__x__.m_c[206] = ((-1.0f * __x__.m_c[63] * __x__.m_c[1]) + (-1.0f * __x__.m_c[33] * __x__.m_c[11]) + (__x__.m_c[43] * __x__.m_c[6]));
			__x__.m_c[216] = ((-1.0f * __x__.m_c[83] * __x__.m_c[11]) + (-1.0f * __x__.m_c[63] * __x__.m_c[16]) + (-1.0f * __x__.m_c[73] * __x__.m_c[6]));
			__x__.m_c[127] = ((__x__.m_c[112] * __x__.m_c[11]) + (-1.0f * __x__.m_c[102] * __x__.m_c[16]) + (__x__.m_c[72] * __x__.m_c[21]));
			__x__.m_c[137] = ((__x__.m_c[82] * __x__.m_c[21]) + (__x__.m_c[92] * __x__.m_c[16]) + (-1.0f * __x__.m_c[112] * __x__.m_c[6]));
			__x__.m_c[147] = ((__x__.m_c[102] * __x__.m_c[6]) + (-1.0f * __x__.m_c[92] * __x__.m_c[11]) + (__x__.m_c[62] * __x__.m_c[21]));
			__x__.m_c[157] = ((__x__.m_c[112] * __x__.m_c[1]) + (__x__.m_c[52] * __x__.m_c[21]) + (-1.0f * __x__.m_c[122] * __x__.m_c[16]));
			__x__.m_c[167] = ((__x__.m_c[92] * __x__.m_c[1]) + (__x__.m_c[32] * __x__.m_c[21]) + (-1.0f * __x__.m_c[122] * __x__.m_c[6]));
			__x__.m_c[177] = ((__x__.m_c[42] * __x__.m_c[21]) + (__x__.m_c[102] * __x__.m_c[1]) + (-1.0f * __x__.m_c[122] * __x__.m_c[11]));
			__x__.m_c[187] = ((-1.0f * __x__.m_c[52] * __x__.m_c[11]) + (__x__.m_c[72] * __x__.m_c[1]) + (__x__.m_c[42] * __x__.m_c[16]));
			__x__.m_c[197] = ((-1.0f * __x__.m_c[82] * __x__.m_c[1]) + (__x__.m_c[32] * __x__.m_c[16]) + (-1.0f * __x__.m_c[52] * __x__.m_c[6]));
			__x__.m_c[207] = ((-1.0f * __x__.m_c[42] * __x__.m_c[6]) + (__x__.m_c[62] * __x__.m_c[1]) + (__x__.m_c[32] * __x__.m_c[11]));
			__x__.m_c[217] = ((__x__.m_c[82] * __x__.m_c[11]) + (__x__.m_c[72] * __x__.m_c[6]) + (__x__.m_c[62] * __x__.m_c[16]));
			__x__.m_c[128] = ((-1.0f * __x__.m_c[74] * __x__.m_c[23]) + (-1.0f * __x__.m_c[114] * __x__.m_c[13]) + (__x__.m_c[104] * __x__.m_c[18]));
			__x__.m_c[138] = ((-1.0f * __x__.m_c[84] * __x__.m_c[23]) + (__x__.m_c[114] * __x__.m_c[8]) + (-1.0f * __x__.m_c[94] * __x__.m_c[18]));
			__x__.m_c[148] = ((-1.0f * __x__.m_c[64] * __x__.m_c[23]) + (-1.0f * __x__.m_c[104] * __x__.m_c[8]) + (__x__.m_c[94] * __x__.m_c[13]));
			__x__.m_c[158] = ((-1.0f * __x__.m_c[54] * __x__.m_c[23]) + (__x__.m_c[124] * __x__.m_c[18]) + (-1.0f * __x__.m_c[114] * __x__.m_c[3]));
			__x__.m_c[168] = ((__x__.m_c[124] * __x__.m_c[8]) + (-1.0f * __x__.m_c[34] * __x__.m_c[23]) + (-1.0f * __x__.m_c[94] * __x__.m_c[3]));
			__x__.m_c[178] = ((-1.0f * __x__.m_c[44] * __x__.m_c[23]) + (-1.0f * __x__.m_c[104] * __x__.m_c[3]) + (__x__.m_c[124] * __x__.m_c[13]));
			__x__.m_c[188] = ((-1.0f * __x__.m_c[44] * __x__.m_c[18]) + (-1.0f * __x__.m_c[74] * __x__.m_c[3]) + (__x__.m_c[54] * __x__.m_c[13]));
			__x__.m_c[198] = ((-1.0f * __x__.m_c[34] * __x__.m_c[18]) + (__x__.m_c[54] * __x__.m_c[8]) + (__x__.m_c[84] * __x__.m_c[3]));
			__x__.m_c[208] = ((__x__.m_c[44] * __x__.m_c[8]) + (-1.0f * __x__.m_c[34] * __x__.m_c[13]) + (-1.0f * __x__.m_c[64] * __x__.m_c[3]));
			__x__.m_c[218] = ((-1.0f * __x__.m_c[84] * __x__.m_c[13]) + (-1.0f * __x__.m_c[74] * __x__.m_c[8]) + (-1.0f * __x__.m_c[64] * __x__.m_c[18]));
			__x__.m_c[129] = ((-1.0f * __x__.m_c[114] * __x__.m_c[11]) + (__x__.m_c[104] * __x__.m_c[16]) + (-1.0f * __x__.m_c[74] * __x__.m_c[21]));
			__x__.m_c[139] = ((-1.0f * __x__.m_c[84] * __x__.m_c[21]) + (-1.0f * __x__.m_c[94] * __x__.m_c[16]) + (__x__.m_c[114] * __x__.m_c[6]));
			__x__.m_c[149] = ((-1.0f * __x__.m_c[64] * __x__.m_c[21]) + (-1.0f * __x__.m_c[104] * __x__.m_c[6]) + (__x__.m_c[94] * __x__.m_c[11]));
			__x__.m_c[159] = ((__x__.m_c[124] * __x__.m_c[16]) + (-1.0f * __x__.m_c[54] * __x__.m_c[21]) + (-1.0f * __x__.m_c[114] * __x__.m_c[1]));
			__x__.m_c[169] = ((-1.0f * __x__.m_c[94] * __x__.m_c[1]) + (__x__.m_c[124] * __x__.m_c[6]) + (-1.0f * __x__.m_c[34] * __x__.m_c[21]));
			__x__.m_c[179] = ((-1.0f * __x__.m_c[104] * __x__.m_c[1]) + (-1.0f * __x__.m_c[44] * __x__.m_c[21]) + (__x__.m_c[124] * __x__.m_c[11]));
			__x__.m_c[189] = ((-1.0f * __x__.m_c[44] * __x__.m_c[16]) + (__x__.m_c[54] * __x__.m_c[11]) + (-1.0f * __x__.m_c[74] * __x__.m_c[1]));
			__x__.m_c[199] = ((__x__.m_c[54] * __x__.m_c[6]) + (-1.0f * __x__.m_c[34] * __x__.m_c[16]) + (__x__.m_c[84] * __x__.m_c[1]));
			__x__.m_c[209] = ((-1.0f * __x__.m_c[34] * __x__.m_c[11]) + (-1.0f * __x__.m_c[64] * __x__.m_c[1]) + (__x__.m_c[44] * __x__.m_c[6]));
			__x__.m_c[219] = ((-1.0f * __x__.m_c[64] * __x__.m_c[16]) + (-1.0f * __x__.m_c[74] * __x__.m_c[6]) + (-1.0f * __x__.m_c[84] * __x__.m_c[11]));
			__x__.m_c[130] = ((-1.0f * __x__.m_c[114] * __x__.m_c[12]) + (-1.0f * __x__.m_c[74] * __x__.m_c[22]) + (__x__.m_c[104] * __x__.m_c[17]));
			__x__.m_c[140] = ((-1.0f * __x__.m_c[84] * __x__.m_c[22]) + (__x__.m_c[114] * __x__.m_c[7]) + (-1.0f * __x__.m_c[94] * __x__.m_c[17]));
			__x__.m_c[150] = ((__x__.m_c[94] * __x__.m_c[12]) + (-1.0f * __x__.m_c[104] * __x__.m_c[7]) + (-1.0f * __x__.m_c[64] * __x__.m_c[22]));
			__x__.m_c[160] = ((__x__.m_c[124] * __x__.m_c[17]) + (-1.0f * __x__.m_c[54] * __x__.m_c[22]) + (-1.0f * __x__.m_c[114] * __x__.m_c[2]));
			__x__.m_c[170] = ((__x__.m_c[124] * __x__.m_c[7]) + (-1.0f * __x__.m_c[34] * __x__.m_c[22]) + (-1.0f * __x__.m_c[94] * __x__.m_c[2]));
			__x__.m_c[180] = ((__x__.m_c[124] * __x__.m_c[12]) + (-1.0f * __x__.m_c[44] * __x__.m_c[22]) + (-1.0f * __x__.m_c[104] * __x__.m_c[2]));
			__x__.m_c[190] = ((-1.0f * __x__.m_c[44] * __x__.m_c[17]) + (__x__.m_c[54] * __x__.m_c[12]) + (-1.0f * __x__.m_c[74] * __x__.m_c[2]));
			__x__.m_c[200] = ((__x__.m_c[54] * __x__.m_c[7]) + (-1.0f * __x__.m_c[34] * __x__.m_c[17]) + (__x__.m_c[84] * __x__.m_c[2]));
			__x__.m_c[210] = ((__x__.m_c[44] * __x__.m_c[7]) + (-1.0f * __x__.m_c[64] * __x__.m_c[2]) + (-1.0f * __x__.m_c[34] * __x__.m_c[12]));
			__x__.m_c[220] = ((-1.0f * __x__.m_c[84] * __x__.m_c[12]) + (-1.0f * __x__.m_c[64] * __x__.m_c[17]) + (-1.0f * __x__.m_c[74] * __x__.m_c[7]));
			__x__.m_c[131] = ((-1.0f * __x__.m_c[99] * __x__.m_c[15]) + (__x__.m_c[109] * __x__.m_c[10]) + (__x__.m_c[69] * __x__.m_c[20]));
			__x__.m_c[141] = ((-1.0f * __x__.m_c[109] * __x__.m_c[5]) + (__x__.m_c[79] * __x__.m_c[20]) + (__x__.m_c[89] * __x__.m_c[15]));
			__x__.m_c[151] = ((__x__.m_c[99] * __x__.m_c[5]) + (-1.0f * __x__.m_c[89] * __x__.m_c[10]) + (__x__.m_c[59] * __x__.m_c[20]));
			__x__.m_c[161] = ((__x__.m_c[109] * __x__.m_c[0]) + (__x__.m_c[49] * __x__.m_c[20]) + (-1.0f * __x__.m_c[119] * __x__.m_c[15]));
			__x__.m_c[171] = ((__x__.m_c[89] * __x__.m_c[0]) + (__x__.m_c[29] * __x__.m_c[20]) + (-1.0f * __x__.m_c[119] * __x__.m_c[5]));
			__x__.m_c[181] = ((__x__.m_c[39] * __x__.m_c[20]) + (-1.0f * __x__.m_c[119] * __x__.m_c[10]) + (__x__.m_c[99] * __x__.m_c[0]));
			__x__.m_c[191] = ((__x__.m_c[69] * __x__.m_c[0]) + (__x__.m_c[39] * __x__.m_c[15]) + (-1.0f * __x__.m_c[49] * __x__.m_c[10]));
			__x__.m_c[201] = ((-1.0f * __x__.m_c[49] * __x__.m_c[5]) + (-1.0f * __x__.m_c[79] * __x__.m_c[0]) + (__x__.m_c[29] * __x__.m_c[15]));
			__x__.m_c[211] = ((-1.0f * __x__.m_c[39] * __x__.m_c[5]) + (__x__.m_c[59] * __x__.m_c[0]) + (__x__.m_c[29] * __x__.m_c[10]));
			__x__.m_c[221] = ((__x__.m_c[59] * __x__.m_c[15]) + (__x__.m_c[79] * __x__.m_c[10]) + (__x__.m_c[69] * __x__.m_c[5]));
			__x__.m_c[132] = ((-1.0f * __x__.m_c[110] * __x__.m_c[10]) + (__x__.m_c[100] * __x__.m_c[15]) + (-1.0f * __x__.m_c[70] * __x__.m_c[20]));
			__x__.m_c[142] = ((-1.0f * __x__.m_c[90] * __x__.m_c[15]) + (__x__.m_c[110] * __x__.m_c[5]) + (-1.0f * __x__.m_c[80] * __x__.m_c[20]));
			__x__.m_c[152] = ((__x__.m_c[90] * __x__.m_c[10]) + (-1.0f * __x__.m_c[100] * __x__.m_c[5]) + (-1.0f * __x__.m_c[60] * __x__.m_c[20]));
			__x__.m_c[162] = ((-1.0f * __x__.m_c[110] * __x__.m_c[0]) + (-1.0f * __x__.m_c[50] * __x__.m_c[20]) + (__x__.m_c[120] * __x__.m_c[15]));
			__x__.m_c[172] = ((-1.0f * __x__.m_c[90] * __x__.m_c[0]) + (-1.0f * __x__.m_c[30] * __x__.m_c[20]) + (__x__.m_c[120] * __x__.m_c[5]));
			__x__.m_c[182] = ((__x__.m_c[120] * __x__.m_c[10]) + (-1.0f * __x__.m_c[40] * __x__.m_c[20]) + (-1.0f * __x__.m_c[100] * __x__.m_c[0]));
			__x__.m_c[192] = ((-1.0f * __x__.m_c[40] * __x__.m_c[15]) + (__x__.m_c[50] * __x__.m_c[10]) + (-1.0f * __x__.m_c[70] * __x__.m_c[0]));
			__x__.m_c[202] = ((-1.0f * __x__.m_c[30] * __x__.m_c[15]) + (__x__.m_c[80] * __x__.m_c[0]) + (__x__.m_c[50] * __x__.m_c[5]));
			__x__.m_c[212] = ((__x__.m_c[40] * __x__.m_c[5]) + (-1.0f * __x__.m_c[60] * __x__.m_c[0]) + (-1.0f * __x__.m_c[30] * __x__.m_c[10]));
			__x__.m_c[222] = ((-1.0f * __x__.m_c[70] * __x__.m_c[5]) + (-1.0f * __x__.m_c[60] * __x__.m_c[15]) + (-1.0f * __x__.m_c[80] * __x__.m_c[10]));
			__x__.m_c[133] = ((__x__.m_c[108] * __x__.m_c[10]) + (-1.0f * __x__.m_c[98] * __x__.m_c[15]) + (__x__.m_c[68] * __x__.m_c[20]));
			__x__.m_c[143] = ((__x__.m_c[88] * __x__.m_c[15]) + (-1.0f * __x__.m_c[108] * __x__.m_c[5]) + (__x__.m_c[78] * __x__.m_c[20]));
			__x__.m_c[153] = ((-1.0f * __x__.m_c[88] * __x__.m_c[10]) + (__x__.m_c[58] * __x__.m_c[20]) + (__x__.m_c[98] * __x__.m_c[5]));
			__x__.m_c[163] = ((-1.0f * __x__.m_c[118] * __x__.m_c[15]) + (__x__.m_c[108] * __x__.m_c[0]) + (__x__.m_c[48] * __x__.m_c[20]));
			__x__.m_c[173] = ((-1.0f * __x__.m_c[118] * __x__.m_c[5]) + (__x__.m_c[88] * __x__.m_c[0]) + (__x__.m_c[28] * __x__.m_c[20]));
			__x__.m_c[183] = ((__x__.m_c[98] * __x__.m_c[0]) + (__x__.m_c[38] * __x__.m_c[20]) + (-1.0f * __x__.m_c[118] * __x__.m_c[10]));
			__x__.m_c[193] = ((__x__.m_c[38] * __x__.m_c[15]) + (__x__.m_c[68] * __x__.m_c[0]) + (-1.0f * __x__.m_c[48] * __x__.m_c[10]));
			__x__.m_c[203] = ((-1.0f * __x__.m_c[48] * __x__.m_c[5]) + (__x__.m_c[28] * __x__.m_c[15]) + (-1.0f * __x__.m_c[78] * __x__.m_c[0]));
			__x__.m_c[213] = ((__x__.m_c[28] * __x__.m_c[10]) + (__x__.m_c[58] * __x__.m_c[0]) + (-1.0f * __x__.m_c[38] * __x__.m_c[5]));
			__x__.m_c[223] = ((__x__.m_c[78] * __x__.m_c[10]) + (__x__.m_c[58] * __x__.m_c[15]) + (__x__.m_c[68] * __x__.m_c[5]));
			__x__.m_c[134] = ((-1.0f * __x__.m_c[100] * __x__.m_c[17]) + (__x__.m_c[70] * __x__.m_c[22]) + (__x__.m_c[110] * __x__.m_c[12]));
			__x__.m_c[144] = ((-1.0f * __x__.m_c[110] * __x__.m_c[7]) + (__x__.m_c[90] * __x__.m_c[17]) + (__x__.m_c[80] * __x__.m_c[22]));
			__x__.m_c[154] = ((__x__.m_c[100] * __x__.m_c[7]) + (__x__.m_c[60] * __x__.m_c[22]) + (-1.0f * __x__.m_c[90] * __x__.m_c[12]));
			__x__.m_c[164] = ((__x__.m_c[110] * __x__.m_c[2]) + (-1.0f * __x__.m_c[120] * __x__.m_c[17]) + (__x__.m_c[50] * __x__.m_c[22]));
			__x__.m_c[174] = ((-1.0f * __x__.m_c[120] * __x__.m_c[7]) + (__x__.m_c[30] * __x__.m_c[22]) + (__x__.m_c[90] * __x__.m_c[2]));
			__x__.m_c[184] = ((__x__.m_c[40] * __x__.m_c[22]) + (__x__.m_c[100] * __x__.m_c[2]) + (-1.0f * __x__.m_c[120] * __x__.m_c[12]));
			__x__.m_c[194] = ((-1.0f * __x__.m_c[50] * __x__.m_c[12]) + (__x__.m_c[40] * __x__.m_c[17]) + (__x__.m_c[70] * __x__.m_c[2]));
			__x__.m_c[204] = ((__x__.m_c[30] * __x__.m_c[17]) + (-1.0f * __x__.m_c[50] * __x__.m_c[7]) + (-1.0f * __x__.m_c[80] * __x__.m_c[2]));
			__x__.m_c[214] = ((__x__.m_c[30] * __x__.m_c[12]) + (-1.0f * __x__.m_c[40] * __x__.m_c[7]) + (__x__.m_c[60] * __x__.m_c[2]));
			__x__.m_c[224] = ((__x__.m_c[70] * __x__.m_c[7]) + (__x__.m_c[60] * __x__.m_c[17]) + (__x__.m_c[80] * __x__.m_c[12]));
			__x__.m_c[225] = ((-1.0f * __x__.m_c[154] * __x__.m_c[19]) + (__x__.m_c[224] * __x__.m_c[24]) + (-1.0f * __x__.m_c[134] * __x__.m_c[9]) + (-1.0f * __x__.m_c[144] * __x__.m_c[14]));
			__x__.m_c[230] = ((__x__.m_c[164] * __x__.m_c[14]) + (-1.0f * __x__.m_c[184] * __x__.m_c[19]) + (__x__.m_c[194] * __x__.m_c[24]) + (-1.0f * __x__.m_c[134] * __x__.m_c[4]));
			__x__.m_c[235] = ((__x__.m_c[204] * __x__.m_c[24]) + (__x__.m_c[164] * __x__.m_c[9]) + (-1.0f * __x__.m_c[174] * __x__.m_c[19]) + (__x__.m_c[144] * __x__.m_c[4]));
			__x__.m_c[240] = ((-1.0f * __x__.m_c[174] * __x__.m_c[14]) + (-1.0f * __x__.m_c[154] * __x__.m_c[4]) + (__x__.m_c[214] * __x__.m_c[24]) + (__x__.m_c[184] * __x__.m_c[9]));
			__x__.m_c[245] = ((__x__.m_c[194] * __x__.m_c[9]) + (-1.0f * __x__.m_c[204] * __x__.m_c[14]) + (__x__.m_c[214] * __x__.m_c[19]) + (-1.0f * __x__.m_c[224] * __x__.m_c[4]));
			__x__.m_c[226] = ((-1.0f * __x__.m_c[151] * __x__.m_c[19]) + (-1.0f * __x__.m_c[141] * __x__.m_c[14]) + (__x__.m_c[221] * __x__.m_c[24]) + (-1.0f * __x__.m_c[131] * __x__.m_c[9]));
			__x__.m_c[231] = ((-1.0f * __x__.m_c[131] * __x__.m_c[4]) + (__x__.m_c[191] * __x__.m_c[24]) + (-1.0f * __x__.m_c[181] * __x__.m_c[19]) + (__x__.m_c[161] * __x__.m_c[14]));
			__x__.m_c[236] = ((__x__.m_c[141] * __x__.m_c[4]) + (__x__.m_c[201] * __x__.m_c[24]) + (-1.0f * __x__.m_c[171] * __x__.m_c[19]) + (__x__.m_c[161] * __x__.m_c[9]));
			__x__.m_c[241] = ((-1.0f * __x__.m_c[151] * __x__.m_c[4]) + (__x__.m_c[181] * __x__.m_c[9]) + (-1.0f * __x__.m_c[171] * __x__.m_c[14]) + (__x__.m_c[211] * __x__.m_c[24]));
			__x__.m_c[246] = ((-1.0f * __x__.m_c[221] * __x__.m_c[4]) + (__x__.m_c[211] * __x__.m_c[19]) + (-1.0f * __x__.m_c[201] * __x__.m_c[14]) + (__x__.m_c[191] * __x__.m_c[9]));
			__x__.m_c[227] = ((-1.0f * __x__.m_c[152] * __x__.m_c[19]) + (__x__.m_c[222] * __x__.m_c[24]) + (-1.0f * __x__.m_c[142] * __x__.m_c[14]) + (-1.0f * __x__.m_c[132] * __x__.m_c[9]));
			__x__.m_c[232] = ((-1.0f * __x__.m_c[132] * __x__.m_c[4]) + (__x__.m_c[162] * __x__.m_c[14]) + (__x__.m_c[192] * __x__.m_c[24]) + (-1.0f * __x__.m_c[182] * __x__.m_c[19]));
			__x__.m_c[237] = ((__x__.m_c[202] * __x__.m_c[24]) + (-1.0f * __x__.m_c[172] * __x__.m_c[19]) + (__x__.m_c[162] * __x__.m_c[9]) + (__x__.m_c[142] * __x__.m_c[4]));
			__x__.m_c[242] = ((__x__.m_c[182] * __x__.m_c[9]) + (-1.0f * __x__.m_c[152] * __x__.m_c[4]) + (-1.0f * __x__.m_c[172] * __x__.m_c[14]) + (__x__.m_c[212] * __x__.m_c[24]));
			__x__.m_c[247] = ((__x__.m_c[192] * __x__.m_c[9]) + (-1.0f * __x__.m_c[202] * __x__.m_c[14]) + (__x__.m_c[212] * __x__.m_c[19]) + (-1.0f * __x__.m_c[222] * __x__.m_c[4]));
			__x__.m_c[228] = ((-1.0f * __x__.m_c[133] * __x__.m_c[9]) + (__x__.m_c[223] * __x__.m_c[24]) + (-1.0f * __x__.m_c[153] * __x__.m_c[19]) + (-1.0f * __x__.m_c[143] * __x__.m_c[14]));
			__x__.m_c[233] = ((-1.0f * __x__.m_c[133] * __x__.m_c[4]) + (__x__.m_c[193] * __x__.m_c[24]) + (-1.0f * __x__.m_c[183] * __x__.m_c[19]) + (__x__.m_c[163] * __x__.m_c[14]));
			__x__.m_c[238] = ((__x__.m_c[203] * __x__.m_c[24]) + (-1.0f * __x__.m_c[173] * __x__.m_c[19]) + (__x__.m_c[163] * __x__.m_c[9]) + (__x__.m_c[143] * __x__.m_c[4]));
			__x__.m_c[243] = ((-1.0f * __x__.m_c[153] * __x__.m_c[4]) + (-1.0f * __x__.m_c[173] * __x__.m_c[14]) + (__x__.m_c[213] * __x__.m_c[24]) + (__x__.m_c[183] * __x__.m_c[9]));
			__x__.m_c[248] = ((__x__.m_c[193] * __x__.m_c[9]) + (-1.0f * __x__.m_c[203] * __x__.m_c[14]) + (__x__.m_c[213] * __x__.m_c[19]) + (-1.0f * __x__.m_c[223] * __x__.m_c[4]));
			__x__.m_c[229] = ((__x__.m_c[154] * __x__.m_c[15]) + (__x__.m_c[144] * __x__.m_c[10]) + (-1.0f * __x__.m_c[224] * __x__.m_c[20]) + (__x__.m_c[134] * __x__.m_c[5]));
			__x__.m_c[234] = ((-1.0f * __x__.m_c[164] * __x__.m_c[10]) + (-1.0f * __x__.m_c[194] * __x__.m_c[20]) + (__x__.m_c[134] * __x__.m_c[0]) + (__x__.m_c[184] * __x__.m_c[15]));
			__x__.m_c[239] = ((-1.0f * __x__.m_c[204] * __x__.m_c[20]) + (-1.0f * __x__.m_c[164] * __x__.m_c[5]) + (__x__.m_c[174] * __x__.m_c[15]) + (-1.0f * __x__.m_c[144] * __x__.m_c[0]));
			__x__.m_c[244] = ((-1.0f * __x__.m_c[214] * __x__.m_c[20]) + (__x__.m_c[154] * __x__.m_c[0]) + (-1.0f * __x__.m_c[184] * __x__.m_c[5]) + (__x__.m_c[174] * __x__.m_c[10]));
			__x__.m_c[249] = ((__x__.m_c[224] * __x__.m_c[0]) + (__x__.m_c[204] * __x__.m_c[10]) + (-1.0f * __x__.m_c[194] * __x__.m_c[5]) + (-1.0f * __x__.m_c[214] * __x__.m_c[15]));
			__x__.m_c[250] = ((__x__.m_c[229] * __x__.m_c[4]) + (-1.0f * __x__.m_c[234] * __x__.m_c[9]) + (-1.0f * __x__.m_c[244] * __x__.m_c[19]) + (__x__.m_c[249] * __x__.m_c[24]) + (__x__.m_c[239] * __x__.m_c[14]));
		}
		void set(omFlatPoint& __x__, const om& __y__) {
			__x__.m_c[0] = ((__y__.m_c[24] * __y__.m_c[6]) + (-1.0f * __y__.m_c[9] * __y__.m_c[21]));
			__x__.m_c[1] = ((-1.0f * __y__.m_c[14] * __y__.m_c[21]) + (__y__.m_c[24] * __y__.m_c[11]));
			__x__.m_c[2] = ((__y__.m_c[24] * __y__.m_c[16]) + (-1.0f * __y__.m_c[19] * __y__.m_c[21]));
			__x__.m_c[3] = ((-1.0f * __y__.m_c[4] * __y__.m_c[21]) + (__y__.m_c[24] * __y__.m_c[1]));
			__x__.m_c[4] = ((__y__.m_c[24] * __y__.m_c[7]) + (-1.0f * __y__.m_c[9] * __y__.m_c[22]));
			__x__.m_c[5] = ((-1.0f * __y__.m_c[14] * __y__.m_c[22]) + (__y__.m_c[24] * __y__.m_c[12]));
			__x__.m_c[6] = ((__y__.m_c[24] * __y__.m_c[17]) + (-1.0f * __y__.m_c[19] * __y__.m_c[22]));
			__x__.m_c[7] = ((-1.0f * __y__.m_c[4] * __y__.m_c[22]) + (__y__.m_c[24] * __y__.m_c[2]));
			__x__.m_c[8] = ((-1.0f * __y__.m_c[9] * __y__.m_c[23]) + (__y__.m_c[24] * __y__.m_c[8]));
			__x__.m_c[9] = ((__y__.m_c[24] * __y__.m_c[13]) + (-1.0f * __y__.m_c[14] * __y__.m_c[23]));
			__x__.m_c[10] = ((__y__.m_c[24] * __y__.m_c[18]) + (-1.0f * __y__.m_c[19] * __y__.m_c[23]));
			__x__.m_c[11] = ((__y__.m_c[24] * __y__.m_c[3]) + (-1.0f * __y__.m_c[4] * __y__.m_c[23]));
			__x__.m_c[12] = ((-1.0f * __y__.m_c[9] * __y__.m_c[20]) + (__y__.m_c[24] * __y__.m_c[5]));
			__x__.m_c[13] = ((__y__.m_c[24] * __y__.m_c[10]) + (-1.0f * __y__.m_c[14] * __y__.m_c[20]));
			__x__.m_c[14] = ((-1.0f * __y__.m_c[19] * __y__.m_c[20]) + (__y__.m_c[24] * __y__.m_c[15]));
			__x__.m_c[15] = ((-1.0f * __y__.m_c[4] * __y__.m_c[20]) + (__y__.m_c[24] * __y__.m_c[0]));
		}
	} /* end of namespace __G2_GENERATED__ */


	// algebra / user constants:
	__no_ct__ no;
	__ni_ct__ ni;
	__e3_ct__ e3;
	__e2ni_ct__ e2ni;
	__I3_ct__ I3;
	__e1_ct__ e1;
	__e1ni_ct__ e1ni;
	__e2_ct__ e2;
	__e3ni_ct__ e3ni;
	__noni_ct__ noni;
	__I5_ct__ I5;
	__I5i_ct__ I5i;

	char *string(const mv & obj, char *str, int maxLength, const char *fp /* = NULL */) {
		int stdIdx = 0, l;
		char tmpBuf[256], tmpFloatBuf[256]; 
		int i, j, k = 0, bei, ia = 0, s = mv_size[obj.gu()], p = 0, cnt = 0;

		// set up the floating point precision
		if (fp == NULL) fp = mv_string_fp;

		// start the string
		l = sprintf(tmpBuf, "%s", mv_string_start);
		if (stdIdx + l <= maxLength) {
			strcpy(str + stdIdx, tmpBuf);
			stdIdx += l;
		}
		else mv_throw_exception("Buffer supplied to string() is too small", MV_EXCEPTION_ERROR);

		// print all coordinates
		for (i = 0; i <= 5; i++) {
			if (obj.gu() & (1 << i)) {
				for (j = 0; j < mv_gradeSize[i]; j++) {
					float coord = (float)mv_basisElementSign[ia] * obj.m_c[k];
					/* goal: print [+|-]obj.m_c[k][* basisVector1 ^ ... ^ basisVectorN] */			
					sprintf(tmpFloatBuf, fp, fabs(coord));
					if (atof(tmpFloatBuf) != 0.0) {
						l = 0;

						// print [+|-]
						l += sprintf(tmpBuf + l, "%s", (coord >= 0.0) 
							? (cnt ? mv_string_plus : "")
							: mv_string_minus);
						// print obj.m_c[k]
						l += sprintf(tmpBuf + l, tmpFloatBuf);

						if (i) { // if not grade 0, print [* basisVector1 ^ ... ^ basisVectorN]
							l += sprintf(tmpBuf + l, "%s", mv_string_mul);

							// print all basis vectors
							bei = 0;
							while (mv_basisElements[ia][bei] >= 0) {
								l += sprintf(tmpBuf + l, "%s%s", (bei) ? mv_string_wedge : "", 
									mv_basisVectorNames[mv_basisElements[ia][bei]]);
								bei++;
							}
						}

						//copy all to 'str'
						if (stdIdx + l <= maxLength) {
							strcpy(str + stdIdx, tmpBuf);
							stdIdx += l;
						}
						else mv_throw_exception("Buffer supplied to string() is too small", MV_EXCEPTION_ERROR);
						cnt++;
					}
					k++; ia++;
				}
			}
			else ia += mv_gradeSize[i];
		}

		// if no coordinates printed: 0
		l = 0;
		if (cnt == 0) {
			l += sprintf(tmpBuf + l, "0");
		}

		// end the string
		l += sprintf(tmpBuf + l, "%s", mv_string_end);
		if (stdIdx + l <= maxLength) {
			strcpy(str + stdIdx, tmpBuf);
			stdIdx += l;
		}
		else mv_throw_exception("Buffer supplied to string() is too small", MV_EXCEPTION_ERROR);

		return str;
	}

	// this function should be deprecated (conflicts with C++ stdlib)
	char *string(const mv & obj, const char *fp /* = NULL */) {
		// not multithreading safe, but not fatal either.
		static char str[2048];
		return string(obj, str, 2047, fp);
	}

	char *c_str(const mv & obj, const char *fp /* = NULL */) {
		return string(obj, fp);
	}

	std::string toString(const mv & obj, const char *fp /* = NULL */) {
		std::string str;
		const int SIZE = 2048;
		str.resize(SIZE);
		string(obj, &(str[0]), SIZE-1, fp);
		str.resize(strlen(&(str[0])));
		return str;
	}






	/** This function is not for external use. It compressed arrays of floats for storage in multivectors. */
	void compress(const float *c, float *cc, int &cgu, float epsilon /*= 0.0*/, int gu /*= ...*/) {
		int i, j, ia = 0, ib = 0, f, s;
		cgu = 0;

		// for all grade parts...
		for (i = 0; i <= 5; i++) {
			// check if grade part has memory use:
			if (!(gu & (1 << i))) continue;

			// check if abs coordinates of grade part are all < epsilon
			s = mv_gradeSize[i];
			j = ia + s;
			f = 0;
			for (; ia < j; ia++)
			if (mv_absLessThan(c[ia], epsilon)) {f = 1; break;}
			ia = j;
			if (f) {
				mv_memcpy(cc + ib, c + ia - s, s);
				ib += s;
				cgu |= (1 << i);
			}
		}	
	}

	mv mv_compress(const float *c, float epsilon/*= 0.0*/, int gu /*= ...*/) {
		float cc[32];
		int cgu;
		compress(c, cc, cgu, epsilon, gu);
		return mv(cgu, cc);
	}

	mv compress(const mv & arg1, float epsilon /*= 0.0*/) {
		return mv_compress(arg1.m_c, epsilon, arg1.m_gu);
	}

	void mv::compress(float epsilon /*= 0.0*/) {
		float cc[32];
		int cgu;
		c3ga::compress(m_c, cc, cgu, epsilon, m_gu);
		set(cgu, cc);
	}



	/** This function is not for external use. It decompresses the coordinates stored in this */
	void mv::expand(const Float *ptrs[], bool nulls /* = true */) const {
		const Float *c(m_c);
		const Float *null = (nulls) ? NULL : nullFloats();

		if (m_gu & 1) {
			ptrs[0] =  c;
			c += 1;
		}
		else ptrs[0] = null;	
		if (m_gu & 2) {
			ptrs[1] =  c;
			c += 5;
		}
		else ptrs[1] = null;	
		if (m_gu & 4) {
			ptrs[2] =  c;
			c += 10;
		}
		else ptrs[2] = null;	
		if (m_gu & 8) {
			ptrs[3] =  c;
			c += 10;
		}
		else ptrs[3] = null;	
		if (m_gu & 16) {
			ptrs[4] =  c;
			c += 5;
		}
		else ptrs[4] = null;	
		if (m_gu & 32) {
			ptrs[5] =  c;
			c += 1;
		}
		else ptrs[5] = null;	
	}


	void mvType::init(const mv &X, mv::Float epsilon) {
		m_type = MULTIVECTOR;

		// first of all determine grade usage & parity
		mv cX = X;
		cX.compress(epsilon);
		m_gradeUsage = (int)cX.gu();
		int cnt[2] = {0,0}; // nb even, odd grade parts in use
		{
			// count grade part usage:
			int cntIdx = 0;
			int gu = m_gradeUsage;
			while (gu != 0) {
				if ((gu & 1) != 0)
					cnt[cntIdx & 1]++;
				gu >>= 1;
				m_grade = cntIdx;
				cntIdx++;
			}

			// if no grade part in use: zero blade
			if ((cnt[0] == 0) && (cnt[1] == 0)) {
				// multivector = zero blade, case closed
				m_zero = true;
				m_type = BLADE;
				m_parity = 0;
				m_grade = 0; // forced to grade 0, but actually, does not really have a grade
				return;
			}
			else {
				m_zero = false;
				// if both even and odd grade parts in use: multivector
				if ((cnt[0] != 0) && (cnt[1] != 0)) {
					// X = multivector, case closed
					m_parity = -1;
					return;
				}
				else // more work to do, but parity is known:
				// either a blade, or a versor, TBD below
				m_parity = (cnt[1] != 0) ? 1 : 0;
			}
		}

		// first test for versor:
		bool useAlgebraMetric = true;
		init(X, epsilon, useAlgebraMetric, cnt[0] + cnt[1]);

		// Only if metric is not Euclidean:
		// If it was not a versor, or blade using the algebra metric, then try again,
		// at least, if only one grade part is in use:
		if ((m_type == MULTIVECTOR) && ((cnt[0] + cnt[1]) == 1)) {
			useAlgebraMetric = false;
			init(X, epsilon, useAlgebraMetric, cnt[0] + cnt[1]);
		}
	}


	void mvType::init(const mv &X, mv::Float epsilon, bool useAlgebraMetric, int guCnt) {
		mv rX = reverse(X);

		// test if null:
		mv Sq = (useAlgebraMetric) ? scp(X, rX) : scpEM(X, rX);
		Sq.compress(epsilon);
		if (_Float(Sq) == 0) {
			// X = multivector, case closed
			m_type = MULTIVECTOR;
			return;
		}

		// versor inverse must be true inverse:
		mv Xvi = (useAlgebraMetric) ? inverse(X) : inverseEM(X);
		mv Xgi = gradeInvolution(X);

		// check if (Xgi Xvi) is a scalar:
		mv XgiXvi = (useAlgebraMetric) ? gp(Xgi, Xvi) : gpEM(Xgi, Xvi);
		{
			mv tmp = XgiXvi;
			tmp.compress(epsilon);
			if (tmp.gu() != GRADE_0) { // if not scalar:
				// X = multivector, case closed
				m_type = MULTIVECTOR;
				return;
			}
		}

		// check if Xgi Xvi == Xvi Xgi
		mv XviXgi = (useAlgebraMetric) ? gp(Xvi, Xgi) : gpEM(Xvi, Xgi);
		{
			mv tmp = XviXgi - XgiXvi;
			tmp.compress(epsilon); // this should result in 0
			if (tmp.gu()) {
				// if not:
				// X = multivector, case closed
				m_type = MULTIVECTOR;
				return;
			}
		}

		// check if grade preserving for all basis vectors:
		{
			{
				// test no		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, no), Xgi) : gpEM(gpEM(Xvi, no), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test e1		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e1), Xgi) : gpEM(gpEM(Xvi, e1), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test e2		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e2), Xgi) : gpEM(gpEM(Xvi, e2), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test e3		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, e3), Xgi) : gpEM(gpEM(Xvi, e3), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
			{
				// test ni		
				mv tmp = (useAlgebraMetric) ? gp(gp(Xvi, ni), Xgi) : gpEM(gpEM(Xvi, ni), Xgi);
				tmp.compress(epsilon);
				if (tmp.gu() != GRADE_1) { // X = multivector, case closed
					m_type = MULTIVECTOR;
					return;
				}
			}
		}

		// if homogeneous: blade
		if (guCnt == 1) m_type = BLADE;
		else m_type = VERSOR;
	}



	std::string mvType::toString() const {
		char buf[1024];
		sprintf(buf, "%s, grade: %d, gradeUsage: %X, parity: %s",
			(m_type == MULTIVECTOR) ? "multivector" : ((m_type == BLADE) ? "blade" : "versor"),
			m_grade, m_gradeUsage,
			(m_parity < 0) ? "none" : ((m_parity == 0) ? "even" : "odd"));
		return buf;
	}










} // end of namespace c3ga
// post_cpp_include

