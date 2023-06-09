#pragma once

typedef float (*fourParamFunc) (float*);

float derivitive(fourParamFunc func, int index, float* abcd);
float det4(fourParamFunc** opps, float* abcd);
float det3(fourParamFunc** opps, float* abcd);
