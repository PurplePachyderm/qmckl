#include <stdbool.h>

#ifdef VFC_CI
#include <vfc_probes.h>
vfc_probes * probes = NULL;
#endif


// Wrappers to Verificarlo functions

bool qmckl_probe(
    char * testName,
    char * varName,
    double value,
    double expectedValue
) {
#ifdef VFC_CI
    if(probes == NULL) {
        *probes = vfc_init_probes();
    }
    return vfc_probe(probes, testName, varName, value);
#else
    return value == expectedValue;
#endif
}


bool qmckl_probe_check(
    char * testName,
    char * varName,
    double value,
    double expectedValue,
    double accuracyTarget
) {
#ifdef VFC_CI
    if(probes == NULL) {
        *probes = vfc_init_probes();
    }
    return vfc_probe_check(probes, testName, varName, value, accuracyTarget);
#else
    return value == expectedValue;
#endif
}


bool qmckl_probe_check_relative(
    char * testName,
    char * varName,
    double value,
    double expectedValue,
    double accuracyTarget
) {
#ifdef VFC_CI
    if(probes == NULL) {
        *probes = vfc_init_probes();
    }
    return vfc_probe_check_relative(probes, testName, varName, value, accuracyTarget);
#else
    return value == expectedValue;
#endif
}

void qmckl_dump_probes() {
#ifdef VFC_CI
    vfc_dump_probes(probes);
#endif
}


// Fortran wrappers

bool qmckl_probe_f(
    char * testName,
    char * varName,
    double * value,
    double * expectedValue
) {
    return qmckl_probe(testName, varName, *value, *expectedValue);
}


bool qmckl_probe_check_f(
    char * testName,
    char * varName,
    double * value,
    double * expectedValue,
    double * accuracyTarget
) {
    return qmckl_probe_check(
        testName, varName,
        *value, *expectedValue, *accuracyTarget
    );
}


bool qmckl_probe_check_relative_f(
    char * testName,
    char * varName,
    double * value,
    double * expectedValue,
    double * accuracyTarget
) {
    return qmckl_probe_check_relative(
        testName, varName,
        *value, *expectedValue, *accuracyTarget
    );
}
