

void drawCube(const vector &p, float size) {
//	printf("%f %f %f, Size: %f\n", pc[0], pc[1], pc[2], size);
	glPushMatrix();
	glTranslatef(p.e1(), p.e2(), p.e3());
	glScalef(size, size, size);
//	printf("Call list: %d\n", cubeListName);
	glCallList(cubeListName);
	glPopMatrix();
}
