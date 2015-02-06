#pragma once
#include <tools/NamedObject.hpp>
#include <tools/SettableIdentifier.hpp>
class DeckPresenter;
class BoxModel;
class BoxView;
class DeckModel;

namespace iscore
{
	class SerializableCommand;
}

class BoxPresenter : public NamedObject
{
	Q_OBJECT

	public:
		BoxPresenter(BoxModel* model,
					 BoxView* view,
					 QObject* parent);
		virtual ~BoxPresenter();

		int height() const;
		int width() const;
		void setWidth(int);

		id_type<BoxModel> id() const;

	signals:
		void submitCommand(iscore::SerializableCommand*);
		void elementSelected(QObject*);

		void askUpdate();

	public slots:
		void setDuration(int duration);
		void on_deckCreated(id_type<DeckModel> deckId);
		void on_deckRemoved(id_type<DeckModel> deckId);

		void on_askUpdate();

		void on_horizontalZoomChanged(int val);

	private:
		void on_deckCreated_impl(DeckModel* m);

		// Updates the shape of the view
		void updateShape();

		BoxModel* m_model;
		BoxView* m_view;
		std::vector<DeckPresenter*> m_decks;

		int m_horizontalZoomSliderVal{};
};

