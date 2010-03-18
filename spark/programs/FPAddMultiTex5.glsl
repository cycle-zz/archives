uniform samplerRECT texture0;
uniform samplerRECT texture1;
uniform samplerRECT texture2;
uniform samplerRECT texture3;
uniform samplerRECT texture4;

void main()
{
	vec4 kV = vec4(1,1,1,1);
	vec4 kV0 = texture2DRect(texture0, gl_TexCoord[0].st);
	vec4 kV1 = texture2DRect(texture1, gl_TexCoord[0].st);
	vec4 kV2 = texture2DRect(texture2, gl_TexCoord[0].st);
	vec4 kV3 = texture2DRect(texture3, gl_TexCoord[0].st);
	vec4 kV4 = texture2DRect(texture4, gl_TexCoord[0].st);
	
	// uncomment this line for individual component display
	//vec4 kC = vec4( kV0.r, kV1.g, kV2.b, kV3.a );

	vec4 kC = kV0 + kV1 + kV2 + kV3 + kV4;
	//vec4 kC = kV * kV0;
	gl_FragColor = clamp( kC, 0, 1 );
  
}
