/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "ftp.h"

bool_t
xdr_data (XDR *xdrs, data *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->buffer, 25000,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->size))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_Path (XDR *xdrs, Path *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->FileName, 20,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}
