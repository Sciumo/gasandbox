#include <stdio.h>

#include <lib2ndgencap/xml.h>
#include <libmarkers3d/xml.h>
#include <libmarkers3d/binary.h>
#include <libmarkers3d/reconstruct.h>


int main(int argc, char *argv[]) {
	markers3d::scene *S = NULL;
	S = new markers3d::scene();
	markers3d::binary::readScene("chap12data.rmb", *S);

	FILE *F = fopen("chap12data.txt", "wb+");
	if (F == NULL) {
		printf("Could not open output file\n");
		return -1;
	}

	fprintf(F, "nbCams %d\n", S->getCameras().size());
	fprintf(F, "nbFrames %d\n", S->getFrames().size());

	for (int i = 0; i < S->getCameras().size(); i++) {
		fprintf(F, "cam %d\n", i);
		fprintf(F, "xf: %s\n", S->getCameras()[i].getXForm().c_str_e20());
		for (int f = 0; f < S->getFrames().size(); f++) {
			for (int m = 0; m < S->getFrames()[f].getMarkers2D(i).size(); m++) {
				fprintf(F, "frame %d %s\n", f, S->getFrames()[f].getMarkers2D(i)[m].getImagePlanePt().c_str_f());

			}

		}
	}






	printf("%d frames\n", S->getFrames().size());


	delete S;

	return 0;
}