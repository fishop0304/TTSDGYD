/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "detection_responder.h"

#include "hx_drv_tflm.h"

// This dummy implementation writes person and no person scores to the error
// console. Real applications will want to take some custom action instead, and
// should implement their own versions of this function.
void RespondToDetection(tflite::ErrorReporter* error_reporter,
                        int8_t person_score, int8_t no_person_score) {
  hx_drv_share_switch(SHARE_MODE_I2CM);
  uint8_t data_write_1[1] = {0x31};
  uint8_t data_write_2[1] = {0x30};

  if (person_score > no_person_score) {
    hx_drv_led_on(HX_DRV_LED_GREEN);
    hx_drv_i2cm_set_data(0x3c, NULL, 0 , data_write_1, 1);
  } else {
    hx_drv_led_off(HX_DRV_LED_GREEN);
    hx_drv_i2cm_set_data(0x3c, NULL, 0 , data_write_2, 1);
  }

  TF_LITE_REPORT_ERROR(error_reporter, "person score:%d no person score %d",
                       person_score, no_person_score);
}
