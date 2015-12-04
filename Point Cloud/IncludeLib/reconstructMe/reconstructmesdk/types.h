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

#ifndef REME_TYPES_H
#define REME_TYPES_H

#include "defines.h"

REME_BEGIN_DECLS


/** \brief Handle referencing a context object.
  *
  * A reme_context_t contains the complete state of the current reconstruction process,
  * including sensor objects, reconstruction volumes and surface objects. reme_context_t
  * objects are central to ReconstructMe SDK and all operations always require such a context
  * as input.
  *
  * \ingroup ContextGroup
  */
typedef struct _reme_context* reme_context_t;

/** \brief Status enumeration
  *
  * A reme_error_t contains the available status codes as returned by all methods of
  * ReconstructMe SDK. In case of error, use reme_context_get_last_error to get the latest details.
  *
  * \ingroup ContextGroup
  */
typedef enum _reme_error {
    REME_ERROR_SUCCESS = 0,                 /**< No error occurred */
    REME_ERROR_UNSPECIFIED = -1,            /**< Unspecified error occurred */
    REME_ERROR_FAILED_TO_GRAB = -2,         /**< Could not grab from sensor */
    REME_ERROR_TRACK_LOST = -3,             /**< Camera tracking lost */
    REME_ERROR_INVALID_LICENSE = -4,        /**< Failed to verify license */
    REME_ERROR_NO_CALIBRATION_TARGET = -5,  /**< Calibration target was not found in image */
    REME_ERROR_NO_COLOR_SUPPORT = -6,       /**< Color support not available. Enable in config.*/
    REME_ERROR_NO_FLOOR = -7                /**< Floor detection failed.*/
} reme_error_t;


/** \brief Logging severity levels
  *
  * Defines the severity of a given logging message
  *
  * \ingroup ContextGroup
  */
typedef enum _reme_log_severity {
    REME_LOG_SEVERITY_INFO = 2,     ///< Used to inform about changes in state.
    REME_LOG_SEVERITY_WARNING = 3,  ///< Used to indicate potential problems and unwanted behaviour.
    REME_LOG_SEVERITY_ERROR = 4     ///< Genuine errors without a recovering strategy.
} reme_log_severity_t;

/** \brief Auto-tuning profiles
  *
  * Defines for target profile to tune reconstruction settings for
  *
  * \ingroup ContextGroup
  */
typedef enum _reme_tune_profile {
    REME_TUNE_PROFILE_LOW_QUALITY = 0,           /**< Low quality profile */
    REME_TUNE_PROFILE_MID_QUALITY = 1,           /**< Mid quality profile */
    REME_TUNE_PROFILE_MAX_QUALITY = 2,           /**< Maximum quality profile */
} reme_tune_profile_t;

/** \brief Callback function prototype to receive logging information.
  *
  * Receives logging information consisting of severity level and message. Use
  * reme_context_set_log_callback to register a new callback.
  *
  * It allows passing of an optional void pointer to user specified data.
  *
  * \param sev severity level
  * \param message the log message
  * \param user_info optional pointer as specified by at reme_context_add_log_callback
  *
  * \ingroup ContextGroup
  */
typedef void (*reme_log_callback_t)(reme_log_severity_t sev, const char *message, void *user_info);

/** \brief Handle referencing a license object.
  *
  * ReconstructMe SDK commercial requires a valid license to be used.
  *
  * \ingroup LicenseGroup
  */
typedef int reme_license_t;

/** \brief Handle referencing an options object.
  *
  * A reme_options_t references a specific options class. Internally ReconstructMe SDK uses Google's protocol
  * buffers to represent options and parameters. Protocol buffers a language-neutral, platform-neutral,
  * extensible mechanism for serializing structured data.
  *
  * In order to manipulate these protocol buffer options you have two options:
  * - use the lazy dynamic interface and manipulate variables through a reflection like mechanism.
  *   \sa reme_options_set
  *   \sa reme_options_get
  * - use the typesafe interface and generate a structure from the protobuf specification file using
  *   the protobuf compiler. Interact with this class and pass ReconstructMe SDK a serialized string to its content.
  *   \sa reme_options_set_bytes
  *   \sa reme_options_get_bytes
  *
  * https://developers.google.com/protocol-buffers/
  *
  * \ingroup OptionsGroup
  */
