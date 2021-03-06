#pragma once
#include <QByteArray>
#include <Scenario/Commands/ScenarioCommandFactory.hpp>
#include <iscore/command/Command.hpp>
#include <iscore/model/path/Path.hpp>
#include <iscore/tools/std/Optional.hpp>

#include <iscore/model/Identifier.hpp>

struct DataStreamInput;
struct DataStreamOutput;
namespace Process
{
class LayerModel;
}
namespace Process
{
class ProcessModel;
}

namespace Scenario
{
class ConstraintModel;
class RackModel;
class SlotModel;
namespace Command
{
/**
        * @brief The AddLayerInNewSlot class
        */
class ISCORE_PLUGIN_SCENARIO_EXPORT AddLayerInNewSlot final
    : public iscore::Command
{
  ISCORE_COMMAND_DECL(
      ScenarioCommandFactoryName(), AddLayerInNewSlot, "Add a new layer")
public:
  AddLayerInNewSlot(
      Path<ConstraintModel>&& constraintPath,
      Id<Process::ProcessModel>
          process); // maybe should we pass the viewmodel too, if many
                    // available ?

  void undo() const override;
  void redo() const override;

  Id<Process::ProcessModel> processId() const
  {
    return m_processId;
  }

protected:
  void serializeImpl(DataStreamInput&) const override;
  void deserializeImpl(DataStreamOutput&) override;

private:
  Path<ConstraintModel> m_path;

  bool m_existingRack{};

  Id<Process::ProcessModel> m_processId{};
  OptionalId<RackModel> m_createdRackId{};
  Id<SlotModel> m_createdSlotId{};
  Id<Process::LayerModel> m_createdLayerId{};
  Id<Process::ProcessModel> m_sharedProcessModelId{};

  QByteArray m_processData;
};
}
}
