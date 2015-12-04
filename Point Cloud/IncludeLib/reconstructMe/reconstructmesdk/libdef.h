/** ReMe - a real-time 3D reconstruction engine
  *
  * \file
  * \author Christoph Heindl
  *         info@reconstructme.net
  *         2006-2014 PROFACTOR GmbH.
  *         All rights reserved.
  *         Use is subject to license terms.
  *
  */

#ifndef REME_LIBDEF_H
#define REME_LIBDEF_H

#ifdef _MSC_VER
#ifdef LIBRECONSTRUCTMESDK_EXPORTS
#define LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE __declspec(dllexport)
#else
#define LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE __declspec(dllimport)
#endif
#else
#define LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
#endif

#endif