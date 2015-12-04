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

#ifndef REME_FUNCTIONS_H
#define REME_FUNCTIONS_H

#include "libdef.h"
#include "defines.h"
#include "types.h"

REME_BEGIN_DECLS

/** \ingroup ContextGroup
  * \{
  */

/** \brief Create a new reme_context_t object.
  *
  * \param c A pointer that will receive the created context handle
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_create(reme_context_t *c);


/** \brief Destroy a previously created reme_context_t object.
  *
  * Destroys all associated handles and memory allocated.
  *
  * \param c A pointer to a valid context object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_destroy(reme_context_t *c);

/** \brief Get the ReconstructMe SDK version string
  *
  * Format is \verbatim <major>.<minor>.<build> - <revision> \endverbatim
  *
  * \param c A valid context object
  * \param version A mutable pointer that receives the null terminated string
  * \param length length of string in bytes
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_get_version(reme_context_t c, const char **version, int *length);

/** \brief Set the logging callback
  *
  * The function pointer must stay valid until the context is destroyed or
  * ::reme_context_set_log_callback is invoked with a different function pointer.
  *
  * Invoke with a NULL function pointer to indicate that logging should be disabled.
  *
  * \param c A valid context object
  * \param lc Logging callback function pointer
  * \param user_data A pointer to optional user data to be passed to the callback function
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_set_log_callback(reme_context_t c, reme_log_callback_t lc, void *user_data = 0);

/** Default logging callback.
  *
  * Default logging callback logs infos to STDOUT and everything else to STDERR.
  *
  * \param sev Logging severity
  * \param message Message to log
  * \param user_info additional user info. Unused.
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
void reme_default_log_callback(reme_log_severity_t sev, const char *message, void *user_info);

/** \brief Access the reconstruction options.
  *
  * The reconstruction options define the behaviour of the reconstruction process. Note that some
  * options can be set during run-time and others require re-compilation by invoking
  * ::reme_context_compile. The protocol buffer specification documents when a re-compilation is
  * necessary.
  *
  * \par Associated Protocol Buffers Specification
  * \include reconstruction_settings.proto
  *
  * \param c A valid context object
  * \param o A valid options binding
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_bind_reconstruction_options(reme_context_t c, reme_options_t o);

/** \brief Access platform OpenCL information.
  *
  * \par Associated Protocol Buffers Specification
  * \include opencl_info.proto
  *
  * \param c A valid context object
  * \param o A valid options binding
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_bind_opencl_info(reme_context_t c, reme_options_t o);


/** \brief Auto-tune reconstruction settings.
  *
  * This function tries to tune the reconstruction settings with respect to a given quality profile (::reme_tune_profile_t).
  * It takes into account the specified device limitations and adjusts settings to for single volume scan.
  *
  * \note Quality is often inversely related to speed - a low quality profile will perform faster than a high quality
  * profile setting.
  *
  * The tuning algorithm reads the following reconstruction fields (see ::reme_context_bind_reconstruction_options)
  *  - <code>device_id</code>
  *  - <code>volume.minimum_corner</code> and <code>volume.maximum_corner</code>
  *  - <code>data_integration.use_colors</code>
  *
  * The tuning algorithm tunes the following reconstruction fields
  *  - <code>volume.resolution</code>
  *  - <code>data_integration.truncation</code>
  *  - <code>depthmap_erosion.*</code>
  *  - <code>colormap_erosion.*</code>
  *
  * \note Compiling (::reme_context_compile) is required for the changed parameters to take effect.
  *
  * \param c A valid context object
  * \param profile Profile to tune for
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_tune_reconstruction_options(reme_context_t c, reme_tune_profile_t profile);


/** \brief Compile OpenCL related kernels.
  *
  * Based on the compile time settings reme_context_get_compile_options, try to compile
  * for the selected OpenCL compatible device.
  *
  * In case of error check the last error through reme_context_get_last_error to receive the
  * full build log.
  *
  * Note that a successful compilation will force all objects that communicate with the
  * computation device to re-initialize. Foremost these are the ::reme_sensor_t and
  * ::reme_volume_t objects. Data of these objects will be reset to empty state.
  *
  * \param c A valid context object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_compile(reme_context_t c);

/** \brief Access current error state
  *
  * \par Associated Protocol Buffers Specification
  * \include error_info.proto
  *
  * \param c A valid context object
  * \param o A valid options binding
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_bind_error_info(reme_context_t c, reme_options_t o);

/** \brief Print all errors to standard error output and reset errors
  *
  * \param c A valid context object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_context_print_errors(reme_context_t c);

/** \} */

/** \ingroup LicenseGroup
  * \{
  */

/** \brief Creates a new license object.
  *
  * Only one license object can be around for a context. Multiple invocations
  * will return the same handle.
  *
  * \param c A valid context object
  * \param l A pointer that will receive the license handle.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_license_create(reme_context_t c, reme_license_t *l);

/** \brief Destroy a previously created license object.
  *
  * \param c A pointer to a valid context object
  * \param l A mutable pointer to a valid license handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_license_destroy(reme_context_t c, reme_license_t *l);

/** \brief Reset data related to runtime information
  *
  * \param c A pointer to a valid context object
  * \param l A valid license handle
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_license_clear_runtime_info(reme_context_t c, reme_license_t l);

/** \brief Add licensed software
  *
  * These values are required when the license is bound to specific software
  *
  * \param c A pointer to a valid context object
  * \param l A valid license handle
  * \param module Name of the module that the signed hash corresponds to.
  *               This module must be found in the current process (i.e. loaded by the current process).
  *               Wildcards *? are accepted.
  * \param module_length length of module string in bytes
  * \param shash the signed checksum of the module
  * \param shash_length length of the signed checksum in bytes
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_license_add_software(reme_context_t c, reme_license_t l, const char *module, int module_length, const char *shash, int shash_length);

/** \brief Authenticate using the given license file and any specified runtime data.
  *
  * Unless a valid ReconstructMe SDK license is specified, this SDK runs in
  * non-commercial mode.
  *
  * \param c A valid context handle
  * \param l A valid license handle
  * \param license The license file path containing it.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_INVALID_LICENSE On authentication error. ::reme_context_bind_error_info contains details.
  * \retval ::REME_ERROR_UNSPECIFIED On failure.
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_license_authenticate(reme_context_t c, reme_license_t l, const char *license);

/** \brief Access hardware hashes for generating single user licenses bound to specific hardware.
  *
  * \par Associated Protocol Buffers Specification
  * \snippet license.proto Hardware Hashes
  *
  * \param c A valid context object
  * \param l A valid license object
  * \param o A valid options binding
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_license_bind_hardware_hashes(reme_context_t c, reme_license_t l, reme_options_t o);

/** \} */

/** \ingroup OptionsGroup
  * \{
  */

