#pragma once

#include "Event.h"

namespace GG {

  class KeyEvent : public Event {
    public:
      inline int GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
      KeyEvent(int keycode)
        : m_KeyCode(keycode) {}

      // 具体的按键码
      int m_KeyCode;
  };

  class KeyPressEvent : public KeyEvent {
    public:
      KeyPressEvent(int keycode, int repeatCount)
        : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

      inline int GetRepeatCount() const { return m_RepeatCount; }

      std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
        return ss.str();
      }
      EVENT_CLASS_TYPE(KeyPressed)
    private:
      int m_RepeatCount;
  };

  class KeyReleaseEvent : public KeyEvent {
    public:
      KeyReleaseEvent(int keycode)
        : KeyEvent(keycode) {}
        
      std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleaseEvent: " << m_KeyCode;
        return ss.str();
      }
      EVENT_CLASS_TYPE(KeyReleased)
  };
}