/** ReMe - a real-time 3D reconstruction engine
  *
  * \file
  * \author christoph.heindl@profactor.at
  *         2006-2013 PROFACTOR GmbH.
  *         All rights reserved.
  *         Use is subject to license terms.
  *
  */

#ifndef REME_DEFINES_H
#define REME_DEFINES_H

#define REME_VERSION_MAJOR 2
#define REME_VERSION_MINOR 1
#define REME_VERSION_BUILD 845
#define REME_VERSION_REVISION 97399

#define REME_SUCCESS(err) ((err) == 0)
#define REME_FAILED(err) ((err) != 0)

#ifdef  __cplusplus
# define REME_BEGIN_DECLS  extern "C" {
# define REME_END_DECLS    }
#else
# define REME_BEGIN_DECLS
# define REME_END_DECLS
#endif

#endif
