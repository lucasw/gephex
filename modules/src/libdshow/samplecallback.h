#ifndef INCLUDED_SAMPLE_CALLBACK_H
#define INCLUDED_SAMPLE_CALLBACK_H

#include <dshow.h>
#include <qedit.h>


/**
 * The callback mechanism for the ISampleGrabber seems 
 * not to be suitable for the purpose of copying the frames.
 *
 * Reason: You are not allowed to use a critical section in it,
 * but without that, you can't make sure that the consumer of
 * the data get's a consistent buffer of samples
 * (it could be deleted while the user copies it...).
 *
 * As experiments showed, it is even possible that the
 * callback method itself is called simultaneously (from
 * directshow). This can lead to segfaults.
 */
class SampleCallback : public ISampleGrabberCB
{
	
public:
	SampleCallback();
	~SampleCallback();
	
	STDMETHODIMP SampleCB( double SampleTime, IMediaSample * pSample );
	
    STDMETHODIMP BufferCB( double dblSampleTime,
		                   BYTE * pBuffer,
                           long lBufferSize );
	
    STDMETHODIMP_(ULONG) AddRef(void);
	
    STDMETHODIMP_(ULONG) Release(void);
	
    STDMETHODIMP QueryInterface(REFIID RefIID,
		                        void** ppOutputInterface);
	
	unsigned char* samples() const;
	
	int buffer_size() const;
	
	void sample_fetched();
	
	bool new_sample() const;
	
private:
	unsigned char* m_samples;
	int m_bufsize;

	bool m_new_sample;
};

#endif
