#include "constants.h"
#include <QtCore>

#define _STR(x) #x
#define STRINGIFY(x)  _STR(x)

const char *Constants::VERSION = STRINGIFY(APP_VERSION);
const char *Constants::GIT_VERSION = STRINGIFY(GIT_VERSION);
const char *Constants::NAME = STRINGIFY(APP_NAME);
const char *Constants::UNIX_NAME = STRINGIFY(APP_UNIX_NAME);