/** \brief Create a new options binding.
  *
  * Creates an empty options binding.
  *
  * \param c A valid context object
  * \param o A pointer that will receive the options handle.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_create(reme_context_t c, reme_options_t *o);

/** \brief Destroy a previously created options object.
  *
  * \param c A pointer to a valid context object
  * \param o A mutable pointer to a valid options handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_destroy(reme_context_t c, reme_options_t *o);

/** \brief Set the value of options field.
  *
  * This method uses a reflection like mechanism to set the specified field value.
  * Use the '.' character to separate nested fields. If any field encountered is
  * repeated the first element is used.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field to manipulate
  * \param value String to set
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_set(reme_context_t c, reme_options_t o, const char *field_name, const char *value);

/** \brief Set a specific integer options field.
  *
  * This method uses a reflection like mechanism to set the specified field value.
  * Use the '.' character to separate nested fields. If any field encountered is
  * repeated the first element is used.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field to manipulate
  * \param value value to set
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_set_int(reme_context_t c, reme_options_t o, const char *field_name, int value);

/** \brief Set a specific real options field.
  *
  * This method uses a reflection like mechanism to set the specified field value.
  * Use the '.' character to separate nested fields. If any field encountered is
  * repeated the first element is used.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field to manipulate
  * \param value value to set
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_set_real(reme_context_t c, reme_options_t o, const char *field_name, float value);

/** \brief Set a specific boolean options field.
  *
  * This method uses a reflection like mechanism to set the specified field value.
  * Use the '.' character to separate nested fields. If any field encountered is
  * repeated the first element is used.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field to manipulate
  * \param value value to set
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_set_bool(reme_context_t c, reme_options_t o, const char *field_name, bool value);

/** \brief Get the value of an options field as string.
  *
  * This method uses a reflection like mechanism to get the specified field value.
  * Use the '.' character to separate nested fields. If any field encountered is
  * repeated the first element is used.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field to access
  * \param value Pre-allocated buffer to assign the string to
  * \param length Length of buffer
  * \param index Repeated field index
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_get(reme_context_t c, reme_options_t o, const char *field_name, char *value, int length, int index = 0);

/** \brief Get the value of an integer options field.
  *
  * This method uses a reflection like mechanism to get the specified field value.
  * Use the '.' character to separate nested fields. If any field encountered is
  * repeated the first element is used.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field to access
  * \param value Value to assign to
  * \param index Repeated field index
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_get_int(reme_context_t c, reme_options_t o, const char *field_name, int *value, int index = 0);

/** \brief Get the value of a real options field.
  *
  * This method uses a reflection like mechanism to get the specified field value.
  * Use the '.' character to separate nested fields. If any field encountered is
  * repeated the first element is used.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field to access
  * \param value Value to assign to
  * \param index Repeated field index
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_get_real(reme_context_t c, reme_options_t o, const char *field_name, float *value, int index = 0);

/** \brief Get the value of a boolean options field.
  *
  * This method uses a reflection like mechanism to get the specified field value.
  * Use the '.' character to separate nested fields. If any field encountered is
  * repeated the first element is used.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field to access
  * \param value Value to assign to
  * \param index Repeated field index
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_get_bool(reme_context_t c, reme_options_t o, const char *field_name, bool *value, int index = 0);

/** \brief Return the number of elements in a repeated field.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field to manipulate
  * \param length Number of elements in repeated field. If field is not repeated, returns 1.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_get_repeated_count(reme_context_t c, reme_options_t o, const char *field_name, int *length);

/** \brief Clear options.
  *
  * Clearing option values means to reset them into an empty state. If you retrieve a value from an empty field,
  * the fields default value (see associated .proto file) will be returned. When the field does not have any default
  * value assigned, an error will be returned.
  *
  * Clearing is useful when one wants to introduce an optional state. For example, ::reme_sensor_apply_capture_options
  * will only apply those capture options that are not empty. Take note that by default the bound capture options, i.e
  * ::reme_sensor_bind_capture_options will contain the current set values. Therefore, clear those options before setting
  * individual option values.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_clear(reme_context_t c, reme_options_t o);

/** \brief Bind options object to a nested message.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field containing the nested message
  * \param o_nested A valid options object recieving the binding.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_bind_message(reme_context_t c, reme_options_t o, const char *field_name, reme_options_t o_nested);

/** \brief Bind options object to a nested repeated message.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param field_name Name of the field containing the nested message
  * \param repeated_index When the target message is repeated the command applies to the i-th field.
  * \param o_nested A valid options object recieving the binding.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_bind_repeated_message(reme_context_t c, reme_options_t o, const char *field_name, int repeated_index, reme_options_t o_nested);

/** \brief Copy the content of the source options to the destination options.
  *
  * This method requires the two option sets involved to be of the same type.
  *
  * \param c A valid context object
  * \param o_src A valid options object to copy from
  * \param o_dst A valid options object to copy to
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_copy(reme_context_t c, reme_options_t o_src, reme_options_t o_dst);

/** \brief Set options by loading a human readable options representation from file
  *
  * This method uses protobuf's text format parser to read in the content of the file.
  * This text format is very similar to json.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param filename Path to file.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_load_from_file(reme_context_t c, reme_options_t o, const char *filename);

/** \brief Set options by loading a human readable options representation from a given string
  *
  * This method uses protobuf's text format parser to read in the content of the string.
  * This text format is very similar to json.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param message Immutable pointer to start of string.
  * \param length Number of characters in string.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_load_from_string(reme_context_t c, reme_options_t o, const char *message, int length);

/** \brief Save options in a human readable file format
  *
  * This method uses protobuf's text format serializer to write in the content of the file.
  * The output is similar to json.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param filename Path to file.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_save_to_file(reme_context_t c, reme_options_t o, const char *filename);

/** \brief Get options as string using a human readable serialization.
  *
  * This method uses protobuf's text format serializer to write in the content of the file.
  * The output is similar to json.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param message A mutable pointer that will receive the content of the message
  * \param length A pointer that will receive the length of the serialized message in bytes
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_save_to_string(reme_context_t c, reme_options_t o, const char **message, int *length);

/** \brief Set options by reading a binary options representation
  *
  * This method uses protobuf's standard serialization format (binary) to read in the desired
  * options value.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param message A valid pointer to the serialized message
  * \param length The length of the serialized message in bytes.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_set_bytes(reme_context_t c, reme_options_t o, const void *message, int length);

/** \brief Get options by serializing them in a binary options representation
  *
  * This method uses protobuf's standard serialization format (binary) to serialize the current
  * state of option values.
  *
  * \param c A valid context object
  * \param o A valid options object
  * \param message A mutable pointer that will receive the address of the serialized message
  * \param length A pointer that will receive the length of the serialized message in bytes
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_options_get_bytes(reme_context_t c, reme_options_t o, const void **message, int *length);

/** \} */


/** \ingroup VolumeGroup
  * \{
  */

/** \brief Create a new reme_volume_t object.
  *
  * \param c A valid context object
  * \param v A pointer that will receive the handle of the created volume
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_create(reme_context_t c, reme_volume_t *v);

/** \brief Destroy a previously created volume object.
  *
  * \param c A pointer to a valid context object
  * \param v A mutable pointer to a valid volume handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_destroy(reme_context_t c, reme_volume_t *v);

/** \brief Get the volume time
  *
  * The volume time corresponds to the number of updates performed on this volume.
  * Initialize it is set to zero.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param time The volume time
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_get_time(reme_context_t c, reme_volume_t v, int *time);

/** \brief Returns the content of the volume as an array of bytes.
  *
  * Downloads the current content of the volume to host side. Using in combination
  * with ::reme_volume_set_bytes one can resume a previously started reconstruction
  * as long as the volume parameters (dimensions) match.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param bytes A mutable pointer that will receive the address of the volume content.
  * \param length A pointer that will receive the size of the returned array in bytes.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_get_bytes(reme_context_t c, reme_volume_t v, const void **bytes, int *length);

/** \brief Returns the content of the color volume as an array of bytes.
  *
  * Downloads the current content of the color volume to host side. Using in combination
  * with ::reme_volume_color_set_bytes one can resume a previously started reconstruction
  * as long as the volume parameters (dimensions) match.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param bytes A mutable pointer that will receive the address of the color volume content.
  * \param length A pointer that will receive the size of the returned array in bytes.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_color_get_bytes(reme_context_t c, reme_volume_t v, const void **bytes, int *length);

/** \brief Returns the content of a specific slice ("xy-plane") of the volume as an array of bytes.
  *
  * Downloads the current content of the slice ("xy-plane") of the volume to host side. Using in combination
  * with ::reme_volume_slice_set_bytes one can resume a previously started reconstruction
  * as long as the volume parameters (dimensions) match.
  *
  * The number of slices equals the number of voxels in the z-dimension.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param slice Slize index along z-Dimension
  * \param bytes A mutable pointer that will receive the address of the volume content.
  * \param length A pointer that will receive the size of the returned array in bytes.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_slice_get_bytes(reme_context_t c, reme_volume_t v, const int slice, const void **bytes, int *length);

/** \brief Returns the content of a specific slice ("xy-plane") of the color volume as an array of bytes.
  *
  * Downloads the current content of the slice ("xy-plane") of the color volume to host side. Using in combination
  * with ::reme_volume_color_slice_set_bytes one can resume a previously started reconstruction
  * as long as the volume parameters (dimensions) match.
  *
  * The number of slices equals the number of voxels in the z-dimension.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param slice slice index along z-Dimension
  * \param bytes A mutable pointer that will receive the address of the color volume content.
  * \param length A pointer that will receive the size of the returned array in bytes.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_color_slice_get_bytes(reme_context_t c, reme_volume_t v, const int slice, const void **bytes, int *length);

/** \brief Sets the content of the volume to the given array of bytes.
  *
  * Uploads the given array as volume content to the device side. Using in combination
  * with ::reme_volume_get_bytes one can resume a previously started reconstruction
  * as long as the volume parameters (dimensions) match.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param bytes An array of bytes
  * \param length Number of bytes in the array
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_set_bytes(reme_context_t c, reme_volume_t v, const void *bytes, int length);

/** \brief Sets the content of the color volume to the given array of bytes.
  *
  * Uploads the given array as color volume content to the device side. Using in combination
  * with ::reme_volume_color_get_bytes one can resume a previously started reconstruction
  * as long as the volume parameters (dimensions) match.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param bytes An array of bytes
  * \param length Number of bytes in the array
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_color_set_bytes(reme_context_t c, reme_volume_t v, const void *bytes, int length);

/** \brief Sets the content of a slice ("xy-plane") of the volume to the given array of bytes.
  *
  * Uploads the given array as slice ("xy-plane") of the volume content to the device side. Using in combination
  * with ::reme_volume_slice_get_bytes one can resume a previously started reconstruction
  * as long as the volume parameters (dimensions) match.
  *
  * The number of slices equals the number of voxels in the z-dimension.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param slice Slice id along z-Dimension.
  * \param bytes An array of bytes
  * \param length Number of bytes in the array
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_slice_set_bytes(reme_context_t c, reme_volume_t v, const int slice, const void *bytes, int length);

/** \brief Sets the content of a slice ("xy-plane") of the color volume to the given array of bytes.
  *
  * Uploads the given array as slice ("xy-plane") of the color volume content to the device side. Using in combination
  * with ::reme_volume_color_slice_get_bytes one can resume a previously started reconstruction
  * as long as the volume parameters (dimensions) match.
  *
  * The number of slices equals the number of voxels in the z-dimension.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param slice slice id along z-Dimension.
  * \param bytes An array of bytes
  * \param length Number of bytes in the array
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_color_slice_set_bytes(reme_context_t c, reme_volume_t v, const int slice, const void *bytes, int length);

/** \brief Reset the volume to empty state.
  *
  * Forces the volume to clear its content.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_reset(reme_context_t c, reme_volume_t v);

/** \brief Reset the volume to empty state with options.
  *
  * Forces the volume to clear its content.
  *
  * \param c A valid context object
  * \param v A valid volume object
  * \param reset_surface If true resets geometric part of the volume.
  * \param reset_colors If true resets color part of the volume.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_volume_reset_selectively(reme_context_t c, reme_volume_t v, bool reset_surface, bool reset_colors);


/** \} */


