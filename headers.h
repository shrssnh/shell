#ifndef HEADERS_H_
#define HEADERS_H_

#define BUFFER 4096

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <termios.h>
#include <ctype.h>
#include <signal.h>

#include "execute.h"
#include "prompt.h"
#include "tokenize.h"
#include "warp.h"
#include "proclore.h"
#include "peek.h"
#include "seek.h"
#include "pastevents.h"
#include "globals.h"
#include "iman.h"
#include "signals.h"

#endif