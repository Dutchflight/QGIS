class QgsDetailedItemWidget : QWidget
{
%TypeHeaderCode
#include <qgsdetaileditemwidget.h>
%End
  public:
    QgsDetailedItemWidget( QWidget *parent /TransferThis/ = 0 );
    ~QgsDetailedItemWidget();
    void setData( const QgsDetailedItemData &data );
    void setChecked( bool flag );
};
