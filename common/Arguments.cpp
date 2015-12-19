#include "Arguments.h"

Arguments *Arguments::instance = 0;

Arguments *Arguments::gi() {
    if (instance == 0) {
        instance = new Arguments();
    }
    return instance;
}