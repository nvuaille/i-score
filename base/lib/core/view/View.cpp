#include <core/view/View.hpp>
#include <interface/panel/PanelViewInterface.hpp>
#include <interface/panel/PanelPresenterInterface.hpp>
#include <interface/plugincontrol/MenuInterface.hpp>
#include <QDockWidget>
#include <QGridLayout>
#include <QDesktopWidget>

#include <core/application/Application.hpp>
#include <core/document/DocumentView.hpp>

using namespace iscore;

View::View(QObject* parent):
	QMainWindow{}
{
	setObjectName("View");
	setUnifiedTitleAndToolBarOnMac(true);
}

void View::addPanel(PanelViewInterface* v)
{
	m_panelsViews.insert(v);

	QDockWidget* dial = new QDockWidget(this);
	dial->setWidget(v->getWidget());

	QAction* hideDialog = new QAction(v->objectName(), nullptr);
	hideDialog->setCheckable(true);
	hideDialog->setChecked(true);

	connect(hideDialog, &QAction::triggered,
			dial,		&QDockWidget::setVisible);

	emit insertActionIntoMenubar({MenuInterface::name(ToplevelMenuElement::ViewMenu) + "/" +
								  MenuInterface::name(ViewMenuElement::Windows),
								  hideDialog});

	this->addDockWidget(v->defaultDock(), dial);
}

void View::setCentralView(DocumentView* doc)
{
	QDesktopWidget w;
	auto rect = w.availableGeometry();
	doc->setParent(this);
	this->setCentralWidget(doc);
	qDebug() << rect;
	this->resize(rect.width() * 0.75, rect.height() * 0.75);

}