/** \ingroup TransformGroup
  * \{
  */

/** \brief Set the matrix to a predefined transform.
  *
  * \param c A valid context object
  * \param t A predefined transform type
  * \param coordinates A pointer to mutable \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_transform_set_predefined(reme_context_t c, reme_transform_t t, float *coordinates);

/** \brief Defines a viewing transformation
  *
  * This method works similarily to gluLookAt. It defines a viewing transformation based on the
  * eye coordinates, a viewing reference point and an up vector. This method simplifies specifying
  * sensor positions (::reme_sensor_set_position).
  *
  * First, the view direction is \c vz is calculated by <tt>vz = ref - eye</tt>. This vector
  * is normalized to unit length <tt>vz = vz / |vz|</tt> and becomes the z-vector
  * of the viewing transformation. Next, the up vector is normalized to unit length <tt>up = up / |up|</tt>.
  *
  * The cross product <tt>vx = -up x vz</tt> will become the x-axis of the viewing transformation after
  * normalization <tt>vx = vx / |vx|</tt>.
  *
  * Finally the cross product of <tt>vy = vz x vx </tt> defines the y-axis of the
  * viewing transformation. The origin of the viewing transformation is set to the eye coordinates.
  *
  * The final matrix becomes
  *
  \verbatim
  | vx.x vy.x vz.x eye.x |
  | vx.y vy.y vz.y eye.y |
  | vx.z vy.z vz.z eye.z |
  |    0    0    0     1 |
  \endverbatim
  *
  * \param c A valid context object
  * \param eye three dimensional vector defining the eye coordinates
  * \param ref three dimensional vector defining the reference point coordinates
  * \param up three dimensional vector defining the up vector
  * \param coordinates A pointer to mutable \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_transform_look_at(reme_context_t c, const float *eye, const float *ref, const float *up, float *coordinates);

/** \brief Compensate a tilt movement
  *
  * Popular 3D scanners such as the Microsoft Kinect and others have a motorized base that allows enlargement
  * of the interaction space by tilting the sensor. These sensors, however, turn of the IR projector while
  * the tilt is in progress, essentially making ReconstructMe blind while the tilt occurs. Since ReconstructMe
  * currently relies on small movements between frames it will often loose track after the tilt completes.
  *
  * This method allows you to compensate for such a blind tilt by specifying +/- tilt angle difference. As
  * most sensors make the tilt relative to the gravitation vector the tilt angle difference can only be calculated
  * accurately for sensors that stand on a fixed platform and are not moved by hand. After tilting it is currently
  * advised to skip a couple of depth frames to compensate wrong data from a recent projector turn-on.
  *
  * This method assumes that the tilt axis is parallel to the sensor positive sensor x-axis. It also assumes
  * that the origin of the tilt movement is placed at roughly (0, 30, -25) with respect to the sensor coordinate
  * system. As such, this compensation will currently only work for Kinect for Windows sensors. While this is
  * an inaccurate measurement and the assumpations are partly wrong, the solution works in most cases as
  * ReconstructMe is able to compensate for the remaining error.
  *
  * Note that you cannot tilt arbitrary large angles as the Kinect limits the tilt-angle to +/- 27 degrees and
  * a large tilt may force a lot of new data to be integrated which could trigger track-lost detection.
  *
  * Note that starting with ReconstructMe 1.4 global registration is added which should be activated for the
  * first frame after the tilt. This will greatly help to improve the tracking.
  *
  * Warning MSDN states that tilting too often can cause damage to the tilt motor.
  *
  * \param c A valid context object
  * \param cur_coordinates Current sensor position before the tilt.
  * \param tilt_angle_diff +/- difference of tilt angles before and after the tilt in degrees. I.e angles moved.
  * \param new_coordinates Updated sensor position to compensate for tilting.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_transform_compensate_tilt(reme_context_t c, const float *cur_coordinates, int tilt_angle_diff, float *new_coordinates);


/** \brief Calculate the relative transform between two coordinate frames.
  *
  * Given two coordinate frames, \a a_t and \a b_t in the
  * same parental coordinate frame, calculate \a b_t with respect to \a a_t.
  * The result is stored in \a c_t.
  *
  * \param c A valid context object
  * \param a_t A pointer to non mutable \ref TransformGroup data.
  * \param b_t A pointer to non mutable \ref TransformGroup data.
  * \param c_t A pointer to mutable \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_transform_make_relative(reme_context_t c, const float *a_t, const float *b_t, float *c_t);

/** \brief Calculate the signed projected angle in radians between two sensor positions in a given plane.
  *
  * Given two coordinate frames, \a a_t and \a b_t this method calculates the signed projected angle in the
  * plane through the origin given by the unit length \a plane_normal. The resulting \a angle is returned
  * in the interval [-PI, PI].  This method only takes the positional offset between the two frames into
  * account and ignores its orientation.
  *
  * Use this method to determine when the sensor has turned a specific amount around a given axis. To do so,
  * you would pass \a plane_normal the rotation axis of interest, \a a_t the previous sensor position and \a
  * b_t the current sensor position. By accumulating the resulting angles you are able to detect when a full
  * rotation is complete (i.e fabs(sum(angles)) > 2*PI)
  *
  * \param c A valid context object
  * \param plane_normal Immutable pointer to plane normal. Normal is expected as array of 4 floating point values <code>x y z w</code>.
  * \param a_t A pointer to non mutable \ref TransformGroup data.
  * \param b_t A pointer to non mutable \ref TransformGroup data.
  * \param angle Resulting angle.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_transform_get_projected_angle(reme_context_t c, const float *plane_normal, const float *a_t, const float *b_t, float *angle);

/** \brief Invert the given transformation.
  *
  * \param c A valid context object
  * \param m_t A pointer to non mutable \ref TransformGroup data.
  * \param inv_t A pointer to mutable \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_transform_invert(reme_context_t c, const float *m_t, float *inv_t);

/** \} */


/** \ingroup SensorGroup
  * \{
  */

