#include "samplecallback.h"

#include <cassert>
#include <iostream>

SampleCallback::SampleCallback()
: /*ISampleGrabberCB(),*/ m_samples(0), m_bufsize(0),
  m_new_sample(false)
{
}

SampleCallback::~SampleCallback() 
{
	delete[] m_samples;
}

STDMETHODIMP SampleCallback::SampleCB(double SampleTime,
									  IMediaSample * pSample )
{
	return 0;
}

STDMETHODIMP SampleCallback::BufferCB(double sample_time,
									  BYTE * pBuffer,
									  long lBufferSize )
{
	if (m_samples == 0 || m_bufsize < lBufferSize)
	{
		delete[] m_samples;
		m_samples = 0;
		
		m_bufsize = lBufferSize;
		m_samples = new unsigned char[m_bufsize];
	}
	
	if (m_samples)
	{
		assert(m_bufsize >= lBufferSize);
		memcpy(m_samples, pBuffer, lBufferSize);
		
		m_new_sample = true;
	}
	
	return 0;
}

STDMETHODIMP_(ULONG) SampleCallback::AddRef(void)
{
	return 2;
}

STDMETHODIMP_(ULONG) SampleCallback::Release(void)
{		
	return 1;
}

STDMETHODIMP SampleCallback::QueryInterface(REFIID RefIID,
											void** out)
{
	if ((RefIID == IID_ISampleGrabberCB) ||
		(RefIID == IID_IUnknown))
	{
		*out = (void*)(static_cast<ISampleGrabberCB*>(this));
		
		return NOERROR;
	}
	
	return E_NOINTERFACE;
}

unsigned char* SampleCallback::samples() const
{
	return m_samples;
}

int SampleCallback::buffer_size() const
{
	return m_bufsize;
}

void SampleCallback::sample_fetched()
{
	m_new_sample = false;
}

bool SampleCallback::new_sample() const
{
	return m_new_sample;
}

