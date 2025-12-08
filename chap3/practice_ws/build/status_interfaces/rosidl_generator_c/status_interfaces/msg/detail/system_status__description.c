// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from status_interfaces:msg/SystemStatus.idl
// generated code does not contain a copyright notice

#include "status_interfaces/msg/detail/system_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_status_interfaces
const rosidl_type_hash_t *
status_interfaces__msg__SystemStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x78, 0x7d, 0x90, 0xa9, 0x8a, 0xbf, 0x16, 0x03,
      0x60, 0x82, 0x27, 0x7e, 0xd4, 0x16, 0x78, 0xe4,
      0x02, 0x68, 0xeb, 0x3a, 0xdf, 0x69, 0x24, 0xbe,
      0x88, 0xa6, 0xdb, 0xc7, 0x70, 0x15, 0x5b, 0x8e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
#endif

static char status_interfaces__msg__SystemStatus__TYPE_NAME[] = "status_interfaces/msg/SystemStatus";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";

// Define type names, field names, and default values
static char status_interfaces__msg__SystemStatus__FIELD_NAME__stamp[] = "stamp";
static char status_interfaces__msg__SystemStatus__FIELD_NAME__host_name[] = "host_name";
static char status_interfaces__msg__SystemStatus__FIELD_NAME__cpu_percent[] = "cpu_percent";
static char status_interfaces__msg__SystemStatus__FIELD_NAME__memory_percent[] = "memory_percent";
static char status_interfaces__msg__SystemStatus__FIELD_NAME__memory_total[] = "memory_total";
static char status_interfaces__msg__SystemStatus__FIELD_NAME__memory_available[] = "memory_available";
static char status_interfaces__msg__SystemStatus__FIELD_NAME__net_sent[] = "net_sent";
static char status_interfaces__msg__SystemStatus__FIELD_NAME__net_recv[] = "net_recv";

static rosidl_runtime_c__type_description__Field status_interfaces__msg__SystemStatus__FIELDS[] = {
  {
    {status_interfaces__msg__SystemStatus__FIELD_NAME__stamp, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
  {
    {status_interfaces__msg__SystemStatus__FIELD_NAME__host_name, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {status_interfaces__msg__SystemStatus__FIELD_NAME__cpu_percent, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {status_interfaces__msg__SystemStatus__FIELD_NAME__memory_percent, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {status_interfaces__msg__SystemStatus__FIELD_NAME__memory_total, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {status_interfaces__msg__SystemStatus__FIELD_NAME__memory_available, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {status_interfaces__msg__SystemStatus__FIELD_NAME__net_sent, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {status_interfaces__msg__SystemStatus__FIELD_NAME__net_recv, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription status_interfaces__msg__SystemStatus__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
status_interfaces__msg__SystemStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {status_interfaces__msg__SystemStatus__TYPE_NAME, 34, 34},
      {status_interfaces__msg__SystemStatus__FIELDS, 8, 8},
    },
    {status_interfaces__msg__SystemStatus__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "builtin_interfaces/Time stamp\n"
  "string host_name\n"
  "float64 cpu_percent\n"
  "float64 memory_percent\n"
  "float64 memory_total\n"
  "float64 memory_available\n"
  "float64 net_sent\n"
  "float64 net_recv";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
status_interfaces__msg__SystemStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {status_interfaces__msg__SystemStatus__TYPE_NAME, 34, 34},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 170, 170},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
status_interfaces__msg__SystemStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *status_interfaces__msg__SystemStatus__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
