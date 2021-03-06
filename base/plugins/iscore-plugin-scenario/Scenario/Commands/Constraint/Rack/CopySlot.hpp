#pragma once
#include <Scenario/Commands/ScenarioCommandFactory.hpp>
#include <iscore/command/Command.hpp>
#include <iscore/model/path/Path.hpp>
#include <iscore/tools/std/Optional.hpp>

#include <iscore/model/Identifier.hpp>

struct DataStreamInput;
struct DataStreamOutput;

namespace Scenario
{
class RackModel;
class SlotModel;
namespace Command
{
/**
         * @brief The CopyLayerModel class
         *
         * Copy a slot, in any Rack of its parent constraint.
         * The process view models are recursively copied.
         * The Slot is put at the end.
         */
class CopySlot final : public iscore::Command
{
  ISCORE_COMMAND_DECL(ScenarioCommandFactoryName(), CopySlot, "Copy a slot")
public:
  CopySlot(Path<SlotModel>&& slotToCopy, Path<RackModel>&& targetRackPath);

  void undo() const override;
  void redo() const override;

protected:
  void serializeImpl(DataStreamInput&) const override;
  void deserializeImpl(DataStreamOutput&) override;

private:
  Path<SlotModel> m_slotPath;
  Path<RackModel> m_targetRackPath;

  Id<SlotModel> m_newSlotId;
};
}
}
