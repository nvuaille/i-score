#pragma once
#include <iscore/command/AggregateCommand.hpp>

class CreateProcessInExistingSlot final : public iscore::AggregateCommand
{
        ISCORE_AGGREGATE_COMMAND_DECL(ScenarioCommandFactoryName(),
                                      CreateProcessInExistingSlot,
                                      "CreateProcessInExistingSlot")
};