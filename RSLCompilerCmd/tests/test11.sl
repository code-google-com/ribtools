/*==================================================================
/// test11.sl
///
/// Created by Davide Pasca - 2010/02/17
/// See the file "license.txt" that comes with this project for
/// copyright info. 
//================================================================*/

surface test9( float rgbcol[3] ) //{.5,.5,.5} 
{
	Ci = color( rgbcol[0], rgbcol[0+1], rgbcol[2] );
	Oi = 1;
}
