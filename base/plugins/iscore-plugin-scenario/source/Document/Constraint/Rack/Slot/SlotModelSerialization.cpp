#include "SlotModel.hpp"
#include "ProcessInterface/LayerModel.hpp"
#include "source/ProcessInterfaceSerialization/LayerModelSerialization.hpp"
#include <iscore/serialization/JSONVisitor.hpp>
#include <iscore/serialization/DataStreamVisitor.hpp>
#include <iscore/serialization/JSONValueVisitor.hpp>
#include <iscore/tools/NotifyingMap_impl.hpp>

template<> void Visitor<Reader<DataStream>>::readFrom(const SlotModel& slot)
{
    readFrom(static_cast<const IdentifiedObject<SlotModel>&>(slot));

    m_stream << slot.m_frontLayerModelId;

    const auto& lms = slot.layers;
    m_stream << (int) lms.size();

    for(const auto& lm : lms)
    {
        readFrom(lm);
    }

    m_stream << slot.height();

    insertDelimiter();
}

template<> void Visitor<Writer<DataStream>>::writeTo(SlotModel& slot)
{
    Id<LayerModel> editedProcessId;
    m_stream >> editedProcessId;

    int lm_size;
    m_stream >> lm_size;

    const auto& cstr = slot.parentConstraint();

    for(int i = 0; i < lm_size; i++)
    {
        auto lm = createLayerModel(*this, cstr, &slot);
        slot.layers.add(lm);
    }

    qreal height;
    m_stream >> height;
    slot.setHeight(height);

    slot.putToFront(editedProcessId);

    checkDelimiter();
}





template<> void Visitor<Reader<JSONObject>>::readFrom(const SlotModel& slot)
{
    readFrom(static_cast<const IdentifiedObject<SlotModel>&>(slot));

    m_obj["EditedProcess"] = toJsonValue(slot.m_frontLayerModelId);
    m_obj["Height"] = slot.height();

    QJsonArray arr;

    for(const auto& lm : slot.layers)
    {
        arr.push_back(toJsonObject(lm));
    }

    m_obj["LayerModels"] = arr;
}

template<> void Visitor<Writer<JSONObject>>::writeTo(SlotModel& slot)
{
    QJsonArray arr = m_obj["LayerModels"].toArray();

    const auto& cstr = slot.parentConstraint();

    for(const auto& json_vref : arr)
    {
        Deserializer<JSONObject> deserializer {json_vref.toObject() };
        auto lm = createLayerModel(deserializer,
                                          cstr,
                                          &slot);
        slot.layers.add(lm);
    }

    slot.setHeight(static_cast<qreal>(m_obj["Height"].toDouble()));
    slot.putToFront(
                fromJsonValue<Id<LayerModel>>(
                    m_obj["EditedProcess"]));
}
