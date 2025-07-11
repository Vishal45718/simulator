# -*- Makefile -*-

#target : dependencies
#	action

# Linking all the object files to create the final executable file 'riscv_sim'
# Generates the main executable
all : risc_sim.o Iconvert.o Rconvert.o Sconvert.o Bconvert.o Jconvert.o Uconvert.o sort_find.o commalgo.o
	g++ -o riscv_sim risc_sim.o Iconvert.o Rconvert.o Sconvert.o Bconvert.o sort_find.o Jconvert.o Uconvert.o commalgo.o

# Creating the object file for 'risc_sim.cpp'
# Dependencies: risc_sim.cpp, commalgo.hh, struct.hh, sort_find.hh, risc_sim.hh
# This will create 'risc_sim.o' which contains the compiled code of risc_sim.cpp
risc_sim.o : risc_sim.cpp commalgo.hh struct.hh sort_find.hh risc_sim.hh
	g++ -c risc_sim.cpp

# Creating the object file for 'Iconvert.cpp'
# Dependencies: Iconvert.cpp, commalgo.hh
# This will create 'Iconvert.o' which contains the compiled code of Iconvert.cpp
Iconvert.o : Iconvert.cpp commalgo.hh
	g++ -c Iconvert.cpp

# Creating the object file for 'Rconvert.cpp'
# Dependencies: Rconvert.cpp, commalgo.hh
# This will create 'Rconvert.o' which contains the compiled code of Rconvert.cpp
Rconvert.o : Rconvert.cpp commalgo.hh
	g++ -c Rconvert.cpp

# Creating the object file for 'Sconvert.cpp'
# Dependencies: Sconvert.cpp, commalgo.hh
# This will create 'Sconvert.o' which contains the compiled code of Sconvert.cpp
Sconvert.o : Sconvert.cpp commalgo.hh
	g++ -c Sconvert.cpp

# Creating the object file for 'Bconvert.cpp'
# Dependencies: Bconvert.cpp, commalgo.hh
# This will create 'Bconvert.o' which contains the compiled code of Bconvert.cpp
Bconvert.o : Bconvert.cpp commalgo.hh
	g++ -c Bconvert.cpp

# Creating the object file for 'Uconvert.cpp'
# Dependencies: Uconvert.cpp, commalgo.hh
# This will create 'Uconvert.o' which contains the compiled code of Uconvert.cpp
Uconvert.o : Uconvert.cpp commalgo.hh
	g++ -c Uconvert.cpp

# Creating the object file for 'Jconvert.cpp'
# Dependencies: Jconvert.cpp, commalgo.hh
# This will create 'Jconvert.o' which contains the compiled code of Jconvert.cpp
Jconvert.o : Jconvert.cpp commalgo.hh
	g++ -c Jconvert.cpp

# Creating the object file for 'sort_find.cpp'
# Dependencies: sort_find.cpp, Iconvert.hh, Rconvert.hh, Sconvert.hh, Bconvert.hh, Jconvert.hh, Uconvert.hh, sort_find.hh
# This will create 'sort_find.o' which contains the compiled code of sort_find.cpp
sort_find.o : sort_find.cpp Iconvert.hh Rconvert.hh Sconvert.hh Bconvert.hh Jconvert.hh Uconvert.hh sort_find.hh
	g++ -c sort_find.cpp

# Creating the object file for 'commalgo.cpp'
# Dependencies: commalgo.cpp, struct.hh, commalgo.hh
# This will create 'commalgo.o' which contains the compiled code of commalgo.cpp
commalgo.o : commalgo.cpp struct.hh commalgo.hh
	g++ -c commalgo.cpp

# Target to remove all the object files and the main executable
# Removes intermediate object files and the final executable to clean up the workspace
clear :
	rm *.o riscv_sim
