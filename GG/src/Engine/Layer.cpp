#include "Layer.h"
#include "ggpch.h"

namespace GG {
  Layer::Layer(const std::string& debugName)
    : m_DebugName(debugName) {}

  Layer::~Layer() {}
}