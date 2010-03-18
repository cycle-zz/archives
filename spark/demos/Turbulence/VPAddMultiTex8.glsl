void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord1;
	gl_TexCoord[2] = gl_MultiTexCoord2;
	gl_TexCoord[3] = gl_MultiTexCoord3;
	gl_TexCoord[4] = gl_MultiTexCoord4;
	gl_TexCoord[5] = gl_MultiTexCoord5;
	gl_TexCoord[6] = gl_MultiTexCoord6;
	gl_TexCoord[7] = gl_MultiTexCoord7;
	gl_TexCoord[8] = gl_MultiTexCoord8;
	gl_Position = ftransform();
}
