#include "MetadataParameters.hpp"
#include <Engine/LocalTree/GetProperty.hpp>
#include <Engine/LocalTree/Property.hpp>
#include <Process/ModelMetadata.hpp>
namespace Engine
{
namespace LocalTree
{
ISCORE_PLUGIN_ENGINE_EXPORT
void make_metadata_node(
        ModelMetadata& metadata,
        ossia::net::node_base& parent,
        std::vector<std::unique_ptr<BaseProperty>>& properties,
        QObject* context)
{

    properties.push_back(
    add_getProperty<QString>(parent, "name", &metadata,
                             &ModelMetadata::name,
                             &ModelMetadata::nameChanged,
                             context));

    properties.push_back(
    add_property<QString>(parent, "comment", &metadata,
                          &ModelMetadata::comment,
                          &ModelMetadata::setComment,
                          &ModelMetadata::commentChanged,
                          context));

    properties.push_back(
    add_property<QString>(parent, "label", &metadata,
                          &ModelMetadata::label,
                          &ModelMetadata::setLabel,
                          &ModelMetadata::labelChanged,
                          context));
}
}
}