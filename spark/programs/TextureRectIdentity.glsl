uniform samplerRECT texture;

void main()
{
  gl_FragColor =  texture2DRect(texture,gl_TexCoord[0].st);
}
