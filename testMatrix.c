#include <stdio.h>

#include "testCommon.h"

void testAbs() {
    testStart("abs");
    assertEqualsInt(abs(-1), 1);
}

int main() {
    testAbs();
    testErrorCheck();
}
