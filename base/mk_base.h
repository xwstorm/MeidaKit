#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include <string.h>
#include <assert.h>

#define mkns mk
#define MK_BEGIN namespace mkns {
#define MK_END  }

const int S_OK = 0;
const int S_FAIL = -1;

enum MKSourceState {
    MKStateReady,
    MKStateOpened,
    MKStateClosed,
};