/** \brief Create a new sensor object.
  *
  * Creates a new sensor. The \em driver argument specifies which sensor to open.
  * The following sensor drivers are currently available
  *
  * - \em mskinect Microsoft Kinect for Windows and Kinect for XBox
  * - \em openni Asus Xtion, Asus Xtion Pro Live, Primsense Carmine 1.08, Primesense Carmine 1.09
  * - \em file A generic file sensor to read previously recorded data
  * - \em external A generic external sensor whose data is provided from the caller.
  *
  * You might specify a specific driver backend
  * \code "openni" \endcode
  *
  * Alternatively you can specify a list of drivers to test, in which case it will return the first sensor that works.
  * \code "openni;mskinect;file" \endcode
  *
  * Or, specify file containing a sensor configuration file (see ::reme_sensor_bind_camera_options for camera
  * specific options and \ref OptionsPage for background information about options)
  * \code "c:/drivers/asus_xtion_pro_live.txt;c:/drivers/my_file.txt" \endcode
  *
  * The drivers will be tested in the given order.
  *
  * Set \em require_can_open to true to ensure the created sensor can be created
  * and opened using either the default settings, or if file paths are specifed using
  * the settings specified in the file.
  *
  * No matter how \em require_can_open is set the sensor is returned in closed state.
  * Use ::reme_sensor_open to open it.
  *
  * \warning \em require_can_open set to true can lead to longer sensor opening times, because the sensor
  * is tested. If you know what sensor you are opening set it to false.
  *
  * \warning \em require_can_open can lead to deadlocks when using 'mskinect' due to fast opening and closing
  * of the sensor.
  *
  * \param c A valid context object
  * \param driver The name of sensor driver to instance a sensor from
  * \param require_can_open Ensures that the returned sensor can be opened using either the default
  *                         sensor options.
  * \param s A pointer that will receive the handle of the created sensor
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_create(reme_context_t c, const char *driver, bool require_can_open, reme_sensor_t *s);

/** \brief Destroy a previously created sensor object.
  *
  * \param c A pointer to a valid context object
  * \param s A mutable pointer to a valid sensor handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_destroy(reme_context_t c, reme_sensor_t *s);

/** \brief Open a sensor
  *
  * Attempts to opens the specified sensor using the specified sensor options.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_open(reme_context_t c, reme_sensor_t s);

/** \brief Close a an open sensor
  *
  * Indicates that no more grabbing is done from sensor. Re-opening a sensor
  * is possible.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_close(reme_context_t c, reme_sensor_t s);

/** \brief Set the working volume
  *
  * The sensor will use this volume to keep track of its position and it will also
  * update into this volume. By default the sensor is assigned to the first volume
  * available.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param v A valid volume object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_set_volume(reme_context_t c, reme_sensor_t s, reme_volume_t v);

/** \brief Set tracking mode.
  *
  * Sets the overall tracking strategy. By default ::REME_SENSOR_TRACKMODE_AUTO is used.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param t A valid tracking mode
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_set_trackmode(reme_context_t c, reme_sensor_t s, reme_sensor_trackmode_t t);

/** \brief Sets a tracking hint.
  *
  * The tracking hint is an external user supplied information to support the camera tracking module. Any
  * tracking hint given remains active until the next call to ::reme_sensor_track_position.
  *
  * Supplying tracking hints becomes useful when the caller has external knowledge unknown to the tracking
  * module. For example the caller might set ::REME_SENSOR_TRACKHINT_USE_GLOBAL to indicate that the tracking
  * module is should resort to global tracking in the next iteration.
  *
  * Tracking hints are automatically cleared after the next call to ::reme_sensor_track_position.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param t A valid tracking hint
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_set_trackhint(reme_context_t c, reme_sensor_t s, reme_sensor_trackhint_t t);

/** \brief Access the sensor specific options that affect how the camera is opened.
  *
  * \par Associated Protocol Buffers Specification
  * Depending on the sensor chosen on create, different specs are needed, since each
  * sensor supports a different set of parameters.
  *
  * For \em openni sensors (OpenNI 2.x)
  * \include openni2_sensor_config.proto
  *
  * For \em mskinect sensors
  * \include mskinect_sensor_config.proto
  *
  * For \em file sensors
  * \include file_sensor_config.proto
  *
  * For \em external sensors
  * \include external_sensor_config.proto
  *
  * Common to all configurations above is the usage of the LibRGBDSensor.videostream
  *
  * \include videostream.proto
  *
  * The referenced LibRGBDSensor.intrinsics has the following layout
  *
  * \include intrinsics.proto
  *
  * \note When radial or tangential distortion parameters are not equal zero a distortion correction will be performed.
  * \note Changing camera options take effect on the next call to ::reme_sensor_open.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_bind_camera_options(reme_context_t c, reme_sensor_t s, reme_options_t o);

/** \brief Access the sensor specific capture options with their current values.
  *
  * \par Associated Protocol Buffers Specification
  *
  * Depending on the sensor chosen on create, different specs are needed, since each
  * sensor supports a different set of parameters.
  *
  * For \em openni sensors
  * \include openni2_sensor_capture_parameter.proto
  *
  * For \em mskinect sensors
  * \include mskinect_sensor_capture_parameter.proto
  *
  * For \em file sensors
  * \include file_sensor_capture_parameter.proto
  *
  * Common to all configurations above is the \em frame_info field. It is mendatory for reconstruction and has the
  * following structure
  *
  * \include basic_frame_support.proto
  *
  * \note The capture options are updated with current value when ::reme_sensor_bind_capture_options is called.
  * \note Changing capture options without a call to ::reme_sensor_apply_capture_options has no effect.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_bind_capture_options(reme_context_t c, reme_sensor_t s, reme_options_t o);

/** \brief Apply capture options.
  *
  * Causes all capture options set to be applied at given sensor. In order to set only specific options,
  * invoke ::reme_options_clear on the options target before setting the new values. Then invoke
  * ::reme_sensor_apply_capture_options.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_apply_capture_options(reme_context_t c, reme_sensor_t s, reme_options_t o);

/** \brief Access the sensor specific render options.
  *
  * These options define how sensor images are rendered. Use ::reme_sensor_apply_render_options to apply
  * value changes.
  *
  * \par Associated Protocol Buffers Specification
  * \include render_options.proto
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_bind_render_options(reme_context_t c, reme_sensor_t s, reme_options_t o);

/** \brief Apply render options.
  *
  * Causes all render options to be applied at given sensor.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_apply_render_options(reme_context_t c, reme_sensor_t s, reme_options_t o);

/** \brief Get the sensor position with respect to the world coordinate frame.
  *
  * Initially this is set to identity for all sensors. The position is modified
  * when ::reme_sensor_track_position succeeds, or ::reme_sensor_set_position is called.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param coordinates A constant pointer to constant \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_get_position(reme_context_t c, reme_sensor_t s, float *coordinates);

/** \brief Get the sensor recovery position with respect to the world coordinate frame.
  *
  * Whenever the sensor cannot find track, it puts itself into recovery pose. It then
  * waits in the recovery pose for tracking to succeed. The recovery pose will be updated
  * during ongoing tracking automatically. I.e when there is sufficient confidence that
  * the last n-frames where tracked successfully, ReconstructMe generates a new recovery pose.
  *
  * Initially this is set to identity for all sensors. The position is modified
  * when ::reme_sensor_track_position succeeds several times,
  * or ::reme_sensor_set_recovery_position is called.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param coordinates A constant pointer to constant \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_get_recovery_position(reme_context_t c, reme_sensor_t s, float *coordinates);

/** \brief Get the incremental movement of the sensor.
  *
  * When reme_sensor_track_position succeeds this position reflects the
  * movement of the sensor between the last position of the sensor and
  * the current position of the sensor.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param coordinates A constant pointer to pre-allocated \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_get_incremental_position(reme_context_t c, reme_sensor_t s, float *coordinates);

/** \brief Calculate a predefined sensor position with respect to the volume.
  *
  * This method calculates a sensor position based on the value of ::reme_sensor_position_t. Depending on the choice of
  * ::reme_sensor_position_t, this method makes use the the attached volume and/or the last sensor depth-map.
  *
  * The meaning of ::reme_sensor_position_t is as follows:
  *  - ::REME_SENSOR_POSITION_INFRONT Assume without loss of generality that the sensor held horizontally pointing towards the target.
  *                                   Then the position is chosen so that z-axis of the world coordinate is the natural up-direction,
  *                                   the sensor looks towards the positive y-axis of the world coordinate system, the sensor is located at
  *                                   the center of the front face of the reconstruction volume and is moved back (negative y-axis) by 300 units.
  *  - REME_SENSOR_POSITION_CENTER    The sensor is placed in the center of the volume.
  *  - REME_SENSOR_POSITION_FLOOR     The sensor is placed such that the volume is pinned to the floor according to ::reme_sensor_find_floor. This type
  *                                   makes use of the current depth-map to determine the floor.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param t Type of predefined position to set
  * \param coordinates A pointer to pre-allocated \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_NO_FLOOR If no floor is found in the current sensor's depthmap
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_get_prescan_position(reme_context_t c, reme_sensor_t s, reme_sensor_position_t t, float *coordinates);

/** \brief Set the sensor position with respect to the world coordinate frame.
  *
  * Initially this is set to identity for all sensors.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param coordinates A pointer to constant \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_set_position(reme_context_t c, reme_sensor_t s, const float *coordinates);


/** \brief Set the incremental movement of the sensor.
  *
  * Updates the world position of the sensor by the incremental position specified.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param coordinates A pointer to constant \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_set_incremental_position(reme_context_t c, reme_sensor_t s, const float *coordinates);

/** \brief Set the sensor recovery position with respect to the world coordinate frame.
  *
  * Whenever the sensor cannot find track, it puts itself into recovery pose. It then
  * waits in the recovery pose for tracking to succeed. The recovery pose will be updated
  * during ongoing tracking automatically. I.e when there is sufficient confidence that
  * the last n-frames where tracked successfully, ReconstructMe generates a new recovery pose.
  *
  * Initially this is set to identity for all sensors. The position is modified
  * when ::reme_sensor_track_position succeeds several times,
  * or ::reme_sensor_set_recovery_position is called.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param coordinates A constant pointer to constant \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_set_recovery_position(reme_context_t c, reme_sensor_t s, const float *coordinates);

/** \brief Position the sensor and volume with respect to each other using a predefined position.
  *
  * Initially the sensor position is identity for all sensors. By calling this method the sensor
  * position and recovery position change to an auto-calculated sensor position based on the value of
  * ::reme_sensor_position_t.
  *
  * This method is considered a helper method consisting of the following steps:
  *  - ::reme_sensor_get_prescan_position
  *  - ::reme_sensor_set_position
  *  - ::reme_sensor_set_recovery_position
  *
  * Please refer to ::reme_sensor_get_prescan_position for an in-depth explanation of ::reme_sensor_position_t choices.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param t Type of predefined position to set
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_NO_FLOOR If no floor is found in the current sensor's depthmap
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_set_prescan_position(reme_context_t c, reme_sensor_t s, reme_sensor_position_t t);

/** \brief Resets the sensor to identity position.
  *
  * Forces the sensor to loose track.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \retval ::REME_ERROR_SUCCESS On tracking success or the corresponding volume is empty.
  * \retval ::REME_ERROR_UNSPECIFIED is returned otherwise.
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_reset(reme_context_t c, reme_sensor_t s);

/** \brief Get a specific sensor image.
  *
  * Each sensor might provide different frame types. Not all sensors support all frames, or the number of frames
  * supported is configuration dependant. See reme_sensor_image_t for a complete enumeration of available image types.
  *
  * \par Memory Management Rules Exception
  *
  * The returned image remains valid until the sensor is destroyed or the dimension of the image changes.
  * The pointer is recycled internally, which means that it will point to different values
  * each time the sensor images are updated.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param it Image type to access
  * \param i A valid image object to receive image data
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_get_image(reme_context_t c, reme_sensor_t s, reme_sensor_image_t it, reme_image_t i);

/** \brief Test if a specific image type is available.
  *
  * Each sensor might provide different frame types. Not all sensors support all frames, or the number of frames
  * supported is configuration dependant. See reme_sensor_image_t for a complete enumeration of available image types.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param it Image type to access
  * \param result Whether image type is supported or not.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_is_image_supported(reme_context_t c, reme_sensor_t s, reme_sensor_image_t it, bool *result);

/** \brief Get points corresponding to the current sensor view.
  *
  * Depending on the choice of \c v (::reme_sensor_view_t) this returns
  *  - ::REME_SENSOR_VIEW_RAW the raw sensor points generated from the last invocation of ::reme_sensor_prepare_images or
  *    ::reme_sensor_prepare_image with argument ::REME_IMAGE_VOLUME.
  *  - ::REME_SENSOR_VIEW_RECONSTRUCTED the synthetic raytraced sensor points generated from the last invocation of ::reme_sensor_prepare_images or
  *    ::reme_sensor_prepare_image with argument ::REME_IMAGE_VOLUME.
  *
  * The points are represented as an array of floats where each point consists of 4 coordinates <code> Px Py Pz Pw Px Py Pz Pw ... </code>.
  * The \c w component is always zero. The i-th point starts at index <code> i * 4 </code> of coordinate array returned.
  *
  * The number of points returned corresponds to the number of pixels of the native sensor. That is, if your sensor has a resolution
  * of 640x480 (cols x rows) the number of returned normals is 640 * 480. The normals are returned in row-wise order. Those points that do not represent
  * a valid data are marked with a sentinel value (NAN) in their x-coordinate. To access the point corresponding to pixel of row \c i and column
  * \c j use <code>i * cols * 4 + j * 4</code> where \c cols is the number of pixel columns of the native sensor.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param v view type specification
  * \param coordinates A mutable pointer to constant point data.
  * \param length The number of coordinates returned. To get the number of points divide this value by 4.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_get_points(reme_context_t c, reme_sensor_t s, reme_sensor_view_t v, const float **coordinates, int *length);

/** \brief Get point normals corresponding to the current sensor view.
  *
  * Depending on the choice of \c v (::reme_sensor_view_t) this returns
  *  - ::REME_SENSOR_VIEW_RAW the raw sensor normals generated from the last invocation of ::reme_sensor_prepare_images or
  *    ::reme_sensor_prepare_image with argument ::REME_IMAGE_VOLUME.
  *  - ::REME_SENSOR_VIEW_RECONSTRUCTED the synthetic raytraced sensor normals generated from the last invocation of ::reme_sensor_prepare_images or
  *    ::reme_sensor_prepare_image with argument ::REME_IMAGE_VOLUME.
  *
  * The point normals are represented as an array of floats where each point
  * consists of 4 coordinates <code> Px Py Pz Pw Px Py Pz Pw ... </code>. The \c w component is always zero.
  * The i-th normal starts at index <code> i * 4 </code> of coordinate array returned.
  *
  * The number of normals returned corresponds to the number of pixels of the native sensor. That is, if your sensor has a resolution
  * of 640x480 (cols x rows) the number of returned normals is 640 * 480. The normals are returned in row-wise order. Those normals that do not represent
  * a valid data are marked with a sentinel value (NAN) in their x-coordinate. To access the normal corresponding to pixel of row \c i and column
  * \c j use <code>i * cols * 4 + j * 4</code> where \c cols is the number of pixel columns of the native sensor.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param v view type specification
  * \param coordinates A mutable pointer to constant normal data.
  * \param length The number of coordinates returned. To get the number of normals divide this value by 4.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_get_point_normals(reme_context_t c, reme_sensor_t s, reme_sensor_view_t v, const float **coordinates, int *length);

/** \brief Get point colors corresponding to the current sensor view.
  *
  * Depending on the choice of \c v (::reme_sensor_view_t) this returns
  *  - ::REME_SENSOR_VIEW_RAW the raw sensor colors generated from the last invocation of ::reme_sensor_prepare_images or
  *    ::reme_sensor_prepare_image with argument ::REME_IMAGE_VOLUME.
  *  - ::REME_SENSOR_VIEW_RECONSTRUCTED the synthetic raytraced sensor colors generated from the last invocation of ::reme_sensor_prepare_images or
  *    ::reme_sensor_prepare_image with argument ::REME_IMAGE_VOLUME.
  *
  * Colors are only available if the current compiled context supports colorization of vertices.
  *
  * The point colors are represented as an array of floats where each color consists of 4 channels <code> r g b a r g b a ... </code>.
  * The \c a component is always zero. The i-th color starts at index <code> i * 4 </code> of array returned. The range for each channel is [0..1].
  *
  * The number of colors returned corresponds to the number of pixels of the native sensor. That is, if your sensor has a resolution
  * of 640x480 (cols x rows) the number of returned colors is 640 * 480. The colors are returned in row-wise order. To access the color corresponding
  * to pixel of row \c i and column \c j use <code>i * cols * 4 + j * 4</code> where \c cols is the number of pixel columns of the native sensor.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param v view type specification
  * \param channels A mutable pointer to constant color data.
  * \param length The number of channels returned. To get the number of colors divide this value by 4.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_NO_COLOR_SUPPORT if no color is available.
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_get_point_colors(reme_context_t c, reme_sensor_t s, reme_sensor_view_t v, const float **channels, int *length);

/** \brief Get the tracking time
  *
  * The tracking time corresponds to the number of frames in which
  * tracking succeeded. In case tracking fails the counter gets negative.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param track_time The tracking time
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_get_track_time(reme_context_t c, reme_sensor_t s, int *track_time);

/** \brief Trigger frame grabbing.
  *
  * Provides a synchronization point to trigger image generation of
  * all image types. This method is intended to be fast.
  *
  * In order to synchronize frame grabbing from multiple sensors,
  * call this method in sequence for each sensor before calling
  * reme_sensor_retrieve.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_FAILED_TO_GRAB Failed to grab from sensor. This is not necessarily an error, you might re-try.
  * \retval ::REME_ERROR_UNSPECIFIED Is returned otherwise.
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_grab(reme_context_t c, reme_sensor_t s);

/** \brief Retrieve image data corresponding to the previous grab command for further processing
  *
  * Updates the internal state of all images and prepares the required data structures on the
  * computation device.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_prepare_images(reme_context_t c, reme_sensor_t s);

/** \brief Retrieve specific image data for subsequent processing.
  *
  * In case REME_IMAGE_AUX or REME_IMAGE_DEPTH is passed, this method will fetch the data into internal memory. In case
  * REME_IMAGE_VOLUME is passed, the previously prepared REME_IMAGE_DEPTH will be uploaded to the computation device for
  * subsequent processing (::reme_sensor_track_position, ::reme_sensor_update_volume).
  *
  * This method is especially useful (when compared to ::reme_sensor_prepare_images) when only depth and image data is
  * required. For example when recording, there is no need for REME_IMAGE_VOLUME and it should be skipped so no time
  * is wasted waiting for the data to be uploaded to the computation device.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param i Image type to prepare
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_prepare_image(reme_context_t c, reme_sensor_t s, _reme_sensor_image_t i);

/** \brief Attempts to track the sensor position.
  *
  * Tries to track the sensor movement by matching the current depth data
  * against the perspective from the last position. Initially the sensor position
  * is the identity position, unless otherwise specified.
  *
  * The tracking behaviour is affected by the tracking strategy (::reme_sensor_set_trackmode) and any external
  * tracking hint (::reme_sensor_set_trackhint). Any tracking hint will be cleared after calling this method.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \retval ::REME_ERROR_SUCCESS On tracking success or the corresponding volume is empty.
  * \retval ::REME_ERROR_TRACK_LOST When the tracking did not succeed. In this case the sensor is repositioned
  *         into latest recovery pose.
  * \retval ::REME_ERROR_UNSPECIFIED is returned otherwise.
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_track_position(reme_context_t c, reme_sensor_t s);

/** \brief Update the volume using the current sensor data
  *
  * Uses the current sensor position as the perspective to update the volume. If color support
  * is enabled this method will also update the colors. Use ::reme_sensor_update_volume_selectively
  * to change that behaviour.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_update_volume(reme_context_t c, reme_sensor_t s);

/** \brief Update the volume using the current sensor data selectively.
  *
  * Uses the current sensor position as the perspective to update the volume.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param update_surface If true updates geometric part of the volume.
  * \param update_colors If true updates color part of the volume.
  * \param s A valid sensor object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_NO_COLOR_SUPPORT When \a update_colors is selected but color support is disabled.
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_update_volume_selectively(reme_context_t c, reme_sensor_t s, bool update_surface, bool update_colors);

/** \brief Detect floor plane in current sensor data.
  *
  * This method attempts to detect the floor plane in the current sensor data. It
  * uses the sensor's depth data from the last invocation of ::reme_sensor_prepare_images or
  * ::reme_sensor_prepare_image with ::REME_IMAGE_DEPTH as input and if successful returns
  * a coordinate system of the floor with respect to the sensor coordinate system.
  *
  * The algorithm works best when a large portion of the image is covered by floor data and
  * the sensor is held without roll (i.e no rotation around the sensor's z-axis). Note vertical front facing
  * walls can be detected erroneously as floors if the make up the major part of the sensor image.
  *
  * The floor is returned as a coordinate frame with the following properties:
  *  - the origin is located at the intersection of the sensor view direction and the estimated floor plane
  *  - the z-axis is normal to to the floor plane and points towards the natural ceiling
  *  - the x-axis is aligned with the sensor's x-axis
  *  - the y-axis is formed by the cross product of the former two axes.
  *
  * \param c A valid context object
  * \param s A valid sensor object
  * \param coordinates A constant pointer to constant \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_NO_FLOOR If no floor is found in the current sensor's depth-map
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_sensor_find_floor(reme_context_t c, reme_sensor_t s, float *coordinates);

/** \} */

