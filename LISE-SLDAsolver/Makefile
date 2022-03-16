# Makefile tested on LASSEN.LLNL.GOV
#environment module load essl lapack
# this version requires the clang compitler
# module swap xl clang

PE=$(shell echo $(PE_ENV) | tr '[:upper:]' '[:lower:]')
LA=LISE_LA_REF
COMP=cc -w -O3
GTL_LIB=#-L$(MPICH_DIR)/../../../gtl/lib -lmpi_gtl_cuda (FOR CUDA AWARE)

FFTW_INCLUDE_OPTS=-I${FFTW_DIR}/include -I$(ELPA_ROOT)/include -I$(CUDA_PATH)/include

LAPACK_LIBS=-L${CRAY_MPICH_DIR}/lib -lsci_$(PE)_mpi -L$(ELPA_ROOT)/lib -Wl,-rpath=$(ELPA_ROOT)/lib -lelpa
SCALAPACK_LIBS= #-L/opt/cray/pe/lib64 -L${CRAY_MPICH_DIR}/lib -l_pat_scalapack

LINK_LIBS=$(GTL_LIB) $(LAPACK_LIBS) $(SCALAPACK_LIBS)

MPI_LIBS = -L${MPICH_DIR}/lib 
MPI_INCLUDE = -I${MPICH_DIR}/include

EXE = lise-static

OBJS = broyden_min.o print_wf.o deform.o \
	get-blcs-dscr.o create_destroy_groups.o system_energy.o external_pot.o \
	pots_io.o cnuclear-slda-solver_pn.o dens_io.o dens_start.o make_potentials.o \
	get-mem-req-blk-cyc.o ham_matrix.o operators.o constr_dens.o axial_symmetry.o \
	2dbc-slda-mpi-wr.o

$(info $(LAPACK_LIBS) $(ELPA_ROOT))

all: $(EXE)
	cp $(EXE) $(LISE_BIN_DIR)

2dbc-slda-mpi-wr.o: 2dbc-slda-mpi-wr.c
	$(COMP)  -c ${MPI_INCLUDE} 2dbc-slda-mpi-wr.c
get-blcs-dscr.o: get-blcs-dscr.c
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} get-blcs-dscr.c
get-mem-req-blk-cyc.o: get-mem-req-blk-cyc.c
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} get-mem-req-blk-cyc.c
ham_matrix.o: ham_matrix.c vars_nuclear.h 
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} ham_matrix.c
pots_io.o: pots_io.c vars_nuclear.h
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} pots_io.c
constr_dens.o: constr_dens.c vars_nuclear.h 
	$(COMP)  -c $(OPT_OMP) ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} constr_dens.c 
operators.o: operators.c vars_nuclear.h
	$(COMP)  -c $(OPT_OMP) ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} operators.c
cnuclear-slda-solver_pn.o: cnuclear-slda-solver_pn.c vars_nuclear.h 
	$(COMP)  -c  $(LAPACK_LIBS) ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} cnuclear-slda-solver_pn.c
external_pot.o: external_pot.c vars_nuclear.h 
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} external_pot.c 
dens_start.o: dens_start.c vars_nuclear.h
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} dens_start.c
make_potentials.o: make_potentials.c vars_nuclear.h 
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} make_potentials.c 
dens_io.o: dens_io.c vars_nuclear.h
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} dens_io.c 
system_energy.o: system_energy.c vars_nuclear.h
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} ${MPI_INCLUDE} system_energy.c 
deform.o: deform.c vars_nuclear.h
	$(COMP)  -c ${FFTW_INCLUDE_OPTS} deform.c 
broyden_min.o: broyden_min.c
	@echo "BROYDEN DEFS"
	$(COMP)  -c broyden_min.c 
print_wf.o: print_wf.c vars_nuclear.h
	$(COMP)  ${MPI_INCLUDE} -c print_wf.c
create_destroy_groups.o: create_destroy_groups.c
	$(COMP)  -c ${MPI_INCLUDE} create_destroy_groups.c 
axial_symmetry.o: axial_symmetry.c vars_nuclear.h
	$(COMP)  -c ${MPI_INCLUDE} axial_symmetry.c
clean:
	rm -f $(OBJS) $(EXE) $(COBSJ) *.o.tmp

$(EXE): $(OBJS) 
	$(COMP) $(OPT_OMP) -o $(EXE) -L${FFTW_DIR}/lib -lfftw3 -lfftw3_threads $(LINK_LIBS) -lm ${MPI_LIBS} -lmpich  $(OBJS)
