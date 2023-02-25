SWIG=swig4.0
SRC=../lib/*.cpp

perl:
	${SWIG} -c++ -perl -I../lib Netkit.i

	g++ --std=c++17 -fPIC -shared -DSWIG `perl -MConfig -e 'print join(" ", @Config{qw(ccflags optimize cccdlflags)}, "-I$$Config{archlib}/CORE")'` \
		`perl -MConfig -e 'print $$Config{lddlflags}'` -I../lib ${SRC} Netkit_wrap.cxx -o Netkit.so
