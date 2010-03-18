uniform samplerRECT texture0;
uniform samplerRECT texture1;
uniform samplerRECT texture2;
uniform samplerRECT texture3;
uniform samplerRECT texture4;
uniform samplerRECT texture5;
uniform samplerRECT texture6;
uniform samplerRECT texture7;
uniform samplerRECT texture8;
uniform samplerRECT texture9;
uniform samplerRECT texture10;
uniform samplerRECT texture11;
uniform samplerRECT texture12;
uniform samplerRECT texture13;
uniform samplerRECT texture14;
uniform samplerRECT texture15;

void main()
{
	vec4 kV = vec4(1,1,1,1);
	vec4 kV0  = texture2DRect( texture0,  gl_TexCoord[0].st );
	vec4 kV1  = texture2DRect( texture1,  gl_TexCoord[0].st );
	vec4 kV2  = texture2DRect( texture2,  gl_TexCoord[0].st );
	vec4 kV3  = texture2DRect( texture3,  gl_TexCoord[0].st );
	vec4 kV4  = texture2DRect( texture4,  gl_TexCoord[0].st );
	vec4 kV5  = texture2DRect( texture5,  gl_TexCoord[0].st );
	vec4 kV6  = texture2DRect( texture6,  gl_TexCoord[0].st );
	vec4 kV7  = texture2DRect( texture7,  gl_TexCoord[0].st );
	vec4 kV8  = texture2DRect( texture8,  gl_TexCoord[0].st );
	vec4 kV9  = texture2DRect( texture9,  gl_TexCoord[0].st );
	vec4 kV10 = texture2DRect( texture10, gl_TexCoord[0].st );
	vec4 kV11 = texture2DRect( texture11, gl_TexCoord[0].st );
	vec4 kV12 = texture2DRect( texture12, gl_TexCoord[0].st );
	vec4 kV13 = texture2DRect( texture13, gl_TexCoord[0].st );
	vec4 kV14 = texture2DRect( texture14, gl_TexCoord[0].st );
	vec4 kV15 = texture2DRect( texture15, gl_TexCoord[0].st );
	
	// uncomment this line for individual component display
	// vec4 kC = vec4( kV3.r, kV4.r, kV5.r, 1 );

	vec4 kC = kV0 + kV1 + kV2 + kV3 + kV4 + kV5 + kV6
		+ kV7 + kV8 + kV9 + kV10 + kV11 + kV12 
		+ kV13 + kV14 + kV15;

	//vec4 kC = kV * kV0;
	gl_FragColor = clamp( kC, 0, 1 );
  
}