/** \ingroup RecorderGroup
  * \{
  */

/** \brief Create a new sensor recorder object.
  *
  * \param c A valid context object
  * \param r A pointer that will receive the handle of the created recorder
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_recorder_create(reme_context_t c, reme_recorder_t *r);

/** \brief Destroy a previously created recorder object.
  *
  * \param c A pointer to a valid context object
  * \param r A mutable pointer to a valid recorder handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_recorder_destroy(reme_context_t c, reme_recorder_t *r);

/** \brief Set the sensor to record from
  *
  * The recorder will use the given sensor to stream data from. It will also
  * copy the sensors' intrinsics to the resulting file sensor configuration file,
  * so replaying from this sensor uses the correct camera intrinsics.
  *
  * By default the recorder streams from the first sensor.
  *
  * \param c A valid context object
  * \param r A valid recorder object
  * \param s A valid sensor object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_recorder_set_sensor(reme_context_t c, reme_recorder_t r, reme_sensor_t s);

/** \brief Access the recorder specific file options.
  *
  * \par Associated Protocol Buffers Specification
  * \include recorder_options.proto
  *
  * \param c A valid context object
  * \param r A valid recorder object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_recorder_bind_file_options(reme_context_t c, reme_recorder_t r, reme_options_t o);

/** \brief Open the recorder for streaming
  *
  * This will force existing files to be overridden.
  *
  * \param c A valid context object
  * \param r A valid recorder object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_recorder_open(reme_context_t c, reme_recorder_t r);

/** \brief Update the associated file streams with the current sensor content.
  *
  * \param c A valid context object
  * \param r A valid recorder object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_recorder_update(reme_context_t c, reme_recorder_t r);

/** \brief Close the recorder file streams
  *
  * Closes the file streams.
  *
  * \param c A valid context object
  * \param r A valid recorder object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_recorder_close(reme_context_t c, reme_recorder_t r);

/** \} */

