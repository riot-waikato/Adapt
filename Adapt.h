/* Adapt.h - Library for getting averages out of arrays
   Created by Nathan Bryan Kelly, April 7, 2016
   I should probably pick a license later
*/
#ifndef Adapt_h
#define Adapt_h
class Adapt {
 public:
  Adapt(int resolution);
  void insert(int value);
  int average();
  int weighted();
  int nonlinear();
  int exponential();

  int newest();
  int oldest();
 private:
  int _count;
  int _resolution;
  //int _acount;
  int _set[10];
  //int _adp[3];
};
#endif
