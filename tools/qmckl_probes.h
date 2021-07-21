#include <stdbool.h>


// Wrappers to Verificarlo functions

bool qmckl_probe(
    char * testName,
    char * varName,
    double value,
    double expectedValue
);

bool qmckl_probe_check(
    char * testName,
    char * varName,
    double value,
    double expectedValue,
    double accuracyTarget
);


bool qmckl_probe_check_relative(
    char * testName,
    char * varName,
    double value,
    double expectedValue,
    double accuracyTarget
);

void qmckl_dump_probes();


// Fortran wrappers

bool qmckl_probe_f(
    char * testName,
    char * varName,
    double * value,
    double * expectedValue
);

bool qmckl_probe_check_f(
    char * testName,
    char * varName,
    double * value,
    double * expectedValue,
    double * accuracyTarget
);


bool qmckl_probe_check_relative_f(
    char * testName,
    char * varName,
    double * value,
    double * expectedValue,
    double * accuracyTarget
);
