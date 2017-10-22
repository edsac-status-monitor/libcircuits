
TESTS = check_vector check_circuit

check_PROGRAMS = $(TESTS)


check_vector_SOURCES = check_vector.c
check_vector_CFLAGS = @CHECK_CFLAGS@ -DCHECK
check_vector_LDADD = $(top_builddir)/src/libcircuit.la @CHECK_LIBS@

check_circuit_SOURCES = check_circuit.c
check_circuit_CFLAGS = @CHECK_CFLAGS@ -DCHECK
check_circuit_LDADD = $(top_builddir)/src/libcircuit.la @CHECK_LIBS@
