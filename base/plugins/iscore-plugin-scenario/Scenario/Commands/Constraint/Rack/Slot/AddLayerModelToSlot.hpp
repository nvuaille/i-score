#pragma once
#include <QByteArray>
#include <Scenario/Commands/ScenarioCommandFactory.hpp>
#include <iscore/command/Command.hpp>
#include <iscore/model/path/Path.hpp>
#include <iscore/tools/std/Optional.hpp>

#include <iscore/model/Identifier.hpp>
#include <iscore_plugin_scenario_export.h>
struct DataStreamInput;
struct DataStreamOutput;
namespace Process
{
class LayerModel;
class LayerFactory;
}
namespace Process
{
class ProcessModel;
}

namespace Scenario
{
class SlotModel;
namespace Command
{
/**
         * @brief The AddLayerToSlot class
         *
         * Adds a process view to a slot.
         */
class ISCORE_PLUGIN_SCENARIO_EXPORT AddLayerModelToSlot final
    : public iscore::Command
{
  ISCORE_COMMAND_DECL(
      ScenarioCommandFactoryName(),
      AddLayerModelToSlot,
      "Add a layer to a slot")
public:
  AddLayerModelToSlot(
      const SlotModel& slot, const Process::ProcessModel& process);

  // Use this constructor when the process isn't created yet
  AddLayerModelToSlot(
      Path<SlotModel>&& slot,
      const Process::ProcessModel& process,
      QByteArray processConstructionData);

  AddLayerModelToSlot(
      Path<SlotModel>&& slot,
      Id<Process::LayerModel>
          layerid,
      Path<Process::ProcessModel>
          process,
      UuidKey<Process::LayerFactory>
          uid,
      QByteArray processConstructionData);

  void undo() const override;
  void redo() const override;

protected:
  void serializeImpl(DataStreamInput&) const override;
  void deserializeImpl(DataStreamOutput&) override;

private:
  Path<SlotModel> m_slotPath;
  Path<Process::ProcessModel> m_processPath;
  UuidKey<Process::LayerFactory> m_layerFactory;

  QByteArray m_processData;

  Id<Process::LayerModel> m_createdLayerId{};
};
}
}
