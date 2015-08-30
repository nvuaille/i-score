#pragma once
#include <Document/Constraint/ConstraintDurations.hpp>
#include <Document/Constraint/Rack/RackModel.hpp>
#include <ProcessInterface/ProcessModel.hpp>

#include <source/Document/ModelMetadata.hpp>
#include <source/Document/ModelConsistency.hpp>
#include <source/Document/State/StateModel.hpp>

#include <iscore/tools/IdentifiedObjectMap.hpp>
#include <iscore/serialization/VisitorInterface.hpp>
#include <ProcessInterface/TimeValue.hpp>

#include <iscore/selection/Selectable.hpp>

#include <iscore/plugins/documentdelegate/plugin/ElementPluginModelList.hpp>
#include <QColor>
#include <vector>

namespace OSSIA
{
    class TimeRack;
}

class Process;
class ConstraintViewModel;
class FullViewConstraintViewModel;

class RackModel;
class EventModel;
class TimeRack;
class ScenarioInterface;

class ConstraintModel : public IdentifiedObject<ConstraintModel>
{
        Q_OBJECT
        ISCORE_METADATA("ConstraintModel")

        ISCORE_SERIALIZE_FRIENDS(ConstraintModel, DataStream)
        ISCORE_SERIALIZE_FRIENDS(ConstraintModel, JSONObject)

        // TODO must go in view model
        Q_PROPERTY(double heightPercentage
                   READ heightPercentage
                   WRITE setHeightPercentage
                   NOTIFY heightPercentageChanged)


    public:
        /** Properties of the class **/
        Selectable selection;
        ModelMetadata metadata;
        ModelConsistency consistency;
        ConstraintDurations duration{*this};

        iscore::ElementPluginModelList pluginModelList;

        static QString prettyName()
        { return QObject::tr("Constraint"); }

        /** The class **/
        ConstraintModel(const Id<ConstraintModel>&,
                        const Id<ConstraintViewModel>& fullViewId,
                        double yPos,
                        QObject* parent);


        // Copy
        ConstraintModel(const ConstraintModel &source,
                        const Id<ConstraintModel>& id,
                        QObject* parent);

        // Serialization
        template<typename Deserializer>
        ConstraintModel(Deserializer&& vis, QObject* parent) :
            IdentifiedObject{vis, parent}
        {
            vis.writeTo(*this);
        }

        // Factories for the view models.
        template<typename ViewModelType> // Arg might be an id or a datastream [
        ViewModelType* makeConstraintViewModel(
                const Id<ConstraintViewModel>& id,
                QObject* parent)
        {
            auto viewmodel = new ViewModelType {id, *this, parent};
            setupConstraintViewModel(viewmodel);
            return viewmodel;
        }

        // If the constraint is in a scenario, then returns the scenario
        ScenarioInterface* parentScenario() const;

        // Note : the Constraint does not have ownership (it's generally the Slot)
        void setupConstraintViewModel(ConstraintViewModel* viewmodel);

        // Sub-element creation
        void addProcess(Process*);
        void removeProcess(const Id<Process>& processId);

        void addRack(RackModel*);
        void removeRack(const Id<RackModel>& rackId);

        const Id<StateModel>& startState() const;
        void setStartState(const Id<StateModel>& eventId);

        const Id<StateModel>& endState() const;
        void setEndState(const Id<StateModel> &endState);

        RackModel& rack(const Id<RackModel>& id) const;
        Process& process(
                const Id<Process>& processId) const;


        const auto& racks() const
        { return m_racks; }

        const auto& processes() const
        { return m_processes; }

        // Here we won't remove / add things from the outside so it is safe to
        // return a reference
        const QVector<ConstraintViewModel*>& viewModels() const
        { return m_constraintViewModels; }

        const TimeValue& startDate() const;
        void setStartDate(const TimeValue& start);
        void translate(const TimeValue& deltaTime);

        double heightPercentage() const;


        FullViewConstraintViewModel* fullView() const
        {
            return m_fullViewModel;
        }

        void setFullView(FullViewConstraintViewModel* fv);


        // Resets the execution display recursively
        void reset();

    signals:
        void processCreated(const Id<Process>&);
        void processRemoved(const Id<Process>&);

        void rackCreated(const Id<RackModel>&);
        void rackRemoved(const Id<RackModel>&);

        void viewModelCreated(const Id<ConstraintViewModel>&);
        void viewModelRemoved(const Id<ConstraintViewModel>&);

        void heightPercentageChanged(double);

        void startDateChanged(const TimeValue&);

    public slots:
        void setHeightPercentage(double arg);

    private slots:
        void on_destroyedViewModel(QObject*);

    private:
        IdContainer<RackModel> m_racks; // No content -> Phantom ?
        IdContainer<Process> m_processes;

        // The small view constraint view models that show this constraint
        // The constraint does not have ownership of these: their parent (in the Qt sense) are
        // the scenario view models
        QVector<ConstraintViewModel*> m_constraintViewModels;

        // Model for the full view.
        // Note : it is also present in m_constraintViewModels.
        FullViewConstraintViewModel* m_fullViewModel {};

        Id<StateModel> m_startState;
        Id<StateModel> m_endState;

        TimeValue m_startDate; // origin

        double m_heightPercentage {0.5};
};
