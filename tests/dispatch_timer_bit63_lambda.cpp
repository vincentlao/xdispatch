/*
 * Copyright (c) 2008-2009 Apple Inc. All rights reserved.
 *
 * @APPLE_APACHE_LICENSE_HEADER_START@
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @APPLE_APACHE_LICENSE_HEADER_END@
 */

#include <xdispatch/dispatch.h>

#include "tests.h"
#include <assert.h>


//
// There were several bugs related to sign extension / integer overflow that
// were encountered during development. Create a timer whose interval has the
// 63rd bit of the word set to verify that it behaves correctly.
//
// The expected side-effect of integer overflow would be for the timer to
// fire immediately since its interval has "elapsed." If the timer does not
// fire within 1s we can assume the arithmetic was performed correctly.
//


extern "C" void dispatch_timer_bit63_lambda() {
    MU_BEGIN_TEST(dispatch_timer_bit63_lambda);

    //uint64_t interval = 0xffffffffffffffffull;
    uint64_t interval = 0x8000000000000001ull;

    dispatch_queue_t mainq = dispatch_get_main_queue();

    int* i = new int;
    MU_ASSERT_NOT_NULL(i);
    *i = 0;
    struct timeval start_time;

    gettimeofday(&start_time, NULL);

    dispatch_source_t ds;
    ds = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, mainq);
    MU_ASSERT_NOT_NULL(ds);
    dispatch_source_set_event_handler(ds, [=]{
        MU_ASSERT_LESS_THAN(*i, 1);
        MU_MESSAGE("%d", (*i)++);
    });
    dispatch_source_set_timer(ds, DISPATCH_TIME_NOW, interval, 0);
    dispatch_resume(ds);

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 5.0*NSEC_PER_SEC),
        dispatch_get_main_queue(), [=]{
          delete i;
          MU_PASS("");
        });

    dispatch_main();

    MU_END_TEST
}
