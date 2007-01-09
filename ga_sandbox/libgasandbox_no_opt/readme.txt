This directory contains unoptimized geometric algebra implementations.

The algebra implementation in ../libgasandbox contain all 
optimizations required to run the examples at full speed
(see Chapter 22 of the book for what `optimizations' these are
and how they are generated).

Because the examples make a very diverse use of geometric algebra,
the number of optimization is very high, resulting in large source files.

The most extreme example is the conformal algebra of 3-D space (c3ga).
The file sizes are:
c3ga.cpp: 653KB
c3ga.h  : 2.18MB
Especially the header file is large due to the large amount of inlined code.
The same algebra implementation, but without optimizations, has the sizes:
c3ga.cpp: 393KB
c3ga.h  : 415KB
The large file sizes may lead to long compile times. If you are having trouble
with this, copy the files in this directory (libgasandbox_no_opt) to ../libgasandbox.
This will remove all optimizations. The examples will still run at acceptable speed,
and they will compile a lot faster.


In an actual application the number of optimizations is lower because the use
of geometric algebra is less diverse. For example, the conformal algebra 
implementation I use for my motion capture system currently has the following 
file sizes:
c3ga.cpp: 470KB
c3ga.h  : 1.01MB
So this is still rather large but not as extreme as the GA Sandbox version.


D.F.