#include "constants.h"
#include <QtCore>

#define _STR(x) #x
#define STRINGIFY(x)  _STR(x)

const char *Constants::VERSION = STRINGIFY(APPVERSION);
const char *Constants::GIT_VERSION = STRINGIFY(GITVERSION);
const char *Constants::NAME = STRINGIFY(APP_NAME);
const char *Constants::UNIX_NAME = STRINGIFY(APP_UNIX_NAME);