/** \ingroup ImageGroup
  * \{
  */

/** \brief Create a new empty image object.
  *
  * \param c A valid context object
  * \param i A pointer that will receive the handle of the created image
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_image_create(reme_context_t c, reme_image_t *i);

/** \brief Destroy a previously created image object.
  *
  * \param c A pointer to a valid context object
  * \param i A mutable pointer to a valid image handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_image_destroy(reme_context_t c, reme_image_t *i);

/** \brief Get image information such as size, channels and layout.
  *
  * You can pass a zero pointer for those fields you are not interested in.
  *
  * \param c A valid context object
  * \param i A valid image object
  * \param width Width of image in pixels
  * \param height Height of image in pixels
  * \param num_channels Number of channels per pixel
  * \param num_bytes_per_channel Number of bytes per channel
  * \param row_stride Distance between successive rows in bytes
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_image_get_info(reme_context_t c, reme_image_t i, int *width = 0, int *height = 0,
                                 int *num_channels = 0, int *num_bytes_per_channel = 0, int *row_stride = 0);

/** \brief Save the image in the desired format.
  *
  * The exporter is chosen based on the file extension. Currently supported are
  * - \b .PNG - Portable Network Graphics
  * - \b .BMP - Windows Bitmap
  * - \b .JPG - Jpeg
  *
  * \param c A valid context object
  * \param i A valid image object
  * \param filename path to save image to
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_image_save_to_file(reme_context_t c, reme_image_t i, const char *filename);

/** \brief Load image from disk.
  *
  * The importer is chosen based on the file extension. Currently supported are
  * - \b .PNG - Portable Network Graphics
  * - \b .BMP - Windows Bitmap
  * - \b .JPG - Jpeg
  *
  * \param c A valid context object
  * \param i A valid image object
  * \param filename path to save image to
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_image_load_from_file(reme_context_t c, reme_image_t i, const char *filename);

/** \brief Get image pixel data as byte array
  *
  * \param c A valid context object
  * \param i A valid image object
  * \param pixels A mutable pointer that will receive the address of pixel array
  * \param length A pointer that will receive the length of the array in bytes (use ::reme_image_get_info to derive the correct format)
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_image_get_bytes(reme_context_t c, reme_image_t i, const void **pixels, int *length);

/** \brief Get mutable image pixel data as byte array
  *
  * \param c A valid context object
  * \param i A valid image object
  * \param pixels A mutable pointer that will receive the address of pixel array
  * \param length A pointer that will receive the length of the array in bytes (use ::reme_image_get_info to derive the correct format)
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_image_get_mutable_bytes(reme_context_t c, reme_image_t i, void **pixels, int *length);

/** \} */

/** \ingroup CalibrationGroup
  * \{
  */

