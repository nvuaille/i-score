#pragma once
#include <Process/ZoomHelper.hpp>
#include <iscore/plugins/panel/PanelPresenter.hpp>

class DynamicProcessList;
class LayerModel;
class LayerPresenter;
class LayerView;
class ProcessPanelGraphicsProxy;
class QSize;
namespace iscore {
class PanelView;
class Presenter;
}  // namespace iscore

class ProcessPanelPresenter final : public iscore::PanelPresenter
{
        Q_OBJECT
    public:
        ProcessPanelPresenter(
                const DynamicProcessList& plist,
                iscore::Presenter* parent_presenter,
                iscore::PanelView* view);

        int panelId() const override;
        void on_modelChanged() override;

        ZoomRatio zoomRatio() const
        { return m_zoomRatio; }

    private slots:
        void on_focusedViewModelChanged(const LayerModel*);
        void on_sizeChanged(const QSize& size);
        void on_zoomChanged(ZoomRatio ratio);

    private:
        void cleanup();

        const DynamicProcessList& m_processList;
        ProcessPanelGraphicsProxy* m_obj{};
        const LayerModel* m_layerModel{};
        LayerPresenter* m_processPresenter{};
        LayerView* m_layer{};

        ZoomRatio m_zoomRatio{};
};
