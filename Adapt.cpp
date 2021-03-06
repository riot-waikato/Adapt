#include "Adapt.h"
#include "Arduino.h"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

Adapt::Adapt(int resolution) {
  _resolution = MIN(resolution, 10);
  _count = 0;
}

void Adapt::insert(int value) {
  if(_count < _resolution) _count++;
  for(int i = _count - 1; i > 0; i--)
    _set[i] = _set[i-1];
  _set[0] = value;
}

int Adapt::average() {
  long av = 0;
  for(int i = 0; i < _count; i++)
    av += _set[i];
  av/= _count;
  return (int)av;
}

int Adapt::weighted() { //euclidean distance
  long av = 0;
  for(int i = 0; i < _count; i++)
    av += _set[i]*_set[i];
  av = sqrt(av) / sqrt(_count);
  return (int) av;
}

int Adapt::nonlinear() { //ordered euclidian distance
  long av = 0;
  for(int i = 0; i < _count; i++)
    av +=(_count - i)*_set[i]*_set[i];
  av = sqrt(av) / (sqrt(_count)*1.5);
  return (int) av;
}

int Adapt::exponential() { //unordered euclidian distance
  long av = 0;
  for(int i = 0; i < _count; i++)
    av +=(sqrt(_count - 1)*_set[i]*_set[i]);
  av = sqrt(av) / (sqrt(_count)*sqrt(1.75));
  return (int) av;
}

int Adapt::asymp() { //taking sharp asymptote
  long av = 0;
  for(int i = 0; i < _count; i++)
    av += (_count - 1)*(_count - 1)*(long)_set[i]*_set[i];
  av = sqrt(av) / (_count * 2);
  return (int) av;
}

int Adapt::asymp_2() { //modest asymptote
  long av = 0;
  bool select = false;
  for(int i = 0; i < _count; i++) {
    if(!select && i < _count + 1)
      if(((float)MIN(_set[i], _set[i + 1]) / (float)MAX(_set[i], _set[i+1])) > 0.8 && abs(_set[i] - _set[i + 1]) > 10) {
	av += (long)pow(_count -i, 1.5)*(long)_set[i + 1]*_set[i + 1];
	select = true;
      }
      else
	av += (long)pow(_count -i, 1.5)*(long)_set[i]*_set[i];
    else
      av += (long)pow(_count -i, 1.5)*(long)_set[i]*_set[i];
  }
  av = sqrt(av) / ((long)pow(_count, (2.0/3.0)) * 2.15);
  return (int) av;
}

int Adapt:: newest() {
  return _set[0];
}
int Adapt::oldest() {
  return _set[_count - 1];
}

