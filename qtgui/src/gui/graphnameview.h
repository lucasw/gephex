#ifndef INCLUDED_GRAPHNAME_VIEW_H
#define INCLUDED_GRAPHNAME_VIEW_H

#include <map>

#include <qobject.h>

#include "base/treeview.h"

#include "interfaces/igraphnamereceiver.h"

#include "utils/autoptr.h"

class QWidget;
class IModelControlReceiver;

namespace gui
{

  class GraphTopItem;
  class GraphItem;
  class SnapItem;
  class GraphNameView;
  class TreeView;
  class ISceneSequencer;


  class GraphNameViewObject : public QObject
  {
    Q_OBJECT
  public:
    GraphNameViewObject(QObject* parent, GraphNameView& view);


 public slots:

    /**
     * Is called when the model tells that the edit Graph changed
     */
    void editGraphChanged( const std::string& graphID,
			   const std::string& snapID );

    /**
     * Is called when the model tells that the rendered Graph changed
     */
    void renderedGraphChanged( const std::string& graphID );


  private:
    GraphNameView& m_view;
  };

  class GraphNameView : public IGraphNameReceiver
  {
  public:
    GraphNameView(QWidget* parent, IModelControlReceiver& gModel,
		  ISceneSequencer& sequencer);

    virtual ~GraphNameView();

    QObject* signalObject();
    QWidget* widget();

    virtual void graphExists(const std::string& graphID,
			     const std::string& snapID,
			     const std::string& graphName,
			     const std::string& snapName);

    virtual void graphNoLongerExists(const std::string& graphID,
				     const std::string& snapID);

    virtual void graphRenamed(const std::string& graphID,
			      const std::string& snapID,
			      const std::string& newGraphName,
			      const std::string& newSnapName);

    void markEditGraph( const std::string& graphID,
			const std::string& snapID );

    void markRenderedGraph( const std::string& graphID );


  private:
    typedef utils::AutoPtr<GraphItem> GraphItemPtr;
    typedef utils::AutoPtr<SnapItem> SnapItemPtr;

    typedef std::map<std::string,GraphItemPtr> GraphMap;
    typedef std::map<std::pair<std::string,std::string>,SnapItemPtr> SnapMap;

    TreeView* m_treeView;
    GraphMap m_graphs;
    SnapMap m_snaps;

    GraphNameViewObject stupidObject;

    SnapItemPtr editSnap;
    GraphItemPtr renderedGraph;

    IModelControlReceiver& m_model;

    typedef utils::AutoPtr<GraphTopItem> TopItemPtr;
    TopItemPtr m_topItem;

    ISceneSequencer* m_sequencer;
  };
			
  bool checkNamePolicy (const std::string& name);
}

#endif