/** \brief Create a new calibration object.
  *
  * \param c A valid context object
  * \param cb A pointer that will receive the handle of the created calibration object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_calibrator_create(reme_context_t c, reme_calibrator_t *cb);

/** \brief Destroy a previously created calibrator object.
  *
  * \param c A pointer to a valid context object
  * \param cb A mutable pointer to a valid calibrator handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_calibrator_destroy(reme_context_t c, reme_calibrator_t *cb);

/** \brief Access the calibration options.
  *
  * \par Associated Protocol Buffers Specification
  * \include calibration_options.proto
  *
  * The calibration options are applied when the first image is added (::reme_calibrator_add_image).
  *
  * \param c A valid context object
  * \param cb A valid calibration object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_calibrator_bind_options(reme_context_t c, reme_calibrator_t cb, reme_options_t o);

/** \brief Add a new image of the calibration target.
  *
  * To receive the best results
  *  - Make sure the calibration target covers most of the image.
  *  - Make sure to supply images taken from different angles.
  *  - Supply between 10 - 20 images.
  *
  * \param c A valid context object
  * \param cb A valid calibration object
  * \param i A valid image object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_NO_CALIBRATION_TARGET When the calibration target was not found in the image supplied.
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_calibrator_add_image(reme_context_t c, reme_calibrator_t cb, reme_image_t i);

/** \brief Receives the result image of the last image added.
  *
  * \param c A valid context object
  * \param cb A valid calibration object
  * \param i A valid image object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_calibrator_get_detection_image(reme_context_t c, reme_calibrator_t cb, reme_image_t i);

/** \brief Calibrate using the images added before.
  *
  * The result of a successful calibration is are new intrinsic settings. Use
  *
  * \param c A valid context object
  * \param cb A valid calibration object
  * \param reprojection_error If not null, the reprojection error of the calibration.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_calibrator_calibrate(reme_context_t c, reme_calibrator_t cb, float *reprojection_error = 0);

/** \brief Access the calibration results.
  *
  * The results are provided as a new intrincis options set.
  *
  * \par Associated Protocol Buffers Specification
  * \include intrinsics.proto
  *
  * \param c A valid context object
  * \param cb A valid calibration object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_calibrator_bind_intrinsics(reme_context_t c, reme_calibrator_t cb, reme_options_t o);

/** \} */


/** \ingroup SurfaceGroup
  * \{
  */

/** \brief Create a new surface object.
  *
  * \param c A valid context object
  * \param s A pointer that will receive the handle of the created surface
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_create(reme_context_t c, reme_surface_t *s);

/** \brief Destroy a previously created surface object.
  *
  * \param c A pointer to a valid context object
  * \param s A mutable pointer to a valid surface handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_destroy(reme_context_t c, reme_surface_t *s);

/** \brief Access the surface generation options.
  *
  * \par Associated Protocol Buffers Specification
  * \snippet surface_generation_options.proto Surface Generation
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_bind_generation_options(reme_context_t c, reme_surface_t s, reme_options_t o);

/** \brief Access the poisson reconstruction options.
  *
  * \par Associated Protocol Buffers Specification
  * \snippet surface_generation_options.proto Poisson Reconstruction
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_bind_poisson_options(reme_context_t c, reme_surface_t s, reme_options_t o);

/** \brief Access the surface decimation options.
  *
  * \par Associated Protocol Buffers Specification
  * \snippet surface_generation_options.proto Mesh Decimation
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_bind_decimation_options(reme_context_t c, reme_surface_t s, reme_options_t o);

/** \brief Access the surface remeshing options.
  *
  * \par Associated Protocol Buffers Specification
  * \snippet surface_generation_options.proto Mesh Remeshing
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_bind_remesh_options(reme_context_t c, reme_surface_t s, reme_options_t o);

/** \brief Access the surface cleanup options.
  *
  * \par Associated Protocol Buffers Specification
  * \snippet surface_generation_options.proto Mesh Cleanup
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param o A valid options binding object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  *
  * \ingroup AvailableOptionSets
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_bind_cleanup_options(reme_context_t c, reme_surface_t s, reme_options_t o);

/** \brief Extract the iso-surface from the given volume.
  *
  * The surface is generated with respect to the world coordinate system.
  *
  * In case you are using an unlicensed version of ReconstructMe SDK, this
  * function blocks for at least 15 seconds. Without this limitation the
  * mesh is usually generated in under a second.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param v A valid volume object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_generate(reme_context_t c, reme_surface_t s, reme_volume_t v);

/** \brief Perform poisson reconstruction on the extracted surface.
  *
  * Use ::reme_surface_bind_poisson_options to control the decimation process.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_poisson(reme_context_t c, reme_surface_t s);

/** \brief Decimate the extracted surface.
  *
  * Use ::reme_surface_bind_decimation_options to control the decimation process.
  * If the input mesh has vertex colors those will be respected in the remesh process.
  *
  * Note that after the decimation vertex colors will be incorrect. You should generate them again
  * using ::reme_surface_colorize_vertices and ::reme_surface_inpaint_vertices.
  *
  * In contrast to ::reme_surface_remesh this function only reduces the number of faces and does
  * not generate an isotropic surface.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_decimate(reme_context_t c, reme_surface_t s);

/** \brief Remesh the extracted surface.
  *
  * Attempts to create an isotropic surface. Isotropic remeshing of surfaces tries to resample the surface
  * to obtain a triangle tesselation, where the shape of each triangle is not biased in a particular direction
  * (isotropy).
  *
  * Use ::reme_surface_bind_remesh_options to control the remeshing process.
  * If the input mesh has vertex colors those will be respected in the remesh process.
  *
  * Note that after the remesh vertex colors will be incorrect. You should generate them again
  * using ::reme_surface_colorize_vertices and ::reme_surface_inpaint_vertices.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_remesh(reme_context_t c, reme_surface_t s);

/** \brief Cleanup the extracted surface.
  *
  * Removes small unconnected components from the given surface. See ::reme_surface_bind_cleanup_options
  * for usable parameters.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_cleanup(reme_context_t c, reme_surface_t s);

/** \brief Transform the surface.
  *
  * This will transform the points and normals of the surface.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param coordinates A pointer to constant \ref TransformGroup data.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_transform(reme_context_t c, reme_surface_t s, const float *coordinates);

/** \brief Colorize surface vertices using the color information stored in the reconstruction volume.
  *
  * Colorizes all vertices of the given surface. Before calling this method you need to at least
  * generate a surface using ::reme_surface_generate. It's possible to use a modified version of the surface.
  * E.g you can even pass a poisson-reconstructed surface.
  *
  * Vertices with missing color information receive a unique color which is currently green (in RGBA: 0/255/0/0).
  * Use the ::reme_surface_inpaint_vertices to generate missing vertex colors.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param v A valid volume object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_NO_COLOR_SUPPORT Setup does not support colors.
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_colorize_vertices(reme_context_t c, reme_surface_t s, reme_volume_t v);

/** \brief Paint missing vertex colors.
  *
  * Vertices without a valid vertex color will be painted by an algorithm that tries to use surrounding color
  * information. A vertex is said to have no color or an invalid color if the color is exactly green
  * (in RGBA: 0/255/0/0).
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_NO_COLOR_SUPPORT Setup does not support colors.
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_inpaint_vertices(reme_context_t c, reme_surface_t s);

/** \brief Get points of a surface.
  *
  * The surface points are represented as an array of floats where each point
  * consists of 4 coordinates <code> Px Py Pz Pw Px Py Pz Pw ... </code>.
  * The \em w component is always zero.
  *
  * Note the i-th point starts at index <code> i * 4 </code> of coordinate array returned.
  *
  * \par Memory Management Rules Exception
  *
  * The returned \em coordinates pointer remains valid until the mesh changes.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param coordinates A mutable pointer to constant point data.
  * \param length The number of coordinates returned. To get the number of points divide this value by 4.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_get_points(reme_context_t c, reme_surface_t s, const float **coordinates, int *length);

/** \brief Get point normals of a surface.
  *
  * The surface point normals are represented as an array of floats where each point
  * consists of 4 coordinates <code> Px Py Pz Pw Px Py Pz Pw ... </code>.
  * The \em w component is always zero.
  *
  * Note the i-th point normal starts at index <code> i * 4 </code> of coordinate array returned.
  *
  * \par Memory Management Rules Exception
  *
  * The returned \em coordinates pointer remains valid until the mesh changes.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param coordinates A mutable pointer to constant point normal data.
  * \param length The number of coordinates returned. To get the number of point normals divide this value by 4.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_get_normals(reme_context_t c, reme_surface_t s, const float **coordinates, int *length);

/** \brief Get colors of surface vertices.
  *
  * The surface vertex colors are represented as an array of floats where each color
  * consists of 4 coordinates <code> R G B A R G B A ... </code>. The \em A component is always zero.
  * The range of each channel is between zero and one.
  *
  * Note the i-th color starts at index <code> i * 4 </code> of coordinate array returned. The returned
  * array might be empty if no colors are have been generated through ::reme_surface_colorize_vertices
  * or colors are not supported by the current setup. Vertices that don't have a valid color will carry
  * an invalid color represented as <code> 0 1 0 0 </code>.
  *
  * \par Memory Management Rules Exception
  *
  * The returned \em coordinates pointer remains valid until the mesh changes.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param coordinates A mutable pointer to constant color data.
  * \param length The number of coordinates returned. To get the number of colors divide this value by 4.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_get_vertex_colors(reme_context_t c, reme_surface_t s, const float **coordinates, int *length);

/** \brief Get triangle faces of a surface.
  *
  * The triangle faces are represented as an array of unsigned integers (point indices) where each triangle
  * consists of 3 indices that represent that points that make up each face <code> P0 P1 P2 P0 P1 P2 ... </code>.
  *
  * Note the i-th triangle starts at index <code>i * 3</code> of index array returned.
  *
  * \par Memory Management Rules Exception
  *
  * The returned \em indices pointer remains valid until the mesh changes.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param indices A mutable pointer to constant triangle index data.
  * \param length The number of indices returned. To get the number of triangles divide this value by 3.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_get_triangles(reme_context_t c, reme_surface_t s, const unsigned int **indices, int *length);

/** \brief Export the surface to file
  *
  * The exporter is chosen based on the file extension. Currently supported are
  * - \b .PLY - Polygon File Format
  * - \b .STL - StereoLithography
  * - \b .OBJ - Wavefront
  * - \b .3DS - 3D Studio Max
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param filename Filename to save mesh as
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_save_to_file(reme_context_t c, reme_surface_t s, const char *filename);

/** \brief Import surface from file
  *
  * The importer is chosen based on the file extension. Currently supported are
  * - \b .PLY - Polygon File Format
  * - \b .STL - StereoLithography
  * - \b .OBJ - Wavefront
  * - \b .3DS - 3D Studio Max
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param filename Filename to load mesh from
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_surface_load_from_file(reme_context_t c, reme_surface_t s, const char *filename);

/** \} */

