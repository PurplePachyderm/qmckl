#include <stdbool.h>

#ifdef VFC_CI
#include <vfc_probes.h>
vfc_probes probes;
#endif


// Wrappers to Verificarlo functions

#ifdef VFC_CI
void qmckl_init_probes() __attribute__((constructor)){
	probes = vfc_init_probes();
}
#endif


bool qmckl_probe(
    char * testName,
    char * varName,
    double value,
    double expectedValue
) {
#ifdef VFC_CI
    return vfc_probe(&probes, testName, varName, value);
#else
	return false;
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
    return vfc_probe_check(&probes, testName, varName, value, accuracyTarget);
#else
    return !(value == expectedValue);
#endif
}


bool qmckl_probe_check_relative (
    char * testName,
    char * varName,
    double value,
    double expectedValue,
    double accuracyTarget
) {
#ifdef VFC_CI
    return vfc_probe_check_relative(&probes, testName, varName, value, accuracyTarget);
#else
    return !(value <= expectedValue + accuracyTarget || value >= expectedValue - accuracyTarget);
#endif
}


void qmckl_dump_probes() __attribute__((destructor)){
#ifdef VFC_CI
    vfc_dump_probes(&probes);
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
