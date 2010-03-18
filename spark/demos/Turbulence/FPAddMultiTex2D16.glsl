uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;
uniform sampler2D texture8;
uniform sampler2D texture9;
uniform sampler2D texture10;
uniform sampler2D texture11;
uniform sampler2D texture12;
uniform sampler2D texture13;
uniform sampler2D texture14;
uniform sampler2D texture15;

void main()
{
	vec4 kV = vec4(1,1,1,1);
	vec4 kV0  = texture2D( texture0,  gl_TexCoord[0].st );
	vec4 kV1  = texture2D( texture1,  gl_TexCoord[0].st );
	vec4 kV2  = texture2D( texture2,  gl_TexCoord[0].st );
	vec4 kV3  = texture2D( texture3,  gl_TexCoord[0].st );
	//vec4 kV4  = texture2D( texture4,  gl_TexCoord[0].st );
	//vec4 kV5  = texture2D( texture5,  gl_TexCoord[0].st );
	//vec4 kV6  = texture2D( texture6,  gl_TexCoord[0].st );
	//vec4 kV7  = texture2D( texture7,  gl_TexCoord[0].st );
	//vec4 kV8  = texture2D( texture8,  gl_TexCoord[0].st );
	//vec4 kV9  = texture2D( texture9,  gl_TexCoord[0].st );
	//vec4 kV10 = texture2D( texture10, gl_TexCoord[0].st );
	//vec4 kV11 = texture2D( texture11, gl_TexCoord[0].st );
	//vec4 kV12 = texture2D( texture12, gl_TexCoord[0].st );
	//vec4 kV13 = texture2D( texture13, gl_TexCoord[0].st );
	//vec4 kV14 = texture2D( texture14, gl_TexCoord[0].st );
	//vec4 kV15 = texture2D( texture15, gl_TexCoord[0].st );
	
	// uncomment this line for individual component display
	//vec4 kC = vec4( kV3.r, kV4.r, kV5.r, 1 );

	float fValue = kV0.r + kV1.r + kV2.r + kV3.r;
	vec4 kC = vec4(fValue, fValue, fValue, 1.0);
	
	//vec4 kC = kV0.r + kV1.r + kV2.r + kV3.r + kV4.r + kV5.r + kV6.r
	//	+ kV7.r + kV8.r + kV9.r + kV10.r + kV11.r + kV12.r 
	//	+ kV13.r + kV14.r + kV15.r;

	//vec4 kC = kV * kV0;
	gl_FragColor = clamp( kC, 0, 1 );
  
}