/** \ingroup ViewingGroup
  * \{
  */

/** \brief Create viewer for viewing multiple images.
  *
  * \param c A valid context object
  * \param title Window title
  * \param v A pointer to the resulting viewer object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_viewer_create_image(reme_context_t c, const char *title, reme_viewer_t *v);

/** \brief Create viewer for specific surface.
  *
  * In order to work properly this method should be called for a non-empty surface.
  *
  * \param c A valid context object
  * \param s A valid surface object
  * \param title Window title
  * \param v A pointer to the resulting viewer object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_viewer_create_surface(reme_context_t c, reme_surface_t s, const char *title, reme_viewer_t *v);

/** \brief Create viewer for specific volume.
  *
  * Directly renders the volume content and allows camera manipulation similar to reme_viewer_create_surface.
  * If colorization is supported, the content is rendered using the recorded colors. Otherwise, the content is
  * rendered using normalmap shading.
  *
  * On average this viewer requires less memory to render than ::reme_viewer_create_surface, plus is can be updated
  * in real-time. This allows real-time visualization of volume changes. By using manipulating the camera position
  * the entire volume can be inspected in real-time.
  *
  * The initial camera position is chosen so that the entire volume (not only its content, but its bounds) is in view.
  * The resolution and the view frustum is defined by the intrinsic parameters delivered by the provided sensor.
  *
  * \param c A valid context object
  * \param vol A valid volume object
  * \param s A valid sensor object
  * \param title Window title
  * \param v A pointer to the resulting viewer object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_viewer_create_volume(reme_context_t c, reme_volume_t vol, reme_sensor_t s, const char *title, reme_viewer_t *v);


/** \brief Destroy a previously created viewer object.
  *
  * \param c A pointer to a valid context object
  * \param v A mutable pointer to a valid viewer handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_viewer_destroy(reme_context_t c, reme_viewer_t *v);

/** \brief Add image to be displayed.
  *
  * \param c A valid context object
  * \param v A valid viewer object
  * \param i A valid image object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_viewer_add_image(reme_context_t c, reme_viewer_t v, reme_image_t i);

/** \brief Update viewer content.
  *
  * Updates the content of the given viewer for a single frame.
  *
  * \param c A valid context object
  * \param v A valid viewer object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_viewer_update(reme_context_t c, reme_viewer_t v);

/** \brief Test if the viewer is closed.
  *
  * \param c A valid context object
  * \param v A valid viewer object
  * \param closed A pointer to a boolean receiving the closed status
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_viewer_is_closed(reme_context_t c, reme_viewer_t v, bool *closed);

/** \brief Update viewer content until the user closes the viewer.
  *
  * Blocks the calling thread until the user closes the viewer.
  *
  * \param c A valid context object
  * \param v A valid viewer object
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_viewer_wait(reme_context_t c, reme_viewer_t v);

/** \} */

/** \ingroup CSGGroup
  * \{
  */

/** \brief Create a new CSG module for performing boolean set operations.
  *
  * \param c A valid context object
  * \param v A valid volume object to work on
  * \param csg A pointer to receive the created CSG object handle.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_csg_create(reme_context_t c, reme_volume_t v, reme_csg_t *csg);

/** \brief Destroy a previously created CSG object.
  *
  * \param c A pointer to a valid context object
  * \param csg A mutable pointer to a valid CSG handle to destroy
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_csg_destroy(reme_context_t c, reme_csg_t *csg);

/** \brief Perform boolean set operation on the volume and one or more spheres.
  *
  * Update the content of the volume by applying a boolean set operation with one ore more spheres. Each sphere is represented by four coordinates:
  * its center (cx, cy, cz) and its radius (r). The spheres are are assumed to be stored in a single consecutive array in the following format
  * <code> cx cy cz r cx cy cz r ... </code>.
  *
  * \param c A valid context object.
  * \param csg A valid CSG object.
  * \param op Set operation to apply.
  * \param spheres Sphere data array.
  * \param numspheres Number of spheres in array.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_csg_update_with_spheres(reme_context_t c, reme_csg_t csg, reme_set_operation_t op, const float *spheres, int numspheres);

/** \brief Perform boolean set operation on the volume and one or more boxes.
  *
  * Update the content of the volume by applying a boolean set operation with one ore more axis aligned boxes. Each box is represented by six coordinates:
  * its minimum corner (minx, miny, minz) and maximum corner (maxx, maxy, maxz). The boxes are are assumed to be stored in a single consecutive array in
  * the following format <code> minx miny minz maxx maxy maxz minx miny minz maxx maxy maxz ... </code>.
  *
  * \param c A valid context object.
  * \param csg A valid CSG object.
  * \param op Set operation to apply.
  * \param boxes Box data array.
  * \param numboxes Number of boxes in array.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_csg_update_with_boxes(reme_context_t c, reme_csg_t csg, reme_set_operation_t op, const float *boxes, int numboxes);

/** \brief Perform boolean set operation on the volume and one or more planes.
  *
  * Update the content of the volume by applying a boolean set operation with one ore more planes. Each plane is represented in Hessian normal form
  * using four coordinates: its unit-length normal vector (nx, ny, nz) and its signed distance from the origin (d). The planes are are assumed to be
  * stored in a single consecutive array in the following format <code> nx ny nz d nx ny nz d ... </code>.
  *
  * \param c A valid context object.
  * \param csg A valid CSG object.
  * \param op Set operation to apply.
  * \param planes Plane data array.
  * \param numplanes Number of planes in array.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_csg_update_with_planes(reme_context_t c, reme_csg_t csg, reme_set_operation_t op, const float *planes, int numplanes);

/** \brief Perform boolean set operation on the volume and a freeform solid mesh.
  *
  * Update the content of the volume by applying a boolean set operation with a freeform solid mesh. The surface needs to be a closed
  * manifold triangular mesh.
  *
  * \param c A valid context object.
  * \param csg A valid CSG object.
  * \param op Set operation to apply.
  * \param s A valid surface handle.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_csg_update_with_surface(reme_context_t c, reme_csg_t csg, reme_set_operation_t op, reme_surface_t s);

/** \brief Make sure that volume borders are closed.
  *
  * Due to the way the surface is extracted from the reconstruction volume, objects sticking out of the volume might not be closed. This
  * method will ensure that all unclosed objects are filled watertight on volume borders through a planar solid.
  *
  * \param c A valid context object.
  * \param csg A valid CSG object.
  * \retval ::REME_ERROR_SUCCESS On success
  * \retval ::REME_ERROR_UNSPECIFIED On failure
  */
LIBRECONSTRUCTMESDK_LIBRARY_INTERFACE
reme_error_t reme_csg_close_volume_borders(reme_context_t c, reme_csg_t csg);

/** \} */

REME_END_DECLS

#endif
