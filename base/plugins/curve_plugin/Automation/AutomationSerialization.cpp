#include "AutomationModel.hpp"
#include "AutomationViewModel.hpp"
#include "AutomationFactory.hpp"

#include <interface/serialization/DataStreamVisitor.hpp>
#include <interface/serialization/JSONVisitor.hpp>

template<>
void Visitor<Reader<DataStream>>::readFrom(const AutomationModel& autom)
{
	m_stream << autom.points();

	insertDelimiter();
}

template<>
void Visitor<Writer<DataStream>>::writeTo(AutomationModel& autom)
{
	m_stream >> autom.points();

	checkDelimiter();
}




template<>
void Visitor<Reader<JSON>>::readFrom(const AutomationModel& autom)
{
	m_obj["Points"] = toJsonMap(autom.points());
}

template<>
void Visitor<Writer<JSON>>::writeTo(AutomationModel& autom)
{
	autom.setPoints(fromJsonMap<double>(m_obj["Points"].toArray()));
}



void AutomationModel::serialize(SerializationIdentifier identifier,
								void* data) const
{
	if(identifier == DataStream::type())
	{
		static_cast<Serializer<DataStream>*>(data)->readFrom(*this);
		return;
	}
	else if(identifier == JSON::type())
	{
		static_cast<Serializer<JSON>*>(data)->readFrom(*this);
		return;
	}

	throw std::runtime_error("AutomationModel only supports DataStream & JSON serialization");
}



ProcessSharedModelInterface* AutomationFactory::makeModel(SerializationIdentifier identifier,
														  void* data,
														  QObject* parent)
{
	if(identifier == DataStream::type())
	{
		return new AutomationModel{*static_cast<Deserializer<DataStream>*>(data), parent};
	}
	else if(identifier == JSON::type())
	{
		return new AutomationModel{*static_cast<Deserializer<JSON>*>(data), parent};
	}

	throw std::runtime_error("Automation only supports DataStream & JSON serialization");
}

ProcessViewModelInterface* AutomationModel::makeViewModel(SerializationIdentifier identifier,
														  void* data,
														  QObject* parent)
{
	if(identifier == DataStream::type())
	{
		auto autom = new AutomationViewModel(*static_cast<Deserializer<DataStream>*>(data),
											 this,
											 parent);
		addViewModel(autom);
		return autom;
	}
	else if(identifier == JSON::type())
	{
		auto autom = new AutomationViewModel(*static_cast<Deserializer<JSON>*>(data),
											 this,
											 parent);
		addViewModel(autom);
		return autom;
	}

	throw std::runtime_error("Automation ViewModel only supports DataStream & JSON serialization");
}
