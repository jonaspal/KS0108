KS0108
======

KS0108 Library


Usage
-------
Include ks0108.c and ioWrapper.c to your project.

Update ioWrapper.c to match your configuration.

	portsInit();

	lcd_init();
	
	lcd_draw_dot(64, 32);
	
	
See GLCDTest.c for more examples