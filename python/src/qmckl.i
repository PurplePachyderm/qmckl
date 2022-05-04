%module qmckl
/* Define SWIGWORDSIZE in order to properly align long integers on 64-bit system */
#define SWIGWORDSIZE64
%{
#define SWIG_FILE_WITH_INIT
/* Include the headers in the wrapper code */
#include "qmckl.h"
%}

/*
 * Get rid of the function prefixes, as the scripting language will use
 * the module's namespace.
 */
%rename("%(strip:[qmckl_])s") "";

/* Include stdint to recognize types from stdint.h */
%include <stdint.i>

/* Include typemaps to play with input/output re-casting (e.g. C pointers) */
%include typemaps.i

%apply int *OUTPUT { qmckl_exit_code *exit_code};

/* Avoid passing file_name length as an additiona argument */
%apply (char *STRING, int LENGTH) { (const char* file_name, const int64_t size_max) };

/* For functions that return strings */
%include <cstring.i>

%cstring_bounded_output(char* function_name, 1024);
%cstring_bounded_output(char* message, 1024);

/* This block is needed make SWIG convert NumPy arrays to/from from the C pointer and size_max argument.
   NOTE: `numpy.i` interface file is not part of SWIG but it is included in the numpy distribution (under numpy/tools/swig/numpy.i)
*/
%include "numpy.i"

%init %{
import_array();
%}

/* Typemaps below change the type of numpy array dimensions from int to int64_t */
%numpy_typemaps(double, NPY_DOUBLE, int64_t)
%numpy_typemaps(float, NPY_FLOAT, int64_t)
%numpy_typemaps(int32_t, NPY_INT32, int64_t)
%numpy_typemaps(int64_t, NPY_INT64, int64_t)

/* Include typemaps generated by the process_header.py script */
%include "qmckl_include.i"

/* exception.i is a generic (language-independent) module */
%include "exception.i"

/* Error handling */
%typemap(out) qmckl_exit_code %{
    if ($1 != QMCKL_SUCCESS) {
        SWIG_exception(SWIG_RuntimeError, qmckl_string_of_error($1));
    }
    $result = Py_None;
    Py_INCREF(Py_None); /* Py_None is a singleton so increment its reference if used. */
%}

/* More swig-y solution (e.g. compatible beyond Python) BUT it does not consume the qmckl_exit_code output as the solution above 
TODO: the sizeof() check below if a dummy workaround
It is good to skip exception raise for functions like context_create and others, but might fail
if sizeof(result) == sizeof(qmckl_exit_code), e.g. for functions that return non-zero integers or floats
*/
/*
%exception {
  $action
  if (result != QMCKL_SUCCESS && sizeof(result) == sizeof(qmckl_exit_code)) {
    SWIG_exception_fail(SWIG_RuntimeError, qmckl_string_of_error(result));
  }
}
*/
/* The exception handling above does not work for void functions like lock/unlock so exclude them for now */
/*
%ignore qmckl_lock;
%ignore qmckl_unlock;
*/

/* Parse the header files to generate wrappers */
%include "qmckl.h"

