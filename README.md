libembryo
=========

screwing around with osx reversing :)

Build Notes
-----------

- Build `distorm`: modify python script to have `-static` and `-DDISTORM_STATIC` (and 32bit only unless you want universal binaries)
	- navigate to the folder with the object files and run `ar rcs distorm.a *.o`
	- A pre-build distorm.a is included in the libs/distorm folder - replace it if necessary