typedef int reme_options_t;

/** \brief Handle referencing a sensor object.
  *
  * A reme_sensor_t represents a RGBD sensor. Associated methods allow to create, open and
  * interact with sensors of various types.
  *
  * \ingroup SensorGroup
  */
typedef int reme_sensor_t;

/** \brief Image type enumeration
  *
  * Each sensor might provide different frame types that are all 2D images. Not
  * all sensors support all frames, or the number of frames supported is configuration
  * dependant.
  *
  * \ingroup SensorGroup
  */
typedef enum _reme_sensor_image_t {
    REME_IMAGE_AUX = 0,         /**< Auxiliary image if provided by sensor. Depending on the sensor type and its configuration
                                     the auxilary image can be of any type. Commonly this is either RGB or IR. Usually RGB 3 channels, 1 byte per channel. */
    REME_IMAGE_DEPTH = 1,       /**< Depth image. RGB 3 channels, 1 byte per channel */
    REME_IMAGE_VOLUME = 2,      /**< Rendered image of the volume as viewed from the current sensor perspective.
                                     RGB 3 channels, 1 byte per channel. */
    REME_IMAGE_RAW_AUX = 3,     /**< Raw auxilary image as provided by sensor. Usually RGB 3 channels, 1 byte per channel.*/
    REME_IMAGE_RAW_DEPTH = 4    /**< Raw depth image as provided by sensor. 1 channel, 2 byte per channel */
} reme_sensor_image_t;

/** \brief Sensor view type
  *
  * When dealing with sensor data ReconstructMe offers two types of views. The first view ::REME_SENSOR_VIEW_RAW corresponds to
  * data passed as raw input to ReconstructMe. The second view type is ::REME_SENSOR_VIEW_RECONSTRUCTED and corresponds to a
  * synthetic view generated by raytracing the volume from the current sensor to volume position.
  *
  * The ::REME_SENSOR_VIEW_RECONSTRUCTED normally is much more smooth and has less holes than ::REME_SENSOR_VIEW_RAW, but naturally
  * limits data to the size of the reconstruction volume.
  *
  * \ingroup SensorGroup
  */
typedef enum _reme_sensor_view_t {
    REME_SENSOR_VIEW_RAW = 0,             ///< Raw data view.
    REME_SENSOR_VIEW_RECONSTRUCTED = 1    ///< Synthetic raytraced data view.
} reme_sensor_view_t;


/** \brief Sensor tracking mode
  *
  * Defines the basic tracking strategy to find the sensor position based on current and past
  * sensor data.
  *
  * \ingroup SensorGroup
  */
typedef enum _reme_sensor_trackmode_t {
    /** \brief Automatic mode. Try to use local search first. If that fails attempt to perform a global search followed
      * by local search. If last tracking attempt was unsuccessful, start using global search immediately. */
    REME_SENSOR_TRACKMODE_AUTO = 0,
    /** \brief Local search. Use local search only. Local search is fast and succeeds when
        * the camera movement between two subsequent frames is small. */
    REME_SENSOR_TRACKMODE_LOCAL = 1,
    /** \brief Global search. Use global search followed by a fine alignment of local search. Global search is slower
        * than local search but succeeds in cases where the camera movement between two subsequent
        * is rather frames large. */
    REME_SENSOR_TRACKMODE_GLOBAL = 2
} reme_sensor_trackmode_t;

/** \brief Sensor tracking hint
  *
  * Provides optional hints for the sensor tracking module.
  *
  * \ingroup SensorGroup
  */
typedef enum _reme_sensor_trackhint_t {
    /** No hint */
    REME_SENSOR_TRACKHINT_NONE = 0,
    /** Temporarily switch to global search until tracking is found again. This
      * hint is automatically cleared when tracking is found. It is a convinient way
      * of letting the tracking module know that tracking should be done using global
      * search until we are sure that tracking is found again. */
    REME_SENSOR_TRACKHINT_USE_GLOBAL = 1,
    /** Temporarily skip tracking for the current invocation. This is useful to avoid
      * growing code complexity when tracking should not occur in a certain frame. The
      * result of setting this track hint and invoking ::reme_sensor_track_position is
      * the same as not calling ::reme_sensor_track_position once.
      */
    REME_SENSOR_TRACKHINT_DONT_TRACK = 2
} reme_sensor_trackhint_t;

