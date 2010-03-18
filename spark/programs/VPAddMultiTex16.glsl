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
	gl_TexCoord[9] = gl_MultiTexCoord9;
	gl_TexCoord[10] = gl_MultiTexCoord10;
	gl_TexCoord[11] = gl_MultiTexCoord11;
	gl_TexCoord[12] = gl_MultiTexCoord12;
	gl_TexCoord[13] = gl_MultiTexCoord13;
	gl_TexCoord[14] = gl_MultiTexCoord14;
	gl_TexCoord[15] = gl_MultiTexCoord15;
	gl_Position = ftransform();
}
