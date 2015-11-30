#include <Scenario/Document/Constraint/Rack/Slot/SlotModel.hpp>
#include <algorithm>

#include "PutLayerModelToFront.hpp"
#include <iscore/tools/ModelPath.hpp>

#include <iscore/tools/SettableIdentifier.hpp>

PutLayerModelToFront::PutLayerModelToFront(
        Path<SlotModel>&& slotPath,
        const Id<LayerModel>& pid):
    m_slotPath{std::move(slotPath)},
    m_pid{pid}
{

}

void PutLayerModelToFront::redo() const
{
    m_slotPath.find().putToFront(m_pid);
}
