#ifndef LASER_UTILS
#define LASER_UTILS


	static void hsbToRgb(GLfloat *hsb, GLfloat *rgb) {

		if ( hsb[1] == 0.0 )                       
		{
		   rgb[0] = hsb[2];
		   rgb[1] = hsb[2];
		   rgb[2] = hsb[2];
		}
		else
		{
		  float var_h = hsb[0] * 6;
		  float var_i = floor( var_h ) ;            //Or ... var_i = floor( var_h )
		  float var_1 = hsb[2] * ( 1 - hsb[1] );
		  float var_2 = hsb[2] * ( 1 - hsb[1] * ( var_h - var_i ) );
		  float var_3 = hsb[2] * ( 1 - hsb[1] * ( 1 - ( var_h - var_i ) ) );


		   if      ( var_i == 0 ) { rgb[0] = hsb[2]     ; rgb[1] = var_3      ; rgb[2] = var_1;   }
		   else if ( var_i == 1 ) { rgb[0] = var_2      ; rgb[1] = hsb[2]     ; rgb[2] = var_1;   }
		   else if ( var_i == 2 ) { rgb[0] = var_1      ; rgb[1] = hsb[2]     ; rgb[2] = var_3;   }
		   else if ( var_i == 3 ) { rgb[0] = var_1      ; rgb[1] = var_2      ; rgb[2] = hsb[2];  }
		   else if ( var_i == 4 ) { rgb[0] = var_3      ; rgb[1] = var_1      ; rgb[2] = hsb[2];  }
		   else                   { rgb[0] = hsb[2]     ; rgb[1] = var_1      ; rgb[2] = var_2;   }

		   rgb[0];                  
		   rgb[1];
		   rgb[2];
		}
	}

	static void rgbToHsb(GLfloat *hsb, GLfloat *rgb)
	{
	    double hue, sat, value;
	    double diff, x, r, g, b;
	    double red, green, blue;

	    red 	= rgb[0];
	    green 	= rgb[1];
	    blue 	= rgb[2];

	    hue = sat = 0.0;
	    value = x = red;
	    if (green > value) value = green;  else x = green;
	    if (blue > value) value = blue;
	    if (blue < x) x = blue;

	    if (value != 0.0) {
		diff = value - x;
		if (diff != 0.0) {
		    sat = diff / value;
		    r = (value - red) / diff;
		    g = (value - green) / diff;
		    b = (value - blue) / diff;
		    if      (red == value)   hue = (green == x) ? 5.0 + b : 1.0 - g;
		    else if (green == value) hue = (blue == x) ? 1.0 + r : 3.0 - b;
		    else                     hue = (red == x) ? 3.0 + g : 5.0 - r;
		    hue /= 6.0;  if (hue >= 1.0 || hue <= 0.0) hue = 0.0;
		}
	    }
	    hsb[0] = hue;
	    hsb[1] = sat;
	    hsb[2] = value;
	}





#endif