/** \brief Predefined sensor position
*
* Determines a predefined sensor position with respect to the current volume.
* See ::reme_sensor_get_prescan_position and ::reme_sensor_set_prescan_position
* for more information.
*
* \ingroup SensorGroup
*/
typedef enum _reme_sensor_position_t {
    /** Determines a sensor position infront of the volume front plane at a distance of 400mm. */
    REME_SENSOR_POSITION_INFRONT = 0,
    /** Determines a sensor position that places the sensor in the center of the volume. */
    REME_SENSOR_POSITION_CENTER = 1,
    /** Determines a sensor position that aligns the volume on th ground floor. */
    REME_SENSOR_POSITION_FLOOR = 2,
} reme_sensor_position_t;

/** \brief Handle referencing a volume object.
  *
  * A reme_volume_t represents a volume in 3D space. Everything within that volume is potentially
  * reconstructed during processing sensor data.
  *
  * \ingroup VolumeGroup
  */
typedef int reme_volume_t;

/** \brief Handle referencing a sensor recorder object.
  *
  * A reme_recorder_t represents a file based recording utility that is able to
  * save sensor frames to disk for later replay.
  *
  * \ingroup RecorderGroup
  */
typedef int reme_recorder_t;

/** \brief Handle referencing a surface object.
  *
  * A reme_surface_t represents a 3D mesh surface extracted from a volume. Its associated methods
  * allow to influence the generation process, access mesh data and save volumes using our exporters.
  *
  * \ingroup SurfaceGroup
  */
typedef int reme_surface_t;

/** \brief Handle referencing a 2D image object.
  *
  * A reme_image_t represents a 2D image object.
  *
  * \ingroup ImageGroup
  */
typedef int reme_image_t;

/** \brief Handle referencing a calibrator.
  *
  * Calibration determines a sensors' intrinsic parameters. Besides the focal length and principal point,
  * also the radial and tangential distortion parameters are calculated. For this to work one has to
  * specify a set of images of a known calibration target. Currently the common chessboard target is supported.
  *
  * \ingroup CalibrationGroup
  */
typedef int reme_calibrator_t;

/** \brief Predefined transform enumeration
  *
  * A reme_transform_t contains a set of predefined, often-used transforms.
  *
  * \ingroup MatrixGroup
  */
typedef enum _reme_transform {
    REME_TRANSFORM_IDENTITY      /**< Identity transform */
} reme_transform_t;

/** \brief Handle referencing a viewer object.
  *
  * Basic viewing of sensor and reconstruction outputs is provided
  * through this SDK as an debugging functionality. You should
  * not rely on its presence, as it might get dropped in later versions
  * of this SDK.
  *
  * \ingroup ViewingGroup
  */
typedef int reme_viewer_t;

/** \brief Handle referencing a CSG object.
  *
  * The CSG object allows you to modify the reconstruction content
  * by applying set operations on solids.
  *
  * \ingroup CSGGroup
  */
typedef int reme_csg_t;

/** \brief Enumeration of available CSG set operations
  *
  * The CSG module updates the content of the reconstruction volume by performing a binary set operation on it. The left
  * hand side of the operation is the content of the volume. The right hand side is one of the available solids. The
  * ::reme_set_operation_t defines the operation to apply. The result of the operation is an updated volume content.
  *
  * \ingroup CSGGroup
  */
typedef enum _reme_set_operation_t {
    REME_SET_UNION,            /**< Joins two or more solids into creating one based on the total geometry of all. */
    REME_SET_SUBTRACTION,      /**< Subtracts one or more solids from another creating a solid based on the remaining geometry.*/
    REME_SET_INTERSECTION,     /**< Creates a single solid from one more solids based on the intersected geometry. */
} reme_set_operation_t;

REME_END_DECLS

#endif