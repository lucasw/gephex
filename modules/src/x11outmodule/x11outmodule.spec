# Das ist die Spezifikation fuer das Addier Module. Blabla

mod_x11outmodule
{
	name          = X11 Output
	deterministic = true
	group	      = Outputs
	xpm	      = x11outmodule.xpm
	author        = Duran Duran
    	version       = 0.61-prealpha
	static        = true
}

inputs
{
    in
    {
	name		  = Bild
    type              = typ_FrameBufferType
	const             = true
	strong_dependency = true
    }

    xsize
    {
	name	= xsize
	type	= typ_NumberType
	const	= true
	strong_dependency = true
	hidden	= true
	default = 640
	widget_type	=	number_selector
	lower_bound	= 0
	higher_bound = 1024
	step_size = 1
	help	= [Wenn x_size und y_size > 0, wird das bild beim Laden auf xsize x ysize skaliert]
     }

     ysize
     {
	name	= ysize
	type	= typ_NumberType
	const	= true
	strong_dependency	= true
	hidden	     = true
	default      = 480
	widget_type  =	number_selector
	lower_bound  = 0
	higher_bound = 1024
	step_size = 1
	help = [Wenn x_size und y_size > 0, wird das bild beim Laden auf xsize x ysize skaliert]
     }

    driver
    {
       name              = OutputDriver
       type              = typ_StringType
       const             = true
       strong_dependency = true
       hidden            = true
       default           = XImage
       widget_type       = combo_box
       values            = XImage,XShm
    }

   server
   {
      name               = Xserver
      type               = typ_StringType
      const              = true
      strong_dependency  = true
      hidden             = true
      default            = :0.0
   }
}

outputs
{
}
