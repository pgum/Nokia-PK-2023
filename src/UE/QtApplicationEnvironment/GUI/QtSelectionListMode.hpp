#pragma once

#include "UeGui/IListViewMode.hpp"
#include "QtUeModeWidget.hpp"

#include <QListWidget>
#include <QFont>

namespace ue
{

class QtSelectionListMode : public QtUeModeWidget, public IUeGui::IListViewMode
{
    Q_OBJECT
public:
    QtSelectionListMode(QtPhoneNumberEdit& phoneNumberTextEdit,
                        QtStackedWidget& stackedWidget);

    OptionalSelection getCurrentItemIndex() const override;
    void addSelectionListItem(const std::string& label, const std::string& tooltip) override;
    void clearSelectionList() override;
    std::string getLabelNameFromIndex(int);


private:
    void constructGui();
    void connectSignals();
    QFont getItemFont();

    QListWidget listWidget;
    std::map<int, std::string> listIndexes;

signals:
    void itemDoubleClicked();
    void addSelectionListItemSignal(QString, QString);
    void clearSelectionListSignal();
private slots:
    void addSelectionListItemSlot(QString label, QString);
    void clearSelectionListSlot();
    void activateSlot() override;
};

}

