#ifndef ULTRA_H__
#define ULTRA_H__

class Ultra{
  private:
    int trig = 16;
    int echo = 17;
  public:
  Ultra();
    int getDistance();
};

#endif
