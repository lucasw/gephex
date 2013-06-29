#ifndef INCLUDED_DSHOW_UTILS_H
#define INCLUDED_DSHOW_UTILS_H

#include <dshow.h>
#include <qedit.h>

// returns the first pin with the right direction
HRESULT GetPin(IBaseFilter *filter,
  			   PIN_DIRECTION PinDir,
			   IPin **pin);

// connects two filters with the first input and
// output pin respectively
HRESULT ConnectFilters(IGraphBuilder *graph,
  					   IBaseFilter *lhs,
					   IBaseFilter *rhs);


// builds a basic grabber graph without a source to grab from
// throws an std::runtime_error if something goes wrong
//
// initializes graph, mediacontrol, samplegrabber
//

// if callback != 0, it configures the samplegrabber to use callback,
// otherwise it sets the bufferstate of the callback to true
//
// if null_renderer != 0, a null_renderer is created 
//
// TODO: callback does not work reliably (see samplegrabber.h)
//
// the grabbers media format is set to RGB32
void build_grabber_graph(IGraphBuilder**  graph,
						 IMediaControl**  mediacontrol,
						 IBaseFilter**    grabber_basefilter,
						 ISampleGrabber** samplegrabber,
						 IBaseFilter**    null_renderer,
						 ISampleGrabberCB* callback);

// connects a source filter to the samplegrabber
// (graph must be built with build_grabber_graph)
//
// note: the src filter must already have been added
//       to the graph
//
// if null_renderer != 0 it is connected to the samplegrabber
//
// throws std::runtime_error if something goes wrong
//
// returns width and height of the media stream
//
// grabber_basefilter must be the IBaseFilter pointer
// to the samplegrabber
void connect_source_filter(IGraphBuilder* graph,
			 		       IBaseFilter* grabber_basefilter,
					       ISampleGrabber* samplegrabber,
						   IBaseFilter* null_renderer,
					       IBaseFilter* src,
					       int& width, int& height);



#endif
