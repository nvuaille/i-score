#pragma once
#include <Scenario/Document/DisplayedElements/DisplayedElementsProvider.hpp>
#include <iscore/plugins/customfactory/FactoryFamily.hpp>

class DisplayedElementsProviderList final : public iscore::FactoryListInterface
{
    public:
      // TODO refactor this with constraint inspector blablabli and triggercommandfactory blablabla
      static const iscore::FactoryBaseKey& staticFactoryKey() {
          return DisplayedElementsProvider::staticFactoryKey();
      }

      iscore::FactoryBaseKey name() const final override {
          return DisplayedElementsProvider::staticFactoryKey();
      }

      void insert(std::unique_ptr<iscore::FactoryInterfaceBase> e) final override
      {
          if(auto pf = dynamic_unique_ptr_cast<DisplayedElementsProvider>(std::move(e)))
              m_list.emplace_back(std::move(pf));
      }

      const auto& list() const
      {
          return m_list;
      }

      auto make(const ConstraintModel& cst) const
      {
          auto it = find_if(m_list, [&] (const auto& elt) { return elt->matches(cst); });
          return (it != m_list.end())
                  ? (*it)->make(cst)
                  : DisplayedElementsContainer{};
      }

    private:
      std::vector<std::unique_ptr<DisplayedElementsProvider>> m_list;
};
