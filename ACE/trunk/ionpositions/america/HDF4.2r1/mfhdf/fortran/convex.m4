divert(-1)

# Name of system platform (for use in comments)
define(`M4__SYSTEM', CONVEX)

# transformation from fortran name to name of C module
define(`NAMEF',`$1')	# for Convex, need post underscore

# transformation from string name to corresponding argument name
define(`STRINGF',`$1')

# extra arguments, if any, for string length
define(`STRINGX',`, $1len')  # one extra stringlen parameter

# declaration to be used for argument name descriptor
define(`STRINGD',`
    char	*$1;	`$2'
    int		$1`'`len';') # declare argument string with extra stringlen parameter

# declarations and initializations of canonical local variables
define(`STRINGL',`')

# FORTRAN declaration for a long integer (e.g. integer*4 for Microsoft)
define(`LONG_INT',`integer')

# FORTRAN declaration for a short integer (e.g. integer*2)
define(`SHORT_INT',`integer*2')

# FORTRAN declaration for an integer byte (e.g. integer*1 or byte)
define(`BYTE_INT',`integer*1')

# FORTRAN declaration for double precision (e.g. real for a Cray)
define(`DOUBLE_PRECISION',`double precision')

# C integral type equivalent to a FORTRAN INTEGER
define(`F_INTEGER',`int')

divert(0)dnl
