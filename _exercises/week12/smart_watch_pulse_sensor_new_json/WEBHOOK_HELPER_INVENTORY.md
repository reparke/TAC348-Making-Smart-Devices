Webhook helper replacement inventory — 2026-11-18

All remaining occurrences have now been approved and updated to the same non-template helper. The two template call sites were converted to ordinary two-argument calls. The user deleted both starter ZIP downloads. The newly found smart_watch_pulse_sensor_20263_mw copy already contained the new helper and is included in the final synchronization. Both new, previously untracked smart-watch source projects are included for publication, as explicitly approved; build outputs and local IDE files are excluded.

Checked the complete on-disk repository, including hidden and ignored paths (excluding Git internals), exercises, assignments, lectures, resources, generated _site files, and all 20 ZIP archives. The initial inventory found 14 standalone headers and 1 archived header. The final inventory has 15 standalone headers and no archived copy, after the user removed the ZIPs and added the mw project copy. No additional copies or references were found under _assignments, resources, or _site.

Header-only compatibility was checked against each existing caller and declared/bundled ArduinoJson version. It is not a claim that every complete project was freshly built or flashed. The current watch built successfully for Photon 2 / Device OS 6.4.1, and the actual helper passed host behavioral tests using both ArduinoJson 7.3.1 and 7.4.3.

| ID | Location | Final status | Compatibility / action taken |
|---|---|---|---|
| 1 | [_exercises/week12/smart_watch_pulse_sensor_new_json/src/json_webhook_response_helper.h](../../../_exercises/week12/smart_watch_pulse_sensor_new_json/src/json_webhook_response_helper.h) | Updated | Unchanged two-argument caller; full Photon 2 / Device OS 6.4.1 build passed. |
| 2 | [_exercises/week11/open-meteo_final/src/json_webhook_response_helper.h](../../../_exercises/week11/open-meteo_final/src/json_webhook_response_helper.h) | Updated — header only | Active two-argument caller; ArduinoJson 7.3.1. The alternate source in alt/open-meteo-alt.cpp also uses that interface. |
| 3 | [_exercises/week11/open-meteo_start/src/json_webhook_response_helper.h](../../../_exercises/week11/open-meteo_start/src/json_webhook_response_helper.h) | Updated — header only | Included but not called yet; ArduinoJson 7.3.1. Student TODOs need no changes. |
| 4 | [_exercises/week11/open-meteo_start_mw_20263/src/json_webhook_response_helper.h](../../../_exercises/week11/open-meteo_start_mw_20263/src/json_webhook_response_helper.h) | Updated — header only | Active two-argument caller; ArduinoJson 7.3.1. |
| 5 | [_exercises/week11/open-meteo_start_tth_20263/src/json_webhook_response_helper.h](../../../_exercises/week11/open-meteo_start_tth_20263/src/json_webhook_response_helper.h) | Updated — header only | Active two-argument caller; ArduinoJson 7.3.1. |
| 6 | [_exercises/week11/sunset_sunrise_final/src/json_webhook_response_helper.h](../../../_exercises/week11/sunset_sunrise_final/src/json_webhook_response_helper.h) | Updated — header only | Included, but the helper call is commented out and the handler parses data directly; ArduinoJson 7.4.3. Replacement does not change that behavior. |
| 7 | [_exercises/week11/sunset_sunrise_start/src/json_webhook_response_helper.h](../../../_exercises/week11/sunset_sunrise_start/src/json_webhook_response_helper.h) | Updated — header only | Included but not called yet; ArduinoJson 7.3.1. |
| 8 | [_exercises/week11/sunset_sunrise_start_mw_20263/src/json_webhook_response_helper.h](../../../_exercises/week11/sunset_sunrise_start_mw_20263/src/json_webhook_response_helper.h) | Updated — header only | Active two-argument caller; ArduinoJson 7.3.1. |
| 9 | [_exercises/week11/sunset_sunrise_start_tth_20263/src/json_webhook_response_helper.h](../../../_exercises/week11/sunset_sunrise_start_tth_20263/src/json_webhook_response_helper.h) | Updated — header only | Active two-argument caller; ArduinoJson 7.3.1. |
| 10 | [_exercises/week12/smart_watch_pulse_sensor_start/src/json_webhook_response_helper.h](../../../_exercises/week12/smart_watch_pulse_sensor_start/src/json_webhook_response_helper.h) | Updated — header only | Included but not called yet; ArduinoJson 7.3.1. The starter remains a starter. |
| 11 | [_exercises/week12/smart_watch_pulse_sensor_20263_tweak/src/json_webhook_response_helper.h](../../../_exercises/week12/smart_watch_pulse_sensor_20263_tweak/src/json_webhook_response_helper.h) | Updated — header only | Included but not called yet; ArduinoJson 7.4.3. |
| 12 | [_exercises/week12/smart_watch_pulse_sensor_final_photon2_rev_lib/src/json_webhook_response_helper.h](../../../_exercises/week12/smart_watch_pulse_sensor_final_photon2_rev_lib/src/json_webhook_response_helper.h) | Updated — caller adjusted | Removed <1> from the sunrise/sunset call. Weather and sunrise/sunset now use the same two-argument interface and separate event-name buffers. |
| 13 | [_exercises/week12/smart_watch_pulse_sensor_gemini/src/json_webhook_response_helper.h](../../../_exercises/week12/smart_watch_pulse_sensor_gemini/src/json_webhook_response_helper.h) | Updated — caller adjusted | Removed <1> from the Gemini call. Weather and Gemini now use the same two-argument interface and separate event-name buffers. |
| 14 | [_lectures/week11/json_webhook_response_helper.h](../../../_lectures/week11/json_webhook_response_helper.h) | Updated — header only | Download linked by lecture_json_parsing_with_arduinojson.md:65. Its example at line 99 uses the unchanged two-argument call; prose about empty versus complete responses remains correct. |
| 15 | `_exercises/week11/open-meteo_start.zip` | Deleted by user | Removed the tracked archive from the publication commit; it is not being rebuilt. |
| 16 | [_exercises/week12/smart_watch_pulse_sensor_20263_mw/src/json_webhook_response_helper.h](../../../_exercises/week12/smart_watch_pulse_sensor_20263_mw/src/json_webhook_response_helper.h) | Updated / synchronized | Newly found copy; active two-argument caller and ArduinoJson 7.4.3. Complete source project approved for publication. |

