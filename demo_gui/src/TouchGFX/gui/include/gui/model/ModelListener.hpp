#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

public:
  // Call this function to notify that temperature has changed.
  // Per default, use an empty implementation so that only those
  // Presenters interested in this specific event need to
  // override this function.
  virtual void notifyTemperatureChanged(int newTemperature) {}
  virtual void notifyHumidityChanged(int newHumidity) {}
  virtual void notifyLightChanged(int newLight) {}
  virtual void notifyKeysPressDown(int id) {}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
