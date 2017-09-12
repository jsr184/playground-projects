#ifndef SIGNAL_SLOT_SIGNAL_H_H
#define SIGNAL_SLOT_SIGNAL_H_H

#include <vector>
#include <cstdint>
#include <functional>

namespace Framework
{

class IConnectable
{
  friend class SignalBase;

public:
  virtual ~IConnectable() = default;

private:

  //std::vector<class Signal*> _connections;
};

/**
 * Class Signal
 * @tparam R
 * @tparam Args
 */

/*
class SignalBase
{
public:

  virtual ~SignalBase()
  {
    disconnectAll();
  }

  virtual void disconnectAll() {};
};
*/
using SlotId = uint32_t;

template<class R, class... Args>
class Signal// : public SignalBase
{
private:

  SlotId currentSlotId{0u};
  using SlotProcType = R(IConnectable::*)(Args...);

  class Slot
  {
    friend class Signal;

  public:
    Slot(IConnectable &obj, SlotProcType proc, SlotId _slotId)
      : object(&obj), slotProc(proc), slotType{SlotType::eMemberFunction}, slotId{_slotId}
    {
    }

    Slot(IConnectable &obj, std::function<R(IConnectable &, Args...)> lambda, SlotId _slotId) : object(&obj),
                                                                                                slotLambda(lambda),
                                                                                                slotType{
                                                                                                  SlotType::eLambda},
                                                                                                slotId{_slotId}
    {
    }

    Slot(std::function<R(Args...)> lambda, SlotId _slotId) : object(nullptr),
                                                             slotStaticLambda(lambda),
                                                             slotType{SlotType::eStaticLambda},
                                                             slotId{_slotId}
    {
    }

    ~Slot() = default;

    R invoke(Args &&... args)
    {
      if (slotType == SlotType::eMemberFunction)
      {
        //return (object->*slotProc)(std::forward<Args&&...>(args...));
        return (object->*slotProc)(args...);
      }
      else if (slotType == SlotType::eStaticLambda)
      {
        return slotStaticLambda(args...);
      }
      else
      {
        return slotLambda(*object, args...);
      }
    }

    IConnectable *object;
    SlotProcType slotProc;
    std::function<R(IConnectable &, Args...)> slotLambda;
    std::function<R(Args...)> slotStaticLambda;
    SlotId                    slotId;
    enum class SlotType
    {
      eLambda,
      eStaticLambda,
      eMemberFunction
    }                         slotType;
  };

public:
  template<class T>
  SlotId connect(T &object, R(T::*slot)(Args &&...))
  {
    auto connected = (isConnected(object, slot) != -1u);
    if (connected)
      return -1u;
    slots.emplace_back(object, static_cast<SlotProcType>(slot), currentSlotId++);
    return currentSlotId;
  }

  template<class T>
  SlotId connect(T &object, std::function<R(IConnectable &, Args...)> fn)
  {
    slots.emplace_back(object, fn, currentSlotId++);
    return currentSlotId - 1;
  }

  SlotId connect(std::function<R(Args...)> fn)
  {
    slots.emplace_back(fn, currentSlotId++);
    return currentSlotId - 1;
  }

  void emit(Args... args)
  {
    for (auto &&slot : slots)
      slot.invoke(args...);
  }

  template<class T>
  bool disconnect(T &object, R(T::*slot)(Args...))
  {
    auto connectedIndex = isConnected(object, slot);
    if (connectedIndex != -1u)
    {
      auto it = slots.begin();
      std::advance(it, connectedIndex);
      slots.erase(it);
      return true;
    }
    return false;
  }

  template<class T>
  bool disconnect(T &object)
  {
    for (auto it = slots.begin(); it != slots.end(); ++it)
    {
      auto &&slot = *it;
      if (slot.object == &object)
      {
        slots.erase(it);
        --it;
      }
    }
  }

  bool disconnect(SlotId slotId)
  {
    for (auto it = slots.begin(); it != slots.end(); ++it)
    {
      if ((*it).slotId == slotId)
      {
        slots.erase(it);
        return true;
      }
    }
    return false;
  }


  inline Signal &operator()()
  {
    return *this;
  }

  template<class T>
  uint32_t isConnected(T &object, R(T::*slotProc)(Args...))
  {
    auto i = 0u;
    for (auto &&slot : slots)
    {
      if (slot.object == &object && slot.slotProc == static_cast<SlotProcType>(slotProc))
      {
        return i;
      }
      ++i;
    }
    return -1u;
  }

  void disconnectAll()
  {
    for (auto &&slot : slots)
    {

    }
  }

  std::vector<Slot> slots;
};

}
#endif //SIGNAL_SLOT_SIGNAL_H_H