The user also deleted `_exercises/week12/smart_watch_pulse_sensor_start.zip`. That older archive was untracked and therefore requires no Git deletion; it remains absent. The tweak project’s bundled OLED source had the old PO/drawBitmap mismatch, so it was replaced with the unmodified, published SparkFunMicroOLED 1.3.0 library. No custom OLED source patch is included. The newly published mw project also had a compiler error from the misspelled variable humidty; it was corrected to the already declared humidity.

The new helper keeps the same two-argument function and String return value. It groups chunks by event name after removing a numeric chunk suffix, supports four active webhook names and ten parts per response, expires each unfinished response independently after 20 seconds without a part, and clears a buffer once parsing succeeds. Unnumbered single-part JSON events are also supported. If all four slots are occupied, chunks from a fifth webhook are ignored until a slot becomes free; they are not queued and existing responses are not evicted.

The unchanged limitation is that overlapping requests to the SAME webhook name cannot be distinguished without a response ID. The existing example request intervals do not themselves guarantee that overlap can never happen on a slow network. The new helper separates DIFFERENT webhook names; it does not claim to solve same-name overlap.

Validation passed: current firmware build; single/multipart responses; interleaved webhook names; out-of-order and duplicate chunks; four-slot capacity and reuse; independent timeouts; malformed inputs; unnumbered events; ten-part responses; clock rollover. Host tests use a small Particle String/clock shim with the real ArduinoJson parser. On-device testing of this new header remains for the user.

Approval is complete. All existing source copies are synchronized; both template calls are removed; neither deleted ZIP will be recreated. Firmware build results for the completed rollout are recorded below.


Final local firmware build results (Photon 2):

| Project | Device OS | Result |
|---|---|---|
| smart_watch_pulse_sensor_final_photon2_rev_lib | 5.8.0 | Passed |
| smart_watch_pulse_sensor_20263_mw | 5.8.0 | Passed |
| smart_watch_pulse_sensor_20263_tweak | 5.8.0 | Passed |
| smart_watch_pulse_sensor_start | 5.8.0 | Passed |
| open-meteo_final | 6.4.1 | Passed |
| smart_watch_pulse_sensor_new_json | 6.4.1 | Passed |
| smart_watch_pulse_sensor_gemini | 6.3.3 | Passed |

All 15 local headers and publication copies are byte-for-byte identical. The final helper passed host behavioral tests against ArduinoJson 7.3.1 and 7.4.3 after the Device OS 5.8-compatible character-pointer parsing adjustment. No template definitions or template calls remain. These builds validate compilation; they do not claim fresh hardware testing of every project.
