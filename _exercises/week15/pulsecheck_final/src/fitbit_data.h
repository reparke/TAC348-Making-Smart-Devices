#pragma once
/*
  FITBIT DATA ===================================================
  Real Fitbit data from a public dataset:
  Furberg, R., Brinton, J., Keating, M., & Ortiz, A. (2016).
  Crowd-sourced Fitbit datasets 03.12.2016-05.12.2016. Zenodo.
  https://doi.org/10.5281/zenodo.53894 (CC BY 4.0)

  The same numbers are in data/fitbit_windows.csv, which you can
  open in Excel or Google Sheets. The Photon 2 can't read a file
  from your computer, so the numbers are also stored here, where
  they are compiled into the firmware.
  ===============================================================
*/
const int MINUTES = 10;                          // one reading per minute

// Part 1: heart rate (bpm) and steps per minute
const int NUM_PART1 = 5;
const char* LABELS_PART1[NUM_PART1] = {"A", "B", "C", "D", "E"};
const int HR_PART1[NUM_PART1][MINUTES] = {
    {100, 97, 100, 104, 104, 100, 96, 100, 100, 97},     // A: user 4558609924, 2016-04-30 19:00
    {42, 42, 43, 42, 42, 43, 42, 43, 43, 43},            // B: user 5577150313, 2016-04-17 03:10
    {70, 68, 66, 68, 65, 68, 144, 143, 143, 138},        // C: user 2347167796, 2016-04-12 17:20 (edited)
    {72, 70, 71, 72, 75, 74, 75, 72, 73, 75},            // D: user 2022484408, 2016-04-13 13:00
    {154, 155, 156, 158, 159, 156, 160, 157, 154, 153},  // E: user 2022484408, 2016-04-17 09:30
};
const int STEPS_PART1[NUM_PART1][MINUTES] = {
    {103, 104, 99, 100, 99, 88, 100, 100, 100, 101},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {172, 169, 166, 170, 174, 171, 171, 173, 172, 171},
};

// Part 2: heart rate and steps, plus four more signals from the same Fitbit data
//   calories  = calories burned per minute (stored x10, so 12 means 1.2)
//   intensity = Fitbit's activity level: 0 sedentary, 1 light, 2 moderate, 3 very active
//   METs      = energy use compared to rest: 1.0 = sitting still, 3+ = exercise
//               (stored x10, so 12 means 1.2)
//   sleep     = 0 awake, 1 asleep, 2 restless (from Fitbit's sleep tracking)
const int NUM_PART2 = 3;
const char* LABELS_PART2[NUM_PART2] = {"F", "G", "H"};
const int HR_PART2[NUM_PART2][MINUTES] = {
    {62, 62, 62, 62, 62, 60, 63, 97, 97, 96},            // F: user 6962181067, 2016-04-21 03:45
    {137, 132, 142, 189, 191, 191, 186, 172, 165, 163},  // G: user 4020332650, 2016-04-15 21:55
    {66, 66, 67, 65, 68, 74, 90, 97, 100, 100},          // H: user 6117666160, 2016-04-28 11:10
};
const int STEPS_PART2[NUM_PART2][MINUTES] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
const int KCAL10_PART2[NUM_PART2][MINUTES] = {
    {9, 9, 9, 9, 9, 9, 9, 10, 11, 9},
    {124, 124, 105, 127, 193, 193, 193, 187, 172, 161},
    {10, 11, 10, 10, 10, 10, 10, 13, 13, 13},
};
const int INTENSITY_PART2[NUM_PART2][MINUTES] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
const int METS10_PART2[NUM_PART2][MINUTES] = {
    {10, 10, 10, 10, 10, 10, 10, 11, 12, 10},
    {90, 90, 76, 92, 140, 140, 140, 136, 125, 117},
    {10, 11, 10, 10, 10, 10, 10, 12, 12, 12},
};
const int SLEEP_PART2[NUM_PART2][MINUTES] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
const char* SLEEP_NAMES[] = {"awake", "asleep", "restless"};
